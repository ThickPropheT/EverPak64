#pragma once

#include "types.h"

struct rectangle
{
	u16 x;
	u16 y;
	u16 w;
	u16 h;

	u16 bx;
	u16 by;
};

static inline struct rectangle rect_new(u16 x, u16 y, u16 w, u16 h)
{
	return (struct rectangle) { x, y, w, h, x + w, y + h };
}
