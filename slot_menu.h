#pragma once

#include <stddef.h>

#include <libdragon.h>

#include "types.h"
#include "menu.h"
#include "console_context.h"
#include "device_state.h"
#include "menu_state.h"


struct slot_menu
{
	u8 i_slot;

	struct menu m;

	u8 rumble;
};


struct slot_menu sm_new(u8 i_slot);

void sm_update(struct game_state gs, struct slot_menu* sm);
void sm_draw(struct game_state gs, struct slot_menu* sm);