#include "lift_host.h"

#include <string.h>

#include "lift_imports.h"

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

uint32_t lift_host_allocate(LiftHost *host, uint32_t size)
{
    return host_allocate(size, host);
}

static uint32_t site_argument(const VertrixCallSite *site, unsigned index)
{
    return index == 0   ? site->stack
           : index == 1 ? site->stack_next
           : index == 2 ? site->stack_third
                        : site->stack_rest[index - 3];
}

static uint32_t host_string_length(LiftHost *host, uint32_t address)
{
    uint32_t length = 0;
    while (bytes_at(host, address + length, 1) != NULL && *bytes_at(host, address + length, 1) != 0)
    {
        length++;
    }
    return length;
}

/* The Win32 imports the original's runtime reaches, served on the host. Returns 1 and the result
 * in *result when the import is implemented. Arguments are the stdcall stack dwords. */
static int host_import(LiftHost *host, const VertrixCallSite *site, const char *name,
                       uint32_t *result)
{
    uint32_t a0 = site_argument(site, 0), a1 = site_argument(site, 1), a2 = site_argument(site, 2);
    if (strcmp(name, "lstrlenA") == 0)
    {
        *result = host_string_length(host, a0);
    }
    else if (strcmp(name, "lstrcpynA") == 0 || strcmp(name, "lstrcpyA") == 0)
    {
        uint32_t length = host_string_length(host, a1);
        uint32_t limit = strcmp(name, "lstrcpynA") == 0 ? (a2 == 0 ? 0 : a2 - 1) : length;
        uint32_t i;
        if (limit > length)
        {
            limit = length;
        }
        for (i = 0; i < limit; i++)
        {
            host_write(host, a0 + i, 1, lift_host_read(host, a1 + i, 1));
        }
        if (strcmp(name, "lstrcpynA") != 0 || a2 != 0)
        {
            host_write(host, a0 + limit, 1, 0);
        }
        *result = a0;
    }
    else if (strcmp(name, "InterlockedDecrement") == 0 || strcmp(name, "InterlockedIncrement") == 0)
    {
        *result = lift_host_read(host, a0, 4) + (name[11] == 'D' ? 0xffffffffu : 1u);
        host_write(host, a0, 4, *result);
    }
    else if (strcmp(name, "InterlockedExchange") == 0)
    {
        *result = lift_host_read(host, a0, 4);
        host_write(host, a0, 4, a1);
    }
    else if (strcmp(name, "GlobalAlloc") == 0 || strcmp(name, "LocalAlloc") == 0)
    {
        *result = host_allocate(a1, host);
    }
    else if (strcmp(name, "GlobalLock") == 0 || strcmp(name, "GlobalHandle") == 0 ||
             strcmp(name, "GlobalReAlloc") == 0)
    {
        *result = a0;
    }
    else if (strcmp(name, "GetVersion") == 0)
    {
        *result = 0x0a280005u; /* Windows XP style: major 5, minor 1 packs as 0x0a280105 */
    }
    else if (strcmp(name, "GlobalFree") == 0 || strcmp(name, "LocalFree") == 0 ||
             strcmp(name, "GlobalUnlock") == 0 || strcmp(name, "InitializeCriticalSection") == 0 ||
             strcmp(name, "DeleteCriticalSection") == 0 ||
             strcmp(name, "EnterCriticalSection") == 0 ||
             strcmp(name, "LeaveCriticalSection") == 0 || strcmp(name, "SetLastError") == 0 ||
             strcmp(name, "GetLastError") == 0)
    {
        *result = 0;
    }
    else
    {
        return 0;
    }
    return 1;
}

static uint32_t host_boundary(VertrixCallSite *site, void *context)
{
    LiftHost *host = context;
    unsigned i;
    {
        uint32_t slot = vertrix_import_slot(host->image, LIFT_HOST_IMAGE_BASE, site->target);
        const char *name = vertrix_import_name(slot);
        uint32_t result;
        if (name != NULL && host_import(host, site, name, &result))
        {
            return result;
        }
        site->target = slot;
    }
    if (site->target == 0x4d88a0)
    {
        host_list_insert(host, site->eax, site->edx, site->ecx, site->ebx);
        return site->eax;
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
