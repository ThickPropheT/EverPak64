#include "slot_menu.h"

#include "accessory.h"

#define FIRST_SLOT_FLAG 0xF000
#define FLAG_WIDTH		4


#define cprintf(...) { \
	cs_printfln(cc, __VA_ARGS__); \
}


struct console_context cc;


void sm_init(struct console_context* c)
{
	cc = *c;
}

struct slot_menu sm_new(u8 i_slot)
{
	return (struct slot_menu) { i_slot, { 0, 0 } };
}



u8 sm_get_slot_number(struct slot_menu m)
{
	return m.i_slot + 1;
}

u16 sm_get_slot_flag(struct slot_menu m)
{
	return FIRST_SLOT_FLAG >> (m.i_slot * FLAG_WIDTH);
}



void sm_update(struct slot_menu* sm, struct menu_state* ms, struct device_state dev)
{
	struct controller_data keys = dev.keys;

	if (keys.c[0].B)
	{
		ms_pop(ms);
	}
}



void draw_header(struct slot_menu sm, struct accessory acc)
{
	u8 sn = sm_get_slot_number(sm);
	char* acc_name = accessory_names[acc.type];

	cprintf("Controller %i [%s]", sn, acc_name);
	cprintf("Back (B)");
}

u8 has_error(struct slot_menu sm, struct device_state dev, struct accessory acc)
{
	u16 f_slot = sm_get_slot_flag(sm);

	//if (!(dev.controllers & f_slot))
	//{
	//	cprintf("Controller missing.\n");
	//	return 1;
	//}

	if (!(dev.accessories_f & f_slot))
	{
		cprintf("Memory Pak missing.\n");
		return 1;
	}

	if (!acc.status)
		return 0;

	switch (acc.status)
	{
	case MPAK_STATUS_UNREADABLE:
		cprintf("Memory Pak missing or unreadable.\n");
		break;

	case MPAK_STATUS_UNFORMATTED:
		cprintf("Memory Pak unformatted.\n");
		break;
	}

	return 1;
}

void draw_entries(struct slot_menu sm, struct device_state dev)
{
	cprintf("1 Banbo-Jazookie\n2 700 Globe in Eye\n3 Oh Hey, Mario 64\n4 Oculus of Time\n");
}

void sm_draw(struct slot_menu* sm, struct device_state dev)
{
	struct accessory acc = dev.accessories[sm->i_slot];

	draw_header(*sm, acc);

	if (!has_error(*sm, dev, acc))
		draw_entries(*sm, dev);
}
