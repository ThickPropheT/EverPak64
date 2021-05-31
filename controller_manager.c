#include "controller_manager.h"

#include <malloc.h>
#include <libdragon.h>
#include "console.h"

#define ANY_SLOT N_SLOTS

static struct input_handler_list* ihl_new(void)
{
	struct input_handler_list* list = calloc(1, sizeof * list);
	return list;
}

struct controller_manager* cman_new(struct device_state* dev)
{
	struct controller_manager* cman = malloc(sizeof * cman);

	cman->dev = dev;

	cman->ctrl_flags = 0;
	cman->acc_flags = 0;

	for (u8 i = 0; i < N_SLOTS; i++)
		cman->controllers[i] = ctrl_new(dev, dev->accessories[i], i);

	cman->any_controller = ctrl_new(dev, NULL, ANY_SLOT);

	for (u8 i = 0; i < N_HANDLERS; i++)
		cman->input_handlers[i] = ihl_new();

	return cman;
}

static inline void flags_changed(struct controller_manager* cman, u16 ctrl_from, u16 ctrl_to, u16 acc_from, u16 acc_to)
{
	u8 ctrl_changed = ctrl_from != ctrl_to;
	u8 acc_changed = acc_from != acc_to;

	for (u8 i = 0; i < N_SLOTS; i++)
	{
		struct controller* ctrl = cman->controllers[i];

		u16 flag = get_flag(i);

		u8 update_status =
			ctrl_changed
			&& did_flag_change(flag, ctrl_from, ctrl_to);

		u8 update_acc =
			acc_changed
			&& did_flag_change(flag, acc_from, acc_to);

		if (update_status)
		{
			ctrl->status = (ctrl_to & flag) == flag
				? CTRL_STATUS_READY
				: CTRL_STATUS_MISSING;
		}

		if (update_acc)
		{
			ctrl->acc = cman->dev->accessories[i];
		}
	}
}

static inline void update_flags(struct controller_manager* cman)
{
	u16 ctrl_f = cman->ctrl_flags;
	u16 acc_f = cman->dev->acc_flags;

	u8 acc_changed = cman->acc_flags != acc_f;

	if (acc_changed
		|| acc_f == 0)
		ctrl_f = get_controllers_present();

	u8 ctrl_changed = cman->ctrl_flags != ctrl_f;

	if (!acc_changed
		&& !ctrl_changed)
		return;

	flags_changed(cman, cman->ctrl_flags, ctrl_f, cman->acc_flags, acc_f);

	cman->ctrl_flags = ctrl_f;
	cman->acc_flags = acc_f;
}


static inline void cman_handle_input(struct controller_manager* cman)
{
	for (u8 slot = 0; slot < N_SLOTS; slot++)
	{
		struct controller* ctrl = cman->controllers[slot];

		if (ctrl->status != CTRL_STATUS_READY)
			continue;

		u8 h_slot = slot;

		struct input_handler* handler = cman->input_handlers[h_slot]->head;

		while (handler != NULL)
		{
			handler->handle(ctrl, handler->context);

			handler = handler->next;
		}

		handler = cman->input_handlers[ANY_SLOT]->head;

		while (handler != NULL)
		{
			handler->handle(ctrl, handler->context);

			handler = handler->next;
		}
	}
}

void cman_update(struct controller_manager* cman)
{
	update_flags(cman);

	cman_handle_input(cman);
}



static struct input_handler* ih_new(struct controller* ctrl, void* context, handle_input handle)
{
	struct input_handler* handler = malloc(sizeof * handler);

	handler->ctrl = ctrl;
	handler->context = context;
	handler->handle = handle;

	handler->prev = NULL;
	handler->next = NULL;

	return handler;
}


static inline void add_handler(struct controller_manager* cman, u8 i_slot, struct input_handler* handler)
{
	struct input_handler_list* list = cman->input_handlers[i_slot];

	if (list->head == NULL)
	{
		list->head = handler;
		list->tail = handler;
		return;
	}

	handler->prev = list->tail;
	list->tail->next = handler;

	list->tail = handler;
}

struct input_handler* cman_add_handler(struct controller_manager* cman, struct controller* ctrl, void* context, handle_input handle)
{
	struct input_handler* handler = ih_new(ctrl, context, handle);

	add_handler(cman, ctrl->i_slot, handler);

	return handler;
}


static inline void remove_handler(struct controller_manager* cman, u8 i_slot, struct input_handler* handler)
{
	if (handler->prev != NULL)
		handler->prev->next = handler->next;

	if (handler->next != NULL)
		handler->next->prev = handler->prev;

	struct input_handler_list* list = cman->input_handlers[i_slot];

	if (list->tail == handler)
		list->tail = handler->prev;

	if (list->head == handler)
		list->head = handler->next;
}

void cman_rem_handler(struct controller_manager* cman, struct input_handler* handler)
{
	remove_handler(cman, handler->ctrl->i_slot, handler);
	free(handler);
}
