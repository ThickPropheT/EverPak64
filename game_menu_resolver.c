#include "game_menu_resolver.h"

#include "acc_mb_args.h"

static struct game_menu* gmres_acc_impl(struct menu_builder* mb, struct accessory* acc)
{
	struct acc_mb_args* args = accmba_new(acc);
	struct game_menu* gm = mb_build_menu(mb, (void*)args);
	free(args);

	return gm;
}

struct game_menu* gmres_acc(struct menu_builder_table* mbt, struct device_state* dev, u8 i_slot) 
{
	struct accessory* acc = dev->accessories[i_slot];

	struct menu_builder* mb = mbt->acc_builders[acc->type];

	if (mb == NULL)
	{
		mb = mbt->acc_builders[ACCESSORY_NONE];
	}

	return gmres_acc_impl(mb, acc);
}
