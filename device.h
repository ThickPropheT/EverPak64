#pragma once

#include <libdragon.h>
#include "types.h"
#include "accessory.h"


#define N_SLOTS		4


struct device_state
{
	u16 controllers;

	u16 accessories_f;
	u8 acc_f_changed;

	struct accessory* accessories[N_SLOTS];

	struct controller_data keys_d;
};


u16 get_flag(u8 i_slot);


struct device_state dev_new(void);

void dev_poll(struct device_state* ds);