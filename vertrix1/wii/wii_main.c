/* Vertrix (1997) on the Wii: the recompiled VERTRIX.EXE on the DOS machine (vertrix1/runtime).
 * The game's directory is sd:/apps/vertrix1/ (or the one the launcher passes, launcher/app.h),
 * which holds the original release (BIN1.BIN,
 * BIN2.BIN and the other files; the game checks them all); it writes SETUP.CFG and its scores
 * there. The VGA's picture is shown at the Wii's own frame rate, the Sound Blaster's samples
 * play on an ASND voice, and the controllers are keys:
 *
 *   Wii Remote 1 (sideways or upright) or any pad:
 *     D-pad, Nunchuk/Classic stick   the arrow keys (one player; player 2 of two)
 *     B                              Up (permute)
 *     A, 2                           Enter
 *     1, Minus                       Escape
 *     Plus                           P (pause)
 *   Wii Remote 2: player 1 of two, on the game's default keys W, X, C and F (scan codes 2Ch,
 *     2Dh, 2Eh and 21h): D-pad left, right, down; B or Up permutes.
 *   Home                             back to the launcher or the loader (the game saves its
 *                                    setup only when left through its own EXIT)
 *
 * A USB keyboard works as itself. The log is vertrix.log in the game's directory. */
#include <asndlib.h>
#include <fat.h>
#include <gccore.h>
#include <malloc.h>
#include <ogc/conf.h>
#include <ogc/lwp_watchdog.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <wiiuse/wpad.h>

#include "app.h"
#include "dos.h"
#include "input_wii.h"
#include "wii_audio.h"

#include "v1_image_bin.h"

#define EFB_WIDTH 640
#define EFB_HEIGHT 400

static const char *directory = "sd:/apps/vertrix1";

/* --- log ---------------------------------------------------------------------------------- */

static FILE *log_file;
static volatile int game_started; /* v1_clock counts from the game's start */
static mutex_t log_lock = LWP_MUTEX_NULL;

