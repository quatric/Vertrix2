#include "rtlthreadslotgets.h"

enum
{
    /* The frame under the return slot: ebx, ecx, then 0x54 bytes of locals whose low end S holds
     * the jump buffer. */
    BELOW = 0x5c,
    JUMP_BUFFER = 0,

    /* The thread slot set (made once by 0x4dbac0 from 0x5c77b0, multi-threaded on Windows NT or a
     * version below 4) and its critical section (+0x20). */
    SLOT_SET = 0x5c77e8,
    SLOT_SET_TEMPLATE = 0x5c77b0,
    SET_SECTION = 0x20,
    VERSION_WIN32S = 0x80000000u,
    VERSION_MAJOR_NT4 = 4,
    LONGJMP_RETURN = 1,

    GET_VERSION = 0x4f1c00,
    ENTER_CRITICAL_SECTION = 0x4f1b48,
    LEAVE_CRITICAL_SECTION = 0x4f1c40,
    SET_MAKE = 0x4dbac0,
    SET_JUMP = 0x4d9f06,
    EXCEPTION_CLEANUP = 0x4da66e,
    SLOT_ALLOCATE = 0x4dbb30,
    SLOT_GET = 0x4dbcd0,
    SLOT_SET_VALUE = 0x4dbd20
};

/* Enter or leave the slot set's critical section; returns the import's eax. */
static uint32_t section(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                        uint32_t ecx)
{
    const uint32_t args[1] = {port_u32(port, SLOT_SET, 0) + SET_SECTION};
    return port_call_stack(port, target, eax, edx, ebx, ecx, args, 1);
}

/* Original 0x4dc030 (eax = a slot index variable, edx = the routine making a value): the calling
 * thread's value in the runtime's thread slot set, made on first use. The set is made once
 * (0x4dbac0, multi-threaded when GetVersion has bit 31 and a major version below 4); a missing slot
 * index is allocated (0x4dbb30). Under the set's section and a jump buffer (0x4d9f06: a jump back
 * leaves the section, runs 0x4da66e and tries again) the slot's value (0x4dbcd0) is returned, or,
 * when it is 0, the maker's value, stored first (0x4dbd20). The exception frame at fs:[0] is left
 * out (docs/NATIVE-PORTS.md). */
uint32_t vertrix_port_rtl_thread_slot_get_4dc030(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[BELOW + 8];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, entry->esp, -4u, entry->ebx);
    port_set32(&port, entry->esp, -8u, entry->ecx);
    const uint32_t index = entry->eax;
    const uint32_t maker = entry->edx;
    const uint32_t buffer = entry->esp - BELOW + JUMP_BUFFER;
    uint32_t edx = entry->edx;
    if (port_u32(&port, SLOT_SET, 0) == 0)
    {
        const uint32_t version =
            port_call_stack(&port, GET_VERSION, index, edx, index, entry->ecx, NULL, 0);
        const uint32_t threaded =
            (version & VERSION_WIN32S) != 0 && (version & 0xff) < VERSION_MAJOR_NT4;
        port_set32(
            &port, SLOT_SET, 0,
            port_forward(&port, entry, SET_MAKE, SLOT_SET_TEMPLATE, threaded, index, entry->ecx));
        edx = vertrix_lift_edx;
    }
    while (port_forward(&port, entry, SET_JUMP, buffer, edx, index, entry->ecx) == LONGJMP_RETURN &&
           !port.env.failed)
    {
        const uint32_t left =
            section(&port, LEAVE_CRITICAL_SECTION, buffer, vertrix_lift_edx, index, entry->ecx);
        port_forward(&port, entry, EXCEPTION_CLEANUP, left, vertrix_lift_edx, index, entry->ecx);
        edx = vertrix_lift_edx;
    }
    section(&port, ENTER_CRITICAL_SECTION, buffer, vertrix_lift_edx, index, entry->ecx);
    if (port_u32(&port, index, 0) == 0)
    {
        port_set32(&port, index, 0,
                   port_call(&port, SLOT_ALLOCATE, port_u32(&port, SLOT_SET, 0), vertrix_lift_edx,
                             index, entry->ecx));
    }
    uint32_t value = port_call(&port, SLOT_GET, port_u32(&port, SLOT_SET, 0),
                               port_u32(&port, index, 0), index, entry->ecx);
    if (value == 0)
    {
        value = port_call(&port, maker, 0, vertrix_lift_edx, index, entry->ecx);
        port_call(&port, SLOT_SET_VALUE, port_u32(&port, SLOT_SET, 0), port_u32(&port, index, 0),
                  value, value);
    }
    section(&port, LEAVE_CRITICAL_SECTION, value, vertrix_lift_edx, index, entry->ecx);
    return port_return(&port, value, vertrix_lift_edx);
}
