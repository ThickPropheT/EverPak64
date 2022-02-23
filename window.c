#include "window.h"

#include "app_info.h"
#include "string_ext.h"

#define MARGIN		8


static void draw(const struct go_delegate *base, struct game_object *go);
const struct go_delegate WIN_DRAW[] = { { draw } };

const struct go_type WIN_TYPE[] = { { NULL, NULL, WIN_DRAW } };


struct window *win_new(struct render_node *root, struct renderer *ren)
{
	struct window *win = malloc(sizeof * win);
	struct game_object *go = (void *)win;

	_go_init(go, WIN_TYPE);

	go->can_update = 0;
	go->can_draw = 1;

	win->vis.node = rn_add_child_for(root, (void *)win);
	win->vis.ren = ren;

	win->vis.bounds = rect_scale(ren->view_port, -MARGIN, -MARGIN);

	return win;
}

static void draw(const struct go_delegate *base, struct game_object *go)
{
	struct window *win = (void *)go;

	struct renderer *ren = win->vis.ren;

	display_context_t dc = ren->dc;
	struct color_palette *cp = ren->cp;

	graphics_fill_screen(dc, cp->bg);
}
