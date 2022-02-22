#pragma once

#include "game_object.h"
#include "renderer.h"
#include "rectangle.h"
#include "types.h"


#define TB_WIDTH	111
#define TB_HEIGHT	7


struct title_bar
{
	struct game_object go;

	struct renderer *ren;

	struct rectangle bounds;
};

struct title_bar *tb_new(u16 x, u16 y, struct renderer *ren);
