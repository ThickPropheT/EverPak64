#include "no_accessory_menu.h"

#include "console.h"
#include "memory_pak.h"


static void nam_draw(const struct go_delegate* base, struct game_object* go);
const struct go_delegate NAM_DRAW[] = { { nam_draw } };

const struct go_type NAM_TYPE[] = { { NULL, GM_UPDATE, NAM_DRAW } };


struct no_accessory_menu* nam_new(struct device_state* dev, struct menu_nav_controller* mnav, struct accessory* acc)
{
	struct no_accessory_menu* menu = malloc(sizeof * menu);

	_gm_init(&menu->gm, NAM_TYPE, dev, mnav, 0);

	menu->acc = acc;

	return menu;
}

static void nam_draw(const struct go_delegate* base, struct game_object* go)
{
	struct no_accessory_menu* menu = (void*)go;
	struct accessory* acc = menu->acc;

	_gm_draw_header(*acc);

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
