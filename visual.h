#pragma once

#include "game_object.h"
#include "render_node.h"
#include "renderer.h"
#include "rectangle.h"

struct visual
{
	struct game_object go;

	struct render_node *node;
	struct renderer *ren;

	struct rectangle bounds;
};
