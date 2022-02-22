#include "controller_manager.h"

#include <malloc.h>
#include <libdragon.h>
#include "console.h"



#define ANY_SLOT N_SLOTS



static void update(const struct go_delegate *base, struct game_object *go);
const struct go_delegate UPDATE[] = { { update } };

const struct go_type TYPE[] = { { NULL, UPDATE } };


static struct input_handler *ih_new(struct controller *ctrl, void *context, handle_input handle)
{
	struct input_handler *handler = malloc(sizeof * handler);

	handler->is_disposed = 0;

	handler->ctrl = ctrl;
	handler->context = context;
	handler->handle = handle;

	ll_node_init((void *)handler);

	return handler;
}



struct controller_manager *cman_new(struct device_state *dev)
{
	struct controller_manager *cman = malloc(sizeof * cman);

	_go_init((void *)cman, TYPE);

	cman->go.can_update = 1;
	cman->go.can_draw = 0;

	cman->dev = dev;

	cman->ctrl_flags = 0;
	cman->acc_flags = 0;

	for (u8 i = 0; i < N_SLOTS; i++)
		cman->controllers[i] = ctrl_new(dev, dev->accessories[i], i);

	cman->any_controller = ctrl_new(dev, NULL, ANY_SLOT);

	for (u8 i = 0; i < N_HANDLERS; i++)
		cman->input_handlers[i] = ll_new();

	return cman;
}



static inline void flags_changed(struct controller_manager *cman, u16 ctrl_from, u16 ctrl_to, u16 acc_from, u16 acc_to)
{
	u8 ctrl_changed = ctrl_from != ctrl_to;
	u8 acc_changed = acc_from != acc_to;

	for (u8 i = 0; i < N_SLOTS; i++)
	{
		struct controller *ctrl = cman->controllers[i];

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

static inline void update_flags(struct controller_manager *cman)
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



static inline void add_handler(struct controller_manager *cman, u8 i_slot, struct input_handler *handler)
{
	ll_add_last(cman->input_handlers[i_slot], (void *)handler);
}

static inline void remove_handler(struct controller_manager *cman, u8 i_slot, struct input_handler *handler)
{
	ll_remove(cman->input_handlers[i_slot], (void *)handler);
	free(handler);
}


static void invoke_handlers(struct controller_manager *cman, struct input_handler *handler, struct controller *ctrl)
{
	while (handler != NULL)
	{
		if (!handler->is_disposed)
			handler->handle(ctrl, handler->context);

		struct input_handler *next = (void *)handler->node.next;

		if (handler->is_disposed)
			remove_handler(cman, handler->ctrl->i_slot, handler);

		handler = next;
	}
}

static inline void cman_handle_input(struct controller_manager *cman)
{
	for (u8 slot = 0; slot < N_SLOTS; slot++)
	{
		struct controller *ctrl = cman->controllers[slot];

		if (ctrl->status != CTRL_STATUS_READY)
			continue;

		struct linked_list **input_handlers = cman->input_handlers;

		invoke_handlers(cman, (void *)input_handlers[slot]->head, ctrl);
		invoke_handlers(cman, (void *)input_handlers[ANY_SLOT]->head, ctrl);
	}
}


static void update(const struct go_delegate *base, struct game_object *go)
{
	struct controller_manager *cman = (void *)go;

	update_flags(cman);

	cman_handle_input(cman);
}



struct input_handler *cman_add_handler(struct controller_manager *cman, struct controller *ctrl, void *context, handle_input handle)
{
	struct input_handler *handler = ih_new(ctrl, context, handle);

	add_handler(cman, ctrl->i_slot, handler);

	return handler;
}

void cman_rem_handler(struct controller_manager *cman, struct input_handler *handler)
{
	handler->is_disposed = 1;
}
