#include "trigger.h"

u8 trg_check(struct trigger* trg)
{
	if (!trg)
		return 1;

	return trg->is_tripped = _trg_invoke(trg->trg_type->check, trg);
}

void trg_reset(struct trigger* trg)
{
	if (!trg)
		return;

	trg->is_tripped = 0;
}