uint64_t v3_microseconds(void)
{
    return ticks_to_microsecs(gettime());
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
    int n = snprintf(line, sizeof line, "[%7.3f] ", game_started ? (double)v1_clock() / 1e6 : 0.0);
    vsnprintf(line + n, sizeof line - (size_t)n, format, args);
    va_end(args);
    if (log_file)
    {
        fputs(line, log_file);
        fputc('\n', log_file);
        fflush(log_file);
        /* libfat writes to the card only on a sync or a close. */
        fsync(fileno(log_file));
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
static int widescreen;

static void video_init(void)
{
    VIDEO_Init();
    mode = VIDEO_GetPreferredMode(NULL);
    widescreen = CONF_GetAspectRatio() == CONF_ASPECT_16_9;
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
    void *fifo = memalign(32, 256 * 1024);
    memset(fifo, 0, 256 * 1024);
    GX_Init(fifo, 256 * 1024);
    GXColor black = {0, 0, 0, 255};
    GX_SetCopyClear(black, 0x00ffffff);
    /* The VGA's 400 lines go into the EFB as they are; the display copy scales them to the TV's
     * lines, as the monitor spread them over its 4:3 screen. */
    GX_SetDispCopySrc(0, 0, EFB_WIDTH, EFB_HEIGHT);
    const f32 scale = GX_GetYScaleFactor(EFB_HEIGHT, mode->xfbHeight);
    const u32 lines = GX_SetDispCopyYScale(scale);
    GX_SetDispCopyDst(mode->fbWidth, (u16)lines);
    GX_SetCopyFilter(mode->aa, mode->sample_pattern, GX_TRUE, mode->vfilter);
    GX_SetFieldMode(mode->field_rendering,
                    mode->viHeight == 2 * mode->xfbHeight ? GX_ENABLE : GX_DISABLE);
    GX_SetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);
    GX_SetDispCopyGamma(GX_GM_1_0);
    GX_SetCullMode(GX_CULL_NONE);
}

/* The VGA's picture as an RGBA8 texture in 4x4 tiles (each tile's alpha and red pairs, then its
 * green and blue pairs), drawn over the EFB: across the whole of a 4:3 TV, and over the
 * middle 480 columns of a 16:9 one, so the picture keeps the monitor's shape. */
static void draw_vga(void)
{
    static uint8_t indices[640 * 480];
    static uint8_t palette[256][3];
    static uint8_t *tiles;
    static GXTexObj texture;
    uint32_t w, h;
    GX_SetViewport(0, 0, EFB_WIDTH, EFB_HEIGHT, 0, 1);
    GX_SetScissor(0, 0, EFB_WIDTH, EFB_HEIGHT);
    if (!v1_vga_render_indexed(indices, palette, &w, &h) || w < 4 || h < 4)
    {
        return;
    }
    w &= ~3u;
    h &= ~3u;
    if (!tiles)
    {
        tiles = memalign(32, 640 * 480 * 4);
        if (!tiles)
        {
            return;
        }
    }
    uint32_t colours[256][2];
    for (unsigned i = 0; i < 256; ++i)
    {
        colours[i][0] = 0xff00u | palette[i][0];
        colours[i][1] = (uint32_t)palette[i][1] << 8 | palette[i][2];
    }
    GX_DrawDone(); /* the last frame's draw has read the texture */
    uint16_t *out = (uint16_t *)tiles;
    for (uint32_t ty = 0; ty < h; ty += 4)
    {
        for (uint32_t tx = 0; tx < w; tx += 4)
        {
            for (uint32_t y = 0; y < 4; ++y)
            {
                const uint8_t *in = indices + (ty + y) * w + tx;
                for (uint32_t x = 0; x < 4; ++x)
                {
                    out[4 * y + x] = (uint16_t)colours[in[x]][0];
                    out[16 + 4 * y + x] = (uint16_t)colours[in[x]][1];
                }
            }
            out += 32;
        }
    }
    DCFlushRange(tiles, w * h * 4);
    GX_InvalidateTexAll();
    GX_InitTexObj(&texture, tiles, (u16)w, (u16)h, GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GX_InitTexObjFilterMode(&texture, widescreen ? GX_LINEAR : GX_NEAR,
                            widescreen ? GX_LINEAR : GX_NEAR);
    GX_LoadTexObj(&texture, GX_TEXMAP0);

    Mtx44 projection;
    guOrtho(projection, 0, EFB_HEIGHT, 0, EFB_WIDTH, 0, 1);
    GX_LoadProjectionMtx(projection, GX_ORTHOGRAPHIC);
    Mtx identity;
    guMtxIdentity(identity);
    GX_LoadPosMtxImm(identity, GX_PNMTX0);
    GX_SetCurrentMtx(GX_PNMTX0);
    GX_ClearVtxDesc();
    GX_SetVtxDesc(GX_VA_POS, GX_DIRECT);
    GX_SetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GX_SetVtxAttrFmt(GX_VTXFMT1, GX_VA_POS, GX_POS_XY, GX_F32, 0);
    GX_SetVtxAttrFmt(GX_VTXFMT1, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GX_SetNumChans(0);
    GX_SetNumTexGens(1);
    GX_SetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
    GX_SetNumIndStages(0);
    GX_SetNumTevStages(1);
    GX_SetTevDirect(GX_TEVSTAGE0);
    GX_SetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLORNULL);
    GX_SetTevOp(GX_TEVSTAGE0, GX_REPLACE);
    GX_SetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GX_SetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, GX_LO_CLEAR);
    GX_SetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GX_SetColorUpdate(GX_TRUE);
    /* The picture fills the 4:3 screen (320x400 is 4:3 on a VGA monitor). */
    const f32 left = widescreen ? (EFB_WIDTH - EFB_WIDTH * 3.0f / 4.0f) / 2.0f : 0.0f;
    const f32 right = EFB_WIDTH - left;
    GX_Begin(GX_QUADS, GX_VTXFMT1, 4);
    GX_Position2f32(left, 0);
    GX_TexCoord2f32(0, 0);
    GX_Position2f32(right, 0);
    GX_TexCoord2f32(1, 0);
    GX_Position2f32(right, EFB_HEIGHT);
    GX_TexCoord2f32(1, 1);
    GX_Position2f32(left, EFB_HEIGHT);
    GX_TexCoord2f32(0, 1);
    GX_End();
}

#ifdef V1_WII_SHOTS
/* Debug builds: every V1_WII_SHOTS-th shown frame as DIRECTORY/shots/frameNNNNN.ppm. */
static void shot(void)
{
    static uint32_t pixels[640 * 480];
    uint32_t w, h;
    char path[128];
    if (!v1_vga_render(pixels, &w, &h))
    {
        return;
    }
    snprintf(path, sizeof path, "%s/shots", directory);
    mkdir(path, 0777);
    snprintf(path, sizeof path, "%s/shots/frame%05u.ppm", directory, frames);
    FILE *f = fopen(path, "wb");
    if (!f)
    {
        return;
    }
    fprintf(f, "P6\n%u %u\n255\n", w, h);
    static uint8_t row[640 * 3];
    for (uint32_t y = 0; y < h; ++y)
    {
        for (uint32_t x = 0; x < w; ++x)
        {
            const uint32_t c = pixels[y * w + x];
            row[3 * x] = (uint8_t)(c >> 16);
            row[3 * x + 1] = (uint8_t)(c >> 8);
            row[3 * x + 2] = (uint8_t)c;
        }
        fwrite(row, 1, 3 * w, f);
    }
    fclose(f);
}
#endif

static void show_frame(void)
{
    draw_vga();
#ifdef V1_WII_SHOTS
    if (frames % V1_WII_SHOTS == 0)
    {
        shot();
    }
#endif
    GX_DrawDone();
    GX_CopyDisp(xfb[xfb_next], GX_TRUE);
    GX_Flush();
    VIDEO_SetNextFramebuffer(xfb[xfb_next]);
    VIDEO_Flush();
    VIDEO_WaitVSync();
    xfb_next ^= 1;
    if (++frames % 3000 == 0)
    {
        const struct mallinfo m = mallinfo();
        v3_log("host memory: %u KB in use, %u KB free in the heap, MEM1 %u KB and MEM2 %u KB left",
               (unsigned)(m.uordblks >> 10), (unsigned)(m.fordblks >> 10),
               (unsigned)(SYS_GetArena1Size() >> 10), (unsigned)(SYS_GetArena2Size() >> 10));
    }
}

/* --- sound -------------------------------------------------------------------------------- */

static void audio(const uint8_t *samples, uint32_t count, uint32_t rate)
{
#ifdef V1_WII_SHOTS
    /* Debug builds: how much sound reached the voice, and its loudest sample, every 5 s. */
    static uint32_t total, loudest;
    static uint64_t next;
    if (!next)
    {
        next = v1_clock() + 5000000;
    }
    for (uint32_t i = 0; i < count; ++i)
    {
        const uint32_t level = samples[i] >= 0x80 ? samples[i] - 0x80u : 0x80u - samples[i];
        loudest = level > loudest ? level : loudest;
    }
    total += count;
    if (v1_clock() >= next)
    {
        v3_log("sound: %u samples at %u Hz, loudest %u of 128", total, rate, loudest);
        next += 5000000;
        total = loudest = 0;
    }
#endif
    vertrix_wii_stream_write(0, samples, count, rate, 1, 8);
}

/* --- input -------------------------------------------------------------------------------- */

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
} pad_keys[] = {{WPAD_BUTTON_UP, KEY_UP},        {WPAD_BUTTON_DOWN, KEY_DOWN},
                {WPAD_BUTTON_LEFT, KEY_LEFT},    {WPAD_BUTTON_RIGHT, KEY_RIGHT},
                {WPAD_BUTTON_B, KEY_UP},         {WPAD_BUTTON_A, KEY_ENTER},
                {WPAD_BUTTON_2, KEY_ENTER},      {WPAD_BUTTON_1, KEY_ESCAPE},
                {WPAD_BUTTON_MINUS, KEY_ESCAPE}, {WPAD_BUTTON_PLUS, KEY_P}};

