#include "streams.h"

/* Runtime library pieces: a forwarding start, an object reset, a record setup, the double-byte
 * space test, a stream's buffer fill, the console read and the long double class. */

/* Original 0x4e14dc: 0x4e14a3 with 0x50817e and 0. */
uint32_t vertrix_port_crt_start_forward_4e14dc(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_forward(&port, entry, 0x4e14a3, 0x50817e, 0, entry->ebx, entry->ecx);
    return port_return(&port, result, entry->edx);
}

/* Original 0x4e3743: the object's +0x10 is released (0x4e0ec7 with +4) and cleared, then
 * 0x4e36e4 with 1. */
uint32_t vertrix_port_crt_object_reset_4e3743(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x4e0ec7, port_u32(&port, object, 0x10), port_u32(&port, object, 4),
                 entry->ebx, object);
    port_set32(&port, object, 0x10, 0);
    result = port_forward(&port, entry, 0x4e36e4, object, 1, entry->ebx, object);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x4e38ff: the record eax takes edx (+4), ecx (+8), the low bit of bl (+0x25 bit 0),
 * 0x4e6d16 on +0x30, +0x18 0, +0xc the type's (ecx +0 +8), +0x25 bit 1 when edx is 0 and bits 2
 * and 3 clear, +0x2c 0 and +0x34 the type's +0x20; the block the edx left gives is the header
 * 0xe5671234, 0, 0, 0, 2, the first stack argument and the record. That argument. */
uint32_t vertrix_port_crt_record_setup_4e38ff(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x10
    };
    Port port;
    uint8_t stack[BELOW + 8 + 8];
    uint32_t record = entry->eax;
    uint32_t first;
    uint32_t block;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 2);
    port_set32(&port, record, 4, entry->edx);
    port_set32(&port, entry->esp, -0x10u, entry->ebx);
    port_set32(&port, record, 8, entry->ecx);
    port_set8(&port, record, 0x25, (port_u8(&port, record, 0x25) & 0xfe) | (entry->ebx & 1));
    port_call_with(&port, 0x4e6d16, record + 0x30, port_u32(&port, entry->esp, 8), entry->ecx,
                   record, record, entry->edx, entry->ebx);
    block = vertrix_lift_edx;
    port_set32(&port, record, 0x18, 0);
    port_set32(&port, record, 0xc, port_u32(&port, port_u32(&port, entry->ecx, 0), 8));
    if (entry->edx == 0)
    {
        port_set8(&port, record, 0x25, port_u8(&port, record, 0x25) | 2);
    }
    else
    {
        port_set8(&port, record, 0x25, port_u8(&port, record, 0x25) & 0xfd);
    }
    port_set32(&port, record, 0x2c, 0);
    port_set8(&port, record, 0x25, port_u8(&port, record, 0x25) & 0xf3);
    port_set32(&port, record, 0x34, port_u32(&port, port_u32(&port, entry->ecx, 0), 0x20));
    first = port_u32(&port, entry->esp, 4);
    port_set32(&port, block, 0, 0xe5671234);
    port_set32(&port, block, 4, 0);
    port_set32(&port, block, 8, 0);
    port_set32(&port, block, 0xc, 0);
    port_set32(&port, block, 0x10, 2);
    port_set32(&port, block, 0x14, first);
    port_set32(&port, block, 0x18, record);
    return port_return(&port, first, block);
}

/* Original 0x4e7140: whether the character is a space: for a double-byte code page (0x4e9020)
 * the ideographic 0x8140 or 0x20 (as the edx left gives), otherwise bit 1 of the character type
 * 0x507d58 (one past the edx's low byte). */
uint32_t vertrix_port_crt_is_space_4e7140(PORT_SIGNATURE)
{
    Port port;
    uint32_t value;
    port_open(&port, calls, services, globals, entry);
    if (port_forward(&port, entry, 0x4e9020, entry->eax, entry->eax, entry->ebx, entry->ecx) == 0)
    {
        value = port_u8(&port, (vertrix_lift_edx + 1) & 0xff, 0x507d58) & 2;
        return port_return(&port, value, entry->edx);
    }
    value = vertrix_lift_edx == 0x8140 || vertrix_lift_edx == 0x20;
    return port_return(&port, value, entry->edx);
}

