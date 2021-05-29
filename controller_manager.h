#pragma once

#include "controller.h"
#include "device_state.h"
#include "types.h"

struct controller_manager
{
	struct device_state* dev;

	u16 ctrl_flags;
	u16 acc_flags;

	struct controller* controllers[N_SLOTS];
	struct controller* any_controller;
};

struct controller_manager* cman_new(struct device_state* dev);

void cman_update(struct controller_manager* cman);
