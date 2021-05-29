#pragma once

#include <libdragon.h>
#include "device_state.h"
#include "accessory.h"
#include "types.h"
#include "device_state.h"


#define CTRL_STATUS_READY		 0
#define CTRL_STATUS_MISSING		-1


typedef unsigned (*sel_button_func)(struct SI_condat c);


struct controller
{
	struct device_state* dev;

	u8 i_slot;

	struct accessory* acc;

	s8 status;
};


struct controller* ctrl_new(struct device_state* dev, struct accessory* acc, u8 i_slot);

u8 ctrl_key_down(struct controller* ctrl, sel_button_func select_button);
u8 ctrl_key_held(struct controller* ctrl, sel_button_func select_button);
u8 ctrl_key_up(struct controller* ctrl, sel_button_func select_button);
