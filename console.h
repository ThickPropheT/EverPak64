#pragma once

#include "renderer.h"
#include "console_context.h"


// TODO could this pattern be converted to a function?
#define cprintf(...) { \
	cc_printfln(cs_get_current(), __VA_ARGS__); \
}


void cs_init(void);

struct console_context *cs_get_current(void);

void cs_clear(struct renderer *ren, uint32_t bg_color);
