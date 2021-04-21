#include "menu_tree.h"

#include "math.h"

struct menu_tree mt_new(void)
{
	struct menu_state ms = ms_new(MAX_MENUS);
	struct root_menu rm = rm_new();

	return (struct menu_tree) { ms, rm };
}

void mt_update(struct game_state gs, struct menu_tree * mt)
{
	struct root_menu* rm = &mt->rm;
	struct menu_state* ms = &mt->ms;

	switch (ms->i_depth)
	{
	case ROOT_MENU:
		rm_update(gs, rm);
		break;

	case SLOT_MENU:
		sm_update(gs, rm_get_current(rm));
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
