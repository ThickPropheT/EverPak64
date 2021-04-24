#include <libdragon.h>

#include "fps_counter.h"

u32 fps_interval_ms = 0;
float *fps_value;
u32 fps_last_ms = 0;

u8 fps_frames = 0;

void fps_init(u32 interval_ms, float *fps)
{
	fps_interval_ms = interval_ms;
	fps_value = fps;
	
	fps_last_ms = get_ticks_ms();
}

void fps_update(void)
{
	fps_frames++;
	
	if (get_ticks_ms() - fps_last_ms >= fps_interval_ms)
	{
		*fps_value = fps_frames / 2.0;
		fps_frames = 0;
		fps_last_ms = get_ticks_ms();
	}
}