#pragma once

#include "device_state.h"
#include "menu_state.h"

struct game_state
{
	const struct device_state* dev;
	const struct menu_state* ms;
};