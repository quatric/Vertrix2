#include "rtlblocklistdestroys.h"

enum
{
    /* The flags in dl: bit 2 frees the instance, bit 4 takes the class's own release instead. */
    FLAG_FREE = 0x2,
    FLAG_CLASS_RELEASE = 0x4,

    VTABLE_OWN = 0x51a1b4,
    VTABLE_BASE = 0x517454,
    CLASS = 0x516f80,

    BLOCKS_CLEAR = 0x4d8b30,
    FREE_INSTANCE = 0x4ca050,
    CLASS_RELEASE = 0x4ccb9f,
    CLASS_FINISH = 0x4ca040
};

/* Original 0x4d8b80 (eax = the object, dl = flags), a runtime object's destructor. With bit 4
 * clear: points the object at its own vtable (0x51a1b4), clears its blocks (0x4d8b30), points it at
 * the base vtable (0x517454) and frees it (0x4ca050) when bit 2 of the edx 0x4d8b30 hands back is
 * set. Returns the object, and in edx the last callee's edx.
 *
 * With bit 4 set: 0x4ccb9f with the object and 0x516f80, then 0x4ca040 with its result; returns the
 * object and 0x4ca040's edx. The original's exception frame is left out (docs/NATIVE-PORTS.md). */
uint32_t vertrix_port_object_destroy_g_4d8b80(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t self = entry->eax;

    if ((entry->edx & FLAG_CLASS_RELEASE) != 0)
    {
        const uint32_t released = port_call(&port, CLASS_RELEASE, self, CLASS, 0, 0);
        port_call(&port, CLASS_FINISH, released, vertrix_lift_edx, 0, 0);
        return port_return(&port, self, vertrix_lift_edx);
    }

    port_set32(&port, self, 0, VTABLE_OWN);
    port_call(&port, BLOCKS_CLEAR, self, entry->edx, 0, 0);
    uint32_t edx = vertrix_lift_edx;
    port_set32(&port, self, 0, VTABLE_BASE);
    if ((edx & FLAG_FREE) != 0)
    {
        port_call(&port, FREE_INSTANCE, self, edx, 0, 0);
        edx = vertrix_lift_edx;
    }
    return port_return(&port, self, edx);
}
