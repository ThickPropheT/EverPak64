#pragma once

#include <stddef.h>

#include "menu.h"
#include "slot_menu.h"
#include "device.h"


struct root_menu
{
	struct menu m;

	struct slot_menu slots[N_SLOTS];
};


void rm_init(struct console_context* cc);

struct root_menu rm_new(void);

struct slot_menu* rm_get_current(struct root_menu* rm);

void rm_update(struct root_menu* rm, struct menu_state* ms, struct device_state* dev);
void rm_draw(struct root_menu* rm, struct device_state dev);