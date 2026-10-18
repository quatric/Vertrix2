#include "rtlactortableupdates.h"

enum
{
    /* The owner's table of 450 actors from +0x15c, its list at +0x864 and its last actor at
     * +0x870. */
    TABLE = 0x15c,
    TABLE_SIZE = 0x708,
    LIST = 0x864,
    LIST_MODE = 3,
    LAST = 0x870,
    ACTOR_ACTIVE = 0x44,
    ACTOR_METHODS = 0x158,
    METHOD_UPDATE = 8,

    LIST_UPDATE = 0x4b2380
};

/* Original 0x43e2a0 (eax = the owner, edx = handed on): calls the update method (+8) of every
 * actor in the table whose +0x44 byte is set (with the value in edx and ecx and the slot's address
 * less 0x15c in ebx, as the original leaves them; an empty slot faults as in the original), updates
 * the list +0x864 (0x4b2380 in mode 3) and calls the last actor's (+0x870) update when there is
 * one. eax and edx are the last call's (callers read edx). */
uint32_t vertrix_port_actor_table_update_43e2a0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t owner = entry->eax;
    const uint32_t value = entry->edx;
    uint32_t edi = entry->edi;
    for (uint32_t slot = owner; slot != owner + TABLE_SIZE && !port.env.failed; slot += 4)
    {
        const uint32_t actor = port_u32(&port, slot, TABLE);
        if (port_u8(&port, actor, ACTOR_ACTIVE) != 0)
        {
            edi = port_u32(&port, actor, ACTOR_METHODS);
            port_call_with(&port, port_u32(&port, edi, METHOD_UPDATE), actor, value, slot, value,
                           owner, edi, entry->ebp);
        }
    }
    uint32_t result = port_call(&port, LIST_UPDATE, owner + LIST, LIST_MODE, value, value);
    const uint32_t last = port_u32(&port, owner, LAST);
    if (last != 0)
    {
        const uint32_t methods = port_u32(&port, last, ACTOR_METHODS);
        result = port_call_with(&port, port_u32(&port, methods, METHOD_UPDATE), last, value,
                                methods, value, owner, edi, entry->ebp);
    }
    return port_return(&port, result, vertrix_lift_edx);
}
