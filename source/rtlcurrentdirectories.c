#include "rtlcurrentdirectories.h"

enum
{
    /* The frame under the return slot: four saved registers, then a MAX_PATH buffer. */
    BELOW = 0x114,
    BUFFER = 0x114,
    PATH_MAX_LENGTH = 0x104,

    ENOMEM_CODE = 5,
    ERANGE_CODE = 0xe,

    GET_CURRENT_DIRECTORY = 0x4f1b90,
    MAP_ERROR = 0x4e0884,
    ALLOCATE = 0x4e7c90,
    SET_ERRNO = 0x4dae70
};

/* The runtime's getcwd (eax = the destination or 0, edx = its size): the current directory
 * (GetCurrentDirectoryA into the frame buffer) copied with its terminator. Without a destination
 * one of the larger of the size and the length plus one is allocated (0x4e7c90). Returns the
 * destination, or 0 when the call fails (0x4e0884 maps the error), the allocation fails (errno 5)
 * or the length exceeds the size (errno 0xe); edx is the last callee's. */
static uint32_t current_directory(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[BELOW + 8];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    uint32_t destination = entry->eax;
    const uint32_t size = entry->edx;
    const uint32_t buffer = entry->esp - BUFFER;
    const uint32_t pushed[2] = {PATH_MAX_LENGTH, buffer};
    const uint32_t length = port_call_stack(&port, GET_CURRENT_DIRECTORY, buffer, size, destination,
                                            entry->ecx, pushed, 2);
    if (length == 0)
    {
        port_call(&port, MAP_ERROR, 0, vertrix_lift_edx, destination, 0);
        return port_return(&port, 0, vertrix_lift_edx);
    }
    if (destination == 0)
    {
        destination = port_call(&port, ALLOCATE, size > length + 1 ? size : length + 1,
                                vertrix_lift_edx, 0, length);
        if (destination == 0)
        {
            port_call(&port, SET_ERRNO, ENOMEM_CODE, vertrix_lift_edx, 0, length);
            return port_return(&port, 0, vertrix_lift_edx);
        }
    }
    else if (length > size)
    {
        port_call(&port, SET_ERRNO, ERANGE_CODE, vertrix_lift_edx, destination, length);
        return port_return(&port, 0, vertrix_lift_edx);
    }
    for (uint32_t i = 0; i <= length && !port.env.failed; i++)
    {
        port_set8(&port, destination + i, 0, port_u8(&port, buffer + i, 0));
    }
    return port_return(&port, destination, vertrix_lift_edx);
}

/* Original 0x4e3ac0: getcwd. */
uint32_t vertrix_port_rtl_getcwd_4e3ac0(PORT_SIGNATURE)
{
    return current_directory(calls, services, globals, entry);
}

/* Original 0x4dabbe: a jump to getcwd (0x4e3ac0). */
uint32_t vertrix_port_rtl_getcwd_jump_4dabbe(PORT_SIGNATURE)
{
    return current_directory(calls, services, globals, entry);
}
