#include "color_palette.h"

#include <libdragon.h>
#include <malloc.h>

struct color_palette *cp_new(void)
{
	struct color_palette *cp = malloc(sizeof * cp);

	cp->trans = graphics_make_color(0xFF, 0xFF, 0xFF, 0);
	cp->black = graphics_make_color(0, 0, 0, 0xFF);
	cp->white = graphics_make_color(0xFF, 0xFF, 0xFF, 0xFF);

	cp->forest_green = graphics_make_color(0x1A, 0x56, 0x53, 0xFF);
	cp->teal_green = graphics_make_color(0x10, 0x78, 0x69, 0xFF);
	/*cp->lime = graphics_make_color(0x32, 0xCD, 0x32, 0xFF);*/
	cp->lime_green = graphics_make_color(0x5C, 0xD8, 0x5A, 0xFF);
	cp->dark_forest_green = graphics_make_color(0x08, 0x31, 0x3A, 0xFF);

	cp->bg = cp->dark_forest_green;
	cp->border = cp->teal_green;
	cp->bg_text = cp->trans;
	cp->fg_text = cp->white;

	return cp;
}
