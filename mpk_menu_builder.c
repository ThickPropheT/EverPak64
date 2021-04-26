#include "mpk_menu_builder.h"

#include "acc_mb_args.h"
#include "memory_pak.h"
#include "mpk_menu.h"
#include "acc_menu_presenter.h"

static struct menu_presenter* mpkmb_build(struct menu_builder* mb, struct mb_args* args);

struct mpk_menu_builder* mpkmb_new(struct device_state* dev, struct menu_nav_controller* mnav)
{
	struct mpk_menu_builder* mb = malloc(sizeof * mb);

	mb->mb.build = &mpkmb_build;

	mb->dev = dev;
	mb->mnav = mnav;

	return mb;
}

static struct menu_presenter* mpkmb_build(struct menu_builder* mb, struct mb_args* args)
{
	struct mpk_menu_builder* mmb = (void*)mb;
	struct acc_mb_args* ama = (void*)args;

	struct memory_pak* mpk = (void*)ama->acc;

	struct game_menu* gm = (void*)mpkm_new(mmb->dev, mmb->mnav, mpk);
	struct menu_presenter* mp = (void*)accmp_new(gm);

	return mp;
}
