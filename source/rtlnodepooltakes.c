#include "rtlnodepooltakes.h"

enum
{
    /* The pool: the count of nodes taken, the free list, the block chain and the nodes a block
     * holds. A node is 0xc bytes: the next free node (then the key), the value and a string. */
    POOL_TAKEN = 0xc,
    POOL_FREE = 0x10,
    POOL_BLOCKS = 0x14,
    POOL_BLOCK_NODES = 0x18,
    NODE_SIZE = 0xc,
    BLOCK_HEADER = 4,
    NODE_KEY = 0,
    NODE_VALUE = 4,
    NODE_STRING = 8,
    STRING_KIND = 4,

    BLOCK_CHAIN_NEW = 0x4e23e0,
    STRING_EMPTY = 0x4ca060,
    STRING_ASSIGN = 0x4eb5e0
};

/* Original 0x4d8c20 (eax = the pool, edx = the value, ebx = the key): when the free list is empty
 * a block of +0x18 nodes (0x4e23e0, stdcall, chained on +0x14) is threaded onto it, the last node
 * first; the node is taken, gets the key and value, is counted (+0xc), and its string (+8) is set
 * to the empty string (0x4ca060, then 0x4eb5e0 with 4 in ebx). Returns the node; no caller reads
 * edx. */
uint32_t vertrix_port_node_pool_take_initialised_4d8c20(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t pool = entry->eax;
    if (port_u32(&port, pool, POOL_FREE) == 0)
    {
        const uint32_t pushed[3] = {pool + POOL_BLOCKS, port_u32(&port, pool, POOL_BLOCK_NODES),
                                    NODE_SIZE};
        const uint32_t block = port_call_stack(&port, BLOCK_CHAIN_NEW, pool + POOL_BLOCKS,
                                               entry->edx, entry->ebx, entry->ecx, pushed, 3);
        int32_t index = (int32_t)port_u32(&port, pool, POOL_BLOCK_NODES) - 1;
        for (uint32_t node = block + BLOCK_HEADER + (uint32_t)index * NODE_SIZE;
             index >= 0 && !port.env.failed; index--, node -= NODE_SIZE)
        {
            port_set32(&port, node, 0, port_u32(&port, pool, POOL_FREE));
            port_set32(&port, pool, POOL_FREE, node);
        }
    }
    const uint32_t node = port_u32(&port, pool, POOL_FREE);
    port_set32(&port, pool, POOL_FREE, port_u32(&port, node, 0));
    port_set32(&port, node, NODE_VALUE, entry->edx);
    port_set32(&port, node, NODE_KEY, entry->ebx);
    port_set32(&port, pool, POOL_TAKEN, port_u32(&port, pool, POOL_TAKEN) + 1);
    const uint32_t empty = port_call(&port, STRING_EMPTY, 0, 0, 0, 0);
    port_call(&port, STRING_ASSIGN, node + NODE_STRING, empty, STRING_KIND, 0);
    return port_return(&port, node, 0);
}
