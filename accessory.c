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
	"VRU"
	// TODO add transfer pak handling
};


struct accessory* acc_alloc(void)
{
	struct accessory a = { { ACC } };

	struct accessory* acc = malloc(sizeof(struct accessory));
	return memcpy(acc, &a, sizeof(struct accessory));
}

struct accessory* acc_init(struct accessory* acc, u8 i_slot)
{
	acc->i_slot = i_slot;
	return acc;
}

struct accessory* acc_new(u8 i_slot)
{
	return acc_init(acc_alloc(), i_slot);
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