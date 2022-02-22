#pragma once

#include "types.h"



struct trigger;
struct trg_type;

typedef u8(*trg_func)(struct trigger *trg);

static inline u8 _trg_invoke(trg_func func, struct trigger *trg)
{
	if (!func)
		return 0;

	return func(trg);
}



struct trg_type
{
	trg_func check;
};

struct trigger
{
	const struct trg_type *trg_type;

	u8 is_tripped;
};


static inline void _trg_init(struct trigger *trg, const struct trg_type *vtable)
{
	trg->trg_type = vtable;
	trg->is_tripped = 0;
}

struct trigger *trigger_manually(void);

void trg_set(struct trigger *trg);
u8 trg_check(struct trigger *trg);
void trg_reset(struct trigger *trg);
