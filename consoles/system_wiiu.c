/* The Wii U under the shell (console.h): the app in sd:/wiiu/apps/vertrix/, the GamePad (with
 * its touch screen) and Pro or Classic Controllers, and Aroma's homebrew loader for the next
 * program: its RPXLoader module's RL_LaunchHomebrew, found at run time, as librpxloader does. */
#include <SDL.h>
#include <coreinit/dynload.h>
#include <coreinit/time.h>
#include <padscore/kpad.h>
#include <padscore/wpad.h>
#include <stdio.h>
#include <string.h>
#include <sysapp/launch.h>
#include <vpad/input.h>

#include "console.h"
#include "shell.h"

const char shell_platform[] = "the Wii U";
const char console_program_extension[] = ".rpx";

/* The SD card as wut mounts it; RPXLoader takes paths from its root. */
#define SD_ROOT "fs:/vol/external01/"

void console_init(void)
{
    KPADInit();
    WPADEnableURCC(1);
}

const char *console_app_folder(void)
{
    return SD_ROOT "wiiu/apps/vertrix";
}

const char *console_launcher_path(void)
{
    return SD_ROOT "wiiu/apps/vertrix/vertrix.wuhb";
}

uint64_t console_microseconds(void)
{
    return (uint64_t)OSTicksToMicroseconds(OSGetSystemTime());
}

typedef struct
{
    uint32_t button, shell;
} Map;

static uint32_t mapped(uint32_t held, const Map *map, unsigned count)
{
    uint32_t out = 0;
    for (unsigned i = 0; i < count; ++i)
    {
        out |= held & map[i].button ? map[i].shell : 0;
    }
    return out;
}

/* Nintendo's labels to the shell's positions: A is the right face button, B the bottom one. */
static const Map gamepad[] = {{VPAD_BUTTON_UP | VPAD_STICK_L_EMULATION_UP, SHELL_PAD_UP},
                              {VPAD_BUTTON_DOWN | VPAD_STICK_L_EMULATION_DOWN, SHELL_PAD_DOWN},
                              {VPAD_BUTTON_LEFT | VPAD_STICK_L_EMULATION_LEFT, SHELL_PAD_LEFT},
                              {VPAD_BUTTON_RIGHT | VPAD_STICK_L_EMULATION_RIGHT, SHELL_PAD_RIGHT},
                              {VPAD_BUTTON_A, SHELL_PAD_B},
                              {VPAD_BUTTON_B, SHELL_PAD_A},
                              {VPAD_BUTTON_X, SHELL_PAD_Y},
                              {VPAD_BUTTON_Y, SHELL_PAD_X},
                              {VPAD_BUTTON_PLUS, SHELL_PAD_MENU},
                              {VPAD_BUTTON_MINUS, SHELL_PAD_OPTIONS},
                              {VPAD_BUTTON_L | VPAD_BUTTON_ZL, SHELL_PAD_SHOULDER_L},
                              {VPAD_BUTTON_R | VPAD_BUTTON_ZR, SHELL_PAD_SHOULDER_R}};

/* The Pro Controller's buttons are the Classic Controller's. */
static const Map classic[] = {
    {WPAD_CLASSIC_BUTTON_UP, SHELL_PAD_UP},
    {WPAD_CLASSIC_BUTTON_DOWN, SHELL_PAD_DOWN},
    {WPAD_CLASSIC_BUTTON_LEFT, SHELL_PAD_LEFT},
    {WPAD_CLASSIC_BUTTON_RIGHT, SHELL_PAD_RIGHT},
    {WPAD_CLASSIC_BUTTON_A, SHELL_PAD_B},
    {WPAD_CLASSIC_BUTTON_B, SHELL_PAD_A},
    {WPAD_CLASSIC_BUTTON_X, SHELL_PAD_Y},
    {WPAD_CLASSIC_BUTTON_Y, SHELL_PAD_X},
    {WPAD_CLASSIC_BUTTON_PLUS, SHELL_PAD_MENU},
    {WPAD_CLASSIC_BUTTON_MINUS, SHELL_PAD_OPTIONS},
    {WPAD_CLASSIC_BUTTON_L | WPAD_CLASSIC_BUTTON_ZL, SHELL_PAD_SHOULDER_L},
    {WPAD_CLASSIC_BUTTON_R | WPAD_CLASSIC_BUTTON_ZR, SHELL_PAD_SHOULDER_R}};

