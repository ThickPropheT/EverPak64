#pragma once

#include "types.h"
#include <libdragon.h>
#include "game_object.h"


#define N_ACC_TYPES		4


#define MPAK_STATUS_READY 			 0
#define MPAK_STATUS_UNREADABLE		-2
#define MPAK_STATUS_UNFORMATTED		-3


struct accessory
{
	// TODO should this be const?
	struct game_object base;

	u8 i_slot;

	u8 type;
	s8 status;
};

extern const struct _go_vtable ACC[];


extern char* accessory_names[N_ACC_TYPES];


struct accessory acc_new(u8 i_slot);

void acc_format(struct accessory* acc);