#include "device_manager.h"

#include "accessory_factory.h"



static void update(const struct go_delegate* base, struct game_object* go);
const struct go_delegate UPDATE[] = { { update } };

const struct go_type TYPE[] = { { NULL, UPDATE } };


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

struct device_manager* devm_new(void)
{
	struct device_manager* devm = malloc(sizeof * devm);

	_go_init(&devm->go, TYPE);

	devm->go.can_update = 1;
	devm->go.can_draw = 0;

	devm->dev = dev_new();

	return devm;
}

static void update(const struct go_delegate* base, struct game_object* go)
{
	//struct device_manager* devm = (void*)go;

	struct controller_data out;
	controller_read(&out);
}

//static void replace_acc(struct device_state* dev, u8 i_slot)
//{
//	free(dev->accessories[i_slot]);
//	dev->accessories[i_slot] = resolve_acc(*dev, i_slot);
//}

//static void acc_flags_changed(struct device_state* dev, u16 from, u16 to)
//{
//	for (u8 i = 0; i < N_SLOTS; i++)
//	{
//		u16 f = get_flag(i);
//		u8 has_f_changed = did_flag_change(f, from, to);
//
//		if (!has_f_changed)
//			continue;
//
//		replace_acc(dev, i);
//	}
//}

//static void set_acc_flags(struct device_state* dev, u16 value)
//{
//	if (dev->acc_flags == value)
//		return;
//
//	u16 old_value = dev->acc_flags;
//
//	dev->acc_flags = value;
//
//	acc_flags_changed(dev, old_value, value);
//}

//static void update_accessories(struct device_state* dev)
//{
//	for (u8 i = 0; i < N_SLOTS; i++)
//	{
//		go_update((struct game_object*)dev->accessories[i]);
//	}
//}

void dev_poll(struct device_state* dev)
{
	struct controller_data out;
	controller_read(&out);
	//controller_scan();

	//struct controller_data out;
	//u16 acc = get_accessories_present(&out);

	//set_acc_flags(dev, acc);

	//update_accessories(dev);

	/*dev->keys_d = get_keys_down();
	dev->keys_h = get_keys_held();
	dev->keys_u = get_keys_up();*/
}
