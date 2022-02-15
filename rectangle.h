#pragma once

#include "types.h"

struct rectangle
{
	u16 l;
	u16 t;
	u16 r;
	u16 b;

	u16 w;
	u16 h;
};

static inline struct rectangle rect_new(u16 x, u16 y, u16 w, u16 h)
{
	return (struct rectangle) { x, y, (x + w) - 1, (y + h) - 1, w, h };
}
