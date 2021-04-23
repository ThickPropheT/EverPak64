#pragma once

#include <stddef.h>

struct menu_state
{
	size_t i_depth;
	size_t max_depth;
};

struct menu_state* ms_new(size_t max_depth);

void ms_popd(struct menu_state* ms);
void ms_pushd(struct menu_state* ms);