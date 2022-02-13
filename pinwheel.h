#pragma once

#include "game_object.h"
#include "renderer.h"
#include "rectangle.h"
#include "types.h"

struct pinwheel
{
	struct game_object go;

	struct renderer* ren;

	struct rectangle bounds;

	u32 resolution;

	u8 current_frame_i;
	u32 last_tick_ms;
};

struct pinwheel* pw_new(u16 x, u16 y, u32 resolution, struct renderer* ren);
