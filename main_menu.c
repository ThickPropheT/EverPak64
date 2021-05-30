#include "main_menu.h"

#include <stddef.h>
#include <malloc.h>
#include "console.h"
#include "controller.h"
#include "keys.h"


static void mm_activating(const struct go_delegate* base, struct game_object* go);
const struct go_delegate MM_ACTIVATING[] = { { mm_activating } };

static void mm_draw(const struct go_delegate* base, struct game_object* go);
const struct go_delegate MM_DRAW[] = { { mm_draw } };

static void mm_deactivating(const struct go_delegate* base, struct game_object* go);
const struct go_delegate MM_DEACTIVATING[] = { { mm_deactivating } };

const struct go_type MM_TYPE[] = { { MM_ACTIVATING, NULL, MM_DRAW, MM_DEACTIVATING } };


struct main_menu* mm_new(struct device_state* dev, struct controller_manager* cman, struct menu_nav_controller* mnav)
{
	struct main_menu* mm = malloc(sizeof * mm);

	_gm_init(&mm->gm, MM_TYPE, dev, cman, mnav, N_SLOTS);

	return mm;
}



static void mm_handle_input(struct controller* ctrl, void* context)
{
	struct game_menu* gm = (void*)context;

	if (ctrl_key_down(ctrl, &key_up))
	{
		_gm_hover_prev(gm);
	}
	else if (ctrl_key_down(ctrl, &key_down))
	{
		_gm_hover_next(gm);
	}
	else if (ctrl_key_down(ctrl, &key_left))
	{
		_gm_hover_prev(gm);
	}
	else if (ctrl_key_down(ctrl, &key_right))
	{
		_gm_hover_next(gm);
	}
	else if (ctrl_key_down(ctrl, &key_A))
	{
		mnav_to_sm(gm->mnav, gm->i_hovered_item);
	}
}

static void mm_activating(const struct go_delegate* base, struct game_object* go)
{
	struct main_menu* menu = (void*)go;
	struct controller_manager* cman = menu->gm.cman;

	menu->input_handler =
		cman_add_handler(cman, cman->any_controller, menu, &mm_handle_input);
}


static void mm_draw(const struct go_delegate* base, struct game_object* go)
{
	struct main_menu* mm = (void*)go;
	struct controller_manager* cman = mm->gm.cman;

	cprintf("Select Controller (A)\n\n");

	for (u8 i = 0; i < N_SLOTS; i++)
	{
		struct controller* ctrl = cman->controllers[i];

		u8 sn = i + 1;

		char* sel =
			i == mm->gm.i_hovered_item
			? ">"
			: " ";

		char* pres =
			ctrl->status == CTRL_STATUS_READY
			? "+"
			: " ";

		cprintf("%s [%s] Slot %u\n", sel, pres, sn);
	}
}


static void mm_deactivating(const struct go_delegate* base, struct game_object* go)
{
	struct main_menu* menu = (void*)go;

	cman_rem_handler(menu->gm.cman, menu->input_handler);
}
