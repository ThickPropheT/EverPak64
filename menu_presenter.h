#pragma once

#include "game_menu.h"

extern const struct go_delegate MP_ACTIVATING[];
extern const struct go_delegate MP_UPDATE[];
extern const struct go_delegate MP_DRAW[];
extern const struct go_delegate MP_DEACTIVATING[];

extern const struct go_type MPO_TYPE[];

struct menu_presenter
{
	struct game_object go;

	struct game_menu* gm;
};


struct menu_presenter* mp_new(struct game_menu* gm);

void _mp_init(struct menu_presenter* mp, const struct go_type* vtable, struct game_menu* gm);

void mp_free(struct menu_presenter* mp);
