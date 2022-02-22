#include "acc_mb_args.h"

struct acc_mb_args *accmba_new(struct controller *ctrl)
{
	struct acc_mb_args *args = malloc(sizeof * args);

	args->ctrl = ctrl;

	return args;
}
