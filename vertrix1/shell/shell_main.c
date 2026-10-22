/* Vertrix (1997) on the Mac or a console: the recompiled VERTRIX.EXE on the DOS machine
 * (vertrix1/runtime), through shell/shell.h. The game's directory is its folder (mac/data.h on
 * the Mac, the launcher's on a console), which holds the original release (the game checks every
 * file BIN2.BIN lists); it writes SETUP.CFG and its scores there. The VGA's picture is read at
 * each refresh of the screen and filled to 4:3, the Sound Blaster's samples play on the system's
 * sound, a keyboard is the PC's, and game controllers are keys as the Wii Remotes are:
 *
 *   Controller 1:  D-pad, left stick   the arrow keys (one player; player 2 of two)
 *                  A                   Up (permute)
 *                  B                   Enter
 *                  X, Menu             Escape
 *                  Options             P (pause)
 *   Controller 2:  player 1 of two, on the game's default keys W, X, C and F: D-pad left,
 *                  right, down; Up or A permutes; B is Enter.
 *
 * Closing the window (or the app) stops the game where it is (it saves its setup only when left
 * through its own EXIT). The log is vertrix.log in the game's directory. */
#include "dos.h"
#include "shell.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static volatile int game_started; /* v1_clock counts from the game's start */

uint64_t v3_microseconds(void)
{
    return shell_microseconds();
}

void v3_sleep_ms(uint32_t ms)
{
    usleep(ms * 1000u);
}

void v3_log(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    char line[1024];
    const int n =
        snprintf(line, sizeof line, "[%7.3f] ", game_started ? (double)v1_clock() / 1e6 : 0.0);
    vsnprintf(line + n, sizeof line - (size_t)n, format, args);
    va_end(args);
    shell_log(line);
}

_Noreturn void v3_fatal(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    char line[1024];
    vsnprintf(line, sizeof line, format, args);
    va_end(args);
    shell_fatal(line);
}

/* --- video --------------------------------------------------------------------------------- */

/* On the main thread, once a refresh: the picture the VGA shows now. */
static void refresh(void)
{
    static uint32_t pixels[640 * 480];
    uint32_t w, h;
    if (game_started && v1_vga_render(pixels, &w, &h))
    {
        shell_present(pixels, w, h);
    }
}

/* --- sound --------------------------------------------------------------------------------- */

static void audio(const uint8_t *samples, uint32_t count, uint32_t rate)
{
    static uint32_t open_rate;
    if (rate != open_rate)
    {
        shell_audio_open(rate, 1, 8);
        open_rate = rate;
    }
    /* The Sound Blaster plays in real time: keep no more than a quarter second queued, so a
     * stall does not leave the sound behind the picture for good. */
    if (shell_audio_queued() < rate / 4u)
    {
        shell_audio_write(samples, count);
    }
}

/* --- input --------------------------------------------------------------------------------- */

/* Set 1 scan codes (0x100: the E0 prefix of the arrow keys). */
enum
{
    KEY_ESCAPE = 0x01,
    KEY_ENTER = 0x1c,
    KEY_P = 0x19,
    KEY_F = 0x21,
    KEY_W = 0x2c,
    KEY_X = 0x2d,
    KEY_C = 0x2e,
    KEY_UP = 0x148,
    KEY_LEFT = 0x14b,
    KEY_RIGHT = 0x14d,
    KEY_DOWN = 0x150
};

static const struct
{
    uint32_t button;
    unsigned key;
} pad_keys[] = {
    {SHELL_PAD_UP, KEY_UP},       {SHELL_PAD_DOWN, KEY_DOWN},   {SHELL_PAD_LEFT, KEY_LEFT},
    {SHELL_PAD_RIGHT, KEY_RIGHT}, {SHELL_PAD_A, KEY_UP},        {SHELL_PAD_B, KEY_ENTER},
    {SHELL_PAD_X, KEY_ESCAPE},    {SHELL_PAD_MENU, KEY_ESCAPE}, {SHELL_PAD_OPTIONS, KEY_P}};

/* The second controller: player 1's default keys in a two-player game. */
static const struct
{
    uint32_t button;
    unsigned key;
} second_keys[] = {{SHELL_PAD_UP, KEY_F},     {SHELL_PAD_A, KEY_F},     {SHELL_PAD_DOWN, KEY_C},
                   {SHELL_PAD_LEFT, KEY_W},   {SHELL_PAD_RIGHT, KEY_X}, {SHELL_PAD_B, KEY_ENTER},
                   {SHELL_PAD_OPTIONS, KEY_P}};

/* Several buttons may share a key: a key is down while any of them is held. */
static void pads(void)
{
    static uint32_t before, before2;
    static uint8_t down_now[0x200];
    const uint32_t held = shell_pad(0), held2 = shell_pad(1);
    const uint32_t changed = held ^ before, changed2 = held2 ^ before2;
    if (!changed && !changed2)
    {
        return;
    }
    before = held;
    before2 = held2;
    uint8_t want[0x200] = {0}, touched[0x200] = {0};
    for (unsigned k = 0; k < sizeof pad_keys / sizeof pad_keys[0]; ++k)
    {
        touched[pad_keys[k].key] |= (changed & pad_keys[k].button) != 0;
        want[pad_keys[k].key] |= (held & pad_keys[k].button) != 0;
    }
    for (unsigned k = 0; k < sizeof second_keys / sizeof second_keys[0]; ++k)
    {
        touched[second_keys[k].key] |= (changed2 & second_keys[k].button) != 0;
        want[second_keys[k].key] |= (held2 & second_keys[k].button) != 0;
    }
    for (unsigned key = 0; key < 0x200; ++key)
    {
        if (touched[key] && want[key] != down_now[key])
        {
            down_now[key] = want[key];
            v1_key(key, want[key]);
        }
    }
}

/* The game thread, about every millisecond of guest time. A key held down repeats as the PC's
 * keyboard repeats it, with its make code again. */
static int poll(void)
{
    ShellInput in;
    while (shell_input(&in))
    {
        if (in.kind == SHELL_KEY)
        {
            v1_key(in.code, in.down);
        }
    }
    pads();
    return shell_quit_requested();
}

/* --- the game ------------------------------------------------------------------------------ */

static void console(const char *text, size_t length)
{
    v3_log("console: %.*s", (int)length, text);
}

static V1Platform platform = {NULL, NULL, NULL, poll, audio, console};
static uint8_t image[0x100000];

static void game(void)
{
    game_started = 1;
    const int code = v1_run(image, &platform);
    v3_log("the game ended with %d", code);
    shell_exit(code < 0 ? 0 : code);
}

int main(int argc, char **argv)
{
    static const ShellOptions options = {&vertrix_games[0], 640, 480, 4.0 / 3.0, 0};
    platform.directory = shell_start(argc, argv, &options);
    shell_log_open("vertrix.log");
    size_t size = 0;
    uint8_t *bytes = shell_resource("v1_image.bin", &size);
    if (!bytes || size != v1_image.size || size > sizeof image)
    {
        shell_fatal("The app's v1_image.bin is missing or does not match its code.");
    }
    memcpy(image, bytes, size);
    free(bytes);
    v3_log("Vertrix for %s: %u KB of image, files in %s", shell_platform, (unsigned)(size >> 10),
           platform.directory);
    shell_set_refresh(refresh);
    shell_run(game);
}
