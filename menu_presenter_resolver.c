#include "menu_presenter_resolver.h"

#include "default_mb_args.h"
#include "acc_mb_args.h"
#include "menu_builder.h"

struct menu_presenter* mbres_build_main(struct menu_builder_table* mbt)
{
	return mb_build(mbt->main_builder, NULL);
}

struct menu_presenter* mbres_build_default(struct menu_builder_table* mbt, u8 i_slot)
{
	struct default_mb_args* args = dmba_new(i_slot);
	struct menu_presenter* mp = mb_build(mbt->default_builder, (struct mb_args*)args);
	free(args);

	return mp;
}

struct menu_presenter* mbres_build_acc(struct menu_builder* mb, struct accessory* acc)
{
	struct acc_mb_args* args = accmba_new(acc);
	struct menu_presenter* mp = mb_build(mb, (struct mb_args*)args);
	free(args);

	return mp;
}

struct menu_presenter* mbres_try_build_acc(struct menu_builder_table* mbt, struct device_state* dev, u8 i_slot)
{
	struct accessory* acc = dev->accessories[i_slot];

	struct menu_builder* mb = mbt->acc_builders[acc->type];

	if (mb != NULL)
		return mbres_build_acc(mb, acc);

	return NULL;
}
