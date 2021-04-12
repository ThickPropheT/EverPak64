#include "device.h"

#include <stdlib.h>
#include "accessory.h"
#include "memory_pak.h"


#define FIRST_SLOT_FLAG 0xF000
#define FLAG_WIDTH		4


u16 get_flag(u8 i_slot)
{
	return FIRST_SLOT_FLAG >> (i_slot * FLAG_WIDTH);
}


static struct accessory* resolve_rpak(u8 i_slot)
{
	return acc_new(i_slot);
}

static struct accessory* resolve_acc(struct device_state dev, u8 i_slot)
{
	u8 type = ACCESSORY_NONE;

	// TODO migrate sm_get_slot_flag somewhere for common access
	if (dev.accessories_f & (0xF000 >> (i_slot * 4)))
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
		dev.accessories[i] = resolve_acc(dev, i);

	return dev;
}

void dev_poll(struct device_state* ds)
{
	controller_scan();

	struct controller_data out;
	u16 acc = get_accessories_present(&out);

	ds->acc_f_changed = ds->accessories_f != acc;
	ds->accessories_f = acc;

	if (ds->acc_f_changed)
	{
		ds->controllers = get_controllers_present();

		// TODO find a way to optimize this so that if the acc
		// TODO didn't change then it doesn't need to be replaced
		for (u8 i = 0; i < N_SLOTS; i++)
			replace_acc(ds, i);

		// TODO ensure this interacts correctly with resolve_acc
		// TODO AND add 'dirty' flag for go_update
		for (u8 i = 0; i < N_SLOTS; i++)
			go_update((struct game_object*)ds->accessories[i]);
	}

	ds->keys_d = get_keys_down();
}
