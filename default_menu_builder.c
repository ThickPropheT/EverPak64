#include "default_menu_builder.h"

#include "default_mb_args.h"
#include "slot_menu.h"

static void* build_menu(struct menu_builder* mb, struct mb_args* args);
static void* build_presenter(struct menu_builder* mb, struct mb_args* args);

const struct mb_type DMB_TYPE[] = { { build_menu, build_presenter } };

struct default_menu_builder* dmb_new(struct device_state* dev, struct menu_nav_controller* mnav)
{
	struct default_menu_builder* dmb = malloc(sizeof * dmb);

	dmb->mb.mb_type = DMB_TYPE;

	dmb->dev = dev;
	dmb->mnav = mnav;

	return dmb;
}


static void* build_menu(struct menu_builder* mb, struct mb_args* args)
{
	struct default_menu_builder* dmb = (void*)mb;
	struct default_mb_args* dmba = (void*)args;

	return sm_new(dmb->dev, dmb->mnav, dmba->i_slot);
}

static void* build_presenter(struct menu_builder* mb, struct mb_args* args)
{
	struct game_menu* gm = build_menu(mb, args);
	return mp_new(gm);
}