/* The second Wii Remote: player 1's default keys in a two-player game. */
static const struct
{
    uint32_t button;
    unsigned key;
} second_keys[] = {{WPAD_BUTTON_UP, KEY_F},    {WPAD_BUTTON_B, KEY_F},
                   {WPAD_BUTTON_DOWN, KEY_C},  {WPAD_BUTTON_LEFT, KEY_W},
                   {WPAD_BUTTON_RIGHT, KEY_X}, {WPAD_BUTTON_A, KEY_ENTER},
                   {WPAD_BUTTON_PLUS, KEY_P}};

/* A USB keyboard: USB HID usage codes to set 1 scan codes. */
static const uint16_t usb_scan_codes[0xe8] = {
    [0x04] = 0x1e,  [0x05] = 0x30,  [0x06] = 0x2e,  [0x07] = 0x20,  [0x08] = 0x12,  [0x09] = 0x21,
    [0x0a] = 0x22,  [0x0b] = 0x23,  [0x0c] = 0x17,  [0x0d] = 0x24,  [0x0e] = 0x25,  [0x0f] = 0x26,
    [0x10] = 0x32,  [0x11] = 0x31,  [0x12] = 0x18,  [0x13] = 0x19,  [0x14] = 0x10,  [0x15] = 0x13,
    [0x16] = 0x1f,  [0x17] = 0x14,  [0x18] = 0x16,  [0x19] = 0x2f,  [0x1a] = 0x11,  [0x1b] = 0x2d,
    [0x1c] = 0x15,  [0x1d] = 0x2c,  [0x1e] = 0x02,  [0x1f] = 0x03,  [0x20] = 0x04,  [0x21] = 0x05,
    [0x22] = 0x06,  [0x23] = 0x07,  [0x24] = 0x08,  [0x25] = 0x09,  [0x26] = 0x0a,  [0x27] = 0x0b,
    [0x28] = 0x1c,  [0x29] = 0x01,  [0x2a] = 0x0e,  [0x2b] = 0x0f,  [0x2c] = 0x39,  [0x2d] = 0x0c,
    [0x2e] = 0x0d,  [0x2f] = 0x1a,  [0x30] = 0x1b,  [0x31] = 0x2b,  [0x33] = 0x27,  [0x34] = 0x28,
    [0x35] = 0x29,  [0x36] = 0x33,  [0x37] = 0x34,  [0x38] = 0x35,  [0x39] = 0x3a,  [0x3a] = 0x3b,
    [0x3b] = 0x3c,  [0x3c] = 0x3d,  [0x3d] = 0x3e,  [0x3e] = 0x3f,  [0x3f] = 0x40,  [0x40] = 0x41,
    [0x41] = 0x42,  [0x42] = 0x43,  [0x43] = 0x44,  [0x44] = 0x57,  [0x45] = 0x58,  [0x48] = 0x45,
    [0x49] = 0x152, [0x4a] = 0x147, [0x4b] = 0x149, [0x4c] = 0x153, [0x4d] = 0x14f, [0x4e] = 0x151,
    [0x4f] = 0x14d, [0x50] = 0x14b, [0x51] = 0x150, [0x52] = 0x148, [0x58] = 0x11c, [0xe0] = 0x1d,
    [0xe1] = 0x2a,  [0xe2] = 0x38,  [0xe4] = 0x11d, [0xe5] = 0x36,  [0xe6] = 0x138};

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

