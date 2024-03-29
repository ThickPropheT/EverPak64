#include "acc_menu_presenter.h"

#include "game_menu_resolver.h"

static void accmp_update(const struct go_delegate *base, struct game_object *go);
const struct go_delegate ACCMP_UPDATE[] = { { accmp_update, MP_UPDATE } };

const struct go_type ACCMP_TYPE[] = { { MP_ACTIVATING, ACCMP_UPDATE, MP_DRAW, MP_DEACTIVATING } };

struct acc_menu_presenter *accmp_new(struct game_menu *gm, struct menu_builder_table *mbt, struct device_state *dev, struct controller_manager *cman, u8 i_slot)
{
	struct acc_menu_presenter *accmp = malloc(sizeof * accmp);

	_mp_init(&accmp->mp, ACCMP_TYPE, gm);

	accmp->mbt = mbt;
	accmp->dev = dev;
	accmp->cman = cman;

	accmp->i_slot = i_slot;

	accmp->acc_flags = dev->acc_flags;

	return accmp;
}

static void replace_menu(struct acc_menu_presenter *accmp)
{
	go_deactivating((void *)accmp->mp.gm);

	free(accmp->mp.gm);

	accmp->mp.gm = gmres_acc(accmp->mbt, accmp->cman, accmp->i_slot);

	go_activating((void *)accmp->mp.gm);
}

static void accmp_update(const struct go_delegate *base, struct game_object *go)
{
	struct acc_menu_presenter *accmp = (void *)go;

	struct device_state *dev = accmp->dev;

	u16 flag = get_flag(accmp->i_slot);

	if (did_flag_change(flag, accmp->acc_flags, dev->acc_flags))
		replace_menu(accmp);

	accmp->acc_flags = dev->acc_flags;

	_god_invoke(base, go);
}