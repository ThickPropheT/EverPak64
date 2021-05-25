#pragma once

#include "types.h"

/// @brief clamp modulus
static inline u64 cmod(u64 x, u64 m)
{
	return (x % m + m) % m;
}