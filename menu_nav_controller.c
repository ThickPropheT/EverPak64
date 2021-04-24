#include "menu_nav_controller.h"

#include <malloc.h>
#include "menu_builder_resolver.h"

struct menu_nav_controller* mnav_new(struct menu_state* ms, struct menu_builder_table* mbt)
{
	struct menu_nav_controller* mnav = malloc(sizeof * mnav);

	mnav->ms = ms;
	mnav->mbt = mbt;

	return mnav;
}

void mnav_to_sm(struct menu_nav_controller* mnav, u8 i_slot)
{
	ms_push(mnav->ms, mbres_build_default(mnav->mbt, i_slot));
}

void mnav_pop(struct menu_nav_controller* mnav)
{
	ms_pop(mnav->ms);
}