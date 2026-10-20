/* Vertrix 3 recompiled, on the Wii: the game reads VERTRIX3.VF and keeps Settings/ in
 * sd:/apps/vertrix3/, draws through GX (render_gx.c), plays the wave-out stream on an ASND
 * voice, and gets its keyboard and mouse from the controllers:
 *
 *   D-pad, Nunchuk/Classic stick   arrow keys (player 1: left, right, Up permutes, down)
 *   B                              Up (permute)
 *   A                              mouse click where the remote points (menus)
 *   1, 2                           Enter, Space
 *   Plus, Minus                    Escape
 *   Home                           back to the loader
 *
 * A USB keyboard and mouse work as themselves. The log goes to sd:/apps/vertrix3/vertrix3.log. */
#include <asndlib.h>
#include <fat.h>
#include <gccore.h>
#include <malloc.h>
#include <ogc/lwp_watchdog.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <wiiuse/wpad.h>

#include "input_wii.h"
#include "render.h"
#include "runtime.h"
#include "wii_audio.h"

#include "v3_image_bin.h"

#define DIRECTORY "sd:/apps/vertrix3"
#define WIDTH 640
#define HEIGHT 480

/* --- log ---------------------------------------------------------------------------------- */

static FILE *log_file;
static mutex_t log_lock = LWP_MUTEX_NULL;

uint64_t v3_microseconds(void)
{
    static uint64_t started;
    const uint64_t now = ticks_to_microsecs(gettime());
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
    if (log_lock != LWP_MUTEX_NULL)
    {
        LWP_MutexLock(log_lock);
    }
    va_list args;
    va_start(args, format);
    char line[512];
    int n = snprintf(line, sizeof line, "[%7.3f] ", (double)(v3_microseconds() - 1000000u) / 1e6);
    vsnprintf(line + n, sizeof line - (size_t)n, format, args);
    va_end(args);
    if (log_file)
    {
        fputs(line, log_file);
        fputc('\n', log_file);
        fflush(log_file);
    }
    printf("%s\n", line); /* Dolphin's log shows OSReport/stdout */
    if (log_lock != LWP_MUTEX_NULL)
    {
        LWP_MutexUnlock(log_lock);
    }
}

_Noreturn void v3_fatal(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    char line[512];
    vsnprintf(line, sizeof line, format, args);
    va_end(args);
    v3_log("FATAL: %s", line);
    if (log_file)
    {
        fclose(log_file);
    }
    exit(2);
}

/* --- video -------------------------------------------------------------------------------- */

static GXRModeObj *mode;
static void *xfb[2];
static unsigned xfb_next;
static unsigned frames;

static void video_init(void)
{
    VIDEO_Init();
    mode = VIDEO_GetPreferredMode(NULL);
    for (int i = 0; i < 2; ++i)
    {
        xfb[i] = MEM_K0_TO_K1(SYS_AllocateFramebuffer(mode));
        VIDEO_ClearFrameBuffer(mode, xfb[i], COLOR_BLACK);
    }
    VIDEO_Configure(mode);
    VIDEO_SetNextFramebuffer(xfb[0]);
    VIDEO_SetBlack(FALSE);
    VIDEO_Flush();
    VIDEO_WaitVSync();
    if (mode->viTVMode & VI_NON_INTERLACE)
    {
        VIDEO_WaitVSync();
    }
    void *fifo = memalign(32, 512 * 1024);
    memset(fifo, 0, 512 * 1024);
    GX_Init(fifo, 512 * 1024);
    GXColor black = {0, 0, 0, 255};
    GX_SetCopyClear(black, 0x00ffffff);
    /* The game draws 640x480 into the EFB; the display copy scales it to the TV's lines. */
    GX_SetDispCopySrc(0, 0, WIDTH, HEIGHT);
    const f32 scale = GX_GetYScaleFactor(HEIGHT, mode->xfbHeight);
    const u32 lines = GX_SetDispCopyYScale(scale);
    GX_SetDispCopyDst(mode->fbWidth, (u16)lines);
    GX_SetCopyFilter(mode->aa, mode->sample_pattern, GX_TRUE, mode->vfilter);
    GX_SetFieldMode(mode->field_rendering, mode->viHeight == 2 * mode->xfbHeight ? GX_ENABLE : GX_DISABLE);
    GX_SetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);
    GX_SetDispCopyGamma(GX_GM_1_0);
    GX_SetViewport(0, 0, WIDTH, HEIGHT, 0, 1);
    GX_SetScissor(0, 0, WIDTH, HEIGHT);
}

