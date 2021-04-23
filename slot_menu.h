#pragma once

#include <stddef.h>

#include <libdragon.h>

#include "types.h"
#include "game_menu.h"


struct slot_menu
{
	struct game_menu gm;

	u8 i_slot;

	u8 rumble;
};


struct slot_menu* sm_new(struct device_state* dev, struct menu_state* ms, u8 i_slot);