/* A controller on a Wii Remote channel, its stick as the D-pad. */
static uint32_t remote(KPADChan channel)
{
    KPADStatus status;
    KPADError error;
    memset(&status, 0, sizeof status);
    if (KPADReadEx(channel, &status, 1, &error) < 1 || error != KPAD_ERROR_OK)
    {
        return 0;
    }
    uint32_t held;
    KPADVec2D stick;
    if (status.extensionType == WPAD_EXT_PRO_CONTROLLER)
    {
        held = status.pro.hold;
        stick = status.pro.leftStick;
    }
    else if (status.extensionType == WPAD_EXT_CLASSIC ||
             status.extensionType == WPAD_EXT_MPLUS_CLASSIC)
    {
        held = status.classic.hold;
        stick = status.classic.leftStick;
    }
    else
    {
        return 0;
    }
    uint32_t out = mapped(held, classic, sizeof classic / sizeof classic[0]);
    out |= stick.y > 0.5f ? SHELL_PAD_UP : stick.y < -0.5f ? SHELL_PAD_DOWN : 0;
    out |= stick.x < -0.5f ? SHELL_PAD_LEFT : stick.x > 0.5f ? SHELL_PAD_RIGHT : 0;
    return out;
}

void console_read_input(uint32_t pads[2], int *touched, int *touch_x, int *touch_y)
{
    static uint32_t gamepad_held;
    static VPADTouchData touch;
    VPADStatus status;
    VPADReadError error;
    if (VPADRead(VPAD_CHAN_0, &status, 1, &error) > 0 && error == VPAD_READ_SUCCESS)
    {
        gamepad_held = mapped(status.hold, gamepad, sizeof gamepad / sizeof gamepad[0]);
        VPADGetTPCalibratedPoint(VPAD_CHAN_0, &touch, &status.tpNormal);
    }
    pads[0] = gamepad_held | remote(WPAD_CHAN_0);
    pads[1] = remote(WPAD_CHAN_1);
    /* Calibrated points are in 1280x720, the screen SDL draws (and mirrors on the GamePad). */
    *touched = touch.touched && touch.validity == VPAD_VALID;
    *touch_x = touch.x;
    *touch_y = touch.y;
}

static char next_program[256];

int console_chain(const char *path, const char *argument)
{
    (void)argument; /* RPXLoader passes no arguments: each game uses its folder in the app's */
    if (strncmp(path, SD_ROOT, strlen(SD_ROOT)) != 0)
    {
        return 0;
    }
    snprintf(next_program, sizeof next_program, "%s", path + strlen(SD_ROOT));
    return 1;
}

/* RPXLoader's RL_LaunchHomebrew: the bundle or RPX, from the SD card's root. */
static int launch_homebrew(const char *path)
{
    OSDynLoad_Module module;
    int (*launch)(const char *) = NULL;
    if (OSDynLoad_Acquire("homebrew_rpx_loader", &module) != OS_DYNLOAD_OK)
    {
        return 0;
    }
    if (OSDynLoad_FindExport(module, OS_DYNLOAD_EXPORT_FUNC, "RL_LaunchHomebrew",
                             (void **)&launch) != OS_DYNLOAD_OK ||
        !launch)
    {
        return 0;
    }
    return launch(path) == 0;
}

void console_finish(int closing)
{
    if (closing)
    {
        return;
    }
    if (!next_program[0] || !launch_homebrew(next_program))
    {
        SYSLaunchMenu();
    }
    /* The system now closes the app: run its loop (SDL's) until it says so. */
    for (;;)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                return;
            }
        }
        SDL_Delay(16);
    }
}
