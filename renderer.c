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

	return (struct rectangle) { 0, 0, w, h };
}

struct renderer* ren_new(resolution_t res, bitdepth_t bpp, uint32_t num_buf, gamma_t gamma, antialias_t aa)
{
	display_init(res, bpp, num_buf, gamma, aa);

	struct renderer* ren = malloc(sizeof * ren);

	ren->res = res;
	ren->bpp = bpp;
	ren->num_buf = num_buf;
	ren->gamma = gamma;
	ren->aa = aa;
	ren->rdp_enabled = 0;

	ren->view_port = to_rect(res);

	ren->dc = 0;

	return ren;
}

void ren_request_rdp(struct renderer* ren)
{
	if (ren->rdp_enabled)
		return;

	rdp_init();

	ren->rdp_enabled = 1;
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

		rdp_close();

		ren->rdp_enabled = 0;
	}

	display_show(ren->dc);
}
