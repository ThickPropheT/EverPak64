#include "game_menu.h"

#include "math.h"
#include "console.h"


static void gm_update(struct game_object* go);

const struct go_type GM_O[] = { { gm_update } };
const struct gm_type GM[] = { { NULL, NULL } };


void _gm_init(struct game_menu* gm, const struct go_type* vtable, struct device_state* dev, size_t n_items)
{
	_go_init(&gm->go, vtable, GM_O);

	gm->go.can_update = 1;
	gm->go.can_draw = 1;

	gm->gm_type = GM;

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


static void gm_update(struct game_object* go)
{

}
