#pragma once

#include "game_object.h"
#include "accessory.h"
#include "device_state.h"
#include "controller_manager.h"
#include "menu_nav_controller.h"
#include "controller.h"


extern const struct go_delegate GM_UPDATE[];

struct game_menu
{
	struct game_object go;

	struct device_state *dev;
	struct controller_manager *cman;
	struct menu_nav_controller *mnav;

	size_t i_hovered_item;
	size_t n_items;
};

void _gm_init(struct game_menu *gm, const struct go_type *vtable, struct device_state *dev, struct controller_manager *cman, struct menu_nav_controller *mnav, size_t n_items);

void _gm_hover_prev(struct game_menu *gm);
void _gm_hover_next(struct game_menu *gm);

void _gm_handle_input(struct controller *ctrl, struct game_menu *menu);

void _gm_draw_header(struct accessory acc);
