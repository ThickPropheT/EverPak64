#include "menu_tree.h"

#include "menu_builder_table.h"
#include "menu_builder_registrar.h"
#include "game_object.h"


struct menu_tree mt_new(struct device_state* dev)
{
	struct menu_state* ms = ms_new();
	struct menu_builder_table* mbt = mbt_new();
	struct menu_nav_controller* mnav = mnav_new(ms, mbt);

	mbr_register(mbt, dev, mnav);

	ms_init_root(ms, (struct game_menu*)rm_new(dev, mnav));

	return (struct menu_tree) { dev, mnav };
}

static inline struct game_object* get_current(struct menu_tree* mt)
{
	// TODO consider moving this into menu_nav_controller
	return (struct game_object*)mt->mnav->ms->mn->gm;
}

void mt_update(struct menu_tree* mt)
{
	// TODO prevents weirdness if controller 1 is removed
	// TODO update this when any/all controllers can input
	if (!(mt->dev->controllers & CONTROLLER_1_INSERTED))
		return;

	go_update(get_current(mt));
}

void mt_draw(struct menu_tree* mt)
{
	go_draw(get_current(mt));
}
