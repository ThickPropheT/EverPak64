#pragma once

#include "types.h"

/// @brief clamp modulus
static inline u64 cmod(u64 x, u64 m)
{
	return (x % m + m) % m;
}

static inline u64 math_min(u64 x, u64 min)
{
	return (x <= min) ? x : min;
}

static inline u64 math_minp(u64 *x, u64 min)
{
	u64 xv = *x;
	return *x = (xv <= min) ? xv : min;
}

static inline u64 math_max(u64 x, u64 max)
{
	return (x >= max) ? x : max;
}

static inline u64 math_maxp(u64 *x, u64 max)
{
	u64 xv = *x;
	return *x = (xv >= max) ? xv : max;
}

static inline u64 math_clamp(u64 x, u64 min, u64 max)
{
	return math_min(max, math_max(min, x));
}

static inline u64 math_clampp(u64 *x, u64 min, u64 max)
{
	return *x = math_min(max, math_max(min, *x));
}
