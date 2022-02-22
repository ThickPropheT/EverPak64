#pragma once

#include <stdio.h>
#include <libdragon.h>
#include "rectangle.h"
#include "color_palette.h"

struct renderer
{
	resolution_t res;
	bitdepth_t bpp;
	uint32_t num_buf;
	gamma_t gamma;
	antialias_t aa;

	struct rectangle view_port;

	struct color_palette* cp;

	u8 rdp_enabled;

	u8 draw_requested;

	display_context_t dc;

	u8 fill_enabled;
	uint32_t fill_color;
};

struct renderer* ren_new(resolution_t res, bitdepth_t bpp, uint32_t num_buf, gamma_t gamma, antialias_t aa);

void ren_set_rdp_enabled(struct renderer* ren, u8 enabled);

void ren_invalidate(struct renderer* ren);

void ren_lock(struct renderer* ren);
void ren_show(struct renderer* ren);

void ren_set_primitive_color(struct renderer* ren, uint32_t color);

void ren_draw_text(struct renderer* ren, int x, int y, const char* const message);
