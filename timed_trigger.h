#pragma once

#include "trigger.h"
#include "interval.h"

struct timed_trigger
{
	struct trigger trg;

	struct interval interval;
};

struct timed_trigger *trigger_at_rate(u32 htz);
