#pragma once

#include "device_state.h"
#include "controller_manager.h"
#include "menu_nav_controller.h"


struct menu_tree
{
	struct device_state* dev;
	struct controller_manager* cman;
	struct menu_nav_controller* mnav;
};


struct menu_tree mt_new(struct device_state* dev, struct controller_manager* cman);

void mt_update(struct menu_tree* mt);
void mt_draw(struct menu_tree* mt);
