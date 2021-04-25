#include "menu_builder_table.h"

struct menu_builder_table* mbt_new(void)
{
	struct menu_builder_table* mbt = malloc(sizeof * mbt);
	return mbt;
}

struct menu_builder* mbt_get_builder(struct menu_builder_table* mbt, struct accessory* acc)
{
	// TODO convert this to an array stored on mbt indexed by acc type
	switch (acc->type)
	{
	case ACCESSORY_MEMPAK:
		return mbt->mpkm_builder;

	default:
		return NULL;
	}
}
