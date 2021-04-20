#pragma once

#include <libdragon.h>

#include <stddef.h>

#include "types.h"
#include "renderer.h"

#define BUFFER_LEN 128 // TODO is this a good buffer length? just used one i saw in another project somewhere. maybe alt64

#define cc_printfln(c, ...) { \
	sprintf(c.buf, __VA_ARGS__); \
	cc_println(&c); \
}

struct console_context
{
	display_context_t dc;
	u8 c;
	u8 r;

	char buf[BUFFER_LEN];
};

struct console_context cc_new(enum renderer r, bitdepth_t d);

void cc_clear(struct console_context* cc, uint32_t bg_color);

void cc_println(struct console_context* cc);

void cc_render(struct console_context* cc);