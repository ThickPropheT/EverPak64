#pragma once

struct game_object
{
	const struct _go_vtable* _vtable;
	const struct game_object* _base;
};

struct _go_vtable
{
	void (*update)(struct game_object* go);
	// TODO add draw?
};

static inline void go_update(struct game_object* go)
{
	go->_vtable->update(go);
}