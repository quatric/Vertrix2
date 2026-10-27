# The launcher (launcher/main.c, unchanged from the Wii's) for a console, on the console shell:
#   make -f consoles/launcher.mk CONSOLE=switch console-program  -> build/switch/launcher/vertrix.nro
# (wiiu: vertrix.wuhb, 3ds: vertrix.3dsx, desktop: vertrix or vertrix.exe). The top Makefile's switch-app (wiiu-app, 3ds-app) runs
# it after writing build/launcher/logo.h; see consoles/README.md.
BUILD ?= build
APP_VERSION := $(shell sed -n 's:.*<version>\(.*\)</version>.*:\1:p' launcher/meta.xml)
CONSOLE_PROGRAM := $(BUILD)/$(CONSOLE)/launcher/vertrix
CONSOLE_OBJ := $(BUILD)/$(CONSOLE)/launcher/obj
CONSOLE_SOURCES := launcher/main.c launcher/music.c consoles/launcher_shell.c
CONSOLE_CFLAGS := -Iconsoles/compat -I$(BUILD)/launcher -DAPP_VERSION=\"$(APP_VERSION)\" \
	-Wno-format-truncation
CONSOLE_DEPS := $(BUILD)/launcher/logo.h $(wildcard launcher/*.h consoles/*.h consoles/compat/*.h)
CONSOLE_TITLE := Vertrix
CONSOLE_BUNDLE := 1
CONSOLE_EXTRA_LIBS := -lmad
include consoles/rules.mk
