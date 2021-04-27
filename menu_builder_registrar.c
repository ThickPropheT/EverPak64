#include "menu_builder_registrar.h"

#include <malloc.h>

#include "main_menu_builder.h"
#include "default_menu_builder.h"
#include "mpk_menu_builder.h"
#include "rpk_menu_builder.h"


void mbreg_register(struct menu_builder_table* mbt, struct device_state* dev, struct menu_nav_controller* mnav)
{
	mbt->main_builder = (void*)mmb_new(dev, mnav);
	mbt->default_builder = (void*)dmb_new(dev, mnav);
	mbt->acc_builders[ACCESSORY_MEMPAK] = (void*)mpkmb_new(dev, mnav, mbt);
	mbt->acc_builders[ACCESSORY_RUMBLEPAK] = (void*)rpkmb_new(dev, mnav, mbt);
}
