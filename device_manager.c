#include "device_manager.h"

#include "memory_pak.h"
#include "rumble_pak.h"

static struct accessory* resolve_rpak(u8 i_slot)
{
	// Brawler64 controllers report mempaks as a rumble pak.
	// TODO could/should the result of this call be cached?
	if (!validate_mempak(i_slot))
		return (struct accessory*)mpk_new(i_slot);

	return (struct accessory*)rpk_new(i_slot);
}

static struct accessory* resolve_acc(struct device_state dev, u8 i_slot)
{
	u8 type = ACCESSORY_NONE;

	if (dev.acc_flags & get_flag(i_slot))
		type = identify_accessory(i_slot);

	switch (type)
	{
	case ACCESSORY_MEMPAK:
		return (struct accessory*)mpk_new(i_slot);

	case ACCESSORY_RUMBLEPAK:
		return resolve_rpak(i_slot);

	default:
		return acc_new(i_slot);
	}
}

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

static void update_accessories(struct device_state* dev)
{
	for (u8 i = 0; i < N_SLOTS; i++)
	{
		struct accessory* acc = dev->accessories[i];

		if (!acc->go.can_update)
			continue;

		go_update((struct game_object*)acc);
	}
}

void dev_poll(struct device_state* dev)
{
	controller_scan();

	struct controller_data out;
	u16 acc = get_accessories_present(&out);

	set_acc_flags(dev, acc);
	update_accessories(dev);

	dev->keys_d = get_keys_down();
}