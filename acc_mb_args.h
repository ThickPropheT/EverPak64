#pragma once

#include "menu_builder.h"
#include "accessory.h"

struct acc_mb_args
{
	struct mb_args mba;

	struct accessory* acc;
};

struct acc_mb_args* accmba_new(struct accessory* acc);