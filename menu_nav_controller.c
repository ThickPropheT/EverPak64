#include "menu_nav_controller.h"

#include <malloc.h>

struct menu_nav_controller* mnav_new(struct menu_state* ms)
{
	struct menu_nav_controller* mnav = malloc(sizeof * mnav);

	mnav->ms = ms;

	return mnav;
}

void mnav_push_sm(struct menu_nav_controller* mnav, u8 i_slot)
{

}