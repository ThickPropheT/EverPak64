#include "rumble_pak.h"

#include <stdlib.h>
#include <string.h>


static void rpk_update(struct game_object* go);

const struct _go_vtable RPK[] = { { rpk_update } };


struct rumble_pak* rpk_new(u8 i_slot)
{
	struct rumble_pak* rpk = malloc(sizeof * rpk);
	_acc_init(&rpk->base, RPK, i_slot);
	return rpk;
}


static void rpk_update(struct game_object* go)
{
	go->_base->_vtable->update(go);
}
