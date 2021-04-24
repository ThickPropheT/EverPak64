#include "default_mb_args.h"

struct default_mb_args* dmba_new(u8 i_slot)
{
	struct default_mb_args* dmba = malloc(sizeof * dmba);

	dmba->i_slot = i_slot;

	return dmba;
}