#include "menu_presenter.h"

#include <malloc.h>

static void _mp_entering(struct menu_presenter* mp);
static void _mp_leaving(struct menu_presenter* mp);

const struct mp_type MP[] = { { _mp_entering, _mp_leaving } };

struct menu_presenter* mp_new(struct game_menu* gm)
{
	struct menu_presenter* mp = malloc(sizeof * mp);

	mp->mp_type = MP;

	mp->gm = gm;

	return mp;
}


static void _mp_entering(struct menu_presenter* mp)
{
	mp->gm->go.can_update = 1;
	mp->gm->go.can_draw = 1;

	gm_entering(mp->gm);
}

static void _mp_leaving(struct menu_presenter* mp)
{
	gm_leaving(mp->gm);

	mp->gm->go.can_update = 0;
	mp->gm->go.can_draw = 0;
}


void mp_free(struct menu_presenter* mp)
{
	free(mp->gm);
	free(mp);
}
