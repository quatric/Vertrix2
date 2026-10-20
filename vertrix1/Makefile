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
