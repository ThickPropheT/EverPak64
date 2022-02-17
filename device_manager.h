#pragma once

#include "game_object.h"
#include "interval.h"
#include "device_state.h"

struct device_manager
{
	struct game_object go;

	struct interval interval;

	struct device_state* dev;
};

struct device_manager* devm_new(u32 resolution);
