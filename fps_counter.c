#include <libdragon.h>

#include "fps_counter.h"

u32 fps_resolution = 0;
float *fps_value;
u32 fps_last_ms = 0;

u8 fps_frames = 0;

void fps_init(u32 resolution, float *fps)
{
	fps_resolution = resolution;
	fps_value = fps;
	
	fps_last_ms = get_ticks_ms();
}

void fps_update(void)
{
	fps_frames++;
	
	if (get_ticks_ms() - fps_last_ms > fps_resolution)
	{
		*fps_value = fps_frames / 2.0;
		fps_frames = 0;
		fps_last_ms = get_ticks_ms();
	}
}