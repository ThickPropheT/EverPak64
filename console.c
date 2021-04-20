#include "console.h"


static struct console_context cc;


void cs_init(enum renderer r, bitdepth_t d)
{
	cc = cc_new(r, d);
}

struct console_context* cs_get_current(void)
{
	return &cc;
}

void cs_clear(uint32_t bg_color)
{
	cc_clear(&cc, bg_color);
}

void cs_render(void)
{
	cc_render(&cc);
}