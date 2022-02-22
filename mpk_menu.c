#include "mpk_menu.h"

#include "menu_nav_controller.h"
#include "console.h"
#include "keys.h"


static void mpkm_activating(const struct go_delegate *base, struct game_object *go);
const struct go_delegate MPKM_ACTIVATING[] = { { mpkm_activating } };

static void mpkm_draw(const struct go_delegate *base, struct game_object *go);
const struct go_delegate MPKM_DRAW[] = { { mpkm_draw } };

static void mpkm_deactivating(const struct go_delegate *base, struct game_object *go);
const struct go_delegate MPKM_DEACTIVATING[] = { { mpkm_deactivating } };

const struct go_type MPKM_TYPE[] = { { MPKM_ACTIVATING, NULL, MPKM_DRAW, MPKM_DEACTIVATING } };


struct mpk_menu *mpkm_new(struct device_state *dev, struct controller_manager *cman, struct menu_nav_controller *mnav, struct controller *ctrl)
{
	struct mpk_menu *mpkm = malloc(sizeof * mpkm);

	_gm_init(&mpkm->gm, MPKM_TYPE, dev, cman, mnav, 0);

	mpkm->ctrl = ctrl;
	mpkm->mpk = (void *)ctrl->acc;

	return mpkm;
}



static void mpkm_handle_input(struct controller *ctrl, void *context)
{
	struct mpk_menu *mpkm = context;

	// for safety
	if (ctrl_key_down(ctrl, &key_L)
		&& ctrl_key_down(ctrl, &key_Z)
		&& ctrl_key_down(ctrl, &key_R))
	{
		mpk_format(mpkm->mpk);
	}

	_gm_handle_input(ctrl, (void *)mpkm);
}


static void mpkm_activating(const struct go_delegate *base, struct game_object *go)
{
	struct mpk_menu *menu = (void *)go;
	struct controller_manager *cman = menu->gm.cman;

	menu->input_handler =
		cman_add_handler(cman, cman->any_controller, menu, &mpkm_handle_input);
}

static void draw_header(struct accessory acc)
{
	_gm_draw_header(acc);

	cprintf("Format (L) + (R) + (Z)");
}

static s8 get_status(struct device_state dev, struct accessory acc)
{
	u16 f_slot = get_flag(acc.i_slot);

	// TODO move this check to mpk_update and cache in acc.status field
	if (!(dev.acc_flags & f_slot))
		return MPAK_STATUS_MISSING;

	return acc.status;
}

static void draw_error(s8 err)
{
	switch (err)
	{
	case MPAK_STATUS_MISSING:
		cprintf("Memory Pak missing.");
		break;

	case MPAK_STATUS_UNREADABLE:
		cprintf("Memory Pak missing or unreadable.");
		break;

	case MPAK_STATUS_UNFORMATTED:
		cprintf("Memory Pak unformatted.");
		break;
	}
}

static void draw_entries(struct memory_pak mpk)
{
	for (u8 i = 0; i < ENTRIES_LEN; i++)
	{
		entry_structure_t es = mpk.entries[i];

		// TODO wrap entry_structure_t to cache this err state
		//s8 err = get_mempak_entry(sm.i_slot, i, &es);
		s8 err = 0;

		// TODO tidy up this shite
		switch (err)
		{
		case 0:
			cprintf("%2i %s", i + 1, es.name);
			break;

		case -1:
			// entry out of bounds or entry_data is null
			cprintf("-1");
			break;

		case -2:
			// mempak is bad or not present
			cprintf("-2");
			break;
		}
	}
}

static void mpkm_draw(const struct go_delegate *base, struct game_object *go)
{
	struct mpk_menu *mpkm = (void *)go;

	struct memory_pak *mpk = mpkm->mpk;
	struct accessory acc = mpk->acc;

	draw_header(acc);

	s8 status = get_status(*mpkm->gm.dev, acc);

	if (status)
	{
		draw_error(status);
		return;
	}

	draw_entries(*mpk);
}



static void mpkm_deactivating(const struct go_delegate *base, struct game_object *go)
{
	struct mpk_menu *menu = (void *)go;

	cman_rem_handler(menu->gm.cman, menu->input_handler);
}
