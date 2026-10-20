/* The Wii recomp (tools/wii_recomp_game.c) on the host: the same startup, idle handler chain,
 * device poll and scripted menu walk, with a simulated clock, writing presented frames as PPM.
 * usage: host_game IMAGE.bin VF OUT_DIR [ticks] [step_ms] [shot_every]
 * Every handler change and the frames at each `shot_every` presented frame are written to OUT_DIR;
 * the run stops after `ticks` loop iterations, or when a handler is not lifted. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jpeg_decode.h"
#include "lift_host.h"
#include "lift_runtime.h"
#include "vf.h"

enum
{
    WIDTH = 640,
    HEIGHT = 480
};

extern uint32_t vertrix_debug_watch;

/* PROFILE=1: how often each lifted routine ran, for choosing what to port to clean code. */
enum
{
    PROFILE_SLOTS = 8192
};

static struct
{
    uint32_t target;
    uint32_t count;
} profile[PROFILE_SLOTS];

static void profile_count(uint32_t target, uint32_t eax)
{
    uint32_t slot = (target * 2654435761u) % PROFILE_SLOTS;
    (void)eax;
    while (profile[slot].target != 0 && profile[slot].target != target)
    {
        slot = (slot + 1) % PROFILE_SLOTS;
    }
    profile[slot].target = target;
    profile[slot].count++;
}

static uint8_t original[LIFT_HOST_IMAGE_SIZE];
static uint8_t image[LIFT_HOST_IMAGE_SIZE];
static uint8_t heap[0x4000000];
static uint8_t second[20 * 1024 * 1024];

static void write_frame(const LiftHost *host, const char *dir, unsigned number, uint32_t handler)
{
    uint32_t width, height, pitch, bytes, base, x, y;
    char path[512];
    FILE *out;
    base = lift_host_surface(host, host->primary_surface, &width, &height, &pitch, &bytes);
    snprintf(path, sizeof path, "%s/frame%05u-%x.ppm", dir, number, (unsigned)handler);
    out = fopen(path, "wb");
    if (out == NULL || base == 0 || bytes != 4)
    {
        if (out != NULL)
        {
            fclose(out);
        }
        return;
    }
    fprintf(out, "P6\n%u %u\n255\n", (unsigned)width, (unsigned)height);
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            uint32_t value = lift_host_read(host, base + y * pitch + 4 * x, 4);
            fputc((int)((value >> 16) & 0xff), out);
            fputc((int)((value >> 8) & 0xff), out);
            fputc((int)(value & 0xff), out);
        }
    }
    fclose(out);
}

/* The scripted pointer of the Wii driver's VERTRIX_AUTOPLAY build, on the simulated clock. */
/* WAVOUT=path: every buffer the original writes to the wave device, as a WAV file. */
typedef struct
{
    FILE *file;
    uint32_t bytes, rate, channels, bits;
} WaveFile;

static void wave_header(WaveFile *wave)
{
    uint32_t block = wave->channels * wave->bits / 8;
    uint8_t h[44];
    memcpy(h, "RIFF", 4);
    h[4] = (uint8_t)(wave->bytes + 36);
    h[5] = (uint8_t)((wave->bytes + 36) >> 8);
    h[6] = (uint8_t)((wave->bytes + 36) >> 16);
    h[7] = (uint8_t)((wave->bytes + 36) >> 24);
    memcpy(h + 8, "WAVEfmt ", 8);
    h[16] = 16, h[17] = h[18] = h[19] = 0;
    h[20] = 1, h[21] = 0;
    h[22] = (uint8_t)wave->channels, h[23] = 0;
    h[24] = (uint8_t)wave->rate, h[25] = (uint8_t)(wave->rate >> 8);
    h[26] = (uint8_t)(wave->rate >> 16), h[27] = (uint8_t)(wave->rate >> 24);
    h[28] = (uint8_t)(wave->rate * block), h[29] = (uint8_t)((wave->rate * block) >> 8);
    h[30] = (uint8_t)((wave->rate * block) >> 16), h[31] = (uint8_t)((wave->rate * block) >> 24);
    h[32] = (uint8_t)block, h[33] = 0;
    h[34] = (uint8_t)wave->bits, h[35] = 0;
    memcpy(h + 36, "data", 4);
    h[40] = (uint8_t)wave->bytes, h[41] = (uint8_t)(wave->bytes >> 8);
    h[42] = (uint8_t)(wave->bytes >> 16), h[43] = (uint8_t)(wave->bytes >> 24);
    fseek(wave->file, 0, SEEK_SET);
    fwrite(h, 1, sizeof h, wave->file);
    fseek(wave->file, 0, SEEK_END);
}

