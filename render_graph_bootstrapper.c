#include "render_graph_bootstrapper.h"

#include <math.h>
#include "hertz.h"
#include "pinwheel.h"
#include "fps_counter.h"
#include "title_bar.h"

#define PADDING_Y	8
#define PADDING_X	8


struct render_graph* rg_init(struct renderer* ren)
{
	struct render_node* root = rn_new(NULL);

	struct rectangle vp = ren->view_port;

	u16 top = vp.t + PADDING_Y;
	u16 left = vp.l + PADDING_X;

	struct pinwheel* pw = pw_new(left, top, htz_from_fps(11), ren);
	struct fps_counter* fps = fps_new(pw->bounds.r + 4, top, htz_from_fps(0.5f), ren);

	u16 tb_x = roundf((vp.t + vp.w / 2.0f) - TB_WIDTH / 2.0f);

	struct title_bar* tb = tb_new(tb_x, fps->bounds.b + 8, ren);

	rn_add_child_for(root, (void*)tb);
	rn_add_child_for(root, (void*)fps);
	rn_add_child_for(root, (void*)pw);

	return rg_new(root, ren);
}
