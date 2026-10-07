/* Host experiment: build the title screen with the lifted routines, then run the original's
 * frame (0x4b6200 updates, 0x4b6240 depth-sorted draws) over the scene list 0x54671c and print
 * the calls that reach the platform boundary. usage: host_title IMAGE.bin [frames] */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#include "lift_host.h"
#include "lift_imports.h"

static uint8_t original[LIFT_HOST_IMAGE_SIZE];
static uint8_t image[LIFT_HOST_IMAGE_SIZE];
static uint8_t heap[0x10000000];

static void host_store(LiftHost *host, uint32_t address, uint32_t value)
{
    unsigned i;
    for (i = 0; i < 4; i++)
    {
        if (address >= LIFT_HOST_HEAP_BASE) host->heap[address - LIFT_HOST_HEAP_BASE + i] = (uint8_t)(value >> (8 * i)); else host->image[address - LIFT_HOST_IMAGE_BASE + i] = (uint8_t)(value >> (8 * i));
    }
}

static LiftHost *current_host;

static void on_alarm(int signal)
{
    unsigned i;
    (void)signal;
    printf("TIMEOUT: %u boundary calls so far\n", current_host->boundary_calls);
    for (i = 0; i < current_host->boundary_distinct; i++)
    {
        printf("  boundary %06x x%u\n", current_host->boundary_targets[i],
               current_host->boundary_counts[i]);
    }
    _exit(3);
}

static void report(const char *what, const LiftHost *host, uint32_t result)
{
    unsigned i;
    printf("%s: result %x, %u boundary calls, heap %x\n", what, result, host->boundary_calls,
           host->heap_top);
    for (i = 0; i < host->boundary_distinct; i++)
    {
        printf("  boundary %06x x%u %s\n", host->boundary_targets[i], host->boundary_counts[i], vertrix_import_name(host->boundary_targets[i]) ? vertrix_import_name(host->boundary_targets[i]) : "");
    }
}

