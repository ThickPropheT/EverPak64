#include <libdragon.h>

#include "pinwheel.h"


#define WIDTH	22
#define	HEIGHT	7


#define N_PW_FRAMES 4
char* pw_frames[N_PW_FRAMES] =
{
	"(\\)",
	"(|)",
	"(/)",
	"(-)"
};


static void pw_update(const struct go_delegate* base, struct game_object* go);
const struct go_delegate PW_UPDATE[] = { { pw_update } };

static void pw_draw(const struct go_delegate* base, struct game_object* go);
const struct go_delegate PW_DRAW[] = { { pw_draw } };

const struct go_type PW_TYPE[] = { { NULL, PW_UPDATE, PW_DRAW } };


struct pinwheel* pw_new(u16 x, u16 y, u32 resolution, struct renderer* ren)
{
	struct pinwheel* pw = calloc(1, sizeof * pw);

	_go_init(&pw->go, PW_TYPE);

	pw->go.can_update = 1;
	pw->go.can_draw = 1;

	pw->ren = ren;

	pw->bounds = rect_new(x, y, WIDTH, HEIGHT);

	pw->resolution = resolution;

	return pw;
}

static void pw_update(const struct go_delegate* base, struct game_object* go)
{
	struct pinwheel* pw = (void*)go;

	u32 ticks_ms = get_ticks_ms();

	if (ticks_ms - pw->last_tick_ms > pw->resolution)
	{
		pw->current_frame_i = (pw->current_frame_i + 1) % N_PW_FRAMES;
		pw->last_tick_ms = ticks_ms;

		ren_invalidate(pw->ren);
	}
}

static void pw_draw(const struct go_delegate* base, struct game_object* go)
{
	struct pinwheel* pw = (void*)go;

	struct renderer* ren = pw->ren;
	struct rectangle b = pw->bounds;

	ren_set_primitive_color(ren, ren->cp->bg);

	rdp_draw_filled_rectangle(b.l, b.t, b.r, b.b);

	graphics_draw_text(ren->dc, b.l, b.t, pw_frames[pw->current_frame_i]);
}
