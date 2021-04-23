#pragma once

#include <stdlib.h>
#include "types.h"

struct game_object
{
	const struct _go_vtable* _vtable;
	const struct game_object* _base;

	u8 can_update;
	u8 can_draw;
};

struct _go_vtable
{
	void (*update)(struct game_object* go);
	void (*draw)(struct game_object* go);
};

static inline struct game_object* go_new(const struct _go_vtable* vtable)
{
	struct game_object* go = malloc(sizeof * go);
	go->_vtable = vtable;
	return go;
}

static inline void _go_init(struct game_object* go, const struct _go_vtable* vtable, const struct _go_vtable* base_vtable)
{
	go->_vtable = vtable;
	go->_base = go_new(base_vtable);
}

static inline void go_update(struct game_object* go)
{
	if (!go->can_update)
		return;

	go->_vtable->update(go);
}

static inline void go_draw(struct game_object* go)
{
	if (!go->can_draw)
		return;

	go->_vtable->draw(go);
}