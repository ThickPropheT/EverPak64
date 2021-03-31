#include "math.h"

int mod(int x, int m)
{
	return (x % m + m) % m;
}