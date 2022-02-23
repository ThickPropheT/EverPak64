#pragma once

#include "visual.h"
#include "rectangle.h"
#include "renderer.h"


struct title_bar
{
	struct visual vis;

	struct rectangle border_bounds;
};

struct title_bar *tb_new(struct visual *parent, struct renderer *ren);
