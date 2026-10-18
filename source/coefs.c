#include "coefs.h"

/* The image decoder's choice of block smoothing, the Huffman slow path and the application marker.
 */

/* Original 0x4b9de0: the decoder eax's coefficient controller +0x1ac picks its output routine:
 * smoothing (0x4ba7b0) when it needs whole rows (+0x10), the image is progressive (+0x50) with
 * the components 0xdc and the bits +0xa0, and every component's (+0xd8, 0x54 bytes each)
 * quantizer +0x4c has its six first entries and known bits (of 0x100 bytes each; their five
 * after the first are kept in the controller's +0x70, made of 24 bytes a component by the
 * memory manager +4's first method) with any set; else the plain one (0x4ba470). Clears +0x9c;
 * the decoder. */
uint32_t vertrix_port_block_smoothing_pick_4b9de0(PORT_SIGNATURE)
{
    static const uint32_t quantizer[] = {0, 2, 0x10, 0x20, 0x12, 4};
    Port port;
    uint32_t decoder = entry->eax;
    uint32_t controller;
    uint32_t saved;
    uint32_t component;
    uint32_t bits;
    uint32_t table;
    uint32_t methods;
    uint32_t index;
    uint32_t value;
    uint32_t smooth = 0;
    int32_t count;
    int32_t number;
    port_open(&port, calls, services, globals, entry);
    controller = port_u32(&port, decoder, 0x1ac);
    if (port_u32(&port, controller, 0x10) == 0)
    {
        port_set32(&port, decoder, 0x9c, 0);
        return port_return(&port, decoder, entry->edx);
    }
    if (port_u32(&port, decoder, 0x50) == 0 || port_u32(&port, decoder, 0xdc) == 0 ||
        port_u32(&port, decoder, 0xa0) == 0)
    {
        port_set32(&port, controller, 0xc, 0x4ba470);
        port_set32(&port, decoder, 0x9c, 0);
        return port_return(&port, decoder, entry->edx);
    }
    if (port_u32(&port, controller, 0x70) == 0)
    {
        count = (int32_t)port_u32(&port, decoder, 0x24);
        methods = port_u32(&port, decoder, 4);
        port_set32(&port, controller, 0x70,
                   port_call_with(&port, port_u32(&port, methods, 0), decoder, 1,
                                  (uint32_t)count * 0x18, methods, 0, controller, entry->esp - 4));
    }
    component = port_u32(&port, decoder, 0xd8);
    saved = port_u32(&port, controller, 0x70);
    for (number = 0; number < (int32_t)port_u32(&port, decoder, 0x24); ++number)
    {
        table = port_u32(&port, component, 0x4c);
        if (table == 0)
        {
            smooth = 0;
            break;
        }
        for (index = 0; index < 6; ++index)
        {
            if (port_u16(&port, table, quantizer[index]) == 0)
            {
                break;
            }
        }
        if (index < 6)
        {
            smooth = 0;
            break;
        }
        bits = port_u32(&port, decoder, 0xa0) + (uint32_t)number * 0x100;
        if ((int32_t)port_u32(&port, bits, 0) < 0)
        {
            smooth = 0;
            break;
        }
        for (index = 1; index < 6; ++index)
        {
            value = port_u32(&port, bits, index * 4);
            port_set32(&port, saved, index * 4, value);
            if (value != 0)
            {
                smooth = 1;
            }
        }
        saved += 0x18;
        component += 0x54;
    }
    port_set32(&port, controller, 0xc, smooth != 0 ? 0x4ba7b0 : 0x4ba470);
    port_set32(&port, decoder, 0x9c, 0);
    return port_return(&port, decoder, entry->edx);
}

/* Original 0x4bc050: the Huffman decoder's slow path (ret 4): from the bit buffer edx holding ebx
 * bits (filled by 0x4bbf30 from the source eax when short), a code of at least the argument's
 * length is read until it is within the table ecx's largest code of its length (+0, a dword a
 * length); the buffer is kept at +8 and +0xc, and the symbol of the table +0x8c (+0x11 past the
 * code and the length's offset +0x48) is the result, edx the offset. A code over 16 bits warns
 * (0x76, the error manager's +4 of -1) and gives 0; a failed fill gives -1. */
uint32_t vertrix_port_huffman_decode_slow_4bc050(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x18
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4];
    uint32_t ebp = entry->esp - 4;
    uint32_t source = entry->eax;
    uint32_t buffer = entry->edx;
    uint32_t bits = entry->ebx;
    uint32_t table = entry->ecx;
    uint32_t length;
    uint32_t code;
    uint32_t largest;
    uint32_t decoder;
    uint32_t methods;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 1);
    length = port_u32(&port, ebp, 8);
    if ((int32_t)bits < (int32_t)length)
    {
        if (port_call_with(&port, 0x4bbf30, source, buffer, bits, length, entry->esi, source,
                           ebp) == 0)
        {
            return port_return(&port, 0xffffffffu, vertrix_lift_edx);
        }
        buffer = port_u32(&port, source, 8);
        bits = port_u32(&port, source, 0xc);
    }
    bits -= length;
    code = ((uint32_t)((int32_t)buffer >> (bits & 31))) & (port_shl(1, length & 31) - 1);
    largest = port_u32(&port, table, length * 4);
    while ((int32_t)code > (int32_t)largest)
    {
        code += code;
        if ((int32_t)bits < 1)
        {
            if (port_call_with(&port, 0x4bbf30, source, buffer, bits, 1, code, source, ebp) == 0)
            {
                return port_return(&port, 0xffffffffu, vertrix_lift_edx);
            }
            buffer = port_u32(&port, source, 8);
            bits = port_u32(&port, source, 0xc);
        }
        --bits;
        code |= ((uint32_t)((int32_t)buffer >> (bits & 31))) & 1;
        ++length;
        largest = port_u32(&port, table, length * 4);
    }
    port_set32(&port, source, 0xc, bits);
    port_set32(&port, source, 8, buffer);
    if ((int32_t)length > 0x10)
    {
        decoder = port_u32(&port, source, 0x10);
        port_set32(&port, port_u32(&port, decoder, 0), 0x14, 0x76);
        methods = port_u32(&port, decoder, 0);
        port_call_with(&port, port_u32(&port, methods, 4), decoder, 0xffffffffu, largest, methods,
                       code, source, ebp);
        return port_return(&port, 0, vertrix_lift_edx);
    }
    buffer = port_u32(&port, table, length * 4 + 0x48);
    return port_return(&port, port_u8(&port, code + buffer + port_u32(&port, table, 0x8c), 0x11),
                       buffer);
}

