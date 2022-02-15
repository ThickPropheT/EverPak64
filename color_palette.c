#include "color_palette.h"

#include <libdragon.h>
#include <malloc.h>

struct color_palette* cp_new(void)
{
	struct color_palette* cp = malloc(sizeof * cp);

	cp->trans = graphics_make_color(0xFF, 0xFF, 0xFF, 0);
	cp->black = graphics_make_color(0, 0, 0, 0xFF);
	cp->white = graphics_make_color(0xFF, 0xFF, 0xFF, 0xFF);
	cp->lime = graphics_make_color(0x32, 0xCD, 0x32, 0xFF);

	cp->bg = cp->white;
	cp->bg_text = cp->trans;
	cp->fg_text = cp->lime;

	return cp;
}
