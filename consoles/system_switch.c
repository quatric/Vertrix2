/* The Switch under the shell (console.h): the app in sdmc:/switch/vertrix/, the Joy-Cons and Pro
 * Controllers through libnx's pads, the touch screen, and the homebrew loader's next program
 * (envSetNextLoad), which it starts when this one ends. */
#include <stdio.h>
#include <switch.h>

#include "console.h"
#include "shell.h"

const char shell_platform[] = "the Switch";
const char console_program_extension[] = ".nro";

static PadState pads[2];

void console_init(void)
{
    padConfigureInput(2, HidNpadStyleSet_NpadStandard);
    padInitialize(&pads[0], HidNpadIdType_No1, HidNpadIdType_Handheld);
    padInitialize(&pads[1], HidNpadIdType_No2);
    hidInitializeTouchScreen();
}

const char *console_app_folder(void)
{
    return "sdmc:/switch/vertrix";
}

const char *console_launcher_path(void)
{
    return "sdmc:/switch/vertrix/vertrix.nro";
}

uint64_t console_microseconds(void)
{
    return armTicksToNs(armGetSystemTick()) / 1000u;
}

/* Nintendo's labels to the shell's positions: A is the right face button, B the bottom one. */
static uint32_t buttons(uint64_t held)
{
    static const struct
    {
        uint64_t button;
        uint32_t shell;
    } map[] = {{HidNpadButton_AnyUp, SHELL_PAD_UP},
               {HidNpadButton_AnyDown, SHELL_PAD_DOWN},
               {HidNpadButton_AnyLeft, SHELL_PAD_LEFT},
               {HidNpadButton_AnyRight, SHELL_PAD_RIGHT},
               {HidNpadButton_A, SHELL_PAD_B},
               {HidNpadButton_B, SHELL_PAD_A},
               {HidNpadButton_X, SHELL_PAD_Y},
               {HidNpadButton_Y, SHELL_PAD_X},
               {HidNpadButton_Plus, SHELL_PAD_MENU},
               {HidNpadButton_Minus, SHELL_PAD_OPTIONS},
               {HidNpadButton_L | HidNpadButton_ZL, SHELL_PAD_SHOULDER_L},
               {HidNpadButton_R | HidNpadButton_ZR, SHELL_PAD_SHOULDER_R}};
    uint32_t out = 0;
    for (unsigned i = 0; i < sizeof map / sizeof map[0]; ++i)
    {
        out |= held & map[i].button ? map[i].shell : 0;
    }
    return out;
}

void console_read_input(uint32_t out[2], int *touched, int *touch_x, int *touch_y)
{
    for (int i = 0; i < 2; ++i)
    {
        padUpdate(&pads[i]);
        out[i] = buttons(padGetButtons(&pads[i]));
    }
    HidTouchScreenState touch = {0};
    *touched = hidGetTouchScreenStates(&touch, 1) && touch.count > 0;
    *touch_x = *touched ? (int)touch.touches[0].x : 0;
    *touch_y = *touched ? (int)touch.touches[0].y : 0;
}

int console_chain(const char *path, const char *argument)
{
    if (!envHasNextLoad())
    {
        return 0;
    }
    static char args[768];
    snprintf(args, sizeof args, argument ? "\"%s\" \"%s\"" : "\"%s\"", path, argument);
    return R_SUCCEEDED(envSetNextLoad(path, args));
}

void console_finish(int closing)
{
    (void)closing; /* the loader starts the next program, if one was set, when this one ends */
}
