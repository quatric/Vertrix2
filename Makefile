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

$(BUILD)/libvertrix-wii-archive.a: $(BUILD)/wii_archive.o $(BUILD)/vf.o
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

# Playable single-player board composed from the recovered routines.
.PHONY: wii-game
wii-game: $(BUILD)/vertrix2.dol

$(BUILD)/wii_game.o: tools/wii_game.c $(wildcard source/*.h) | $(BUILD)
	$(PPC_CC) $(CFLAGS) -DGEKKO -DHW_RVL -D__wii__ -I$(LIBOGC)/include -Isource -c $< -o $@

$(BUILD)/wii_game_art.o: source/wii_game_art.c $(wildcard source/*.h) | $(BUILD)
	$(PPC_CC) $(CFLAGS) -DGEKKO -DHW_RVL -D__wii__ -I$(LIBOGC)/include -I/opt/devkitpro/portlibs/ppc/include -c $< -o $@

$(BUILD)/wii_input.o: source/wii_input.c $(wildcard source/*.h) | $(BUILD)
	$(PPC_CC) $(CFLAGS) -DGEKKO -DHW_RVL -D__wii__ -I$(LIBOGC)/include -c $< -o $@

$(BUILD)/wii_sfx.o: source/wii_sfx.c $(wildcard source/*.h) | $(BUILD)
	$(PPC_CC) $(CFLAGS) -DGEKKO -DHW_RVL -D__wii__ -I$(LIBOGC)/include -c $< -o $@

$(BUILD)/vertrix2.elf: $(BUILD)/wii_game.o $(BUILD)/wii_game_art.o $(BUILD)/wii_input.o $(BUILD)/wii_music.o $(BUILD)/wii_sfx.o $(BUILD)/libvertrix-wii-music-deps.a $(BUILD)/libvertrix-wii-video.a $(BUILD)/libvertrix-wii-archive.a $(BUILD)/libvertrix-recovered.a
	$(PPC_CC) -mrvl $(CFLAGS) $^ -L$(LIBOGC)/lib/wii -L/opt/devkitpro/portlibs/ppc/lib -ljpeg -lmad -lasnd -lfat -lwiiuse -lbte -logc -lm -Wl,-Map,$(BUILD)/vertrix2.map -o $@

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
