#pragma once

#include "menu_presenter.h"

struct acc_menu_presenter
{
	struct menu_presenter mp;
};

struct acc_menu_presenter* accmp_new(struct game_menu* gm);
