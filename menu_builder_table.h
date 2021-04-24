#pragma once

#include "menu_builder.h"

struct menu_builder_table
{
	struct menu_builder* default_builder;
};

struct menu_builder_table* mbt_new(void);