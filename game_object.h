#pragma once

struct game_object
{
	const struct _go_vtable* vtable_;
};

struct _go_vtable
{
	void (*update)(struct game_object* go);
	// TODO add draw?
};

static inline void go_update(struct game_object* go)
{
	go->vtable_->update(go);
}