/* Original 0x4ec578: the stream's buffer fill: a missing buffer is made (0x4e3b60), a console
 * stream (+0xd bit 5 with bit 1 or 2) flushes 0x2000 (0x4e3f28), the read flag cleared and the
 * pointer reset; a console handle 0 with +0xc 0x2400 reads one character (0x4ecaa0), otherwise
 * 0x4ec3e0 reads one byte (unbuffered) or the buffer size; nothing read sets end of file (0x10),
 * an error 0x20 and the count 0. The count (+4). */
uint32_t vertrix_port_crt_stream_fill_4ec578(PORT_SIGNATURE)
{
    Port port;
    uint32_t stream = entry->eax;
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t flags;
    int32_t count;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, port_u32(&port, stream, 8), 8) == 0)
    {
        port_forward(&port, entry, 0x4e3b60, stream, edx, entry->ebx, stream);
        edx = vertrix_lift_edx;
    }
    flags = port_u8(&port, stream, 0xd);
    if ((flags & 0x20) != 0 && (flags & 6) != 0)
    {
        port_forward(&port, entry, 0x4e3f28, 0x2000, edx, entry->ebx, stream);
        edx = vertrix_lift_edx;
    }
    flags = port_u8(&port, stream, 0xc) & 0xfb;
    edx = (edx & 0xffff00ffu) | (flags << 8);
    port_set8(&port, stream, 0xc, flags);
    port_set32(&port, stream, 0, port_u32(&port, port_u32(&port, stream, 8), 8));
    eax = port_u32(&port, stream, 0xc) & 0x2400;
    if (eax == 0x2400 && port_u32(&port, stream, 0x10) == 0)
    {
        uint32_t letter;
        port_set32(&port, stream, 4, 0);
        letter = port_forward(&port, entry, 0x4ecaa0, eax, edx, 0, stream);
        if (letter != 0xffffffffu)
        {
            port_set8(&port, port_u32(&port, stream, 0), 0, letter);
            port_set32(&port, stream, 4, 1);
            return port_return(&port, 1, entry->edx);
        }
    }
    else
    {
        uint32_t size = (port_u8(&port, stream, 0xd) & 4) != 0 ? 1 : port_u32(&port, stream, 0x14);
        port_set32(&port, stream, 4,
                   port_forward(&port, entry, 0x4ec3e0, port_u32(&port, stream, 0x10),
                                port_u32(&port, stream, 0), size, stream));
    }
    count = (int32_t)port_u32(&port, stream, 4);
    if (count > 0)
    {
        return port_return(&port, (uint32_t)count, entry->edx);
    }
    if (count == 0)
    {
        port_set8(&port, stream, 0xc, port_u8(&port, stream, 0xc) | 0x10);
        return port_return(&port, port_u32(&port, stream, 4), entry->edx);
    }
    port_set32(&port, stream, 4, 0);
    port_set8(&port, stream, 0xc, port_u8(&port, stream, 0xc) | 0x20);
    return port_return(&port, 0, entry->edx);
}

/* Original 0x4ecaa0: the console's next character (0x4ed984), echoed (0x4eda00, then the edx it
 * leaves) unless 0x509718 is set. */
uint32_t vertrix_port_crt_console_read_4ecaa0(PORT_SIGNATURE)
{
    Port port;
    uint32_t echo = 0;
    uint32_t letter;
    port_open(&port, calls, services, globals, entry);
    echo = port_u32(&port, 0, 0x509718);
    letter = port_forward(&port, entry, 0x4ed984, entry->eax, entry->edx, echo, entry->ecx);
    if (letter != 0xffffffffu && echo == 0)
    {
        port_forward(&port, entry, 0x4eda00, letter, letter, 0, entry->ecx);
        letter = vertrix_lift_edx;
    }
    return port_return(&port, letter, entry->edx);
}

/* Original 0x4edf7f: the long double's class: 3 infinity, 2 not a number, 0 zero, 4 denormal,
 * 1 normal. */
uint32_t vertrix_port_crt_long_double_class_4edf7f(PORT_SIGNATURE)
{
    Port port;
    uint32_t value = entry->eax;
    uint32_t exponent;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    exponent = port_u16(&port, value, 8) & 0x7fff;
    if (exponent == 0x7fff)
    {
        result = port_u32(&port, value, 4) == 0x80000000u && port_u32(&port, value, 0) == 0 ? 3 : 2;
    }
    else if (exponent == 0)
    {
        result = port_u32(&port, value, 4) == 0 && port_u32(&port, value, 0) == 0 ? 0 : 4;
    }
    else
    {
        result = 1;
    }
    return port_return(&port, result, entry->edx);
}
