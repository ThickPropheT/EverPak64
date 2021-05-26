#pragma once

#include <libdragon.h>

static inline unsigned key_Z(struct SI_condat c)
{
	return c.Z;
}

static inline unsigned key_start(struct SI_condat c)
{
	return c.start;
}

static inline unsigned key_R(struct SI_condat c)
{
	return c.R;
}

static inline unsigned key_C_up(struct SI_condat c)
{
	return c.C_up;
}

static inline unsigned key_C_down(struct SI_condat c)
{
	return c.C_down;
}

static inline unsigned key_C_left(struct SI_condat c)
{
	return c.C_left;
}

static inline unsigned key_C_right(struct SI_condat c)
{
	return c.C_right;
}
