#pragma once

#include "device_state.h"
#include "game_state.h"

struct device_state dev_new(void);

void dev_poll(struct game_state gs, struct device_state* dev);