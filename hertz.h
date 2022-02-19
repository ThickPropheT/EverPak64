#pragma once

#include "types.h"
#include <math.h>

static u64 hz_from_fps(float fps)
{
	return roundf(1000.0f / fps);
}
