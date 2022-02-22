#include "title_bar.h"

#include <malloc.h>
#include "app_info.h"
#include "string_ext.h"


#define BUFFER_LEN	32
static char buffer[BUFFER_LEN];


static void tb_draw(const struct go_delegate* base, struct game_object* go);
const struct go_delegate TB_DRAW[] = { { tb_draw } };

const struct go_type TB_TYPE[] = { { NULL, NULL, TB_DRAW } };


struct title_bar* tb_new(u16 x, u16 y, struct renderer* ren)
{
	struct title_bar* tb = malloc(sizeof * tb);

	_go_init(&tb->go, TB_TYPE);

	tb->go.can_update = 0;
	tb->go.can_draw = 1;

	tb->ren = ren;

	tb->bounds = rect_new(x, y, TB_WIDTH, TB_HEIGHT);

	return tb;
}

static void tb_draw(const struct go_delegate* base, struct game_object* go)
{
	struct title_bar* tb = (void*)go;

	struct renderer* ren = tb->ren;
	struct rectangle b = tb->bounds;

	ren_set_primitive_color(ren, ren->cp->bg);

	rdp_draw_filled_rectangle(b.l, b.t, b.r, b.b);

	sprintf(buffer, "%s v%s", TITLE, TO_STRING(PRETTY_VERSION));
	ren_draw_text(ren, b.l, b.t, buffer);
}
