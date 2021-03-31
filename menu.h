#pragma once

#include <stddef.h>

struct menu
{
	size_t i_item;
	size_t n_items;
};

void m_prev_item(struct menu* m);
void m_next_item(struct menu* m);