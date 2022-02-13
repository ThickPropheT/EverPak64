#include "render_graph_bootstrapper.h"

#include "pinwheel.h"

// render pinwheel @ ~15Hz
#define FIFTEEN_FPS		66

struct render_graph* rg_init(struct renderer* ren)
{
	struct render_node* root = rn_new(NULL);

	rn_add_child_for(root, (void*)pw_new(20, 16, FIFTEEN_FPS, ren));

	return rg_new(root);
}
