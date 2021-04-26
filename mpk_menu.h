#pragma once

#include "game_menu.h"
#include "menu_nav_controller.h"
#include "memory_pak.h"
#include "menu_state.h"

extern const struct go_type MPKM_TYPE[];

struct mpk_menu
{
	struct game_menu gm;

	struct menu_nav_controller* mnav;

	struct memory_pak* mpk;
};

struct mpk_menu* mpkm_new(struct device_state* dev, struct menu_nav_controller* mnav, struct memory_pak* mpk);