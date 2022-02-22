#include "console_context.h"

#define X_SCALE		8
#define X_OFFSET	20

#define Y_SCALE		8
#define Y_OFFSET	16

struct console_context cc_new(void)
{
	return (struct console_context) { (display_context_t)NULL, 0, 0 };
}

void cc_clear(struct console_context *cc, uint32_t bg_color)
{
	graphics_fill_screen(cc->dc, bg_color);
	cc->c = 0;
	cc->r = 0;
}

static inline void draw_line(display_context_t dc, char *text, int x, int y)
{
	x = (x * X_SCALE) + X_OFFSET;
	y = (y * Y_SCALE) + Y_OFFSET;

	graphics_draw_text(dc, x, y, text);
}

void cc_println(struct console_context *cc)
{
	draw_line(cc->dc, cc->buf, cc->c, (cc->r)++);
}
