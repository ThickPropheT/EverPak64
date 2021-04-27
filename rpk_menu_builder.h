#pragma once

#include "menu_builder.h"
#include "menu_builder_table.h"

struct rpk_menu_builder
{
	struct menu_builder mb;

	struct device_state* dev;
	struct menu_nav_controller* mnav;
	struct menu_builder_table* mbt;
};

struct rpk_menu_builder* rpkmb_new(struct device_state* dev, struct menu_nav_controller* mnav, struct menu_builder_table* mbt);
