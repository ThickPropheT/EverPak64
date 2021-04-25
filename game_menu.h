#pragma once

#include "game_object.h"
#include "accessory.h"
#include "device_state.h"

struct game_menu
{
	// TODO should this be const?
	struct game_object go;
	const struct gm_type* gm_type;

	struct device_state* dev;

	size_t i_hovered_item;
	size_t n_items;
};

struct gm_type
{
	void (*entering)(void);
	void (*leaving)(void);
};

void _gm_init(struct game_menu* gm, const struct go_type* vtable, struct device_state* dev, size_t n_items);

static inline void gm_entering(struct game_menu* gm)
{
	void (*entering)(void) = gm->gm_type->entering;

	if (entering == NULL)
		return;

	entering();
}

void _gm_hover_prev(struct game_menu* gm);
void _gm_hover_next(struct game_menu* gm);

void _gm_draw_header(struct accessory acc);

static inline void gm_leaving(struct game_menu* gm)
{
	void(*leaving)(void) = gm->gm_type->leaving;

	if (leaving == NULL)
		return;

	leaving();
}
