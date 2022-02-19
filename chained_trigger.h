#pragma once

#include "trigger.h"

struct chained_trigger
{
	struct trigger trg;

	struct trigger* target;
};

struct chained_trigger* trigger_after(struct trigger* target);
