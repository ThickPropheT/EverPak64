#pragma once

#include "game_menu.h"
#include "menu_nav_controller.h"
#include "rumble_pak.h"
#include "types.h"

extern const struct go_type RPKM_TYPE[];

struct rpk_menu
{
	struct game_menu gm;

	struct rumble_pak* rpk;

	u8 rumble;
};

struct rpk_menu* rpkm_new(struct device_state* dev, struct menu_nav_controller* mnav, struct rumble_pak* rpk);

static inline struct rpk_menu* acc_to_rpkm(struct device_state* dev, struct menu_nav_controller* mnav, struct accessory* acc)
{
	return rpkm_new(dev, mnav, (void*)acc);
}
