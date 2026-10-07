/* Host experiment: build the title screen with the lifted routines, then run the original's
 * frame (0x4b6200 updates, 0x4b6240 depth-sorted draws) over the scene list 0x54671c and print
 * the calls that reach the platform boundary. usage: host_title IMAGE.bin [frames] */
#include <stdio.h>
#include <stdlib.h>

#include "lift_host.h"
#include "lift_imports.h"

static uint8_t original[LIFT_HOST_IMAGE_SIZE];
static uint8_t image[LIFT_HOST_IMAGE_SIZE];
static uint8_t heap[0x800000];

static void host_store(LiftHost *host, uint32_t address, uint32_t value)
{
    unsigned i;
    for (i = 0; i < 4; i++)
    {
        host->heap[address - LIFT_HOST_HEAP_BASE + i] = (uint8_t)(value >> (8 * i));
    }
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
    LiftHost host;
    int lifted, frame, frames = argc > 2 ? atoi(argv[2]) : 1;
    uint32_t result, surface, pixels;
    if (argc < 2 || (file = fopen(argv[1], "rb")) == NULL || fread(original, 1, sizeof original, file) == 0)
    {
        fprintf(stderr, "usage: host_title IMAGE.bin [frames]\n");
        return 2;
    }
    fclose(file);
    lift_host_init(&host, image, original, heap, sizeof heap);
    vertrix_lifted_allow_unverified(1);
    result = lift_host_run(&host, 0x45dca0, 0, 0, 0, 0, &lifted);
    report("load banks 45dca0", &host, result);
    host.boundary_calls = host.boundary_distinct = 0;
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
    printf("scene list count %u\n", lift_host_read(&host, 0x54671c + 8, 4));
    for (frame = 0; frame < frames; frame++)
    {
        host.boundary_calls = host.boundary_distinct = 0;
        result = lift_host_run(&host, 0x4b6200, 0x54671c, 0, 0, 0, &lifted);
        report("update", &host, result);
        host.boundary_calls = host.boundary_distinct = 0;
        result = lift_host_run(&host, 0x4b6240, 0x54671c, surface, 0, 0, &lifted);
        report("draw", &host, result);
    }
    {
        unsigned painted = 0, i;
        for (i = 0; i < 640 * 480; i++)
        {
            painted += lift_host_read(&host, pixels + 4 * i, 4) != 0;
        }
        printf("non-zero pixels after drawing: %u\n", painted);
    }
    return 0;
}
