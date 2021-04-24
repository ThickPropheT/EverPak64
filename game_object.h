#pragma once

#include <stdlib.h>
#include "types.h"

struct game_object
{
	const struct go_type* type;
	const struct game_object* _base;

	u8 can_update;
	u8 can_draw;
};

struct go_type
{
	void (*update)(struct game_object* go);
	void (*draw)(struct game_object* go);
};

static inline struct game_object* go_new(const struct go_type* vtable)
{
	struct game_object* go = malloc(sizeof * go);
	go->type = vtable;
	return go;
}

static inline void _go_init(struct game_object* go, const struct go_type* vtable, const struct go_type* base_vtable)
{
	go->type = vtable;
	go->_base = go_new(base_vtable);
}

static inline void go_update(struct game_object* go)
{
	if (!go->can_update)
		return;

	go->type->update(go);
}

static inline void go_draw(struct game_object* go)
{
	if (!go->can_draw)
		return;

	go->type->draw(go);
}