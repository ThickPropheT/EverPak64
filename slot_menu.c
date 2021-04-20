#include "slot_menu.h"

#include "types.h"
#include "memory_pak.h"
#include "console.h"


struct slot_menu sm_new(u8 i_slot)
{
	return (struct slot_menu) { i_slot, { 0, 0 } };
}


void sm_update(struct slot_menu* sm, struct menu_state* ms, struct device_state* dev)
{
	struct controller_data keys = dev->keys_d;

	// for safety
	if (keys.c[0].L
		&& keys.c[0].Z
		&& keys.c[0].R)
	{
		mpk_format((struct memory_pak*)dev->accessories[sm->i_slot]);
	}
	else if (keys.c[0].B)
	{
		ms_pop(ms);
	}
	else if (keys.c[0].start)
	{
		if (sm->rumble)
			rumble_stop(0);

		else
			rumble_start(0);

		sm->rumble = 1 - sm->rumble;
	}
}



void draw_header(struct slot_menu sm, struct accessory acc)
{
	u8 sn = acc_get_number(acc);
	char* acc_name = accessory_names[acc.type];

	cprintf("Controller %u [%s]", sn, acc_name);
	cprintf("Format (Z)");
	cprintf("Back (B)");
}

u8 has_error(struct slot_menu sm, struct device_state dev, struct accessory acc)
{
	u16 f_slot = get_flag(acc.i_slot);

	//if (!(dev.controllers & f_slot))
	//{
	//	cprintf("Controller missing.\n");
	//	return 1;
	//}

	if (!(dev.acc_flags & f_slot))
	{
		cprintf("Memory Pak missing.");
		return 1;
	}

	if (!acc.status)
		return 0;

	switch (acc.status)
	{
	case MPAK_STATUS_UNREADABLE:
		cprintf("Memory Pak missing or unreadable.");
		break;

	case MPAK_STATUS_UNFORMATTED:
		cprintf("Memory Pak unformatted.");
		break;
	}

	return 1;
}

void draw_entries(struct slot_menu sm, struct device_state dev)
{
	struct memory_pak* mpk = (struct memory_pak*)dev.accessories[sm.i_slot];

	for (u8 i = 0; i < ENTRIES_LEN; i++)
	{
		entry_structure_t es = mpk->entries[i];

		// TODO wrap entry_structure_t to cache this err state
		//s8 err = get_mempak_entry(sm.i_slot, i, &es);
		s8 err = 0;

		switch (err)
		{
		case 0:
			cprintf("%2i %s", i + 1, es.name);
			break;

		case -1:
			// entry out of bounds or entry_data is null
			cprintf("-1");
			break;

		case -2:
			// mempak is bad or not present
			cprintf("-2");
			break;
		}
	}
}

void sm_draw(struct slot_menu* sm, struct device_state dev)
{
	struct accessory* acc = dev.accessories[sm->i_slot];

	draw_header(*sm, *acc);

	if (!has_error(*sm, dev, *acc))
		draw_entries(*sm, dev);
}
