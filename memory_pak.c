#include "memory_pak.h"

#include <stdlib.h>
#include <string.h>
#include "accessory.h"


static void mpk_update(struct game_object* go);

const struct _go_vtable MPK[] = { { mpk_update } };


static struct memory_pak* mpk_alloc(void)
{
	struct accessory* acc = acc_alloc();
	struct memory_pak m = { { { MPK, (struct game_object*)acc } } };

	struct memory_pak* mpk = malloc(sizeof(struct memory_pak));
	return memcpy(mpk, &m, sizeof(struct memory_pak));
}

static struct memory_pak* mpk_init(struct memory_pak* mpk, u8 i_slot)
{
	acc_init((struct accessory*)mpk, i_slot);
	return mpk;
}


struct memory_pak* mpk_new(u8 i_slot)
{
	return mpk_init(mpk_alloc(), i_slot);
}



static void mpk_update(struct game_object* go)
{
	go->_base->_vtable->update(go);
}
