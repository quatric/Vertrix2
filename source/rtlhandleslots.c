#include "rtlhandleslots.h"

enum
{
    /* The runtime's handle table and its length in slots. */
    TABLE = 0x507c8c,
    COUNT = 0x507c90,
    LOCK = 0x507cd0,
    UNLOCK = 0x507cd4,

    /* The standard input, output and error slots, and their STD_*_HANDLE numbers. */
    SLOT_INPUT = 0,
    SLOT_OUTPUT = 1,
    SLOT_ERROR = 2,
    STD_INPUT = 0xfffffff6u,
    STD_OUTPUT = 0xfffffff5u,
    STD_ERROR = 0xfffffff4u,

    SET_STD_HANDLE = 0x4f1cb8,
    REALLOCATE = 0x4ec0e0
};

/* Original 0x4e0328 (eax = a handle, edx = its slot): stores the handle in the runtime's handle
 * table under the lock routines 0x507cd0 and 0x507cd4; a negative slot does nothing. Slots 0, 1
 * and 2 also become the standard input, output and error (SetStdHandle; the slot tested is the edx
 * the lock routine leaves). A slot past the table grows it (0x4ec0e0) to one past the slot, the new
 * slots before it cleared. Returns the unlock routine's eax, or the handle for a negative slot. */
uint32_t vertrix_port_rtl_handle_slot_set_4e0328(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t handle = entry->eax;
    const uint32_t slot = entry->edx;
    if ((int32_t)slot < 0)
    {
        return port_return(&port, handle, entry->edx);
    }
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    port_call(&port, port_u32(&port, LOCK, 0), handle, slot, ebx, ecx);
    uint32_t edx = vertrix_lift_edx;
    uint32_t standard = 0;
    if (edx == SLOT_INPUT)
    {
        ecx = handle;
        standard = STD_INPUT;
    }
    else if (edx == SLOT_OUTPUT)
    {
        ebx = handle;
        standard = STD_OUTPUT;
    }
    else if (edx == SLOT_ERROR)
    {
        edx = handle;
        standard = STD_ERROR;
    }
    if (standard != 0)
    {
        const uint32_t args[2] = {standard, handle};
        port_call_stack(&port, SET_STD_HANDLE, handle, edx, ebx, ecx, args, 2);
        edx = vertrix_lift_edx;
    }
    uint32_t eax;
    const uint32_t count = port_u32(&port, COUNT, 0);
    uint32_t table = port_u32(&port, TABLE, 0);
    if ((int32_t)slot < (int32_t)count)
    {
        ecx = table + slot * 4;
        port_set32(&port, ecx, 0, handle);
        eax = handle;
    }
    else
    {
        ecx = slot * 4;
        table = port_call(&port, REALLOCATE, table, ecx + 4, ebx, ecx);
        for (uint32_t index = port_u32(&port, COUNT, 0);
             (int32_t)index < (int32_t)slot && !port.env.failed; index++)
        {
            ebx = table;
            port_set32(&port, table, index * 4, 0);
        }
        port_set32(&port, TABLE, 0, table);
        port_set32(&port, COUNT, 0, slot + 1);
        eax = table + slot * 4;
        edx = handle;
        port_set32(&port, eax, 0, handle);
    }
    eax = port_call(&port, port_u32(&port, UNLOCK, 0), eax, edx, ebx, ecx);
    return port_return(&port, eax, vertrix_lift_edx);
}
