#include "main_menu_builder.h"

#include "main_menu.h"

static struct menu_presenter* mmb_build(struct menu_builder* mb, struct mb_args* args);

struct main_menu_builder* mmb_new(struct device_state* dev, struct menu_nav_controller* mnav)
{
	struct main_menu_builder* mmb = malloc(sizeof * mmb);

	mmb->mb.build = &mmb_build;

	mmb->dev = dev;
	mmb->mnav = mnav;

	return mmb;
}

static struct menu_presenter* mmb_build(struct menu_builder* mb, struct mb_args* args)
{
	struct main_menu_builder* mmb = (struct main_menu_builder*)mb;

	struct game_menu* gm = (struct game_menu*)mm_new(mmb->dev, mmb->mnav);
	struct menu_presenter* mp = mp_new(gm);
	
	return mp;
}
