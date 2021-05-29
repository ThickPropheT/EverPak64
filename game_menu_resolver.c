#include "game_menu_resolver.h"

#include "controller.h"
#include "acc_mb_args.h"

static struct game_menu* gmres_acc_impl(struct menu_builder* mb, struct controller* ctrl)
{
	struct acc_mb_args* args = accmba_new(ctrl);
	struct game_menu* gm = mb_build_menu(mb, (void*)args);
	free(args);

	return gm;
}

struct game_menu* gmres_acc(struct menu_builder_table* mbt, struct controller_manager* cman, u8 i_slot)
{
	struct controller* ctrl = cman->controllers[i_slot];
	struct accessory* acc = ctrl->acc;

	return gmres_acc_impl(mbt_get_builder(mbt, acc), ctrl);
}
