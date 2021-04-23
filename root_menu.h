#pragma once

#include <stddef.h>

#include "game_menu.h"
#include "slot_menu.h"
#include "menu_nav_controller.h"


struct root_menu
{
	struct game_menu gm;

	struct slot_menu* slots[N_SLOTS];
};


struct root_menu* rm_new(struct device_state* dev, struct menu_nav_controller* mnav);

struct slot_menu* rm_get_current(struct root_menu* rm);