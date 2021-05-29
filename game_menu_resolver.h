#pragma once

#include "game_menu.h"
#include "menu_builder_table.h"
#include "controller_manager.h"
#include "types.h"

struct game_menu* gmres_acc(struct menu_builder_table* mbt, struct controller_manager* cman, u8 i_slot);
