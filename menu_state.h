#pragma once

#include <stddef.h>

struct menu_state
{
	size_t i_depth;
	size_t max_depth;
};

struct menu_state ms_init(size_t max_depth);

void ms_pop(struct menu_state* ms);
void ms_push(struct menu_state* ms);