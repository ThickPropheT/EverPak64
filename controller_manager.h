#pragma once

#include "controller.h"
#include "device_state.h"
#include "types.h"
#include "linked_list.h"


#define N_HANDLERS	N_SLOTS + 1


typedef void (*handle_input)(struct controller* ctrl, void* context);

struct input_handler
{
	struct ll_node node;

	u8 is_disposed;

	struct controller* ctrl;
	void* context;

	handle_input handle;
};

struct controller_manager
{
	struct device_state* dev;

	u16 ctrl_flags;
	u16 acc_flags;

	struct controller* controllers[N_SLOTS];
	struct controller* any_controller;

	struct linked_list* input_handlers[N_HANDLERS];

};

struct controller_manager* cman_new(struct device_state* dev);

void cman_update(struct controller_manager* cman);

struct input_handler* cman_add_handler(struct controller_manager* cman, struct controller* ctrl, void* context, handle_input handle);
void cman_rem_handler(struct controller_manager* cman, struct input_handler* handler);
