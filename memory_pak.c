#include "memory_pak.h"

#include <stdlib.h>
#include <string.h>


static void mpk_update(const struct go_delegate *base, struct game_object *go);
const struct go_delegate MPK_UPDATE[] = { { mpk_update, ACC_UPDATE } };

const struct go_type MPK_TYPE[] = { { NULL, MPK_UPDATE } };


struct memory_pak *mpk_new(u8 i_slot)
{
	struct memory_pak *mpk = calloc(1, sizeof * mpk);

	_acc_init(&mpk->acc, MPK_TYPE, i_slot);

	mpk->acc.type = ACCESSORY_MEMPAK;
	mpk->acc.go.can_update = 1;

	return mpk;
}

u8 is_mpk(u8 i_slot)
{
	return validate_mempak(i_slot) == MPAK_STATUS_READY;
}

static void load_entry(struct memory_pak *mpk, u8 i)
{
	get_mempak_entry(mpk->acc.i_slot, i, &mpk->entries[i]);
}


static void mpk_update(const struct go_delegate *base, struct game_object *go)
{
	_god_invoke(base, go);

	struct memory_pak *mpk = (void *)go;


	load_entry(mpk, go->can_update - 1);

	go->can_update++;

	if (go->can_update <= ENTRIES_LEN)
		return;

	go->can_update = 0;
}


void mpk_format(struct memory_pak *mpk)
{
	format_mempak(mpk->acc.i_slot);
	mpk->acc.go.can_update = 1;
}
