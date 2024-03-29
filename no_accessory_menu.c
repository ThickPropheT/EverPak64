#include "no_accessory_menu.h"

#include "console.h"
#include "memory_pak.h"


static void nam_activating(const struct go_delegate *base, struct game_object *go);
const struct go_delegate NAM_ACTIVATING[] = { { nam_activating } };

static void nam_draw(const struct go_delegate *base, struct game_object *go);
const struct go_delegate NAM_DRAW[] = { { nam_draw } };

static void nam_deactivating(const struct go_delegate *base, struct game_object *go);
const struct go_delegate NAM_DEACTIVATING[] = { { nam_deactivating } };

const struct go_type NAM_TYPE[] = { { NAM_ACTIVATING, NULL, NAM_DRAW, NAM_DEACTIVATING } };


struct no_accessory_menu *nam_new(struct device_state *dev, struct controller_manager *cman, struct menu_nav_controller *mnav, struct controller *ctrl)
{
	struct no_accessory_menu *menu = malloc(sizeof * menu);

	_gm_init(&menu->gm, NAM_TYPE, dev, cman, mnav, 0);

	menu->ctrl = ctrl;

	menu->input_handler = NULL;

	return menu;
}



static void nam_activating(const struct go_delegate *base, struct game_object *go)
{
	struct no_accessory_menu *menu = (void *)go;
	struct controller_manager *cman = menu->gm.cman;

	menu->input_handler =
		cman_add_handler(cman, cman->any_controller, menu, (handle_input)&_gm_handle_input);
}



static void nam_draw(const struct go_delegate *base, struct game_object *go)
{
	struct no_accessory_menu *menu = (void *)go;
	struct controller *ctrl = menu->ctrl;
	struct accessory *acc = ctrl->acc;

	_gm_draw_header(*acc);

	switch (ctrl->status)
	{
	case CTRL_STATUS_MISSING:
		cprintf("Controller missing.");
		return;

	default:
		break;
	}

	switch (acc->status)
	{
	case MPAK_STATUS_UNREADABLE:
		cprintf("Memory Pak missing or unreadable.");
		break;

	case MPAK_STATUS_UNFORMATTED:
		cprintf("Memory Pak unformatted.");
		break;

	default:
		cprintf("Memory Pak missing.");
		break;
	}
}



static void nam_deactivating(const struct go_delegate *base, struct game_object *go)
{
	struct no_accessory_menu *menu = (void *)go;

	cman_rem_handler(menu->gm.cman, menu->input_handler);
}
