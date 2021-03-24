#include <stdio.h>
#include <stdarg.h>
#include <malloc.h>
#include <string.h>
#include <stdint.h>
#include <libdragon.h>

#define N_CONTROLLERS 4

#define I_DEFAULT_DEPTH 	0
#define I_DEFAULT_SELECTED 	0

// TODO consider converting to enum
// TODO consider renaming to ROOT_MENU
#define SLOT_MENU					0
// TODO consider renaming to SLOT_MENU
#define STATUS_MENU			 		1
#define MAX_MENUS 	STATUS_MENU  + 	1

#define MPAK_READY 			 0
#define MPAK_UNREADABLE		-2
#define MPAK_UNFORMATTED	-3



// #### TODO MOVE THIS ####
void sleep(unsigned long ms)
{
	unsigned start_ms = get_ticks_ms();
	
	while (get_ticks_ms() - start_ms < ms);
}
// #### TODO MOVE THIS ####



char *pinwheel_frames[] =
{
	"\\",
	"|",
	"/",
	"-"
};

char *accessory_names[] =
{
	"None",
	"Mem Pak",
	"Rumble Pak",
	"VRU"
};

struct menu
{
	size_t i_selected;
	size_t n_selections;
};

// TODO move to a utility file
int mod(int x, int m)
{
	return (x % m + m) % m;
}

void m_prev(struct menu *m)
{
	m->i_selected = mod(m->i_selected - 1, m->n_selections);
}

void m_next(struct menu *m)
{
	m->i_selected = mod(m->i_selected + 1, m->n_selections);
}



struct slot_menu
{
	size_t i_slot;
	
	struct menu m;
};

int sm_get_slot_number(struct slot_menu m)
{
	return m.i_slot + 1;
}

// TODO optimize out by caching identify_accessory result
// TODO and using with array indexer
char *sm_get_acc_name(struct slot_menu m)
{
	int i_acc = identify_accessory(m.i_slot);
	return accessory_names[i_acc];
}

int sm_get_slot_flag(struct slot_menu m)
{
	const int FIRST_SLOT_FLAG = 0xF000;
	const int FLAG_WIDTH = 4;
	
	return FIRST_SLOT_FLAG >> (m.i_slot * FLAG_WIDTH);
}



struct root_menu
{
	struct menu m;
	
	size_t i_depth;
	
	size_t n_all;
	struct slot_menu all[];
};

// TODO consider merging this and m_root_create back into one function
struct root_menu *m_root_from_items(size_t n_items, struct slot_menu *items)
{
	struct root_menu *rm = malloc(sizeof *rm + n_items * sizeof *rm->all);
	
	if (!rm)
	{
		printf("m_root_from_items : failed to allocate\n");
		console_render();
		return NULL;
	}
	
	rm->m = (struct menu){ I_DEFAULT_SELECTED, n_items };
	
	rm->i_depth = I_DEFAULT_DEPTH;
	
	rm->n_all = n_items;
	
	for (size_t i = 0; i < n_items; i++)
		rm->all[i] = items[i];
	
	return rm;
}

struct root_menu *m_root_create(void)
{
	struct slot_menu items[N_CONTROLLERS];
	
	for (int i = 0; i < N_CONTROLLERS; i++)
	{
		struct slot_menu m = { i, { I_DEFAULT_SELECTED, 0 } };
		items[i] = m;
	}
	
	return m_root_from_items(N_CONTROLLERS, items);
}

void m_root_pop(struct root_menu *rm)
{
	rm->i_depth = mod(rm->i_depth - 1, MAX_MENUS);
}

void m_root_push(struct root_menu *rm)
{
	rm->i_depth = mod(rm->i_depth + 1, MAX_MENUS);
}

struct device_state
{
	int controllers;
	int accessories;
	// ? identify_accessory()
	// ? validate_mempak(?)
	struct controller_data keys;
};

struct device_state poll_device(void)
{
	controller_scan();
	
	// printf("controller_scan\n");
	// console_render();
	
	int controllers = get_controllers_present();
	
	// printf("get_controllers_present [%X]\n", controllers);
	// console_render();
	
	struct controller_data out;
	int accessories = get_accessories_present(&out);
	
	// printf("get_accessories_present [%X]\n", accessories);
	// console_render();

	struct controller_data keys = get_keys_down();
	
	// printf("get_keys_down\n");
	// console_render();
	
	return (struct device_state)
	{
		controllers,
		accessories,
		keys
	};
}



