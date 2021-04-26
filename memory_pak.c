#include "memory_pak.h"

#include <stdlib.h>
#include <string.h>


static void mpk_update(struct game_object * go);

const struct go_type MPK[] = { { mpk_update } };


struct memory_pak* mpk_new(u8 i_slot)
{
	struct memory_pak* mpk = calloc(1, sizeof * mpk);

	_acc_init(&mpk->acc, MPK, i_slot);

	mpk->acc.type = ACCESSORY_MEMPAK;
	mpk->acc.go.can_update = 1;

	return mpk;
}

static void load_entry(struct memory_pak* mpk, u8 i)
{
	get_mempak_entry(mpk->acc.i_slot, i, &mpk->entries[i]);
}


static void mpk_update(struct game_object * go)
{
	go->_base->go_type->update(go);

	struct memory_pak* mpk = (void*)go;


	load_entry(mpk, go->can_update - 1);

	go->can_update++;

	if (go->can_update <= ENTRIES_LEN)
		return;

	go->can_update = 0;
}


void mpk_format(struct memory_pak* mpk)
{
	format_mempak(mpk->acc.i_slot);
	mpk->acc.go.can_update = 1;
}
