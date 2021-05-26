#include "controller.h"

#define ANY_SLOT 5


struct controller* any;


struct controller* ctrl_any(struct device_state* dev)
{
	if (any == NULL)
	{
		any = malloc(sizeof * any);

		any->dev = dev;
		any->acc = acc_new(ANY_SLOT);
	}

	return any;
}

struct controller* ctrl_new(struct device_state* dev, struct accessory* acc)
{
	struct controller* ctrl = malloc(sizeof * ctrl);

	ctrl->dev = dev;
	ctrl->acc = acc;

	return ctrl;
}

static u8 has_key(struct controller* ctrl, sel_button_func select_button, struct controller_data keys)
{
	u8 slot = ctrl->acc->i_slot;

	if (slot != ANY_SLOT)
		return select_button(keys.c[slot]);

	for (int i = 0; i < N_SLOTS; i++)
	{
		if (ctrl->dev->controllers & get_flag(i)
			&& select_button(keys.c[i]))
			return 1;
	}

	return 0;
}

u8 ctrl_key_down(struct controller* ctrl, sel_button_func select_button)
{
	return has_key(ctrl, select_button, ctrl->dev->keys_d);
}

u8 ctrl_key_held(struct controller* ctrl, sel_button_func select_button)
{
	return has_key(ctrl, select_button, ctrl->dev->keys_h);
}

u8 ctrl_key_up(struct controller* ctrl, sel_button_func select_button)
{
	return has_key(ctrl, select_button, ctrl->dev->keys_u);
}
