#include "device_manager.h"

#include "accessory_factory.h"

static void replace_acc(struct device_state* dev, u8 i_slot)
{
	free(dev->accessories[i_slot]);
	dev->accessories[i_slot] = resolve_acc(*dev, i_slot);
}

struct device_state dev_new(void)
{
	struct device_state dev = { };

	for (u8 i = 0; i < N_SLOTS; i++)
		// TODO this will result in all accessories being accessory
		// TODO since accessories_f will still be 0 becuase
		// TODO get_accessories_present hasn't yet been called.
		dev.accessories[i] = resolve_acc(dev, i);

	return dev;
}



static void acc_flags_changed(struct device_state* dev, u16 from, u16 to)
{
	dev->controllers = get_controllers_present();

	for (u8 i = 0; i < N_SLOTS; i++)
	{
		u16 f = get_flag(i);
		u8 has_f_changed = (from & f) != (to & f);

		if (!has_f_changed)
			continue;

		replace_acc(dev, i);
	}
}

static void set_acc_flags(struct device_state* dev, u16 value)
{
	if (dev->acc_flags == value)
		return;

	u16 old_value = dev->acc_flags;

	dev->acc_flags = value;

	acc_flags_changed(dev, old_value, value);
}

static void update_accessories(struct game_state gs, struct device_state* dev)
{
	for (u8 i = 0; i < N_SLOTS; i++)
	{
		go_update(gs, (struct game_object*)dev->accessories[i]);
	}
}

void dev_poll(struct game_state gs, struct device_state* dev)
{
	controller_scan();

	struct controller_data out;
	u16 acc = get_accessories_present(&out);

	set_acc_flags(dev, acc);
	update_accessories(gs, dev);

	dev->keys_d = get_keys_down();
}