#include "lift_host.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lift_imports.h"

#include "lift_runtime.h"

/* Set by the Wii driver to list the files the original opens. */
int lift_host_trace_files;
#include "palette_tables.h"
#include "rtl_double_add.h"
#include "rtl_double_multiply.h"
#include "rtl_float.h"
#include "rtl_single_divide.h"
#include "rtl_single_multiply.h"

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

static int in_heap2(const LiftHost *host, uint32_t address, unsigned size)
{
    return host->heap2 != NULL && address >= LIFT_HOST_HEAP2_BASE &&
           (uint64_t)address + size <= (uint64_t)LIFT_HOST_HEAP2_BASE + host->heap2_top;
}

static uint8_t *bytes_at(const LiftHost *host, uint32_t address, unsigned size)
{
    if (in_heap2(host, address, size))
    {
        return host->heap2 + (address - LIFT_HOST_HEAP2_BASE);
    }
    if (in_image(address, size))
    {
        return host->image + (address - LIFT_HOST_IMAGE_BASE);
    }
    if (in_heap(host, address, size))
    {
        return host->heap + (address - LIFT_HOST_HEAP_BASE);
    }
    {
        unsigned frame = vertrix_lifted_depth();
        while (frame-- > 0)
        {
            const LiftEnv *env = frame < LIFT_FRAME_LIMIT ? vertrix_lift_frames[frame] : NULL;
            if (env != NULL && lift_in_stack(env, address, size))
            {
                return env->stack + (address - env->low);
            }
            if (env != NULL && lift_in_passed(env, address, size))
            {
                return ((LiftEnv *)env)->passed + (address - env->passed_low);
            }
        }
    }
    return NULL;
}

const uint8_t *lift_host_bytes(const LiftHost *host, uint32_t address, uint32_t size)
{
    return bytes_at(host, address, size);
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
    if (vertrix_debug_watch != 0 && vertrix_debug_watch >= address &&
        vertrix_debug_watch < address + size)
        printf("WATCH host_write %x = %x\n", (unsigned)address, (unsigned)value);
    uint8_t *bytes = bytes_at(host, address, size);
    unsigned i;
    for (i = 0; bytes != NULL && i < size; i++)
    {
        bytes[i] = (uint8_t)(value >> (8 * i));
    }
}

/* vertrix_lift_store_hook: the lifted stores to globals, without the LIFT_GLOBAL_STORE call. */
static void host_store_hook(void *context, uint32_t address, unsigned size, uint32_t value)
{
    host_write(context, address, size, value);
}

static int host_resolve(uint32_t handle, void **storage, size_t *size, void *context)
{
    LiftHost *host = context;
    if (in_heap2(host, handle, 1))
    {
        *storage = host->heap2 + (handle - LIFT_HOST_HEAP2_BASE);
        *size = host->heap2_top - (handle - LIFT_HOST_HEAP2_BASE);
        return 1;
    }
    if (!in_heap(host, handle, 1))
    {
        return 0;
    }
    *storage = host->heap + (handle - LIFT_HOST_HEAP_BASE);
    *size = host->heap_top - (handle - LIFT_HOST_HEAP_BASE);
    return 1;
}

extern uint32_t vertrix_lifted_skip[8];

static uint8_t *region_bytes(const LiftHost *host, unsigned region, uint32_t offset)
{
    return (region ? host->heap2 : host->heap) + offset;
}

static uint32_t region_get32(const LiftHost *host, unsigned region, uint32_t offset)
{
    const uint8_t *p = region_bytes(host, region, offset);
    return (uint32_t)p[0] | (uint32_t)p[1] << 8 | (uint32_t)p[2] << 16 | (uint32_t)p[3] << 24;
}

static void region_put32(LiftHost *host, unsigned region, uint32_t offset, uint32_t value)
{
    uint8_t *p = region_bytes(host, region, offset);
    p[0] = (uint8_t)value;
    p[1] = (uint8_t)(value >> 8);
    p[2] = (uint8_t)(value >> 16);
    p[3] = (uint8_t)(value >> 24);
}

static uint32_t heap_get32(const LiftHost *host, uint32_t offset)
{
    return region_get32(host, 0, offset);
}

static void heap_put32(LiftHost *host, uint32_t offset, uint32_t value)
{
    region_put32(host, 0, offset, value);
}

enum
{
    BIG_BLOCK = 1024u * 16u,  /* larger blocks go to the extents, smaller ones to the bins */
    SPLIT_REST = 64u * 1024u, /* an extent is split when at least this much is left over */
    HEAP2_SIZE = 0x100000u    /* requests of this size or more use the second heap first */
};

/* Writes the 16-byte header of a block at `start` (rounded size, freed flag, capacity) and clears
 * its payload; returns the block's address. */
static uint32_t block_open(LiftHost *host, unsigned region, uint32_t start, uint32_t rounded,
                           uint32_t capacity)
{
    memset(region_bytes(host, region, start), 0, 16u + capacity);
    region_put32(host, region, start, rounded);
    region_put32(host, region, start + 8u, capacity);
    return (region ? LIFT_HOST_HEAP2_BASE : LIFT_HOST_HEAP_BASE) + start + 16u;
}

/* The smallest free extent of `region` holding `need` bytes (header included), split when the rest
 * is large; returns the block address, or 0. */
static uint32_t extent_take(LiftHost *host, unsigned region, uint32_t rounded, uint32_t need)
{
    unsigned i, best = LIFT_HOST_EXTENTS;
    uint32_t start, length;
    for (i = 0; i < host->extents[region]; i++)
    {
        if (host->extent_length[region][i] >= need &&
            (best == LIFT_HOST_EXTENTS ||
             host->extent_length[region][i] < host->extent_length[region][best]))
        {
            best = i;
        }
    }
    if (best == LIFT_HOST_EXTENTS)
    {
        return 0;
    }
    start = host->extent_at[region][best];
    length = host->extent_length[region][best];
    if (length - need >= SPLIT_REST)
    {
        host->extent_at[region][best] += need;
        host->extent_length[region][best] -= need;
        length = need;
    }
    else
    {
        host->extents[region]--;
        host->extent_at[region][best] = host->extent_at[region][host->extents[region]];
        host->extent_length[region][best] = host->extent_length[region][host->extents[region]];
    }
    return block_open(host, region, start, rounded, length - 16u);
}

/* Returns the block at header offset `start` (`length` bytes with the header) to the extents of
 * `region`, merged with the free extents next to it. */
static void extent_give(LiftHost *host, unsigned region, uint32_t start, uint32_t length)
{
    unsigned i = 0;
    while (i < host->extents[region])
    {
        uint32_t at = host->extent_at[region][i], size = host->extent_length[region][i];
        if (at + size == start || start + length == at)
        {
            start = at < start ? at : start;
            length += size;
            host->extents[region]--;
            host->extent_at[region][i] = host->extent_at[region][host->extents[region]];
            host->extent_length[region][i] = host->extent_length[region][host->extents[region]];
            i = 0;
            continue;
        }
        i++;
    }
    if (host->extents[region] < LIFT_HOST_EXTENTS)
    {
        host->extent_at[region][host->extents[region]] = start;
        host->extent_length[region][host->extents[region]] = length;
        host->extents[region]++;
    }
}

/* Every block carries a 16-byte header (rounded size, freed flag, capacity). A freed block of up to
 * 16 KB goes to the bin of its size and the next request of that size takes it again; larger ones
 * return to the free extents of their heap, so the screens' image buffers, allocated again for
 * every screen, do not use up the Wii's memory. */
static uint32_t host_allocate(uint32_t size, void *context)
{
    LiftHost *host = context;
    uint32_t rounded = (size + 15u) & ~15u;
    /* A slack after the large pixel buffers: the load screen's progress bar copies a row
     * wider than the target once its step count passes the total, and the next block must
     * not be the surface object that follows. */
    uint32_t slack = size >= 0x10000u ? 0x4000u : 0u;
    uint32_t bin = rounded / 16u, offset, block;
    if (size >= HEAP2_SIZE && host->heap2 != NULL)
    {
        block = extent_take(host, 1, rounded, 16u + rounded + slack);
        if (block != 0)
        {
            return block;
        }
        if (16u + rounded + slack <= host->heap2_size - host->heap2_top)
        {
            offset = host->heap2_top;
            host->heap2_top += 16u + rounded + slack;
            return block_open(host, 1, offset, rounded, rounded + slack);
        }
    }
    if (getenv("TRACE_ALLOC") && size >= 0x20000u)
        fprintf(stderr, "alloc %u at top %x\n", (unsigned)size, (unsigned)host->heap_top);
    if (slack == 0 && bin < 1025u && host->free_bins[bin] != 0)
    {
        offset = host->free_bins[bin] - LIFT_HOST_HEAP_BASE;
        host->free_bins[bin] = heap_get32(host, offset);
        memset(host->heap + offset, 0, rounded);
        heap_put32(host, offset - 12, 0);
        return LIFT_HOST_HEAP_BASE + offset;
    }
    if (rounded > BIG_BLOCK)
    {
        block = extent_take(host, 0, rounded, 16u + rounded + slack);
        if (block != 0)
        {
            return block;
        }
    }
    if (16u + rounded + slack > host->heap_size - host->heap_top)
    {
        static int reported;
        if (!reported++)
        {
            fprintf(stderr, "heap full: request %u, top %x of %x, second %x of %x, extents %u/%u\n",
                    (unsigned)size, (unsigned)host->heap_top, (unsigned)host->heap_size,
                    (unsigned)host->heap2_top, (unsigned)host->heap2_size, host->extents[0],
                    host->extents[1]);
        }
        return 0;
    }
    offset = host->heap_top;
    host->heap_top += 16u + rounded + slack;
    return block_open(host, 0, offset, rounded, rounded + slack);
}

