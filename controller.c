#include "controller.h"

struct controller *ctrl_new(struct device_state *dev, struct accessory *acc, u8 i_slot)
{
	struct controller *ctrl = malloc(sizeof * ctrl);

	ctrl->i_slot = i_slot;

	ctrl->dev = dev;
	ctrl->acc = acc;

	ctrl->status = CTRL_STATUS_MISSING;

	return ctrl;
}

static inline u8 has_key(struct controller *ctrl, sel_button_func select_button, struct controller_data keys)
{
	return select_button(keys.c[ctrl->i_slot]);
}

u8 ctrl_key_down(struct controller *ctrl, sel_button_func select_button)
{
	return has_key(ctrl, select_button, ctrl->dev->keys_d);
}

u8 ctrl_key_held(struct controller *ctrl, sel_button_func select_button)
{
	return has_key(ctrl, select_button, ctrl->dev->keys_h);
}

u8 ctrl_key_up(struct controller *ctrl, sel_button_func select_button)
{
	return has_key(ctrl, select_button, ctrl->dev->keys_u);
}
