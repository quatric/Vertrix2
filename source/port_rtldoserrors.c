#include "port_rtldoserrors.h"

/* The runtime's map from Windows error codes to its errno values (1 invalid function, 2 no such
 * file, 3 no path, 4 too many open files, 5 access denied, 6 bad handle, ...). */

/* Original 0x4d9ae0 (the error code on the stack): a binary search over the codes it knows; any
 * other code maps to 1, and 0 to 0. */
uint32_t vertrix_port_rtl_dos_error_to_errno_4d9ae0(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[8 + 4];
    port_open_arguments(&port, stack, calls, services, globals, entry, 0, 1);
    const uint32_t code = port_u32(&port, entry->esp, 4);
    uint32_t error;
    switch (code)
    {
        case 0x0:
            error = 0;
            break;
        case 0x2:
        case 0x6:
        case 0x12:
        case 0x6b:
            error = 2;
            break;
        case 0x3:
        case 0xf:
        case 0x11:
        case 0x22:
        case 0x34:
        case 0x35:
        case 0x37:
        case 0x43:
        case 0x46:
        case 0x55:
        case 0x6f:
        case 0x7b:
        case 0x7c:
        case 0x7d:
        case 0x90:
        case 0x9a:
        case 0xa1:
        case 0xce:
        case 0xd0:
        case 0x10b:
            error = 3;
            break;
        case 0x4:
        case 0x24:
        case 0x44:
        case 0x71:
            error = 4;
            break;
        case 0x5:
        case 0xc:
        case 0x13:
        case 0x1d:
        case 0x36:
        case 0x3a:
        case 0x40:
        case 0x41:
        case 0x47:
        case 0x50:
        case 0x52:
        case 0x56:
        case 0xaa:
        case 0xb7:
        case 0x3e7:
            error = 5;
            break;
        case 0xb:
        case 0x1a:
        case 0x3c:
        case 0x42:
        case 0x72:
        case 0xb6:
        case 0xbf:
        case 0xc1:
            error = 6;
            break;
        case 0x10:
        case 0x91:
            error = 7;
            break;
        case 0x3e:
            error = 8;
            break;
        case 0x18:
        case 0x19:
        case 0x1b:
        case 0x1e:
        case 0x83:
        case 0x84:
            error = 9;
            break;
        case 0x14:
        case 0x15:
        case 0x16:
        case 0x17:
        case 0x39:
        case 0x3b:
        case 0x58:
        case 0x75:
        case 0x3e3:
        case 0x3e4:
        case 0x3e5:
            error = 10;
            break;
        case 0x20:
            error = 11;
            break;
        case 0x21:
        case 0x6c:
        case 0xa7:
            error = 12;
            break;
        case 0x27:
        case 0x70:
            error = 13;
            break;
        case 0x26:
            error = 14;
            break;
        default:
            error = 1;
            break;
    }
    return port_return(&port, error, 0);
}
