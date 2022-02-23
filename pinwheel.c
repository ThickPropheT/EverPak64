#include <libdragon.h>

#include "pinwheel.h"
#include "timed_trigger.h"
#include "hertz.h"


#define PW_WIDTH	22
#define PW_HEIGHT	7


#define N_PW_FRAMES 4
char *pw_frames[N_PW_FRAMES] =
{
	"(\\)",
	"(|)",
	"(/)",
	"(-)"
};


static void pw_update(const struct go_delegate *base, struct game_object *go);
const struct go_delegate PW_UPDATE[] = { { pw_update } };

static void pw_draw(const struct go_delegate *base, struct game_object *go);
const struct go_delegate PW_DRAW[] = { { pw_draw } };

const struct go_type PW_TYPE[] = { { NULL, PW_UPDATE, PW_DRAW } };


struct pinwheel *pw_new(struct visual *parent, struct renderer *ren)
{
	struct pinwheel *pw = calloc(1, sizeof * pw);
	struct game_object *go = (void *)pw;

	_go_init(go, PW_TYPE);

	go->can_update = 1;
	go->can_draw = 1;


	struct visual *vis = (void *)pw;

	vis->node = rn_add_child_for(parent->node, go);
	vis->node->update_trigger = (void *)trigger_at_rate(hz_from_fps(11));

	vis->ren = ren;

	struct rectangle b = parent->bounds;

	vis->bounds = rect_new(b.r - PW_WIDTH, b.t, PW_WIDTH, PW_HEIGHT);

	return pw;
}

static void pw_update(const struct go_delegate *base, struct game_object *go)
{
	struct pinwheel *pw = (void *)go;

	pw->current_frame_i = (pw->current_frame_i + 1) % N_PW_FRAMES;
	ren_invalidate(pw->vis.ren);
}

static void pw_draw(const struct go_delegate *base, struct game_object *go)
{
	struct pinwheel *pw = (void *)go;

	struct renderer *ren = pw->vis.ren;
	struct rectangle b = pw->vis.bounds;

	rdp_draw_filled_rectangle(b.l, b.t, b.r, b.b);

	ren_draw_text(ren, b.l, b.t, pw_frames[pw->current_frame_i]);
}
