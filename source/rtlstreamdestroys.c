#include "rtlstreamdestroys.h"

enum
{
    /* The flags in dl: bit 2 frees the instance, bit 4 takes the class's own release instead. */
    FLAG_FREE = 0x2,
    FLAG_CLASS_RELEASE = 0x4,

    VTABLE = 0x519664,
    CLASS = 0x518ed0,
    OBJECT_OPEN = 0x1c,
    OBJECT_CHILD = 0x34,
    OBJECT_OWNER = 0x38,
    OWNER_CURRENT = 0x24,
    CHILD_DESTROY = 4,
    CHILD_FLAGS = 2,
    BASE_FLAGS = 1,

    CLOSE = 0x4d0410,
    BASE_DESTROY = 0x4cb4f0,
    FREE_INSTANCE = 0x4ca050,
    CLASS_RELEASE = 0x4ccb9f,
    CLASS_FINISH = 0x4ca040
};

/* The four static objects that are never closed. */
static const uint32_t statics[4] = {0x5c5c6c, 0x5c5ca8, 0x5c5ce4, 0x5c5d20};

/* Original 0x4d01a0 (eax = the object, dl = flags), a runtime object's destructor. With bit 4
 * clear: points the object at its vtable (0x519664), closes it (0x4d0410) when it is open (+0x1c)
 * and not one of the four static objects 0x5c5c6c..0x5c5d20, destroys its child (+0x34) with the
 * child's method +4 and flags 2 (the flags in ebx and the object in ecx, as the original leaves
 * them), clears its owner's (+0x38) +0x24 when that is the object, runs the base destructor
 * 0x4cb4f0 with flags 1 and frees what it returns (0x4ca050) when bit 2 is set. Returns 0x4cb4f0's
 * result, and in edx the last callee's edx.
 *
 * With bit 4 set: 0x4ccb9f with the object and 0x518ed0, then 0x4ca040 with its result; returns the
 * object and 0x4ca040's edx. The original's exception frame is left out (docs/NATIVE-PORTS.md). */
uint32_t vertrix_port_stream_destroy_4d01a0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t self = entry->eax;
    const uint32_t flags = entry->edx;

    if ((flags & FLAG_CLASS_RELEASE) != 0)
    {
        const uint32_t released = port_call(&port, CLASS_RELEASE, self, CLASS, 0, 0);
        port_call(&port, CLASS_FINISH, released, vertrix_lift_edx, 0, 0);
        return port_return(&port, self, vertrix_lift_edx);
    }

    port_set32(&port, self, 0, VTABLE);
    if (port_u32(&port, self, OBJECT_OPEN) != 0 && self != statics[0] && self != statics[1] &&
        self != statics[2] && self != statics[3])
    {
        port_call(&port, CLOSE, self, flags, flags, self);
    }
    const uint32_t child = port_u32(&port, self, OBJECT_CHILD);
    if (child != 0)
    {
        const uint32_t methods = port_u32(&port, child, 0);
        port_call(&port, port_u32(&port, methods, CHILD_DESTROY), child, CHILD_FLAGS, flags, self);
    }
    const uint32_t owner = port_u32(&port, self, OBJECT_OWNER);
    if (owner != 0 && port_u32(&port, owner, OWNER_CURRENT) == self)
    {
        port_set32(&port, owner, OWNER_CURRENT, 0);
    }
    const uint32_t result = port_call(&port, BASE_DESTROY, self, BASE_FLAGS, flags, self);
    uint32_t edx = vertrix_lift_edx;
    if ((flags & FLAG_FREE) != 0)
    {
        port_call(&port, FREE_INSTANCE, result, edx, 0, 0);
        edx = vertrix_lift_edx;
    }
    return port_return(&port, result, edx);
}
