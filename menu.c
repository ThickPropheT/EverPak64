#include "menu.h"

#include "math.h"

void m_prev_item(struct menu* m)
{
	m->i_item = cmod(m->i_item - 1, m->n_items);
}

void m_next_item(struct menu* m)
{
	m->i_item = cmod(m->i_item + 1, m->n_items);
}
