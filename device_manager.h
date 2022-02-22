#pragma once

#include "game_object.h"
#include "trigger.h"
#include "device_state.h"

struct device_manager
{
	struct game_object go;

	struct trigger *dev_changed;

	struct device_state *dev;
};

struct device_manager *devm_new(struct trigger *dev_changed);
