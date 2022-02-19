#include "interval.h"

u8 ivl_has_elapsed(struct interval* ivl)
{
	u32 ticks_ms = get_ticks_ms();

	ivl->delta_ticks_ms = ticks_ms - ivl->last_tick_ms;

	if (ivl->delta_ticks_ms >= ivl->resolution)
	{
		ivl->last_tick_ms = ticks_ms;
		return 1;
	}

	return 0;
}
