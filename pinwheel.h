#pragma once

#include "visual.h"
#include "types.h"


struct pinwheel
{
	struct visual vis;

	u8 current_frame_i;
};

struct pinwheel *pw_new(struct visual *parent, struct renderer *ren);
