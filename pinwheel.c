#include <libdragon.h>

#include "pinwheel.h"


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


struct pinwheel *pw_new(u16 x, u16 y, struct renderer *ren)
{
	struct pinwheel *pw = calloc(1, sizeof * pw);

	_go_init(&pw->go, PW_TYPE);

	pw->go.can_update = 1;
	pw->go.can_draw = 1;

	pw->ren = ren;

	pw->bounds = rect_new(x, y, PW_WIDTH, PW_HEIGHT);

	return pw;
}

static void pw_update(const struct go_delegate *base, struct game_object *go)
{
	struct pinwheel *pw = (void *)go;

	pw->current_frame_i = (pw->current_frame_i + 1) % N_PW_FRAMES;
	ren_invalidate(pw->ren);
}

static void pw_draw(const struct go_delegate *base, struct game_object *go)
{
	struct pinwheel *pw = (void *)go;

	struct renderer *ren = pw->ren;
	struct rectangle b = pw->bounds;

	ren_set_primitive_color(ren, ren->cp->bg);

	rdp_draw_filled_rectangle(b.l, b.t, b.r, b.b);

	ren_draw_text(ren, b.l, b.t, pw_frames[pw->current_frame_i]);
}
