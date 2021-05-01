#pragma once

#include "game_menu.h"
#include "device_state.h"
#include "menu_nav_controller.h"

extern const struct go_type NAM_TYPE[];

struct no_accessory_menu
{
	struct game_menu gm;

	struct accessory* acc;
};

struct no_accessory_menu* nam_new(struct device_state* dev, struct menu_nav_controller* mnav, struct accessory* acc);

static inline struct game_menu* nam_from_acc(struct device_state* dev, struct menu_nav_controller* mnav, struct accessory* acc)
{
	return (void*)nam_new(dev, mnav, acc);
}