/* The source manager's refill (+0xc) of the decoder eax: 0 when it fails. */
static uint32_t source_fill(Port *port, uint32_t decoder, uint32_t source, uint32_t edx,
                            uint32_t ebx, uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp)
{
    return port_call_with(port, port_u32(port, source, 0xc), decoder, edx, ebx, ecx, esi, edi, ebp);
}

/* Original 0x4bf270: the application marker of the decoder eax: its length (two bytes of the
 * source +0x18, refilled by +0xc), up to 14 of its bytes read to ebp-0x30, handed to 0x4bef10 for
 * the marker 0xe0 (+0x1a0) or 0x4bf190 for 0xee (any other is the error 0x44 of the error
 * manager), and the rest skipped (+0x10). 1, or 0 when a refill fails. As in the original, the
 * position after a refill of the first two bytes is taken from the refill's edx. */
uint32_t vertrix_port_application_marker_4bf270(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x3c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t decoder = entry->eax;
    uint32_t source;
    uint32_t next;
    uint32_t left;
    uint32_t length;
    uint32_t count;
    uint32_t index;
    uint32_t marker;
    uint32_t error;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x1cu, decoder);
    source = port_u32(&port, decoder, 0x18);
    port_set32(&port, ebp, -0x18u, source);
    left = port_u32(&port, source, 4);
    next = port_u32(&port, source, 0);
    if (left == 0)
    {
        if (source_fill(&port, decoder, source, source, entry->ebx, entry->ecx, next, 0, ebp) == 0)
        {
            return port_return(&port, 0, entry->edx);
        }
        next = port_u32(&port, vertrix_lift_edx, 0);
        left = port_u32(&port, vertrix_lift_edx, 4);
    }
    length = port_u8(&port, next, 0) << 8;
    --left;
    ++next;
    port_set32(&port, ebp, -0x20u, length);
    if (left == 0)
    {
        if (source_fill(&port, decoder, source, source, entry->ebx, entry->ecx, next, 0, ebp) == 0)
        {
            return port_return(&port, 0, entry->edx);
        }
        next = port_u32(&port, vertrix_lift_edx, 0);
        left = port_u32(&port, vertrix_lift_edx, 4);
    }
    length = length + port_u8(&port, next, 0) - 2;
    --left;
    ++next;
    port_set32(&port, ebp, -0x20u, length);
    count = (int32_t)length >= 0xe ? 0xe : ((int32_t)length > 0 ? length : 0);
    index = 0;
    while (index < count)
    {
        if (left == 0)
        {
            if (source_fill(&port, decoder, source, index, count, length, source, 0, ebp) == 0)
            {
                return port_return(&port, 0, entry->edx);
            }
            index = vertrix_lift_edx;
            next = port_u32(&port, source, 0);
            left = port_u32(&port, source, 4);
        }
        --left;
        ++index;
        port_set8(&port, ebp, index - 0x31, port_u8(&port, next, 0));
        ++next;
    }
    length -= count;
    port_set32(&port, ebp, -0x20u, length);
    marker = port_u32(&port, decoder, 0x1a0);
    if (marker == 0xe0)
    {
        port_call_with(&port, 0x4bef10, decoder, ebp - 0x30, count, length, next, left, ebp);
    }
    else if (marker == 0xee)
    {
        port_call_with(&port, 0x4bf190, decoder, ebp - 0x30, count, length, next, left, ebp);
    }
    else
    {
        error = port_u32(&port, decoder, 0);
        port_set32(&port, error, 0x14, 0x44);
        port_set32(&port, error, 0x18, port_u32(&port, decoder, 0x1a0));
        error = port_u32(&port, decoder, 0);
        port_call_with(&port, port_u32(&port, error, 0), decoder, error, count, length + count,
                       next, left, ebp);
    }
    source = port_u32(&port, ebp, -0x18u);
    port_set32(&port, source, 0, next);
    port_set32(&port, source, 4, left);
    length = port_u32(&port, ebp, -0x20u);
    if ((int32_t)length > 0)
    {
        source = port_u32(&port, decoder, 0x18);
        port_call_with(&port, port_u32(&port, source, 0x10), decoder, length, source, length, next,
                       left, ebp);
    }
    return port_return(&port, 1, entry->edx);
}
