#pragma once

#include "game_menu.h"
#include "menu_builder_table.h"
#include "accessory.h"
#include "controller_manager.h"

struct menu_presenter *mpres_main(struct menu_builder_table *mbt);

struct menu_presenter *mpres_acc(struct menu_builder_table *mbt, struct controller_manager *cman, u8 i_slot);
