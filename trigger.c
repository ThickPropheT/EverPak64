#include "trigger.h"

#include <malloc.h>


const struct trg_type TRG_TYPE[] = { { } };


struct trigger *trigger_manually(void)
{
	struct trigger *trg = malloc(sizeof * trg);

	_trg_init(trg, TRG_TYPE);

	return trg;
}


void trg_set(struct trigger *trg)
{
	trg->is_tripped = 1;
}

u8 trg_check(struct trigger *trg)
{
	if (!trg || trg->is_tripped)
		return 1;

	return trg->is_tripped = _trg_invoke(trg->trg_type->check, trg);
}

void trg_reset(struct trigger *trg)
{
	if (!trg)
		return;

	trg->is_tripped = 0;
}
