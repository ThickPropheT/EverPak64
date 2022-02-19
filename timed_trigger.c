#include "timed_trigger.h"

#include <malloc.h>


static u8 check(struct trigger* trg);

const struct trg_type TIMED_TRG_TYPE[] = { { check } };


struct timed_trigger* trigger_at_rate(u32 htz)
{
	struct timed_trigger* trg = malloc(sizeof * trg);

	_trg_init((void*)trg, TIMED_TRG_TYPE);

	trg->interval = ivl_new(htz);

	return trg;
}

static u8 check(struct trigger* trg)
{
	struct timed_trigger* tt = (void*)trg;

	return ivl_has_elapsed(&tt->interval);
}
