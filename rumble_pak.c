#include "rumble_pak.h"

#include <stdlib.h>
#include <string.h>


const struct go_type RPK_TYPE[] = { { NULL, ACC_UPDATE } };


struct rumble_pak *rpk_new(u8 i_slot)
{
	struct rumble_pak *rpk = calloc(1, sizeof * rpk);

	_acc_init(&rpk->acc, RPK_TYPE, i_slot);

	rpk->acc.type = ACCESSORY_RUMBLEPAK;

	return rpk;
}
