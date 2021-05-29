#include "mpk_menu.h"

#include "menu_nav_controller.h"
#include "console.h"


static void mpkm_update(const struct go_delegate* base, struct game_object* go);
const struct go_delegate MPKM_UPDATE[] = { { mpkm_update, GM_UPDATE } };

static void mpkm_draw(const struct go_delegate* base, struct game_object* go);
const struct go_delegate MPKM_DRAW[] = { { mpkm_draw } };

const struct go_type MPKM_TYPE[] = { { NULL, MPKM_UPDATE, MPKM_DRAW } };


struct mpk_menu* mpkm_new(struct device_state* dev, struct controller_manager* cman, struct menu_nav_controller* mnav, struct controller* ctrl)
{
	struct mpk_menu* mpkm = malloc(sizeof * mpkm);

	_gm_init(&mpkm->gm, MPKM_TYPE, dev, cman, mnav, 0);

	mpkm->ctrl = ctrl;
	mpkm->mpk = (void*)ctrl->acc;

	return mpkm;
}


static void mpkm_update(const struct go_delegate* base, struct game_object* go)
{
	struct mpk_menu* mpkm = (void*)go;

	struct controller_data keys = mpkm->gm.dev->keys_d;

	// for safety
	if (keys.c[0].L
		&& keys.c[0].Z
		&& keys.c[0].R)
	{
		mpk_format(mpkm->mpk);
	}

	_god_invoke(base, go);
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

static void mpkm_draw(const struct go_delegate* base, struct game_object* go)
{
	struct mpk_menu* mpkm = (void*)go;

	struct memory_pak* mpk = mpkm->mpk;
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