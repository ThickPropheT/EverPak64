#pragma once

#include "menu_presenter.h"

struct mb_args
{

};

struct menu_builder
{
	struct menu_presenter* (*build)(struct menu_builder* mb, struct mb_args* args);
};

static inline struct menu_presenter* mb_build(struct menu_builder* mb, struct mb_args* args)
{
	return mb->build(mb, args);
}
