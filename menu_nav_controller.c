#include "menu_nav_controller.h"

#include <malloc.h>
#include "menu_presenter_resolver.h"

struct menu_nav_controller* mnav_new(struct device_state* dev, struct menu_state* ms, struct menu_builder_table* mbt)
{
	struct menu_nav_controller* mnav = malloc(sizeof * mnav);

	mnav->dev = dev;
	mnav->ms = ms;
	mnav->mbt = mbt;

	return mnav;
}

void mnav_to_sm(struct menu_nav_controller* mnav, u8 i_slot)
{
	struct menu_state* ms = mnav->ms;
	struct menu_builder_table* mbt = mnav->mbt;

	struct menu_presenter* acc_menu = mpres_acc(mbt, mnav->dev, i_slot);
	ms_push(ms, acc_menu);
}

void mnav_pop(struct menu_nav_controller* mnav)
{
	ms_pop(mnav->ms);
}