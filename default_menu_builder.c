#include "default_menu_builder.h"

#include "default_mb_args.h"
#include "slot_menu.h"

static struct game_menu* build_menu(struct menu_builder* mb, struct mb_args* args);
static struct menu_presenter* build_presenter(struct menu_builder* mb, struct mb_args* args);

struct default_menu_builder* dmb_new(struct device_state* dev, struct menu_nav_controller* mnav)
{
	struct default_menu_builder* dmb = malloc(sizeof * dmb);

	dmb->mb.build_menu = &build_menu;
	dmb->mb.build_presenter = &build_presenter;

	dmb->dev = dev;
	dmb->mnav = mnav;

	return dmb;
}


static struct game_menu* build_menu(struct menu_builder* mb, struct mb_args* args)
{
	struct default_menu_builder* dmb = (void*)mb;
	struct default_mb_args* dmba = (void*)args;

	return (void*)sm_new(dmb->dev, dmb->mnav, dmba->i_slot);
}

static struct menu_presenter* build_presenter(struct menu_builder* mb, struct mb_args* args)
{
	struct game_menu* gm = build_menu(mb, args);
	struct menu_presenter* mp = mp_new(gm);

	return mp;
}
