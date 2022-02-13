#include "render_graph.h"

#include <stdlib.h>

struct render_graph* rg_new(struct render_node* root)
{
	struct render_graph* rg = malloc(sizeof * rg);

	rg->root = root;

	return rg;
}

void rg_update(struct render_graph* rg)
{
	rg->draw_requested = rn_update(rg->root);
}

void rg_draw(struct render_graph* rg)
{
	if (!rg->draw_requested)
		return;

	rn_draw(rg->root);
}
