#include "controller_manager.h"

#include <malloc.h>
#include <libdragon.h>
#include "console.h"

#define ANY_SLOT -1

struct controller_manager* cman_new(struct device_state* dev)
{
	struct controller_manager* cman = malloc(sizeof * cman);

	cman->dev = dev;

	for (u8 i = 0; i < N_SLOTS; i++)
		cman->controllers[i] = ctrl_new(dev, dev->accessories[i], i);

	cman->any_controller = ctrl_new(dev, NULL, ANY_SLOT);

	return cman;
}

static void update_controllers(struct controller_manager* cman, u16 ctrl_from, u16 ctrl_to, u16 acc_from, u16 acc_to)
{
	u8 ctrl_changed = ctrl_from != ctrl_to;
	u8 acc_changed = acc_from != acc_to;

	for (u8 i = 0; i < N_SLOTS; i++)
	{
		struct controller* ctrl = cman->controllers[i];

		u16 flag = get_flag(ctrl->i_slot);

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

void cman_update(struct controller_manager* cman)
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

	update_controllers(cman, cman->ctrl_flags, ctrl_f, cman->acc_flags, acc_f);

	cman->ctrl_flags = ctrl_f;
	cman->acc_flags = acc_f;
}
