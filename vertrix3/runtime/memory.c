#include "runtime.h"
#include "threads.h"

#include <string.h>

/* --- regions ------------------------------------------------------------------------------ */

enum
{
    REGIONS = 64
};

static struct
{
    uint32_t start, end;
} regions[REGIONS];
static unsigned region_count;

void v3_note_region(uint32_t address, uint32_t size)
{
    if (region_count < REGIONS)
    {
        regions[region_count].start = address;
        regions[region_count].end = address + size;
        ++region_count;
    }
}

const void *v3_region_of(uint32_t address)
{
    for (unsigned i = 0; i < region_count; ++i)
    {
        if (address >= regions[i].start && address < regions[i].end)
        {
            return &regions[i];
        }
    }
    return NULL;
}

int v3_contiguous(uint32_t address, uint32_t size)
{
    if (size == 0)
    {
        return 1;
    }
    const void *a = v3_region_of(address);
    return a && address + size - 1 >= address && a == v3_region_of(address + size - 1);
}

/* --- system area -------------------------------------------------------------------------- */

static uint32_t system_top = V3_SYSTEM_BASE;

uint32_t v3_system_alloc(uint32_t size)
{
    v3_lock();
    const uint32_t at = (system_top + 15u) & ~15u;
    if (at + size > V3_SYSTEM_BASE + V3_SYSTEM_SIZE)
    {
        v3_fatal("system area full");
    }
    system_top = at + size;
    v3_unlock();
    memset(MEM(at), 0, size);
    return at;
}

uint32_t v3_system_string(const char *text)
{
    const uint32_t length = (uint32_t)strlen(text);
    const uint32_t at = v3_system_alloc(length + 1);
    memcpy(MEM(at), text, length + 1);
    return at;
}

void v3_read_string(uint32_t address, char *out, size_t size)
{
    size_t i = 0;
    if (address != 0)
    {
        for (; i + 1 < size; ++i)
        {
            const char ch = (char)v3_r8(address + (uint32_t)i);
            if (!ch)
            {
                break;
            }
            out[i] = ch;
        }
    }
    out[i] = 0;
}

void v3_write_string(uint32_t address, const char *text, size_t size)
{
    size_t i = 0;
    for (; text[i] && i + 1 < size; ++i)
    {
        v3_w8(address + (uint32_t)i, (uint8_t)text[i]);
    }
    if (size)
    {
        v3_w8(address + (uint32_t)i, 0);
    }
}

uint32_t v3_string_length(uint32_t address)
{
    uint32_t n = 0;
    while (v3_r8(address + n))
    {
        ++n;
    }
    return n;
}

/* --- heap --------------------------------------------------------------------------------- */

/* Blocks of 16-byte granules. Each has a 16-byte header in guest memory: the previous block's
 * size, this block's size with bit 0 set when in use, and for a free block the links of its bin.
 * Small blocks have exact-size bins; larger ones share power-of-two bins searched first fit. */

enum
{
    HEADER = 16,
    SMALL_BINS = 64, /* sizes up to 1 KB */
    BINS = SMALL_BINS + 32,
    USED = 1u
};

static uint32_t heap_start, heap_end, heap_top, heap_used;
static uint32_t bins[BINS];
static uint32_t last_block; /* the block that ends at heap_top */

#define PREV_SIZE(b) v3_r32((b))
#define SIZE(b) (v3_r32((b) + 4) & ~15u)
#define IN_USE(b) (v3_r32((b) + 4) & USED)
#define NEXT_FREE(b) v3_r32((b) + 8)
#define PREV_FREE(b) v3_r32((b) + 12)

static unsigned bin_of(uint32_t size)
{
    if (size < SMALL_BINS * 16u)
    {
        return size / 16u;
    }
    unsigned bin = SMALL_BINS;
    uint32_t limit = SMALL_BINS * 32u;
    while (size >= limit && bin < BINS - 1)
    {
        limit <<= 1;
        ++bin;
    }
    return bin;
}

static void unlink_free(uint32_t b)
{
    const uint32_t next = NEXT_FREE(b);
    const uint32_t prev = PREV_FREE(b);
    if (prev)
    {
        v3_w32(prev + 8, next);
    }
    else
    {
        bins[bin_of(SIZE(b))] = next;
    }
    if (next)
    {
        v3_w32(next + 12, prev);
    }
}

static void link_free(uint32_t b, uint32_t size)
{
    v3_w32(b + 4, size);
    const unsigned bin = bin_of(size);
    const uint32_t head = bins[bin];
    v3_w32(b + 8, head);
    v3_w32(b + 12, 0);
    if (head)
    {
        v3_w32(head + 12, b);
    }
    bins[bin] = b;
}

void v3_heap_init(uint32_t size)
{
    heap_start = V3_HEAP_BASE;
    v3_map(heap_start, size);
    v3_note_region(heap_start, size);
    heap_end = heap_start + size;
    heap_top = heap_start;
    last_block = 0;
}

uint32_t v3_heap_used(void)
{
    return heap_used;
}

