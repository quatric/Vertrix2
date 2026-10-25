/* Vertrix (1997) on the Nintendo DSi: the recompiled VERTRIX.EXE on the DOS machine
 * (vertrix1/runtime). The game needs about 5 MB of memory besides its code (the first two
 * megabytes of the PC and some 3 MB it asks DPMI for), more than a DS has, so the program runs in
 * the DSi's mode only: the generated code and the image are in the DSi's own load area (the
 * build names their objects *.twl.o), and a DS shows why it cannot start the game.
 *
 * The game's directory is vertrix1/ beside the .nds, or sd:/vertrix1/ (fat:/vertrix1/ on a flash
 * card), which holds the original release (BIN1.BIN, BIN2.BIN and the other files; the game
 * checks them all); it writes SETUP.CFG and its scores there. The VGA's 320x400 picture fills
 * both screens, its top half on the top screen and its bottom half on the bottom one, each half
 * scaled to 256x192 by the 2D engines. The Sound Blaster's samples play on sound channel 0, and
 * the buttons are keys:
 *
 *   D-pad            the arrow keys (one player; player 2 of two)
 *   B                Up (permute)
 *   A                Enter
 *   X, Select        Escape
 *   Start            P (pause)
 *   Y, L, R          player 1 of two, on the game's default keys: Y permutes (F), L and R move
 *                    left and right (W, X)
 *   L+R+Start        back to the loader (the game saves its setup only when left through its own
 *                    EXIT)
 *
 * The log is vertrix.log in the game's directory. */
#include <fat.h>
#include <malloc.h>
#include <nds.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "dos.h"

#include "v1_image_bin.h"

static char directory[256];

/* --- log ---------------------------------------------------------------------------------- */

static FILE *log_file;
static volatile int game_started; /* v1_clock counts from the game's start */
static Mutex log_lock;

uint64_t v3_microseconds(void)
{
    return tickGetCount() * 1000000u / TICK_FREQ;
}

void v3_sleep_ms(uint32_t ms)
{
    threadSleep(ms * 1000u);
}

void v3_log(const char *format, ...)
{
    mutexLock(&log_lock);
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
    mutexUnlock(&log_lock);
}

/* A fatal error stops the game thread; the main thread shows the message. */
static char fatal_message[256];
static volatile int game_done;
static int game_code;

_Noreturn void v3_fatal(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vsnprintf(fatal_message, sizeof fatal_message, format, args);
    va_end(args);
    v3_log("FATAL: %s", fatal_message);
    game_code = 2;
    game_done = 1;
    threadExit(2);
}

/* --- video -------------------------------------------------------------------------------- */

/* Each engine shows an 8-bit 512x256 bitmap (BG3, 128 KB: bank A on the top screen, bank C on
 * the bottom one) through its affine matrix. */
enum
{
    BITMAP_WIDTH = 512,
    BITMAP_HEIGHT = 256
};

static uint32_t *const top_bitmap = (uint32_t *)BG_BMP_RAM(0);
static uint32_t *const bottom_bitmap = (uint32_t *)BG_BMP_RAM_SUB(0);
static volatile int fresh; /* a retrace since the last copy */
static unsigned frames;

static void video_init(void)
{
    videoSetMode(MODE_5_2D | DISPLAY_BG3_ACTIVE);
    videoSetModeSub(MODE_5_2D | DISPLAY_BG3_ACTIVE);
    vramSetBankA(VRAM_A_MAIN_BG_0x06000000);
    vramSetBankC(VRAM_C_SUB_BG_0x06200000);
    REG_BG3CNT = BG_BMP8_512x256 | BG_BMP_BASE(0) | BG_WRAP_ON;
    REG_BG3CNT_SUB = BG_BMP8_512x256 | BG_BMP_BASE(0) | BG_WRAP_ON;
    memset(top_bitmap, 0, BITMAP_WIDTH * BITMAP_HEIGHT);
    memset(bottom_bitmap, 0, BITMAP_WIDTH * BITMAP_HEIGHT);
    BG_PALETTE[0] = 0;
    BG_PALETTE_SUB[0] = 0;
    REG_BG3PA = 256;
    REG_BG3PB = 0;
    REG_BG3PC = 0;
    REG_BG3PD = 256;
    REG_BG3X = 0;
    REG_BG3Y = 0;
    REG_BG3PA_SUB = 256;
    REG_BG3PB_SUB = 0;
    REG_BG3PC_SUB = 0;
    REG_BG3PD_SUB = 256;
    REG_BG3X_SUB = 0;
    REG_BG3Y_SUB = 0;
    lcdMainOnTop();
}

