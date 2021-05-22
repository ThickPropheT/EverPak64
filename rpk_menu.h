#pragma once

#include "game_menu.h"
#include "menu_nav_controller.h"
#include "rumble_pak.h"
#include "types.h"

extern const struct go_type RPKM_TYPE[];

struct rpk_menu
{
	struct game_menu gm;

	struct rumble_pak* rpk;

	u8 rumble;

	u8 pwm_tick;
	u8 pwm_high;
	u8 pwm_low;
};

struct rpk_menu* rpkm_new(struct device_state* dev, struct menu_nav_controller* mnav, struct rumble_pak* rpk);
