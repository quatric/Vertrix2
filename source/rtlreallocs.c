#include "rtlreallocs.h"

enum
{
    MALLOC = 0x4e7c90,
    FREE = 0x4ea190,
    BLOCK_SIZE = 0x4ec640, /* _msize */
    EXPAND = 0x4ec650      /* _expand */
};

/* Original 0x4ec0e0 (eax = the block, edx = the size): realloc(). No block is malloc(size)
 * (0x4e7c90); a size of 0 frees the block (0x4ea190) and gives 0. Otherwise the block is resized in
 * place
 * (_expand, 0x4ec650) when it can be; if not, a new block takes its old size's bytes (_msize,
 * 0x4ec640) and the old one is freed, and when there is no memory for one, the block is put back
 * to its old size (_expand again) and the result is 0. */
uint32_t vertrix_port_rtl_realloc_4ec0e0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t block = entry->eax;
    const uint32_t size = entry->edx;
    if (block == 0)
    {
        return port_return(&port, port_call(&port, MALLOC, size, size, 0, size), vertrix_lift_edx);
    }
    if (size == 0)
    {
        port_call(&port, FREE, block, size, block, size);
        return port_return(&port, 0, vertrix_lift_edx);
    }
    const uint32_t old = port_call(&port, BLOCK_SIZE, block, size, block, size);
    const uint32_t resized = port_call(&port, EXPAND, block, size, block, size);
    if (resized != 0)
    {
        return port_return(&port, resized, vertrix_lift_edx);
    }
    const uint32_t moved = port_call(&port, MALLOC, size, vertrix_lift_edx, block, size);
    if (moved == 0)
    {
        port_call(&port, EXPAND, block, old, block, size);
        return port_return(&port, 0, vertrix_lift_edx);
    }
    port_copy(&port, moved, block, old);
    port_call(&port, FREE, block, vertrix_lift_edx, block, 0);
    return port_return(&port, moved, vertrix_lift_edx);
}
