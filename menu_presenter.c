#include "menu_presenter.h"

#include <malloc.h>
#include "console.h"


static void mp_entering(const struct go_delegate *base, struct game_object *go);
const struct go_delegate MP_ACTIVATING[] = { { mp_entering } };

static void mp_update(const struct go_delegate *base, struct game_object *go);
const struct go_delegate MP_UPDATE[] = { { mp_update } };

static void mp_draw(const struct go_delegate *base, struct game_object *go);
const struct go_delegate MP_DRAW[] = { { mp_draw } };

static void mp_leaving(const struct go_delegate *base, struct game_object *go);
const struct go_delegate MP_DEACTIVATING[] = { { mp_leaving } };


const struct go_type MPO_TYPE[] = { { MP_ACTIVATING, MP_UPDATE, MP_DRAW, MP_DEACTIVATING } };



struct menu_presenter *mp_new(struct game_menu *gm)
{
	struct menu_presenter *mp = malloc(sizeof * mp);

	_go_init(&mp->go, MPO_TYPE);

	mp->go.can_update = 1;
	mp->go.can_draw = 1;

	mp->gm = gm;

	return mp;
}

void _mp_init(struct menu_presenter *mp, const struct go_type *vtable, struct game_menu *gm)
{
	_go_init(&mp->go, vtable);

	mp->go.can_update = 1;
	mp->go.can_draw = 1;

	mp->gm = gm;
}


static void mp_entering(const struct go_delegate *base, struct game_object *go)
{
	struct menu_presenter *mp = (void *)go;

	mp->gm->go.can_update = 1;
	mp->gm->go.can_draw = 1;

	go_activating((void *)mp->gm);
}

static void mp_update(const struct go_delegate *base, struct game_object *go)
{
	struct menu_presenter *mp = (void *)go;

	go_update((void *)mp->gm);
}

static void mp_draw(const struct go_delegate *base, struct game_object *go)
{
	struct menu_presenter *mp = (void *)go;

	go_draw((void *)mp->gm);
}

static void mp_leaving(const struct go_delegate *base, struct game_object *go)
{
	struct menu_presenter *mp = (void *)go;

	go_deactivating((void *)mp->gm);

	mp->gm->go.can_update = 0;
	mp->gm->go.can_draw = 0;
}


void mp_free(struct menu_presenter *mp)
{
	free(mp->gm);
	free(mp);
}
