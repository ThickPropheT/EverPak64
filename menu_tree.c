#include "menu_tree.h"

#include "math.h"

void mt_init(struct console_context* c)
{
	rm_init(c);
	sm_init(c);
}

struct menu_tree mt_new(void)
{
	struct menu_state ms = ms_init(MAX_MENUS);
	struct root_menu rm = rm_new();

	return (struct menu_tree) { ms, rm };
}

void mt_update(struct menu_tree* mt, struct device_state* dev)
{
	struct root_menu* rm = &mt->rm;
	struct menu_state* ms = &mt->ms;

	switch (ms->i_depth)
	{
	case ROOT_MENU:
		rm_update(rm, ms, dev);
		break;

	case SLOT_MENU:
		sm_update(rm_get_current(rm), ms, dev);
		break;
	}
}

void mt_draw(struct menu_tree* mt, struct device_state dev)
{
	struct root_menu* rm = &mt->rm;

	switch (mt->ms.i_depth)
	{
	case ROOT_MENU:
		rm_draw(rm, dev);
		break;

	case SLOT_MENU:
		sm_draw(rm_get_current(rm), dev);
		break;
	}
}
