#pragma once

#include "game_object.h"
#include "accessory.h"
#include "device_state.h"
#include "menu_state.h"

struct game_menu
{
	// TODO should this be const?
	struct game_object go;

	struct device_state* dev;
	struct menu_state* ms;

	size_t i_hovered_item;
	size_t n_items;
};

void _gm_init(struct game_menu* gm, const struct _go_vtable* vtable, struct device_state* dev, struct menu_state* ms);

struct game_menu* gm_new(struct menu_state* ms, struct device_state* dev);

void _gm_hover_prev(struct game_menu* gm);
void _gm_hover_next(struct game_menu* gm);

void _gm_draw_header(struct accessory acc);