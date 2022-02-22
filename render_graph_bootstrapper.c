#include "render_graph_bootstrapper.h"

#include <math.h>
#include "hertz.h"
#include "trigger.h"
#include "timed_trigger.h"
#include "chained_trigger.h"
#include "pinwheel.h"
#include "fps_counter.h"
#include "title_bar.h"
#include "device_manager.h"
#include "controller_manager.h"
#include "debug_controller.h"

#define PADDING_Y	4
#define PADDING_X	4


static void build_managers(struct render_node *root, struct renderer *ren)
{
	struct trigger *dev_changed = trigger_manually();

	struct device_manager *devm = devm_new(dev_changed);

	struct render_node *devm_node = rn_add_child_for(root, (void *)devm);
	devm_node->update_trigger = (void *)trigger_at_rate(hz_from_fps(20));


	struct controller_manager *cman = cman_new(devm->dev);

	struct render_node *cman_node = rn_add_child_for(devm_node, (void *)cman);
	cman_node->update_trigger = dev_changed;


	struct debug_controller *dbg = dbg_new(cman_node, cman, ren);
	dbg->node->update_trigger = dev_changed;
}


static void build_visuals(struct render_node *root, struct renderer *ren)
{
	struct rectangle vp = ren->view_port;

	u16 top = vp.t + PADDING_Y;

	u16 tb_x = roundf((vp.t + vp.w / 2.0f) - TB_WIDTH / 2.0f);

	struct title_bar *tb = tb_new(tb_x, top, ren);

	rn_add_child_for(root, (void *)tb);
}


struct render_graph *rg_init(struct renderer *ren)
{
	struct render_node *root = rn_new(NULL);

	build_managers(root, ren);
	build_visuals(root, ren);

	return rg_new(root, ren);
}