#ifdef V3_WII_SHOTS
/* Debug builds: every V3_WII_SHOTS-th frame as DIRECTORY/shots/frameNNNNN.ppm. */
static void shot(void)
{
    static uint32_t *pixels;
    if (!pixels)
    {
        pixels = malloc(WIDTH * HEIGHT * 4);
        mkdir(DIRECTORY "/shots", 0777);
    }
    v3_renderer()->read_back(v3_renderer(), pixels, WIDTH, HEIGHT);
    char path[128];
    snprintf(path, sizeof path, DIRECTORY "/shots/frame%05u.ppm", frames);
    FILE *f = fopen(path, "wb");
    if (!f)
    {
        return;
    }
    fprintf(f, "P6\n%d %d\n255\n", WIDTH, HEIGHT);
    static uint8_t row[WIDTH * 3];
    for (int y = 0; y < HEIGHT; ++y)
    {
        for (int x = 0; x < WIDTH; ++x)
        {
            const uint32_t c = pixels[y * WIDTH + x];
            row[3 * x] = (uint8_t)(c >> 16);
            row[3 * x + 1] = (uint8_t)(c >> 8);
            row[3 * x + 2] = (uint8_t)c;
        }
        fwrite(row, 1, sizeof row, f);
    }
    fclose(f);
}
#endif

static void present(const V3Frame *frame)
{
    (void)frame;
#ifdef V3_WII_SHOTS
    if (frames % V3_WII_SHOTS == 0)
    {
        shot();
    }
#endif
    GX_DrawDone();
    GX_SetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GX_SetColorUpdate(GX_TRUE);
    GX_CopyDisp(xfb[xfb_next], GX_TRUE);
    GX_Flush();
    VIDEO_SetNextFramebuffer(xfb[xfb_next]);
    VIDEO_Flush();
    VIDEO_WaitVSync();
    xfb_next ^= 1;
    if (++frames % 600 == 0)
    {
        const struct mallinfo m = mallinfo();
        v3_log("host memory: %u KB in use, %u KB free in the heap, MEM1 %u KB and MEM2 %u KB left",
               (unsigned)(m.uordblks >> 10), (unsigned)(m.fordblks >> 10),
               (unsigned)(SYS_GetArena1Size() >> 10), (unsigned)(SYS_GetArena2Size() >> 10));
    }
}

/* --- sound -------------------------------------------------------------------------------- */

static uint64_t wave_written, wave_rate_bytes, wave_start;
static uint32_t wave_rate, wave_channels, wave_bits;

static void wave_open(uint32_t rate, uint32_t channels, uint32_t bits)
{
    wave_rate = rate;
    wave_channels = channels;
    wave_bits = bits;
    wave_rate_bytes = (uint64_t)rate * channels * bits / 8u;
    wave_start = v3_microseconds();
    wave_written = 0;
}

static void wave_write(const uint8_t *samples, uint32_t bytes)
{
    vertrix_wii_stream_write(0, samples, bytes, wave_rate, wave_channels, wave_bits);
    wave_written += bytes;
}

/* The device plays in real time: what it has played is what the elapsed time covers. */
static uint64_t wave_played(void)
{
    const uint64_t elapsed = (v3_microseconds() - wave_start) * wave_rate_bytes / 1000000u;
    return elapsed < wave_written ? elapsed : wave_written;
}

