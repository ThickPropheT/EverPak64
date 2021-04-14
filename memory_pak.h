#pragma once

#include "accessory.h"

#define ENTRIES_LEN		16

struct memory_pak
{
	// TODO should this be const?
	struct accessory acc;

	entry_structure_t entries[ENTRIES_LEN];
};


struct memory_pak* mpk_new(u8 i_slot);

void mpk_format(struct memory_pak* mpk);