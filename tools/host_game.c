/* The Wii lifted game (tools/wii_lifted_game.c) on the host: the same startup, idle handler chain,
 * device poll and scripted menu walk, with a simulated clock, writing presented frames as PPM.
 * usage: host_game IMAGE.bin VF OUT_DIR [ticks] [step_ms] [shot_every]
 * Every handler change and the frames at each `shot_every` presented frame are written to OUT_DIR;
 * the run stops after `ticks` loop iterations, or when a handler is not lifted. */
#include <stdio.h>
#include <stdlib.h>

#include "jpeg_decode.h"
#include "lift_host.h"
#include "vf.h"

enum
{
    WIDTH = 640,
    HEIGHT = 480
};

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
    for (m = 0; m < sizeof moves / sizeof moves[0] && handler == 0x41b820; m++)
    {
        if (moves[m].at <= n && moves[m].at > last_n)
        {
            lift_host_write32(host, 0x5588f8 + 0x48, moves[m].x | (moves[m].y << 16));
        }
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
    lift_host_set_heap2(&host, second, sizeof second);
    host.decode_jpeg = jpeg_decode;
    host.archive = vertrix_vf_open(argv[2]);
    if (host.archive == NULL)
    {
        fprintf(stderr, "could not open %s\n", argv[2]);
        return 2;
    }
    vertrix_lifted_allow_unverified(getenv("VERIFIED_ONLY") == NULL);
    form = lift_host_allocate(&host, 0x1000);
    display = lift_host_allocate(&host, 0x800);
    lift_host_write32(&host, 0x544070, display);
    lift_host_run(&host, 0x4df307, 0, 0, 0, 0, &lifted);    /* RTL thread-variable block */
    lift_host_run(&host, 0x475660, 0, 0, 0, 0, &lifted);    /* input unit initialization */
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
        if (getenv("NO_AUTOPLAY") == NULL)
        {
            autoplay(&host, handler, host.clock_ms);
        }
        lift_host_write32(&host, 0x5328bc, 1); /* the form is active: the device poll may run */
        lift_host_run(&host, 0x4b7b80, 0, 0, 0, 0, &lifted); /* the 14 ms timer */
        if (handler != last_handler)
        {
            printf("tick %u (%u ms): handler -> %x, frames %u\n", tick, (unsigned)host.clock_ms,
                   (unsigned)handler, host.frames_presented);
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
        if (host.frames_presented != before &&
            (handler != last_handler || host.frames_presented % every == 0))
        {
            write_frame(&host, argv[3], shots++, handler);
        }
        last_handler = handler;
    }
    write_frame(&host, argv[3], shots, last_handler);
    printf("end: tick %u, frames presented %u, handler %x, boundary calls %u (%u distinct)\n", tick,
           host.frames_presented, (unsigned)last_handler, host.boundary_calls,
           host.boundary_distinct);
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
