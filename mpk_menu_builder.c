#include "mpk_menu_builder.h"

#include "acc_mb_args.h"
#include "memory_pak.h"
#include "mpk_menu.h"

static struct game_menu* mpkmb_build(struct menu_builder* mb, struct mb_args* args);

struct mpk_menu_builder* mpkmb_new(struct device_state* dev, struct menu_nav_controller* mnav)
{
	struct mpk_menu_builder* mb = malloc(sizeof * mb);

	mb->mb.build = &mpkmb_build;

	mb->dev = dev;
	mb->mnav = mnav;

	return mb;
}

static struct game_menu* mpkmb_build(struct menu_builder* mb, struct mb_args* args)
{
	struct mpk_menu_builder* mmb = (struct mpk_menu_builder*)mb;
	struct acc_mb_args* ama = (struct acc_mb_args*)args;

	struct memory_pak* mpk = (struct memory_pak*)ama->acc;

	return (struct game_menu*)mpkm_new(mmb->dev, mmb->mnav, mpk);
}
