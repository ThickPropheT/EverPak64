#include "menu_presenter_resolver.h"

#include "acc_mb_args.h"
#include "menu_builder.h"
#include "controller.h"

struct menu_presenter *mpres_main(struct menu_builder_table *mbt)
{
	return mb_build_presenter(mbt->main_builder, NULL);
}

struct menu_presenter *mpres_acc_impl(struct menu_builder *mb, struct controller *ctrl)
{
	struct acc_mb_args *args = accmba_new(ctrl);
	struct menu_presenter *mp = mb_build_presenter(mb, (struct mb_args *)args);
	free(args);

	return mp;
}

struct menu_presenter *mpres_acc(struct menu_builder_table *mbt, struct controller_manager *cman, u8 i_slot)
{
	struct controller *ctrl = cman->controllers[i_slot];
	struct accessory *acc = ctrl->acc;

	return mpres_acc_impl(mbt_get_builder(mbt, acc), ctrl);
}
