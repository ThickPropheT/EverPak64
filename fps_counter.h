#pragma once

#include "visual.h"
#include "interval.h"
#include "types.h"

struct fps_counter
{
	struct visual vis;

	struct interval interval;

	u64 frame_count;
	double fps;
};

struct fps_counter *fps_new(struct visual *parent, u32 resolution, struct renderer *ren);
