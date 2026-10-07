/* Host probe: run one lifted routine through the dispatcher against the original's static data
 * and a heap arena, and print every call that reaches the platform boundary.
 * usage: host_probe IMAGE.bin ADDRESS   (IMAGE.bin: the mapped PE image from 0x400000, see
 * tools/dump_image.py) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lifted_dispatch.h"

enum
{
    IMAGE_BASE = 0x400000,
    IMAGE_SIZE = 0x200000,
    HEAP_BASE = 0x1000000,
    HEAP_SIZE = 0x400000
};

static uint8_t image[IMAGE_SIZE];
static uint8_t heap[HEAP_SIZE];
static uint32_t heap_top;
static unsigned boundary_calls;

static uint32_t global_read(uint32_t address, void *context)
{
    uint32_t value = 0;
    (void)context;
    if (address >= IMAGE_BASE && address + 4 <= IMAGE_BASE + IMAGE_SIZE)
    {
        memcpy(&value, image + (address - IMAGE_BASE), 4);
    }
    else if (address >= HEAP_BASE && address + 4 <= HEAP_BASE + HEAP_SIZE)
    {
        memcpy(&value, heap + (address - HEAP_BASE), 4);
    }
    return value;
}

static int resolve(uint32_t handle, void **storage, size_t *size, void *context)
{
    (void)context;
    if (handle < HEAP_BASE || handle >= HEAP_BASE + heap_top)
    {
        return 0;
    }
    *storage = heap + (handle - HEAP_BASE);
    *size = heap_top - (handle - HEAP_BASE);
    return 1;
}

static uint32_t allocate(uint32_t size, void *context)
{
    uint32_t address = HEAP_BASE + heap_top;
    (void)context;
    heap_top += (size + 15u) & ~15u;
    return heap_top > HEAP_SIZE ? 0 : address;
}

static uint32_t boundary(VertrixCallSite *site, void *context)
{
    (void)context;
    if (site->target == 0xf0000000u)
    {
        unsigned width = site->stack;
        if (site->eax >= IMAGE_BASE && site->eax + width <= IMAGE_BASE + IMAGE_SIZE)
        {
            memcpy(image + (site->eax - IMAGE_BASE), &site->edx, width);
        }
        return 0;
    }
    if (site->target == 0x4ca000u)
    {
        return allocate(site->eax, NULL);
    }
    boundary_calls++;
    printf("boundary %06x eax=%x edx=%x ebx=%x ecx=%x stack=%x,%x\n", site->target, site->eax,
           site->edx, site->ebx, site->ecx, site->stack, site->stack_next);
    return 0;
}

int main(int argc, char **argv)
{
    FILE *file;
    VertrixCalls inner = {boundary, NULL};
    VertrixGlobals globals = {global_read, NULL};
    VertrixFactoryServices services;
    VertrixLiftedCalls adapter;
    VertrixCallSite site;
    uint32_t result;
    if (argc < 3 || (file = fopen(argv[1], "rb")) == NULL)
    {
        fprintf(stderr, "usage: host_probe IMAGE.bin ADDRESS\n");
        return 2;
    }
    if (fread(image, 1, IMAGE_SIZE, file) == 0)
    {
        return 2;
    }
    fclose(file);
    memset(&services, 0, sizeof services);
    services.resolve = resolve;
    services.allocate = allocate;
    vertrix_lifted_calls_init(&adapter, &inner, &services, &globals);
    memset(&site, 0, sizeof site);
    site.target = (uint32_t)strtoul(argv[2], NULL, 16);
    if (!vertrix_lifted_has(site.target))
    {
        fprintf(stderr, "%x is not lifted\n", site.target);
        return 1;
    }
    result = adapter.calls.call(&site, adapter.calls.context);
    printf("result %x, %u boundary calls, heap %x\n", result, boundary_calls, heap_top);
    return 0;
}
