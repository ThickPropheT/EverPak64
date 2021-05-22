#pragma once

#include "menu_builder.h"
#include "accessory.h"

struct menu_builder_table
{
	struct menu_builder* main_builder;

	struct menu_builder* acc_builders[N_ACC_TYPES];
};

struct menu_builder_table* mbt_new(void);
