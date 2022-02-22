#pragma once

#include "accessory.h"

extern const struct go_type RPK_TYPE[];

struct rumble_pak
{
	struct accessory acc;
};


struct rumble_pak *rpk_new(u8 i_slot);