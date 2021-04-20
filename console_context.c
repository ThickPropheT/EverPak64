#include "console_context.h"

struct console_context cc_new(enum renderer r, bitdepth_t d)
{
	renderer_init(r, d);
	return (struct console_context) { (display_context_t)NULL, 0, 0 };
}

void cc_clear(struct console_context* cc, uint32_t bg_color)
{
	cc->dc = renderer_clear(bg_color);
	cc->c = 0;
	cc->r = 0;
}

void cc_println(struct console_context* cc)
{
	renderer_print(cc->dc, cc->buf, cc->c, (cc->r)++);
}

void cc_render(struct console_context* cc)
{
	renderer_render(cc->dc);
}
