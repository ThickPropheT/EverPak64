#pragma once

#include "game_object.h"
#include "renderer.h"
#include "rectangle.h"
#include "interval.h"
#include "types.h"

struct pinwheel
{
	struct game_object go;

	struct renderer* ren;

	struct rectangle bounds;

	struct interval interval;

	u8 current_frame_i;
};

struct pinwheel* pw_new(u16 x, u16 y, u32 resolution, struct renderer* ren);