static void wave_write(void *context, const uint8_t *samples, uint32_t bytes, uint32_t rate,
                       uint32_t channels, uint32_t bits)
{
    WaveFile *wave = context;
    wave->rate = rate;
    wave->channels = channels;
    wave->bits = bits;
    fwrite(samples, 1, bytes, wave->file);
    wave->bytes += bytes;
}

static void autoplay(LiftHost *host, uint32_t handler, uint32_t tick)
{
    static const struct
    {
        unsigned at;
        unsigned x, y;
    } moves[] = {{150, 320, 350}, {190, 320, 402}, {230, 320, 402}, {320, 330, 130},
                 {360, 330, 130}, {400, 415, 445}, {440, 415, 445}, {480, 415, 445}};
    static int started;
    static int pressed;
    static unsigned clicks;
    static uint32_t menu_ms;
    static unsigned last_n;
    unsigned n;
    unsigned phase;
    unsigned m;
    if (handler == 0x41b820 && !started)
    {
        started = 1;
        menu_ms = tick;
    }
    n = started ? 89 + (tick - menu_ms) / 120 : 89;
    phase = n >= 150 ? (n - 150) % 40 : 0;
    if (handler == 0x41c7b0 || handler == 0x41d0e0)
    {
        lift_host_write32(host, 0x5588f8 + 0x48,
                          handler == 0x41c7b0 ? (330u | (130u << 16)) : (415u | (445u << 16)));
    }
    if (handler == 0x41eab0 && getenv("CONTINUE") != NULL)
    {
        /* CONTINUE=yes|no: the pointer on YES or NO of the end-of-round question. */
        lift_host_write32(host, 0x5588f8 + 0x48,
                          getenv("CONTINUE")[0] == 'y' ? (465u | (440u << 16))
                                                       : (570u | (440u << 16)));
    }
    for (m = 0; m < sizeof moves / sizeof moves[0] && handler == 0x41b820; m++)
    {
        if (moves[m].at <= n && moves[m].at > last_n)
        {
            lift_host_write32(host, 0x5588f8 + 0x48, moves[m].x | (moves[m].y << 16));
        }
    }
    if (handler == 0x41b820 && getenv("MENU") != NULL && n >= 150)
    {
        /* MENU=y[,y...]: the pointer at (320, y) of the title menus, the next y after each click
         * there (title bars at y 353 + 25 * i; options bars GAME..RETURN at y 328 + 25 * i). */
        const char *cursor = getenv("MENU");
        unsigned y = (unsigned)strtoul(cursor, NULL, 10);
        unsigned k;
        for (k = 0; k < clicks; k++)
        {
            const char *comma = strchr(cursor, ',');
            if (comma == NULL)
            {
                break;
            }
            cursor = comma + 1;
            y = (unsigned)strtoul(cursor, NULL, 10);
        }
        lift_host_write32(host, 0x5588f8 + 0x48, 320u | (y << 16));
    }
    if (n >= 150 && phase >= 2 && phase < 25 && !pressed)
    {
        lift_host_mouse(host, 12, 0x80);
        pressed = 1;
    }
    if (n >= 150 && (phase >= 25 || phase < 2) && pressed)
    {
        lift_host_mouse(host, 12, 0);
        pressed = 0;
        clicks += handler == 0x41b820;
    }
    if (started)
    {
        lift_host_mouse(host, 0, 0);
    }
    last_n = n;
}

