# Vertrix 3, recompiled from Vertrix3.exe (see vertrix3/README.md).
# make -C vertrix3 V3_EXE=/path/to/Vertrix3.exe host     -> build/v3/v3_host
PYTHON ?= python3
V3_EXE ?= Vertrix3.exe
BUILD ?= ../build/v3
GEN := $(BUILD)/gen
HOST_CC ?= cc
HOST_CFLAGS ?= -std=gnu11 -O1 -g -DV3_HISTORY -Wno-parentheses-equality -Wno-unused-label -Wno-unused-variable
RUNTIME := $(wildcard runtime/*.c) $(wildcard win32/*.c) d3d/d3d9.c
HOST_RUNTIME := $(filter-out runtime/threads_wii.c,$(RUNTIME)) d3d/render_soft.c host/host_main.c
INCLUDES := -Iruntime -Iwin32 -Id3d -I$(GEN)

.PHONY: host generate link
host: $(GEN)/stamp
	$(MAKE) link

link: $(BUILD)/v3_host

$(GEN)/stamp: recomp.py
	mkdir -p $(GEN)
	$(PYTHON) recomp.py $(V3_EXE) $(GEN)
	touch $@

generate: $(GEN)/stamp

GEN_SOURCES = $(wildcard $(GEN)/v3_code_*.c) $(GEN)/v3_table.c
GEN_OBJECTS = $(patsubst $(GEN)/%.c,$(BUILD)/host/%.o,$(GEN_SOURCES))

$(BUILD)/host/%.o: $(GEN)/%.c $(GEN)/stamp runtime/cpu.h
	@mkdir -p $(BUILD)/host
	$(HOST_CC) $(HOST_CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD)/host/runtime.a: $(HOST_RUNTIME) $(wildcard runtime/*.h) $(wildcard win32/*.h) $(wildcard d3d/*.h) $(GEN)/stamp
	@mkdir -p $(BUILD)/host/rt
	cd $(BUILD)/host/rt && for f in $(abspath $(HOST_RUNTIME)); do $(HOST_CC) $(HOST_CFLAGS) -Wall $(addprefix -I,$(abspath runtime) $(abspath win32) $(abspath d3d) $(abspath $(GEN))) -c $$f || exit 1; done
	ar rcs $@ $(BUILD)/host/rt/*.o

$(BUILD)/v3_host: $(GEN_OBJECTS) $(BUILD)/host/runtime.a
	$(HOST_CC) $(GEN_OBJECTS) $(BUILD)/host/runtime.a -lm -lpthread -o $@

# --- the Wii ------------------------------------------------------------------------------------
# make -C vertrix3 V3_EXE=/path/to/Vertrix3.exe wii      -> build/v3/vertrix3.dol
# make -C vertrix3 V3_EXE=... wii-sync SYNC=/path/to/sd  -> apps/vertrix3/ (boot.dol, meta.xml, icon.png)
# Vertrix 2 v1.2: BUILD=../build/v12 GAME=vertrix2-v12 V3_EXE=/path/to/Vertrix2.exe
#                                                        -> build/v12/vertrix2-v12.dol
# Vertrix 2 v2.0: BUILD=../build/v20 GAME=vertrix2 V3_EXE=/path/to/Vertrix2.exe
#                                                        -> build/v20/vertrix2.dol
# GAME names the DOL, the SD folder (apps/GAME, as recomp.py's v3_wii_folder) and wii/GAME.xml.
DEVKITPRO ?= /opt/devkitpro
PPC_CC := $(DEVKITPRO)/devkitPPC/bin/powerpc-eabi-gcc
PPC_AR := $(DEVKITPRO)/devkitPPC/bin/powerpc-eabi-ar
LIBOGC ?= $(DEVKITPRO)/libogc
WII_ARCH := -mrvl -mcpu=750 -meabi -mhard-float -DGEKKO -DHW_RVL -D__wii__
GAME ?= vertrix3
# The guest heap the Wii can hold: Vertrix 3 peaks at about 25 MB; Vertrix 2 v1.2 keeps its
# images in memory and reaches 32 MB at its menus (31.7 MB at the end of a match); v2.0 peaks at
# 32.0 MB in a Practice match.
ifneq ($(filter vertrix2 vertrix2-v12,$(GAME)),)
WII_HEAP ?= 0x02800000u
else
WII_HEAP ?= 0x02000000u
endif
WII_DEFINES := -DV3_PAGED -DV3_HEAP_SIZE=$(WII_HEAP) $(WII_DEBUG)
# Debug builds for Dolphin: WII_DEBUG='-DV3_WII_SHOTS=300 -DV3_WII_SCRIPT="\"2 move 128 86; ...\""'
WII_CFLAGS := $(WII_ARCH) $(WII_DEFINES) -std=gnu11 -O2 -fno-strict-aliasing \
	-Wno-parentheses-equality -Wno-unused-label -Wno-unused-variable -Wno-unused-but-set-variable \
	-Wno-unused-function -I$(LIBOGC)/include
WII_RUNTIME := $(filter-out runtime/threads_posix.c,$(RUNTIME)) d3d/render_gx.c wii/wii_main.c
WII_SHARED := ../source/wii_audio.c ../source/audio.c ../source/vf.c ../launcher/app.c
WII_INPUT := $(wildcard ../libwiiinput/source/*.c)
WII_INCLUDES := -Iruntime -Iwin32 -Id3d -I$(GEN) -I$(BUILD)/wii -I../source -I../libwiiinput/include \
	-I../launcher
WII_GEN_OBJECTS = $(patsubst $(GEN)/%.c,$(BUILD)/wii/%.o,$(GEN_SOURCES))
WII_RT_OBJECTS := $(patsubst %.c,$(BUILD)/wii/rt/%.o,$(notdir $(WII_RUNTIME) $(WII_SHARED)))
WII_INPUT_OBJECTS := $(patsubst %.c,$(BUILD)/wii/input/%.o,$(notdir $(WII_INPUT)))
SYNC ?= ../../dolphin-user/Load/WiiSDSync

.PHONY: wii wii-link wii-sync
wii: $(GEN)/stamp
	$(MAKE) wii-link

wii-link: $(BUILD)/$(GAME).dol

$(BUILD)/wii/%.o: $(GEN)/%.c $(GEN)/stamp runtime/cpu.h
	@mkdir -p $(BUILD)/wii
	$(PPC_CC) $(WII_CFLAGS) $(INCLUDES) -c $< -o $@

# One rule writes the header and the assembly; the object waits for it (with -j, a rule naming
# both targets ran twice at once and the assembler read a half-written file).
$(BUILD)/wii/v3_image_bin.h: $(GEN)/stamp
	@mkdir -p $(BUILD)/wii
	cp $(GEN)/v3_image.bin $(BUILD)/wii/v3_image.bin
	cd $(BUILD)/wii && $(DEVKITPRO)/tools/bin/bin2s -H v3_image_bin.h v3_image.bin > v3_image_bin.s

$(BUILD)/wii/v3_image_bin.o: $(BUILD)/wii/v3_image_bin.h
	$(PPC_CC) $(WII_ARCH) -c $(BUILD)/wii/v3_image_bin.s -o $@

vpath %.c runtime win32 d3d wii ../source ../libwiiinput/source ../launcher

$(BUILD)/wii/rt/%.o: %.c $(wildcard runtime/*.h win32/*.h d3d/*.h) $(BUILD)/wii/v3_image_bin.h
	@mkdir -p $(BUILD)/wii/rt
	$(PPC_CC) $(WII_CFLAGS) -Wall $(WII_INCLUDES) -c $< -o $@

$(BUILD)/wii/input/%.o: %.c
	@mkdir -p $(BUILD)/wii/input
	$(PPC_CC) $(WII_ARCH) -O2 -I$(LIBOGC)/include -I../libwiiinput/include -c $< -o $@

$(BUILD)/wii/rt/boot_stub.o: ../launcher/boot_stub.S
	@mkdir -p $(BUILD)/wii/rt
	$(PPC_CC) $(WII_ARCH) -c $< -o $@

$(BUILD)/$(GAME).elf: $(WII_GEN_OBJECTS) $(WII_RT_OBJECTS) $(WII_INPUT_OBJECTS) $(BUILD)/wii/v3_image_bin.o \
		$(BUILD)/wii/rt/boot_stub.o
	$(PPC_CC) $(WII_ARCH) $^ -L$(LIBOGC)/lib/wii -lasnd -lfat -lwiikeyboard -lwiiuse -lbte -logc -lm \
		-Wl,-Map,$(BUILD)/$(GAME).map -o $@

$(BUILD)/$(GAME).dol: $(BUILD)/$(GAME).elf
	$(DEVKITPRO)/tools/bin/elf2dol $< $@

wii-sync: wii
	mkdir -p "$(SYNC)/apps/$(GAME)"
	cp $(BUILD)/$(GAME).dol "$(SYNC)/apps/$(GAME)/boot.dol"
	cp wii/$(GAME).xml "$(SYNC)/apps/$(GAME)/meta.xml"
	cp ../wii-game/icon.png "$(SYNC)/apps/$(GAME)/icon.png"
