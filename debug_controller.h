#pragma once

#include "game_object.h"
#include "render_node.h"
#include "controller_manager.h"
#include "renderer.h"
#include "types.h"
#include "visual.h"

struct debug_controller
{
	struct game_object go;

	struct visual *parent;
	struct render_node *node;

	struct controller_manager *cman;
	struct renderer *ren;

	u8 is_enabled;
};

struct debug_controller *dbg_new(struct visual *parent, struct controller_manager *cman, struct renderer *ren);
