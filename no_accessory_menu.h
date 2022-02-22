#pragma once

#include "game_menu.h"
#include "controller.h"
#include "device_state.h"
#include "controller_manager.h"
#include "menu_nav_controller.h"
#include "accessory.h"

extern const struct go_type NAM_TYPE[];

struct no_accessory_menu
{
	struct game_menu gm;

	struct controller *ctrl;

	struct input_handler *input_handler;
};

struct no_accessory_menu *nam_new(struct device_state *dev, struct controller_manager *cman, struct menu_nav_controller *mnav, struct controller *ctrl);
