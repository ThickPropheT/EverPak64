#pragma once

#include <libdragon.h>

#include "types.h"

struct device_state
{
	u16 controllers;
	int accessories;
	// ? identify_accessory()
	// ? validate_mempak(?)
	struct controller_data keys;
};

void dev_poll(struct device_state* ds);