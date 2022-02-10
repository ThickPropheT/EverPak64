#include "console.h"


static struct console_context cc;


void cs_init(void)
{
	cc = cc_new();
}

struct console_context* cs_get_current(void)
{
	return &cc;
}

void cs_clear(struct renderer* ren, uint32_t bg_color)
{
	cc.dc = ren->dc;
	cc_clear(&cc, bg_color);
}
