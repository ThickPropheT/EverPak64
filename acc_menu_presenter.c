#include "acc_menu_presenter.h"

#include "game_menu_resolver.h"

static void accmp_update(const struct go_delegate* base, struct game_object* go);
const struct go_delegate ACCMP_UPDATE[] = { { accmp_update, MP_UPDATE } };

const struct go_type ACCMP_TYPE[] = { { MP_ACTIVATING, ACCMP_UPDATE, MP_DRAW, MP_DEACTIVATING } };

struct acc_menu_presenter* accmp_new(struct game_menu* gm, struct menu_builder_table* mbt, struct device_state* dev, u8 i_slot)
{
	struct acc_menu_presenter* accmp = malloc(sizeof * accmp);

	_mp_init(&accmp->mp, ACCMP_TYPE, gm);

	accmp->mbt = mbt;
	accmp->dev = dev;

	accmp->i_slot = i_slot;

	accmp->acc_flags = dev->acc_flags;

	return accmp;
}

static void replace_menu(struct acc_menu_presenter* accmp)
{
	free(accmp->mp.gm);

	struct menu_builder_table* mbt = accmp->mbt;
	u8 slot = accmp->i_slot;

	accmp->mp.gm = gmres_acc(mbt, accmp->dev, slot);
}

static void accmp_update(const struct go_delegate* base, struct game_object* go)
{
	struct acc_menu_presenter* accmp = (void*)go;

	struct device_state* dev = accmp->dev;

	u16 flag = get_flag(accmp->i_slot);

	if (did_flag_change(flag, accmp->acc_flags, dev->acc_flags))
		replace_menu(accmp);

	accmp->acc_flags = dev->acc_flags;

	_god_invoke(base, go);
}