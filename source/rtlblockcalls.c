#include "rtlblockcalls.h"

/* A runtime block call used by object construction, teardown and the global initialiser. */

enum
{
    /* The block's header dword sits just below the address the callers hold. */
    HEADER = 4,
    BLOCK_RELEASE = 0x4cea15
};

/* Original 0x4ccb9f (eax = a block, edx = a value for the release): with a null block, returns 0
 * and the caller's edx. Otherwise hands 0x4cea15 the block, its header dword in edx and the
 * caller's edx in ebx, and returns the header's address (the block less 4) with the callee's edx.
 * The code after the return (0x4ccbc4..0x4ccc39) is a separate entry the original reaches by its
 * own address; it is not part of this routine. */
uint32_t vertrix_port_rtl_block_call_4ccb9f(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t block = entry->eax;
    if (block == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    const uint32_t header = block - HEADER;
    const uint32_t size = port_u32(&port, header, 0);
    port_call(&port, BLOCK_RELEASE, block, size, entry->edx, 0);
    return port_return(&port, header, vertrix_lift_edx);
}
