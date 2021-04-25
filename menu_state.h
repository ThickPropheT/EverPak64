#pragma once

#include <stddef.h>
#include "menu_presenter.h"
#include "game_menu.h"

struct menu_node
{
	struct menu_presenter* mp;
	struct menu_node* prev;
	struct menu_node* next;
};

struct menu_state
{
	struct menu_node* root;
	struct menu_node* mn;
};

struct menu_state* ms_new(void);

void ms_init_root(struct menu_state* ms, struct game_menu* gm);

void ms_push(struct menu_state* ms, struct game_menu* gm);
void ms_pop(struct menu_state* ms);
