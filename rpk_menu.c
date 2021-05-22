#include "rpk_menu.h"

#include "menu_nav_controller.h"
#include "console.h"


static void rpkmn_update(const struct go_delegate* base, struct game_object* go);
const struct go_delegate RPKM_UPDATE[] = { { rpkmn_update, GM_UPDATE } };

static void rpkmn_draw(const struct go_delegate* base, struct game_object* go);
const struct go_delegate RPKM_DRAW[] = { { rpkmn_draw } };

static void rpkmn_deactivating(const struct go_delegate* base, struct game_object* go);
const struct go_delegate RPKM_DEACTIVATING[] = { { rpkmn_deactivating } };

const struct go_type RPKM_TYPE[] = { { NULL, RPKM_UPDATE, RPKM_DRAW, RPKM_DEACTIVATING } };


struct rpk_menu* rpkm_new(struct device_state* dev, struct menu_nav_controller* mnav, struct rumble_pak* rpk)
{
	struct rpk_menu* menu = malloc(sizeof * menu);

	_gm_init(&menu->gm, RPKM_TYPE, dev, mnav, 0);

	menu->rpk = rpk;

	menu->rumble = 0;

	return menu;
}

static void rpkmn_update(const struct go_delegate* base, struct game_object* go)
{
	struct rpk_menu* menu = (void*)go;

	struct device_state* dev = menu->gm.dev;

	struct controller_data keys_d = dev->keys_d;
	struct controller_data keys_h = dev->keys_h;

	struct accessory acc = menu->rpk->acc;

	if (keys_d.c[0].C_down)
	{
		menu->gm.go.can_update = 1;
	}

	if (menu->gm.go.can_update == 1)
	{
		if (keys_d.c[0].start)
		{
			if (menu->rumble)
			{
				rumble_stop(acc.i_slot);
				menu->rumble = 0;
			}
			else
			{
				rumble_start(acc.i_slot);
				menu->rumble = 1;
			}
		}
		else if (!menu->rumble)
		{
			if (keys_h.c[0].Z)
			{
				rumble_start(acc.i_slot);
			}
			else if (keys_d.c[0].C_up)
			{
				menu->gm.go.can_update = 2;
			}
			else
			{
				rumble_stop(acc.i_slot);
			}
		}
	}
	else if (menu->gm.go.can_update == 2)
	{
		rumble_start(acc.i_slot);
		menu->gm.go.can_update = 3;
	}
	else if (menu->gm.go.can_update == 3)
	{
		rumble_stop(acc.i_slot);
		menu->gm.go.can_update = 2;
	}

	_god_invoke(base, go);
}

static void rpkmn_draw(const struct go_delegate* base, struct game_object* go)
{
	struct rpk_menu* menu = (void*)go;
	struct accessory* acc = (void*)menu->rpk;

	_gm_draw_header(*acc);

	cprintf("Rumble (Z)");
}

static void rpkmn_deactivating(const struct go_delegate* base, struct game_object* go)
{
	struct rpk_menu* menu = (void*)go;
	struct accessory acc = menu->rpk->acc;

	rumble_stop(acc.i_slot);
}
