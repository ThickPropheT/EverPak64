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
	struct menu_node* mn = calloc(1, sizeof * mn);

	mn->mp = mp_new(gm);

	return mn;
}


void ms_init_root(struct menu_state* ms, struct game_menu* gm)
{
	if (ms->mn != NULL)
		return;

	struct menu_node* root = mn_new(gm);

	ms->root = root;
	ms->mn = ms->root;

	mp_entering(root->mp);
}

static inline void push_node(struct menu_state* ms, struct game_menu* gm)
{
	struct menu_node* current = ms->mn;

	mp_leaving(current->mp);

	struct menu_node* new_node = mn_new(gm);

	new_node->prev = current;
	current->next = new_node;

	ms->mn = new_node;

	mp_entering(new_node->mp);
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
	struct menu_node* current = ms->mn;
	struct menu_node* prev = current->prev;

	if (prev == NULL)
		return;

	mp_leaving(current->mp);

	free_leaf(current);

	prev->next = NULL;
	ms->mn = prev;

	mp_entering(prev->mp);
}


struct mn_enumerator ms_get_enumerator(struct menu_state* ms)
{
	struct mn_enumerator mne = { ms->root };
	return mne;
}

struct menu_presenter* mne_move_next(struct mn_enumerator* mne)
{
	struct menu_node* current = mne->current;

	if (current == NULL)
		return NULL;

	mne->current = current->next;

	return current->mp;
}
