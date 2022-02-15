#pragma once

#include "render_node.h"
#include "types.h"

struct render_graph
{
	struct render_node* root;

	struct renderer* ren;

	u8 draw_requested;
};

struct render_graph* rg_new(struct render_node* root, struct renderer* ren);

void rg_update(struct render_graph* rg);
void rg_draw(struct render_graph* rg);
