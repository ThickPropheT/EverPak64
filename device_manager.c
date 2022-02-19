#include "device_manager.h"

#include "accessory_factory.h"



static void update(const struct go_delegate* base, struct game_object* go);
const struct go_delegate DEVM_UPDATE[] = { { update } };

const struct go_type DEVM_TYPE[] = { { NULL, DEVM_UPDATE } };


static struct device_state* dev_new(void)
{
	struct device_state* dev = malloc(sizeof * dev);

	for (u8 i = 0; i < N_SLOTS; i++)
		// TODO this will result in all accessories being accessory
		// TODO since accessories_f will still be 0 becuase
		// TODO get_accessories_present hasn't yet been called.
		dev->accessories[i] = resolve_acc(*dev, i);

	return dev;
}

struct device_manager* devm_new(struct trigger* dev_changed)
{
	struct device_manager* devm = malloc(sizeof * devm);

	_go_init(&devm->go, DEVM_TYPE);

	devm->go.can_update = 1;
	devm->go.can_draw = 0;

	devm->dev_changed = dev_changed;

	devm->dev = dev_new();

	return devm;
}

static void replace_acc(struct device_state* dev, u8 i_slot)
{
	free(dev->accessories[i_slot]);
	dev->accessories[i_slot] = resolve_acc(*dev, i_slot);
}

static void acc_flags_changed(struct device_state* dev, u16 from, u16 to)
{
	for (u8 i = 0; i < N_SLOTS; i++)
	{
		u16 f = get_flag(i);
		u8 has_f_changed = did_flag_change(f, from, to);

		if (!has_f_changed)
			continue;

		replace_acc(dev, i);
	}
}

static void set_acc_flags(struct device_manager* devm, u16 value)
{
	struct device_state* dev = devm->dev;

	if (dev->acc_flags == value)
		return;

	u16 old_value = dev->acc_flags;

	dev->acc_flags = value;

	acc_flags_changed(dev, old_value, value);

	trg_set(devm->dev_changed);
}

static void update_accessories(struct device_state* dev)
{
	for (u8 i = 0; i < N_SLOTS; i++)
	{
		go_update((void*)dev->accessories[i]);
	}
}

u8 keys_are_equal(struct SI_condat* keys1, struct SI_condat* keys2)
{
	struct SI_condat k1 = *keys1;
	struct SI_condat k2 = *keys2;

	return k1.A == k2.A
		&& k1.B == k2.B
		&& k1.Z == k2.Z
		&& k1.start == k2.start

		&& k1.up == k2.up
		&& k1.down == k2.down
		&& k1.left == k2.left
		&& k1.right == k2.right

		&& k1.L == k2.L
		&& k1.R == k2.R

		&& k1.C_up == k2.C_up
		&& k1.C_down == k2.C_down
		&& k1.C_left == k2.C_left
		&& k1.C_right == k2.C_right

		&& k1.x == k2.x
		&& k1.y == k2.y;
}

static void update(const struct go_delegate* base, struct game_object* go)
{
	struct device_manager* devm = (void*)go;
	struct device_state* dev = devm->dev;
	
	controller_scan();

	struct controller_data out;
	u16 acc = get_accessories_present(&out);

	set_acc_flags(devm, acc);

	update_accessories(dev);

	struct controller_data keys_d = get_keys_down();

	if (!keys_are_equal(dev->keys_d.c, keys_d.c))
	{
		dev->keys_d = keys_d;
		dev->keys_h = get_keys_held();
		dev->keys_u = get_keys_up();

		trg_set(devm->dev_changed);
	}
}
