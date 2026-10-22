# Vertrix (1997), recompiled from VERTRIX.EXE (see vertrix1/README.md).
# make -C vertrix1 V1_EXE=/path/to/VERTRIX.EXE host     -> build/v1/v1_host
PYTHON ?= python3
V1_EXE ?= VERTRIX.EXE
BUILD ?= ../build/v1
GEN := $(BUILD)/gen
HOST_CC ?= cc
HOST_CFLAGS ?= -std=gnu11 -O1 -g -DV3_HISTORY -Wno-parentheses-equality -Wno-unused-label \
	-Wno-unused-variable -Wno-unused-but-set-variable
RUNTIME := runtime/machine.c runtime/dos.c runtime/ports.c runtime/vga.c runtime/sb.c \
	runtime/shared.c
HEADERS := $(wildcard runtime/*.h) ../vertrix3/runtime/cpu.c ../vertrix3/runtime/memory.c
INCLUDES := -Iruntime -I$(GEN)

.PHONY: host generate link
host: $(GEN)/stamp
	$(MAKE) link

link: $(BUILD)/v1_host

$(GEN)/stamp: recomp.py ../vertrix3/recomp.py
	mkdir -p $(GEN)
	$(PYTHON) recomp.py $(V1_EXE) $(GEN)
	touch $@

generate: $(GEN)/stamp

GEN_SOURCES = $(wildcard $(GEN)/v1_code_*.c) $(GEN)/v3_table.c
GEN_OBJECTS = $(patsubst $(GEN)/%.c,$(BUILD)/host/%.o,$(GEN_SOURCES))
HOST_RT_OBJECTS = $(patsubst runtime/%.c,$(BUILD)/host/rt/%.o,$(RUNTIME)) $(BUILD)/host/rt/host_main.o

$(BUILD)/host/%.o: $(GEN)/%.c $(GEN)/stamp runtime/cpu.h runtime/dos.h
	@mkdir -p $(BUILD)/host
	$(HOST_CC) $(HOST_CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD)/host/rt/%.o: runtime/%.c $(HEADERS)
	@mkdir -p $(BUILD)/host/rt
	$(HOST_CC) $(HOST_CFLAGS) -Wall $(INCLUDES) -c $< -o $@

$(BUILD)/host/rt/host_main.o: host/host_main.c $(HEADERS)
	@mkdir -p $(BUILD)/host/rt
	$(HOST_CC) $(HOST_CFLAGS) -Wall $(INCLUDES) -c $< -o $@

$(BUILD)/v1_host: $(GEN_OBJECTS) $(HOST_RT_OBJECTS)
	$(HOST_CC) $(GEN_OBJECTS) $(HOST_RT_OBJECTS) -lm -o $@

# --- the game's data ---------------------------------------------------------------------------
# make -C vertrix1 V1_EXE=/path/to/VERTRIX.EXE PYTHON=... assets  -> build/v1-assets/index.html
V1_BIN1 ?= $(dir $(V1_EXE))BIN1.BIN

.PHONY: assets
assets:
	$(PYTHON) -I assets.py $(V1_EXE) $(V1_BIN1) $(BUILD)-assets

# --- the Wii ------------------------------------------------------------------------------------
# make -C vertrix1 V1_EXE=/path/to/VERTRIX.EXE wii      -> build/v1/vertrix.dol
# make -C vertrix1 V1_EXE=... wii-sync SYNC=/path/to/sd  -> apps/vertrix1/ (boot.dol, meta.xml, icon.png)
# The game's own files are not part of the build: copy the release into apps/vertrix1/. In the
# one-app build (make wii-app at the top) the launcher passes apps/vertrix/vertrix1/ instead.
DEVKITPRO ?= /opt/devkitpro
PPC_CC := $(DEVKITPRO)/devkitPPC/bin/powerpc-eabi-gcc
LIBOGC ?= $(DEVKITPRO)/libogc
WII_ARCH := -mrvl -mcpu=750 -meabi -mhard-float -DGEKKO -DHW_RVL -D__wii__
# The DPMI memory the game can have: it asks for about 4 MB.
WII_HEAP ?= 0x00800000u
WII_DEFINES := -DV3_PAGED -DV1_HEAP_SIZE=$(WII_HEAP) $(WII_DEBUG)
# Debug builds for Dolphin: WII_DEBUG='-DV1_WII_SHOTS=70 -DV1_WII_SCRIPT="\"3 key 1c 1; ...\""'
WII_CFLAGS := $(WII_ARCH) $(WII_DEFINES) -std=gnu11 -O2 -fno-strict-aliasing \
	-Wno-parentheses-equality -Wno-unused-label -Wno-unused-variable -Wno-unused-but-set-variable \
	-Wno-unused-function -I$(LIBOGC)/include
WII_SHARED := ../source/wii_audio.c ../source/audio.c ../source/vf.c ../launcher/app.c
WII_INPUT := $(wildcard ../libwiiinput/source/*.c)
WII_INCLUDES := -Iruntime -I$(GEN) -I$(BUILD)/wii -I../source -I../libwiiinput/include -I../launcher
WII_GEN_OBJECTS = $(patsubst $(GEN)/%.c,$(BUILD)/wii/%.o,$(GEN_SOURCES))
WII_RT_OBJECTS := $(patsubst %.c,$(BUILD)/wii/rt/%.o,$(notdir $(RUNTIME) wii/wii_main.c $(WII_SHARED)))
WII_INPUT_OBJECTS := $(patsubst %.c,$(BUILD)/wii/input/%.o,$(notdir $(WII_INPUT)))
SYNC ?= ../../dolphin-user/Load/WiiSDSync

.PHONY: wii wii-link wii-sync
wii: $(GEN)/stamp
	$(MAKE) wii-link

wii-link: $(BUILD)/vertrix.dol

$(BUILD)/wii/%.o: $(GEN)/%.c $(GEN)/stamp runtime/cpu.h runtime/dos.h
	@mkdir -p $(BUILD)/wii
	$(PPC_CC) $(WII_CFLAGS) $(WII_INCLUDES) -c $< -o $@

$(BUILD)/wii/v1_image_bin.h $(BUILD)/wii/v1_image_bin.o: $(GEN)/stamp
	@mkdir -p $(BUILD)/wii
	cp $(GEN)/v1_image.bin $(BUILD)/wii/v1_image.bin
	cd $(BUILD)/wii && $(DEVKITPRO)/tools/bin/bin2s -H v1_image_bin.h v1_image.bin > v1_image_bin.s
	$(PPC_CC) $(WII_ARCH) -c $(BUILD)/wii/v1_image_bin.s -o $(BUILD)/wii/v1_image_bin.o

vpath %.c runtime wii ../source ../libwiiinput/source ../launcher

$(BUILD)/wii/rt/%.o: %.c $(HEADERS) $(BUILD)/wii/v1_image_bin.h
	@mkdir -p $(BUILD)/wii/rt
	$(PPC_CC) $(WII_CFLAGS) -Wall $(WII_INCLUDES) -c $< -o $@

$(BUILD)/wii/input/%.o: %.c
	@mkdir -p $(BUILD)/wii/input
	$(PPC_CC) $(WII_ARCH) -O2 -I$(LIBOGC)/include -I../libwiiinput/include -c $< -o $@

$(BUILD)/wii/rt/boot_stub.o: ../launcher/boot_stub.S
	@mkdir -p $(BUILD)/wii/rt
	$(PPC_CC) $(WII_ARCH) -c $< -o $@

$(BUILD)/vertrix.elf: $(WII_GEN_OBJECTS) $(WII_RT_OBJECTS) $(WII_INPUT_OBJECTS) $(BUILD)/wii/v1_image_bin.o $(BUILD)/wii/rt/boot_stub.o
	$(PPC_CC) $(WII_ARCH) $^ -L$(LIBOGC)/lib/wii -lasnd -lfat -lwiikeyboard -lwiiuse -lbte -logc -lm \
		-Wl,-Map,$(BUILD)/vertrix.map -o $@

$(BUILD)/vertrix.dol: $(BUILD)/vertrix.elf
	$(DEVKITPRO)/tools/bin/elf2dol $< $@

wii-sync: wii
	mkdir -p "$(SYNC)/apps/vertrix1"
	cp $(BUILD)/vertrix.dol "$(SYNC)/apps/vertrix1/boot.dol"
	cp wii/vertrix.xml "$(SYNC)/apps/vertrix1/meta.xml"
	cp ../wii-game/icon.png "$(SYNC)/apps/vertrix1/icon.png"

# --- the Mac ------------------------------------------------------------------------------------
# make -C vertrix1 V1_EXE=/path/to/VERTRIX.EXE PYTHON=... mac  -> build/v1/mac/vertrix1.app
# The app is one of the games of Vertrix.app (make mac-app at the top, mac/README.md); on its own
# it reads the release from ~/Library/Application Support/Vertrix/vertrix1/. MAC_ARCHS picks the
# architectures (a universal app by default); the generated code is the same C as the Wii's.
MAC_ARCHS ?= arm64 x86_64
MAC_MIN ?= 11.0
MAC_VERSION ?= $(shell sed -n 's:.*<version>\(.*\)</version>.*:\1:p' ../launcher/meta.xml)
MAC_ARCH_FLAGS := $(addprefix -arch ,$(MAC_ARCHS)) -mmacosx-version-min=$(MAC_MIN)
MAC_CC ?= clang
MAC_CFLAGS := $(MAC_ARCH_FLAGS) -std=gnu11 -O2 -fno-strict-aliasing -Wno-parentheses-equality \
	-Wno-unused-label -Wno-unused-variable -Wno-unused-but-set-variable -Wno-unused-function
MAC_RUNTIME := $(RUNTIME) mac/mac_main.c ../mac/vertrix_games.c
MAC_OBJC := ../mac/shell.m ../mac/data.m
MAC_INCLUDES := -Iruntime -I$(GEN) -I../mac
MAC_GEN_OBJECTS = $(patsubst $(GEN)/%.c,$(BUILD)/mac/%.o,$(GEN_SOURCES))
MAC_RT_OBJECTS := $(patsubst %.c,$(BUILD)/mac/rt/%.o,$(notdir $(MAC_RUNTIME))) \
	$(patsubst %.m,$(BUILD)/mac/rt/%.o,$(notdir $(MAC_OBJC)))
MAC_APP := $(BUILD)/mac/vertrix1.app
MAC_FRAMEWORKS := -framework Cocoa -framework QuartzCore -framework GameController \
	-framework AudioToolbox

.PHONY: mac mac-link
mac: $(GEN)/stamp
	$(MAKE) mac-link

mac-link: $(MAC_APP)/Contents/MacOS/vertrix1

$(BUILD)/mac/%.o: $(GEN)/%.c $(GEN)/stamp runtime/cpu.h runtime/dos.h
	@mkdir -p $(BUILD)/mac
	$(MAC_CC) $(MAC_CFLAGS) $(INCLUDES) -c $< -o $@

vpath %.c mac ../mac
vpath %.m ../mac

$(BUILD)/mac/rt/%.o: %.c $(HEADERS) $(wildcard ../mac/*.h)
	@mkdir -p $(BUILD)/mac/rt
	$(MAC_CC) $(MAC_CFLAGS) -Wall $(MAC_INCLUDES) -c $< -o $@

$(BUILD)/mac/rt/%.o: %.m $(wildcard ../mac/*.h)
	@mkdir -p $(BUILD)/mac/rt
	$(MAC_CC) $(MAC_ARCH_FLAGS) -O2 -fobjc-arc -Wall $(MAC_INCLUDES) -c $< -o $@

$(BUILD)/mac/vertrix1: $(MAC_GEN_OBJECTS) $(MAC_RT_OBJECTS)
	$(MAC_CC) $(MAC_ARCH_FLAGS) $^ $(MAC_FRAMEWORKS) -o $@

# The DOS executable has no icon: the Vertrix logo the Wii apps show.
$(BUILD)/mac/AppIcon.icns: ../mac/icon.py ../wii-game/icon.png
	@mkdir -p $(BUILD)/mac
	$(PYTHON) -I ../mac/icon.py ../wii-game/icon.png $@

# The bundle: the program, the image it loads and the icon.
$(MAC_APP)/Contents/MacOS/vertrix1: $(BUILD)/mac/vertrix1 $(BUILD)/mac/AppIcon.icns ../mac/Info.plist.in
	@mkdir -p $(MAC_APP)/Contents/MacOS $(MAC_APP)/Contents/Resources
	sed -e 's|@NAME@|Vertrix|g' -e 's|@EXECUTABLE@|vertrix1|g' \
		-e 's|@IDENTIFIER@|com.quatric.vertrix.vertrix1|g' -e 's|@VERSION@|$(MAC_VERSION)|g' \
		-e 's|@MIN@|$(MAC_MIN)|g' ../mac/Info.plist.in > $(MAC_APP)/Contents/Info.plist
	cp $(GEN)/v1_image.bin $(BUILD)/mac/AppIcon.icns $(MAC_APP)/Contents/Resources/
	cp $(BUILD)/mac/vertrix1 $@
	codesign --force --sign - $(MAC_APP)
