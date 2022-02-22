#include "renderer.h"

#include <malloc.h>

#include "types.h"

static struct rectangle to_rect(resolution_t res)
{
	u16 w = 320;
	u16 h = 240;

	switch (res)
	{
	case RESOLUTION_640x480:
		w = 640;
	case RESOLUTION_512x480:
		w = 512;
		h = 480;
		break;

	case RESOLUTION_256x240:
		w = 256;
	case RESOLUTION_512x240:
		w = 512;
	case RESOLUTION_640x240:
		w = 640;
	case RESOLUTION_320x240:
		w = 320;
		h = 240;
	}

	return rect_new(0, 0, w, h);
}

struct renderer* ren_new(resolution_t res, bitdepth_t bpp, uint32_t num_buf, gamma_t gamma, antialias_t aa)
{
	display_init(res, bpp, num_buf, gamma, aa);

	struct renderer* ren = calloc(1, sizeof * ren);

	ren->res = res;
	ren->bpp = bpp;
	ren->num_buf = num_buf;
	ren->gamma = gamma;
	ren->aa = aa;

	ren->view_port = to_rect(res);

	ren->cp = cp_new();

	return ren;
}

void ren_set_rdp_enabled(struct renderer* ren, u8 enabled)
{
	u8 is_enabled = ren->rdp_enabled;

	if (is_enabled == enabled)
		return;

	ren->rdp_enabled = enabled;

	if (enabled)
	{
		rdp_init();
	}
	else if (is_enabled)
	{
		rdp_close();
	}
}


void ren_invalidate(struct renderer* ren)
{
	ren->draw_requested = 1;
}

static inline display_context_t lock_graphics(void)
{
	display_context_t dc;

	while (!(dc = display_lock()));

	return dc;
}

void ren_lock(struct renderer* ren)
{
	display_context_t dc = lock_graphics();

	if (ren->rdp_enabled)
	{
		rdp_sync(SYNC_PIPE);
		rdp_set_default_clipping();
		rdp_attach_display(dc);
	}

	ren->dc = dc;
}

void ren_show(struct renderer* ren)
{
	if (ren->rdp_enabled)
	{
		rdp_detach_display();
	}

	display_show(ren->dc);

	ren->draw_requested = 0;
}


void ren_set_primitive_color(struct renderer* ren, uint32_t color)
{
	u8 fill_enabled = ren->fill_enabled;
	u8 color_changed = ren->fill_color != color;

	if (fill_enabled
		&& !color_changed)
		return;

	ren->fill_enabled = 1;
	ren->fill_color = color;

	if (ren->rdp_enabled)
	{
		rdp_sync(SYNC_PIPE);

		if (!fill_enabled)
			rdp_enable_primitive_fill();

		if (color_changed)
			rdp_set_primitive_color(color);
	}
}

void ren_draw_text(struct renderer* ren, int x, int y, const char* const message)
{
	if (ren->rdp_enabled)
		rdp_detach_display();

	display_context_t dc = ren->dc;

	graphics_draw_text(dc, x, y, message);

	if (ren->rdp_enabled)
		rdp_attach_display(dc);
}
