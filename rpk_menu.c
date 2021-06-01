#include "rpk_menu.h"

#include "menu_nav_controller.h"
#include "console.h"
#include "math.h"
#include "controller.h"
#include "keys.h"


static void rpkm_activating(const struct go_delegate* base, struct game_object* go);
const struct go_delegate RPKM_ACTIVATING[] = { { rpkm_activating } };

static void rpkm_update(const struct go_delegate* base, struct game_object* go);
const struct go_delegate RPKM_UPDATE[] = { { rpkm_update } };

static void rpkm_draw(const struct go_delegate* base, struct game_object* go);
const struct go_delegate RPKM_DRAW[] = { { rpkm_draw } };

static void rpkm_deactivating(const struct go_delegate* base, struct game_object* go);
const struct go_delegate RPKM_DEACTIVATING[] = { { rpkm_deactivating } };

const struct go_type RPKM_TYPE[] = { { RPKM_ACTIVATING, RPKM_UPDATE, RPKM_DRAW, RPKM_DEACTIVATING } };


struct rumble_state* rs_new(void)
{
	struct rumble_state* rs = calloc(1, sizeof * rs);
	return rs;
}

struct rpk_menu* rpkm_new(struct device_state* dev, struct controller_manager* cman, struct menu_nav_controller* mnav, struct controller* ctrl)
{
	struct rpk_menu* menu = malloc(sizeof * menu);

	_gm_init(&menu->gm, RPKM_TYPE, dev, cman, mnav, 0);

	menu->ctrl = ctrl;
	menu->rpk = (void*)ctrl->acc;

	menu->rumble_pwm = pwm_new(0, 1, 0);
	menu->state = rs_new();

	return menu;
}



static inline void pwm_handle_input(struct controller* ctrl, struct pwm_state* pwm)
{
	if (ctrl_key_down(ctrl, &key_C_left))
	{
		pwm_dec_low(pwm);
	}
	else if (ctrl_key_down(ctrl, &key_C_up))
	{
		pwm_inc_high(pwm);
	}
	else if (ctrl_key_down(ctrl, &key_C_right))
	{
		pwm_inc_low(pwm);
	}
	else if (ctrl_key_down(ctrl, &key_C_down))
	{
		pwm_dec_high(pwm);
	}
}

static inline void rmbl_handle_input(struct controller* ctrl, struct pwm_state* pwm, struct rumble_state* state)
{
	u8 r = state->rumble;

	if (ctrl_key_held(ctrl, &key_Z))
	{
		r = 1;
	}
	else if (ctrl_key_up(ctrl, &key_Z))
	{
		r = 0;
	}
	else if (ctrl_key_down(ctrl, &key_start))
	{
		r = !pwm->enabled;
	}

	state->rumble = r;
}

static inline void reset_handle_input(struct controller* ctrl, struct pwm_state* pwm)
{
	if (ctrl_key_down(ctrl, &key_R))
	{
		pwm_reset(pwm);
	}
}

static void rpkm_handle_input(struct controller* ctrl, void* context)
{
	struct rpk_menu* menu = context;
	struct pwm_state* pwm = menu->rumble_pwm;

	pwm_handle_input(ctrl, pwm);
	rmbl_handle_input(ctrl, pwm, menu->state);
	reset_handle_input(ctrl, pwm);

	_gm_handle_input(ctrl, (void*)menu);
}

static void rpkm_activating(const struct go_delegate* base, struct game_object* go)
{
	struct rpk_menu* menu = (void*)go;
	struct controller_manager* cman = menu->gm.cman;

	menu->input_handler =
		cman_add_handler(cman, cman->any_controller, menu, &rpkm_handle_input);
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

static void rpkm_update(const struct go_delegate* base, struct game_object* go)
{
	struct rpk_menu* menu = (void*)go;
	struct accessory acc = menu->rpk->acc;


	set_rumble(menu, menu->state->rumble);


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
}



static void rpkm_draw(const struct go_delegate* base, struct game_object* go)
{
	struct rpk_menu* menu = (void*)go;
	struct accessory* acc = (void*)menu->rpk;

	_gm_draw_header(*acc);

	struct pwm_state* pwm = menu->rumble_pwm;

	cprintf("Rumble (Z)");
	cprintf("rumble: %4d", pwm->enabled);
	cprintf("tick: %6llu", pwm->tick);
	cprintf("pwm high: %2llu", pwm->high_interval);
	cprintf("pwm low: %3llu", pwm->low_interval);
}

static void rpkm_deactivating(const struct go_delegate* base, struct game_object* go)
{
	struct rpk_menu* menu = (void*)go;
	struct accessory acc = menu->rpk->acc;

	rumble_stop(acc.i_slot);

	cman_rem_handler(menu->gm.cman, menu->input_handler);
	free(menu->state);

	pwm_free(menu->rumble_pwm);
}
