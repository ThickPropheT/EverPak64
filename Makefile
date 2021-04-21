ROOTDIR = $(N64_INST)
GCCN64PREFIX = $(ROOTDIR)/bin/mips64-elf-
CHKSUM64PATH = $(ROOTDIR)/bin/chksum64
MKDFSPATH = $(ROOTDIR)/bin/mkdfs
HEADERPATH = $(ROOTDIR)/mips64-elf/lib
N64TOOL = $(ROOTDIR)/bin/n64tool
HEADERNAME = header
LINK_FLAGS = -L$(ROOTDIR)/mips64-elf/lib -ldragon -lc -lm -ldragonsys -Tn64.ld --gc-sections
CFLAGS = -std=gnu99 -march=vr4300 -mtune=vr4300 -O2 -Wall -Werror -I$(ROOTDIR)/mips64-elf/include
ASFLAGS = -mtune=vr4300 -march=vr4300
CC = $(GCCN64PREFIX)gcc
AS = $(GCCN64PREFIX)as
LD = $(GCCN64PREFIX)ld
OBJCOPY = $(GCCN64PREFIX)objcopy

ifeq ($(N64_BYTE_SWAP),true)
ROM_EXTENSION = .v64
N64_FLAGS = -b -l 2M -h $(HEADERPATH)/$(HEADERNAME) -o $(PROG_NAME)$(ROM_EXTENSION)
else
ROM_EXTENSION = .z64
N64_FLAGS = -l 2M -h $(HEADERPATH)/$(HEADERNAME) -o $(PROG_NAME)$(ROM_EXTENSION)
endif


OBJS = $(PROG_NAME).o pinwheel.o fps_counter.o renderer.o gra_console.o console.o console_context.o math.o device_manager.o device_state.o accessory.o memory_pak.o rumble_pak.o menu.o menu_state.o menu_tree.o root_menu.o slot_menu.o

PROG_NAME = main



all: $(PROG_NAME)$(ROM_EXTENSION)

$(PROG_NAME)$(ROM_EXTENSION): $(PROG_NAME).elf
	$(OBJCOPY) $(PROG_NAME).elf $(PROG_NAME).bin -O binary
	rm -f $(PROG_NAME)$(ROM_EXTENSION)
	$(N64TOOL) $(N64_FLAGS) -t "Menu" $(PROG_NAME).bin
	$(CHKSUM64PATH) $(PROG_NAME)$(ROM_EXTENSION)

$(PROG_NAME).elf : $(OBJS)
	$(LD) -o $(PROG_NAME).elf $(OBJS) $(LINK_FLAGS)

.PHONY: clean
clean:
	rm -f *.v64 *.z64 *.elf *.o *.bin
	
.PHONY: run
run: $(PROG_NAME)$(ROM_EXTENSION)
	$(DEPLOY_CMD)