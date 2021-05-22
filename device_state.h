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
	struct controller_data keys_h;
	struct controller_data keys_u;
};


u16 get_flag(u8 i_slot);

u8 did_flag_change(u16 flag, u16 from, u16 to);
