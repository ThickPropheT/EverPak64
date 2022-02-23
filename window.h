#pragma once

#include "visual.h"
#include "render_node.h"
#include "renderer.h"

struct window
{
	struct visual vis;
};

struct window *win_new(struct render_node *root, struct renderer *ren);
