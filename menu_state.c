#include "menu_state.h"

#include "math.h"

struct menu_state ms_new(size_t max_depth)
{
	return (struct menu_state) { 0, max_depth };
}

void ms_popd(struct menu_state* ms)
{
	ms->i_depth = cmod(ms->i_depth - 1, ms->max_depth);
}

void ms_pushd(struct menu_state* ms)
{
	ms->i_depth = cmod(ms->i_depth + 1, ms->max_depth);
}