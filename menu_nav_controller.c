#include "menu_nav_controller.h"

#include <malloc.h>
#include "menu_presenter_resolver.h"

struct menu_nav_controller *mnav_new(struct controller_manager *cman, struct menu_state *ms, struct menu_builder_table *mbt)
{
	struct menu_nav_controller *mnav = malloc(sizeof * mnav);

	mnav->cman = cman;
	mnav->ms = ms;
	mnav->mbt = mbt;

	return mnav;
}

void mnav_to_sm(struct menu_nav_controller *mnav, u8 i_slot)
{
	struct menu_presenter *acc_menu =
		mpres_acc(mnav->mbt, mnav->cman, i_slot);

	ms_push(mnav->ms, acc_menu);
}

void mnav_pop(struct menu_nav_controller *mnav)
{
	ms_pop(mnav->ms);
}