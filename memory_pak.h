#pragma once

#include "accessory.h"

struct memory_pak
{
	struct accessory base;
};


struct memory_pak* mpk_new(u8 i_slot);