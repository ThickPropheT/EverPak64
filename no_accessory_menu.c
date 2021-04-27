#include "no_accessory_menu.h"

#include "rpk_menu.h"


static void nam_update(const struct go_delegate* base, struct game_object* go);
const struct go_delegate NAM_UPDATE[] = { { nam_update, GM_UPDATE } };

const struct go_type NAM_TYPE[] = { { NAM_UPDATE } };


struct no_accessory_menu* nam_new(struct device_state* dev)
{
	struct no_accessory_menu* menu = malloc(sizeof * menu);

	_gm_init(&menu->gm, NAM_TYPE, dev, 0);

	return menu;
}


static void nam_update(const struct go_delegate* base, struct game_object* go)
{
	_god_invoke(base, go);
}