int main(int argc, char **argv)
{
    FILE *file;
    signal(SIGALRM, on_alarm);
    alarm(getenv("ALARM") ? atoi(getenv("ALARM")) : 20);
    setvbuf(stdout, NULL, _IOLBF, 0);
    LiftHost host;
    int lifted, frame, frames = argc > 2 ? atoi(argv[2]) : 1;
    uint32_t result, surface, pixels, wrapper;
    if (argc < 2 || (file = fopen(argv[1], "rb")) == NULL || fread(original, 1, sizeof original, file) == 0)
    {
        fprintf(stderr, "usage: host_title IMAGE.bin [frames]\n");
        return 2;
    }
    fclose(file);
    lift_host_init(&host, image, original, heap, sizeof heap);
    current_host = &host;
    host.archive = vertrix_vf_open(getenv("VF") ? getenv("VF") : "hardware-check/Vertrix2.vf");
    if (host.archive == NULL) { fprintf(stderr, "no archive\n"); return 2; }
    vertrix_lifted_allow_unverified(1);
    if (getenv("MASTER"))
    {
        uint32_t form = lift_host_allocate(&host, 0x1000);
        uint32_t display = lift_host_allocate(&host, 0x800);
        host_store(&host, 0x544070, display);
        if (getenv("TRACE")) vertrix_lifted_set_trace(1);
        result = lift_host_run(&host, 0x41a080, form, 0, 0, 0, &lifted);
        report("startup 41a080", &host, result);
        host.boundary_calls = host.boundary_distinct = 0;
        result = lift_host_run(&host, 0x41a540, form, 0, 0, 0, &lifted);
        report("load 41a540", &host, result);
        vertrix_lifted_set_trace(0);
        host.boundary_calls = host.boundary_distinct = 0;
    }
    else
    {
        uint32_t display = lift_host_allocate(&host, 0x800);
        host_store(&host, 0x544070, display);
        result = lift_host_run(&host, 0x484b60, 0x5b9c50, 0, 0x14, 0, &lifted);
        report("display init 484b60", &host, result);
        { unsigned k; for (k = 0; k < 0x100; k += 4) { if (k % 32 == 0) printf("\n%x:", 0x5b9c50 + k); printf(" %x", lift_host_read(&host, 0x5b9c50 + k, 4)); } printf("\n"); }
        printf("display object: +60 %x +64 %x +68 %x +6c %x primary %x bits %u\n", lift_host_read(&host, 0x5b9c50 + 0x60, 4),
               lift_host_read(&host, 0x5b9c50 + 0x64, 4), lift_host_read(&host, 0x5b9c50 + 0x68, 4),
               lift_host_read(&host, 0x5b9c50 + 0x6c, 4), host.primary_surface, host.display_bits);
        host.boundary_calls = host.boundary_distinct = 0;
    }
    if (!getenv("MASTER"))
    {
        result = lift_host_run(&host, 0x413bd0, 0, 0, 0, 0, &lifted);
        report("init tables 413bd0", &host, result);
        host.boundary_calls = host.boundary_distinct = 0;
        result = lift_host_run(&host, 0x45dca0, 0, 0, 0, 0, &lifted);
        report("load banks 45dca0", &host, result);
        host.boundary_calls = host.boundary_distinct = 0;
    }
    result = lift_host_run(&host, 0x465af0, 0, 0xffffffffu, 0, 0, &lifted);
    report("title build", &host, result);
    surface = lift_host_allocate(&host, 0x20);
    pixels = lift_host_allocate(&host, 640 * 480 * 4);
    host_store(&host, surface + 0, pixels);
    host_store(&host, surface + 4, 640);
    host_store(&host, surface + 8, 480);
    host_store(&host, surface + 0xc, 0x00000004); /* 4 bytes per pixel, sub-format 0 */
    host_store(&host, surface + 0x10, 0);
    host_store(&host, surface + 0x14, 640 * 4);
    {
        uint32_t items = lift_host_read(&host, 0x54671c + 4, 4), n = lift_host_read(&host, 0x54671c + 8, 4), i;
        for (i = 0; i < 6 && i < n; i++)
        {
            uint32_t a = lift_host_read(&host, items + 4 * i, 4);
            printf("actor %u at %x: x %d y %d image(+b4) %x flag(+13c) %x bank(+144) %x vt(+158) %x\n", i, a,
                   (int)(int16_t)lift_host_read(&host, a + 0xe, 2), (int)(int16_t)lift_host_read(&host, a + 0x16, 2),
                   lift_host_read(&host, a + 0xb4, 4), lift_host_read(&host, a + 0x13c, 4),
                   lift_host_read(&host, a + 0x144, 4), lift_host_read(&host, a + 0x158, 4));
        }
    }
    {
        uint32_t w, h, pitch, bytes, base = lift_host_surface(&host, host.back_surface, &w, &h, &pitch, &bytes);
        wrapper = lift_host_allocate(&host, 0x40);
        host_store(&host, wrapper + 0, base);
        host_store(&host, wrapper + 4, w);
        host_store(&host, wrapper + 8, h);
        host_store(&host, wrapper + 0xc, bytes); /* bytes per pixel; sub-format byte 0 */
        host_store(&host, wrapper + 0x10, 0);
        host_store(&host, wrapper + 0x14, pitch);
        host_store(&host, 0x5bc010, wrapper); /* the current render target */
        {
            uint32_t view = lift_host_read(&host, 0x544070, 4);
            host_store(&host, view + 0x208, 640);
            host_store(&host, view + 0x20c, 480);
        }
    }
    printf("scene list count %u\n", lift_host_read(&host, 0x54671c + 8, 4));
    for (frame = 0; frame < frames; frame++)
    {
        host.boundary_calls = host.boundary_distinct = 0;
        result = lift_host_run(&host, 0x4b6200, 0x54671c, 0, 0, 0, &lifted);
        report("update", &host, result);
        host.boundary_calls = host.boundary_distinct = 0;
        if (getenv("TRACE_DRAW")) vertrix_lifted_set_trace(1);
        result = lift_host_run(&host, 0x4b6240, 0x54671c, wrapper, 0, 0, &lifted);
        vertrix_lifted_set_trace(0);
        report("draw", &host, result);
    }
    {
        uint32_t items = lift_host_read(&host, 0x54671c + 4, 4), n = lift_host_read(&host, 0x54671c + 8, 4), i, with_image = 0;
        for (i = 0; i < n; i++)
        {
            uint32_t a = lift_host_read(&host, items + 4 * i, 4);
            with_image += lift_host_read(&host, a + 0xb4, 4) != 0;
            if (i < 4 || (i > 40 && i < 44))
            {
                printf("after: actor %u x %d y %d image %x token(+144) %x frame(+1e) %d kind(+94) %u vt %x\n", i,
                       (int)(int16_t)lift_host_read(&host, a + 0xe, 2), (int)(int16_t)lift_host_read(&host, a + 0x16, 2),
                       lift_host_read(&host, a + 0xb4, 4), lift_host_read(&host, a + 0x144, 4),
                       (int)(int16_t)lift_host_read(&host, a + 0x1e, 2), lift_host_read(&host, a + 0x94, 1),
                       lift_host_read(&host, a + 0x158, 4));
            }
        }
        printf("%u of %u actors have an image\n", with_image, n);
    }
    {
        uint32_t w, h, pitch, bytes, base = lift_host_surface(&host, host.back_surface, &w, &h, &pitch, &bytes);
        unsigned painted = 0, x, y;
        FILE *out = fopen("/tmp/title.ppm", "wb");
        if (out != NULL)
        {
            fprintf(out, "P6\n%u %u\n255\n", w, h);
        }
        for (y = 0; base != 0 && y < h; y++)
        {
            for (x = 0; x < w; x++)
            {
                uint32_t p = lift_host_read(&host, base + y * pitch + x * bytes, bytes);
                painted += (p & 0xffffff) != 0;
                if (out != NULL)
                {
                    fputc(bytes == 4 ? (p >> 16) & 255 : p & 255, out);
                    fputc(bytes == 4 ? (p >> 8) & 255 : p & 255, out);
                    fputc(bytes == 4 ? p & 255 : p & 255, out);
                }
            }
        }
        if (out != NULL)
        {
            fclose(out);
        }
        printf("back buffer %ux%u, %u bytes per pixel, non-zero pixels after drawing: %u\n", w, h, bytes, painted);
    }
    return 0;
}
