#include "menu_presenter.h"

#include <malloc.h>


static void mp_update(const struct go_delegate* base, struct game_object* go);
const struct go_delegate MP_UPDATE[] = { { mp_update } };

static void mp_draw(const struct go_delegate* base, struct game_object* go);
const struct go_delegate MP_DRAW[] = { { mp_draw } };

const struct go_type MPO_TYPE[] = { { MP_UPDATE, MP_DRAW } };


static void _mp_entering(struct menu_presenter* mp);
static void _mp_leaving(struct menu_presenter* mp);

const struct mp_type MP[] = { { _mp_entering, _mp_leaving } };

struct menu_presenter* mp_new(struct game_menu* gm)
{
	struct menu_presenter* mp = malloc(sizeof * mp);

	mp->go.go_type = MPO_TYPE;
	mp->go.can_update = 1;
	mp->go.can_draw = 1;

	mp->mp_type = MP;

	mp->gm = gm;

	return mp;
}

void _mp_init(struct menu_presenter* mp, const struct go_type* vtable, struct game_menu* gm)
{
	_go_init(&mp->go, vtable);

	mp->gm = gm;
}


static void _mp_entering(struct menu_presenter* mp)
{
	mp->gm->go.can_update = 1;
	mp->gm->go.can_draw = 1;

	gm_entering(mp->gm);
}

static void mp_update(const struct go_delegate* base, struct game_object* go)
{
	struct menu_presenter* mp = (void*)go;

	go_update((struct game_object*)mp->gm);
}

static void mp_draw(const struct go_delegate* base, struct game_object* go)
{
	struct menu_presenter* mp = (void*)go;

	go_draw((struct game_object*)mp->gm);
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
