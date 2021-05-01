#include "menu_builder_registrar.h"

#include <malloc.h>

#include "main_menu_builder.h"
#include "default_menu_builder.h"
#include "acc_menu_builder.h"

#include "acc_menu_presenter.h"

#include "no_accessory_menu.h"
#include "mpk_menu.h"
#include "rpk_menu.h"



void mbreg_register(struct menu_builder_table* mbt, struct device_state* dev, struct menu_nav_controller* mnav)
{
	mbt->main_builder = (void*)mmb_new(dev, mnav);
	mbt->default_builder = (void*)dmb_new(dev, mnav);

	build_presenter_delegate build_acc = (void*)&accmp_new;

	mbt->acc_builders[ACCESSORY_NONE] = (void*)accmb_new(dev, mnav, mbt, (build_menu_delegate)&nam_from_acc, build_acc);
	mbt->acc_builders[ACCESSORY_MEMPAK] = (void*)accmb_new(dev, mnav, mbt, (build_menu_delegate)&mpkm_from_acc, build_acc);
	mbt->acc_builders[ACCESSORY_RUMBLEPAK] = (void*)accmb_new(dev, mnav, mbt, (build_menu_delegate)&acc_to_rpkm, build_acc);
}
