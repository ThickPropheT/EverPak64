#include "menu_builder_resolver.h"

#include "default_mb_args.h"
#include "menu_builder.h"

struct game_menu* mbres_build_default(struct menu_builder_table* mbt, u8 i_slot)
{
	struct default_mb_args* args = dmba_new(i_slot);
	struct game_menu* gm = mb_build(mbt->default_builder, (struct mb_args*)args);
	free(args);

	return gm;
}