static void retrace(void)
{
    fresh = 1;
}

/* The CRT controller's scan-out of the planes into the two bitmaps: the four pixels of a
 * character are the four planes' bytes at one address, one 32-bit word of the bitmap (VRAM takes
 * no 8-bit writes). The game thread is stopped while this runs (it has the lower priority), so
 * the planes do not change under it. */
static void draw_vga(void)
{
    V1Scan scan;
    if (!v1_vga_scan(&scan) || scan.width < 4 || scan.height < 2)
    {
        return;
    }
    const uint32_t width = (scan.width > BITMAP_WIDTH ? BITMAP_WIDTH : scan.width) & ~3u;
    const uint32_t top_rows = (scan.height + 1) / 2; /* at most 240: each half fits a bitmap */
    for (uint32_t y = 0; y < scan.height; ++y)
    {
        uint32_t *out = y < top_rows ? top_bitmap + y * (BITMAP_WIDTH / 4)
                                     : bottom_bitmap + (y - top_rows) * (BITMAP_WIDTH / 4);
        const uint32_t row = scan.start + y * scan.pitch;
        for (uint32_t x = 0; x < width / 4; ++x)
        {
            uint32_t a = row + x;
            if (scan.dword)
            {
                a <<= 2;
            }
            a &= 0xffffu;
            out[x] = scan.planes[0][a] | (uint32_t)scan.planes[1][a] << 8 |
                     (uint32_t)scan.planes[2][a] << 16 | (uint32_t)scan.planes[3][a] << 24;
        }
    }
    uint8_t palette[256][3];
    v1_vga_palette(palette);
    for (unsigned i = 0; i < 256; ++i)
    {
        const uint16_t colour = RGB15(palette[i][0] >> 3, palette[i][1] >> 3, palette[i][2] >> 3);
        BG_PALETTE[i] = colour;
        BG_PALETTE_SUB[i] = colour;
    }
    /* Each half of the picture over a whole screen: source pixels per screen pixel in 8.8. */
    const int16_t step_x = (int16_t)(width * 256 / SCREEN_WIDTH);
    const int16_t step_y = (int16_t)(top_rows * 256 / SCREEN_HEIGHT);
    REG_BG3PA = step_x;
    REG_BG3PD = step_y;
    REG_BG3PA_SUB = step_x;
    REG_BG3PD_SUB = step_y;
}

static void show_frame(void)
{
    threadWaitForVBlank();
    if (fresh)
    {
        fresh = 0;
        draw_vga();
    }
    if (++frames % 3600 == 0)
    {
        const struct mallinfo m = mallinfo();
        v3_log("host memory: %u KB in use, %u KB free in the heap", (unsigned)(m.uordblks >> 10),
               (unsigned)(m.fordblks >> 10));
    }
}

/* --- sound -------------------------------------------------------------------------------- */

/* The samples go round a ring that channel 0 repeats; the write position keeps a short lead on
 * where the channel plays, from the time since it started. The main thread stops the channel
 * when no sound has come for a while, so the ring's old samples do not play again. */
enum
{
    SOUND_CHANNEL = 0,
    RING_SIZE = 16384, /* samples (bytes), a multiple of 32 */
    SOUND_LEAD_MS = 60,
    SOUND_IDLE_MS = 150
};

static int8_t ring[RING_SIZE] __attribute__((aligned(32)));
static Mutex sound_lock;
static uint32_t ring_rate, ring_period;
static uint64_t ring_start, last_audio; /* ticks */
static uint64_t written;                /* samples since the start */

/* Samples the channel has played since it started. */
static uint64_t played(uint64_t now)
{
    /* The channel's timer counts the sound clock, 32 ticks of the system timer's each. */
    return (now - ring_start) * (SOUND_CLOCK / TICK_FREQ) / ring_period;
}

static void flush_ring(uint32_t from, uint32_t count)
{
    const uintptr_t start = (uintptr_t)(ring + from) & ~31u;
    const uintptr_t end = ((uintptr_t)(ring + from + count) + 31u) & ~31u;
    armDCacheFlush((void *)start, end - start);
}

