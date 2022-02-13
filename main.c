#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>
#include <libdragon.h>

#include "game_object.h"
#include "device_manager.h"
#include "controller_manager.h"
#include "pinwheel.h"
#include "fps_counter.h"
#include "color_palette.h"
#include "types.h"
#include "math.h"
#include "menu_state.h"
#include "menu_tree.h"
#include "main_menu.h"
#include "renderer.h"
#include "render_graph_bootstrapper.h"
#include "console.h"


#define TITLE			"EverPak64"
#define VERSION			"0.1.0.1"

// render fps counter @ 0.5Hz
#define HALF_FPS		2000

#define RENDERER		Gx2D
#define BIT_DEPTH		DEPTH_32_BPP

#define BG_COLOR 		BLACK(BIT_DEPTH)
#define BG_TEXT_COLOR	TRANS
#define FG_TEXT_COLOR	LIME(BIT_DEPTH)


// #### TODO MOVE THIS ####
void sleep(unsigned long ms)
{
	unsigned start_ms = get_ticks_ms();

	while (get_ticks_ms() - start_ms < ms);
}
// #### TODO MOVE THIS ####



static inline void update(struct render_graph* rg, struct menu_tree* mt)
{
	// TODO prevents weirdness if controller 1 is removed
	// TODO update this when any/all controllers can input
	if (!(mt->cman->ctrl_flags & CONTROLLER_1_INSERTED))
		return;

	rg_update(rg);

	mt_update(mt);
}



static inline void draw_header(float fps)
{
	cprintf("    %.1f fps [%s v%s]\n\n", fps, TITLE, VERSION);
}

static inline void draw(struct render_graph* rg, struct menu_tree* mt)
{
	rg_draw(rg);

	mt_draw(mt);
}



static struct renderer* set_up(void)
{
	/* enable interrupts (on the CPU) */
	init_interrupts();

	struct renderer* ren = ren_new(RESOLUTION_320x240, BIT_DEPTH, 2, GAMMA_NONE, ANTIALIAS_RESAMPLE);

	cs_init();

	controller_init();

	return ren;
}



int main(void)
{
	struct renderer* ren = set_up();

	float fps = 0;
	fps_init(HALF_FPS, &fps);

	graphics_set_color(FG_TEXT_COLOR, BG_TEXT_COLOR);

	struct device_state dev = dev_new();
	struct controller_manager* cman = cman_new(&dev);

	struct render_graph* rg = rg_init(ren);

	struct menu_tree mt = mt_new(&dev, cman);

	while (1)
	{
		fps_update();

		dev_poll(&dev);
		cman_update(cman);

		update(rg, &mt);

		ren_lock(ren);

		cs_clear(ren, BG_COLOR);

		draw_header(fps);

		draw(rg, &mt);

		ren_show(ren);
	}

	return 0;
}