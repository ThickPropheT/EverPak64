#pragma once

struct game_object
{
	const struct game_object_vtable_* vtable_;
};

struct game_object_vtable_
{
	void (*update)(struct game_object* go);
	// TODO add draw?
};

static inline void go_update(struct game_object* go)
{
	go->vtable_->update(go);
}