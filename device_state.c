#include "device_state.h"


#define FIRST_SLOT_FLAG 0xF000
#define FLAG_WIDTH		4


u16 get_flag(u8 i_slot)
{
	return FIRST_SLOT_FLAG >> (i_slot * FLAG_WIDTH);
}
