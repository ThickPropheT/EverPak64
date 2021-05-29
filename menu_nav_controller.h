#pragma once

#include "menu_state.h"
#include "menu_builder_table.h"
#include "controller_manager.h"
#include "types.h"

struct menu_nav_controller
{
	struct controller_manager* cman;
	struct menu_state* ms;
	struct menu_builder_table* mbt;
};

struct menu_nav_controller* mnav_new(struct controller_manager* cman, struct menu_state* ms, struct menu_builder_table* mbt);

void mnav_to_sm(struct menu_nav_controller* mnav, u8 i_slot);

void mnav_pop(struct menu_nav_controller* mnav);