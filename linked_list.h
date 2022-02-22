#pragma once

struct ll_node
{
	struct ll_node *prev;
	struct ll_node *next;
};

struct linked_list
{
	struct ll_node *head;
	struct ll_node *tail;
};

struct ll_enumerator
{
	struct ll_node *current;
};

struct linked_list *ll_new(void);

void ll_node_init(struct ll_node *node);

void ll_add_last(struct linked_list *list, struct ll_node *node);
void ll_remove(struct linked_list *list, struct ll_node *node);

struct ll_enumerator ll_get_enumerator(struct ll_node *node);

struct ll_node *lle_next(struct ll_enumerator *en);
