#include "pwm_state.h"

#include <malloc.h>

#include "math.h"

static inline struct pwm_state *pwm_new_impl(u8 enabled, u8 high_interval, u8 low_interval)
{
	struct pwm_state *pwm = malloc(sizeof * pwm);

	pwm->enabled = enabled;

	pwm->tick = 0;
	pwm->high_interval = high_interval;
	pwm->low_interval = low_interval;

	return pwm;
}

struct pwm_state *pwm_new(u8 enabled, u8 high_interval, u8 low_interval)
{
	struct pwm_state *def = pwm_new_impl(enabled, high_interval, low_interval);
	struct pwm_state *pwm = pwm_new_impl(enabled, high_interval, low_interval);

	pwm->def = def;

	return pwm;
}


u8 pwm_set_enabled(struct pwm_state *pwm, u8 value)
{
	if (pwm->enabled == value)
		return 0;

	pwm->enabled = value;

	pwm->tick = 0;

	return 1;
}


void pwm_set_high(struct pwm_state *pwm, u64 value)
{
	pwm->high_interval = value;

	if (pwm->tick >= pwm->high_interval)
	{
		pwm->tick = 0;
	}
}

void pwm_inc_high(struct pwm_state *pwm)
{
	pwm->high_interval++;

	if (pwm->tick >= pwm->high_interval)
	{
		pwm->tick = 0;
	}
}

void pwm_dec_high(struct pwm_state *pwm)
{
	pwm->high_interval--;
	pwm->tick = 0;
}


void pwm_set_low(struct pwm_state *pwm, u64 value)
{
	pwm->low_interval = value;

	if (pwm->tick >= pwm->low_interval)
	{
		pwm->tick = 0;
	}
}

void pwm_inc_low(struct pwm_state *pwm)
{
	pwm->low_interval++;

	if (pwm->tick >= pwm->low_interval)
	{
		pwm->tick = 0;
	}
}

void pwm_dec_low(struct pwm_state *pwm)
{
	pwm->low_interval--;
	pwm->tick = 0;
}


enum pwm_event pwm_update(struct pwm_state *pwm)
{
	math_maxp(&pwm->high_interval, 1);

	if (!pwm->enabled)
		return NONE;

	u8 tick = pwm->tick;
	pwm->tick++;

	u8 can_pulse = pwm->low_interval > 0;

	u8 rising = tick == pwm->high_interval + pwm->low_interval;
	u8 falling = tick == pwm->high_interval;

	if (tick == 0)
	{
		return INIT;
	}
	else if (can_pulse && falling)
	{
		return FALLING;
	}
	else if (can_pulse && rising)
	{
		pwm->tick = 1;
		return RISING;
	}

	return NONE;
}

void pwm_reset(struct pwm_state *pwm)
{
	struct pwm_state *def = pwm->def;

	pwm->enabled = def->enabled;

	pwm->tick = 0;
	pwm->high_interval = def->high_interval;
	pwm->low_interval = def->low_interval;
}

void pwm_free(struct pwm_state *pwm)
{
	free(pwm->def);
	free(pwm);
}