/* --- input -------------------------------------------------------------------------------- */

static const struct
{
    uint32_t button;
    unsigned scan_code;
} pad_keys[] = {{WPAD_BUTTON_UP, 0xc8},    {WPAD_BUTTON_DOWN, 0xd0}, {WPAD_BUTTON_LEFT, 0xcb},
                {WPAD_BUTTON_RIGHT, 0xcd}, {WPAD_BUTTON_B, 0xc8},    {WPAD_BUTTON_1, 0x1c},
                {WPAD_BUTTON_2, 0x39},     {WPAD_BUTTON_PLUS, 0x01}, {WPAD_BUTTON_MINUS, 0x01}};

/* A USB keyboard: USB HID usage codes to DirectInput scan codes. */
static const uint8_t usb_scan_codes[0xe8] = {
    [0x04] = 0x1e, [0x05] = 0x30, [0x06] = 0x2e, [0x07] = 0x20, [0x08] = 0x12, [0x09] = 0x21,
    [0x0a] = 0x22, [0x0b] = 0x23, [0x0c] = 0x17, [0x0d] = 0x24, [0x0e] = 0x25, [0x0f] = 0x26,
    [0x10] = 0x32, [0x11] = 0x31, [0x12] = 0x18, [0x13] = 0x19, [0x14] = 0x10, [0x15] = 0x13,
    [0x16] = 0x1f, [0x17] = 0x14, [0x18] = 0x16, [0x19] = 0x2f, [0x1a] = 0x11, [0x1b] = 0x2d,
    [0x1c] = 0x15, [0x1d] = 0x2c, [0x1e] = 0x02, [0x1f] = 0x03, [0x20] = 0x04, [0x21] = 0x05,
    [0x22] = 0x06, [0x23] = 0x07, [0x24] = 0x08, [0x25] = 0x09, [0x26] = 0x0a, [0x27] = 0x0b,
    [0x28] = 0x1c, [0x29] = 0x01, [0x2a] = 0x0e, [0x2b] = 0x0f, [0x2c] = 0x39, [0x2d] = 0x0c,
    [0x2e] = 0x0d, [0x2f] = 0x1a, [0x30] = 0x1b, [0x31] = 0x2b, [0x33] = 0x27, [0x34] = 0x28,
    [0x35] = 0x29, [0x36] = 0x33, [0x37] = 0x34, [0x38] = 0x35, [0x39] = 0x3a, [0x3a] = 0x3b,
    [0x3b] = 0x3c, [0x3c] = 0x3d, [0x3d] = 0x3e, [0x3e] = 0x3f, [0x3f] = 0x40, [0x40] = 0x41,
    [0x41] = 0x42, [0x42] = 0x43, [0x43] = 0x44, [0x44] = 0x57, [0x45] = 0x58, [0x48] = 0xc5,
    [0x49] = 0xd2, [0x4a] = 0xc7, [0x4b] = 0xc9, [0x4c] = 0xd3, [0x4d] = 0xcf, [0x4e] = 0xd1,
    [0x4f] = 0xcd, [0x50] = 0xcb, [0x51] = 0xd0, [0x52] = 0xc8, [0x58] = 0x9c, [0xe0] = 0x1d,
    [0xe1] = 0x2a, [0xe2] = 0x38, [0xe4] = 0x9d, [0xe5] = 0x36, [0xe6] = 0xb8};

/* The game moves its own cursor from DirectInput's relative motion, two pixels per unit,
 * clamped to the screen, starting at the centre. The pointer is absolute, so the driver tracks
 * where the cursor must be and sends the difference; before a click it first pins the cursor to
 * the corner (one poll), then moves it exactly (the next poll), then presses (the one after),
 * as the game adds up the motion of one poll before clamping. */
static int cursor_x = WIDTH / 2, cursor_y = HEIGHT / 2;
static int target_x = WIDTH / 2, target_y = HEIGHT / 2;
static int click_phase; /* 0 idle, 1 pinned, 2 moved; then the press */
static int click_button;

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

