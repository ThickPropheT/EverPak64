#include "accessory.h"

char* accessory_names[N_ACC_TYPES] =
{
	"None",
	"Mem Pak",
	"Rumble Pak",
	"VRU"
};

struct accessory acc_new(u8 i_slot)
{
	return (struct accessory) { i_slot };
}

void acc_update(struct accessory* acc)
{
	u8 slot = acc->i_slot;

	acc->status = validate_mempak(slot);
	acc->type = identify_accessory(slot);
}
