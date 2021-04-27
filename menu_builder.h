#pragma once

#include "menu_presenter.h"

struct mb_args
{

};

struct menu_builder
{
	struct game_menu* (*build_menu)(struct menu_builder* mb, struct mb_args* args);
	struct menu_presenter* (*build_presenter)(struct menu_builder* mb, struct mb_args* args);
};

static inline struct game_menu* mb_build_menu(struct menu_builder* mb, struct mb_args* args)
{
	return mb->build_menu(mb, args);
}

static inline struct menu_presenter* mb_build_presenter(struct menu_builder* mb, struct mb_args* args)
{
	return mb->build_presenter(mb, args);
}
