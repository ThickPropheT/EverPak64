#include "menu_builder_table.h"

struct menu_builder_table* mbt_new(void)
{
	struct menu_builder_table* mbt = calloc(1, sizeof * mbt);
	return mbt;
}