static void audio(const uint8_t *samples, uint32_t count, uint32_t rate)
{
    if (!count || !rate)
    {
        return;
    }
    mutexLock(&sound_lock);
    const uint64_t now = tickGetCount();
    const uint64_t lead = (uint64_t)rate * SOUND_LEAD_MS / 1000u;
    if (rate != ring_rate)
    {
        soundStop(1u << SOUND_CHANNEL);
        memset(ring, 0, sizeof ring);
        armDCacheFlush(ring, sizeof ring);
        ring_rate = rate;
        ring_period = soundTimerFromHz(rate);
        ring_start = now;
        written = lead;
        soundPreparePcm(SOUND_CHANNEL | SOUND_START, 2047, 64, ring_period, SoundMode_Repeat,
                        SoundFmt_Pcm8, ring, 0, RING_SIZE / 4);
    }
    const uint64_t at = played(now);
    if (written < at || written > at + RING_SIZE - count)
    {
        written = at + lead; /* fell behind or ran too far ahead: start again at the lead */
    }
    /* The Sound Blaster's samples are unsigned, the DS's signed. */
    uint32_t position = (uint32_t)(written % RING_SIZE);
    for (uint32_t done = 0; done < count;)
    {
        uint32_t part = RING_SIZE - position;
        part = part < count - done ? part : count - done;
        for (uint32_t i = 0; i < part; ++i)
        {
            ring[position + i] = (int8_t)(samples[done + i] ^ 0x80u);
        }
        flush_ring(position, part);
        done += part;
        position = (position + part) % RING_SIZE;
    }
    written += count;
    last_audio = now;
    mutexUnlock(&sound_lock);
}

static void sound_idle(void)
{
    mutexLock(&sound_lock);
    if (ring_rate && tickGetCount() - last_audio > ticksFromUsec(SOUND_IDLE_MS * 1000u))
    {
        soundStop(1u << SOUND_CHANNEL);
        ring_rate = 0;
    }
    mutexUnlock(&sound_lock);
}

/* --- input -------------------------------------------------------------------------------- */

/* Set 1 scan codes (0x100: the E0 prefix of the arrow keys). */
enum
{
    SCAN_ESCAPE = 0x01,
    SCAN_ENTER = 0x1c,
    SCAN_P = 0x19,
    SCAN_F = 0x21,
    SCAN_W = 0x2c,
    SCAN_X = 0x2d,
    SCAN_UP = 0x148,
    SCAN_LEFT = 0x14b,
    SCAN_RIGHT = 0x14d,
    SCAN_DOWN = 0x150
};

static const struct
{
    uint32_t button;
    unsigned key;
} button_keys[] = {{KEY_UP, SCAN_UP},       {KEY_DOWN, SCAN_DOWN},     {KEY_LEFT, SCAN_LEFT},
                   {KEY_RIGHT, SCAN_RIGHT}, {KEY_B, SCAN_UP},          {KEY_A, SCAN_ENTER},
                   {KEY_X, SCAN_ESCAPE},    {KEY_SELECT, SCAN_ESCAPE}, {KEY_START, SCAN_P},
                   {KEY_Y, SCAN_F},         {KEY_L, SCAN_W},           {KEY_R, SCAN_X}};

/* Keys go from the main thread, which reads the buttons once a frame, to the game thread, which
 * hands them to the keyboard controller when it polls. */
static struct
{
    uint16_t key;
    uint8_t down;
} key_queue[256];
static unsigned key_head, key_tail;
static Mutex key_lock;
static volatile int quit;

static void queue_key(unsigned key, int down)
{
    mutexLock(&key_lock);
    if (key_tail - key_head < sizeof key_queue / sizeof key_queue[0])
    {
        key_queue[key_tail % 256].key = (uint16_t)key;
        key_queue[key_tail % 256].down = (uint8_t)down;
        ++key_tail;
    }
    mutexUnlock(&key_lock);
}

/* Several buttons may share a key: a key is down while any of them is held. */
static void read_buttons(void)
{
    scanKeys();
    static uint32_t before;
    const uint32_t held = keysHeld();
    const uint32_t changed = held ^ before;
    before = held;
    if ((held & (KEY_L | KEY_R | KEY_START)) == (KEY_L | KEY_R | KEY_START))
    {
        quit = 1;
        return;
    }
    static uint8_t down_now[0x200];
    uint8_t want[0x200] = {0};
    uint8_t touched[0x200] = {0};
    for (unsigned k = 0; k < sizeof button_keys / sizeof button_keys[0]; ++k)
    {
        touched[button_keys[k].key] |= (changed & button_keys[k].button) != 0;
        want[button_keys[k].key] |= (held & button_keys[k].button) != 0;
    }
    for (unsigned key = 0; key < 0x200; ++key)
    {
        if (touched[key] && want[key] != down_now[key])
        {
            down_now[key] = want[key];
            queue_key(key, want[key]);
        }
    }
}

