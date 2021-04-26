#pragma once

#include "game_menu.h"

struct mb_args
{

};

struct menu_builder
{
	struct game_menu* (*build)(struct menu_builder* mb, struct mb_args* args);
};

static inline struct game_menu* mb_build(struct menu_builder* mb, struct mb_args* args)
{
	return mb->build(mb, args);
}
