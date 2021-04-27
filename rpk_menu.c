#include "rpk_menu.h"

#include "console.h"


static void rpkmn_update(const struct go_delegate* base, struct game_object* go);
const struct go_delegate RPKM_UPDATE[] = { { rpkmn_update } };

static void rpkmn_draw(const struct go_delegate* base, struct game_object* go);
const struct go_delegate RPKM_DRAW[] = { { rpkmn_draw } };

const struct go_type RPKM_TYPE[] = { { RPKM_UPDATE, RPKM_DRAW } };


struct rpk_menu* rpkm_new(struct device_state* dev, struct rumble_pak* rpk)
{
	struct rpk_menu* rpkm = malloc(sizeof * rpkm);

	_gm_init(&rpkm->gm, RPKM_TYPE, dev, 0);

	rpkm->rpk = rpk;

	return rpkm;
}

static void rpkmn_update(const struct go_delegate* base, struct game_object* go)
{
	struct rpk_menu* menu = (void*)go;

	struct device_state* dev = menu->gm.dev;
	struct controller_data keys = dev->keys_d;

	if (keys.c[0].Z)
	{
		if (menu->rumble)
			rumble_stop(0);

		else
			rumble_start(0);

		menu->rumble = 1 - menu->rumble;
	}
}

static void rpkmn_draw(const struct go_delegate* base, struct game_object* go)
{
	struct rpk_menu* menu = (void*)go;
	struct accessory* acc = (void*)menu->rpk;

	_gm_draw_header(*acc);

	cprintf("Rumble (Z)");
}
