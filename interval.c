#include "interval.h"

u8 ivl_has_elapsed(struct interval* ivl, u32* delta_ticks_ms)
{
	u32 ticks_ms = get_ticks_ms();

	*delta_ticks_ms = ticks_ms - ivl->last_tick_ms;

	if (*delta_ticks_ms >= ivl->resolution)
	{
		ivl->last_tick_ms = ticks_ms;
		return 1;
	}

	return 0;
}
