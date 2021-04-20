#pragma once

#include <stddef.h>

#include <libdragon.h>

#include "types.h"
#include "menu.h"
#include "console_context.h"
#include "device.h"
#include "menu_state.h"


struct slot_menu
{
	u8 i_slot;

	struct menu m;

	u8 rumble;
};


void sm_init(struct console_context* cc);

struct slot_menu sm_new(u8 i_slot);

void sm_update(struct slot_menu* sm, struct menu_state* ms, struct device_state* dev);
void sm_draw(struct slot_menu* sm, struct device_state dev);