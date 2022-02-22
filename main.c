#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>
#include <libdragon.h>

#include "game_object.h"
#include "device_manager.h"
#include "controller_manager.h"
#include "types.h"
#include "math.h"
#include "menu_state.h"
#include "menu_tree.h"
#include "main_menu.h"
#include "renderer.h"
#include "render_graph_bootstrapper.h"
#include "console.h"


//static inline void update(struct menu_tree* mt)
//{
//	// TODO prevents weirdness if controller 1 is removed
//	// TODO update this when any/all controllers can input
//	/*if (!(mt->cman->ctrl_flags & CONTROLLER_1_INSERTED))
//		return;*/
//
//	//mt_update(mt);
//}


static struct renderer *set_up(void)
{
	/* enable interrupts (on the CPU) */
	init_interrupts();

	struct renderer *ren = ren_new(RESOLUTION_320x240, DEPTH_32_BPP, 2, GAMMA_NONE, ANTIALIAS_RESAMPLE);

	cs_init();

	controller_init();

	return ren;
}


int main(void)
{
	struct renderer *ren = set_up();

	// TODO find a better place for this
	graphics_set_color(ren->cp->fg_text, ren->cp->bg_text);

	struct render_graph *rg = rg_init(ren);

	while (1)
	{
		rg_update(rg);

		rg_draw(rg);
	}

	return 0;
}
