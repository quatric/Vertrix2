/* A recompiled game on the Mac (Vertrix 3, Vertrix 2 v1.2 and v2.0), through mac/shell.h: the
 * software renderer's frames (or the frames the game drew itself, DirectDraw) in a window at
 * 60 Hz, as a Flip waits for the vertical blank; the wave-out stream on Core Audio; the keyboard
 * and mouse as DirectInput's; and a game controller as the Wii's buttons are:
 *
 *   D-pad, left stick   arrow keys (player 1: left, right, down; Up permutes)
 *   A                   Up (permute)
 *   B                   Enter
 *   X                   Space
 *   Menu, Options       Escape
 *
 * The game's files and settings are in its folder (mac/data.h); the log is FOLDER.log there. */
#include "process.h"
#include "runtime.h"
#include "shell.h"

#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define WIDTH 640
#define HEIGHT 480

static uint64_t started;

uint64_t v3_microseconds(void)
{
    const uint64_t now = shell_microseconds();
    if (!started)
    {
        started = now;
    }
    return now - started + 1000000u;
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
        snprintf(line, sizeof line, "[%7.3f] ", (double)(v3_microseconds() - 1000000u) / 1e6);
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

static unsigned frames;

static void present(const V3Frame *frame)
{
    if (frame->pixels)
    {
        shell_present(frame->pixels, frame->width, frame->height);
    }
    ++frames;
    shell_wait_frame();
}

/* --- sound --------------------------------------------------------------------------------- */

static void wave_open(uint32_t rate, uint32_t channels, uint32_t bits)
{
    shell_audio_open(rate, channels, bits);
}

static void wave_write(const uint8_t *samples, uint32_t bytes)
{
    shell_audio_write(samples, bytes);
}

static uint64_t wave_played(void)
{
    return shell_audio_played();
}

/* --- input --------------------------------------------------------------------------------- */

/* A set 1 scan code as DirectInput's: the E0 keys have the high bit. */
static unsigned direct_input(unsigned scan_code)
{
    return scan_code & 0x100u ? 0x80u | (scan_code & 0x7fu) : scan_code;
}

static const struct
{
    uint32_t button;
    unsigned scan_code;
} pad_keys[] = {{SHELL_PAD_UP, 0xc8},    {SHELL_PAD_DOWN, 0xd0}, {SHELL_PAD_LEFT, 0xcb},
                {SHELL_PAD_RIGHT, 0xcd}, {SHELL_PAD_A, 0xc8},    {SHELL_PAD_B, 0x1c},
                {SHELL_PAD_X, 0x39},     {SHELL_PAD_MENU, 0x01}, {SHELL_PAD_OPTIONS, 0x01}};

/* The game moves its own cursor from DirectInput's relative motion, two pixels per unit,
 * clamped to the screen, starting at the centre. The Mac's pointer is absolute, so the driver
 * tracks where the cursor must be and sends the difference; before a click it first pins the
 * cursor to the corner (one poll), then moves it exactly (the next poll), then presses (the one
 * after), as the game adds up the motion of one poll before clamping (the Wii driver does the
 * same with the remote's pointer). */
static int cursor_x = WIDTH / 2, cursor_y = HEIGHT / 2;
static int target_x = WIDTH / 2, target_y = HEIGHT / 2;
static int click_phase; /* 0 idle, 1 pinned, 2 moved, 3 pressed */
static int left_held;

static void cursor_to(int x, int y)
{
    const int dx = (x - cursor_x) / 2, dy = (y - cursor_y) / 2;
    if (dx || dy)
    {
        v3_input_mouse_move(dx, dy);
        cursor_x += 2 * dx;
        cursor_y += 2 * dy;
    }
}

static void pointer(int pinned)
{
    int x, y;
    if (shell_pointer(&x, &y))
    {
        target_x = x;
        target_y = y;
    }
    if (click_phase == 1 && pinned)
    {
        return; /* the pin's own poll */
    }
    if (click_phase == 1)
    {
        cursor_to(target_x, target_y);
        click_phase = 2;
        return;
    }
    if (click_phase == 2)
    {
        v3_input_mouse_button(0, 1);
        click_phase = 3;
        return;
    }
    if (click_phase == 3 && !left_held)
    {
        v3_input_mouse_button(0, 0);
        click_phase = 0;
    }
    cursor_to(target_x, target_y);
}

static int poll(void)
{
    int pinned = 0;
    ShellInput in;
    while (shell_input(&in))
    {
        if (in.kind == SHELL_KEY)
        {
            v3_input_key(direct_input(in.code), in.down);
        }
        else if (in.code == 0)
        {
            left_held = in.down;
            if (in.down && click_phase == 0)
            {
                click_phase = 1;
                pinned = 1;
                v3_input_mouse_move(-WIDTH, -HEIGHT);
                cursor_x = cursor_y = 0;
            }
        }
        else
        {
            v3_input_mouse_button(in.code, in.down);
        }
    }
    /* Several buttons may share a key: a key is down while any of them is held. */
    static uint32_t before;
    const uint32_t held = shell_pad(0) | shell_pad(1);
    const uint32_t changed = held ^ before;
    before = held;
    uint8_t want[256] = {0}, touched[256] = {0};
    for (unsigned k = 0; k < sizeof pad_keys / sizeof pad_keys[0]; ++k)
    {
        touched[pad_keys[k].scan_code] |= changed & pad_keys[k].button ? 1 : 0;
        want[pad_keys[k].scan_code] |= held & pad_keys[k].button ? 1 : 0;
    }
    for (unsigned code = 0; code < 256; ++code)
    {
        if (touched[code])
        {
            v3_input_key(code, want[code]);
        }
    }
    pointer(pinned);
    return shell_quit_requested();
}

/* --- the game ------------------------------------------------------------------------------ */

static V3Platform platform = {NULL, present, poll, wave_open, wave_write, wave_played};
static uint8_t *image;
static size_t image_size;

static void game(void)
{
    const int code = v3_run(image, (uint32_t)image_size, NULL, &platform);
    v3_log("game exited with %d after %u frames", code, frames);
    exit(code);
}

/* A fault inside the guest space: say where, and what the game was doing. */
static void on_fault(int signal, siginfo_t *info, void *context)
{
    (void)context;
    const uintptr_t at = (uintptr_t)info->si_addr;
    const uintptr_t base = (uintptr_t)v3_memory;
    if (at >= base && at - base < ((uintptr_t)1 << 32))
    {
        v3_log("signal %d: guest address %08x", signal, (unsigned)(at - base));
    }
    else
    {
        v3_log("signal %d: host address %p", signal, info->si_addr);
    }
    v3_history_dump(64);
    _exit(128 + signal);
}

int main(int argc, char **argv)
{
    static const ShellOptions options = {NULL, WIDTH, HEIGHT, 0, 1};
    ShellOptions o = options;
    o.game = vertrix_game(v3_wii_folder);
    const char *directory = shell_start(argc, argv, &o);
    platform.directory = directory;
    char log_name[64];
    snprintf(log_name, sizeof log_name, "%s.log", v3_wii_folder);
    shell_log_open(log_name);
    image = shell_resource("v3_image.bin", &image_size);
    if (!image)
    {
        shell_fatal("The app is missing its v3_image.bin.");
    }
    v3_log("%s for the Mac: %u KB of image, files in %s", v3_game_title,
           (unsigned)(image_size >> 10), directory);
    struct sigaction action = {0};
    action.sa_sigaction = on_fault;
    action.sa_flags = SA_SIGINFO | SA_ONSTACK;
    sigaction(SIGSEGV, &action, NULL);
    sigaction(SIGBUS, &action, NULL);
    shell_run(game);
}
