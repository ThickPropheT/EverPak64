#include "render_node.h"

#include <stdlib.h>

#include "console.h"

struct render_node* rn_new(struct game_object* payload)
{
	struct render_node* rn = calloc(1, sizeof * rn);

	rn->payload = payload;

	return rn;
}

void rn_add_child(struct render_node* rn, struct render_node* child)
{
	if (!rn->children)
		rn->children = ll_new();

	ll_add_last(rn->children, (void*)child);
	child->parent = rn;
}

void rn_add_child_for(struct render_node* rn, struct game_object* payload)
{
	rn_add_child(rn, rn_new(payload));
}


void rn_update(struct render_node* rn)
{
	struct game_object* go = rn->payload;

	if (go)
	{
		go_update(go);
	}

	if (rn->children)
	{
		struct ll_enumerator en = ll_get_enumerator(rn->children->head);

		struct render_node* child;
		while ((child = (void*)lle_next(&en)))
		{
			rn_update(child);
		}
	}
}

void rn_draw(struct render_node* rn)
{
	struct game_object* go = rn->payload;

	if (go)
		go_draw(go);

	if (rn->children)
	{
		struct ll_enumerator en = ll_get_enumerator(rn->children->head);

		struct render_node* child;
		while ((child = (void*)lle_next(&en)))
		{
			rn_draw(child);
		}
	}
}
