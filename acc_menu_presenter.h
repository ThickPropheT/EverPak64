#pragma once

#include "menu_presenter.h"
#include "menu_builder_table.h"
#include "device_state.h"
#include "controller_manager.h"
#include "types.h"

struct acc_menu_presenter
{
	struct menu_presenter mp;

	struct menu_builder_table* mbt;
	struct device_state* dev;
	struct controller_manager* cman;

	u8 i_slot;

	u16 acc_flags;
};

struct acc_menu_presenter* accmp_new(struct game_menu* gm, struct menu_builder_table* mbt, struct device_state* dev, struct controller_manager* cman, u8 i_slot);
