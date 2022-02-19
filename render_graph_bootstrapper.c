#include "render_graph_bootstrapper.h"

#include <math.h>
#include "hertz.h"
#include "timed_trigger.h"
#include "chained_trigger.h"
#include "pinwheel.h"
#include "fps_counter.h"
#include "title_bar.h"
#include "device_manager.h"
#include "controller_manager.h"

#define PADDING_Y	4
#define PADDING_X	4


static void build_managers(struct render_node* root)
{
	struct device_manager* devm = devm_new();

	struct render_node* devm_node = rn_add_child_for(root, (void*)devm);
	devm_node->update_trigger = (void*)trigger_at_rate(hz_from_fps(15));

	struct controller_manager* cman = cman_new(devm->dev);

	struct render_node* cman_node = rn_add_child_for(devm_node, (void*)cman);
	cman_node->update_trigger = (void*)trigger_after(devm_node->update_trigger);
}


static void build_visuals(struct render_node* root, struct renderer* ren)
{
	struct rectangle vp = ren->view_port;

	u16 top = vp.t + PADDING_Y;
	u16 left = vp.l + PADDING_X;
	u16 right = vp.r - PADDING_X;

	struct pinwheel* pw = pw_new(right - PW_WIDTH, top, ren);
	struct fps_counter* fps = fps_new(left, top, hz_from_fps(0.5f), ren);

	u16 tb_x = roundf((vp.t + vp.w / 2.0f) - TB_WIDTH / 2.0f);

	struct title_bar* tb = tb_new(tb_x, top, ren);

	rn_add_child_for(root, (void*)tb);

	rn_add_child_for(root, (void*)fps);

	struct render_node* pw_node = rn_add_child_for(root, (void*)pw);
	pw_node->update_trigger = (void*)trigger_at_rate(hz_from_fps(11));
}


struct render_graph* rg_init(struct renderer* ren)
{
	struct render_node* root = rn_new(NULL);

	build_managers(root);
	build_visuals(root, ren);

	return rg_new(root, ren);
}
