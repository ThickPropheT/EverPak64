#include "render_graph.h"

#include <stdlib.h>
#include "renderer.h"

struct render_graph* rg_new(struct render_node* root, struct renderer* ren)
{
	struct render_graph* rg = malloc(sizeof * rg);

	rg->root = root;
	rg->ren = ren;

	ren_set_rdp_enabled(ren, 1);

	// use only to prompt first draw
	rg->draw_requested = 1;

	return rg;
}

void rg_update(struct render_graph* rg)
{
	rn_update(rg->root);

	struct renderer* ren = rg->ren;

	if (!ren->draw_requested
		&& rg->draw_requested)
		ren_invalidate(ren);
}

void rg_draw(struct render_graph* rg)
{
	struct renderer* ren = rg->ren;

	if (!rg->ren->draw_requested)
		return;

	ren_lock(ren);

	graphics_fill_screen(ren->dc, ren->cp->black);

	rn_draw(rg->root);

	ren_show(ren);

	rg->draw_requested = 0;
}
