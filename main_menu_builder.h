#pragma once

#include "menu_builder.h"
#include "device_state.h"
#include "menu_nav_controller.h"

struct main_menu_builder
{
	struct menu_builder mb;

	struct device_state* dev;
	struct menu_nav_controller* mnav;
};

struct main_menu_builder* mmb_new(struct device_state* dev, struct menu_nav_controller* mnav);
