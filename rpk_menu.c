#include "rpk_menu.h"

#include "menu_nav_controller.h"
#include "console.h"


static void rpkmn_update(const struct go_delegate* base, struct game_object* go);
const struct go_delegate RPKM_UPDATE[] = { { rpkmn_update, GM_UPDATE } };

static void rpkmn_draw(const struct go_delegate* base, struct game_object* go);
const struct go_delegate RPKM_DRAW[] = { { rpkmn_draw } };

static void rpkmn_deactivating(const struct go_delegate* base, struct game_object* go);
const struct go_delegate RPKM_DEACTIVATING[] = { { rpkmn_deactivating } };

const struct go_type RPKM_TYPE[] = { { NULL, RPKM_UPDATE, RPKM_DRAW, RPKM_DEACTIVATING } };


struct rpk_menu* rpkm_new(struct device_state* dev, struct menu_nav_controller* mnav, struct rumble_pak* rpk)
{
	struct rpk_menu* menu = malloc(sizeof * menu);

	_gm_init(&menu->gm, RPKM_TYPE, dev, mnav, 0);

	menu->rpk = rpk;

	menu->rumble = 0;

	menu->pwm_tick = 0;
	menu->pwm_high = 1;
	menu->pwm_low = 0;

	return menu;
}

static void rpkmn_update(const struct go_delegate* base, struct game_object* go)
{
	struct rpk_menu* menu = (void*)go;

	struct device_state* dev = menu->gm.dev;

	struct controller_data keys_d = dev->keys_d;
	struct controller_data keys_h = dev->keys_h;
	struct controller_data keys_u = dev->keys_u;

	struct accessory acc = menu->rpk->acc;

	if (keys_d.c[0].C_left)
	{
		menu->pwm_low--;
	}
	else if (keys_d.c[0].C_up)
	{
		menu->pwm_high++;
	}
	else if (keys_d.c[0].C_right)
	{
		menu->pwm_low++;
	}
	else if (keys_d.c[0].C_down)
	{
		menu->pwm_high--;
	}


	u8 rumble = menu->rumble;

	if (keys_h.c[0].Z)
	{
		rumble = 1;
	}
	else if (keys_u.c[0].Z)
	{
		rumble = 0;
	}
	else if (keys_d.c[0].start)
	{
		rumble = !menu->rumble;
	}


	u8 rumbleChanged = rumble != menu->rumble;

	if (rumbleChanged)
	{
		menu->rumble = rumble;

		menu->pwm_tick = 0;

		if (!rumble)
			rumble_stop(acc.i_slot);
	}


	if (menu->pwm_high == 0)
	{
		menu->pwm_high = 1;
	}


	if (rumble)
	{
		u8 tick = menu->pwm_tick;
		menu->pwm_tick++;

		u8 can_pulse = menu->pwm_low > 0;

		u8 rising = tick == menu->pwm_high + menu->pwm_low;
		u8 falling = tick == menu->pwm_high;

		if (tick == 0)
		{
			rumble_start(acc.i_slot);
		}
		else if (can_pulse && falling)
		{
			rumble_stop(acc.i_slot);
		}
		else if (can_pulse && rising)
		{
			rumble_start(acc.i_slot);
			menu->pwm_tick = 1;
		}
	}


	_god_invoke(base, go);
}

static void rpkmn_draw(const struct go_delegate* base, struct game_object* go)
{
	struct rpk_menu* menu = (void*)go;
	struct accessory* acc = (void*)menu->rpk;

	_gm_draw_header(*acc);

	cprintf("Rumble (Z)");
	cprintf("rumble: %d", menu->rumble);
	cprintf("tick: %hu", menu->pwm_tick);
	cprintf("pwm high: %d", menu->pwm_high);
	cprintf("pwm low: %d", menu->pwm_low);
}

static void rpkmn_deactivating(const struct go_delegate* base, struct game_object* go)
{
	struct rpk_menu* menu = (void*)go;
	struct accessory acc = menu->rpk->acc;

	rumble_stop(acc.i_slot);
}
