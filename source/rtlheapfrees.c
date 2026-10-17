#include "rtlheapfrees.h"

/* The runtime heap's free: marks a block free, merges it with free neighbours and links it into
 * the address-ordered free list. */

enum
{
    /* A block: its size with bit 0 set while in use; a free block links to its neighbours in the
     * free list. The heap ends with a block of size -1. */
    BLOCK_SIZE = 0,
    BLOCK_PREVIOUS = 4,
    BLOCK_NEXT = 8,
    BLOCK_IN_USE = 1,
    BLOCK_END = 0xffffffffu,
    HEADER = 4,

    /* The heap: the roving free block, the largest free sizes before and after it, the counts of
     * blocks and free blocks, the free list's sentinel and its first block. */
    HEAP_ROVER = 0xc,
    HEAP_LARGEST_BEFORE = 0x10,
    HEAP_LARGEST = 0x14,
    HEAP_BLOCKS = 0x18,
    HEAP_FREE_BLOCKS = 0x1c,
    HEAP_SENTINEL = 0x20,
    HEAP_LAST = 0x24,
    HEAP_FIRST = 0x28
};

static uint32_t size_of(uint32_t header)
{
    return header & ~(uint32_t)BLOCK_IN_USE;
}

/* The free block to link the block before: the rover or its neighbours when they bound it, else
 * a short walk over the following blocks for a free one, else a walk of the free list. */
static uint32_t find_next_free(Port *port, uint32_t heap, uint32_t block)
{
    const uint32_t rover = port_u32(port, heap, HEAP_ROVER);
    if (block < rover)
    {
        if (block > port_u32(port, rover, BLOCK_PREVIOUS))
        {
            return rover;
        }
        const uint32_t first = port_u32(port, heap, HEAP_FIRST);
        if (block < first)
        {
            return first;
        }
    }
    else
    {
        const uint32_t after = port_u32(port, rover, BLOCK_NEXT);
        if (block < after)
        {
            return after;
        }
        if (block > port_u32(port, heap, HEAP_LAST))
        {
            return heap + HEAP_SENTINEL;
        }
    }

    /* Walk the blocks after this one, at most twice the average run of used blocks per free one
     * (unbounded when most blocks are free). */
    const uint32_t free_blocks = port_u32(port, heap, HEAP_FREE_BLOCKS);
    const uint32_t blocks = port_u32(port, heap, HEAP_BLOCKS);
    const uint32_t run = blocks / (free_blocks + 1);
    if (run < free_blocks)
    {
        uint32_t limit = blocks - free_blocks > free_blocks ? run * 2 : 0xffffffffu;
        uint32_t at = block + port_u32(port, block, BLOCK_SIZE);
        while (!port->env.failed)
        {
            const uint32_t header = port_u32(port, at, BLOCK_SIZE);
            if ((header & BLOCK_IN_USE) == 0)
            {
                return at;
            }
            if (header == BLOCK_END)
            {
                break;
            }
            at += size_of(header);
            if (--limit == 0)
            {
                break;
            }
        }
    }

    uint32_t next = port_u32(port, heap, HEAP_ROVER);
    if (block < next)
    {
        next = port_u32(port, heap, HEAP_FIRST);
    }
    while (block >= next && !port->env.failed)
    {
        next = port_u32(port, next, BLOCK_NEXT);
    }
    return next;
}

/* Original 0x4e9a30 (eax = the pointer, ebx = the heap): nothing for a null pointer or a block not
 * in use. Keeps the largest free sizes (+0x10 before the rover, +0x14) up to date. */
uint32_t vertrix_port_rtl_heap_free_block_4e9a30(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t heap = entry->ebx;
    if (entry->eax == 0)
    {
        return port_return(&port, 0, 0);
    }
    uint32_t block = entry->eax - HEADER;
    if ((port_u8(&port, block, BLOCK_SIZE) & BLOCK_IN_USE) == 0)
    {
        return port_return(&port, 0, 0);
    }
    const uint32_t size = size_of(port_u32(&port, block, BLOCK_SIZE));
    const uint32_t following = block + size;
    uint32_t next;
    if ((port_u8(&port, following, BLOCK_SIZE) & BLOCK_IN_USE) == 0)
    {
        /* Merge with the free block after it, taking its place in the list. */
        port_set32(&port, block, BLOCK_SIZE, size + port_u32(&port, following, BLOCK_SIZE));
        if (following == port_u32(&port, heap, HEAP_ROVER))
        {
            port_set32(&port, heap, HEAP_ROVER, block);
        }
        const uint32_t previous = port_u32(&port, following, BLOCK_PREVIOUS);
        next = port_u32(&port, following, BLOCK_NEXT);
        port_set32(&port, previous, BLOCK_NEXT, next);
        port_set32(&port, next, BLOCK_PREVIOUS, previous);
        port_set32(&port, heap, HEAP_FREE_BLOCKS, port_u32(&port, heap, HEAP_FREE_BLOCKS) - 1);
    }
    else
    {
        port_set32(&port, block, BLOCK_SIZE, size);
        next = find_next_free(&port, heap, block);
    }

    const uint32_t previous = port_u32(&port, next, BLOCK_PREVIOUS);
    uint32_t free_size = port_u32(&port, block, BLOCK_SIZE);
    if (previous + port_u32(&port, previous, BLOCK_SIZE) == block)
    {
        /* Merge into the free block before it. */
        free_size += port_u32(&port, previous, BLOCK_SIZE);
        port_set32(&port, previous, BLOCK_SIZE, free_size);
        if (block == port_u32(&port, heap, HEAP_ROVER))
        {
            port_set32(&port, heap, HEAP_ROVER, previous);
        }
        block = previous;
    }
    else
    {
        port_set32(&port, heap, HEAP_FREE_BLOCKS, port_u32(&port, heap, HEAP_FREE_BLOCKS) + 1);
        port_set32(&port, block, BLOCK_NEXT, next);
        port_set32(&port, block, BLOCK_PREVIOUS, previous);
        port_set32(&port, previous, BLOCK_NEXT, block);
        port_set32(&port, next, BLOCK_PREVIOUS, block);
    }
    const uint32_t blocks = port_u32(&port, heap, HEAP_BLOCKS) - 1;
    const uint32_t rover = port_u32(&port, heap, HEAP_ROVER);
    port_set32(&port, heap, HEAP_BLOCKS, blocks);
    if (block < rover && free_size > port_u32(&port, heap, HEAP_LARGEST_BEFORE))
    {
        port_set32(&port, heap, HEAP_LARGEST_BEFORE, free_size);
    }
    if (free_size > port_u32(&port, heap, HEAP_LARGEST))
    {
        port_set32(&port, heap, HEAP_LARGEST, free_size);
    }
    return port_return(&port, 0, 0);
}
