#include "console.h"

struct console_context cs_init(enum renderer r, bitdepth_t d)
{
	renderer_init(r, d);
	return (struct console_context) { (display_context_t)NULL, 0, 0 };
}

void cs_clear(struct console_context* cc, uint32_t bg_color)
{
	cc->dc = renderer_clear(bg_color);
	cc->c = 0;
	cc->r = 0;
}

void cs_println(struct console_context* cc)
{
	renderer_print(cc->dc, cc->buf, cc->c, (cc->r)++);
}

void cs_render(struct console_context* cc)
{
	renderer_render(cc->dc);
}
