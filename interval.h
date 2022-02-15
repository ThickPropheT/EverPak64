#pragma once

#include <libdragon.h>
#include "types.h"

struct interval
{
	u32 resolution;
	u32 last_tick_ms;
};

static inline struct interval ivl_new(u32 resolution)
{
	return (struct interval) { resolution, 0 };
}

u8 ivl_has_elapsed(struct interval* ivl, u32* delta_ticks_ms);
