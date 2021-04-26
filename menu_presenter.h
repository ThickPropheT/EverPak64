#pragma once

#include "game_menu.h"

extern const struct go_type MPO_TYPE[];

struct menu_presenter
{
	struct game_object go;
	const struct mp_type* mp_type;

	struct game_menu* gm;
};

struct mp_type
{
	void (*entering)(struct menu_presenter* mp);
	void (*leaving)(struct menu_presenter* mp);
};



struct menu_presenter* mp_new(struct game_menu* gm);

void _mp_init(struct menu_presenter* mp, const struct go_type* vtable, struct game_menu* gm);



static inline void mp_entering(struct menu_presenter* mp)
{
	void (*entering)(struct menu_presenter*) = mp->mp_type->entering;

	if (entering == NULL)
		return;

	entering(mp);
}


static inline void mp_leaving(struct menu_presenter* mp)
{
	void (*leaving)(struct menu_presenter*) = mp->mp_type->leaving;

	if (leaving == NULL)
		return;

	leaving(mp);
}



void mp_free(struct menu_presenter* mp);
