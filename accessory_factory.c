#include "accessory_factory.h"

#include "memory_pak.h"
#include "rumble_pak.h"

static struct accessory *resolve_rpak(u8 i_slot)
{
	// Brawler64 controllers report mempaks as a rumble pak.
	// TODO could/should the result of this call be cached?
	if (is_mpk(i_slot))
		return (void *)mpk_new(i_slot);

	return (void *)rpk_new(i_slot);
}

struct accessory *resolve_acc(struct device_state dev, u8 i_slot)
{
	u8 type = ACCESSORY_NONE;

	if (dev.acc_flags & get_flag(i_slot))
		type = identify_accessory(i_slot);

	switch (type)
	{
	case ACCESSORY_MEMPAK:
		return (void *)mpk_new(i_slot);

	case ACCESSORY_RUMBLEPAK:
		return resolve_rpak(i_slot);

	default:
		return acc_new(i_slot);
	}
}