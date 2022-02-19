#include "chained_trigger.h"

#include <malloc.h>
#include "types.h"


static u8 check(struct trigger* trg);

const struct trg_type CHAINED_TRG_TYPE[] = { { check } };


struct chained_trigger* trigger_after(struct trigger* target)
{
	struct chained_trigger* ct = malloc(sizeof * ct);

	_trg_init((void*)ct, CHAINED_TRG_TYPE);

	ct->target = target;

	return ct;
}

static u8 check(struct trigger* trg)
{
	struct chained_trigger* ct = (void*)trg;

	return ct->target->is_tripped;
}
