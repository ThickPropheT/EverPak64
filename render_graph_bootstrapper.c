#include "render_graph_bootstrapper.h"

#include "hertz.h"
#include "trigger.h"
#include "timed_trigger.h"
#include "chained_trigger.h"
#include "pinwheel.h"
#include "fps_counter.h"
#include "title_bar.h"
#include "window.h"
#include "device_manager.h"
#include "controller_manager.h"
#include "debug_controller.h"


struct render_graph_bootstrapper
{
	struct render_node *root;
	struct renderer *ren;

	struct trigger *dev_changed;

	struct device_manager *devm;
	struct controller_manager *cman;
};


static void build_managers(struct render_graph_bootstrapper *boot)
{
	struct trigger *dev_changed = trigger_manually();

	struct device_manager *devm = devm_new(dev_changed);

	struct render_node *devm_node = rn_add_child_for(boot->root, (void *)devm);
	devm_node->update_trigger = (void *)trigger_at_rate(hz_from_fps(20));

	boot->dev_changed = dev_changed;
	boot->devm = devm;


	struct controller_manager *cman = cman_new(devm->dev);

	struct render_node *cman_node = rn_add_child_for(devm_node, (void *)cman);
	cman_node->update_trigger = dev_changed;

	boot->cman = cman;
}


static void build_visuals(struct render_graph_bootstrapper *boot)
{
	struct render_node *root = boot->root;
	struct renderer *ren = boot->ren;

	struct window *win = win_new(root, ren);
	struct visual *win_vis = (void *)win;

	tb_new(win_vis, ren);

	struct debug_controller *dbg = dbg_new(win_vis, boot->cman, ren);
	dbg->node->update_trigger = boot->dev_changed;
}


struct render_graph *rg_init(struct renderer *ren)
{
	struct render_graph_bootstrapper *boot = malloc(sizeof * boot);


	graphics_set_color(ren->cp->fg_text, ren->cp->bg_text);


	boot->ren = ren;

	struct render_node *root = rn_new(NULL);
	boot->root = root;


	build_managers(boot);
	build_visuals(boot);


	free(boot);

	return rg_new(root, ren);
}