void m_slot_update(struct root_menu *rm, struct controller_data keys)
{
	if (keys.c[0].up)
	{
		m_prev(&rm->m);
	}
	else if (keys.c[0].down)
	{
		m_next(&rm->m);
	}
	else if (keys.c[0].left)
	{
		m_prev(&rm->m);
	}
	else if (keys.c[0].right)
	{
		m_next(&rm->m);
	}
	else if (keys.c[0].A)
	{
		m_root_push(rm);
	}
}

void m_status_update(struct root_menu *rm, struct controller_data keys)
{
	if (keys.c[0].B)
	{
		m_root_pop(rm);
	}
}

void m_root_update(struct root_menu *rm, struct device_state dev)
{
	// TODO prevents weirdness if controller 1 is removed
	// TODO update this when any/all controllers can input
	if (!(dev.controllers & CONTROLLER_1_INSERTED))
		return;
	
	switch (rm->i_depth)
	{
		case SLOT_MENU:
			m_slot_update(rm, dev.keys);
			break;
			
		case STATUS_MENU:
			m_status_update(rm, dev.keys);
			break;
	}
}



void m_slot_draw(struct root_menu *rm, struct device_state dev)
{
	printf("Select Controller (A)\n\n");
	
	for (size_t i = 0; i < rm->n_all; i++)
	{
		struct slot_menu mi = rm->all[i];
		int sn = sm_get_slot_number(mi);
		
		char *sel = 
			i == rm->m.i_selected
				? ">"
				: " ";
			
		int f_slot = sm_get_slot_flag(mi);
			
		char *pres =
			dev.controllers & f_slot
				? "+"
				: " ";

		printf("%s [%s] Slot %i\n", sel, pres, sn);
	}
}

void m_status_draw_header(struct slot_menu sm)
{
	int sn = sm_get_slot_number(sm);
	char *acc_name = sm_get_acc_name(sm);
	
	printf("Controller %i [%s]\n", sn, acc_name);
	printf("Back (B)\n\n");
}

int m_status_has_error(struct slot_menu sm, struct device_state dev)
{
	int f_slot = sm_get_slot_flag(sm);
	
	if (!(dev.controllers & f_slot))
	{
		printf("Controller missing.\n");
		return 1;
	}
	
	if (!(dev.accessories & f_slot))
	{
		printf("Memory Pak missing.\n");
		return 1;
	}
	
	int err;
	if (!(err = validate_mempak(sm.i_slot)))
		return 0;
	
	switch (err)
	{
		case MPAK_UNREADABLE:
			printf("Memory Pak missing or unreadable.\n");
			break;
		
		case MPAK_UNFORMATTED:
			printf("Memory Pak unformatted.\n");
			break;
	}
	
	return 1;
}

void m_status_draw_entries(struct device_state dev)
{
	printf("1 Banbo-Jazookie\n");
	printf("2 700 Globe in Eye\n");
	printf("3 Oh Hey, Mario 64\n");
	printf("4 Oculus of Time\n");
}

void m_status_draw(struct slot_menu sm, struct device_state dev)
{
	m_status_draw_header(sm);
	
	if (!m_status_has_error(sm, dev))
		m_status_draw_entries(dev);
}

void m_root_draw(struct root_menu *rm, struct device_state dev)
{
	switch (rm->i_depth)
	{
		case SLOT_MENU:
			m_slot_draw(rm, dev);
			break;
			
		case STATUS_MENU:
			m_status_draw(rm->all[rm->m.i_selected], dev);
			break;
	}
}



void setup(void)
{
	/* enable interrupts (on the CPU) */
    init_interrupts();

    /* Initialize peripherals */
    console_init();
    controller_init();

    console_set_render_mode(RENDER_MANUAL);
}



int main(void)
{
	setup();
	
	int ticks = 0;
	
	int i_frame = 0;
	char *pinwheel = pinwheel_frames[i_frame];
	int max = sizeof pinwheel_frames / sizeof *pinwheel_frames;
	
	struct root_menu *rm = m_root_create();

	// TODO this is unverified
	while (!rm);
	
	while(1)
	{
		console_clear();
		
		printf("(%s) menu.z64\n\n", pinwheel);

		struct device_state dev = poll_device();

		m_root_update(rm, dev);
		m_root_draw(rm, dev);
		
		console_render();

		ticks++;
		
		if (ticks % 2 == 1)
			continue;
		
		i_frame++;
		pinwheel = pinwheel_frames[i_frame % max];
	}
	
	return 0;
}