static void pointer(uint32_t pads_down, uint32_t pads_up)
{
    if (INPUT_CursorActive())
    {
        int x, y;
        INPUT_CursorPosition(&x, &y);
        target_x = x < 0 ? 0 : x >= WIDTH ? WIDTH - 1 : x;
        target_y = y < 0 ? 0 : y >= HEIGHT ? HEIGHT - 1 : y;
    }
    const u8 mouse_down = INPUT_MouseButtonsPressed(), mouse_up = INPUT_MouseButtonsReleased();
    if (click_phase == 0 && ((pads_down & WPAD_BUTTON_A) || (mouse_down & INPUT_MOUSE_LEFT)))
    {
        click_phase = 1;
        click_button = 0;
        v3_input_mouse_move(-WIDTH, -HEIGHT);
        cursor_x = cursor_y = 0;
        return;
    }
    if (click_phase == 1)
    {
        cursor_to(target_x, target_y);
        click_phase = 2;
        return;
    }
    if (click_phase == 2)
    {
        v3_input_mouse_button((unsigned)click_button, 1);
        click_phase = 3;
        return;
    }
    if (click_phase == 3 && ((pads_up & WPAD_BUTTON_A) || (mouse_up & INPUT_MOUSE_LEFT)))
    {
        v3_input_mouse_button((unsigned)click_button, 0);
        click_phase = 0;
    }
    else if (click_phase == 3 && !(INPUT_PadsHeld() & WPAD_BUTTON_A) &&
             !(INPUT_MouseButtonsHeld() & INPUT_MOUSE_LEFT))
    {
        v3_input_mouse_button((unsigned)click_button, 0);
        click_phase = 0;
    }
    if (mouse_down & INPUT_MOUSE_RIGHT)
    {
        v3_input_mouse_button(1, 1);
    }
    if (mouse_up & INPUT_MOUSE_RIGHT)
    {
        v3_input_mouse_button(1, 0);
    }
    cursor_to(target_x, target_y);
}

/* The strongest stick past half way acts as the D-pad. */
static uint32_t stick_directions(void)
{
    float x, y;
    uint32_t held = 0;
    if (INPUT_Stick(INPUT_STICK_LEFT, &x, &y, NULL) > 0.5f)
    {
        held |= x < -0.5f ? WPAD_BUTTON_LEFT : x > 0.5f ? WPAD_BUTTON_RIGHT : 0;
        held |= y < -0.5f ? WPAD_BUTTON_DOWN : y > 0.5f ? WPAD_BUTTON_UP : 0;
    }
    return held;
}

#ifdef V3_WII_SCRIPT
/* Debug builds: timed input as the build machine's V3_SCRIPT ("SECONDS key SCAN DOWN",
 * "SECONDS move DX DY", "SECONDS button N DOWN", separated by semicolons). */
static void run_script(void)
{
    static const char *script = V3_WII_SCRIPT;
    static double late; /* a step the game was too busy to take delays the ones after it */
    const double now = (double)(v3_microseconds() - 1000000u) / 1e6;
    while (*script)
    {
        double at;
        char kind[16];
        int a = 0, b = 0, used = 0;
        if (sscanf(script, " %lf %15s %d %d%n", &at, kind, &a, &b, &used) < 4 || at + late > now)
        {
            return;
        }
        if (now - (at + late) > 0.05)
        {
            late = now - at;
        }
        if (!strcmp(kind, "key"))
            v3_input_key((unsigned)a, b);
        else if (!strcmp(kind, "move"))
            v3_input_mouse_move(a, b);
        else if (!strcmp(kind, "button"))
            v3_input_mouse_button((unsigned)a, b);
        v3_log("script: %s %d %d", kind, a, b);
        script += used;
        while (*script == ' ' || *script == ';')
            ++script;
        /* One step per poll: the game adds up a poll's mouse motion before clamping. */
        return;
    }
}
#endif

