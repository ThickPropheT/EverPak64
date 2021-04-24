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

static struct menu_node* mn_new(struct game_menu* gm)
{
	struct menu_node* mn = malloc(sizeof * mn);

	mn->gm = gm;

	return mn;
}

static inline void ms_init(struct menu_state* ms, struct game_menu* gm)
{
	ms->mn = mn_new(gm);
}

static inline void ms_push_impl(struct menu_state* ms, struct game_menu* gm)
{
	struct menu_node* new_node = mn_new(gm);

	new_node->prev = ms->mn;
	ms->mn->next = new_node;

	ms->mn = new_node;
}

void ms_push(struct menu_state* ms, struct game_menu* gm)
{
	if (ms->mn != NULL)
	{
		ms_push_impl(ms, gm);
		return;
	}

	ms_init(ms, gm);
}

void ms_pop(struct menu_state* ms)
{
	struct menu_node* prev = ms->mn->prev;

	if (prev == NULL)
		return;

	free(ms->mn);

	prev->next = NULL;
	ms->mn = prev;
}