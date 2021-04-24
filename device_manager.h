#pragma once

#include "device_state.h"

struct device_state dev_new(void);

void dev_poll(struct device_state* dev);