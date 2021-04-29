#include "slot_menu.h"

#include "types.h"
#include "memory_pak.h"
#include "console.h"
#include "device_state.h"


static void sm_update(const struct go_delegate* base, struct game_object* go);
const struct go_delegate SM_UPDATE[] = { { sm_update, GM_UPDATE } };

static void sm_draw(const struct go_delegate* base, struct game_object* go);
const struct go_delegate SM_DRAW[] = { { sm_draw } };

const struct go_type SM_TYPE[] = { { NULL, SM_UPDATE, SM_DRAW } };


struct slot_menu* sm_new(struct device_state* dev, struct menu_nav_controller* mnav, u8 i_slot)
{
	struct slot_menu* sm = malloc(sizeof * sm);

	_gm_init(&sm->gm, SM_TYPE, dev, mnav, 0);

	sm->i_slot = i_slot;

	return sm;
}


static void sm_update(const struct go_delegate* base, struct game_object* go)
{
	struct slot_menu* sm = (void*)go;

	struct device_state* dev = sm->gm.dev;
	struct controller_data keys = dev->keys_d;

	// for safety
	if (keys.c[0].L
		&& keys.c[0].Z
		&& keys.c[0].R)
	{
		mpk_format((void*)dev->accessories[sm->i_slot]);
	}
	else if (keys.c[0].start)
	{
		if (sm->rumble)
			rumble_stop(0);

		else
			rumble_start(0);

		sm->rumble = 1 - sm->rumble;
	}

	_god_invoke(base, go);
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
	struct memory_pak* mpk = (void*)dev.accessories[sm.i_slot];

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

static void sm_draw(const struct go_delegate* base, struct game_object* go)
{
	struct slot_menu* sm = (void*)go;
	struct device_state* dev = sm->gm.dev;
	struct accessory* acc = dev->accessories[sm->i_slot];

	draw_header(*sm, *acc);

	if (!has_error(*sm, *dev, *acc))
		draw_entries(*sm, *dev);
}
