#pragma once

#include "accessory.h"

struct rumble_pak
{
	struct accessory acc;
};


struct rumble_pak* rpk_new(u8 i_slot);