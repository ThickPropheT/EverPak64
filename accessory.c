#include "accessory.h"

#include <stdlib.h>
#include <string.h>


static void acc_update(struct game_object* go);

const struct _go_vtable ACC[] = { { acc_update } };


char* accessory_names[N_ACC_TYPES] =
{
	"None",
	"Mem Pak",
	"Rumble Pak",
	"VRU",
	"Transfer Pak"
};


void _acc_init(struct accessory* acc, const struct _go_vtable* vtable, u8 i_slot)
{
	acc->base._vtable = vtable;
	acc->base._base = go_new(ACC);

	acc->i_slot = i_slot;
}

struct accessory* acc_new(u8 i_slot)
{
	struct accessory* acc = malloc(sizeof * acc);

	acc->base._vtable = ACC;

	acc->i_slot = i_slot;
	acc->type = ACCESSORY_NONE;

	return acc;
}

u8 acc_get_number(struct accessory acc)
{
	return acc.i_slot + 1;
}



static void acc_update(struct game_object* go)
{
	struct accessory* acc = (struct accessory*)go;

	u8 slot = acc->i_slot;

	acc->status = validate_mempak(slot);
}