#include "acc_mb_args.h"

struct acc_mb_args* accmba_new(struct accessory* acc)
{
	struct acc_mb_args* args = malloc(sizeof * args);

	args->acc = acc;

	return args;
}