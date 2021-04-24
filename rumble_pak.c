#include "rumble_pak.h"

#include <stdlib.h>
#include <string.h>


static void rpk_update(struct game_object* go);

const struct go_type RPK[] = { { rpk_update } };


struct rumble_pak* rpk_new(u8 i_slot)
{
	struct rumble_pak* rpk = calloc(1, sizeof * rpk);

	_acc_init(&rpk->acc, RPK, i_slot);

	rpk->acc.type = ACCESSORY_RUMBLEPAK;

	return rpk;
}


static void rpk_update(struct game_object* go) 
{
	go->_base->type->update(go);
}
