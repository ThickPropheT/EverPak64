#include "menu_nav_controller.h"

#include <malloc.h>
#include "menu_builder.h"
#include "default_mb_args.h"

struct menu_nav_controller* mnav_new(struct menu_state* ms, struct menu_builder_table* mbt)
{
	struct menu_nav_controller* mnav = malloc(sizeof * mnav);

	mnav->ms = ms;
	mnav->mbt = mbt;

	return mnav;
}

void mnav_to_sm(struct menu_nav_controller* mnav, u8 i_slot)
{
	struct default_mb_args* args = dmba_new(i_slot);
	struct game_menu* gm = mb_build(mnav->mbt->default_builder, (struct mb_args*)args);
	
	ms_push(mnav->ms, gm);

	free(args);
}

void mnav_pop(struct menu_nav_controller* mnav)
{
	ms_pop(mnav->ms);
}