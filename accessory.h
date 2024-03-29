#pragma once

#include "types.h"
#include <libdragon.h>
#include "game_object.h"


#define N_ACC_TYPES		5


extern const struct go_delegate ACC_UPDATE[];
extern const struct go_type ACC_TYPE[];

struct accessory
{
	struct game_object go;

	u8 i_slot;

	u8 type;
	s8 status;
};


extern char *accessory_names[N_ACC_TYPES];

void _acc_init(struct accessory *acc, const struct go_type *vtable, u8 i_slot);

struct accessory *acc_new(u8 i_slot);
