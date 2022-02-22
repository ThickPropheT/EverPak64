#pragma once

#include "menu_builder.h"
#include "controller.h"

struct acc_mb_args
{
	struct mb_args mba;

	struct controller *ctrl;
};

struct acc_mb_args *accmba_new(struct controller *ctrl);
