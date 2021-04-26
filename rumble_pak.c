#include "rumble_pak.h"

#include <stdlib.h>
#include <string.h>


static void rpk_update(const struct go_delegate* base, struct game_object* go);
const struct go_delegate RPK_UPDATE[] = { { rpk_update, ACC_UPDATE } };

const struct go_type RPK_TYPE[] = { { RPK_UPDATE } };


struct rumble_pak* rpk_new(u8 i_slot)
{
	struct rumble_pak* rpk = calloc(1, sizeof * rpk);

	_acc_init(&rpk->acc, RPK_TYPE, i_slot);

	rpk->acc.type = ACCESSORY_RUMBLEPAK;

	return rpk;
}


static void rpk_update(const struct go_delegate* base, struct game_object* go)
{
	_god_invoke(base, go);
}
