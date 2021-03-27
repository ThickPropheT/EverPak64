#include <libdragon.h>

#include "pinwheel.h"

u32 pw_resolution = 0;
u8 pw_frame_i = 0;
char *pw_frame;

u32 pw_last_ms = 0;

#define N_PW_FRAMES 4
char pw_frames[N_PW_FRAMES] =
{
	'\\',
	'|',
	'/',
	'-'
};

void pw_init(u32 resolution, u8 frame_i, char *pinwheel)
{
	pw_resolution = resolution;
	pw_frame_i = frame_i;
	pw_frame = pinwheel;
	
	*pw_frame = pw_frames[pw_frame_i];
	
	pw_last_ms = get_ticks_ms();
}

void pw_update(void)
{
	if (get_ticks_ms() - pw_last_ms > pw_resolution)
	{
		pw_frame_i = (pw_frame_i + 1) % N_PW_FRAMES;
		*pw_frame = pw_frames[pw_frame_i];
		
		pw_last_ms = get_ticks_ms();
	}
}