#include "menu_builder_registrar.h"

#include "default_menu_builder.h"

void mbr_register(struct menu_builder_table* mbt, struct device_state* dev, struct menu_nav_controller* mnav) 
{
	mbt->default_builder = (struct menu_builder*)dmb_new(dev, mnav);
}