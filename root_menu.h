#pragma once

#include <stddef.h>

#include "menu.h"
#include "slot_menu.h"
#include "device_state.h"


struct root_menu
{
	struct menu m;

	struct slot_menu slots[N_SLOTS];
};


struct root_menu rm_new(void);

struct slot_menu* rm_get_current(struct root_menu* rm);

void rm_update(struct game_state gs, struct root_menu* rm);
void rm_draw(struct game_state gs, struct root_menu* rm);