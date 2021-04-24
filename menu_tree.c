#include "menu_tree.h"

#include "math.h"
#include "menu_nav_controller.h"
#include "menu_builder_table.h"
#include "default_menu_builder.h"
#include "game_object.h"

struct menu_tree mt_new(struct device_state* dev)
{
	struct menu_state* ms = ms_new(MAX_MENUS);

	struct menu_builder_table* mbt = mbt_new();

	struct menu_nav_controller* mnav = mnav_new(ms, mbt);

	mbt->default_builder = (struct menu_builder*)dmb_new(dev, mnav);

	struct root_menu* rm = rm_new(dev, mnav);
	ms_push(ms, (struct game_menu*)rm);

	return (struct menu_tree) { dev, ms, rm };
}

void mt_update(struct menu_tree * mt)
{
	// TODO prevents weirdness if controller 1 is removed
	// TODO update this when any/all controllers can input
	if (!(mt->dev->controllers & CONTROLLER_1_INSERTED))
		return;

	//struct root_menu* rm = mt->rm;

	go_update((struct game_object*)mt->ms->mn->gm);

	//switch (mt->ms->i_depth)
	//{
	//case ROOT_MENU:
	//	go_update((struct game_object*)rm);
	//	break;

	//case SLOT_MENU:
	//	go_update((struct game_object*)rm_get_current(rm));
	//	break;
	//}
}

void mt_draw(struct menu_tree* mt)
{
	go_draw((struct game_object*)mt->ms->mn->gm);

	/*struct root_menu* rm = mt->rm;

	switch (mt->ms->i_depth)
	{
	case ROOT_MENU:
		go_draw((struct game_object*)rm);
		break;

	case SLOT_MENU:
		go_draw((struct game_object*)rm_get_current(rm));
		break;
	}*/
}
