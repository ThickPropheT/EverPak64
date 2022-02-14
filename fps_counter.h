#pragma once

#include "game_object.h"
#include "renderer.h"
#include "rectangle.h"
#include "types.h"

struct fps_counter
{
	struct game_object go;

	struct renderer* ren;

	struct rectangle bounds;

	u32 resolution;
	u32 last_tick_ms;

	u64 frame_count;
	double fps;
};

struct fps_counter* fps_new(u16 x, u16 y, u32 resolution, struct renderer* ren);
