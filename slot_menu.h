#pragma once

#include <stddef.h>

#include <libdragon.h>

#include "types.h"
#include "game_menu.h"
#include "menu_nav_controller.h"


extern const struct go_type SM_TYPE[];

struct slot_menu
{
	struct game_menu gm;

	struct menu_nav_controller* mnav;

	u8 i_slot;

	u8 rumble;
};


struct slot_menu* sm_new(struct device_state* dev, struct menu_nav_controller* mnav, u8 i_slot);