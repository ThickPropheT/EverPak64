#pragma once

#include <stdint.h>


struct color_palette
{
	uint32_t trans;
	uint32_t black;
	uint32_t white;

	uint32_t forest_green;
	uint32_t teal_green;
	uint32_t lime_green;
	uint32_t dark_forest_green;

	uint32_t bg;
	uint32_t border;
	uint32_t bg_text;
	uint32_t fg_text;
};

struct color_palette *cp_new(void);
