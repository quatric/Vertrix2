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
