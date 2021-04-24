#pragma once

#include <stddef.h>
#include "game_menu.h"

struct menu_node
{
	struct game_menu* gm;
	struct menu_node* prev;
	struct menu_node* next;
};

struct menu_state
{
	size_t i_depth;
	size_t max_depth;

	struct menu_node* mn;
};

struct menu_state* ms_new(size_t max_depth);

void ms_popd(struct menu_state* ms);
void ms_pushd(struct menu_state* ms);

void ms_push(struct menu_state* ms, struct game_menu* gm);
void ms_pop(struct menu_state* ms);
