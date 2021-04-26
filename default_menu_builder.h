#pragma once

#include "menu_builder.h"
#include "device_state.h"
#include "menu_nav_controller.h"

struct default_menu_builder
{
	struct menu_builder mb;

	struct device_state* dev;
	struct menu_nav_controller* mnav;
};

struct default_menu_builder* dmb_new(struct device_state* dev, struct menu_nav_controller* mnav);
