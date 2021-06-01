#pragma once

#include <libdragon.h>

static inline unsigned key_A(struct SI_condat c)
{
	return c.A;
}

static inline unsigned key_B(struct SI_condat c)
{
	return c.B;
}

static inline unsigned key_Z(struct SI_condat c)
{
	return c.Z;
}

static inline unsigned key_start(struct SI_condat c)
{
	return c.start;
}

static inline unsigned key_up(struct SI_condat c)
{
	return c.up;
}

static inline unsigned key_down(struct SI_condat c)
{
	return c.down;
}

static inline unsigned key_left(struct SI_condat c)
{
	return c.left;
}

static inline unsigned key_right(struct SI_condat c)
{
	return c.right;
}

static inline unsigned key_L(struct SI_condat c)
{
	return c.L;
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
