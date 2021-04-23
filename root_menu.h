#pragma once

#include <stddef.h>

#include "slot_menu.h"
#include "game_menu.h"


struct root_menu
{
	struct game_menu gm;

	struct slot_menu* slots[N_SLOTS];
};


struct root_menu* rm_new(struct device_state* dev, struct menu_state* ms);

struct slot_menu* rm_get_current(struct root_menu* rm);