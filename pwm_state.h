#pragma once

#include "types.h"

enum pwm_event
{
	NONE,
	INIT,
	RISING,
	FALLING
};

struct pwm_state
{
	struct pwm_state* def;

	u8 enabled;

	u64 tick;
	u64 high_interval;
	u64 low_interval;
};


struct pwm_state* pwm_new(u8 enabled, u8 high_interval, u8 low_interval);


u8 pwm_set_enabled(struct pwm_state* pwm, u8 value);

void pwm_set_high(struct pwm_state* pwm, u64 value);
void pwm_inc_high(struct pwm_state* pwm);
void pwm_dec_high(struct pwm_state* pwm);

void pwm_set_low(struct pwm_state* pwm, u64 value);
void pwm_inc_low(struct pwm_state* pwm);
void pwm_dec_low(struct pwm_state* pwm);


enum pwm_event pwm_update(struct pwm_state* pwm);

void pwm_reset(struct pwm_state* pwm);

void pwm_free(struct pwm_state* pwm);
