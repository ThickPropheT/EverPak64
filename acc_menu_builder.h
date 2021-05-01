#pragma once

#include "game_menu.h"
#include "menu_presenter.h"
#include "types.h"
#include "menu_builder.h"
#include "device_state.h"
#include "menu_nav_controller.h"
#include "menu_builder_table.h"

typedef struct game_menu* (*build_menu_delegate)(struct device_state* dev, struct menu_nav_controller* mnav, struct accessory* acc);
typedef struct menu_presenter* (*build_presenter_delegate)(struct game_menu* menu, struct menu_builder_table* mbt, struct device_state* dev, u8 i_slot);

struct acc_menu_builder
{
	struct menu_builder mb;

	struct device_state* dev;
	struct menu_nav_controller* mnav;
	struct menu_builder_table* mbt;

	build_menu_delegate on_build_menu;
	build_presenter_delegate on_build_presenter;
};

struct acc_menu_builder* accmb_new(struct device_state* dev, struct menu_nav_controller* mnav, struct menu_builder_table* mbt, build_menu_delegate on_build_menu, build_presenter_delegate on_build_presenter);
