#pragma once

#include "game_menu.h"
#include "device_state.h"
#include "controller_manager.h"
#include "menu_nav_controller.h"
#include "controller.h"
#include "memory_pak.h"
#include "menu_state.h"

extern const struct go_type MPKM_TYPE[];

struct mpk_menu
{
	struct game_menu gm;

	struct controller *ctrl;
	struct memory_pak *mpk;

	struct input_handler *input_handler;
};

struct mpk_menu *mpkm_new(struct device_state *dev, struct controller_manager *cman, struct menu_nav_controller *mnav, struct controller *ctrl);
