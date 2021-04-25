#include "menu_presenter.h"

#include <malloc.h>

struct menu_presenter* mp_new(struct game_menu* gm)
{
	struct menu_presenter* mp = malloc(sizeof * mp);

	mp->gm = gm;

	return mp;
}

void mp_free(struct menu_presenter* mp)
{
	free(mp->gm);
	free(mp);
}
