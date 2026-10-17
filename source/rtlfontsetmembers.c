#include "rtlfontsetmembers.h"

/* The font set member's destructor, called only by vertrix_port_font_set_construct (0x48b711). */

enum
{
    /* The flags in dl: bit 2 frees the instance, bit 4 takes the class's own release instead. */
    FLAG_FREE = 0x2,
    FLAG_CLASS_RELEASE = 0x4,

    VTABLE_FIELD = 0x1c8,
    VTABLE = 0x516a54,
    CLASS = 0x516aa0,
    LOCK_FIRST = 0x558cb4,
    LOCK_SECOND = 0x558c9c,

    /* The three strings released, each address taken from the one before it. */
    FIRST_STRING = 0x40,
    SECOND_STEP = 0x4,
    THIRD_STEP = 0x20,
    THIRD_STRING_TO_SELF = 0x1c,

    DELETE_CRITICAL_SECTION = 0x4f1b3c,
    CO_UNINITIALIZE = 0x4f1768,
    STRING_RELEASE = 0x4ca210,
    FREE_INSTANCE = 0x4ca050,
    CLASS_RELEASE = 0x4ccb9f,
    CLASS_FINISH = 0x4ca040
};

static uint32_t release_string(Port *port, uint32_t field)
{
    return port_call(port, STRING_RELEASE, field, 0, 0, 0);
}

/* Original 0x47e680 (eax = the member, dl = flags). With bit 4 clear: points +0x1c8 at 0x516a54,
 * deletes the critical sections 0x558cb4 and 0x558c9c, calls CoUninitialize, releases the strings
 * at +0x40, +0x3c and +0x1c (each address is the release's result less a step, as the original
 * computes it), and frees the member (0x4ca050) when bit 2 is set. Returns the member, and in edx
 * the last callee's edx with dl replaced by the flags (or 0x4ca050's edx when it ran).
 *
 * With bit 4 set: 0x4ccb9f with the member and 0x516aa0, then 0x4ca040 with its result; returns the
 * member and 0x4ca040's edx. The original's exception frame is left out (docs/NATIVE-PORTS.md). */
uint32_t vertrix_port_font_set_member_construct_47e680(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t self = entry->eax;
    const uint32_t flags = entry->edx & 0xff;

    if ((flags & FLAG_CLASS_RELEASE) != 0)
    {
        const uint32_t released = port_call(&port, CLASS_RELEASE, self, CLASS, 0, 0);
        port_call(&port, CLASS_FINISH, released, 0, 0, 0);
        return port_return(&port, self, vertrix_lift_edx);
    }

    port_set32(&port, self, VTABLE_FIELD, VTABLE);
    const uint32_t first_lock = LOCK_FIRST;
    port_call_stack(&port, DELETE_CRITICAL_SECTION, 0, 0, 0, 0, &first_lock, 1);
    const uint32_t second_lock = LOCK_SECOND;
    port_call_stack(&port, DELETE_CRITICAL_SECTION, 0, 0, 0, 0, &second_lock, 1);
    port_call(&port, CO_UNINITIALIZE, 0, 0, 0, 0);

    uint32_t at = release_string(&port, self + FIRST_STRING);
    at = release_string(&port, at - SECOND_STEP);
    at = release_string(&port, at - THIRD_STEP);
    const uint32_t member = at - THIRD_STRING_TO_SELF;
    uint32_t edx = (vertrix_lift_edx & 0xffffff00u) | flags;
    if ((flags & FLAG_FREE) != 0)
    {
        port_call(&port, FREE_INSTANCE, member, edx, 0, 0);
        edx = vertrix_lift_edx;
    }
    return port_return(&port, member, edx);
}
