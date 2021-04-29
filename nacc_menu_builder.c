#include "nacc_menu_builder.h"

#include "no_accessory_menu.h"
#include "acc_menu_presenter.h"
#include "acc_mb_args.h"

static void* build_menu(struct menu_builder* mb, struct mb_args* args);
static void* build_presenter(struct menu_builder* mb, struct mb_args* args);

const struct mb_type NACCMB_TYPE[] = { { build_menu, build_presenter } };

struct nacc_menu_builder* naccmb_new(struct device_state* dev, struct menu_nav_controller* mnav, struct menu_builder_table* mbt)
{
	struct nacc_menu_builder* builder = malloc(sizeof * builder);

	builder->mb.mb_type = NACCMB_TYPE;

	builder->dev = dev;
	builder->mnav = mnav;
	builder->mbt = mbt;

	return builder;
}

static inline void* unpack(struct menu_builder* mb, struct mb_args* args, struct accessory** acc)
{
	*acc = ((struct acc_mb_args*)args)->acc;
	return mb;
}

static void* build_menu(struct menu_builder* mb, struct mb_args* args)
{
	struct accessory* acc = NULL;
	struct nacc_menu_builder* builder = unpack(mb, args, &acc);

	return nam_new(builder->dev, builder->mnav, acc);
}

static void* build_presenter(struct menu_builder* mb, struct mb_args* args)
{
	struct accessory* acc = NULL;
	struct nacc_menu_builder* builder = unpack(mb, args, &acc);

	struct device_state* dev = builder->dev;

	struct game_menu* menu = (void*)nam_new(dev, builder->mnav, acc);
	return accmp_new(menu, builder->mbt, dev, acc->i_slot);
}
