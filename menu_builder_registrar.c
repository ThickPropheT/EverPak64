#include "menu_builder_registrar.h"

#include "default_menu_builder.h"
#include "mpk_menu_builder.h"

void mbreg_register(struct menu_builder_table* mbt, struct device_state* dev, struct menu_nav_controller* mnav) 
{
	mbt->default_builder = (struct menu_builder*)dmb_new(dev, mnav);
	mbt->mpkm_builder = (struct menu_builder*)mpkmb_new(dev, mnav);
}