static uint32_t take(uint32_t need)
{
    /* Exact small bin, then any larger bin. */
    for (unsigned bin = bin_of(need); bin < BINS; ++bin)
    {
        for (uint32_t b = bins[bin]; b; b = NEXT_FREE(b))
        {
            const uint32_t size = SIZE(b);
            if (size < need)
            {
                continue;
            }
            unlink_free(b);
            if (size - need >= 64)
            {
                const uint32_t rest = b + need;
                v3_w32(rest, need);
                link_free(rest, size - need);
                const uint32_t after = rest + (size - need);
                if (after < heap_top)
                {
                    v3_w32(after, size - need);
                }
                else
                {
                    last_block = rest;
                }
                v3_w32(b + 4, need | USED);
            }
            else
            {
                v3_w32(b + 4, size | USED);
            }
            return b;
        }
        if (bin < SMALL_BINS && bin + 1 < SMALL_BINS && bins[bin] == 0)
        {
            continue;
        }
    }
    /* Grow at the top. */
    if (heap_top + need > heap_end || heap_top + need < heap_top)
    {
        return 0;
    }
    const uint32_t b = heap_top;
    v3_w32(b, last_block ? SIZE(last_block) : 0);
    v3_w32(b + 4, need | USED);
    heap_top += need;
    last_block = b;
    return b;
}

uint32_t v3_alloc(uint32_t size)
{
    if (size > 0x7fff0000u)
    {
        return 0;
    }
    const uint32_t need = (size + HEADER + 15u) & ~15u;
    v3_lock();
    const uint32_t b = take(need);
    if (b)
    {
        heap_used += SIZE(b);
    }
    v3_unlock();
    if (!b)
    {
        v3_log("heap exhausted asking for %u bytes (%u in use)", size, heap_used);
        return 0;
    }
    memset(MEM(b + HEADER), 0, SIZE(b) - HEADER);
    return b + HEADER;
}

uint32_t v3_alloc_aligned(uint32_t size, uint32_t alignment)
{
    if (alignment <= 16)
    {
        return v3_alloc(size);
    }
    /* Over-allocate, then give the unaligned front back as its own free block. */
    const uint32_t raw = v3_alloc(size + alignment + 64);
    if (!raw)
    {
        return 0;
    }
    uint32_t aligned = (raw + alignment - 1) & ~(alignment - 1);
    if (aligned - raw < 64 && aligned != raw)
    {
        aligned += alignment;
    }
    if (aligned == raw)
    {
        return raw;
    }
    v3_lock();
    const uint32_t b = raw - HEADER;
    const uint32_t total = SIZE(b);
    const uint32_t front = aligned - raw;
    const uint32_t nb = b + front;
    v3_w32(nb, front);
    v3_w32(nb + 4, (total - front) | USED);
    const uint32_t after = b + total;
    if (after < heap_top)
    {
        v3_w32(after, total - front);
    }
    else
    {
        last_block = nb;
    }
    v3_w32(b + 4, front | USED);
    heap_used -= 0;
    v3_unlock();
    v3_free(raw);
    return aligned;
}

uint32_t v3_alloc_size(uint32_t address)
{
    return address ? SIZE(address - HEADER) - HEADER : 0;
}

void v3_free(uint32_t address)
{
    if (!address)
    {
        return;
    }
    if (address < heap_start + HEADER || address >= heap_top)
    {
        v3_log("free of %08x outside the heap ignored", address);
        return;
    }
    v3_lock();
    uint32_t b = address - HEADER;
    if (!IN_USE(b))
    {
        v3_unlock();
        v3_log("double free of %08x ignored", address);
        return;
    }
    uint32_t size = SIZE(b);
    heap_used -= size;
    /* Merge with the following free block. */
    const uint32_t next = b + size;
    if (next < heap_top && !IN_USE(next))
    {
        unlink_free(next);
        if (next == last_block)
        {
            last_block = b;
        }
        size += SIZE(next);
    }
    /* And the preceding one. */
    const uint32_t prev_size = PREV_SIZE(b);
    if (b > heap_start && prev_size && !IN_USE(b - prev_size))
    {
        const uint32_t prev = b - prev_size;
        unlink_free(prev);
        if (b == last_block)
        {
            last_block = prev;
        }
        b = prev;
        size += prev_size;
    }
    if (b + size >= heap_top)
    {
        /* The top block: give it back to the top. */
        heap_top = b;
        last_block = b > heap_start ? b - PREV_SIZE(b) : 0;
        if (b == heap_start)
        {
            last_block = 0;
        }
        v3_unlock();
        return;
    }
    v3_w32(b + size, size);
    link_free(b, size);
    v3_unlock();
}

uint32_t v3_realloc(uint32_t address, uint32_t size)
{
    if (!address)
    {
        return v3_alloc(size);
    }
    const uint32_t old = v3_alloc_size(address);
    if (size <= old && old - size < 4096)
    {
        return address;
    }
    const uint32_t fresh = v3_alloc(size);
    if (!fresh)
    {
        return 0;
    }
    memmove(MEM(fresh), MEM(address), old < size ? old : size);
    v3_free(address);
    return fresh;
}
