#pragma once

#include "menu_builder_table.h"
#include "device_state.h"
#include "menu_nav_controller.h"

void mbreg_register(struct menu_builder_table* mbt, struct device_state* dev, struct controller_manager* cman, struct menu_nav_controller* mnav);
