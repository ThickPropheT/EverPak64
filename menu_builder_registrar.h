#pragma once

#include "menu_builder_table.h"
#include "device_state.h"
#include "menu_nav_controller.h"

void mbr_register(struct menu_builder_table* mbt, struct device_state* dev, struct menu_nav_controller* mnav);