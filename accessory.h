#pragma once

#include "types.h"
#include <libdragon.h>


#define N_ACC_TYPES		4


#define MPAK_STATUS_READY 			 0
#define MPAK_STATUS_UNREADABLE		-2
#define MPAK_STATUS_UNFORMATTED		-3


struct accessory
{
	u8 i_slot;

	u8 type;
	s8 status;
};


extern char* accessory_names[N_ACC_TYPES];


struct accessory acc_new(u8 i_slot);

void acc_update(struct accessory* acc);