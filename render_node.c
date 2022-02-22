#include "render_node.h"

#include <stdlib.h>

struct render_node *rn_new(struct game_object *payload)
{
	struct render_node *rn = calloc(1, sizeof * rn);

	rn->payload = payload;

	return rn;
}

void rn_add_child(struct render_node *rn, struct render_node *child)
{
	if (!rn->children)
		rn->children = ll_new();

	ll_add_last(rn->children, (void *)child);
	child->parent = rn;
}

struct render_node *rn_add_child_for(struct render_node *rn, struct game_object *payload)
{
	struct render_node *child = rn_new(payload);
	rn_add_child(rn, child);
	return child;
}

void rn_clear_children(struct render_node *rn)
{
	struct linked_list *children = rn->children;

	if (!children)
		return;

	struct ll_node *child = children->head;
	struct ll_node *next;

	while (child)
	{
		next = child->next;

		struct render_node *cn = (void *)child;

		rn_clear_children(cn);

		ll_remove(children, child);

		free(cn->payload);
		free(cn->update_trigger);
		free(cn);

		child = next;
	}
}


void rn_update(struct render_node *rn)
{
	struct game_object *go = rn->payload;

	// check trigger before checking if go exists
	// so that trigger is always updated
	if (trg_check(rn->update_trigger) && go)
	{
		go_update(go);
	}

	if (rn->children)
	{
		struct ll_enumerator en = ll_get_enumerator(rn->children->head);

		struct render_node *child;
		while ((child = (void *)lle_next(&en)))
		{
			rn_update(child);
		}
	}

	trg_reset(rn->update_trigger);
}

void rn_draw(struct render_node *rn)
{
	struct game_object *go = rn->payload;

	if (go)
		go_draw(go);

	if (rn->children)
	{
		struct ll_enumerator en = ll_get_enumerator(rn->children->head);

		struct render_node *child;
		while ((child = (void *)lle_next(&en)))
		{
			rn_draw(child);
		}
	}
}
