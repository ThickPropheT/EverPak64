#pragma once

#include "game_object.h"
#include "renderer.h"
#include "rectangle.h"
#include "types.h"


#define PW_WIDTH	22
#define	PW_HEIGHT	7


struct pinwheel
{
	struct game_object go;

	struct renderer* ren;

	struct rectangle bounds;

	u8 current_frame_i;
};

struct pinwheel* pw_new(u16 x, u16 y, struct renderer* ren);
