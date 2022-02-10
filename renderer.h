#pragma once

#include <stdio.h>
#include <libdragon.h>

#include "rectangle.h"

struct renderer
{
	resolution_t res;
	bitdepth_t bpp;
	uint32_t num_buf;
	gamma_t gamma;
	antialias_t aa;

	u8 rdp_enabled;

	struct rectangle view_port;

	display_context_t dc;
};

struct renderer* ren_new(resolution_t res, bitdepth_t bpp, uint32_t num_buf, gamma_t gamma, antialias_t aa);

void ren_request_rdp(struct renderer* ren);

void ren_lock(struct renderer* ren);
void ren_show(struct renderer* ren);
