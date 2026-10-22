# One program for a console (consoles/README.md): its objects, its link, and its file for the
# system's homebrew loader. vertrix1/Makefile and vertrix3/Makefile include it for the games, the
# top Makefile for the launcher. Before including it, set
#
#   CONSOLE            switch, wiiu or 3ds
#   CONSOLE_PROGRAM    the program's path without its extension
#   CONSOLE_OBJ        the folder for its objects
#   CONSOLE_SOURCES    its C files (any folder); CONSOLE_GEN_SOURCES the recompiler's
#   CONSOLE_CFLAGS     its includes, defines and warnings
#   CONSOLE_DEPS       what every object waits for (headers, the recompiler's stamp)
#   CONSOLE_IMAGE      the image built into it (v3_image.bin, v1_image.bin), if any
#   CONSOLE_TITLE      its name in the system's menu
#   CONSOLE_BUNDLE     (Wii U) set for the launcher: a .wuhb with its icon, else a plain .rpx
#
# and, for a debug build, CONSOLE_DEBUG (for example -DSHELL_SCRIPT='"3 b; 5 down"', see
# shell_common.c; rebuild shell_common.o for it to take).
# Then `console-program` builds $(CONSOLE_PROGRAM)$(CONSOLE_EXT).
DEVKITPRO ?= /opt/devkitpro
PORTLIBS := $(DEVKITPRO)/portlibs
CONSOLE_ROOT := $(or $(patsubst %/consoles/,%,$(filter %/consoles/,$(dir $(lastword $(MAKEFILE_LIST))))),.)
PYTHON ?= python3
CONSOLE_VERSION ?= $(shell sed -n 's:.*<version>\(.*\)</version>.*:\1:p' $(CONSOLE_ROOT)/launcher/meta.xml)
CONSOLE_AUTHOR := quatric
CONSOLE_LOGO := $(CONSOLE_ROOT)/wii-game/icon.png
CONSOLE_ART := $(PYTHON) $(CONSOLE_ROOT)/tools/console_art.py $(CONSOLE_LOGO)
TOOLS := $(DEVKITPRO)/tools/bin

ifeq ($(CONSOLE),switch)
CONSOLE_CC := $(DEVKITPRO)/devkitA64/bin/aarch64-none-elf-gcc
CONSOLE_ARCH := -march=armv8-a+crc+crypto -mtune=cortex-a57 -mtp=soft -fPIE
CONSOLE_SYSTEM := -D__SWITCH__ -ftls-model=local-exec -isystem $(DEVKITPRO)/libnx/include \
	-I$(PORTLIBS)/switch/include -I$(PORTLIBS)/switch/include/SDL2
CONSOLE_LDFLAGS := -specs=$(DEVKITPRO)/libnx/switch.specs -L$(PORTLIBS)/switch/lib \
	-L$(DEVKITPRO)/libnx/lib
CONSOLE_LIBS := -lmad -lSDL2 -lEGL -lstdc++ -lglapi -ldrm_nouveau -lnx -lpthread -lm
CONSOLE_SHELL := shell_sdl.c system_switch.c
CONSOLE_EXT := .nro
else ifeq ($(CONSOLE),wiiu)
CONSOLE_CC := $(DEVKITPRO)/devkitPPC/bin/powerpc-eabi-gcc
CONSOLE_ARCH := -mcpu=750 -meabi -mhard-float
CONSOLE_SYSTEM := -D__WIIU__ -D__WUT__ -I$(DEVKITPRO)/wut/include -I$(PORTLIBS)/wiiu/include \
	-I$(PORTLIBS)/wiiu/include/SDL2 -I$(PORTLIBS)/ppc/include
CONSOLE_LDFLAGS := -specs=$(DEVKITPRO)/wut/share/wut.specs -L$(PORTLIBS)/wiiu/lib \
	-L$(PORTLIBS)/ppc/lib -L$(DEVKITPRO)/wut/lib
CONSOLE_LIBS := -lmad -lSDL2 -lwut -lm
CONSOLE_SHELL := shell_sdl.c system_wiiu.c
CONSOLE_EXT := $(if $(CONSOLE_BUNDLE),.wuhb,.rpx)
else ifeq ($(CONSOLE),3ds)
CONSOLE_CC := $(DEVKITPRO)/devkitARM/bin/arm-none-eabi-gcc
CONSOLE_ARCH := -march=armv6k -mtune=mpcore -mfloat-abi=hard -mtp=soft
CONSOLE_SYSTEM := -D__3DS__ -mword-relocations -I$(DEVKITPRO)/libctru/include -I$(PORTLIBS)/3ds/include
CONSOLE_LDFLAGS := -specs=3dsx.specs -L$(PORTLIBS)/3ds/lib -L$(DEVKITPRO)/libctru/lib
CONSOLE_LIBS := -lmad -lctru -lm
CONSOLE_SHELL := shell_3ds.c system_3ds.c
CONSOLE_EXT := .3dsx
else
$(error CONSOLE is switch, wiiu or 3ds)
endif

# Every console's program has the shell, its error screen (the launcher's canvas and font) and
# the system's part.
CONSOLE_SOURCES += $(CONSOLE_ROOT)/consoles/shell_common.c $(CONSOLE_ROOT)/launcher/gfx.c \
	$(CONSOLE_ROOT)/consoles/font_8x16.c $(addprefix $(CONSOLE_ROOT)/consoles/,$(CONSOLE_SHELL))
