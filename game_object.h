#pragma once

#include <stdlib.h>

struct game_object
{
	const struct _go_vtable* _vtable;
	const struct game_object* _base;

	u8 can_update;
};

struct _go_vtable
{
	void (*update)(struct game_object* go);
	// TODO add draw?
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
	go->_vtable->update(go);
}