/* The usable size of a live host block, or 0 when `address` is not the start of one. */
static uint32_t host_block_size(LiftHost *host, uint32_t address)
{
    unsigned region;
    uint32_t offset, rounded, top;
    if (host->heap2 != NULL && address >= LIFT_HOST_HEAP2_BASE + 16u &&
        address - LIFT_HOST_HEAP2_BASE < host->heap2_top)
    {
        region = 1;
        offset = address - LIFT_HOST_HEAP2_BASE;
    }
    else if (address >= LIFT_HOST_HEAP_BASE + 16u && address - LIFT_HOST_HEAP_BASE < host->heap_top)
    {
        region = 0;
        offset = address - LIFT_HOST_HEAP_BASE;
    }
    else
    {
        return 0;
    }
    rounded = region_get32(host, region, offset - 16u);
    top = region ? host->heap2_top : host->heap_top;
    if (rounded == 0 || (rounded & 15u) != 0 || region_get32(host, region, offset - 12u) != 0 ||
        region_get32(host, region, offset - 8u) < rounded ||
        offset + region_get32(host, region, offset - 8u) > top)
    {
        return 0;
    }
    return rounded;
}

static void host_release(LiftHost *host, uint32_t address)
{
    unsigned region;
    uint32_t offset, rounded, top;
    if (host->heap2 != NULL && address >= LIFT_HOST_HEAP2_BASE + 16u &&
        address - LIFT_HOST_HEAP2_BASE < host->heap2_top)
    {
        region = 1;
        offset = address - LIFT_HOST_HEAP2_BASE;
    }
    else if (address >= LIFT_HOST_HEAP_BASE + 16u && address - LIFT_HOST_HEAP_BASE < host->heap_top)
    {
        region = 0;
        offset = address - LIFT_HOST_HEAP_BASE;
    }
    else
    {
        return;
    }
    rounded = region_get32(host, region, offset - 16u);
    top = region ? host->heap2_top : host->heap_top;
    if (rounded == 0 || (rounded & 15u) != 0 || region_get32(host, region, offset - 12u) != 0 ||
        region_get32(host, region, offset - 8u) < rounded ||
        offset + region_get32(host, region, offset - 8u) > top)
    {
        return; /* not the start of a live block */
    }
    region_put32(host, region, offset - 12u, 1);
    if (region == 1 || rounded > BIG_BLOCK)
    {
        extent_give(host, region, offset - 16u, 16u + region_get32(host, region, offset - 8u));
        return;
    }
    if (getenv("TRACE_FREE"))
        fprintf(stderr, "free %x size %u\n", (unsigned)address, (unsigned)rounded);
    heap_put32(host, offset, host->free_bins[rounded / 16u]);
    host->free_bins[rounded / 16u] = address;
}

static void host_write(LiftHost *host, uint32_t address, unsigned size, uint32_t value);