#ifdef V1_WII_SCRIPT
/* Debug builds: timed keys as the build machine's V1_SCRIPT ("SECONDS key SCAN DOWN", scan
 * codes in hex, separated by semicolons; "SECONDS quit 0 0" stops). Nonzero once it quits. */
static int run_script(void)
{
    static const char *script = V1_WII_SCRIPT;
    const double now = (double)v1_clock() / 1e6;
    while (*script)
    {
        double at;
        char kind[16];
        unsigned a = 0;
        int b = 0, used = 0;
        if (sscanf(script, " %lf %15s %x %d%n", &at, kind, &a, &b, &used) < 4 || at > now)
        {
            return 0;
        }
        if (!strcmp(kind, "key"))
        {
            v1_key(a, b);
        }
        else if (!strcmp(kind, "quit"))
        {
            return 1;
        }
        script += used;
        while (*script == ' ' || *script == ';')
        {
            ++script;
        }
    }
    return 0;
}
#endif

/* Keys go from the video thread, which reads the controllers once a frame, to the game thread,
 * which hands them to the keyboard controller when it polls. */
static struct
{
    uint16_t key;
    uint8_t down;
} key_queue[256];
static unsigned key_head, key_tail;
static mutex_t key_lock = LWP_MUTEX_NULL;
static volatile int quit;

