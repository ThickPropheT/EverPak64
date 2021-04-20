#pragma once

#include "console_context.h"

// TODO figure out how to hide this as best as possible while allowing
// TODO for the functionality above
//struct console_context cs;


// TODO could this pattern be converted to a function?
#define cprintf(...) { \
	cc_printfln(cs_get_current(), __VA_ARGS__); \
}


void cs_init(enum renderer r, bitdepth_t d);

struct console_context *cs_get_current(void);

void cs_clear(uint32_t bg_color);

void cs_render(void);