#pragma once

#include "types.h"
#include "menu_state.h"

struct menu_nav_controller
{
	struct menu_state* ms;
};

struct menu_nav_controller* mnav_new(struct menu_state* ms);

void mnav_to_sm(struct menu_nav_controller* mnav, u8 i_slot);

void mnav_pop(struct menu_nav_controller* mnav);