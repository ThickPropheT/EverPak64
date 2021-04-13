#include "memory_pak.h"

#include <stdlib.h>
#include <string.h>


static void mpk_update(struct game_object* go);

const struct _go_vtable MPK[] = { { mpk_update } };


struct memory_pak* mpk_new(u8 i_slot)
{
	struct memory_pak* mpk = calloc(1, sizeof * mpk);

	_acc_init(&mpk->base, MPK, i_slot);

	mpk->base.type = ACCESSORY_MEMPAK;
	mpk->base.base.can_update = 1;

	return mpk;
}

static void load_entry(struct memory_pak* mpk, u8 i)
{
	get_mempak_entry(mpk->base.i_slot, i, &mpk->entries[i]);
}


static void mpk_update(struct game_object* go)
{
	go->_base->_vtable->update(go);

	struct memory_pak* mpk = (struct memory_pak*)go;


	load_entry(mpk, go->can_update - 1);

	go->can_update++;

	if (go->can_update <= ENTRIES_LEN)
		return;

	go->can_update = 0;
}


void mpk_format(struct memory_pak* mpk)
{
	format_mempak(mpk->base.i_slot);
	mpk->base.base.can_update = 1;
}
