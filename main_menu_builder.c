#include "main_menu_builder.h"

#include "main_menu.h"

static struct game_menu* build_menu(struct menu_builder* mb, struct mb_args* args);
static struct menu_presenter* build_presenter(struct menu_builder* mb, struct mb_args* args);

struct main_menu_builder* mmb_new(struct device_state* dev, struct menu_nav_controller* mnav)
{
	struct main_menu_builder* mmb = malloc(sizeof * mmb);

	mmb->mb.build_menu = &build_menu;
	mmb->mb.build_presenter = &build_presenter;

	mmb->dev = dev;
	mmb->mnav = mnav;

	return mmb;
}


static struct game_menu* build_menu(struct menu_builder* mb, struct mb_args* args)
{
	struct main_menu_builder* mmb = (void*)mb;

	return (void*)mm_new(mmb->dev, mmb->mnav);
}

static struct menu_presenter* build_presenter(struct menu_builder* mb, struct mb_args* args)
{
	struct game_menu* gm = build_menu(mb, args);
	struct menu_presenter* mp = mp_new(gm);
	
	return mp;
}
