#include "port_rtldevicemessages.h"

enum
{
    /* The object the events go to, and its method table. */
    TARGET = 0x558ccc,
    TARGET_METHODS = 0x1c8,
    /* The stack arguments above the return address: the COM object, the event and its value. */
    ARGUMENT_EVENT = 8,
    ARGUMENT_VALUE = 0xc,
    /* The events handled: 0xffff0000 plus a number (the original switches on event + 0xfffb). */
    EVENTS = 0xffff0000u,
    ON_EVENT_17 = 0x47ed10,
    ON_EVENT_11 = 0x47eeb0
};

/* A method of the target: like the original, it leaves the method table in ebx and the target in
 * ecx. */
static uint32_t method(Port *port, uint32_t target, uint32_t slot, uint32_t value)
{
    const uint32_t methods = port_u32(port, target, TARGET_METHODS);
    return port_call(port, port_u32(port, methods, slot), target, value, methods, target);
}

/* Original 0x47eab0 (stdcall: object, event, value; ret 0xc): the event callback the sound
 * device's COM object is set up with (0x47e7d0). Events 0xffff0000 + 7, 9, 22 and 20 go with
 * their value to the methods +8, +0xc, +0x10 and +0x18 of the object at 0x558ccc, 17 and 11 to
 * 0x47ed10 (which also gets the caller's ebx, as the original keeps it) and 0x47eeb0. Returns what
 * the handler returns, eax and edx; any other event returns 0 and the caller's edx. */
uint32_t vertrix_port_device_message_dispatch_47eab0(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[8 + 4 * 3];
    port_open_arguments(&port, stack, calls, services, globals, entry, 0, 3);
    const uint32_t event = port_u32(&port, entry->esp, ARGUMENT_EVENT);
    const uint32_t value = port_u32(&port, entry->esp, ARGUMENT_VALUE);
    const uint32_t target = port_u32(&port, TARGET, 0);
    uint32_t result;
    switch (event - EVENTS)
    {
        case 7:
            result = method(&port, target, 8, value);
            break;
        case 9:
            result = method(&port, target, 0xc, value);
            break;
        case 22:
            result = method(&port, target, 0x10, value);
            break;
        case 20:
            result = method(&port, target, 0x18, value);
            break;
        case 17:
            result = port_call(&port, ON_EVENT_17, target, value, entry->ebx, target);
            break;
        case 11:
            result = port_call(&port, ON_EVENT_11, target, value, 0, target);
            break;
        default:
            return port_return(&port, 0, entry->edx);
    }
    return port_return(&port, result, vertrix_lift_edx);
}
