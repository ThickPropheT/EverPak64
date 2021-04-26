#include "acc_menu_presenter.h"

static void accmp_update(const struct go_delegate* base, struct game_object* go);
const struct go_delegate ACCMP_UPDATE[] = { { accmp_update, MP_UPDATE } };

const struct go_type ACCMP_TYPE[] = { { ACCMP_UPDATE, MP_DRAW } };

struct acc_menu_presenter* accmp_new(struct game_menu* gm)
{
	struct acc_menu_presenter* accmp = malloc(sizeof * accmp);

	_mp_init(&accmp->mp, ACCMP_TYPE, gm);

	return accmp;
}

static void accmp_update(const struct go_delegate* base, struct game_object* go)
{
	_god_invoke(base, go);
}