int main(int argc, char **argv)
{
    static LiftHost host;
    FILE *file;
    int lifted;
    uint32_t form;
    uint32_t display;
    uint32_t last_handler = 0;
    unsigned ticks = argc > 4 ? (unsigned)atoi(argv[4]) : 3000;
    unsigned step = argc > 5 ? (unsigned)atoi(argv[5]) : 14;
    unsigned every = argc > 6 ? (unsigned)atoi(argv[6]) : 100;
    unsigned tick;
    unsigned shots = 0;
    setvbuf(stdout, NULL, _IOLBF, 0);
    if (argc < 4 || (file = fopen(argv[1], "rb")) == NULL)
    {
        fprintf(stderr, "usage: host_game IMAGE.bin VF OUT_DIR [ticks] [step_ms] [shot_every]\n");
        return 2;
    }
    if (fread(original, 1, sizeof original, file) == 0)
    {
        fclose(file);
        return 2;
    }
    fclose(file);
    lift_host_init(&host, image, original, heap, sizeof heap);
    if (getenv("WAVOUT") != NULL)
    {
        static WaveFile wave;
        wave.file = fopen(getenv("WAVOUT"), "wb+");
        if (wave.file != NULL)
        {
            wave_header(&wave);
            host.wave_output = wave_write;
            host.wave_context = &wave;
        }
    }
    lift_host_set_heap2(&host, second, sizeof second);
    host.decode_jpeg = jpeg_decode;
    host.archive = vertrix_vf_open(argv[2]);
    if (host.archive == NULL)
    {
        fprintf(stderr, "could not open %s\n", argv[2]);
        return 2;
    }
    vertrix_lifted_set_trace(getenv("TRACE_LIFTED") != NULL);
    if (getenv("PROFILE") != NULL)
    {
        vertrix_lifted_after_hook = profile_count;
    }
    form = lift_host_allocate(&host, 0x1000);
    display = lift_host_allocate(&host, 0x800);
    lift_host_write32(&host, 0x544070, display);
    lift_host_startup(&host, &lifted);
    if (getenv("PROBE") != NULL)
    {
        /* PROBE=target,eax,edx,ebx,ecx[;...]: run routines after the startup and print eax and the
         * edx they return (comparing lifted routines with the original's in an emulator). */
        char *cursor = getenv("PROBE");
        while (*cursor != '\0')
        {
            uint32_t r[5];
            unsigned i;
            for (i = 0; i < 5; i++)
            {
                r[i] = (uint32_t)strtoul(cursor, &cursor, 16);
                if (*cursor == ',')
                {
                    cursor++;
                }
            }
            vertrix_lift_edx = r[2];
            r[0] = lift_host_run(&host, r[0], r[1], r[2], r[3], r[4], &lifted);
            printf("probe: edx:eax %08x:%08x (lifted %d)\n", (unsigned)vertrix_lift_edx,
                   (unsigned)r[0], lifted);
            while (*cursor == ';')
            {
                cursor++;
            }
        }
        return 0;
    }
    lift_host_run(&host, 0x41a080, form, 0, 0, 0, &lifted); /* master startup */
    lift_host_run(&host, 0x41a540, form, 0, 0, 0, &lifted); /* loader */
    lift_host_run(&host, 0x45dca0, 0, 0, 0, 0, &lifted);    /* sprite banks */
    lift_host_run(&host, 0x45dca0, 0, 0, 0, 0, &lifted);    /* sprite banks */
    printf("startup done: boundary calls %u (%u distinct)\n", host.boundary_calls,
           host.boundary_distinct);
    for (tick = 0; tick < ticks; tick++)
    {
        uint32_t handler = lift_host_read(&host, form + 0xbc, 4);
        unsigned before = host.frames_presented;
        host.clock_ms = tick * step;
        lift_host_thread_step(&host, &lifted);
        if (getenv("NO_AUTOPLAY") == NULL)
        {
            autoplay(&host, handler, host.clock_ms);
        }
        if (getenv("SCORE") != NULL && handler == 0x425810 && last_handler != handler)
        {
            /* SCORE=n: player 1's score (+0x174 of the player at 0x540f8c, slot 1 of the table
             * 0x540f88) when the round ends, to reach the high-score entry. */
            uint32_t player = lift_host_read(&host, 0x540f8c, 4);
            if (player != 0)
            {
                lift_host_write32(&host, player + 0x174, (uint32_t)strtoul(getenv("SCORE"), 0, 0));
            }
        }
        if (getenv("GAMEKEYS") != NULL && handler == 0x424990)
        {
            /* Player 1 during play: one key of the Wii mapping every 20 ticks, held 6 ticks
             * (left, left, up, right, down, Z, X; Enter and Space pause). */
            static const unsigned keys[] = {0xcb, 0xcb, 0xc8, 0xcd, 0xd0, 0x2c, 0x2d};
            static unsigned played;
            unsigned key = keys[(played / 20) % (sizeof keys / sizeof keys[0])];
            if (played % 20 == 0)
            {
                lift_host_key(&host, key, 1);
            }
            if (played % 20 == 6)
            {
                lift_host_key(&host, key, 0);
            }
            played++;
        }
        if (getenv("WATCHPIXEL") != NULL && getenv("WATCHTICK") != NULL)
        {
            /* WATCHPIXEL=x,y WATCHTICK=t [WATCHLEN=n]: for ticks t..t+n-1, trace the lifted calls
             * and report the writes to that pixel of the back surface. */
            unsigned from = (unsigned)atoi(getenv("WATCHTICK"));
            unsigned length = getenv("WATCHLEN") != NULL ? (unsigned)atoi(getenv("WATCHLEN")) : 1;
            int inside = tick >= from && tick < from + length;
            uint32_t width, height, pitch, bytes;
            uint32_t base =
                lift_host_surface(&host, host.back_surface, &width, &height, &pitch, &bytes);
            char *cursor = getenv("WATCHPIXEL");
            unsigned x = (unsigned)strtoul(cursor, &cursor, 10);
            unsigned y = *cursor == ',' ? (unsigned)strtoul(cursor + 1, NULL, 10) : 0;
            vertrix_debug_watch = inside && base != 0 ? base + y * pitch + bytes * x : 0;
            vertrix_lifted_set_trace(inside || getenv("TRACE_LIFTED") != NULL);
        }
        lift_host_write32(&host, 0x5328bc, 1); /* the form is active: the device poll may run */
        lift_host_run(&host, 0x4b7b80, 0, 0, 0, 0, &lifted); /* the 14 ms timer */
        if (handler != last_handler)
        {
            printf("tick %u (%u ms): handler -> %x, frames %u, heap %x/%x\n", tick,
                   (unsigned)host.clock_ms, (unsigned)handler, host.frames_presented,
                   (unsigned)host.heap_top, (unsigned)host.heap2_top);
        }
        lifted = 1;
        if (handler != 0)
        {
            lift_host_run(&host, handler, form, 0, 0, 0, &lifted);
        }
        if (!lifted)
        {
            printf("tick %u: handler %x is not lifted\n", tick, (unsigned)handler);
            break;
        }
        if (host.close_requested)
        {
            printf("tick %u: the original closed its window (EXIT)\n", tick);
            break;
        }
        if (host.frames_presented != before &&
            (handler != last_handler || host.frames_presented % every == 0))
        {
            write_frame(&host, argv[3], shots++, handler);
        }
        last_handler = handler;
    }
    write_frame(&host, argv[3], shots, last_handler);
    if (host.wave_context != NULL)
    {
        WaveFile *wave = host.wave_context;
        wave_header(wave);
        fclose(wave->file);
        printf("wave: %u bytes, %u Hz, %u channels, %u bits\n", (unsigned)wave->bytes,
               (unsigned)wave->rate, (unsigned)wave->channels, (unsigned)wave->bits);
    }
    printf("heap: top %x of %x, second %x of %x, free extents %u and %u\n", (unsigned)host.heap_top,
           (unsigned)host.heap_size, (unsigned)host.heap2_top, (unsigned)host.heap2_size,
           host.extents[0], host.extents[1]);
    printf("end: tick %u, frames presented %u, handler %x, boundary calls %u (%u distinct)\n", tick,
           host.frames_presented, (unsigned)last_handler, host.boundary_calls,
           host.boundary_distinct);
    for (unsigned i = 0; i < PROFILE_SLOTS; i++)
    {
        if (profile[i].target != 0)
        {
            printf("profile %x %u\n", (unsigned)profile[i].target, (unsigned)profile[i].count);
        }
    }
    if (getenv("PEEK") != NULL)
    {
        /* PEEK=address[,address...]: eight dwords at each address, for inspecting state. */
        char *cursor = getenv("PEEK");
        while (*cursor != '\0')
        {
            uint32_t address = (uint32_t)strtoul(cursor, &cursor, 16);
            unsigned i;
            printf("  %08x:", (unsigned)address);
            for (i = 0; i < 8; i++)
            {
                printf(" %08x", (unsigned)lift_host_read(&host, address + 4 * i, 4));
            }
            printf("\n");
            while (*cursor == ',')
            {
                cursor++;
            }
        }
    }
    if (getenv("DUMPSCENE") != NULL)
    {
        /* The three scene lists of the game frame (0x54671c, 0x546744, 0x546730; TList: items at
         * +4, count at +8) with each actor's position (+0xe, +0x16), image (+0xb4), state
         * (+0x13c), token (+0x144) and class (+0x158). */
        static const uint32_t lists[] = {0x54671c, 0x546744, 0x546730};
        unsigned l;
        for (l = 0; l < 3; l++)
        {
            uint32_t items = lift_host_read(&host, lists[l] + 4, 4);
            uint32_t count = lift_host_read(&host, lists[l] + 8, 4);
            unsigned i;
            printf("  list %x: %u actors\n", (unsigned)lists[l], (unsigned)count);
            for (i = 0; i < count && i < 400; i++)
            {
                uint32_t a = lift_host_read(&host, items + 4 * i, 4);
                printf("    [%u] %x x %d y %d image %x state %x token %x class %x\n", i,
                       (unsigned)a, (int)(int16_t)lift_host_read(&host, a + 0xe, 2),
                       (int)(int16_t)lift_host_read(&host, a + 0x16, 2),
                       (unsigned)lift_host_read(&host, a + 0xb4, 4),
                       (unsigned)lift_host_read(&host, a + 0x13c, 4),
                       (unsigned)lift_host_read(&host, a + 0x144, 4),
                       (unsigned)lift_host_read(&host, a + 0x158, 4));
            }
        }
    }
    if (getenv("PEEKSTR") != NULL)
    {
        /* PEEKSTR=table,count: the strings a table of `count` string pointers names. */
        char *cursor = getenv("PEEKSTR");
        uint32_t table = (uint32_t)strtoul(cursor, &cursor, 16);
        unsigned count = *cursor == ',' ? (unsigned)strtoul(cursor + 1, NULL, 0) : 1;
        unsigned i;
        for (i = 0; i < count; i++)
        {
            uint32_t text = lift_host_read(&host, table + 4 * i, 4);
            unsigned k;
            printf("  [%u] %08x '", i, (unsigned)text);
            for (k = 0; text != 0 && k < 80; k++)
            {
                uint32_t c = lift_host_read(&host, text + k, 1);
                if (c == 0)
                {
                    break;
                }
                putchar((int)c);
            }
            printf("'\n");
        }
    }
    {
        /* The routines the original asked for that are neither lifted nor served by the host. */
        unsigned i;
        for (i = 0; i < host.boundary_distinct; i++)
        {
            printf("  unserved %x: %u calls\n", (unsigned)host.boundary_targets[i],
                   host.boundary_counts[i]);
        }
    }
    return 0;
}
