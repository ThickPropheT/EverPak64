#pragma once

#include <stddef.h>

#include <libdragon.h>

#include "types.h"
#include "menu.h"
#include "console.h"
#include "device.h"
#include "menu_state.h"


#define MPAK_READY 			 0
#define MPAK_UNREADABLE		-2
#define MPAK_UNFORMATTED	-3


struct slot_menu
{
	u8 i_slot;

	u8 i_acc;
	s8 acc_status;

	struct menu m;
};


void sm_init(struct console_context* cc);

struct slot_menu sm_new(u8 i_slot);

u8 sm_get_slot_number(struct slot_menu m);
u16 sm_get_slot_flag(struct slot_menu m);

void sm_update(struct slot_menu* sm, struct menu_state* ms, struct device_state dev);
void sm_draw(struct slot_menu* sm, struct device_state dev);