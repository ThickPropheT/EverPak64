#pragma once

#include <stddef.h>

#include "game_menu.h"
#include "controller_manager.h"


extern const struct go_type MM_TYPE[];

struct main_menu
{
	struct game_menu gm;

	struct input_handler* input_handler;
};


struct main_menu* mm_new(struct device_state* dev, struct controller_manager* cman, struct menu_nav_controller* mnav);
