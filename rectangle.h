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

static inline struct rectangle rect_new(u16 l, u16 t, u16 w, u16 h)
{
	return (struct rectangle) { l, t, (l + w) - 1, (t + h) - 1, w, h };
}

static inline struct rectangle rect_scale(struct rectangle r, u16 x, u16 y)
{
	return (struct rectangle) { r.l - x, r.t - y, r.r + x, r.b + y, (r.r - r.l) + 1, (r.b - r.t) + 1 };
}