/* Move (0x4e1140): eax = destination, edx = source, ebx = byte count; overlap-safe. */
static void host_move(LiftHost *host, uint32_t destination, uint32_t source, uint32_t count)
{
    if (vertrix_debug_watch != 0 && vertrix_debug_watch >= destination &&
        vertrix_debug_watch < destination + count)
        printf("WATCH move dst %x src %x count %u\n", (unsigned)destination, (unsigned)source,
               (unsigned)count);
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

enum
{
    LIFT_COM_BASE = 0xe0000000u,
    COM_DRAW = 1,
    COM_SURFACE = 2,
    COM_INPUT = 3,
    COM_DEVICE = 4
};

static uint32_t host_com_object(LiftHost *host, unsigned interface_id);

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

/* Look a path up in the archive: drops a leading ".\\" or drive, folds separators. */
static int host_find_file(LiftHost *host, uint32_t name, uint32_t *index)
{
    char text[300];
    unsigned length = 0;
    const char *start = text;
    if (host->archive == NULL)
    {
        return 0;
    }
    while (length < sizeof text - 1 && lift_host_read(host, name + length, 1) != 0)
    {
        text[length] = (char)lift_host_read(host, name + length, 1);
        length++;
    }
    text[length] = 0;
    {
        int found = vertrix_vf_find(host->archive, start, index);
        if (lift_host_trace_files || getenv("TRACE_FILES"))
        {
            printf("file %s -> %d\n", text, found);
        }
        return found;
    }
}

/* The Win32 imports the original's runtime reaches, served on the host. Returns 1 and the result
 * in *result when the import is implemented. Arguments are the stdcall stack dwords. */
/* Mark the queued wave headers whose play time has passed as done (WHDR_DONE, out of the queue);
 * with `all`, the head one regardless of the clock. */
static void wave_advance(LiftHost *host, int all)
{
    uint64_t now = (uint64_t)host->clock_ms * 1000u;
    while (host->wave_count > 0 && (all || now >= host->wave_head_end_us))
    {
        uint32_t header = host->wave_queue[0];
        unsigned i;
        host_write(host, header + 16, 4, (lift_host_read(host, header + 16, 4) & ~0x10u) | 1u);
        for (i = 1; i < host->wave_count; i++)
        {
            host->wave_queue[i - 1] = host->wave_queue[i];
        }
        host->wave_count--;
        if (host->wave_count > 0)
        {
            uint32_t length = lift_host_read(host, host->wave_queue[0] + 4, 4);
            host->wave_head_end_us += (uint64_t)length * 1000000u / host->wave_bytes_per_second;
        }
        if (all)
        {
            return;
        }
    }
}

static int host_import(LiftHost *host, const VertrixCallSite *site, const char *name,
                       uint32_t *result)
{
    uint32_t a0 = site_argument(site, 0), a1 = site_argument(site, 1), a2 = site_argument(site, 2);
    if (getenv("TRACE_IMPORTS"))
    {
        printf("import %s(%x, %x, %x)\n", name, (unsigned)a0, (unsigned)a1, (unsigned)a2);
    }
    if (strcmp(name, "timeSetEvent") == 0) /* (delay, resolution, proc, user, flags) */
    {
        host->timer_period = a0;
        host->timer_proc = a2;
        host->timer_user = site_argument(site, 3);
        *result = 1;
    }
    else if (strcmp(name, "CoCreateInstance") ==
             0) /* (clsid, outer, context, iid, out): no COM classes */
    {
        host_write(host, site_argument(site, 4), 4, 0);
        *result = 0x80040154u; /* REGDB_E_CLASSNOTREG */
    }
    else if (strcmp(name, "DirectInput8Create") == 0) /* (instance, version, iid, out, outer) */
    {
        uint32_t input = getenv("NODI") ? 0 : host_com_object(host, COM_INPUT);
        if (getenv("NODI"))
        {
            host_write(host, site_argument(site, 3), 4, 0);
            *result = 0x80004002u;
            return 1;
        }
        host_write(host, site_argument(site, 3), 4, input);
        *result = input == 0 ? 0x8007000eu : 0;
    }
    else if (strcmp(name, "CoInitialize") == 0 || strcmp(name, "CoUninitialize") == 0 ||
             strcmp(name, "CoInitializeEx") == 0)
    {
        *result = 0;
    }
    else if (strcmp(name, "timeGetTime") == 0 || strcmp(name, "GetTickCount") == 0)
    {
        *result = host->clock_ms;
        host->clock_ms += 1; /* a routine that waits on the clock sees it move */
    }
    else if (strcmp(name, "lstrlenA") == 0)
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
    else if (strcmp(name, "GlobalLock") == 0 || strcmp(name, "GlobalHandle") == 0)
    {
        *result = a0;
    }
    else if (strcmp(name, "GlobalReAlloc") == 0 || strcmp(name, "LocalReAlloc") == 0)
    {
        /* (block, bytes, flags): the handles are the blocks themselves, which stay in place
         * when they shrink; a larger block is a new one holding the old contents (new blocks
         * are zeroed, as LMEM_ZEROINIT asks). */
        uint32_t size = host_block_size(host, a0);
        *result = 0;
        if (size != 0 && a1 <= size)
        {
            *result = a0;
        }
        else if (size != 0)
        {
            uint32_t block = host_allocate(a1, host);
            uint8_t *to = block != 0 ? bytes_at(host, block, size) : NULL;
            const uint8_t *from = bytes_at(host, a0, size);
            if (to != NULL && from != NULL)
            {
                memcpy(to, from, size);
                host_release(host, a0);
                *result = block;
            }
        }
    }
    else if (strcmp(name, "GetCursorPos") == 0) /* (POINT *): no desktop cursor on the Wii */
    {
        host_write(host, a0, 4, 0);
        host_write(host, a0 + 4, 4, 0);
        *result = 1;
    }
    else if (strcmp(name, "DirectDrawCreateEx") == 0) /* (guid, out, iid, outer) */
    {
        uint32_t device = host_com_object(host, COM_DRAW);
        host_write(host, a1, 4, device);
        *result = device == 0 ? 0x8007000eu : 0;
    }
    else if (strcmp(name, "GetFullPathNameA") == 0) /* (name, size, buffer, file part) */
    {
        uint32_t length = host_string_length(host, a0), i;
        for (i = 0; i <= length && i < a1; i++)
        {
            host_write(host, a2 + i, 1, lift_host_read(host, a0 + i, 1));
        }
        *result = length;
    }
    else if (strcmp(name, "TlsAlloc") == 0)
    {
        *result = host->tls_count < 64 ? host->tls_count++ : 0xffffffffu;
    }
    else if (strcmp(name, "TlsGetValue") == 0)
    {
        *result = a0 < 64 ? host->tls[a0] : 0;
    }
    else if (strcmp(name, "TlsSetValue") == 0)
    {
        if (a0 < 64)
        {
            host->tls[a0] = a1;
        }
        *result = a0 < 64;
    }
    else if (strcmp(name, "TlsFree") == 0)
    {
        *result = 1;
    }
    else if (strcmp(name, "FileTimeToLocalFileTime") == 0)
    {
        host_write(host, a1, 4, lift_host_read(host, a0, 4));
        host_write(host, a1 + 4, 4, lift_host_read(host, a0 + 4, 4));
        *result = 1;
    }
    else if (strcmp(name, "FileTimeToSystemTime") == 0)
    {
        uint32_t i;
        for (i = 0; i < 16; i += 4)
        {
            host_write(host, a1 + i, 4, 0);
        }
        host_write(host, a1, 2, 2004);
        host_write(host, a1 + 2, 2, 1);
        host_write(host, a1 + 6, 2, 1);
        *result = 1;
    }
    else if (strcmp(name, "GetTimeZoneInformation") == 0)
    {
        uint32_t i;
        for (i = 0; i < 172; i += 4)
        {
            host_write(host, a0 + i, 4, 0);
        }
        *result = 0; /* TIME_ZONE_ID_UNKNOWN, UTC */
    }
    else if (strcmp(name, "GetStringTypeA") == 0) /* (locale, type, text, count, out) */
    {
        uint32_t count = site_argument(site, 3), out = site_argument(site, 4), i;
        if (count == 0xffffffffu)
        {
            count = host_string_length(host, a2) + 1;
        }
        for (i = 0; i < count; i++)
        {
            int c = (int)lift_host_read(host, a2 + i, 1);
            uint32_t bits = 0;
            bits |= isupper(c) ? 1 : 0;
            bits |= islower(c) ? 2 : 0;
            bits |= isdigit(c) ? 4 : 0;
            bits |= isspace(c) ? 8 : 0;
            bits |= ispunct(c) ? 0x10 : 0;
            bits |= iscntrl(c) ? 0x20 : 0;
            bits |= (c == ' ' || c == '\t') ? 0x40 : 0;
            bits |= isxdigit(c) ? 0x80 : 0;
            bits |= isalpha(c) ? 0x100 : 0;
            host_write(host, out + 2 * i, 2, bits);
        }
        *result = 1;
    }
    else if (strcmp(name, "LoadLibraryA") == 0)
    {
        *result = 0x70000000u; /* a library handle; GetProcAddress is not served */
    }
    else if (strcmp(name, "FreeLibrary") == 0)
    {
        *result = 1;
    }
    else if (strcmp(name, "CharUpperA") == 0)
    {
        if (a0 < 0x10000u)
        {
            *result = a0 >= 'a' && a0 <= 'z' ? a0 - 32 : a0;
        }
        else
        {
            uint32_t i;
            for (i = 0; lift_host_read(host, a0 + i, 1) != 0; i++)
            {
                uint32_t c = lift_host_read(host, a0 + i, 1);
                host_write(host, a0 + i, 1, c >= 'a' && c <= 'z' ? c - 32 : c);
            }
            *result = a0;
        }
    }
    else if (strcmp(name, "FindFirstFileA") == 0) /* (name, find data) */
    {
        uint32_t index, size, i, length;
        if (!host_find_file(host, a0, &index) || !vertrix_vf_size(host->archive, index, &size))
        {
            *result = 0xffffffffu;
            return 1;
        }
        for (i = 0; i < 320; i += 4)
        {
            host_write(host, a1 + i, 4, 0);
        }
        host_write(host, a1, 4, 0x80);
        host_write(host, a1 + 32, 4, size);
        length = host_string_length(host, a0);
        for (i = 0; i < length && i < 259; i++)
        {
            host_write(host, a1 + 44 + i, 1, lift_host_read(host, a0 + i, 1));
        }
        *result = 0x1001;
    }
    else if (strcmp(name, "FindClose") == 0)
    {
        *result = 1;
    }
    else if (strcmp(name, "CreateFileA") == 0)
    {
        uint32_t index, size;
        unsigned slot;
        *result = 0xffffffffu;
        if (host_find_file(host, a0, &index) && vertrix_vf_size(host->archive, index, &size))
        {
            for (slot = 0; slot < 16; slot++)
            {
                if (!host->files[slot].open)
                {
                    host->files[slot].open = 1;
                    host->files[slot].index = index;
                    host->files[slot].position = 0;
                    host->files[slot].size = size;
                    *result = 0x100 + slot;
                    break;
                }
            }
        }
    }
    else if (strcmp(name, "ReadFile") == 0) /* (handle, buffer, count, read*, overlapped) */
    {
        unsigned slot = a0 - 0x100;
        uint32_t count = a2, available;
        uint8_t *to =
            a0 >= 0x100 && slot < 16 && host->files[slot].open ? bytes_at(host, a1, count) : NULL;
        *result = 0;
        if (to != NULL || count == 0)
        {
            available = host->files[slot].size - host->files[slot].position;
            if (count > available)
            {
                count = available;
            }
            if (count == 0 || vertrix_vf_read(host->archive, host->files[slot].index,
                                              host->files[slot].position, to, count))
            {
                host->files[slot].position += count;
                if (site_argument(site, 3) != 0)
                {
                    host_write(host, site_argument(site, 3), 4, count);
                }
                *result = 1;
            }
        }
    }
    else if (strcmp(name, "SetFilePointer") == 0) /* (handle, distance, high*, method) */
    {
        unsigned slot = a0 - 0x100;
        uint32_t method = site_argument(site, 3);
        *result = 0xffffffffu;
        if (a0 >= 0x100 && slot < 16 && host->files[slot].open)
        {
            uint32_t base = method == 0   ? 0
                            : method == 1 ? host->files[slot].position
                                          : host->files[slot].size;
            host->files[slot].position = base + a1;
            *result = host->files[slot].position;
        }
    }
    else if (strcmp(name, "GetFileSize") == 0)
    {
        unsigned slot = a0 - 0x100;
        *result = a0 >= 0x100 && slot < 16 && host->files[slot].open ? host->files[slot].size
                                                                     : 0xffffffffu;
        if (a1 != 0)
        {
            host_write(host, a1, 4, 0);
        }
    }
    else if (strcmp(name, "CloseHandle") == 0)
    {
        unsigned slot = a0 - 0x100;
        if (a0 >= 0x100 && slot < 16)
        {
            host->files[slot].open = 0;
        }
        *result = 1;
    }
    else if (strcmp(name, "GetVolumeInformationA") == 0) /* (root, name, size, serial, ...) */
    {
        uint32_t serial = site_argument(site, 3), length = site_argument(site, 4),
                 flags = site_argument(site, 5);
        if (a1 != 0)
        {
            host_write(host, a1, 1, 0);
        }
        if (serial != 0)
        {
            host_write(host, serial, 4, 0x1234abcdu);
        }
        if (length != 0)
        {
            host_write(host, length, 4, 255);
        }
        if (flags != 0)
        {
            host_write(host, flags, 4, 0);
        }
        *result = 1;
    }
    else if (strcmp(name, "GetLocalTime") == 0) /* (out SYSTEMTIME): read by localtime 0x4ec850 */
    {
        /* The same fixed date FileTimeToSystemTime reports (1 January 2004), advanced by the
         * driver's clock, so a run is reproducible. */
        uint32_t seconds = host->clock_ms / 1000;
        host_write(host, a0, 2, 2004);                    /* wYear */
        host_write(host, a0 + 2, 2, 1);                   /* wMonth */
        host_write(host, a0 + 4, 2, 4);                   /* wDayOfWeek: a Thursday */
        host_write(host, a0 + 6, 2, 1 + seconds / 86400); /* wDay */
        host_write(host, a0 + 8, 2, seconds / 3600 % 24);
        host_write(host, a0 + 10, 2, seconds / 60 % 60);
        host_write(host, a0 + 12, 2, seconds % 60);
        host_write(host, a0 + 14, 2, host->clock_ms % 1000);
        *result = 0;
    }
    else if (strcmp(name, "GetSystemMetrics") == 0) /* the 640x480 full-screen display mode */
    {
        *result = a0 == 0 ? 640 : a0 == 1 ? 480 : 0; /* SM_CXSCREEN, SM_CYSCREEN */
    }
    else if (strcmp(name, "GetACP") == 0)
    {
        *result = 1252; /* Windows Latin 1 */
    }
    else if (strcmp(name, "GetOEMCP") == 0)
    {
        *result = 850; /* the Western European OEM code page that goes with 1252 */
    }
    else if (strcmp(name, "GetCPInfo") == 0) /* (code page, CPINFO *): a single-byte code page */
    {
        unsigned i;
        host_write(host, a1, 4, 1); /* MaxCharSize */
        host_write(host, a1 + 4, 2, '?');
        for (i = 0; i < 12; i++)
        {
            host_write(host, a1 + 6 + i, 1, 0); /* no lead byte ranges */
        }
        *result = 1;
    }
    else if (strcmp(name, "GetProcessVersion") == 0)
    {
        *result = 0x40000; /* the 4.0 subsystem version of a Windows 95/98 executable */
    }
    else if (strcmp(name, "GetDC") == 0)
    {
        *result = 0x300; /* the screen's device context */
    }
    else if (strcmp(name, "ReleaseDC") == 0)
    {
        *result = 1;
    }
    else if (strcmp(name, "GetDeviceCaps") == 0) /* (dc, index) of the 640x480 32-bit display */
    {
        *result = a1 == 8                ? 640
                  : a1 == 10             ? 480
                  : a1 == 12             ? 32
                  : a1 == 14             ? 1
                  : a1 == 88 || a1 == 90 ? 96
                                         : 0; /* HORZRES, VERTRES, BITSPIXEL, PLANES, LOGPIXELS */
    }
    else if (strcmp(name, "GetSysColor") == 0)
    {
        /* The "Windows Standard" scheme; the window's GDI colours never reach the DirectDraw
         * screen. */
        static const uint32_t colors[] = {0xc0c0c0, 0x808000, 0x800000, 0x808080, 0xc0c0c0,
                                          0xffffff, 0x000000, 0x000000, 0x000000, 0xffffff,
                                          0xc0c0c0, 0xc0c0c0, 0x808080, 0x800000, 0xffffff,
                                          0xc0c0c0, 0x808080, 0x808080, 0x000000, 0xc0c0c0,
                                          0xffffff, 0x000000, 0xdfdfdf, 0x000000, 0xe1ffff};
        *result = a0 < sizeof colors / sizeof colors[0] ? colors[a0] : 0;
    }
    else if (strcmp(name, "CreateSolidBrush") == 0 || strcmp(name, "CreatePen") == 0 ||
             strcmp(name, "LoadCursorA") == 0)
    {
        static uint32_t next = 0x400;
        *result = next++; /* a distinct GDI or cursor handle */
    }
    else if (strcmp(name, "RegisterWindowMessageA") == 0)
    {
        static uint32_t message = 0xc000;
        *result = message++; /* the registered message range starts at 0xc000 */
    }
    else if (strcmp(name, "ShowCursor") == 0) /* the display counter after the change */
    {
        *result = a0 != 0 ? 0 : 0xffffffffu;
    }
    else if (strcmp(name, "ShowWindow") == 0)
    {
        *result = 0; /* the window was not visible before */
    }
    else if (strcmp(name, "CreateEventA") == 0)
    {
        *result = 0x7e000000u + host->events_created++; /* a distinct nonzero handle */
    }
    else if (strcmp(name, "PostMessageA") == 0) /* (window, message, wparam, lparam) */
    {
        /* EXIT posts WM_CLOSE to the form (0x41a010); the driver ends the game on it. */
        if (a1 == 0x10)
        {
            host->close_requested = 1;
        }
        *result = 1;
    }
    else if (strcmp(name, "GetCurrentThreadId") == 0)
    {
        *result = 1; /* the one thread the lifted code runs on */
    }
    else if (strcmp(name, "waveOutGetNumDevs") == 0)
    {
        *result = 1; /* the Wii's audio output */
    }
    else if (strcmp(name, "waveOutGetDevCapsA") == 0) /* (device, WAVEOUTCAPSA *, size) */
    {
        static const char device_name[] = "Wii audio";
        unsigned i;
        for (i = 0; i < a2 && i < 0x34; i++)
        {
            host_write(host, a1 + i, 1, 0);
        }
        for (i = 0; i < sizeof device_name; i++)
        {
            host_write(host, a1 + 8 + i, 1, (uint8_t)device_name[i]); /* szPname */
        }
        host_write(host, a1 + 0x28, 4, 0xfff); /* dwFormats: every 11/22/44 kHz format */
        host_write(host, a1 + 0x2c, 2, 2);     /* wChannels */
        *result = 0;
    }
    else if (strcmp(name, "waveOutOpen") == 0) /* (HWAVEOUT *, device, WAVEFORMATEX *, ...) */
    {
        host->wave_open = 1;
        host->wave_channels = lift_host_read(host, a2 + 2, 2);
        host->wave_rate = lift_host_read(host, a2 + 4, 4);
        host->wave_bytes_per_second = lift_host_read(host, a2 + 8, 4);
        host->wave_bits = lift_host_read(host, a2 + 14, 2);
        host->wave_count = 0;
        host->wave_end_us = (uint64_t)host->clock_ms * 1000u;
        host_write(host, a0, 4, 0x600); /* the device handle */
        *result = 0;
    }
    else if (strcmp(name, "waveOutPrepareHeader") == 0) /* (device, WAVEHDR *, size) */
    {
        host_write(host, a1 + 16, 4, lift_host_read(host, a1 + 16, 4) | 2u); /* WHDR_PREPARED */
        *result = 0;
    }
    else if (strcmp(name, "waveOutUnprepareHeader") == 0)
    {
        uint32_t flags = lift_host_read(host, a1 + 16, 4);
        *result = flags & 0x10u ? 33u : 0u; /* WAVERR_STILLPLAYING while queued */
        if (*result == 0)
        {
            host_write(host, a1 + 16, 4, flags & ~2u);
        }
    }
    else if (strcmp(name, "waveOutWrite") == 0) /* (device, WAVEHDR *, size) */
    {
        uint32_t data = lift_host_read(host, a1, 4), length = lift_host_read(host, a1 + 4, 4);
        uint64_t now = (uint64_t)host->clock_ms * 1000u, start;
        *result = 0;
        if (!host->wave_open || host->wave_bytes_per_second == 0 ||
            host->wave_count == sizeof host->wave_queue / sizeof host->wave_queue[0])
        {
            *result = 11; /* MMSYSERR_INVALPARAM */
        }
        else
        {
            const uint8_t *samples = bytes_at(host, data, length);
            start = host->wave_end_us > now ? host->wave_end_us : now;
            host->wave_end_us = start + (uint64_t)length * 1000000u / host->wave_bytes_per_second;
            if (host->wave_count == 0)
            {
                host->wave_head_end_us = host->wave_end_us;
            }
            host->wave_queue[host->wave_count++] = a1;
            /* WHDR_INQUEUE set, WHDR_DONE cleared */
            host_write(host, a1 + 16, 4, (lift_host_read(host, a1 + 16, 4) & ~1u) | 0x10u);
            if (host->wave_output != NULL && samples != NULL)
            {
                host->wave_output(host->wave_context, samples, length, host->wave_rate,
                                  host->wave_channels, host->wave_bits);
            }
        }
    }
    else if (strcmp(name, "waveOutReset") == 0)
    {
        while (host->wave_count > 0)
        {
            host->wave_head_end_us = (uint64_t)host->clock_ms * 1000u;
            wave_advance(host, 1);
        }
        host->wave_end_us = (uint64_t)host->clock_ms * 1000u;
        *result = 0;
    }
    else if (strcmp(name, "waveOutClose") == 0)
    {
        host->wave_open = 0;
        *result = 0;
    }
    else if (strcmp(name, "GetCurrentThread") == 0)
    {
        *result = 0xfffffffeu; /* the pseudo handle Windows returns */
    }
    else if (strcmp(name, "CreateThread") ==
             0) /* (attributes, stack, start, parameter, flags, id*) */
    {
        uint32_t id = site_argument(site, 5);
        host->thread_start = a2;
        host->thread_parameter = site_argument(site, 3);
        host->thread_due = host->clock_ms;
        if (id != 0)
        {
            host_write(host, id, 4, 2);
        }
        *result = 0x200; /* its handle */
    }
    else if (strcmp(name, "SetPriorityClass") == 0 || strcmp(name, "SetThreadPriority") == 0)
    {
        *result = 1;
    }
    else if (strcmp(name, "VirtualQuery") == 0) /* (address, out MEMORY_BASIC_INFORMATION, size) */
    {
        /* 0x4e6630 asks about its own stack for the thread's stack bounds. The lifted frames
         * descend from 0x7f0000 (lifted_dispatch.c); report the committed region from the page
         * of the address up to that top, allocated from 0x700000. */
        uint32_t page = a0 & ~0xfffu;
        uint32_t top = page < 0x7f0000u ? 0x7f0000u : page + 0x1000;
        host_write(host, a1, 4, page);            /* BaseAddress */
        host_write(host, a1 + 4, 4, 0x700000);    /* AllocationBase */
        host_write(host, a1 + 8, 4, 4);           /* AllocationProtect: PAGE_READWRITE */
        host_write(host, a1 + 12, 4, top - page); /* RegionSize */
        host_write(host, a1 + 16, 4, 0x1000);     /* State: MEM_COMMIT */
        host_write(host, a1 + 20, 4, 4);          /* Protect: PAGE_READWRITE */
        host_write(host, a1 + 24, 4, 0x20000);    /* Type: MEM_PRIVATE */
        *result = 28;
    }
    else if (strcmp(name, "timeBeginPeriod") == 0)
    {
        *result = 0; /* TIMERR_NOERROR */
    }
    else if (strcmp(name, "timeGetDevCaps") == 0) /* (out TIMECAPS, size) */
    {
        host_write(host, a0, 4, 1);           /* wPeriodMin */
        host_write(host, a0 + 4, 4, 1000000); /* wPeriodMax */
        *result = 0;
    }
    else if (strcmp(name, "GetVersion") == 0)
    {
        *result = 0x0a280005u; /* Windows XP style: major 5, minor 1 packs as 0x0a280105 */
    }
    else if (strcmp(name, "GlobalFree") == 0 || strcmp(name, "LocalFree") == 0)
    {
        host_release(host, a0); /* the handle is the GlobalAlloc block itself */
        *result = 0;
    }
    else if (strcmp(name, "GlobalUnlock") == 0 || strcmp(name, "InitializeCriticalSection") == 0 ||
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

/* ---- DirectDraw emulation -------------------------------------------------------------------
 * COM objects are heap blocks { +0 vtable, +4 pixels, +8 width, +12 height, +16 pitch, +20 bytes
 * per pixel }; a vtable entry is the fake address LIFT_COM_BASE + interface * 0x100 + index, which
 * lands on the boundary where host_com serves it. Interfaces: 1 IDirectDraw7, 2 surface. */
static uint32_t host_com_object(LiftHost *host, unsigned interface_id)
{
    uint32_t object = host_allocate(32, host);
    uint32_t table = host_allocate(0x100 * 4, host);
    uint32_t i;
    for (i = 0; object != 0 && table != 0 && i < 0x40; i++)
    {
        host_write(host, table + 4 * i, 4, LIFT_COM_BASE + interface_id * 0x100 + i);
    }
    if (object != 0)
    {
        host_write(host, object, 4, table);
    }
    return object;
}

uint32_t lift_host_surface(const LiftHost *host, uint32_t surface, uint32_t *width,
                           uint32_t *height, uint32_t *pitch, uint32_t *bytes_per_pixel)
{
    if (surface == 0)
    {
        return 0;
    }
    *width = lift_host_read(host, surface + 8, 4);
    *height = lift_host_read(host, surface + 12, 4);
    *pitch = lift_host_read(host, surface + 16, 4);
    *bytes_per_pixel = lift_host_read(host, surface + 20, 4);
    return lift_host_read(host, surface + 4, 4);
}

static uint32_t host_create_surface(LiftHost *host, uint32_t desc, uint32_t out)
{
    uint32_t flags = lift_host_read(host, desc + 4, 4);
    uint32_t height = (flags & 2) ? lift_host_read(host, desc + 8, 4) : host->display_height;
    uint32_t width = (flags & 4) ? lift_host_read(host, desc + 12, 4) : host->display_width;
    uint32_t bits = (flags & 0x1000) ? lift_host_read(host, desc + 84, 4) : host->display_bits;
    uint32_t caps = lift_host_read(host, desc + 104, 4);
    uint32_t surface = host_com_object(host, COM_SURFACE);
    uint32_t pixels;
    if (bits == 0)
    {
        bits = 32;
    }
    if ((caps & 0x200) != 0 && width == 0)
    {
        width = 640;
        height = 480;
    }
    if (width == 0 || height == 0)
    {
        width = 640;
        height = 480;
    }
    pixels = host_allocate(width * height * (bits / 8), host);
    if (surface == 0 || pixels == 0)
    {
        return 0x8007000e; /* E_OUTOFMEMORY */
    }
    host_write(host, surface + 4, 4, pixels);
    host_write(host, surface + 8, 4, width);
    host_write(host, surface + 12, 4, height);
    host_write(host, surface + 16, 4, width * (bits / 8));
    host_write(host, surface + 20, 4, bits / 8);
    if ((caps & 0x200) != 0)
    {
        host->primary_surface = surface;
    }
    host_write(host, out, 4, surface);
    return 0;
}

/* Copy a rectangle between emulated surfaces of the same pixel size; a zero rectangle pointer is
 * the whole surface. Clipped to both. */
static void host_surface_copy(LiftHost *host, uint32_t target, uint32_t tx, uint32_t ty,
                              uint32_t source, uint32_t rect)
{
    uint32_t sw, sh, sp, sb, tw, th, tp, tb;
    uint32_t spixels = lift_host_surface(host, source, &sw, &sh, &sp, &sb);
    uint32_t tpixels = lift_host_surface(host, target, &tw, &th, &tp, &tb);
    int32_t left = 0, top = 0, right = (int32_t)sw, bottom = (int32_t)sh, x, y;
    if (spixels == 0 || tpixels == 0 || sb != tb || sb == 0)
    {
        return;
    }
    if (rect != 0)
    {
        left = (int32_t)lift_host_read(host, rect, 4);
        top = (int32_t)lift_host_read(host, rect + 4, 4);
        right = (int32_t)lift_host_read(host, rect + 8, 4);
        bottom = (int32_t)lift_host_read(host, rect + 12, 4);
    }
    for (y = top; y < bottom; y++)
    {
        int32_t dy = (int32_t)ty + (y - top);
        if (y < 0 || y >= (int32_t)sh || dy < 0 || dy >= (int32_t)th)
        {
            continue;
        }
        {
            /* The columns inside both surfaces: x in [from, to). */
            int32_t from = left, to = right, shift = (int32_t)tx - left;
            uint32_t length, i;
            const uint8_t *in;
            uint8_t *out;
            from = from < 0 ? 0 : from;
            from = from < -shift ? -shift : from;
            to = to > (int32_t)sw ? (int32_t)sw : to;
            to = to > (int32_t)tw - shift ? (int32_t)tw - shift : to;
            if (from >= to)
            {
                continue;
            }
            length = (uint32_t)(to - from) * sb;
            in = bytes_at(host, spixels + y * sp + (uint32_t)from * sb, length);
            out = bytes_at(host, tpixels + dy * tp + (uint32_t)(from + shift) * tb, length);
            if (in != NULL && out != NULL)
            {
                /* Forward, a byte at a time, as before: a copy within one surface overlaps the
                 * same way. */
                for (i = 0; i < length; i++)
                {
                    out[i] = in[i];
                }
                continue;
            }
            for (x = from; x < to; x++)
            {
                int32_t dx = x + shift;
                for (i = 0; i < sb; i++)
                {
                    host_write(host, tpixels + dy * tp + dx * tb + i, 1,
                               lift_host_read(host, spixels + y * sp + x * sb + i, 1));
                }
            }
        }
    }
}

void lift_host_key(LiftHost *host, unsigned scan_code, int down)
{
    unsigned next = (host->key_tail + 1) % 64;
    if (next != host->key_head)
    {
        host->key_queue[host->key_tail][0] = scan_code;
        host->key_queue[host->key_tail][1] = down ? 0x80 : 0;
        host->key_tail = next;
    }
}

void lift_host_mouse(LiftHost *host, unsigned offset, int32_t data)
{
    unsigned next = (host->mouse_tail + 1) % 64;
    if (next != host->mouse_head)
    {
        host->mouse_queue[host->mouse_tail][0] = offset;
        host->mouse_queue[host->mouse_tail][1] = (uint32_t)data;
        host->mouse_tail = next;
    }
}

/* DirectInput: IDirectInput8 (3) creates devices; only the system keyboard (GUID 6F1D2B61) has
 * events, which GetDeviceData hands out as DIDEVICEOBJECTDATA { offset, data, time, sequence,
 * app data }. The mouse and joystick read as idle and EnumDevices finds nothing. */
static uint32_t host_input(LiftHost *host, unsigned interface_id, unsigned index,
                           const VertrixCallSite *site)
{
    uint32_t this_ = site_argument(site, 0);
    if (getenv("TRACE_INPUT"))
        fprintf(stderr, "input %s[%u] kind %u this %x\n",
                interface_id == COM_INPUT ? "IDirectInput" : "Device", index,
                (unsigned)lift_host_read(host, this_ + 24, 4), (unsigned)this_);
    if (interface_id == COM_INPUT)
    {
        if (index == 3) /* CreateDevice(this, guid, out, outer) */
        {
            uint32_t device = host_com_object(host, COM_DEVICE);
            if (getenv("TRACE_INPUT"))
                fprintf(stderr, "CreateDevice guid %x device %x\n",
                        (unsigned)lift_host_read(host, site_argument(site, 1), 4),
                        (unsigned)device);
            if (device == 0)
            {
                return 0x8007000eu;
            }
            {
                uint32_t guid = lift_host_read(host, site_argument(site, 1), 4);
                host_write(host, device + 24, 4,
                           guid == 0x6f1d2b61u   ? 1
                           : guid == 0x6f1d2b60u ? 2
                                                 : 0);
            }
            host_write(host, site_argument(site, 2), 4, device);
        }
        return 0;
    }
    if (index == 10 && lift_host_read(host, this_ + 24, 4) !=
                           0) /* GetDeviceData(this, size, data, count, flags) */
    {
        uint32_t kind = lift_host_read(host, this_ + 24, 4);
        uint32_t size = site_argument(site, 1), data = site_argument(site, 2),
                 count = site_argument(site, 3);
        uint32_t room = lift_host_read(host, count, 4), n = 0;
        unsigned *head = kind == 1 ? &host->key_head : &host->mouse_head;
        unsigned tail = kind == 1 ? host->key_tail : host->mouse_tail;
        uint32_t (*queue)[2] = kind == 1 ? host->key_queue : host->mouse_queue;
        while (n < room && *head != tail && size >= 20)
        {
            uint32_t at = data + n * size;
            host_write(host, at, 4, queue[*head][0]);
            host_write(host, at + 4, 4, queue[*head][1]);
            host_write(host, at + 8, 4, host->clock_ms);
            host_write(host, at + 12, 4, n);
            host_write(host, at + 16, 4, 0);
            *head = (*head + 1) % 64;
            n++;
        }
        if (n != 0 && getenv("TRACE_INPUT"))
            fprintf(stderr, "delivered %u events to kind %u\n", (unsigned)n, (unsigned)kind);
        host_write(host, count, 4, n);
        return 0;
    }
    if (index == 9) /* GetDeviceState(this, size, buffer): nothing pressed */
    {
        uint32_t i, size = site_argument(site, 1), buffer = site_argument(site, 2);
        for (i = 0; i < size; i++)
        {
            host_write(host, buffer + i, 1, 0);
        }
    }
    return 0;
}

static uint32_t host_com(LiftHost *host, unsigned interface_id, unsigned index,
                         const VertrixCallSite *site)
{
    uint32_t this_ = site_argument(site, 0);
    if (interface_id == COM_INPUT || interface_id == COM_DEVICE)
    {
        return host_input(host, interface_id, index, site);
    }
    if (getenv("TRACE_IMPORTS"))
    {
        printf("com %s[%u](%x, %x, %x)\n", interface_id == COM_DRAW ? "DirectDraw" : "Surface",
               index, (unsigned)this_, (unsigned)site_argument(site, 1),
               (unsigned)site_argument(site, 2));
    }
    if (interface_id == COM_DRAW)
    {
        if (index == 6) /* CreateSurface(this, desc, out, outer) */
        {
            return host_create_surface(host, site_argument(site, 1), site_argument(site, 2));
        }
        if (index == 21) /* SetDisplayMode(this, width, height, bits, ...) */
        {
            host->display_width = site_argument(site, 1);
            host->display_height = site_argument(site, 2);
            host->display_bits = site_argument(site, 3);
        }
        return 0; /* QueryInterface, SetCooperativeLevel and the rest report DD_OK */
    }
    if (interface_id == COM_SURFACE)
    {
        uint32_t pixels = lift_host_read(host, this_ + 4, 4);
        if (index == 12) /* GetAttachedSurface(this, caps, out): the back buffer, same size */
        {
            uint32_t back = host_com_object(host, COM_SURFACE);
            uint32_t bytes = lift_host_read(host, this_ + 20, 4);
            uint32_t width = lift_host_read(host, this_ + 8, 4);
            uint32_t height = lift_host_read(host, this_ + 12, 4);
            uint32_t memory = host_allocate(width * height * bytes, host);
            if (back == 0 || memory == 0)
            {
                return 0x8007000e;
            }
            host_write(host, back + 4, 4, memory);
            host_write(host, back + 8, 4, width);
            host_write(host, back + 12, 4, height);
            host_write(host, back + 16, 4, width * bytes);
            host_write(host, back + 20, 4, bytes);
            host_write(host, site_argument(site, 2), 4, back);
            if (this_ == host->primary_surface)
            {
                host->back_surface = back;
            }
            return 0;
        }
        if (index == 5) /* Blt(this, target rect, source, source rect, flags, effects) */
        {
            uint32_t target_rect = site_argument(site, 1);
            if (getenv("TRACE_BLT"))
                fprintf(stderr, "Blt dst %x src %x rect %x\n", (unsigned)this_,
                        (unsigned)site_argument(site, 2), (unsigned)target_rect);
            host_surface_copy(host, this_,
                              target_rect != 0 ? lift_host_read(host, target_rect, 4) : 0,
                              target_rect != 0 ? lift_host_read(host, target_rect + 4, 4) : 0,
                              site_argument(site, 2), site_argument(site, 3));
            return 0;
        }
        if (index == 7) /* BltFast(this, x, y, source, source rect, flags) */
        {
            if (getenv("TRACE_BLT"))
                fprintf(stderr, "BltFast dst %x src %x x %u y %u\n", (unsigned)this_,
                        (unsigned)site_argument(site, 3), (unsigned)site_argument(site, 1),
                        (unsigned)site_argument(site, 2));
            host_surface_copy(host, this_, site_argument(site, 1), site_argument(site, 2),
                              site_argument(site, 3), site_argument(site, 4));
            return 0;
        }
        if (index == 11) /* Flip: the back buffer becomes what the primary shows */
        {
            if (host->primary_surface == this_)
            {
                host_surface_copy(host, this_, 0, 0, host->back_surface, 0);
            }
            host->frames_presented++;
            return 0;
        }
        if (index == 25) /* Lock(this, rect, desc, flags, event) */
        {
            uint32_t desc = site_argument(site, 2);
            host_write(host, desc + 4, 4, 0x100f | 0x1000);
            host_write(host, desc + 8, 4, lift_host_read(host, this_ + 12, 4));
            host_write(host, desc + 12, 4, lift_host_read(host, this_ + 8, 4));
            host_write(host, desc + 16, 4, lift_host_read(host, this_ + 16, 4));
            host_write(host, desc + 36, 4, pixels);
            host_write(host, desc + 84, 4, 8 * lift_host_read(host, this_ + 20, 4));
            /* The DDPIXELFORMAT the original reads to pick its renderer: the channel masks of the
             * host's pixel layout (red in bits 16-23, as the JPEG loader packs it and the Wii
             * display reads it). An 8-bit surface keeps zero masks. */
            host_write(host, desc + 72, 4, 32);
            if (lift_host_read(host, this_ + 20, 4) == 4)
            {
                host_write(host, desc + 76, 4, 0x40); /* DDPF_RGB */
                host_write(host, desc + 88, 4, 0x00ff0000);
                host_write(host, desc + 92, 4, 0x0000ff00);
                host_write(host, desc + 96, 4, 0x000000ff);
                host_write(host, desc + 100, 4, 0);
            }
        }
        return 0; /* Unlock, Blt, GetFlipStatus, Restore, Release... report DD_OK */
    }
    return 0;
}

typedef struct
{
    LiftHost *host;
    int cache_published;
} HostSingleContext;

static void host_single_publish(HostSingleContext *context, const VertrixRtlFloatState *state)
{
    if (!context->cache_published)
    {
        host_write(context->host, 0x503ea0, 4, state->helper);
        host_write(context->host, 0x503ea4, 4, state->multiply);
        host_write(context->host, 0x503ea8, 4, state->divide);
        context->cache_published = 1;
    }
}

static void host_single_refresh(VertrixRtlFloatState *state, LiftHost *host)
{
    state->helper = lift_host_read(host, 0x503ea0, 4);
    state->multiply = lift_host_read(host, 0x503ea4, 4);
    state->divide = lift_host_read(host, 0x503ea8, 4);
    state->hardware = lift_host_read(host, 0x5054a1, 1);
    state->capability = lift_host_read(host, 0x508798, 1);
    state->control = host->rtl_single_control;
}

static void host_single_exception(uint32_t target, VertrixRtlFloatState *state, void *opaque)
{
    HostSingleContext *context = opaque;
    LiftHost *host = context->host;
    /* Publish lazy initialization before the first boundary. Refresh before each call so
     * direct writes by the previous boundary remain live. Explicit state-field changes by
     * the boundary commit to host globals; otherwise its direct host writes are retained. */
    host_single_publish(context, state);
    host_single_refresh(state, host);
    VertrixRtlFloatState before = *state;
    host->rtl_single_exception(target, state, host->rtl_single_exception_context);
    if (state->helper != before.helper)
        host_write(host, 0x503ea0, 4, state->helper);
    if (state->multiply != before.multiply)
        host_write(host, 0x503ea4, 4, state->multiply);
    if (state->divide != before.divide)
        host_write(host, 0x503ea8, 4, state->divide);
    if (state->hardware != before.hardware)
        host_write(host, 0x5054a1, 1, state->hardware);
    if (state->capability != before.capability)
        host_write(host, 0x508798, 1, state->capability);
    if (state->control != before.control)
        host->rtl_single_control = state->control;
    host_single_refresh(state, host);
}

static uint32_t host_rtl_arithmetic(VertrixCallSite *site, LiftHost *host)
{
    VertrixRtlFloatState state = {site->eax,
                                  site->edx,
                                  site->ebx,
                                  site->ecx,
                                  lift_host_read(host, 0x503ea0, 4),
                                  lift_host_read(host, 0x503ea4, 4),
                                  lift_host_read(host, 0x503ea8, 4),
                                  lift_host_read(host, 0x5054a1, 1),
                                  lift_host_read(host, 0x508798, 1),
                                  host->rtl_single_control};
    HostSingleContext context = {host, 0};
    VertrixRtlFloatCall call = host->rtl_single_exception ? host_single_exception : NULL;
    int ok;
    switch (site->target)
    {
        case 0x4db350:
            ok = vertrix_rtl_double_add_full(&state, call, &context);
            break;
        case 0x4db507:
            ok = vertrix_rtl_double_multiply_full(&state, call, &context);
            break;
        case 0x4d809c:
            ok = vertrix_rtl_single_subtract_full(&state, call, &context);
            break;
        case 0x4d80a6:
            ok = vertrix_rtl_single_add_full(&state, call, &context);
            break;
        case 0x4d8177:
            ok = vertrix_rtl_single_multiply_full(&state, call, &context);
            break;
        default:
            ok = vertrix_rtl_single_divide_full(&state, call, &context);
            break;
    }
    if (!ok)
    {
        host->rtl_single_failures++;
        site->out_value = site->edx;
        return site->eax;
    }
    host_single_publish(&context, &state);
    site->edx = state.edx;
    site->ebx = state.ebx;
    site->ecx = state.ecx;
    site->out_value = state.edx;
    return state.eax;
}

/* Original 0x475090: the RGB lookup, hue and auxiliary tables and the pointer tables that index
 * them. The lifted routine scans 101 channel values per colour for 262144 colours, which is too
 * slow on the Wii, so the recovered builder (palette_tables.c, verified against the original)
 * fills the same memory. */
static uint32_t host_palette_build(LiftHost *host)
{
    VertrixPaletteTables tables = {0};
    uint32_t lookup, hue, i;
    if (!vertrix_palette_tables_build(&tables))
    {
        return 0;
    }
    lookup = host_allocate(0x100000, host);
    hue = host_allocate(0x40000, host);
    host_write(host, 0x54b800, 4, lookup);
    host_write(host, 0x54b804, 4, hue);
    for (i = 0; i < 262144; i++)
    {
        host_write(host, lookup + 4 * i, 4, tables.lookup[i]);
        host_write(host, hue + i, 1, tables.hue[i]);
    }
    for (i = 0; i < sizeof tables.channels; i++)
    {
        host_write(host, 0x5468b0 + i, 1, tables.channels[i]);
    }
    for (i = 0; i < 255; i++)
    {
        host_write(host, 0x54c1d4 + 4 * i, 4, tables.auxiliary[i]);
    }
    for (i = 4; i <= 0x3fc; i += 4) /* 0x4753e4: the copy and the constant 100 column */
    {
        host_write(host, 0x54c9c8 + i, 4, 0x64);
        host_write(host, 0x54c5cc + i, 4, (uint32_t)host_read(0x54c1d0 + i, host));
    }
    for (i = 4; i <= 0x320; i += 4)
    {
        host_write(host, 0x54b86c + i, 4, 0x5468b0);
        host_write(host, 0x54beb0 + i, 4, 0x54b798);
    }
    for (i = 0; i < 0x324; i += 4)
    {
        host_write(host, 0x54bb90 + i, 4, 0x5468b0 + 0x65 * (i / 4));
    }
    host_write(host, 0x54d1d0, 4, 0x54c9cc);
    for (i = 0; i < 255; i++)
    {
        host_write(host, 0x54d1d4 + 4 * i, 4, 0x54c1d4 + 4 * i);
    }
    host_write(host, 0x54cdc8, 4, 0x54bb90);
    host_write(host, 0x54cdcc, 4, 0x54d1d0);
    return 0;
}

/* The decoder's destination for an image file: a width by height surface of 4 bytes per pixel
 * (0x478d10), written in place through its pixel memory. */
typedef struct
{
    LiftHost *host;
    uint32_t surface, base, pitch, width, height;
} ImageTarget;

static uint8_t *image_target(void *context, uint32_t width, uint32_t height, uint32_t *pitch)
{
    ImageTarget *image = context;
    LiftHost *host = image->host;
    VertrixCallSite create;
    uint8_t *pixels;
    memset(&create, 0, sizeof create);
    create.target = 0x478d10;
    create.eax = width;
    create.edx = height;
    create.ebx = 4;
    image->surface = host->calls.calls.call(&create, host->calls.calls.context);
    if (image->surface == 0 || width == 0 || height == 0)
    {
        return NULL;
    }
    image->base = lift_host_read(host, image->surface, 4);
    image->pitch = lift_host_read(host, image->surface + 0x14, 4);
    image->width = width;
    image->height = height;
    pixels = bytes_at(host, image->base, image->pitch * (height - 1) + 4 * width);
    *pitch = image->pitch;
    return pixels;
}

static uint32_t host_boundary(VertrixCallSite *site, void *context)
{
    LiftHost *host = context;
    unsigned i;
    /* The stores to globals come first: the lifted code makes most of its boundary calls with
     * them (eax the address, edx the value, the stack dword the width). */
    if (site->target == LIFT_GLOBAL_STORE)
    {
        host_write(host, site->eax, site->stack, site->edx);
        return 0;
    }
    /* The runtime's float helpers next: the MP3 decoder calls them for every sample. */
    if (site->target == 0x4d809c || site->target == 0x4d80a6 || site->target == 0x4d8177 ||
        site->target == 0x4d81fe || site->target == 0x4db350 || site->target == 0x4db507)
    {
        return host_rtl_arithmetic(site, host);
    }
    if (site->target >= LIFT_COM_BASE && site->target < LIFT_COM_BASE + 0x500)
    {
        return host_com(host, (site->target - LIFT_COM_BASE) >> 8,
                        (site->target - LIFT_COM_BASE) & 0xff, site);
    }
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
    if (site->target == 0x475090)
        return host_palette_build(host);
    if (site->target == 0x48ac50 ||
        site->target ==
            0x48ad00) /* load an image file: eax = path, the result is a surface object */
    {
        char text[260];
        unsigned k;
        ImageTarget image = {host, 0, 0, 0, 0, 0};
        for (k = 0;
             k < sizeof text - 1 && (text[k] = (char)lift_host_read(host, site->eax + k, 1)) != 0;
             k++)
        {
        }
        text[k] = 0;
        if (host->decode_jpeg == NULL ||
            !host->decode_jpeg(host->archive, text, image_target, &image))
        {
            if (lift_host_trace_files || getenv("TRACE_FILES"))
            {
                printf("image %s: not decoded\n", text);
            }
            return 0;
        }
        if (lift_host_trace_files)
        {
            printf("image %s: %ux%u surface %x pixels %x first %x\n", text, (unsigned)image.width,
                   (unsigned)image.height, (unsigned)image.surface, (unsigned)image.base,
                   (unsigned)lift_host_read(
                       host, image.base + image.pitch * (image.height / 2) + 4 * (image.width / 2),
                       4));
        }
        if (getenv("TRACE_IMAGES"))
        {
            unsigned long lit = 0;
            uint32_t x, y;
            for (y = 0; y < image.height; y++)
                for (x = 0; x < image.width; x++)
                    lit += (lift_host_read(host, image.base + y * image.pitch + 4 * x, 4) &
                            0xffffffu) != 0;
            fprintf(stderr, "image %s: %ux%u surface %x base %x lit %lu\n", text,
                    (unsigned)image.width, (unsigned)image.height, (unsigned)image.surface,
                    (unsigned)image.base, lit);
        }
        return image.surface;
    }
    if (site->target == 0x48ae00) /* JPEG decode: no bitmap until a native decoder exists */
        return 0;
    if (site->target == 0x4eb652) /* RTL double divide: edx:eax / ecx:ebx */
    {
        union
        {
            uint64_t bits;
            double value;
        } left, right, out;
        left.bits = ((uint64_t)site->edx << 32) | site->eax;
        right.bits = ((uint64_t)site->ecx << 32) | site->ebx;
        out.value = left.value / right.value;
        if ((uint32_t)(out.bits >> 32) == 0x80000000u)
        {
            out.bits = 0;
        }
        site->out_value = (uint32_t)(out.bits >> 32);
        return (uint32_t)out.bits;
    }
    if (site->target == 0x4e04f4 || site->target == 0x4e0f8b || site->target == 0x4cd8b0)
    {
        return site->eax; /* a bare ret; 0x4e0f8b is the exception-state check, 0x4cd8b0 the raise:
                           the original's frames resume at the instruction after the raising call,
                           so no unwinding is needed */
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
    if (site->target == LIFT_HOST_FREEMEM || site->target == LIFT_HOST_FREEMEM_ALIAS ||
        site->target == LIFT_HOST_FREE)
    {
        host_release(host, site->eax);
        return 0;
    }
    if (site->target == LIFT_HOST_FPU_DETECT)
    {
        /* 0x4e536c runs fninit and fnstcw; without a coprocessor the control word stays 0, so it
         * stores 0 in both flags ([0x5054a0], [0x5054a1]) and the runtime's software floating
         * point serves every float operation. */
        host_write(host, 0x5054a0, 1, 0);
        host_write(host, 0x5054a1, 1, 0);
        return site->eax;
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
    if (getenv("TRACE_UNSERVED"))
    {
        printf("unserved %x (eax %x, depth %u)\n", (unsigned)site->target, (unsigned)site->eax,
               vertrix_lifted_depth());
    }
    return 0;
}

void lift_host_set_heap2(LiftHost *host, uint8_t *memory, uint32_t size)
{
    host->heap2 = memory;
    host->heap2_size = size;
    host->heap2_top = 0;
}

void lift_host_write32(LiftHost *host, uint32_t address, uint32_t value)
{
    unsigned i;
    for (i = 0; i < 4; i++)
    {
        uint8_t *byte = bytes_at(host, address + i, 1);
        if (byte != NULL)
        {
            *byte = (uint8_t)(value >> (8 * i));
        }
    }
}

void lift_host_init(LiftHost *host, uint8_t *image, const uint8_t *original, uint8_t *heap,
                    uint32_t heap_size)
{
    memset(host, 0, sizeof *host);
    vertrix_lifted_skip[0] = LIFT_HOST_FREEMEM_ALIAS; /* the host frees heap blocks itself */
    vertrix_lifted_skip[1] = LIFT_HOST_FREEMEM;
    memcpy(image, original, LIFT_HOST_IMAGE_SIZE);
    host->image = image;
    host->heap = heap;
    host->heap_size = heap_size;
    host->rtl_single_control = 0x037f;
    host->inner.call = host_boundary;
    host->inner.context = host;
    host->globals.read = host_read;
    vertrix_lift_store_hook = host_store_hook;
    vertrix_lift_store_context = host;
    host->globals.context = host;
    host->services.resolve = host_resolve;
    host->services.allocate = host_allocate;
    host->services.context = host;
    vertrix_lifted_calls_init(&host->calls, &host->inner, &host->services, &host->globals);
    {
        static const uint32_t image_size = LIFT_HOST_IMAGE_SIZE;
        vertrix_lift_flat[0] =
            (LiftFlatRegion){LIFT_HOST_HEAP2_BASE, &host->heap2_top, &host->heap2, 0};
        vertrix_lift_flat[1] = (LiftFlatRegion){LIFT_HOST_IMAGE_BASE, &image_size, &host->image, 4};
        vertrix_lift_flat[2] =
            (LiftFlatRegion){LIFT_HOST_HEAP_BASE, &host->heap_top, &host->heap, 0};
    }
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

/* 0x40aed0 reads timeGetTime, then calls 0x40ab10 and waits until 10 ms after the previous
 * call, until 0x40af90 sets [0x52f14c]. The host has no second thread: the driver calls this
 * after advancing the clock, and the calls the thread would have made by then happen here. */
void lift_host_thread_step(LiftHost *host, int *lifted)
{
    uint32_t now = host->clock_ms;
    wave_advance(host, 0);
    if (host->thread_start != 0x40aed0)
    {
        return;
    }
    while ((int32_t)(now - host->thread_due) >= 0 && lift_host_read(host, 0x52f14c, 4) == 0)
    {
        /* Each call sees the time the thread would have made it at. */
        host->clock_ms = host->thread_due;
        wave_advance(host, 0);
        lift_host_run(host, 0x40ab10, 0, 0, 0, 0, lifted);
        host->thread_due += 10u;
    }
    host->clock_ms = now;
    wave_advance(host, 0);
}

void lift_host_run_initializers(LiftHost *host, unsigned limit, int *lifted)
{
    for (;;)
    {
        uint32_t at, pick = 0x51c440;
        unsigned best = limit;
        for (at = 0x51c308; at < 0x51c440; at += 6)
        {
            if (lift_host_read(host, at, 1) != 2 && lift_host_read(host, at + 1, 1) <= best)
            {
                pick = at;
                best = lift_host_read(host, at + 1, 1);
            }
        }
        if (pick == 0x51c440)
        {
            return;
        }
        {
            uint32_t routine = lift_host_read(host, pick + 2, 4);
            if (routine != 0)
            {
                /* Through the whole call path: a lifted routine, else the host's boundary. */
                VertrixCallSite site;
                memset(&site, 0, sizeof site);
                site.target = routine;
                *lifted = vertrix_lifted_has(routine);
                if (!*lifted && routine != LIFT_HOST_FPU_DETECT)
                {
                    fprintf(stderr, "initializer %x is not lifted\n", (unsigned)routine);
                }
                host->calls.calls.call(&site, host->calls.calls.context);
            }
        }
        host_write(host, pick, 1, 2);
    }
}

void lift_host_startup(LiftHost *host, int *lifted)
{
    lift_host_run_initializers(host, 1, lifted); /* 0x4ec209 */
    /* 0x4e0508 creates the thread data (0x4e0517: [0x5c7b9c] = 0x4e587c(0)); rand 0x4d85fc
     * and srand 0x4d8620 keep their seed in it, and return 0 without it. */
    lift_host_write32(host, 0x5c7b9c, lift_host_run(host, 0x4e587c, 0, 0, 0, 0, lifted));
    lift_host_run_initializers(host, 0x21, lifted);    /* 0x4e076b */
    lift_host_run(host, 0x4e04f4, 0, 0, 0, 0, lifted); /* 0x4e0775: call [0x507cdc] */
    lift_host_run_initializers(host, 0xff, lifted);    /* 0x4e077b */
}
