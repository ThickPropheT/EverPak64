#include "render_graph.h"

#include <stdlib.h>
#include "renderer.h"

struct render_graph* rg_new(struct render_node* root, struct renderer* ren)
{
	struct render_graph* rg = malloc(sizeof * rg);

	rg->root = root;
	rg->ren = ren;

	return rg;
}

u8 wentFalse = 0;

void rg_update(struct render_graph* rg)
{
	rn_update(rg->root);
}

void rg_draw(struct render_graph* rg)
{
	struct renderer* ren = rg->ren;

	if (!rg->ren->draw_requested)
		return;

	ren_lock(ren);

	rn_draw(rg->root);

	ren_show(ren);
}
