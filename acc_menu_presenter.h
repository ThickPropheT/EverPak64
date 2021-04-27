#pragma once

#include "menu_presenter.h"
#include "menu_builder_table.h"
#include "device_state.h"
#include "types.h"

struct acc_menu_presenter
{
	struct menu_presenter mp;

	struct menu_builder_table* mbt;
	struct device_state* dev;

	u8 i_slot;

	u16 acc_flags;
};

struct acc_menu_presenter* accmp_new(struct game_menu* gm, struct menu_builder_table* mbt, struct device_state* dev, u8 i_slot);
