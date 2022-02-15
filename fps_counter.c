#include <libdragon.h>

#include "fps_counter.h"

#include <malloc.h>

#include <math.h>


#define WIDTH	94
#define HEIGHT	8


#define BUFFER_LEN	16
static char buffer[BUFFER_LEN];


static void fps_update(const struct go_delegate* base, struct game_object* go);
const struct go_delegate FPS_UPDATE[] = { { fps_update } };

static void fps_draw(const struct go_delegate* base, struct game_object* go);
const struct go_delegate FPS_DRAW[] = { { fps_draw } };

const struct go_type FPS_TYPE[] = { { NULL, FPS_UPDATE, FPS_DRAW } };


struct fps_counter* fps_new(u16 x, u16 y, u32 resolution, struct renderer* ren)
{
	struct fps_counter* fps = calloc(1, sizeof * fps);

	_go_init(&fps->go, FPS_TYPE);

	fps->go.can_update = 1;
	fps->go.can_draw = 1;

	fps->ren = ren;

	fps->bounds = rect_new(x, y, WIDTH, HEIGHT);

	fps->resolution = resolution;

	return fps;
}

static void fps_update(const struct go_delegate* base, struct game_object* go)
{
	struct fps_counter* fps = (void*)go;

	fps->frame_count++;

	u32 ticks_ms = get_ticks_ms();

	u32 ticks_diff = ticks_ms - fps->last_tick_ms;

	if (ticks_diff >= fps->resolution)
	{
		//  n f   1000mf   n2 mf    n3 mf   1000mf
		// ---- * ------ = ----- X ------ / ------ = n4 f / 1s
		// i ms    1ms      i ms   1000ms   1000ms

		//  n f     n3 f
		// ---- X ------ = n4 f / 1s
		// i ms   1000ms

		// n4 = n3 =       n        * 1000ms /     i
		fps->fps = fps->frame_count * 1000.0 / ticks_diff;

		fps->frame_count = 0;
		fps->last_tick_ms = ticks_ms;

		ren_invalidate(fps->ren);
	}
}

static void fps_draw(const struct go_delegate* base, struct game_object* go)
{
	struct fps_counter* fps = (void*)go;

	struct renderer* ren = fps->ren;
	struct rectangle b = fps->bounds;

	ren_set_primitive_color(ren, ren->cp->bg);

	rdp_draw_filled_rectangle(b.l, b.t, b.r, b.b);

	sprintf(buffer, "%.1lf fps", fps->fps);
	graphics_draw_text(ren->dc, b.l, b.t, buffer);
}
