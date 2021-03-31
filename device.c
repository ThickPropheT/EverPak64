#include "device.h"

void dev_poll(struct device_state* ds)
{
	controller_scan();

	//ds->controllers = get_controllers_present();

	struct controller_data out;
	int accessories = get_accessories_present(&out);

	ds->accessories_changed = ds->accessories != accessories;
	ds->accessories = accessories;

	ds->keys = get_keys_down();
}
