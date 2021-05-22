#pragma once

#include "game_menu.h"
#include "menu_builder_table.h"
#include "types.h"
#include "accessory.h"

struct game_menu* gmres_acc(struct menu_builder_table* mbt, struct device_state* dev, u8 i_slot);
