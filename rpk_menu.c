#include "rpk_menu.h"

#include "menu_nav_controller.h"
#include "console.h"
#include "math.h"


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

	menu->rumble_pwm = pwm_new(0, 1, 0);

	return menu;
}

static inline void pwm_get_input(struct device_state* dev, struct rpk_menu* menu)
{
	struct controller_data keys_d = dev->keys_d;

	struct pwm_state* pwm = menu->rumble_pwm;

	if (keys_d.c[0].C_left)
	{
		pwm_dec_low(pwm);
	}
	else if (keys_d.c[0].C_up)
	{
		pwm_inc_high(pwm);
	}
	else if (keys_d.c[0].C_right)
	{
		pwm_inc_low(pwm);
	}
	else if (keys_d.c[0].C_down)
	{
		pwm_dec_high(pwm);
	}
}

static inline void rmbl_get_input(struct device_state* dev, struct rpk_menu* menu, u8* rumble)
{
	struct controller_data keys_d = dev->keys_d;
	struct controller_data keys_h = dev->keys_h;
	struct controller_data keys_u = dev->keys_u;

	struct pwm_state* pwm = menu->rumble_pwm;

	u8 r = pwm->enabled;

	if (keys_h.c[0].Z)
	{
		r = 1;
	}
	else if (keys_u.c[0].Z)
	{
		r = 0;
	}
	else if (keys_d.c[0].start)
	{
		r = !pwm->enabled;
	}

	*rumble = r;
}

static inline void reset_get_input(struct device_state* dev, struct rpk_menu* menu)
{
	struct controller_data keys_d = dev->keys_d;

	if (keys_d.c[0].R)
	{
		pwm_reset(menu->rumble_pwm);
	}
}

static inline void set_rumble(struct rpk_menu* menu, u8 value)
{
	struct pwm_state* pwm = menu->rumble_pwm;

	if (!pwm_set_enabled(pwm, value))
		return;

	if (value)
		return;

	rumble_stop(menu->rpk->acc.i_slot);
}

static void rpkmn_update(const struct go_delegate* base, struct game_object* go)
{
	struct rpk_menu* menu = (void*)go;

	struct device_state* dev = menu->gm.dev;

	struct accessory acc = menu->rpk->acc;


	pwm_get_input(dev, menu);

	u8 rumble;
	rmbl_get_input(dev, menu, &rumble);

	reset_get_input(dev, menu);


	set_rumble(menu, rumble);


	switch (pwm_update(menu->rumble_pwm))
	{
	case INIT:
		rumble_start(acc.i_slot);
		break;

	case RISING:
		rumble_start(acc.i_slot);
		break;

	case FALLING:
		rumble_stop(acc.i_slot);
		break;

	case NONE:
		break;
	}


	_god_invoke(base, go);
}

static void rpkmn_draw(const struct go_delegate* base, struct game_object* go)
{
	struct rpk_menu* menu = (void*)go;
	struct accessory* acc = (void*)menu->rpk;

	_gm_draw_header(*acc);

	struct pwm_state* pwm = menu->rumble_pwm;

	cprintf("Rumble (Z)");
	cprintf("rumble: %d", pwm->enabled);
	cprintf("tick: %llu", pwm->tick);
	cprintf("pwm high: %llu", pwm->high_interval);
	cprintf("pwm low: %llu", pwm->low_interval);
}

static void rpkmn_deactivating(const struct go_delegate* base, struct game_object* go)
{
	struct rpk_menu* menu = (void*)go;
	struct accessory acc = menu->rpk->acc;

	rumble_stop(acc.i_slot);

	pwm_free(menu->rumble_pwm);
}
