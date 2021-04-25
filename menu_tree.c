#include "menu_tree.h"

#include "menu_state.h"
#include "menu_builder_table.h"
#include "menu_nav_controller.h"
#include "menu_builder_registrar.h"
#include "main_menu.h"
#include "game_object.h"


struct menu_tree mt_new(struct device_state* dev)
{
	struct menu_state* ms = ms_new();
	struct menu_builder_table* mbt = mbt_new();
	struct menu_nav_controller* mnav = mnav_new(dev, ms, mbt);

	mbreg_register(mbt, dev, mnav);

	ms_init_root(ms, (struct game_menu*)mm_new(dev, mnav));

	return (struct menu_tree) { dev, mnav };
}


void mt_update(struct menu_tree* mt)
{
	// TODO prevents weirdness if controller 1 is removed
	// TODO update this when any/all controllers can input
	if (!(mt->dev->controllers & CONTROLLER_1_INSERTED))
		return;

	// TODO ooowee he's trying
	struct menu_node* mn = mt->mnav->ms->root;

	while (mn != NULL)
	{
		go_update((struct game_object*)mn->mp->gm);

		mn = mn->next;
	}
}

void mt_draw(struct menu_tree* mt)
{
	struct menu_node* mn = mt->mnav->ms->root;

	while (mn != NULL)
	{
		go_draw((struct game_object*)mn->mp->gm);

		mn = mn->next;
	}
}
