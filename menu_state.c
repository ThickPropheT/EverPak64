#include "menu_state.h"

#include <malloc.h>
#include "math.h"

struct menu_state* ms_new(size_t max_depth)
{
	struct menu_state* ms = malloc(sizeof * ms);

	ms->i_depth = 0;
	ms->max_depth = max_depth;

	return ms;
}

void ms_popd(struct menu_state* ms)
{
	ms->i_depth = cmod(ms->i_depth - 1, ms->max_depth);
}

void ms_pushd(struct menu_state* ms)
{
	ms->i_depth = cmod(ms->i_depth + 1, ms->max_depth);
}