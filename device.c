#include "device.h"

#include "accessory.h"

struct device_state dev_new(void)
{
	struct device_state dev = { };

	for (u8 i = 0; i < N_SLOTS; i++)
		dev.accessories[i] = acc_new(i);

	return dev;
}

void dev_poll(struct device_state* ds)
{
	controller_scan();

	struct controller_data out;
	u16 acc = get_accessories_present(&out);

	ds->acc_f_changed = ds->accessories_f != acc;
	ds->accessories_f = acc;

	if (ds->acc_f_changed)
	{
		ds->controllers = get_controllers_present();

		for (u8 i = 0; i < N_SLOTS; i++)
			acc_update(&ds->accessories[i]);
	}

	ds->keys_d = get_keys_down();
}
