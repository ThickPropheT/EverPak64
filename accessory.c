#include "accessory.h"

//#include <stdlib.h>
//#include <string.h>

char* accessory_names[N_ACC_TYPES] =
{
	"None",
	"Mem Pak",
	"Rumble Pak",
	"VRU"
};

struct accessory acc_new(u8 i_slot)
{
	struct accessory a = { { ACC }, i_slot };

	// TODO start from this if base is changed to const.
	// 	   it blackscreens and not sure what's wrong with it.
	//struct accessory* acc = malloc(sizeof(struct accessory));
	//memcpy(acc, &a, sizeof(struct accessory));

	return a;
}



static void acc_update(struct game_object* go)
{
	struct accessory* acc = (struct accessory*)go;

	u8 slot = acc->i_slot;

	acc->status = validate_mempak(slot);
	acc->type = identify_accessory(slot);
}

const struct game_object_vtable_ ACC[] = { { acc_update } };



void acc_format(struct accessory* acc)
{
	// TODO convert this to signal an acc_update
	//		rather than doing it directly here.
	format_mempak(acc->i_slot);
	acc_update((struct game_object*)acc);
}