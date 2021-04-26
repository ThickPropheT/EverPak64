#pragma once

#include <stddef.h>

#include "game_menu.h"
#include "slot_menu.h"
#include "menu_nav_controller.h"


extern const struct go_type MM_TYPE[];

struct main_menu
{
	struct game_menu gm;

	struct menu_nav_controller* mnav;

	struct slot_menu* slots[N_SLOTS];
};


struct main_menu* mm_new(struct device_state* dev, struct menu_nav_controller* mnav);

struct slot_menu* mm_get_current(struct main_menu* mm);
