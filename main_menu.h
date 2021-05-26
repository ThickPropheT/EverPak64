#pragma once

#include <stddef.h>

#include "game_menu.h"


extern const struct go_type MM_TYPE[];

struct main_menu
{
	struct game_menu gm;
};


struct main_menu* mm_new(struct device_state* dev, struct menu_nav_controller* mnav);
