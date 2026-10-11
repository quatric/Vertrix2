#include "port_memory.h"

enum
{
    OUT_OF_MEMORY = 0x518870,
    THREAD_HANDLER = 0x28,
    ALLOCATE = 0x4e7c90,
    THREAD_RECORD = 0x4ce780
};

uint32_t vertrix_port_get_memory(PORT_SIGNATURE)
{
    Port port;
    uint32_t size = entry->eax;
    uint32_t handler;
    uint32_t block;
    port_open(&port, calls, services, globals, entry);
    handler = port_u32(&port, 0, OUT_OF_MEMORY);
    for (;;)
    {
        block = port_call(&port, ALLOCATE, size, handler, size, entry->ecx);
        if (block != 0)
        {
            break;
        }
        handler = vertrix_lift_edx;
        if (handler == port_u32(&port, 0, OUT_OF_MEMORY))
        {
            uint32_t thread = port_call(&port, THREAD_RECORD, block, handler, size, entry->ecx);
            handler = port_u32(&port, thread, THREAD_HANDLER);
        }
        if (handler == 0 || port_call(&port, handler, size, handler, size, entry->ecx) == 0)
        {
            break;
        }
        handler = vertrix_lift_edx;
    }
    return port_return(&port, block, entry->edx);
}
