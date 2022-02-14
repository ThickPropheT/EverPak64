#include "render_graph_bootstrapper.h"

#include "hertz.h"
#include "pinwheel.h"
#include "fps_counter.h"

struct render_graph* rg_init(struct renderer* ren)
{
	struct render_node* root = rn_new(NULL);

	rn_add_child_for(root, (void*)fps_new(45, 16, htz_from_fps(0.5f), ren));
	rn_add_child_for(root, (void*)pw_new(20, 16, htz_from_fps(11), ren));

	return rg_new(root, ren);
}
