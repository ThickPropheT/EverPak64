#pragma once

#include "menu_presenter.h"

struct mb_args
{

};

struct menu_builder
{
	const struct mb_type* mb_type;
};

typedef void* (*build_func)(struct menu_builder* mb, struct mb_args* args);

struct mb_type
{
	build_func build_menu;
	build_func build_presenter;
};

static inline struct game_menu* mb_build_menu(struct menu_builder* mb, struct mb_args* args)
{
	return mb->mb_type->build_menu(mb, args);
}

static inline struct menu_presenter* mb_build_presenter(struct menu_builder* mb, struct mb_args* args)
{
		return mb->mb_type->build_presenter(mb, args);
}
