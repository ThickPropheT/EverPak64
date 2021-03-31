#include "device.h"

void dev_poll(struct device_state* ds)
{
	controller_scan();

	//ds->controllers = get_controllers_present();

	struct controller_data out;
	ds->accessories = get_accessories_present(&out);

	ds->keys = get_keys_down();
}
