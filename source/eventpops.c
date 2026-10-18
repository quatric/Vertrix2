#include "eventpops.h"

/* The event stack's pop. */

/* Original 0x482110: the top record (0x34 bytes at 0x34 times the count byte +0x208 of the stack
 * eax) is handed out through each pointer that is set: edx the byte +0, ebx the byte +1, ecx the
 * dword +4, then the eleven stack words the byte +8, the dwords +0xc and +0x10, the byte +0x14,
 * the dwords +0x2c, +0x18 and +0x1c, the words +0x20 and +0x22 and the dwords +0x24 and +0x28,
 * and the count steps down. With no record eax and edx are kept; otherwise eax is the record (or
 * +0x28 when the last pointer is set) and edx the last pointer, as the original leaves them.
 * ret 0x2c. */
uint32_t vertrix_port_event_stack_pop_482110(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0xc
    };
    static const struct
    {
        uint8_t field;
        uint8_t size;
    } outs[11] = {{8, 1},    {0xc, 4},  {0x10, 4}, {0x14, 1}, {0x2c, 4}, {0x18, 4},
                  {0x1c, 4}, {0x20, 2}, {0x22, 2}, {0x24, 4}, {0x28, 4}};
    Port port;
    uint8_t stack[BELOW + 8 + 0x2c];
    uint32_t events = entry->eax;
    uint32_t count;
    uint32_t record;
    uint32_t to;
    uint32_t eax;
    unsigned i;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 11);
    count = port_u8(&port, events, 0x208);
    if ((int32_t)count <= 0)
    {
        return port_return(&port, events, entry->edx);
    }
    record = count * 0x34 + events;
    eax = record;
    if (entry->edx != 0)
    {
        port_set8(&port, entry->edx, 0, port_u8(&port, record, 0));
    }
    if (entry->ebx != 0)
    {
        port_set8(&port, entry->ebx, 0, port_u8(&port, record, 1));
    }
    if (entry->ecx != 0)
    {
        port_set32(&port, entry->ecx, 0, port_u32(&port, record, 4));
    }
    for (i = 0; i < 11; i++)
    {
        to = port_u32(&port, entry->esp, 4 + i * 4);
        if (to == 0)
        {
            continue;
        }
        if (outs[i].size == 1)
        {
            port_set8(&port, to, 0, port_u8(&port, record, outs[i].field));
        }
        else if (outs[i].size == 2)
        {
            port_set16(&port, to, 0, port_u16(&port, record, outs[i].field));
        }
        else
        {
            if (i == 10)
            {
                eax = port_u32(&port, record, outs[i].field);
            }
            port_set32(&port, to, 0, port_u32(&port, record, outs[i].field));
        }
    }
    port_set8(&port, events, 0x208, port_u8(&port, events, 0x208) - 1);
    return port_return(&port, eax, port_u32(&port, entry->esp, 0x2c));
}
