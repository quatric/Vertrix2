#include "rtltypesizes.h"

enum
{
    /* A type record (from 0x4e37fe): its kind byte, its size (+4) and a class's size (+0x10). */
    TYPE_KIND = 0,
    TYPE_SIZE = 4,
    TYPE_CLASS_SIZE = 0x10,
    POINTER_SIZE = 4,

    TYPE_RECORD = 0x4e37fe,
    BAD_KIND = 0x4e0bf8
};

/* Original 0x4e6c98 (eax = a type descriptor): the size of a value of the type. Kinds 0 and 4
 * take the class size (+0x10), 3 and 8 the size (+4), 1, 6 and 7 a pointer's 4; 2, 5 and any past
 * 8 go to 0x4e0bf8 and return the caller's ecx. ecx and edx are kept. */
uint32_t vertrix_port_rtl_type_size_4e6c98(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t type =
        port_call(&port, TYPE_RECORD, entry->eax, entry->edx, entry->ebx, entry->ecx);
    uint32_t size;
    switch (port_u8(&port, type, TYPE_KIND))
    {
        case 0:
        case 4:
            size = port_u32(&port, type, TYPE_CLASS_SIZE);
            break;
        case 3:
        case 8:
            size = port_u32(&port, type, TYPE_SIZE);
            break;
        case 1:
        case 6:
        case 7:
            size = POINTER_SIZE;
            break;
        default:
            port_call(&port, BAD_KIND, type, vertrix_lift_edx, entry->ebx, entry->ecx);
            size = entry->ecx;
            break;
    }
    return port_return(&port, size, entry->edx);
}
