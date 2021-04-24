#include "default_menu_builder.h"

#include "slot_menu.h"
#include "default_mb_args.h"

static struct game_menu* dmb_build(struct menu_builder* mb, struct mb_args* args);

struct default_menu_builder* dmb_new(struct device_state* dev, struct menu_nav_controller* mnav)
{
	struct default_menu_builder* dmb = malloc(sizeof * dmb);

	dmb->mb.build = &dmb_build;

	dmb->dev = dev;
	dmb->mnav = mnav;

	return dmb;
}

static struct game_menu* dmb_build(struct menu_builder* mb, struct mb_args* args)
{
	struct default_menu_builder* dmb = (struct default_menu_builder*)mb;
	struct default_mb_args* dmba = (struct default_mb_args*)args;

	return (struct game_menu*)sm_new(dmb->dev, dmb->mnav, dmba->i_slot);
}