#pragma once

#include "game_menu.h"

struct menu_presenter
{
	struct game_menu* gm;
};

struct menu_presenter* mp_new(struct game_menu* gm);
void mp_free(struct menu_presenter* mp);
