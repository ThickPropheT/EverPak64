#pragma once

#include "menu_builder.h"
#include "device_state.h"
#include "menu_nav_controller.h"
#include "menu_builder_table.h"

struct nacc_menu_builder
{
	struct menu_builder mb;

	struct device_state* dev;
	struct menu_nav_controller* mnav;
	struct menu_builder_table* mbt;
};

struct nacc_menu_builder* naccmb_new(struct device_state* dev, struct menu_nav_controller* mnav, struct menu_builder_table* mbt);
