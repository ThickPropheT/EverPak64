#pragma once

#include <stdlib.h>
#include "types.h"

struct game_object
{
	const struct go_type *go_type;

	u8 can_update;
	u8 can_draw;
};

struct go_type
{
	const struct go_delegate *activating;
	const struct go_delegate *update;
	const struct go_delegate *draw;
	const struct go_delegate *deactivating;
};


typedef void (*go_func)(const struct go_delegate *base, struct game_object *go);

struct go_delegate
{
	go_func invoke;
	const struct go_delegate *base;
};

static inline void _god_invoke(const struct go_delegate *god, struct game_object *go)
{
	if (god == NULL)
		return;

	god->invoke(god->base, go);
}



static inline void _go_init(struct game_object *go, const struct go_type *vtable)
{
	go->go_type = vtable;
}

static inline void go_activating(struct game_object *go)
{
	_god_invoke(go->go_type->activating, go);
}

static inline void go_update(struct game_object *go)
{
	if (!go->can_update)
		return;

	_god_invoke(go->go_type->update, go);
}

static inline void go_draw(struct game_object *go)
{
	if (!go->can_draw)
		return;

	_god_invoke(go->go_type->draw, go);
}

static inline void go_deactivating(struct game_object *go)
{
	_god_invoke(go->go_type->deactivating, go);
}
