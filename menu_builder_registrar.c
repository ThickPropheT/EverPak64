#include "menu_builder_registrar.h"

#include "main_menu_builder.h"
#include "acc_menu_builder.h"

#include "acc_menu_presenter.h"

#include "no_accessory_menu.h"
#include "mpk_menu.h"
#include "rpk_menu.h"



void mbreg_register(struct menu_builder_table *mbt, struct device_state *dev, struct controller_manager *cman, struct menu_nav_controller *mnav)
{
	mbt->main_builder = (void *)mmb_new(dev, cman, mnav);

	build_presenter_delegate build_acc = (void *)&accmp_new;

	mbt->acc_builders[ACCESSORY_NONE] = (void *)accmb_new(dev, cman, mnav, mbt, (build_menu_delegate)&nam_new, build_acc);
	mbt->acc_builders[ACCESSORY_MEMPAK] = (void *)accmb_new(dev, cman, mnav, mbt, (build_menu_delegate)&mpkm_new, build_acc);
	mbt->acc_builders[ACCESSORY_RUMBLEPAK] = (void *)accmb_new(dev, cman, mnav, mbt, (build_menu_delegate)&rpkm_new, build_acc);
}
