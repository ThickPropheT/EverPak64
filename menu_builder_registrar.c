#include "menu_builder_registrar.h"

#include <malloc.h>

#include "main_menu_builder.h"
#include "default_menu_builder.h"
#include "mpk_menu_builder.h"


void mbreg_register(struct menu_builder_table* mbt, struct device_state* dev, struct menu_nav_controller* mnav)
{
	mbt->main_builder = (struct menu_builder*)mmb_new(dev, mnav);
	mbt->default_builder = (struct menu_builder*)dmb_new(dev, mnav);
	mbt->acc_builders[ACCESSORY_MEMPAK] = (struct menu_builder*)mpkmb_new(dev, mnav);
}
