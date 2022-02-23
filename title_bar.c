#include "title_bar.h"

#include <malloc.h>
#include <math.h>

#include "app_info.h"
#include "string_ext.h"


#define MARGIN		6

#define PADDING_X	9
#define PADDING_Y	3

#define TB_WIDTH	111
#define TB_HEIGHT	7


#define BUFFER_LEN	32
static char buffer[BUFFER_LEN];


static void tb_draw(const struct go_delegate *base, struct game_object *go);
const struct go_delegate TB_DRAW[] = { { tb_draw } };

const struct go_type TB_TYPE[] = { { NULL, NULL, TB_DRAW } };


struct title_bar *tb_new(struct visual *parent, struct renderer *ren)
{
	struct title_bar *tb = malloc(sizeof * tb);
	struct game_object *go = (void *)tb;

	_go_init(go, TB_TYPE);

	go->can_update = 0;
	go->can_draw = 1;

	struct visual *vis = (void *)tb;

	vis->node = rn_add_child_for(parent->node, go);
	vis->ren = ren;

	struct rectangle b = parent->bounds;

	u16 top = b.t + MARGIN;
	u16 left = roundf((b.t + b.w / 2.0f) - TB_WIDTH / 2.0f);

	vis->bounds = rect_new(left, top, TB_WIDTH, TB_HEIGHT);

	tb->border_bounds = rect_scale(tb->vis.bounds, PADDING_X, PADDING_Y);

	return tb;
}

static void tb_draw(const struct go_delegate *base, struct game_object *go)
{
	struct title_bar *tb = (void *)go;

	struct renderer *ren = tb->vis.ren;
	struct rectangle b = tb->vis.bounds;

	ren_draw_rectangle(ren, tb->border_bounds, ren->cp->border);

	sprintf(buffer, "%s v%s", TITLE, TO_STRING(PRETTY_VERSION));
	ren_draw_text(ren, b.l, b.t, buffer);
}
