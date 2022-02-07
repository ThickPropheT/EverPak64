#pragma once

struct ll_node
{
	struct ll_node* prev;
	struct ll_node* next;
};

struct linked_list
{
	struct ll_node* head;
	struct ll_node* tail;
};

struct linked_list* ll_new(void);

void ll_node_init(struct ll_node* node);

void ll_add_last(struct linked_list* list, struct ll_node* node);
void ll_remove(struct linked_list* list, struct ll_node* node);