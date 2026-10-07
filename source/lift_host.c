#include "lift_host.h"

#include <string.h>

#include "lift_runtime.h"

static int in_image(uint32_t address, unsigned size)
{
    return address >= LIFT_HOST_IMAGE_BASE &&
           (uint64_t)address + size <= (uint64_t)LIFT_HOST_IMAGE_BASE + LIFT_HOST_IMAGE_SIZE;
}

static int in_heap(const LiftHost *host, uint32_t address, unsigned size)
{
    return address >= LIFT_HOST_HEAP_BASE &&
           (uint64_t)address + size <= (uint64_t)LIFT_HOST_HEAP_BASE + host->heap_top;
}

static uint8_t *bytes_at(const LiftHost *host, uint32_t address, unsigned size)
{
    if (in_image(address, size))
    {
        return host->image + (address - LIFT_HOST_IMAGE_BASE);
    }
    if (in_heap(host, address, size))
    {
        return host->heap + (address - LIFT_HOST_HEAP_BASE);
    }
    return NULL;
}

uint32_t lift_host_read(const LiftHost *host, uint32_t address, unsigned size)
{
    const uint8_t *bytes = bytes_at(host, address, size);
    uint32_t value = 0;
    unsigned i;
    for (i = 0; bytes != NULL && i < size; i++)
    {
        value |= (uint32_t)bytes[i] << (8 * i);
    }
    return value;
}

static uint32_t host_read(uint32_t address, void *context)
{
    return lift_host_read(context, address, 4);
}

static void host_write(LiftHost *host, uint32_t address, unsigned size, uint32_t value)
{
    uint8_t *bytes = bytes_at(host, address, size);
    unsigned i;
    for (i = 0; bytes != NULL && i < size; i++)
    {
        bytes[i] = (uint8_t)(value >> (8 * i));
    }
}

static int host_resolve(uint32_t handle, void **storage, size_t *size, void *context)
{
    LiftHost *host = context;
    if (!in_heap(host, handle, 1))
    {
        return 0;
    }
    *storage = host->heap + (handle - LIFT_HOST_HEAP_BASE);
    *size = host->heap_top - (handle - LIFT_HOST_HEAP_BASE);
    return 1;
}

static uint32_t host_allocate(uint32_t size, void *context)
{
    LiftHost *host = context;
    uint32_t address = LIFT_HOST_HEAP_BASE + host->heap_top;
    uint32_t rounded = (size + 15u) & ~15u;
    if (rounded > host->heap_size - host->heap_top)
    {
        return 0;
    }
    memset(host->heap + host->heap_top, 0, rounded);
    host->heap_top += rounded;
    return address;
}

static uint32_t host_boundary(VertrixCallSite *site, void *context)
{
    LiftHost *host = context;
    unsigned i;
    if (site->target == LIFT_GLOBAL_STORE)
    {
        host_write(host, site->eax, site->stack, site->edx);
        return 0;
    }
    if (site->target == LIFT_HOST_ALLOCATOR || site->target == LIFT_HOST_GETMEM)
    {
        return host_allocate(site->eax, host);
    }
    host->boundary_calls++;
    for (i = 0; i < host->boundary_distinct; i++)
    {
        if (host->boundary_targets[i] == site->target)
        {
            host->boundary_counts[i]++;
            return 0;
        }
    }
    if (host->boundary_distinct < LIFT_HOST_TARGETS)
    {
        host->boundary_targets[host->boundary_distinct] = site->target;
        host->boundary_counts[host->boundary_distinct++] = 1;
    }
    return 0;
}

void lift_host_init(LiftHost *host, uint8_t *image, const uint8_t *original, uint8_t *heap,
                    uint32_t heap_size)
{
    memset(host, 0, sizeof *host);
    memcpy(image, original, LIFT_HOST_IMAGE_SIZE);
    host->image = image;
    host->heap = heap;
    host->heap_size = heap_size;
    host->inner.call = host_boundary;
    host->inner.context = host;
    host->globals.read = host_read;
    host->globals.context = host;
    host->services.resolve = host_resolve;
    host->services.allocate = host_allocate;
    host->services.context = host;
    vertrix_lifted_calls_init(&host->calls, &host->inner, &host->services, &host->globals);
}

uint32_t lift_host_run(LiftHost *host, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                       uint32_t ecx, int *lifted)
{
    VertrixCallSite site;
    *lifted = vertrix_lifted_has(target);
    if (!*lifted)
    {
        return 0;
    }
    memset(&site, 0, sizeof site);
    site.target = target;
    site.eax = eax;
    site.edx = edx;
    site.ebx = ebx;
    site.ecx = ecx;
    return host->calls.calls.call(&site, host->calls.calls.context);
}
