#include "menu_presenter_resolver.h"

#include "default_mb_args.h"
#include "acc_mb_args.h"
#include "menu_builder.h"

struct menu_presenter* mpres_main(struct menu_builder_table* mbt)
{
	return mb_build_presenter(mbt->main_builder, NULL);
}

struct menu_presenter* mpres_default(struct menu_builder_table* mbt, u8 i_slot)
{
	struct default_mb_args* args = dmba_new(i_slot);
	struct menu_presenter* mp = mb_build_presenter(mbt->default_builder, (struct mb_args*)args);
	free(args);

	return mp;
}

struct menu_presenter* mpres_acc(struct menu_builder* mb, struct accessory* acc)
{
	struct acc_mb_args* args = accmba_new(acc);
	struct menu_presenter* mp = mb_build_presenter(mb, (struct mb_args*)args);
	free(args);

	return mp;
}

u8 mpres_try_acc(struct menu_builder_table* mbt, struct device_state* dev, u8 i_slot, struct menu_presenter** result)
{
	struct accessory* acc = dev->accessories[i_slot];

	struct menu_builder* mb = mbt->acc_builders[acc->type];

	if (mb != NULL)
	{
		*result = mpres_acc(mb, acc);
		return *result != NULL;
	}

	*result = NULL;
	return 0;
}
