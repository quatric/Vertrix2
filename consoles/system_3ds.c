/* The 3DS under the shell (console.h): the app in sdmc:/3ds/vertrix/, the buttons and the Circle
 * Pad, the touch screen, and Luma3DS's homebrew loader for the next program: its hb:ldr service
 * takes the program and its arguments, and the app relaunches itself into it, as the Homebrew
 * Launcher starts a program. */
#include <3ds.h>
#include <stdio.h>
#include <string.h>

#include "console.h"
#include "shell.h"

const char shell_platform[] = "the 3DS";
const char console_program_extension[] = ".3dsx";

/* The rest of the application's memory is the heap the games need (the default keeps 32 MB for
 * the GPU, which the shell uses only for the two screens and the sound). */
u32 __ctru_linear_heap_size = 4u << 20;

void console_init(void)
{
    osSetSpeedupEnable(true);
}

const char *console_app_folder(void)
{
    return "sdmc:/3ds/vertrix";
}

const char *console_launcher_path(void)
{
    return "sdmc:/3ds/vertrix/vertrix.3dsx";
}

uint64_t console_microseconds(void)
{
    const uint64_t ticks = svcGetSystemTick();
    return ticks / SYSCLOCK_ARM11 * 1000000u + ticks % SYSCLOCK_ARM11 * 1000000u / SYSCLOCK_ARM11;
}

/* Nintendo's labels to the shell's positions: A is the right face button, B the bottom one. */
void console_read_input(uint32_t pads[2], int *touched, int *touch_x, int *touch_y)
{
    static const struct
    {
        u32 key;
        uint32_t shell;
    } map[] = {{KEY_UP, SHELL_PAD_UP},
               {KEY_DOWN, SHELL_PAD_DOWN},
               {KEY_LEFT, SHELL_PAD_LEFT},
               {KEY_RIGHT, SHELL_PAD_RIGHT},
               {KEY_A, SHELL_PAD_B},
               {KEY_B, SHELL_PAD_A},
               {KEY_X, SHELL_PAD_Y},
               {KEY_Y, SHELL_PAD_X},
               {KEY_START, SHELL_PAD_MENU},
               {KEY_SELECT, SHELL_PAD_OPTIONS},
               {KEY_L | KEY_ZL, SHELL_PAD_SHOULDER_L},
               {KEY_R | KEY_ZR, SHELL_PAD_SHOULDER_R}};
    hidScanInput();
    const u32 held = hidKeysHeld();
    pads[0] = 0;
    for (unsigned i = 0; i < sizeof map / sizeof map[0]; ++i)
    {
        pads[0] |= held & map[i].key ? map[i].shell : 0;
    }
    pads[1] = 0;
    touchPosition touch = {0};
    *touched = (held & KEY_TOUCH) != 0;
    if (*touched)
    {
        hidTouchRead(&touch);
    }
    *touch_x = touch.px;
    *touch_y = touch.py;
}

static char next_program[256];
/* hbmenu's argument block: the count, then the arguments one after another. */
static u32 next_arguments[0x400 / 4];

int console_chain(const char *path, const char *argument)
{
    if (strncmp(path, "sdmc:/", 6) != 0)
    {
        return 0;
    }
    snprintf(next_program, sizeof next_program, "%s", path + 5); /* "/3ds/...", as hb:ldr takes */
    memset(next_arguments, 0, sizeof next_arguments);
    char *out = (char *)&next_arguments[1];
    const char *end = (const char *)next_arguments + sizeof next_arguments;
    const char *args[2] = {path, argument};
    for (int i = 0; i < 2 && args[i]; ++i)
    {
        const size_t length = strlen(args[i]) + 1;
        if (out + length > end)
        {
            break;
        }
        memcpy(out, args[i], length);
        out += length;
        next_arguments[0]++;
    }
    return 1;
}

static Result hbldr_request(Handle service, u32 command, const void *data, u32 size)
{
    u32 *cmd = getThreadCommandBuffer();
    cmd[0] = IPC_MakeHeader(command, 0, 2);
    cmd[1] = IPC_Desc_StaticBuffer(size, command == 2 ? 0 : 1);
    cmd[2] = (u32)data;
    const Result result = svcSendSyncRequest(service);
    return R_FAILED(result) ? result : (Result)cmd[1];
}

void console_finish(int closing)
{
    if (closing || !next_program[0])
    {
        return;
    }
    Handle service;
    if (R_FAILED(svcConnectToPort(&service, "hb:ldr")))
    {
        return; /* not under Luma3DS's loader (an emulator): back to the HOME Menu */
    }
    /* 2: SetTarget, 3: SetArgv. */
    if (R_SUCCEEDED(hbldr_request(service, 2, next_program, strlen(next_program) + 1)) &&
        R_SUCCEEDED(hbldr_request(service, 3, next_arguments, sizeof next_arguments)))
    {
        aptSetChainloaderToSelf();
    }
    svcCloseHandle(service);
}
