#include "linked_list.h"

#include <malloc.h>

struct linked_list* ll_new(void)
{
	struct linked_list* list = calloc(1, sizeof * list);
	return list;
}

void ll_node_init(struct ll_node* node)
{
	node->prev = NULL;
	node->next = NULL;
}

void ll_add_last(struct linked_list* list, struct ll_node* node)
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

void ll_remove(struct linked_list* list, struct ll_node* node)
{
	if (node->prev != NULL)
		node->prev->next = node->next;

	if (node->next != NULL)
		node->next->prev = node->prev;

	if (list->tail == node)
		list->tail = node->prev;

	if (list->head == node)
		list->head = node->next;
}