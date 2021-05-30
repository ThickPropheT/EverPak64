#pragma once

#include "game_menu.h"
#include "device_manager.h"
#include "controller_manager.h"
#include "menu_nav_controller.h"
#include "controller.h"
#include "rumble_pak.h"
#include "pwm_state.h"

extern const struct go_type RPKM_TYPE[];

struct rumble_state
{
	struct input_handler* handler;

	struct pwm_state* pwm;
	u8 rumble;
};

struct rpk_menu
{
	struct game_menu gm;

	struct controller* ctrl;
	struct rumble_pak* rpk;

	struct rumble_state* state;
	struct pwm_state* rumble_pwm;
};

struct rpk_menu* rpkm_new(struct device_state* dev, struct controller_manager* cman, struct menu_nav_controller* mnav, struct controller* ctrl);
