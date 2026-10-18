#include "rtlscreenobjectdestroys.h"

enum
{
    /* The flags in dl: bit 2 frees the instance, bit 4 takes the class's own release instead. */
    FLAG_FREE = 0x2,
    FLAG_CLASS_RELEASE = 0x4,

    OBJECT_METHODS = 0x158,
    OBJECT_CHILD = 0x160,
    METHODS = 0x517c64,
    CLASS = 0x517c80,
    CHILD_DESTROY = 0,
    CHILD_FLAGS = 2,
    BASE_FLAGS = 1,

    BASE_DESTROY = 0x4b5420,
    FREE_INSTANCE = 0x4ca050,
    CLASS_RELEASE = 0x4ccb9f,
    CLASS_FINISH = 0x4ca040
};

/* Original 0x4b3140 (eax = the object, dl = flags), a destructor. With bit 4 clear: points the
 * object's method table (+0x158) at 0x517c64, destroys its child (+0x160, when there is one) with
 * its method +0 and flags 2 (the flags in ebx and the object in ecx, as the original leaves them),
 * runs the base destructor 0x4b5420 with flags 1 and frees what it returns (0x4ca050) when bit 2
 * is set. Returns 0x4b5420's result, and in edx the last callee's edx.
 *
 * With bit 4 set: 0x4ccb9f with the object and 0x517c80, then 0x4ca040 with its result; returns the
 * object and 0x4ca040's edx. The original's exception frame is left out (docs/NATIVE-PORTS.md). */
uint32_t vertrix_port_object_destroy_4b3140(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t self = entry->eax;
    const uint32_t flags = entry->edx;

    if ((flags & FLAG_CLASS_RELEASE) != 0)
    {
        const uint32_t released = port_call(&port, CLASS_RELEASE, self, CLASS, 0, 0);
        port_call(&port, CLASS_FINISH, released, 0, 0, 0);
        return port_return(&port, self, vertrix_lift_edx);
    }

    port_set32(&port, self, OBJECT_METHODS, METHODS);
    const uint32_t child = port_u32(&port, self, OBJECT_CHILD);
    if (child != 0)
    {
        const uint32_t methods = port_u32(&port, child, OBJECT_METHODS);
        port_call(&port, port_u32(&port, methods, CHILD_DESTROY), child, CHILD_FLAGS, flags, self);
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