CONSOLE_COMMON := $(CONSOLE_ARCH) $(CONSOLE_SYSTEM) $(CONSOLE_DEBUG) -std=gnu11 -O2 -fno-strict-aliasing \
	-I$(CONSOLE_ROOT)/shell -I$(CONSOLE_ROOT)/consoles -I$(CONSOLE_ROOT)/launcher
CONSOLE_QUIET := -Wno-parentheses-equality -Wno-unused-label -Wno-unused-variable \
	-Wno-unused-but-set-variable -Wno-unused-function

# An object per source, named after its file (no two sources of a program share a name).
console_object = $(CONSOLE_OBJ)/$(notdir $(basename $(1))).o

define console_compile
$(call console_object,$(1)): $(1) $(CONSOLE_DEPS)
	@mkdir -p $$(dir $$@)
	$(CONSOLE_CC) $(CONSOLE_COMMON) $(2) -c $$< -o $$@
endef

$(foreach s,$(CONSOLE_GEN_SOURCES),$(eval $(call console_compile,$(s),$(CONSOLE_QUIET) $(CONSOLE_CFLAGS))))
$(foreach s,$(CONSOLE_SOURCES),$(eval $(call console_compile,$(s),-Wall $(CONSOLE_QUIET) $(CONSOLE_CFLAGS))))

CONSOLE_OBJECTS := $(foreach s,$(CONSOLE_GEN_SOURCES) $(CONSOLE_SOURCES),$(call console_object,$(s)))

# The image, as v3_image_bin[] and v3_image_bin_size (shell_common.c's shell_resource). bin2s's
# .note.GNU-stack section is dropped: elf2rpl (the Wii U) cannot place it.
ifneq ($(CONSOLE_IMAGE),)
CONSOLE_IMAGE_OBJECT := $(CONSOLE_OBJ)/$(basename $(notdir $(CONSOLE_IMAGE)))_bin.o
$(CONSOLE_IMAGE_OBJECT): $(CONSOLE_IMAGE)
	@mkdir -p $(CONSOLE_OBJ)
	cp $< $(CONSOLE_OBJ)/$(notdir $<)
	cd $(CONSOLE_OBJ) && $(TOOLS)/bin2s $(notdir $<) | grep -v '\.note\.GNU-stack' \
		> $(basename $(notdir $<))_bin.s
	$(CONSOLE_CC) $(CONSOLE_ARCH) -c $(CONSOLE_OBJ)/$(basename $(notdir $<))_bin.s -o $@
CONSOLE_OBJECTS += $(CONSOLE_IMAGE_OBJECT)
endif

$(CONSOLE_PROGRAM).elf: $(CONSOLE_OBJECTS)
	$(CONSOLE_CC) $(CONSOLE_ARCH) $(CONSOLE_LDFLAGS) $^ $(CONSOLE_LIBS) \
		-Wl,-Map,$(CONSOLE_PROGRAM).map -o $@

$(CONSOLE_OBJ)/art/%: $(CONSOLE_LOGO) $(CONSOLE_ROOT)/tools/console_art.py
	@mkdir -p $(dir $@)
	$(CONSOLE_ART) $(basename $*) $@

.PHONY: console-program
console-program: $(CONSOLE_PROGRAM)$(CONSOLE_EXT)

$(CONSOLE_PROGRAM).nro: $(CONSOLE_PROGRAM).elf $(CONSOLE_OBJ)/art/switch-icon.jpg
	$(TOOLS)/nacptool --create "$(CONSOLE_TITLE)" "$(CONSOLE_AUTHOR)" "$(CONSOLE_VERSION)" \
		$(CONSOLE_PROGRAM).nacp
	$(TOOLS)/elf2nro $< $@ --icon=$(CONSOLE_OBJ)/art/switch-icon.jpg --nacp=$(CONSOLE_PROGRAM).nacp

$(CONSOLE_PROGRAM).rpx: $(CONSOLE_PROGRAM).elf
	$(TOOLS)/elf2rpl $< $@

$(CONSOLE_PROGRAM).wuhb: $(CONSOLE_PROGRAM).rpx $(CONSOLE_OBJ)/art/wiiu-icon.png \
		$(CONSOLE_OBJ)/art/wiiu-tv.png $(CONSOLE_OBJ)/art/wiiu-drc.png
	$(TOOLS)/wuhbtool $< $@ --name="$(CONSOLE_TITLE)" --short-name="$(CONSOLE_TITLE)" \
		--author="$(CONSOLE_AUTHOR)" --icon=$(CONSOLE_OBJ)/art/wiiu-icon.png \
		--tv-image=$(CONSOLE_OBJ)/art/wiiu-tv.png --drc-image=$(CONSOLE_OBJ)/art/wiiu-drc.png

$(CONSOLE_PROGRAM).3dsx: $(CONSOLE_PROGRAM).elf $(CONSOLE_OBJ)/art/3ds-icon.png
	$(TOOLS)/smdhtool --create "$(CONSOLE_TITLE)" "Recompiled from the original" \
		"$(CONSOLE_AUTHOR)" $(CONSOLE_OBJ)/art/3ds-icon.png $(CONSOLE_PROGRAM).smdh
	$(TOOLS)/3dsxtool $< $@ --smdh=$(CONSOLE_PROGRAM).smdh
