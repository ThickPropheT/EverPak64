#include "linked_list.h"

#include <malloc.h>

struct linked_list *ll_new(void)
{
	struct linked_list *list = calloc(1, sizeof * list);
	return list;
}

void ll_node_init(struct ll_node *node)
{
	node->prev = NULL;
	node->next = NULL;
}

void ll_add_last(struct linked_list *list, struct ll_node *node)
{
	if (list->head == NULL)
	{
		list->head = node;
		list->tail = node;
		return;
	}

	node->prev = list->tail;
	list->tail->next = node;

	list->tail = node;
}

void ll_remove(struct linked_list *list, struct ll_node *node)
{
	if (node->prev)
		node->prev->next = node->next;

	if (node->next)
		node->next->prev = node->prev;

	if (list->tail == node)
		list->tail = node->prev;

	if (list->head == node)
		list->head = node->next;
}

struct ll_enumerator ll_get_enumerator(struct ll_node *node)
{
	struct ll_enumerator en = { node };
	return en;
}

struct ll_node *lle_next(struct ll_enumerator *en)
{
	struct ll_node *current = en->current;

	if (!current)
		return NULL;

	en->current = current->next;

	return current;
}
