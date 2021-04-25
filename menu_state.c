#include "menu_state.h"

#include <malloc.h>
#include "math.h"

struct menu_state* ms_new(void)
{
	struct menu_state* ms = malloc(sizeof * ms);
	return ms;
}

static struct menu_node* mn_new(struct game_menu* gm)
{
	struct menu_node* mn = malloc(sizeof * mn);

	mn->mp = mp_new(gm);

	return mn;
}

static inline struct menu_presenter* get_current(struct menu_state* ms)
{
	return ms->mn->mp;
}

void ms_init_root(struct menu_state* ms, struct game_menu* gm)
{
	if (ms->mn != NULL)
		return;

	ms->mn = mn_new(gm);

	mp_entering(ms->mn->mp);
}

static inline void push_node(struct menu_state* ms, struct game_menu* gm)
{
	struct menu_node* new_node = mn_new(gm);

	new_node->prev = ms->mn;
	ms->mn->next = new_node;

	ms->mn = new_node;

	mp_entering(ms->mn->mp);
}

void ms_push(struct menu_state* ms, struct game_menu* gm)
{
	if (ms->mn != NULL)
	{
		push_node(ms, gm);
		return;
	}

	ms_init_root(ms, gm);
}

static void free_leaf(struct menu_node* mn)
{
	mp_free(mn->mp);
	free(mn);
}

void ms_pop(struct menu_state* ms)
{
	struct menu_node* prev = ms->mn->prev;

	if (prev == NULL)
		return;

	mp_leaving(get_current(ms));

	free_leaf(ms->mn);

	prev->next = NULL;
	ms->mn = prev;
}