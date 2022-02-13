#include <libdragon.h>

#include "pinwheel.h"

#define WIDTH	21
#define	HEIGHT	6

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
	struct pinwheel* pw = malloc(sizeof * pw);

	_go_init(&pw->go, PW_TYPE);

	pw->go.can_update = 1;
	pw->go.can_draw = 1;

	pw->ren = ren;

	pw->bounds = (struct rectangle){ x, y, x + WIDTH, y + HEIGHT };

	pw->resolution = resolution;
	pw->current_frame_i = 0;

	return pw;
}

static void pw_update(const struct go_delegate* base, struct game_object* go)
{
	struct pinwheel* pw = (void*)go;

	ren_request_rdp(pw->ren);

	u32 ticks_ms = get_ticks_ms();

	if (ticks_ms - pw->last_tick_ms > pw->resolution)
	{
		pw->current_frame_i = (pw->current_frame_i + 1) % N_PW_FRAMES;
		pw->last_tick_ms = ticks_ms;

		//go->can_draw = 1;
	}
}

static void pw_draw(const struct go_delegate* base, struct game_object* go)
{
	struct pinwheel* pw = (void*)go;

	struct rectangle b = pw->bounds;

	rdp_sync(SYNC_PIPE);

	rdp_enable_primitive_fill();

	rdp_set_primitive_color(0xFFFFFFFF);
	rdp_draw_filled_rectangle(b.x, b.y, b.w, b.h);

	graphics_draw_text(pw->ren->dc, b.x, b.y, pw_frames[pw->current_frame_i]);

	//go->can_draw = 0;
}
