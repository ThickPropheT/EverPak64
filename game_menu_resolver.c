#include "game_menu_resolver.h"

#include "default_mb_args.h"
#include "acc_mb_args.h"

struct game_menu* gmres_default(struct menu_builder_table* mbt, u8 i_slot)
{
	struct default_mb_args* args = dmba_new(i_slot);
	struct game_menu* gm = mb_build_menu(mbt->default_builder, (void*)args);
	free(args);

	return gm;
}

static struct game_menu* gmres_acc(struct menu_builder* mb, struct accessory* acc)
{
	struct acc_mb_args* args = accmba_new(acc);
	struct game_menu* gm = mb_build_menu(mb, (void*)args);
	free(args);

	return gm;
}

u8 gmres_try_acc(struct menu_builder_table* mbt, struct device_state* dev, u8 i_slot, struct game_menu** result)
{
	struct accessory* acc = dev->accessories[i_slot];

	struct menu_builder* mb = mbt->acc_builders[acc->type];

	if (mb != NULL)
	{
		*result = gmres_acc(mb, acc);
		return *result != NULL;
	}

	*result = NULL;
	return 0;
}
