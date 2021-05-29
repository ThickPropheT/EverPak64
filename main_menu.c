#include "main_menu.h"

#include <stddef.h>
#include <malloc.h>
#include "console.h"
#include "controller.h"


static void mm_update(const struct go_delegate* base, struct game_object* go);
const struct go_delegate MM_UPDATE[] = { { mm_update } };

static void mm_draw(const struct go_delegate* base, struct game_object* go);
const struct go_delegate MM_DRAW[] = { { mm_draw } };

const struct go_type MM_TYPE[] = { { NULL, MM_UPDATE, MM_DRAW } };


struct main_menu* mm_new(struct device_state* dev, struct controller_manager* cman, struct menu_nav_controller* mnav)
{
	struct main_menu* mm = malloc(sizeof * mm);

	_gm_init(&mm->gm, MM_TYPE, dev, cman, mnav, N_SLOTS);

	return mm;
}

static void mm_update(const struct go_delegate* base, struct game_object* go)
{
	struct main_menu* mm = (void*)go;
	struct game_menu* gm = &mm->gm;

	struct controller_data keys = gm->dev->keys_d;

	if (keys.c[0].up)
	{
		_gm_hover_prev(gm);
	}
	else if (keys.c[0].down)
	{
		_gm_hover_next(gm);
	}
	else if (keys.c[0].left)
	{
		_gm_hover_prev(gm);
	}
	else if (keys.c[0].right)
	{
		_gm_hover_next(gm);
	}
	else if (keys.c[0].A)
	{
		mnav_to_sm(gm->mnav, gm->i_hovered_item);
	}
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
