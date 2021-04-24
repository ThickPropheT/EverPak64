#include "root_menu.h"

#include <stddef.h>
#include <malloc.h>
#include "console.h"


// TODO i don't think these are wired up
#define I_DEFAULT_SELECTED	0
#define I_DEFAULT_DEPTH		0


static void rm_update(struct game_object* go);
static void rm_draw(struct game_object* go);

const struct go_type RM[] = { { rm_update, rm_draw } };


struct root_menu* rm_new(struct device_state* dev, struct menu_nav_controller* mnav)
{
	struct root_menu* rm = malloc(sizeof * rm);

	_gm_init(&rm->gm, RM, dev, N_SLOTS);

	rm->mnav = mnav;

	for (int i = 0; i < N_SLOTS; i++)
		rm->slots[i] = sm_new(dev, mnav, i);

	return rm;
}

struct slot_menu* rm_get_current(struct root_menu* rm)
{
	return rm->slots[rm->gm.i_hovered_item];
}

static void rm_update(struct game_object* go)
{
	struct root_menu* rm = (struct root_menu*)go;
	struct game_menu* gm = &rm->gm;

	struct controller_data keys = gm->dev->keys_d;

	if (keys.c[0].up)
	{
		_gm_hover_prev(gm);
	}
	else if (keys.c[0].down)
	{
		_gm_hover_next(gm);
	}
	else if (keys.c[0].left)
	{
		_gm_hover_prev(gm);
	}
	else if (keys.c[0].right)
	{
		_gm_hover_next(gm);
	}
	else if (keys.c[0].A)
	{
		mnav_to_sm(rm->mnav, gm->i_hovered_item);
	}
}

static void rm_draw(struct game_object* go)
{
	struct root_menu* rm = (struct root_menu*)go;
	struct device_state* dev = rm->gm.dev;

	cprintf("Select Controller (A)\n\n");

	for (u8 i = 0; i < N_SLOTS; i++)
	{
		struct accessory acc = *dev->accessories[i];

		u8 sn = acc_get_number(acc);

		char* sel =
			i == rm->gm.i_hovered_item
			? ">"
			: " ";

		u16 f_slot = get_flag(acc.i_slot);

		char* pres =
			dev->controllers & f_slot
			? "+"
			: " ";

		cprintf("%s [%s] Slot %u\n", sel, pres, sn);
	}
}
