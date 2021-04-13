#include "memory_pak.h"

#include <stdlib.h>
#include <string.h>


static void mpk_update(struct game_object* go);

const struct _go_vtable MPK[] = { { mpk_update } };


struct memory_pak* mpk_new(u8 i_slot)
{
	struct memory_pak* mpk = malloc(sizeof * mpk);

	_acc_init(&mpk->base, MPK, i_slot);

	mpk->base.type = ACCESSORY_MEMPAK;

	return mpk;
}


static void mpk_update(struct game_object* go)
{
	go->_base->_vtable->update(go);
}