static void queue_key(unsigned key, int down)
{
    LWP_MutexLock(key_lock);
    if (key_tail - key_head < sizeof key_queue / sizeof key_queue[0])
    {
        key_queue[key_tail % 256].key = (uint16_t)key;
        key_queue[key_tail % 256].down = (uint8_t)down;
        ++key_tail;
    }
    LWP_MutexUnlock(key_lock);
}

/* Several buttons may share a key: a key is down while any of them is held. */
static void read_controllers(void)
{
    INPUT_Update();
    static uint32_t before, before2;
    const uint32_t held = INPUT_PadsHeld() | stick_directions();
    const uint32_t held2 = WPAD_ButtonsHeld(1);
    const uint32_t changed = held ^ before, changed2 = held2 ^ before2;
    if (held & ~before & WPAD_BUTTON_HOME)
    {
        quit = 1;
    }
    before = held;
    before2 = held2;
    static uint8_t down_now[0x200];
    uint8_t want[0x200] = {0};
    uint8_t touched[0x200] = {0};
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
            queue_key(key, want[key]);
        }
    }
    for (unsigned code = 0; code < sizeof usb_scan_codes / sizeof usb_scan_codes[0]; ++code)
    {
        if (usb_scan_codes[code] && INPUT_KeyPressed((u8)code))
        {
            queue_key(usb_scan_codes[code], 1);
        }
        if (usb_scan_codes[code] && INPUT_KeyReleased((u8)code))
        {
            queue_key(usb_scan_codes[code], 0);
        }
    }
}

/* The game thread, about every millisecond of guest time. */
static int poll(void)
{
#ifdef V1_WII_SCRIPT
    if (run_script())
    {
        return 1;
    }
#endif
    if (key_head != key_tail)
    {
        LWP_MutexLock(key_lock);
        while (key_head != key_tail)
        {
            v1_key(key_queue[key_head % 256].key, key_queue[key_head % 256].down);
            ++key_head;
        }
        LWP_MutexUnlock(key_lock);
    }
    return quit;
}

/* --- the game ----------------------------------------------------------------------------- */

static void console(const char *text, size_t length)
{
    v3_log("console: %.*s", (int)length, text);
}

static V1Platform platform = {NULL, NULL, NULL, poll, audio, console};

enum
{
    GAME_STACK = 4 * 1024 * 1024
};

static volatile int game_done;
static int game_code;

static void *game(void *unused)
{
    (void)unused;
    game_started = 1;
    game_code = v1_run(v1_image_bin, &platform);
    v3_log("the game ended with %d after %u frames", game_code, frames);
    game_done = 1;
    return NULL;
}

int main(int argc, char **argv)
{
    vertrix_app_init(argc, argv);
    directory = vertrix_app_directory(directory);
    platform.directory = directory;
    SYS_STDIO_Report(true); /* stdout into Dolphin's OSReport log */
    video_init();
    LWP_MutexInit(&log_lock, false);
    LWP_MutexInit(&key_lock, false);
    if (fatInitDefault())
    {
        char path[96];
        snprintf(path, sizeof path, "%s/vertrix.log", directory);
        log_file = fopen(path, "w");
    }
    INPUT_Init();
    INPUT_KeyboardMapClear();
    INPUT_SetCursorMode(0);
    /* The second Wii Remote's buttons are player 1's keys, not the shared pad. */
    INPUT_IgnoreWiimoteButtons(1, 0xffffffffu);
    ASND_Init();
    ASND_Pause(0);
    v3_log("Vertrix for the Wii: %u-line TV mode%s, %u KB of image", mode->xfbHeight,
           widescreen ? ", 16:9" : "", (unsigned)(v1_image_bin_size >> 10));
    char path[96];
    snprintf(path, sizeof path, "%s/BIN1.BIN", directory);
    FILE *archive = fopen(path, "rb");
    if (!archive)
    {
        v3_log("no %s: copy the original release's files there", path);
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
        read_controllers();
        show_frame();
    }
    /* Stop the DSP voices and the controller threads before returning to the loader. */
    ASND_Pause(1);
    ASND_End();
    INPUT_Shutdown();
    if (log_file)
    {
        FILE *f = log_file;
        log_file = NULL;
        fclose(f);
    }
    vertrix_app_return();
    return game_code;
}
