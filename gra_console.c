#include "gra_console.h"

#ifndef BIN_TYPES
#define BIN_TYPES

#define X_SCALE		8
#define X_OFFSET	20

#define Y_SCALE		8
#define Y_OFFSET	16

void gra_print(display_context_t dc, char *text, int x, int y)
{
	x = (x*X_SCALE) + X_OFFSET;
	y = (y*Y_SCALE) + Y_OFFSET;
	
	graphics_draw_text(dc, x, y, text);
}

#endif