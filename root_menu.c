#include "root_menu.h"

#include <stddef.h>
#include <malloc.h>
#include "console.h"


// TODO i don't think these are wired up
#define I_DEFAULT_SELECTED	0
#define I_DEFAULT_DEPTH		0


static void rm_update(struct game_state gs, struct game_object* go);
static void rm_draw(struct game_state gs, struct game_object* go);

const struct _go_vtable RM[] = { { rm_update, rm_draw } };


struct root_menu* rm_new(void)
{
	struct root_menu* rm = malloc(sizeof * rm);

	rm->go._vtable = RM;
	rm->go.can_update = 1;
	rm->go.can_draw = 1;

	struct menu m = { 0, N_SLOTS };
	rm->m = m;

	for (int i = 0; i < N_SLOTS; i++)
		rm->slots[i] = sm_new(i);

	return rm;
}

struct slot_menu* rm_get_current(struct root_menu* rm)
{
	return rm->slots[rm->m.i_item];
}

static void rm_update(struct game_state gs, struct game_object* go)
{
	struct root_menu* rm = (struct root_menu*)go;
	struct menu_state* ms = (struct menu_state*)gs.ms;

	struct controller_data keys = gs.dev->keys_d;

	if (keys.c[0].up)
	{
		m_prev_item(&rm->m);
	}
	else if (keys.c[0].down)
	{
		m_next_item(&rm->m);
	}
	else if (keys.c[0].left)
	{
		m_prev_item(&rm->m);
	}
	else if (keys.c[0].right)
	{
		m_next_item(&rm->m);
	}
	else if (keys.c[0].A)
	{
		ms_pushd(ms);
	}
}

static void rm_draw(struct game_state gs, struct game_object* go)
{
	struct root_menu* rm = (struct root_menu*)go;

	cprintf("Select Controller (A)\n\n");

	for (u8 i = 0; i < N_SLOTS; i++)
	{
		struct accessory acc = *gs.dev->accessories[i];

		u8 sn = acc_get_number(acc);

		char* sel =
			i == rm->m.i_item
			? ">"
			: " ";

		u16 f_slot = get_flag(acc.i_slot);

		char* pres =
			gs.dev->controllers & f_slot
			? "+"
			: " ";

		cprintf("%s [%s] Slot %u\n", sel, pres, sn);
	}
}
