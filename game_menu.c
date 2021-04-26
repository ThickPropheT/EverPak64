#include "game_menu.h"

#include "math.h"
#include "console.h"


const struct go_type GMO_TYPE[] = { { NULL, NULL } };
const struct gm_type GM_TYPE[] = { { NULL, NULL } };


void _gm_init(struct game_menu* gm, const struct go_type* vtable, struct device_state* dev, size_t n_items)
{
	_go_init(&gm->go, vtable, GMO_TYPE);

	gm->go.can_update = 1;
	gm->go.can_draw = 1;

	gm->gm_type = GM_TYPE;

	gm->dev = dev;

	gm->i_hovered_item = 0;
	gm->n_items = n_items;
}

void _gm_hover_prev(struct game_menu* gm)
{
	gm->i_hovered_item = cmod(gm->i_hovered_item - 1, gm->n_items);
}

void _gm_hover_next(struct game_menu* gm)
{
	gm->i_hovered_item = cmod(gm->i_hovered_item + 1, gm->n_items);
}

void _gm_draw_header(struct accessory acc)
{
	u8 sn = acc.i_slot + 1;
	char* acc_name = accessory_names[acc.type];

	cprintf("Controller %u [%s]", sn, acc_name);
	cprintf("Back (B)");
}
