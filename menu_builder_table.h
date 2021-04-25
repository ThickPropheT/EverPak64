#pragma once

#include "menu_builder.h"
#include "accessory.h"

struct menu_builder_table
{
	struct menu_builder* default_builder;

	struct menu_builder* mpkm_builder;
};

struct menu_builder_table* mbt_new(void);

struct menu_builder* mbt_get_builder(struct menu_builder_table* mbt, struct accessory* acc);
