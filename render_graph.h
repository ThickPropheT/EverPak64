#pragma once

#include "render_node.h"
#include "types.h"

struct render_graph
{
	struct render_node* root;

	u8 draw_requested;
};

struct render_graph* rg_new(struct render_node* root);

void rg_update(struct render_graph* rg);
void rg_draw(struct render_graph* rg);
