#pragma once

#include <stdio.h>
#include <libdragon.h>

#include "types.h"

enum renderer
{
	CONSOLE,
	Gx2D,
	N_RENDERERS
};

char *renderer_nameof(enum renderer r);

char* renderer_current_name(void);
bitdepth_t renderer_current_bitdepth(void);

void renderer_init(enum renderer r, bitdepth_t d);

display_context_t renderer_clear(uint32_t color);

void renderer_print(display_context_t dc, char* text, int x, int y);
void renderer_render(display_context_t dc);

void renderer_current_next(void);
void renderer_bitdepth_next(void);
