#include "debug_controller.h"

#include "keys.h"
#include "pinwheel.h"
#include "fps_counter.h"
#include "hertz.h"
#include "timed_trigger.h"


#define PADDING_Y	4
#define PADDING_X	4


static void dbg_handle_input(struct controller *ctrl, void *context);
static void enable_debug(struct debug_controller *dbg);

const struct go_type DBG_TYPE[] = { { } };


struct debug_controller *dbg_new(struct render_node *parent, struct controller_manager *cman, struct renderer *ren)
{
	struct debug_controller *dbg = malloc(sizeof * dbg);

	_go_init((void *)dbg, DBG_TYPE);

	dbg->go.can_update = 0;
	dbg->go.can_draw = 0;

	dbg->node = rn_add_child_for(parent, (void *)dbg);

	dbg->cman = cman;
	dbg->ren = ren;

	dbg->is_enabled = 0;

	cman_add_handler(cman, cman->any_controller, dbg, &dbg_handle_input);

	return dbg;
}


static void enable_debug(struct debug_controller *dbg)
{
	struct render_node *node = dbg->node;
	struct renderer *ren = dbg->ren;
	struct rectangle vp = ren->view_port;

	u16 top = vp.t + PADDING_Y;
	u16 left = vp.l + PADDING_X;
	u16 right = vp.r - PADDING_X;

	struct pinwheel *pw = pw_new(right - PW_WIDTH, top, ren);
	struct fps_counter *fps = fps_new(left, top, hz_from_fps(0.5f), ren);

	rn_add_child_for(node, (void *)fps);

	struct render_node *pw_node = rn_add_child_for(node, (void *)pw);
	pw_node->update_trigger = (void *)trigger_at_rate(hz_from_fps(11));

	dbg->is_enabled = 1;
}

static void disable_debug(struct debug_controller *dbg)
{
	rn_clear_children(dbg->node);

	ren_invalidate(dbg->ren);

	dbg->is_enabled = 0;
}

static void dbg_handle_input(struct controller *ctrl, void *context)
{
	struct debug_controller *dbg = context;

	if (ctrl_key_down(ctrl, &key_start))
	{
		if (dbg->is_enabled)
		{
			disable_debug(dbg);
		}
		else
		{
			enable_debug(dbg);
		}
	}
}
