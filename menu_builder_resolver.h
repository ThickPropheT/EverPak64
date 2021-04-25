#pragma once

#include "game_menu.h"
#include "menu_builder_table.h"
#include "accessory.h"
#include "device_state.h"

struct game_menu* mbres_build_default(struct menu_builder_table* mbt, u8 i_slot);

struct game_menu* mbres_build_acc(struct menu_builder* mb, struct accessory* acc);

struct game_menu* mbres_try_build_acc(struct menu_builder_table* mbt, struct device_state* dev, u8 i_slot);
