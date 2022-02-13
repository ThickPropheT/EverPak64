#pragma once

#include "linked_list.h"
#include "game_object.h"
#include "types.h"

struct render_node
{
	struct ll_node node;

	struct render_node* parent;

	struct linked_list* children;

	struct game_object* payload;
};

struct render_node* rn_new(struct game_object* payload);

void rn_add_child(struct render_node* rn, struct render_node* child);
void rn_add_child_for(struct render_node* rn, struct game_object* payload);

u8 rn_update(struct render_node* rn);
void rn_draw(struct render_node* rn);
