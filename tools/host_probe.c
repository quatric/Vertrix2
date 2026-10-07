/* Host probe: run one lifted routine through the dispatcher against the original's static data
 * and a heap arena, and print the calls that reach the platform boundary.
 * usage: host_probe IMAGE.bin ADDRESS   (IMAGE.bin from tools/dump_image.py) */
#include <stdio.h>
#include <stdlib.h>

#include "lift_host.h"

static uint8_t original[LIFT_HOST_IMAGE_SIZE];
static uint8_t image[LIFT_HOST_IMAGE_SIZE];
static uint8_t heap[0x400000];

int main(int argc, char **argv)
{
    FILE *file;
    LiftHost host;
    int lifted;
    uint32_t target, result;
    unsigned i;
    if (argc < 3 || (file = fopen(argv[1], "rb")) == NULL)
    {
        fprintf(stderr, "usage: host_probe IMAGE.bin ADDRESS\n");
        return 2;
    }
    if (fread(original, 1, sizeof original, file) == 0)
    {
        return 2;
    }
    fclose(file);
    lift_host_init(&host, image, original, heap, sizeof heap);
    target = (uint32_t)strtoul(argv[2], NULL, 16);
    result = lift_host_run(&host, target, 0, 0xffffffffu, 0, 0, &lifted);
    if (!lifted)
    {
        fprintf(stderr, "%x is not lifted\n", target);
        return 1;
    }
    for (i = 0; i < host.boundary_distinct; i++)
    {
        printf("boundary %06x x%u\n", host.boundary_targets[i], host.boundary_counts[i]);
    }
    printf("result %x, %u boundary calls, heap %x\n", result, host.boundary_calls, host.heap_top);
    return 0;
}
