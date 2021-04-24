#pragma once

#include "menu_builder.h"

struct default_mb_args
{
	struct mb_args mba;

	u8 i_slot;
};

struct default_mb_args* dmba_new(u8 i_slot);