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
	// TODO bake this directly into sub-types instead
	acc->type = identify_accessory(slot);
}

void acc_format(struct accessory* acc)
{
	// TODO convert this to signal an acc_update
	//		rather than doing it directly here.
	format_mempak(acc->i_slot);
	acc_update((struct game_object*)acc);
}