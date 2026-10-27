/* The desktop under the shell (console.h): Linux and Windows (and the Mac, for testing), on the
 * console shell's SDL 2 layer. The app is one folder that holds the launcher, the games in
 * games/ and each game's own files, as on a console's SD card; started from anywhere, it finds
 * that folder next to its program (VERTRIX_HOME names another). The controllers are SDL's game
 * controllers, and a program starts the next one by running it. */
#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <process.h>
#else
#include <spawn.h>
extern char **environ;
#endif

#include "console.h"
#include "shell.h"

const char shell_platform[] = "the PC";
const char console_program_extension[] = VERTRIX_EXE_EXT;

static char app_folder[512];
static char launcher_path[600];
static SDL_GameController *pads[2];
static unsigned scans;

static void slashes(char *text)
{
    for (; *text; ++text)
    {
        if (*text == '\\')
        {
            *text = '/';
        }
    }
}

static void trim_slashes(char *text)
{
    size_t length = strlen(text);
    while (length > 1 && text[length - 1] == '/')
    {
        text[--length] = 0;
    }
}

void console_init(void)
{
    SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER);
}

/* VERTRIX_HOME, else the folder of the program (or the one above, for a game in games/). */
const char *console_app_folder(void)
{
    if (app_folder[0])
    {
        return app_folder;
    }
    const char *home = getenv("VERTRIX_HOME");
    if (home && *home)
    {
        snprintf(app_folder, sizeof app_folder, "%s", home);
    }
    else
    {
        char *base = SDL_GetBasePath();
        snprintf(app_folder, sizeof app_folder, "%s", base ? base : ".");
        SDL_free(base);
    }
    slashes(app_folder);
    trim_slashes(app_folder);
    const size_t length = strlen(app_folder);
    if (length >= 6 && strcmp(app_folder + length - 6, "/games") == 0)
    {
        app_folder[length - 6] = 0;
    }
    return app_folder;
}

const char *console_launcher_path(void)
{
    if (!launcher_path[0])
    {
        snprintf(launcher_path, sizeof launcher_path, "%s/vertrix%s", console_app_folder(),
                 console_program_extension);
    }
    return launcher_path;
}

uint64_t console_microseconds(void)
{
    return SDL_GetPerformanceCounter() * 1000000u / SDL_GetPerformanceFrequency();
}

/* The first two connected controllers, looked for again about once a second. */
static void find_pads(void)
{
    for (int slot = 0; slot < 2; ++slot)
    {
        if (pads[slot] && !SDL_GameControllerGetAttached(pads[slot]))
        {
            SDL_GameControllerClose(pads[slot]);
            pads[slot] = NULL;
        }
    }
    for (int index = 0; index < SDL_NumJoysticks(); ++index)
    {
        if (!SDL_IsGameController(index))
        {
            continue;
        }
        SDL_GameController *found =
            SDL_GameControllerFromInstanceID(SDL_JoystickGetDeviceInstanceID(index));
        if (found)
        {
            continue; /* already open */
        }
        for (int slot = 0; slot < 2; ++slot)
        {
            if (!pads[slot])
            {
                pads[slot] = SDL_GameControllerOpen(index);
                break;
            }
        }
    }
}

static uint32_t buttons(SDL_GameController *pad)
{
    static const struct
    {
        SDL_GameControllerButton button;
        uint32_t shell;
    } map[] = {{SDL_CONTROLLER_BUTTON_DPAD_UP, SHELL_PAD_UP},
               {SDL_CONTROLLER_BUTTON_DPAD_DOWN, SHELL_PAD_DOWN},
               {SDL_CONTROLLER_BUTTON_DPAD_LEFT, SHELL_PAD_LEFT},
               {SDL_CONTROLLER_BUTTON_DPAD_RIGHT, SHELL_PAD_RIGHT},
               {SDL_CONTROLLER_BUTTON_A, SHELL_PAD_A},
               {SDL_CONTROLLER_BUTTON_B, SHELL_PAD_B},
               {SDL_CONTROLLER_BUTTON_X, SHELL_PAD_X},
               {SDL_CONTROLLER_BUTTON_Y, SHELL_PAD_Y},
               {SDL_CONTROLLER_BUTTON_START, SHELL_PAD_MENU},
               {SDL_CONTROLLER_BUTTON_BACK, SHELL_PAD_OPTIONS},
               {SDL_CONTROLLER_BUTTON_LEFTSHOULDER, SHELL_PAD_SHOULDER_L},
               {SDL_CONTROLLER_BUTTON_RIGHTSHOULDER, SHELL_PAD_SHOULDER_R}};
    uint32_t out = 0;
    for (unsigned i = 0; i < sizeof map / sizeof map[0]; ++i)
    {
        out |= SDL_GameControllerGetButton(pad, map[i].button) ? map[i].shell : 0;
    }
    const int x = SDL_GameControllerGetAxis(pad, SDL_CONTROLLER_AXIS_LEFTX);
    const int y = SDL_GameControllerGetAxis(pad, SDL_CONTROLLER_AXIS_LEFTY);
    if (x < -16000)
    {
        out |= SHELL_PAD_LEFT;
    }
    if (x > 16000)
    {
        out |= SHELL_PAD_RIGHT;
    }
    if (y < -16000)
    {
        out |= SHELL_PAD_UP;
    }
    if (y > 16000)
    {
        out |= SHELL_PAD_DOWN;
    }
    if (SDL_GameControllerGetAxis(pad, SDL_CONTROLLER_AXIS_TRIGGERLEFT) > 16000)
    {
        out |= SHELL_PAD_SHOULDER_L;
    }
    if (SDL_GameControllerGetAxis(pad, SDL_CONTROLLER_AXIS_TRIGGERRIGHT) > 16000)
    {
        out |= SHELL_PAD_SHOULDER_R;
    }
    return out;
}

/* The mouse is the shell's own (shell_sdl.c); there is no touch screen. */
void console_read_input(uint32_t out[2], int *touched, int *touch_x, int *touch_y)
{
    if (scans++ % 60u == 0)
    {
        find_pads();
    }
    for (int slot = 0; slot < 2; ++slot)
    {
        out[slot] = pads[slot] ? buttons(pads[slot]) : 0;
    }
    *touched = 0;
    *touch_x = 0;
    *touch_y = 0;
}

/* --- the next program ---------------------------------------------------------------------- */

static char next_path[600], next_argument[600];
static int has_next;

int console_chain(const char *path, const char *argument)
{
    snprintf(next_path, sizeof next_path, "%s", path);
    snprintf(next_argument, sizeof next_argument, "%s", argument ? argument : "");
    has_next = 1;
    return 1;
}

/* Runs the program chosen; this one ends right after. */
void console_finish(int closing)
{
    if (!has_next || closing)
    {
        return;
    }
    has_next = 0;
#ifdef _WIN32
    char quoted_path[620], quoted_argument[620];
    snprintf(quoted_path, sizeof quoted_path, "\"%s\"", next_path);
    snprintf(quoted_argument, sizeof quoted_argument, "\"%s\"", next_argument);
    const char *args[3] = {quoted_path, next_argument[0] ? quoted_argument : NULL, NULL};
    _spawnv(_P_NOWAIT, next_path, args);
#else
    char *args[3] = {next_path, next_argument[0] ? next_argument : NULL, NULL};
    pid_t child;
    posix_spawn(&child, next_path, NULL, NULL, args, environ);
#endif
}
