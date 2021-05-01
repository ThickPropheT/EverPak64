#include "acc_menu_builder.h"

#include "acc_mb_args.h"

static void* build_menu(struct menu_builder* mb, struct mb_args* args);
static void* build_presenter(struct menu_builder* mb, struct mb_args* args);

const struct mb_type ACCMB_TYPE[] = { { build_menu, build_presenter } };

struct acc_menu_builder* accmb_new(struct device_state* dev, struct menu_nav_controller* mnav, struct menu_builder_table* mbt, build_menu_delegate on_build_menu, build_presenter_delegate on_build_presenter)
{
	struct acc_menu_builder* builder = malloc(sizeof * builder);

	builder->mb.mb_type = ACCMB_TYPE;

	builder->dev = dev;
	builder->mnav = mnav;
	builder->mbt = mbt;

	builder->on_build_menu = on_build_menu;
	builder->on_build_presenter = on_build_presenter;

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
	struct acc_menu_builder* builder = unpack(mb, args, &acc);

	return (void*)builder->on_build_menu(builder->dev, builder->mnav, acc);
}

static void* build_presenter(struct menu_builder* mb, struct mb_args* args)
{
	struct accessory* acc = NULL;
	struct acc_menu_builder* builder = unpack(mb, args, &acc);

	struct device_state* dev = builder->dev;

	struct game_menu* menu = builder->on_build_menu(dev, builder->mnav, acc);
	return (void*)builder->on_build_presenter(menu, builder->mbt, dev, acc->i_slot);
}
