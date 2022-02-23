#include <libdragon.h>
#include <malloc.h>
#include <math.h>

#include "fps_counter.h"


#define WIDTH	94
#define HEIGHT	8


#define BUFFER_LEN	16
static char buffer[BUFFER_LEN];


static void fps_update(const struct go_delegate *base, struct game_object *go);
const struct go_delegate FPS_UPDATE[] = { { fps_update } };

static void fps_draw(const struct go_delegate *base, struct game_object *go);
const struct go_delegate FPS_DRAW[] = { { fps_draw } };

const struct go_type FPS_TYPE[] = { { NULL, FPS_UPDATE, FPS_DRAW } };


struct fps_counter *fps_new(struct visual *parent, u32 resolution, struct renderer *ren)
{
	struct fps_counter *fps = calloc(1, sizeof * fps);
	struct game_object *go = (void *)fps;

	_go_init(go, FPS_TYPE);

	go->can_update = 1;
	go->can_draw = 1;


	struct visual *vis = (void *)fps;

	vis->node = rn_add_child_for(parent->node, go);
	vis->ren = ren;

	struct rectangle b = parent->bounds;

	vis->bounds = rect_new(b.l, b.t, WIDTH, HEIGHT);

	fps->interval = ivl_new(resolution);

	return fps;
}

static void fps_update(const struct go_delegate *base, struct game_object *go)
{
	struct fps_counter *fps = (void *)go;

	fps->frame_count++;

	if (ivl_has_elapsed(&fps->interval))
	{
		//  n f   1000mf   n2 mf    n3 mf   1000mf
		// ---- * ------ = ----- X ------ / ------ = n4 f / 1s
		// i ms    1ms      i ms   1000ms   1000ms

		//  n f     n3 f
		// ---- X ------ = n4 f / 1s
		// i ms   1000ms

		// n4 = n3 =       n        * 1000ms /             i
		fps->fps = fps->frame_count * 1000.0 / fps->interval.delta_ticks_ms;
		fps->frame_count = 0;

		ren_invalidate(fps->vis.ren);
	}
}

static void fps_draw(const struct go_delegate *base, struct game_object *go)
{
	struct fps_counter *fps = (void *)go;

	struct renderer *ren = fps->vis.ren;
	struct rectangle b = fps->vis.bounds;

	ren_set_primitive_color(ren, ren->cp->bg);

	rdp_draw_filled_rectangle(b.l, b.t, b.r, b.b);

	sprintf(buffer, "%.1lf fps", fps->fps);
	ren_draw_text(ren, b.l, b.t, buffer);
}
