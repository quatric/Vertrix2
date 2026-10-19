#include "rtlheapexpands.h"

enum
{
    BELOW = 0x20,
    /* _expand's local the resize writes the bytes still missing to, under its saved registers. */
    MISSING = 0x10,

    /* The data selector (mov edx, ds): the oracle's flat data segment. */
    DATA_SELECTOR = 0x10,

    /* The heap regions' list, and each region's fields. */
    REGIONS = 0x50aefc,
    REGION_SIZE = 0,
    REGION_NEXT = 8,
    REGION_ROVER = 0xc,
    REGION_FREED = 0x18,
    REGION_FREE_BLOCKS = 0x1c,
    /* A free block: its size word (bit 0 set when in use, -1 at a region's end), its list links. */
    BLOCK_PREVIOUS = 4,
    BLOCK_NEXT = 8,
    END_OF_REGION = 0xffffffffu,
    MINIMUM_BLOCK = 0x10,
    /* Cleared whenever a free block is taken. */
    HEAP_CHECKED = 0x5c8ac1,

    LOCK = 0x507cb8,   /* a procedure variable */
    UNLOCK = 0x507cc0, /* a procedure variable */
    EXPAND_BLOCK = 0x4ec68c,
    FREE = 0x4ea190
};

/* The region holding `pointer` in the default data segment: the first region of the list whose
 * range holds it, else the last one. For another segment the original leaves esi as it was. */
static uint32_t region_of(Port *port, uint32_t segment, uint32_t pointer, uint32_t region)
{
    if ((segment & 0xffff) != DATA_SELECTOR)
    {
        return region;
    }
    region = port_u32(port, REGIONS, 0);
    if (port_u32(port, region, REGION_NEXT) == 0)
    {
        return region;
    }
    for (;;)
    {
        if (region <= pointer && region + port_u32(port, region, REGION_SIZE) > pointer)
        {
            return region;
        }
        region = port_u32(port, region, REGION_NEXT);
        if (port_u32(port, region, REGION_NEXT) == 0 || port->env.failed)
        {
            return region;
        }
    }
}

/* Original 0x4ec68c (eax = the block's segment, edx = the block, ebx = the size wanted, ecx = where
 * to put the bytes still missing, esi = the region for another segment): resize a heap block in
 * place. The size is rounded to 8 with its 4-byte header (0x10 at least; a size that wraps asks
 * for 0xffffffff). Shrinking by 0x10 or more splits off the rest as a block marked in use and
 * frees it (0x4ea190, the region's freed count +0x18 up). Growing takes the free blocks after the
 * block one by one, each unlinked (the region's rover +0xc moved past it, its free count +0x1c
 * down) and absorbed whole, or split when it holds 0x10 more than is missing. Returns 0 when done,
 * 1 when a block in use is in the way and 2 at the region's end (the missing bytes stored). */
uint32_t vertrix_port_rtl_expand_block_4ec68c(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t segment = entry->eax;
    const uint32_t pointer = entry->edx;
    const uint32_t size = entry->ebx;
    const uint32_t missing_at = entry->ecx;
    uint32_t region = entry->esi;
    uint32_t wanted = (size + 0xb) & 0xfffffff8u;
    if (wanted < size)
    {
        wanted = 0xffffffffu;
    }
    else if (wanted < MINIMUM_BLOCK)
    {
        wanted = MINIMUM_BLOCK;
    }
    const uint32_t header = pointer - 4;
    const uint32_t current = port_u32(&port, header, 0) & 0xfffffffeu;
    if (wanted <= current)
    {
        const uint32_t rest = current - wanted;
        if (rest < MINIMUM_BLOCK)
        {
            return port_return(&port, 0, vertrix_lift_edx);
        }
        port_set32(&port, header, 0, wanted | 1);
        const uint32_t split = header + wanted;
        port_set32(&port, split, 0, rest | 1);
        region = region_of(&port, segment, pointer, region);
        port_set32(&port, region, REGION_FREED, port_u32(&port, region, REGION_FREED) + 1);
        port_call(&port, FREE, split + 4, 0, 0, 0);
        return port_return(&port, 0, vertrix_lift_edx);
    }
    uint32_t next = header + current;
    uint32_t missing = wanted - current;
    while (!port.env.failed)
    {
        port_set32(&port, missing_at, 0, missing);
        const uint32_t free_size = port_u32(&port, next, 0);
        if (free_size == END_OF_REGION)
        {
            return port_return(&port, 2, vertrix_lift_edx);
        }
        if (free_size & 1)
        {
            return port_return(&port, 1, vertrix_lift_edx);
        }
        const uint32_t after = port_u32(&port, next, BLOCK_NEXT);
        const uint32_t before = port_u32(&port, next, BLOCK_PREVIOUS);
        region = region_of(&port, segment, pointer, region);
        const uint32_t rover = port_u32(&port, region, REGION_ROVER);
        if (next == rover)
        {
            port_set32(&port, region, REGION_ROVER, port_u32(&port, rover, BLOCK_PREVIOUS));
        }
        missing = port_u32(&port, missing_at, 0);
        if (free_size >= missing && free_size - missing >= MINIMUM_BLOCK)
        {
            /* Split: the rest of the free block takes its place in the list. */
            const uint32_t rest = next + missing;
            port_set32(&port, rest, 0, free_size - missing);
            port_set32(&port, rest, BLOCK_PREVIOUS, before);
            port_set32(&port, rest, BLOCK_NEXT, after);
            port_set32(&port, before, BLOCK_NEXT, rest);
            port_set32(&port, after, BLOCK_PREVIOUS, rest);
            port_set32(&port, header, 0,
                       port_u32(&port, header, 0) + port_u32(&port, missing_at, 0));
            port_set8(&port, HEAP_CHECKED, 0, 0);
            return port_return(&port, 0, vertrix_lift_edx);
        }
        /* Absorb the whole free block. */
        port_set32(&port, before, BLOCK_NEXT, after);
        port_set32(&port, after, BLOCK_PREVIOUS, before);
        port_set32(&port, header, 0, port_u32(&port, header, 0) + free_size);
        port_set32(&port, region, REGION_FREE_BLOCKS,
                   port_u32(&port, region, REGION_FREE_BLOCKS) - 1);
        port_set8(&port, HEAP_CHECKED, 0, 0);
        missing = port_u32(&port, missing_at, 0);
        if (free_size >= missing)
        {
            return port_return(&port, 0, vertrix_lift_edx);
        }
        missing -= free_size;
        next += free_size;
    }
    return port_return(&port, 0, vertrix_lift_edx);
}

/* Original 0x4ec650 (eax = the block, edx = the size wanted): _expand(). Under the heap lock
 * (0x507cb8, 0x507cc0) the block is resized in place (0x4ec68c, in the data segment, the missing
 * bytes into a local). Returns the block, or 0 when it could not be resized. */
uint32_t vertrix_port_rtl_expand_4ec650(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[BELOW + 8];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t block = entry->eax;
    const uint32_t size = entry->edx;
    const uint32_t missing_at = entry->esp - MISSING;
    port_call(&port, port_u32(&port, LOCK, 0), block, size, size, entry->ecx);
    const uint32_t result =
        port_call_with(&port, EXPAND_BLOCK, DATA_SELECTOR, block, size, missing_at, block, 0, 0);
    port_call(&port, port_u32(&port, UNLOCK, 0), result, vertrix_lift_edx, size, missing_at);
    return port_return(&port, result != 0 ? 0 : block, vertrix_lift_edx);
}
