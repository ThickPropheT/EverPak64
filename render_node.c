#include "render_node.h"

#include <stdlib.h>

#include "console.h"

struct render_node* rn_new(struct game_object* payload)
{
	struct render_node* rn = malloc(sizeof * rn);

	rn->parent = NULL;
	rn->children = ll_new();

	rn->payload = payload;

	return rn;
}

void rn_add_child(struct render_node* rn, struct render_node* child)
{
	ll_add_last(rn->children, (void*)child);
	child->parent = rn;
}

void rn_add_child_for(struct render_node* rn, struct game_object* payload)
{
	rn_add_child(rn, rn_new(payload));
}


u8 rn_update(struct render_node* rn)
{
	if (rn->payload)
		go_update(rn->payload);

	u8 draw_requested = 1;

	struct ll_enumerator en = ll_get_enumerator(rn->children->head);

	struct render_node* child;
	while ((child = (void*)lle_next(&en)))
	{
		draw_requested |= rn_update(child);
	}

	return draw_requested;
}

void rn_draw(struct render_node* rn)
{
	if (rn->payload)
		go_draw(rn->payload);

	struct ll_enumerator en = ll_get_enumerator(rn->children->head);

	struct render_node* child;
	while ((child = (void*)lle_next(&en)))
	{
		rn_draw(child);
	}
}
