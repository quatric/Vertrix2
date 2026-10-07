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

static void host_write(LiftHost *host, uint32_t address, unsigned size, uint32_t value);

/* Move (0x4e1140): eax = destination, edx = source, ebx = byte count; overlap-safe. */
static void host_move(LiftHost *host, uint32_t destination, uint32_t source, uint32_t count)
{
    uint8_t *to = bytes_at(host, destination, count);
    uint8_t *from = bytes_at(host, source, count);
    if (to != NULL && from != NULL && count != 0)
    {
        memmove(to, from, count);
    }
}

/* TList insert (0x4d88a0): eax = list, edx = index, ecx = number of slots, ebx = the value stored
 * in each new slot. A list is { +4 items, +8 count, +0xc capacity }; 0x4d8770 resizes it. */
static void host_list_insert(LiftHost *host, uint32_t list, uint32_t index, uint32_t count,
                             uint32_t value)
{
    VertrixCallSite resize;
    uint32_t old = lift_host_read(host, list + 8, 4);
    uint32_t items;
    uint32_t i;
    memset(&resize, 0, sizeof resize);
    resize.target = 0x4d8770;
    resize.eax = list;
    resize.edx = (index >= old ? index : old) + count;
    resize.ebx = 0xffffffffu;
    host->calls.calls.call(&resize, host->calls.calls.context);
    items = lift_host_read(host, list + 4, 4);
    if (index < old)
    {
        host_move(host, items + (index + count) * 4, items + index * 4, (old - index) * 4);
        if (count != 0 && bytes_at(host, items + index * 4, count * 4) != NULL)
        {
            memset(bytes_at(host, items + index * 4, count * 4), 0, count * 4);
        }
    }
    for (i = 0; i < count; i++)
    {
        host_write(host, items + (index + i) * 4, 4, value);
    }
}

static uint32_t host_boundary(VertrixCallSite *site, void *context)
{
    LiftHost *host = context;
    unsigned i;
    if (site->target == 0x4d88a0)
    {
        host_list_insert(host, site->eax, site->edx, site->ecx, site->ebx);
        return site->eax;
    }
    if (site->target == 0x4f1d24) /* KERNEL32 lstrlenA(stack[0]) */
    {
        uint32_t length = 0;
        while (bytes_at(host, site->stack + length, 1) != NULL &&
               *bytes_at(host, site->stack + length, 1) != 0)
        {
            length++;
        }
        return length;
    }
    if (site->target == 0x4f1c34) /* KERNEL32 InterlockedDecrement(stack[0]) */
    {
        uint32_t value = lift_host_read(host, site->stack, 4) - 1;
        host_write(host, site->stack, 4, value);
        return value;
    }
    if (site->target == 0x482310) /* mov [eax + 0x30], 0x516b94; ret */
    {
        host_write(host, site->eax + 0x30, 4, 0x516b94);
        return site->eax;
    }
    if (site->target == 0x4e04f4)
    {
        return site->eax; /* a bare ret */
    }
    if (site->target == 0x4eb5e0)
    {
        host_move(host, site->eax, site->edx, site->ebx); /* copy edx to eax, ebx bytes */
        return site->eax;
    }
    if (site->target == 0x4e1140)
    {
        host_move(host, site->eax, site->edx, site->ebx);
        return site->eax;
    }
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
