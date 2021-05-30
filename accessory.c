#include "accessory.h"

#include <stdlib.h>
#include <string.h>


static void acc_update(const struct go_delegate* base, struct game_object* go);
const struct go_delegate ACC_UPDATE[] = { { acc_update } };

const struct go_type ACC_TYPE[] = { { NULL, ACC_UPDATE } };


char* accessory_names[N_ACC_TYPES] =
{
	"None",
	"Mem Pak",
	"Rumble Pak",
	"VRU",
	"Transfer Pak"
};


void _acc_init(struct accessory* acc, const struct go_type* vtable, u8 i_slot)
{
	_go_init(&acc->go, vtable);

	acc->i_slot = i_slot;
}

struct accessory* acc_new(u8 i_slot)
{
	struct accessory* acc = malloc(sizeof * acc);

	acc->go.go_type = ACC_TYPE;

	acc->go.can_update = 0;
	acc->go.can_draw = 0;

	acc->i_slot = i_slot;
	acc->type = ACCESSORY_NONE;

	return acc;
}


static void acc_update(const struct go_delegate* base, struct game_object* go)
{
	struct accessory* acc = (void*)go;

	u8 slot = acc->i_slot;

	acc->status = validate_mempak(slot);
}