static int poll(void)
{
#ifdef V3_WII_SCRIPT
    run_script();
#endif
    INPUT_Update();
    static uint32_t before;
    const uint32_t held = INPUT_PadsHeld() | stick_directions();
    const uint32_t down = held & ~before, up = before & ~held;
    before = held;
    if (down & WPAD_BUTTON_HOME)
    {
        return 1;
    }
    /* Several buttons may share a key: a key is down while any of them is held. */
    uint8_t want[256] = {0};
    uint8_t touched[256] = {0};
    for (unsigned k = 0; k < sizeof pad_keys / sizeof pad_keys[0]; ++k)
    {
        touched[pad_keys[k].scan_code] |= (down | up) & pad_keys[k].button ? 1 : 0;
        want[pad_keys[k].scan_code] |= held & pad_keys[k].button ? 1 : 0;
    }
    for (unsigned code = 0; code < 256; ++code)
    {
        if (touched[code])
        {
            v3_input_key(code, want[code]);
        }
    }
    for (unsigned code = 0; code < sizeof usb_scan_codes; ++code)
    {
        if (usb_scan_codes[code] && INPUT_KeyPressed((u8)code))
        {
            v3_input_key(usb_scan_codes[code], 1);
        }
        if (usb_scan_codes[code] && INPUT_KeyReleased((u8)code))
        {
            v3_input_key(usb_scan_codes[code], 0);
        }
    }
#ifndef V3_WII_SCRIPT
    pointer(down, up); /* a script's motion would fight the pointer's */
#endif
    return 0;
}

/* --- the game ----------------------------------------------------------------------------- */

static const V3Platform platform = {DIRECTORY, present, poll, wave_open, wave_write, wave_played};

enum
{
    GAME_STACK = 4 * 1024 * 1024
};

static volatile int game_done;
static int game_code;

static void *game(void *unused)
{
    (void)unused;
    game_code = v3_run(v3_image_bin, v3_image_bin_size, "\"C:\\Vertrix3\\Vertrix3.exe\"", &platform);
    v3_log("game exited with %d after %u frames", game_code, frames);
    game_done = 1;
    return NULL;
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    SYS_STDIO_Report(true); /* stdout into Dolphin's OSReport log */
#ifdef V3_WII_ENV
    /* Debug builds: the build machine's diagnostic variables, as "NAME=VALUE;NAME=VALUE". */
    {
        static char env[] = V3_WII_ENV;
        for (char *item = strtok(env, ";"); item; item = strtok(NULL, ";"))
        {
            char *equals = strchr(item, '=');
            if (equals)
            {
                *equals = 0;
                setenv(item, equals + 1, 1);
            }
        }
    }
#endif
    video_init();
    LWP_MutexInit(&log_lock, false);
    if (fatInitDefault())
    {
        log_file = fopen(DIRECTORY "/vertrix3.log", "w");
    }
    INPUT_Init();
    INPUT_SetScreenSize(WIDTH, HEIGHT);
    INPUT_KeyboardMapClear();
    ASND_Init();
    ASND_Pause(0);
    v3_log("Vertrix 3 for the Wii: %u-line TV mode, %u KB of image", mode->xfbHeight,
           (unsigned)(v3_image_bin_size >> 10));
    FILE *archive = fopen(DIRECTORY "/VERTRIX3.VF", "rb");
    if (!archive)
    {
        v3_log("no " DIRECTORY "/VERTRIX3.VF: copy the game's VERTRIX3.VF there");
    }
    else
    {
        fclose(archive);
    }
    lwp_t thread;
    void *stack = memalign(32, GAME_STACK);
    LWP_CreateThread(&thread, game, NULL, stack, GAME_STACK, 48);
    while (!game_done)
    {
        usleep(100 * 1000);
    }
    if (log_file)
    {
        fclose(log_file);
    }
    return game_code;
}
