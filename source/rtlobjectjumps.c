#include "rtlobjectjumps.h"

enum
{
    /* The frame under the return slot: the buffer the object's method fills. */
    BELOW = 0xd8,
    BUFFER = 0xd4,
    OBJECT_METHODS = 0,
    METHOD_FILL = 0xc,
    OBJECT_JUMP = 0x84,
    LONG_JUMP = 0x4d9f45
};

/* Original 0x48ac10 (eax = an owner whose first dword is an object): the object's method +0xc
 * fills a 0xc8-byte buffer in the frame (edx; ebx holds the object, as the original leaves it),
 * then longjmp (0x4d9f45) to the object's jump buffer (+0x84) with value 1. Returns what that call
 * returns and keeps edx. */
uint32_t vertrix_port_object_jump_48ac10(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[BELOW + 8];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t object = port_u32(&port, entry->eax, OBJECT_METHODS);
    port_call(&port, port_u32(&port, object, METHOD_FILL), entry->eax, entry->esp - 4 - BUFFER,
              object, object);
    const uint32_t result = port_call(&port, LONG_JUMP, object + OBJECT_JUMP, 1, 0, 0);
    return port_return(&port, result, entry->edx);
}
