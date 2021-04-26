#include <stdio.h>
#include <stdarg.h>
#include <malloc.h>
#include <string.h>
#include <stdint.h>
#include <libdragon.h>

#include "game_object.h"
#include "device_manager.h"
#include "pinwheel.h"
#include "fps_counter.h"
#include "color_palette.h"
#include "types.h"
#include "math.h"
#include "menu_state.h"
#include "menu_tree.h"
#include "main_menu.h"
#include "slot_menu.h"
#include "console.h"


// render pinwheel @ ~15Hz
#define FIFTEEN_FPS		66
// render fps counter @ 0.5Hz
#define HALF_FPS		2000


#define BG_COLOR 		0x10001
#define BG_TEXT_COLOR	TRANS
#define FG_TEXT_COLOR	0x364D364D


// #### TODO MOVE THIS ####
void sleep(unsigned long ms)
{
	unsigned start_ms = get_ticks_ms();

	while (get_ticks_ms() - start_ms < ms);
}
// #### TODO MOVE THIS ####



void update(struct menu_tree* mt)
{
	mt_update(mt);
}



void draw(struct menu_tree* mt)
{
	mt_draw(mt);
}



void set_up(void)
{
	/* enable interrupts (on the CPU) */
	init_interrupts();

	/* Initialize peripherals */
	cs_init(Gx2D, DEPTH_16_BPP);

	controller_init();
}



int main(void)
{
	set_up();

	char pinwheel = 0;
	pw_init(FIFTEEN_FPS, 0, &pinwheel);

	float fps = 0;
	fps_init(HALF_FPS, &fps);

	graphics_set_color(FG_TEXT_COLOR, BG_TEXT_COLOR);

	struct device_state dev = dev_new();

	struct menu_tree mt = mt_new(&dev);

	while (1)
	{
		pw_update();
		fps_update();

		dev_poll(&dev);

		update(&mt);

		cs_clear(BG_COLOR);

		cprintf("(%c) %.1f fps [menu.z64]\n\n", pinwheel, fps);

		draw(&mt);

		cs_render();
	}

	return 0;
}