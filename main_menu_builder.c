#include "main_menu_builder.h"

#include "main_menu.h"

static void *build_menu(struct menu_builder *mb, struct mb_args *args);
static void *build_presenter(struct menu_builder *mb, struct mb_args *args);

const struct mb_type MMB_TYPE[] = { { build_menu, build_presenter } };

struct main_menu_builder *mmb_new(struct device_state *dev, struct controller_manager *cman, struct menu_nav_controller *mnav)
{
	struct main_menu_builder *mmb = malloc(sizeof * mmb);

	mmb->mb.mb_type = MMB_TYPE;

	mmb->dev = dev;
	mmb->cman = cman;
	mmb->mnav = mnav;

	return mmb;
}


static void *build_menu(struct menu_builder *mb, struct mb_args *args)
{
	struct main_menu_builder *mmb = (void *)mb;

	return mm_new(mmb->dev, mmb->cman, mmb->mnav);
}

static void *build_presenter(struct menu_builder *mb, struct mb_args *args)
{
	struct game_menu *gm = build_menu(mb, args);
	return mp_new(gm);
}
