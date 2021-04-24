#include "math.h"

/// @brief clamp modulus
u64 cmod(u64 x, u64 m)
{
	return (x % m + m) % m;
}