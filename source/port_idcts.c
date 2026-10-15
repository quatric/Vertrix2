#include "port_idcts.h"

/* The image decoder's reduced inverse DCTs. */

static uint32_t sar(uint32_t value, unsigned bits)
{
    return (uint32_t)((int32_t)value >> bits);
}

static uint32_t coefficient(Port *port, uint32_t block, uint32_t quant, unsigned row)
{
    return (uint32_t)(int32_t)(int16_t)port_u16(port, block, row * 0x10) *
           port_u32(port, quant, row * 0x20);
}

/* Original 0x4c4b00 (ret 4): the 2x2 reduced inverse DCT of the coefficients ebx (quantized by
 * the component edx's table +0x50) into the two rows of ecx at the column of the stack argument,
 * through the decoder eax's range limit +0x144 (from +0x80). Columns 0, 1, 3, 5 and 7 go through
 * the odd terms (-5906, 6967, -10426, 29692) into a workspace, a column without them as its DC;
 * the rows then likewise. eax ends past the original's workspace, edx at the last row. */
uint32_t vertrix_port_idct_2x2_4c4b00(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0
    };
    static const unsigned columns[5] = {0, 1, 3, 5, 7};
    Port port;
    uint8_t stack[BELOW + 8 + 4];
    uint32_t workspace[16] = {0};
    uint32_t limit;
    uint32_t block = entry->ebx;
    uint32_t quant;
    uint32_t column;
    uint32_t odd;
    uint32_t even;
    uint32_t value;
    uint32_t out = 0;
    uint32_t *ws;
    unsigned i;
    unsigned row;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 1);
    limit = port_u32(&port, entry->eax, 0x144) + 0x80;
    quant = port_u32(&port, entry->edx, 0x50);
    column = port_u32(&port, entry->esp, 4);
    for (i = 0; i < 5; i++)
    {
        uint32_t in = block + columns[i] * 2;
        uint32_t q = quant + columns[i] * 4;
        ws = workspace + columns[i];
        if (port_u16(&port, in, 0x10) == 0 && port_u16(&port, in, 0x30) == 0 &&
            port_u16(&port, in, 0x50) == 0 && port_u16(&port, in, 0x70) == 0)
        {
            value = coefficient(&port, in, q, 0) << 2;
            ws[0] = value;
            ws[8] = value;
            continue;
        }
        even = coefficient(&port, in, q, 0) << 15;
        odd = coefficient(&port, in, q, 7) * 0xffffe8eeu + coefficient(&port, in, q, 5) * 0x1b37 +
              coefficient(&port, in, q, 3) * 0xffffd746u + coefficient(&port, in, q, 1) * 0x73fc;
        ws[0] = sar(even + odd + 0x1000, 13);
        ws[8] = sar(even - odd + 0x1000, 13);
    }
    for (row = 0; row < 2; row++)
    {
        ws = workspace + row * 8;
        out = port_u32(&port, entry->ecx + row * 4, 0) + column;
        if (ws[1] == 0 && ws[3] == 0 && ws[5] == 0 && ws[7] == 0)
        {
            value = port_u8(&port, limit + (sar(ws[0] + 0x10, 5) & 0x3ff), 0);
            port_set8(&port, out, 0, value);
            port_set8(&port, out, 1, value);
            continue;
        }
        odd = ws[7] * 0xffffe8eeu + ws[5] * 0x1b37 + ws[3] * 0xffffd746u + ws[1] * 0x73fc;
        even = ws[0] << 15;
        port_set8(&port, out, 0,
                  port_u8(&port, limit + (sar(even + odd + 0x80000, 20) & 0x3ff), 0));
        port_set8(&port, out, 1,
                  port_u8(&port, limit + (sar(even - odd + 0x80000, 20) & 0x3ff), 0));
    }
    return port_return(&port, entry->esp - 0x1c, out);
}
