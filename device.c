#include "device.h"

void dev_poll(struct device_state* ds)
{
	controller_scan();

	//ds->controllers = get_controllers_present();

	struct controller_data out;
	u16 acc = get_accessories_present(&out);

	ds->acc_changed = ds->accessories != acc;
	ds->accessories = acc;

	ds->keys = get_keys_down();
}
