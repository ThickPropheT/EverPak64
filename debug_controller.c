#include "debug_controller.h"

#include "keys.h"
#include "pinwheel.h"
#include "fps_counter.h"
#include "hertz.h"
#include "timed_trigger.h"


static void dbg_handle_input(struct controller *ctrl, void *context);
static void enable_debug(struct debug_controller *dbg);

const struct go_type DBG_TYPE[] = { { } };


struct debug_controller *dbg_new(struct visual *parent, struct controller_manager *cman, struct renderer *ren)
{
	struct debug_controller *dbg = malloc(sizeof * dbg);

	_go_init((void *)dbg, DBG_TYPE);

	dbg->go.can_update = 0;
	dbg->go.can_draw = 0;

	dbg->parent = parent;
	dbg->node = rn_add_child_for(parent->node, (void *)dbg);

	dbg->cman = cman;
	dbg->ren = ren;

	dbg->is_enabled = 0;

	cman_add_handler(cman, cman->any_controller, dbg, &dbg_handle_input);

	return dbg;
}


static void enable_debug(struct debug_controller *dbg)
{
	struct renderer *ren = dbg->ren;
	struct visual *parent = dbg->parent;

	pw_new(parent, ren);
	fps_new(parent, hz_from_fps(0.5f), ren);

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
