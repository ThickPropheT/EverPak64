#include "renderer.h"

#include "gra_console.h"

enum renderer renderer;
bitdepth_t bit_depth;


char* renderer_nameof(enum renderer r)
{
	switch (r)
	{
	case CONSOLE:
		return "console";

	case Gx2D:
		return "2D graphics";

	default:
		return (char*)NULL;
	}
}



char* renderer_current_name(void)
{
	return renderer_nameof(renderer);
}

bitdepth_t renderer_current_bitdepth(void)
{
	return bit_depth;
}



void set_up_console(void)
{
	/* Initialize peripherals */
	console_init();
	console_set_render_mode(RENDER_MANUAL);
}

void set_up_graphics(void)
{
	/* Initialize peripherals */
	display_init(RESOLUTION_320x240, bit_depth, 2, GAMMA_NONE, ANTIALIAS_RESAMPLE);
}

void renderer_init(enum renderer r, bitdepth_t d)
{
	renderer = r;
	bit_depth = d;

	switch (renderer)
	{
	case CONSOLE:
		set_up_console();
		break;

	case Gx2D:
		set_up_graphics();
		break;

	default:
		break;
	}
}



display_context_t lock_graphics(void)
{
	display_context_t dc;

	while (!(dc = display_lock()));

	return dc;
}

display_context_t clear_graphics(uint32_t color)
{
	display_context_t dc = lock_graphics();
	graphics_fill_screen(dc, color);
	return dc;
}

display_context_t renderer_clear(uint32_t color)
{
	switch (renderer)
	{
	case CONSOLE:
		console_clear();
		break;

	case Gx2D:
		return clear_graphics(color);
		
	default:
		break;
	}

	return (display_context_t)NULL;
}



void renderer_print(display_context_t dc, char* text, int x, int y)
{
	switch (renderer)
	{
	case CONSOLE:
		printf(text);
		break;

	case Gx2D:
		gra_print(dc, text, x, y);
		break;

	default:
		break;
	}
}



void renderer_render(display_context_t dc)
{
	switch (renderer)
	{
	case CONSOLE:
		console_render();
		break;

	case Gx2D:
		display_show(dc);
		break;

	default:
		break;
	}
}



void renderer_tear_down(void)
{
	switch (renderer)
	{
	case CONSOLE:
		console_close();
		break;

	case Gx2D:
		display_close();
		break;

	default:
		break;
	}

	renderer_init(renderer, bit_depth);
}

void renderer_current_next(void)
{
	renderer_tear_down();

	renderer++;

	if (renderer >= N_RENDERERS)
		renderer = 0;

	renderer_init(renderer, bit_depth);
}

void renderer_bitdepth_next(void)
{
	renderer_tear_down();

	bit_depth = 1 - bit_depth;

	renderer_init(renderer, bit_depth);
}