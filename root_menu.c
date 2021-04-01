#include "root_menu.h"

#include <stddef.h>
#include <malloc.h>


// TODO i don't think these are wired up
#define I_DEFAULT_SELECTED	0
#define I_DEFAULT_DEPTH		0


#define cprintf(...) { \
	cs_printfln(cc, __VA_ARGS__); \
}

struct console_context cc;

void rm_init(struct console_context* c)
{
	cc = *c;
}

struct root_menu rm_new(void)
{
	struct root_menu rm = { { 0, N_SLOTS } };

	for (int i = 0; i < N_SLOTS; i++)
		rm.slots[i] = sm_new(i);

	return rm;
}

struct slot_menu* rm_get_current(struct root_menu* rm)
{
	return &(rm->slots[rm->m.i_item]);
}

void rm_update(struct root_menu* rm, struct menu_state* ms, struct device_state* dev)
{
	struct controller_data keys = dev->keys;

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
		ms_push(ms);
	}
}

void rm_draw(struct root_menu* rm, struct device_state dev)
{
	cprintf("Select Controller (A)\n\n");

	for (u8 i = 0; i < N_SLOTS; i++)
	{
		struct slot_menu mi = rm->slots[i];
		u8 sn = sm_get_slot_number(mi);

		char* sel =
			i == rm->m.i_item
			? ">"
			: " ";

		u16 f_slot = sm_get_slot_flag(mi);

		char* pres =
			dev.controllers & f_slot
			? "+"
			: " ";

		cprintf("%s [%s] Slot %u\n", sel, pres, sn);
	}
}
