#include "mpk_menu_builder.h"

#include "acc_mb_args.h"
#include "memory_pak.h"
#include "mpk_menu.h"
#include "acc_menu_presenter.h"

static struct game_menu* build_menu(struct menu_builder* mb, struct mb_args* args);
static struct menu_presenter* build_presenter(struct menu_builder* mb, struct mb_args* args);

struct mpk_menu_builder* mpkmb_new(struct device_state* dev, struct menu_nav_controller* mnav, struct menu_builder_table* mbt)
{
	struct mpk_menu_builder* mb = malloc(sizeof * mb);

	mb->mb.build_menu = &build_menu;
	mb->mb.build_presenter = &build_presenter;

	mb->dev = dev;
	mb->mnav = mnav;
	mb->mbt = mbt;

	return mb;
}


static struct game_menu* build_menu_impl(struct mpk_menu_builder* mmb, struct acc_mb_args* args, struct memory_pak* mpk)
{
	return (void*)mpkm_new(mmb->dev, mmb->mnav, mpk);
}

static struct game_menu* build_menu(struct menu_builder* mb, struct mb_args* args)
{
	struct mpk_menu_builder* mmb = (void*)mb;
	struct acc_mb_args* ama = (void*)args;

	struct memory_pak* mpk = (void*)ama->acc;

	return build_menu_impl(mmb, ama, mpk);
}

static struct menu_presenter* build_presenter(struct menu_builder* mb, struct mb_args* args)
{
	struct mpk_menu_builder* mmb = (void*)mb;
	struct acc_mb_args* ama = (void*)args;

	struct memory_pak* mpk = (void*)ama->acc;

	struct game_menu* gm = build_menu_impl(mmb, ama, mpk);
	struct menu_presenter* mp = (void*)accmp_new(gm, mmb->mbt, mmb->dev, mpk->acc.i_slot);

	return mp;
}
