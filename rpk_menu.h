#pragma once

#include "game_menu.h"
#include "rumble_pak.h"
#include "types.h"

extern const struct go_type RPKM_TYPE[];

struct rpk_menu
{
	struct game_menu gm;

	struct rumble_pak* rpk;

	u8 rumble;
};

struct rpk_menu* rpkm_new(struct device_state* dev, struct rumble_pak* rpk);
