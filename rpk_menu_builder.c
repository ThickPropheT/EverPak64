#include "rpk_menu_builder.h"

#include "rpk_menu.h"
#include "acc_mb_args.h"
#include "acc_menu_presenter.h"

static struct game_menu* build_menu(struct menu_builder* mb, struct mb_args* args);
static struct menu_presenter* build_presenter(struct menu_builder* mb, struct mb_args* args);

struct rpk_menu_builder* rpkmb_new(struct device_state* dev, struct menu_nav_controller* mnav, struct menu_builder_table* mbt)
{
	struct rpk_menu_builder* mb = malloc(sizeof * mb);

	mb->mb.build_menu = &build_menu;
	mb->mb.build_presenter = &build_presenter;

	mb->dev = dev;
	mb->mnav = mnav;
	mb->mbt = mbt;

	return mb;
}


static inline void* unpack(struct menu_builder* mb, struct mb_args* args, struct rpk_menu_builder** builder, struct rumble_pak** rpk)
{
	*rpk = (void*)((struct acc_mb_args*)args)->acc;
	return (void*)mb;
}

static struct game_menu* build_menu(struct menu_builder* mb, struct mb_args* args)
{
	struct rumble_pak* rpk = NULL;
	struct rpk_menu_builder* builder = unpack(mb, args, &builder, &rpk);

	return (void*)rpkm_new(builder->dev, builder->mnav, rpk);
}

static struct menu_presenter* build_presenter(struct menu_builder* mb, struct mb_args* args)
{
	struct rumble_pak* rpk = NULL;
	struct rpk_menu_builder* builder = unpack(mb, args, &builder, &rpk);

	struct device_state* dev = builder->dev;

	struct game_menu* menu = (void*)rpkm_new(dev, builder->mnav, rpk);
	return (void*)accmp_new(menu, builder->mbt, dev, rpk->acc.i_slot);
}
