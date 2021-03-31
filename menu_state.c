#include "menu_state.h"

#include "math.h"

struct menu_state ms_init(size_t max_depth)
{
	return (struct menu_state) { 0, max_depth };
}

void ms_pop(struct menu_state* ms)
{
	ms->i_depth = cmod(ms->i_depth - 1, ms->max_depth);
}

void ms_push(struct menu_state* ms)
{
	ms->i_depth = cmod(ms->i_depth + 1, ms->max_depth);
}