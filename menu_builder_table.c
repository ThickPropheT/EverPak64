#include "menu_builder_table.h"

struct menu_builder_table *mbt_new(void)
{
	struct menu_builder_table *mbt = calloc(1, sizeof * mbt);
	return mbt;
}

struct menu_builder *mbt_get_builder(struct menu_builder_table *mbt, struct accessory *acc)
{
	struct menu_builder *mb = mbt->acc_builders[acc->type];

	if (mb != NULL)
		return mb;

	return mbt->acc_builders[ACCESSORY_NONE];
}
