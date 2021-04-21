#pragma once

#include <libdragon.h>
#include "types.h"
#include "accessory.h"


#define N_SLOTS		4


struct device_state
{
	u16 controllers;

	u16 acc_flags;

	struct accessory* accessories[N_SLOTS];

	struct controller_data keys_d;
};


u16 get_flag(u8 i_slot);
