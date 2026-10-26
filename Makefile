# Recovered native library only. The full Wii application is still in recovery.
DEVKITPPC ?= /opt/devkitpro/devkitPPC
BUILD ?= build
PPC_CC := $(DEVKITPPC)/bin/powerpc-eabi-gcc
PPC_AR := $(DEVKITPPC)/bin/powerpc-eabi-ar
LIBOGC ?= /opt/devkitpro/libogc
CFLAGS := -mcpu=750 -meabi -mhard-float -O2 -std=c11 -Wall -Wextra -Werror
PORTABLE_SOURCES := $(filter-out source/wii_%.c,$(wildcard source/*.c))
OBJECTS := $(patsubst source/%.c,$(BUILD)/%.o,$(PORTABLE_SOURCES))

.PHONY: all format check-format wii-textures
all: $(BUILD)/libvertrix-recovered.a

wii-textures: $(BUILD)/libvertrix-wii-textures.a

$(BUILD)/wii_texture.o: source/wii_texture.c $(wildcard source/*.h) | $(BUILD)
	$(PPC_CC) $(CFLAGS) -DGEKKO -DHW_RVL -D__wii__ -I$(LIBOGC)/include -c $< -o $@

$(BUILD)/libvertrix-wii-textures.a: $(BUILD)/wii_texture.o $(BUILD)/texture.o
	$(PPC_AR) rcs $@ $^

$(BUILD):
	mkdir -p $@

$(BUILD)/%.o: source/%.c $(wildcard source/*.h) | $(BUILD)
	$(PPC_CC) $(CFLAGS) -c $< -o $@

$(BUILD)/libvertrix-recovered.a: $(OBJECTS)
	rm -f $@
	$(PPC_AR) rcs $@ $^

format:
	clang-format -i source/*.c source/*.h

check-format:
	clang-format --dry-run --Werror source/*.c source/*.h

.PHONY: wii-archive
wii-archive: $(BUILD)/libvertrix-wii-archive.a

$(BUILD)/wii_archive.o: source/wii_archive.c $(wildcard source/*.h) | $(BUILD)
	$(PPC_CC) $(CFLAGS) -DGEKKO -DHW_RVL -D__wii__ -I$(LIBOGC)/include -c $< -o $@

$(BUILD)/libvertrix-wii-archive.a: $(BUILD)/wii_archive.o $(BUILD)/vf.o $(BUILD)/games.o
	$(PPC_AR) rcs $@ $^

.PHONY: wii-assets
wii-assets: $(BUILD)/libvertrix-wii-assets.a

$(BUILD)/wii_assets.o: source/wii_assets.c $(wildcard source/*.h) | $(BUILD)
	$(PPC_CC) $(CFLAGS) -DGEKKO -DHW_RVL -D__wii__ -I$(LIBOGC)/include -c $< -o $@

$(BUILD)/libvertrix-wii-assets.a: $(BUILD)/wii_assets.o $(BUILD)/wii_texture.o $(BUILD)/texture.o $(BUILD)/assets.o $(BUILD)/image.o $(BUILD)/vf.o
	$(PPC_AR) rcs $@ $^

.PHONY: wii-audio
wii-audio: $(BUILD)/libvertrix-wii-audio.a

$(BUILD)/wii_audio.o: source/wii_audio.c $(wildcard source/*.h) | $(BUILD)
	$(PPC_CC) $(CFLAGS) -DGEKKO -DHW_RVL -D__wii__ -I$(LIBOGC)/include -c $< -o $@

$(BUILD)/libvertrix-wii-audio.a: $(BUILD)/wii_audio.o $(BUILD)/audio.o $(BUILD)/vf.o
	$(PPC_AR) rcs $@ $^

.PHONY: wii-mp3
wii-mp3: $(BUILD)/libvertrix-wii-mp3.a

$(BUILD)/wii_mp3.o: source/wii_mp3.c $(wildcard source/*.h) | $(BUILD)
	$(PPC_CC) $(CFLAGS) -DGEKKO -DHW_RVL -D__wii__ -I$(LIBOGC)/include -c $< -o $@

$(BUILD)/libvertrix-wii-mp3.a: $(BUILD)/wii_mp3.o $(BUILD)/vf.o
	$(PPC_AR) rcs $@ $^

.PHONY: wii-music
wii-music: $(BUILD)/libvertrix-wii-music.a

$(BUILD)/wii_music.o: source/wii_music.c $(wildcard source/*.h) | $(BUILD)
	$(PPC_CC) $(CFLAGS) -DGEKKO -DHW_RVL -D__wii__ -I$(LIBOGC)/include -c $< -o $@

$(BUILD)/libvertrix-wii-music.a: $(BUILD)/wii_music.o $(BUILD)/sequencer.o $(BUILD)/mixer.o $(BUILD)/xm.o $(BUILD)/audio.o $(BUILD)/vf.o
	$(PPC_AR) rcs $@ $^

.PHONY: wii-frames
wii-frames: $(BUILD)/libvertrix-wii-frames.a

$(BUILD)/wii_frame_texture.o: source/wii_frame_texture.c $(wildcard source/*.h) | $(BUILD)
	$(PPC_CC) $(CFLAGS) -DGEKKO -DHW_RVL -D__wii__ -I$(LIBOGC)/include -c $< -o $@

$(BUILD)/libvertrix-wii-frames.a: $(BUILD)/wii_frame_texture.o $(BUILD)/wii_texture.o $(BUILD)/frame_texture.o $(BUILD)/texture.o
	$(PPC_AR) rcs $@ $^

.PHONY: wii-frame-draw
wii-frame-draw: $(BUILD)/libvertrix-wii-frame-draw.a

$(BUILD)/wii_frame_draw.o: source/wii_frame_draw.c $(wildcard source/*.h) | $(BUILD)
	$(PPC_CC) $(CFLAGS) -DGEKKO -DHW_RVL -D__wii__ -I$(LIBOGC)/include -c $< -o $@

$(BUILD)/libvertrix-wii-frame-draw.a: $(BUILD)/wii_frame_draw.o $(BUILD)/wii_frame_texture.o $(BUILD)/wii_texture.o $(BUILD)/frame_texture.o $(BUILD)/texture.o
	$(PPC_AR) rcs $@ $^

.PHONY: wii-frame-present
wii-frame-present: $(BUILD)/libvertrix-wii-frame-present.a

$(BUILD)/wii_frame_present.o: source/wii_frame_present.c $(wildcard source/*.h) | $(BUILD)
	$(PPC_CC) $(CFLAGS) -DGEKKO -DHW_RVL -D__wii__ -I$(LIBOGC)/include -c $< -o $@

$(BUILD)/libvertrix-wii-frame-present.a: $(BUILD)/wii_frame_present.o $(BUILD)/wii_frame_draw.o $(BUILD)/wii_frame_texture.o $(BUILD)/wii_texture.o $(BUILD)/frame_texture.o $(BUILD)/texture.o
	$(PPC_AR) rcs $@ $^

.PHONY: wii-video
wii-video: $(BUILD)/libvertrix-wii-video.a

$(BUILD)/wii_video.o: source/wii_video.c $(wildcard source/*.h) | $(BUILD)
	$(PPC_CC) $(CFLAGS) -DGEKKO -DHW_RVL -D__wii__ -I$(LIBOGC)/include -c $< -o $@

$(BUILD)/libvertrix-wii-video.a: $(BUILD)/wii_video.o $(BUILD)/wii_frame_present.o $(BUILD)/wii_frame_draw.o $(BUILD)/wii_frame_texture.o $(BUILD)/wii_texture.o $(BUILD)/frame_texture.o $(BUILD)/texture.o
	$(PPC_AR) rcs $@ $^

# Diagnostic executable; the full game application remains in recovery.
.PHONY: wii-platform-check
wii-platform-check: $(BUILD)/vertrix2-platform-check.dol

$(BUILD)/wii_platform_check.o: tools/wii_platform_check.c $(wildcard source/*.h) | $(BUILD)
	$(PPC_CC) $(CFLAGS) -DGEKKO -DHW_RVL -D__wii__ -I$(LIBOGC)/include -Isource -c $< -o $@

$(BUILD)/vertrix2-platform-check.elf: $(BUILD)/wii_platform_check.o $(BUILD)/libvertrix-wii-video.a $(BUILD)/libvertrix-wii-archive.a $(BUILD)/libvertrix-recovered.a
	$(PPC_CC) -mrvl $(CFLAGS) $^ -L$(LIBOGC)/lib/wii -lfat -lwiiuse -lbte -logc -lm -Wl,-Map,$(BUILD)/vertrix2-platform-check.map -o $@

$(BUILD)/vertrix2-platform-check.dol: $(BUILD)/vertrix2-platform-check.elf
	/opt/devkitpro/tools/bin/elf2dol $< $@

# Input from every controller, keyboard and mouse (libwiiinput), and the update check on the
# releases page (libwiiupdate); both are submodules (git submodule update --init).
INPUT_SOURCES := $(wildcard libwiiinput/source/*.c)
INPUT_OBJECTS := $(patsubst libwiiinput/source/%.c,$(BUILD)/libwiiinput/%.o,$(INPUT_SOURCES))
WII_INCLUDES := -Ilibwiiinput/include -Ilibwiiupdate/include
APP_VERSION := $(shell sed -n 's:.*<version>\(.*\)</version>.*:\1:p' wii-game/meta.xml)

$(BUILD)/libwiiinput/%.o: libwiiinput/source/%.c libwiiinput/source/libinput_internal.h libwiiinput/include/input_wii.h
	@mkdir -p $(dir $@)
	$(PPC_CC) -O2 -Wall -Wextra -DGEKKO -DHW_RVL -mrvl -mcpu=750 -meabi -mhard-float -Ilibwiiinput/include -I$(LIBOGC)/include -c $< -o $@

$(BUILD)/libwiiinput.a: $(INPUT_OBJECTS)
	$(PPC_AR) rcs $@ $^

libwiiupdate/lib/libwiiupdate.a: $(wildcard libwiiupdate/source/* libwiiupdate/include/* libwiiupdate/config/*)
	$(MAKE) -C libwiiupdate DEVKITPPC=$(DEVKITPPC) LIBOGC=$(LIBOGC)

# Playable single-player board composed from the recovered routines.
.PHONY: wii-game
wii-game: $(BUILD)/vertrix2.dol

$(BUILD)/wii_game.o: tools/wii_game.c $(wildcard source/*.h) | $(BUILD)
	$(PPC_CC) $(CFLAGS) -DGEKKO -DHW_RVL -D__wii__ -I$(LIBOGC)/include -Isource -c $< -o $@

$(BUILD)/wii_game_art.o: source/wii_game_art.c $(wildcard source/*.h) | $(BUILD)
	$(PPC_CC) $(CFLAGS) -DGEKKO -DHW_RVL -D__wii__ -I$(LIBOGC)/include -I/opt/devkitpro/portlibs/ppc/include -c $< -o $@

$(BUILD)/wii_input.o: source/wii_input.c $(wildcard source/*.h) | $(BUILD)
	$(PPC_CC) $(CFLAGS) -DGEKKO -DHW_RVL -D__wii__ -I$(LIBOGC)/include $(WII_INCLUDES) -c $< -o $@

$(BUILD)/wii_sfx.o: source/wii_sfx.c $(wildcard source/*.h) | $(BUILD)
	$(PPC_CC) $(CFLAGS) -DGEKKO -DHW_RVL -D__wii__ -I$(LIBOGC)/include -c $< -o $@

$(BUILD)/vertrix2.elf: $(BUILD)/wii_game.o $(BUILD)/wii_game_art.o $(BUILD)/wii_input.o $(BUILD)/wii_music.o $(BUILD)/wii_sfx.o $(BUILD)/libvertrix-wii-music-deps.a $(BUILD)/libvertrix-wii-video.a $(BUILD)/libvertrix-wii-archive.a $(BUILD)/libvertrix-recovered.a $(BUILD)/libwiiinput.a
	$(PPC_CC) -mrvl $(CFLAGS) $^ -L$(LIBOGC)/lib/wii -L/opt/devkitpro/portlibs/ppc/lib -ljpeg -lmad -lasnd -lfat -lwiikeyboard -lwiiuse -lbte -logc -lm -Wl,-Map,$(BUILD)/vertrix2.map -o $@

$(BUILD)/vertrix2.dol: $(BUILD)/vertrix2.elf
	/opt/devkitpro/tools/bin/elf2dol $< $@

# The sequencer, mixer and XM readers are already in libvertrix-recovered.a.
$(BUILD)/libvertrix-wii-music-deps.a: $(BUILD)/libvertrix-recovered.a
	cp $< $@

# The lifted screen builders run on the Wii through the dispatcher (not the game loop).
.PHONY: wii-lifted-probe
wii-lifted-probe: $(BUILD)/vertrix2-lifted-probe.dol

$(BUILD)/image.bin: Vertrix2.exe tools/dump_image.py | $(BUILD)
	python3 tools/dump_image.py $@ $<

$(BUILD)/image_bin.o: $(BUILD)/image.bin
	cd $(BUILD) && /opt/devkitpro/tools/bin/bin2s -H image_bin.h image.bin > image_bin.s
	$(PPC_CC) -c $(BUILD)/image_bin.s -o $@

$(BUILD)/wii_lifted_probe.o: tools/wii_lifted_probe.c $(wildcard source/*.h) | $(BUILD)
	$(PPC_CC) $(CFLAGS) -DGEKKO -DHW_RVL -D__wii__ -I$(LIBOGC)/include -Isource -c $< -o $@

$(BUILD)/vertrix2-lifted-probe.elf: $(BUILD)/wii_lifted_probe.o $(BUILD)/image_bin.o $(BUILD)/libvertrix-recovered.a
	$(PPC_CC) -mrvl $(CFLAGS) $^ -L$(LIBOGC)/lib/wii -lwiiuse -lbte -logc -lm -o $@

$(BUILD)/vertrix2-lifted-probe.dol: $(BUILD)/vertrix2-lifted-probe.elf
	/opt/devkitpro/tools/bin/elf2dol $< $@

# Fill a Dolphin WiiSDSync folder (or an SD card root) with the app folder the Wii build reads:
# make wii-sync SYNC=/path/to/Load/WiiSDSync
SYNC ?= ../dolphin-user/Load/WiiSDSync
wii-sync: $(BUILD)/vertrix2.dol
	mkdir -p "$(SYNC)/apps/vertrix2"
	cp $(BUILD)/vertrix2.dol "$(SYNC)/apps/vertrix2"/boot.dol
	cp wii-game/meta.xml "$(SYNC)/apps/vertrix2"/meta.xml
	cp wii-game/icon.png "$(SYNC)/apps/vertrix2"/icon.png
	cp hardware-check/Vertrix2.vf "$(SYNC)/apps/vertrix2"/Vertrix2.vf

# The recompiled original running on the Wii host (startup, loader, banks, frame loop; SD archive
# data): every routine of the original runs as a native port through the dispatcher.
.PHONY: wii-recomp wii-sync-recomp
wii-recomp: $(BUILD)/vertrix2-recomp.dol

$(BUILD)/wii_recomp_game.o: tools/wii_recomp_game.c tools/jpeg_decode.h wii-game/meta.xml $(wildcard source/*.h) | $(BUILD)
	$(PPC_CC) $(CFLAGS) -DGEKKO -DHW_RVL -D__wii__ -DAPP_VERSION=\"$(APP_VERSION)\" -I$(LIBOGC)/include -I/opt/devkitpro/portlibs/ppc/include $(WII_INCLUDES) -Ilauncher -Isource -Itools -c $< -o $@

$(BUILD)/vertrix2-recomp.elf: $(BUILD)/wii_recomp_game.o $(BUILD)/launcher/app.o $(BUILD)/launcher/boot_stub.o $(BUILD)/image_bin.o $(BUILD)/libvertrix-wii-audio.a $(BUILD)/libvertrix-wii-video.a $(BUILD)/libvertrix-wii-archive.a $(BUILD)/libvertrix-recovered.a $(BUILD)/libwiiinput.a libwiiupdate/lib/libwiiupdate.a
	$(PPC_CC) -mrvl $(CFLAGS) $^ -L$(LIBOGC)/lib/wii -L/opt/devkitpro/portlibs/ppc/lib -ljpeg -lasnd -lfat -lwiikeyboard -lwiiuse -lbte -logc -lm -o $@

$(BUILD)/vertrix2-recomp.dol: $(BUILD)/vertrix2-recomp.elf
	/opt/devkitpro/tools/bin/elf2dol $< $@

wii-sync-recomp: $(BUILD)/vertrix2-recomp.dol
	mkdir -p "$(SYNC)/apps/vertrix2"
	cp $(BUILD)/vertrix2-recomp.dol "$(SYNC)/apps/vertrix2"/boot.dol
	cp wii-game/meta.xml "$(SYNC)/apps/vertrix2"/meta.xml
	cp wii-game/icon.png "$(SYNC)/apps/vertrix2"/icon.png
	cp hardware-check/Vertrix2.vf "$(SYNC)/apps/vertrix2"/Vertrix2.vf

# The former names, from when the routines still ran as lifted code.
.PHONY: wii-lifted-game wii-sync-lifted
wii-lifted-game: wii-recomp
wii-sync-lifted: wii-sync-recomp

# The Wii recomp's startup and frame loop on the build machine, writing frames as PPM:
# build/host_game build/image.bin hardware-check/Vertrix2.vf OUT_DIR [ticks] [step_ms] [shot_every]
HOST_CC ?= cc
HOST_JPEG ?= /opt/homebrew
.PHONY: host-game
host-game: $(BUILD)/host_game

$(BUILD)/host_game: tools/host_game.c tools/jpeg_decode.h $(filter-out source/wii_%.c,$(wildcard source/*.c)) $(wildcard source/*.h) | $(BUILD)
	$(HOST_CC) -std=gnu11 -O2 -w -Isource -Itools -I$(HOST_JPEG)/include tools/host_game.c $(filter-out source/wii_%.c,$(wildcard source/*.c)) -L$(HOST_JPEG)/lib -ljpeg -lm -o $@

# --- One app for every game --------------------------------------------------------------------
# The launcher (launcher/) is sd:/apps/vertrix/boot.dol: it starts the four games from
# sd:/apps/vertrix/games/ and plays the MP3 albums in sd:/apps/vertrix/music/. Every DOL is
# packed with FIX94's dolxz (the tools/dolxz submodule). See launcher/README.md.
#
#   make wii-app V1_EXE=.../VERTRIX.EXE V12_EXE=.../Vertrix2.exe V3_EXE=.../Vertrix3.exe
#                [V20_EXE=Vertrix2.exe]  # v2.0, recompiled whole like v1.2 and Vertrix 3
#   make wii-app-sync SYNC=/path/to/sd     # copies build/app/apps/vertrix/ there
#   make wii-app-zip                       # build/vertrix-wii.zip, for the releases page
#
# The zip carries the games' data files; the music is not part of the build.
# Debug launchers for Dolphin: LAUNCHER_DEBUG='-DLAUNCHER_SCRIPT="\"1 shot; 2 down; 3 a\""'
# (and -DLAUNCHER_BACK_SCRIPT for the start after a game); rebuild with make -B.
PYTHON ?= python3
V1_EXE ?= VERTRIX.EXE
V3_EXE ?= Vertrix3.exe
V12_EXE ?= Vertrix2-v12.exe
V20_EXE ?= Vertrix2.exe
LAUNCHER_VERSION := $(shell sed -n 's:.*<version>\(.*\)</version>.*:\1:p' launcher/meta.xml)
LAUNCHER_SOURCES := launcher/main.c launcher/gfx.c launcher/gfx_wii.c launcher/music.c launcher/app.c
LAUNCHER_OBJECTS := $(patsubst launcher/%.c,$(BUILD)/launcher/%.o,$(LAUNCHER_SOURCES))
APP_DIR := $(BUILD)/app/apps/vertrix
DOLXZ := $(BUILD)/dolxz/dolxz

$(BUILD)/launcher/logo.h: wii-game/icon.png launcher/png2c.py
	@mkdir -p $(dir $@)
	$(PYTHON) launcher/png2c.py $< logo $@

$(BUILD)/launcher/%.o: launcher/%.c $(wildcard launcher/*.h) $(BUILD)/launcher/logo.h
	@mkdir -p $(dir $@)
	$(PPC_CC) $(CFLAGS) -Wno-format-truncation -mrvl -DGEKKO -DHW_RVL -D__wii__ -DAPP_VERSION=\"$(LAUNCHER_VERSION)\" $(LAUNCHER_DEBUG) -I$(LIBOGC)/include -I/opt/devkitpro/portlibs/ppc/include $(WII_INCLUDES) -I$(BUILD)/launcher -c $< -o $@

$(BUILD)/launcher/boot_stub.o: launcher/boot_stub.S
	@mkdir -p $(dir $@)
	$(PPC_CC) -mrvl -mcpu=750 -meabi -mhard-float -c $< -o $@

$(BUILD)/launcher.elf: $(LAUNCHER_OBJECTS) $(BUILD)/launcher/boot_stub.o $(BUILD)/libwiiinput.a libwiiupdate/lib/libwiiupdate.a
	$(PPC_CC) -mrvl $(CFLAGS) $^ -L$(LIBOGC)/lib/wii -L/opt/devkitpro/portlibs/ppc/lib -lmad -lasnd -lfat -lwiikeyboard -lwiiuse -lbte -logc -lm -Wl,-Map,$(BUILD)/launcher.map -o $@

$(BUILD)/launcher.dol: $(BUILD)/launcher.elf
	/opt/devkitpro/tools/bin/elf2dol $< $@

$(DOLXZ): tools/build_dolxz.sh $(wildcard tools/dolxz/*.c tools/dolxz/loader/*.c tools/dolxz/loader/wii/*)
	sh tools/build_dolxz.sh $(BUILD)/dolxz /opt/devkitpro

.PHONY: wii-launcher wii-app wii-app-games wii-app-sync wii-app-zip
wii-launcher: $(BUILD)/launcher.dol

# The games through their own makefiles (each regenerates only when its recompiler changed).
wii-app-games:
	$(MAKE) -C vertrix1 V1_EXE=$(abspath $(V1_EXE)) PYTHON=$(PYTHON) wii
	$(MAKE) -C vertrix3 BUILD=../build/v20 GAME=vertrix2 V3_EXE=$(abspath $(V20_EXE)) PYTHON=$(PYTHON) wii
	$(MAKE) -C vertrix3 BUILD=../build/v12 GAME=vertrix2-v12 V3_EXE=$(abspath $(V12_EXE)) PYTHON=$(PYTHON) wii
	$(MAKE) -C vertrix3 V3_EXE=$(abspath $(V3_EXE)) PYTHON=$(PYTHON) wii

wii-app: $(BUILD)/launcher.dol $(DOLXZ) wii-app-games
	mkdir -p $(APP_DIR)/games
	$(DOLXZ) $(BUILD)/launcher.dol $(APP_DIR)/boot.dol -wii >/dev/null
	$(DOLXZ) $(BUILD)/v1/vertrix.dol $(APP_DIR)/games/vertrix1.dol -wii >/dev/null
	$(DOLXZ) $(BUILD)/v12/vertrix2-v12.dol $(APP_DIR)/games/vertrix2-v12.dol -wii >/dev/null
	$(DOLXZ) $(BUILD)/v20/vertrix2.dol $(APP_DIR)/games/vertrix2.dol -wii >/dev/null
	$(DOLXZ) $(BUILD)/v3/vertrix3.dol $(APP_DIR)/games/vertrix3.dol -wii >/dev/null
	$(PYTHON) tools/dol_align.py $(APP_DIR)/boot.dol $(APP_DIR)/games/*.dol
	cp launcher/meta.xml $(APP_DIR)/meta.xml
	cp wii-game/icon.png $(APP_DIR)/icon.png
	cp launcher/README.md $(APP_DIR)/README.md
	@ls -l $(APP_DIR) $(APP_DIR)/games

wii-app-sync: wii-app
	mkdir -p "$(SYNC)/apps/vertrix/games"
	cp $(APP_DIR)/boot.dol $(APP_DIR)/meta.xml $(APP_DIR)/icon.png $(APP_DIR)/README.md "$(SYNC)/apps/vertrix/"
	cp $(APP_DIR)/games/*.dol "$(SYNC)/apps/vertrix/games/"

# The games' own files (Vertrix2.vf and the rest), staged from beside the executables.
GAME_DATA := $(BUILD)/game-data
# MUSIC= a folder of albums (folders of MP3 files), copied into the Wii and console zips' music/
# and the Mac app (tools/fetch_mac_inputs.sh downloads them to inputs/music).
MUSIC ?=
MAC_MUSIC ?= $(MUSIC)
.PHONY: game-data
game-data:
	tools/stage_game_data.sh $(GAME_DATA) $(V1_EXE) $(V12_EXE) $(V20_EXE) $(V3_EXE)

wii-app-zip: wii-app game-data
	rm -f $(BUILD)/vertrix-wii.zip
	rm -rf $(BUILD)/app-zip && mkdir -p $(BUILD)/app-zip/apps
	cp -R $(APP_DIR) $(BUILD)/app-zip/apps/vertrix
	cp -R $(GAME_DATA)/. $(BUILD)/app-zip/apps/vertrix/
	$(if $(MUSIC),mkdir -p $(BUILD)/app-zip/apps/vertrix/music && cp -R "$(MUSIC)"/. $(BUILD)/app-zip/apps/vertrix/music/)
	cd $(BUILD)/app-zip && zip -qr ../vertrix-wii.zip apps/vertrix
	@ls -l $(BUILD)/vertrix-wii.zip

# --- the Mac: one app for the four games ----------------------------------------------------------
#   make mac-app V1_EXE=.../VERTRIX.EXE V12_EXE=.../Vertrix2.exe V3_EXE=.../Vertrix3.exe \
#                [V20_EXE=Vertrix2.exe] [MAC_MUSIC=folder of albums]     # build/mac/Vertrix.app
#   make mac-app-zip                                                       # build/vertrix-mac.zip
# Vertrix.app (mac/launcher.m) lists the games and plays the soundtrack; each game is its own app
# in Contents/Helpers (vertrix1/Makefile, vertrix3/Makefile: mac). The games' files are in
# Contents/Resources/Data; each game copies its own into ~/Library/Application Support/Vertrix
# the first time (mac/README.md). MAC_MUSIC copies albums (folders of MP3 files) into the app.
MAC_ARCHS ?= arm64 x86_64
MAC_MIN ?= 11.0
MAC_APP := $(BUILD)/mac/Vertrix.app
MAC_VERSION := $(shell sed -n 's:.*<version>\(.*\)</version>.*:\1:p' launcher/meta.xml)
MAC_ARCH_FLAGS := $(addprefix -arch ,$(MAC_ARCHS)) -mmacosx-version-min=$(MAC_MIN)
MAC_HELPERS := $(BUILD)/v1/mac/vertrix1.app $(BUILD)/v12/mac/vertrix2-v12.app \
	$(BUILD)/v20/mac/vertrix2.app $(BUILD)/v3/mac/vertrix3.app

.PHONY: mac-app mac-app-games mac-app-zip
mac-app-games:
	$(MAKE) -C vertrix1 V1_EXE=$(abspath $(V1_EXE)) PYTHON=$(PYTHON) MAC_ARCHS="$(MAC_ARCHS)" mac
	$(MAKE) -C vertrix3 BUILD=../build/v20 GAME=vertrix2 V3_EXE=$(abspath $(V20_EXE)) PYTHON=$(PYTHON) MAC_ARCHS="$(MAC_ARCHS)" mac
	$(MAKE) -C vertrix3 BUILD=../build/v12 GAME=vertrix2-v12 V3_EXE=$(abspath $(V12_EXE)) PYTHON=$(PYTHON) MAC_ARCHS="$(MAC_ARCHS)" mac
	$(MAKE) -C vertrix3 V3_EXE=$(abspath $(V3_EXE)) PYTHON=$(PYTHON) MAC_ARCHS="$(MAC_ARCHS)" mac

$(BUILD)/mac/launcher/Vertrix: mac/launcher.m mac/data.m shell/vertrix_games.c $(wildcard mac/*.h shell/*.h)
	@mkdir -p $(dir $@)
	clang $(MAC_ARCH_FLAGS) -O2 -fobjc-arc -Wall -Imac -Ishell mac/launcher.m mac/data.m \
		shell/vertrix_games.c -framework Cocoa -framework AVFoundation -o $@

# The app's icon is Vertrix 3's, from its executable.
$(BUILD)/mac/launcher/AppIcon.icns: mac/icon.py $(V3_EXE)
	@mkdir -p $(dir $@)
	$(PYTHON) -I mac/icon.py $(V3_EXE) $@

mac-app: mac-app-games game-data $(BUILD)/mac/launcher/Vertrix $(BUILD)/mac/launcher/AppIcon.icns
	rm -rf $(MAC_APP)
	mkdir -p $(MAC_APP)/Contents/MacOS $(MAC_APP)/Contents/Resources $(MAC_APP)/Contents/Helpers
	sed -e 's|@NAME@|Vertrix|g' -e 's|@EXECUTABLE@|Vertrix|g' \
		-e 's|@IDENTIFIER@|com.quatric.vertrix|g' -e 's|@VERSION@|$(MAC_VERSION)|g' \
		-e 's|@MIN@|$(MAC_MIN)|g' mac/Info.plist.in > $(MAC_APP)/Contents/Info.plist
	cp $(BUILD)/mac/launcher/Vertrix $(MAC_APP)/Contents/MacOS/
	cp $(BUILD)/mac/launcher/AppIcon.icns $(MAC_APP)/Contents/Resources/
	cp wii-game/icon.png $(MAC_APP)/Contents/Resources/Logo.png
	cp mac/README.md $(MAC_APP)/Contents/Resources/README.md
	cp -R $(MAC_HELPERS) $(MAC_APP)/Contents/Helpers/
	mkdir -p $(MAC_APP)/Contents/Resources/Data
	cp -R $(GAME_DATA)/. $(MAC_APP)/Contents/Resources/Data/
	$(if $(MAC_MUSIC),cp -R "$(MAC_MUSIC)" $(MAC_APP)/Contents/Resources/Music)
	for a in $(MAC_APP)/Contents/Helpers/*.app; do codesign --force --sign - "$$a"; done
	codesign --force --sign - $(MAC_APP)
	@du -sh $(MAC_APP) $(MAC_APP)/Contents/Helpers/*.app

mac-app-zip: mac-app
	rm -f $(BUILD)/vertrix-mac.zip
	cd $(BUILD)/mac && ditto -c -k --keepParent Vertrix.app ../vertrix-mac.zip
	@ls -l $(BUILD)/vertrix-mac.zip

# --- the consoles: the launcher and the four games for the Switch, the Wii U and the 3DS ---------
#   make switch-app V1_EXE=.../VERTRIX.EXE V12_EXE=.../Vertrix2.exe V3_EXE=.../Vertrix3.exe \
#                   [V20_EXE=Vertrix2.exe]          # build/switch/sd/switch/vertrix/
#   make switch-app-zip                             # build/vertrix-switch.zip
# and wiiu-app (build/wiiu/sd/wiiu/apps/vertrix/), 3ds-app (build/3ds/sd/3ds/vertrix/) likewise.
# The launcher is the Wii's (consoles/launcher.mk); each game is built by its own Makefile on the
# console shell (consoles/rules.mk). The games' data files are in the zip.
CONSOLE_SD_switch := switch/vertrix
CONSOLE_SD_wiiu := wiiu/apps/vertrix
CONSOLE_SD_3ds := 3ds/vertrix
CONSOLE_GAME_switch := .nro
CONSOLE_GAME_wiiu := .rpx
CONSOLE_GAME_3ds := .3dsx
CONSOLE_LAUNCHER_switch := .nro
CONSOLE_LAUNCHER_wiiu := .wuhb
CONSOLE_LAUNCHER_3ds := .3dsx

define console_app
.PHONY: $(1)-app $(1)-app-games $(1)-launcher $(1)-app-zip
$(1)-app-games:
	$$(MAKE) -C vertrix1 V1_EXE=$$(abspath $$(V1_EXE)) PYTHON=$$(PYTHON) $(1)
	$$(MAKE) -C vertrix3 BUILD=../build/v20 GAME=vertrix2 V3_EXE=$$(abspath $$(V20_EXE)) PYTHON=$$(PYTHON) $(1)
	$$(MAKE) -C vertrix3 BUILD=../build/v12 GAME=vertrix2-v12 V3_EXE=$$(abspath $$(V12_EXE)) PYTHON=$$(PYTHON) $(1)
	$$(MAKE) -C vertrix3 V3_EXE=$$(abspath $$(V3_EXE)) PYTHON=$$(PYTHON) $(1)

$(1)-launcher: $$(BUILD)/launcher/logo.h
	$$(MAKE) -f consoles/launcher.mk CONSOLE=$(1) BUILD=$$(BUILD) PYTHON=$$(PYTHON) console-program

$(1)-app: $(1)-app-games $(1)-launcher game-data
	rm -rf $$(BUILD)/$(1)/sd
	mkdir -p $$(BUILD)/$(1)/sd/$$(CONSOLE_SD_$(1))/games
	cp $$(BUILD)/$(1)/launcher/vertrix$$(CONSOLE_LAUNCHER_$(1)) $$(BUILD)/$(1)/sd/$$(CONSOLE_SD_$(1))/
	cp $$(BUILD)/v1/$(1)/vertrix1$$(CONSOLE_GAME_$(1)) $$(BUILD)/v12/$(1)/vertrix2-v12$$(CONSOLE_GAME_$(1)) \
		$$(BUILD)/v20/$(1)/vertrix2$$(CONSOLE_GAME_$(1)) $$(BUILD)/v3/$(1)/vertrix3$$(CONSOLE_GAME_$(1)) \
		$$(BUILD)/$(1)/sd/$$(CONSOLE_SD_$(1))/games/
	cp -R $$(GAME_DATA)/. $$(BUILD)/$(1)/sd/$$(CONSOLE_SD_$(1))/
	$$(if $$(MUSIC),mkdir -p $$(BUILD)/$(1)/sd/$$(CONSOLE_SD_$(1))/music && cp -R "$$(MUSIC)"/. $$(BUILD)/$(1)/sd/$$(CONSOLE_SD_$(1))/music/)
	cp consoles/README.md $$(BUILD)/$(1)/sd/$$(CONSOLE_SD_$(1))/README.md
	@ls -l $$(BUILD)/$(1)/sd/$$(CONSOLE_SD_$(1)) $$(BUILD)/$(1)/sd/$$(CONSOLE_SD_$(1))/games

$(1)-app-zip: $(1)-app
	rm -f $$(BUILD)/vertrix-$(1).zip
	cd $$(BUILD)/$(1)/sd && zip -qr ../../vertrix-$(1).zip .
	@ls -l $$(BUILD)/vertrix-$(1).zip
endef

$(foreach console,switch wiiu 3ds,$(eval $(call console_app,$(console))))

# --- the 3DS as installable titles (.cia) -------------------------------------------------------
#   make 3ds-app-zip ... ; make 3ds-cia             # build/3ds/cia/*.cia, build/vertrix-3ds-cia.zip
# Each game's title carries its data files in its RomFS (the game copies them to the card the first
# time it starts). One title per program, packed from the .elf that 3ds-app built (tools/make_cia.sh; needs makerom
# and bannertool on the PATH). A game started from the menu is still the .3dsx beside it.
CIA_DIR := $(BUILD)/3ds/cia
CIA_VERSION := $(shell sed -n 's:.*<version>\(.*\)</version>.*:\1:p' launcher/meta.xml)

# The menu's title carries the soundtrack (MUSIC=) as music/ in its RomFS.
CIA_MUSIC := $(if $(MUSIC),$(BUILD)/cia-music)
# cia(name, title, unique id, product code, system mode, elf)
define cia
CIA_ALL += $(CIA_DIR)/$(1).cia
$(CIA_DIR)/$(1).cia: $(if $(7),$(if $(wildcard $(GAME_DATA)),,game-data))
	@mkdir -p $(CIA_DIR)
	$(if $(filter $(BUILD)/cia-music,$(7)),rm -rf $(7) && mkdir -p $(7)/music && cp -R "$(MUSIC)"/. $(7)/music/)
	PYTHON=$(PYTHON) tools/make_cia.sh $(6) $$@ "$(2)" $(3) $(4) $(5) $(CIA_VERSION) $(7)
endef

$(eval $(call cia,vertrix,Vertrix,0xf7a10,CTR-P-VRTX,64MB,$(BUILD)/3ds/launcher/vertrix.elf,$(CIA_MUSIC)))
$(eval $(call cia,vertrix1,Vertrix (1997),0xf7a11,CTR-P-VRT1,80MB,$(BUILD)/v1/3ds/vertrix1.elf,$(GAME_DATA)/vertrix1))
$(eval $(call cia,vertrix2-v12,Vertrix 2 v1.2,0xf7a12,CTR-P-VRT2,80MB,$(BUILD)/v12/3ds/vertrix2-v12.elf,$(GAME_DATA)/vertrix2-v12))
$(eval $(call cia,vertrix2,Vertrix 2,0xf7a13,CTR-P-VRT3,80MB,$(BUILD)/v20/3ds/vertrix2.elf,$(GAME_DATA)/vertrix2))
$(eval $(call cia,vertrix3,Vertrix 3,0xf7a14,CTR-P-VRT4,80MB,$(BUILD)/v3/3ds/vertrix3.elf,$(GAME_DATA)/vertrix3))

.PHONY: 3ds-cia 3ds-cia-zip
3ds-cia:
	rm -f $(CIA_ALL)
	$(MAKE) $(CIA_ALL) PYTHON=$(PYTHON)
	@ls -l $(CIA_DIR)

3ds-cia-zip: 3ds-cia
	rm -f $(BUILD)/vertrix-3ds-cia.zip
	cd $(CIA_DIR) && zip -qj ../../vertrix-3ds-cia.zip *.cia
	@ls -l $(BUILD)/vertrix-3ds-cia.zip

# --- every app: the Wii, the Mac and the consoles ------------------------------------------------
#   make apps-zip V1_EXE=.../VERTRIX.EXE V12_EXE=.../Vertrix2.exe V3_EXE=.../Vertrix3.exe \
#                 [V20_EXE=Vertrix2.exe]                          # build/vertrix-<app>.zip each
# The Mac only on a Mac. APPS="wii mac" picks some. One after another: they share the games' build.
APPS ?= wii $(if $(filter Darwin,$(shell uname -s)),mac) switch wiiu 3ds

.PHONY: apps apps-zip
apps:
	for a in $(APPS); do $(MAKE) $$a-app || exit 1; done

apps-zip:
	for a in $(APPS); do $(MAKE) $$a-app-zip || exit 1; done