/* The game thread, about every millisecond of guest time. */
static int poll(void)
{
    if (key_head != key_tail)
    {
        mutexLock(&key_lock);
        while (key_head != key_tail)
        {
            v1_key(key_queue[key_head % 256].key, key_queue[key_head % 256].down);
            ++key_head;
        }
        mutexUnlock(&key_lock);
    }
    return quit;
}

/* --- the game ----------------------------------------------------------------------------- */

static void console(const char *text, size_t length)
{
    v3_log("console: %.*s", (int)length, text);
}

static V1Platform platform = {directory, NULL, retrace, poll, audio, console};

enum
{
    GAME_STACK = 256 * 1024,
    /* Below the main thread, which then takes the CPU at each VBlank. */
    GAME_PRIORITY = MAIN_THREAD_PRIO + 8
};

static Thread game_thread;

static int game(void *unused)
{
    (void)unused;
    game_started = 1;
    game_code = v1_run(v1_image_bin, &platform);
    v3_log("the game ended with %d after %u frames", game_code, frames);
    game_done = 1;
    return game_code;
}

/* A message on the bottom screen until a button is pressed. */
static int sound_ready; /* soundInit has run */

static void stop_with(const char *format, ...)
{
    if (sound_ready)
    {
        soundStop(1u << SOUND_CHANNEL);
    }
    videoSetModeSub(MODE_0_2D);
    vramSetBankC(VRAM_C_SUB_BG);
    consoleDemoInit();
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    printf("\n\nPress a button to leave.");
    do
    {
        threadWaitForVBlank();
        scanKeys();
    } while (!keysDown());
}

static int has_release(const char *folder)
{
    char path[sizeof directory + 16];
    snprintf(path, sizeof path, "%s/BIN1.BIN", folder);
    struct stat st;
    return stat(path, &st) == 0;
}

/* vertrix1/ beside the .nds, then on the SD card, then on a flash card. */
static int find_directory(int argc, char **argv)
{
    if (argc > 0 && argv[0] && strchr(argv[0], '/'))
    {
        snprintf(directory, sizeof directory, "%s", argv[0]);
        *strrchr(directory, '/') = '\0';
        strncat(directory, "/vertrix1", sizeof directory - strlen(directory) - 1);
        if (has_release(directory))
        {
            return 1;
        }
    }
    static const char *const places[] = {"sd:/vertrix1", "fat:/vertrix1"};
    for (unsigned i = 0; i < sizeof places / sizeof places[0]; ++i)
    {
        snprintf(directory, sizeof directory, "%s", places[i]);
        if (has_release(directory))
        {
            return 1;
        }
    }
    return 0;
}

int main(int argc, char **argv)
{
    if (!isDSiMode())
    {
        stop_with("Vertrix needs a Nintendo DSi\n(or a 3DS) in DSi mode.\n\nThe game uses about "
                  "5 MB of\nmemory, more than a DS has.");
        return 1;
    }
    setCpuClock(true);
    if (!fatInitDefault())
    {
        stop_with("Vertrix cannot read the SD card.");
        return 1;
    }
    if (!find_directory(argc, argv))
    {
        stop_with("Vertrix needs the original\nrelease (VERTRIX.EXE, BIN1.BIN,\nBIN2.BIN and the "
                  "rest) in\nsd:/vertrix1/ or in vertrix1/\nbeside the .nds.");
        return 1;
    }
    char path[sizeof directory + 16];
    snprintf(path, sizeof path, "%s/vertrix.log", directory);
    log_file = fopen(path, "w");
    video_init();
    soundInit();
    soundPowerOn();
    soundSetMixerVolume(127);
    sound_ready = 1;
    v3_log("Vertrix for the DSi: %s, %u KB of image, %u KB of heap", directory,
           (unsigned)(v1_image_bin_size >> 10),
           (unsigned)((getHeapLimit() - getHeapStart()) >> 10));

    void *stack = memalign(8, GAME_STACK);
    if (!stack)
    {
        stop_with("Vertrix is out of memory.");
        return 1;
    }
    threadPrepare(&game_thread, game, NULL, (uint8_t *)stack + GAME_STACK, GAME_PRIORITY);
    threadAttachLocalStorage(&game_thread, NULL);
    threadStart(&game_thread);
    while (!game_done && !quit)
    {
        read_buttons();
        show_frame();
        sound_idle();
    }
    /* The game thread stops at its next poll. */
    while (!game_done)
    {
        threadWaitForVBlank();
    }
    soundStop(1u << SOUND_CHANNEL);
    if (fatal_message[0])
    {
        stop_with("Vertrix stopped:\n\n%s", fatal_message);
    }
    if (log_file)
    {
        FILE *f = log_file;
        log_file = NULL;
        fclose(f);
    }
    return game_code;
}
