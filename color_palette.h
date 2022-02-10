#pragma once

// TODO should these includes be here? technically they aren't needed for the defines below,
// but including this file without these includes will (may?) be problematic

// uint32_t seems to work even if you remove the stdint.h include. for some reason...
//#include <stdint.h>

// TODO test what happens if a consumer doesn't include display.h but does include color_pallete.h (AND use the defines)
//#include "display.h"

// 0x00000000
#define TRANS			(uint32_t)0x0

// 0x000000FF
// 16 : 00010001
// 32 : 000000FF
#define BLACK(bpp)		(uint32_t)(bpp == DEPTH_16_BPP ? 0x10001 : 0xFF)

//0x32CD32FF
// 16 : 364D364D
// 32 : 32CD32FF
#define LIME(bpp)		(uint32_t)(bpp == DEPTH_16_BPP ? 0x364D364D : 0x32CD32FF)
