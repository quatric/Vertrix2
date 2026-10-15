#include "port_colorconverts.h"

/* The image decoder's colour conversions. */

/* Original 0x4bb510 (ret 4): YCCK to CMYK for the decoder eax: the stack argument counts the rows
 * down (kept in its slot), from row ebx of the four planes edx into the rows ecx. Each of the +0x70
 * columns inverts through the range limit +0x144 the red (converter +0x1c8's Cr table +8), green
 * (the Cb +0x14 and Cr +0x10 terms, high half) and blue (Cb +0xc) of its Y and copies K. eax is
 * the last output place (the row offset when no row runs), edx the count left. */
uint32_t vertrix_port_ycck_cmyk_convert_4bb510(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4];
    uint32_t decoder = entry->eax;
    uint32_t planes = entry->edx;
    uint32_t rows = entry->ecx;
    uint32_t columns;
    uint32_t limit;
    uint32_t converter;
    uint32_t red;
    uint32_t blue;
    uint32_t green_red;
    uint32_t green_blue;
    uint32_t offset;
    uint32_t count;
    uint32_t eax;
    uint32_t y_in;
    uint32_t cb_in;
    uint32_t cr_in;
    uint32_t k_in;
    uint32_t end;
    uint32_t y;
    uint32_t cb;
    uint32_t cr;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 1);
    columns = port_u32(&port, decoder, 0x70);
    limit = port_u32(&port, decoder, 0x144);
    converter = port_u32(&port, decoder, 0x1c8);
    red = port_u32(&port, converter, 8);
    blue = port_u32(&port, converter, 0xc);
    green_red = port_u32(&port, converter, 0x10);
    green_blue = port_u32(&port, converter, 0x14);
    offset = entry->ebx * 4;
    eax = offset;
    for (;;)
    {
        count = port_u32(&port, entry->esp, 4) - 1;
        port_set32(&port, entry->esp, 4, count);
        if ((int32_t)count < 0 || port.env.failed)
        {
            break;
        }
        y_in = port_u32(&port, port_u32(&port, planes, 0) + offset, 0);
        cb_in = port_u32(&port, port_u32(&port, planes, 4) + offset, 0);
        cr_in = port_u32(&port, port_u32(&port, planes, 8) + offset, 0);
        k_in = port_u32(&port, port_u32(&port, planes, 0xc) + offset, 0);
        eax = port_u32(&port, rows, 0);
        offset += 4;
        rows += 4;
        if (columns == 0)
        {
            continue;
        }
        end = y_in + columns;
        do
        {
            cb = port_u8(&port, cb_in, 0);
            cr = port_u8(&port, cr_in, 0);
            y = port_u8(&port, y_in, 0);
            port_set8(&port, eax, 0,
                      port_u8(&port, limit + 0xff - (port_u32(&port, red + cr * 4, 0) + y), 0));
            port_set8(&port, eax, 1,
                      port_u8(&port,
                              limit + 0xff -
                                  ((uint32_t)((int32_t)(port_u32(&port, green_blue + cb * 4, 0) +
                                                        port_u32(&port, green_red + cr * 4, 0)) >>
                                              16) +
                                   y),
                              0));
            port_set8(&port, eax, 2,
                      port_u8(&port, limit + 0xff - (port_u32(&port, blue + cb * 4, 0) + y), 0));
            port_set8(&port, eax, 3, port_u8(&port, k_in, 0));
            eax += 4;
            y_in++;
            cb_in++;
            cr_in++;
            k_in++;
        } while (y_in < end && !port.env.failed);
    }
    return port_return(&port, eax, count);
}

/* The decoder's error `code` (+0x14 of the error manager [cinfo]) raised by its method +0; the
 * call's eax. */
static uint32_t raise_error(Port *port, const LiftEntry *entry, uint32_t cinfo, uint32_t code,
                            uint32_t ebx, uint32_t esi, uint32_t edi)
{
    uint32_t error = port_u32(port, cinfo, 0);
    port_set32(port, error, 0x14, code);
    error = port_u32(port, cinfo, 0);
    return port_call_with(port, port_u32(port, error, 0), cinfo, error, ebx, cinfo, esi, edi,
                          entry->ebp);
}

/* Original 0x4bb6c0: the colour deconverter of the decoder eax: 0x18 bytes from the memory
 * manager +4's first method go to +0x1c8 with the start 0x4bb260. The component count +0x24 must
 * suit the colour space +0x28 (1 for grey, 3 for YCbCr and RGB, 4 for CMYK and YCCK, at least 1
 * otherwise; error 0xa). The output space +0x2c picks the conversion +4 and its component count
 * +0x78: grey from grey or YCbCr (0x4bb470, the other components not needed, +0x30 of each 0x54
 * bytes at +0xd8), RGB from YCbCr (0x4bb270 with the tables of 0x4bb170), grey (0x4bb4a0) or RGB
 * (0x4bb3d0), CMYK from YCCK (0x4bb510 with the tables) or CMYK (0x4bb3d0), any space from itself
 * (0x4bb3d0, all components); others error 0x1b. +0x7c is 1 when quantizing (+0x54), else +0x78
 * (then also eax). edx kept. */
uint32_t vertrix_port_color_deconverter_init_4bb6c0(PORT_SIGNATURE)
{
    Port port;
    uint32_t cinfo = entry->eax;
    uint32_t mem;
    uint32_t converter;
    uint32_t eax;
    uint32_t ebx = 0x18;
    uint32_t esi;
    uint32_t edi = entry->edi;
    uint32_t space;
    uint32_t count;
    uint32_t i;
    port_open(&port, calls, services, globals, entry);
    mem = port_u32(&port, cinfo, 4);
    esi = mem;
    converter =
        port_call_with(&port, port_u32(&port, mem, 0), cinfo, 1, ebx, cinfo, esi, edi, entry->ebp);
    port_set32(&port, cinfo, 0x1c8, converter);
    port_set32(&port, converter, 0, 0x4bb260);
    space = port_u32(&port, cinfo, 0x28);
    count = port_u32(&port, cinfo, 0x24);
    if (space == 1                 ? count != 1
        : space == 2 || space == 3 ? count != 3
        : space == 4 || space == 5 ? count != 4
                                   : (int32_t)count < 1)
    {
        ebx = port_u32(&port, cinfo, 0);
        port_set32(&port, ebx, 0x14, 0xa);
        ebx = port_u32(&port, cinfo, 0);
        port_call_with(&port, port_u32(&port, ebx, 0), cinfo, converter, ebx, cinfo, esi, edi,
                       entry->ebp);
    }
    eax = port_u32(&port, cinfo, 0x2c);
    if (eax == 1)
    {
        edi = port_u32(&port, cinfo, 0x28);
        port_set32(&port, cinfo, 0x78, eax);
        if (edi == 1 || edi == 3)
        {
            port_set32(&port, converter, 4, 0x4bb470);
            if (1 < (int32_t)port_u32(&port, cinfo, 0x24))
            {
                eax = 0x54;
                i = 1;
                do
                {
                    ebx = port_u32(&port, cinfo, 0xd8);
                    port_set32(&port, ebx + eax, 0x30, 0);
                    i++;
                    esi = port_u32(&port, cinfo, 0x24);
                    eax += 0x54;
                } while ((int32_t)i < (int32_t)esi && !port.env.failed);
            }
        }
        else
        {
            eax = raise_error(&port, entry, cinfo, 0x1b, ebx, esi, edi);
        }
    }
    else if (eax == 2)
    {
        edi = port_u32(&port, cinfo, 0x28);
        port_set32(&port, cinfo, 0x78, 3);
        if (edi == 3)
        {
            port_set32(&port, converter, 4, 0x4bb270);
            eax =
                port_call_with(&port, 0x4bb170, cinfo, converter, ebx, cinfo, esi, edi, entry->ebp);
        }
        else if (edi == 1)
        {
            port_set32(&port, converter, 4, 0x4bb4a0);
        }
        else if (edi == 2)
        {
            port_set32(&port, converter, 4, 0x4bb3d0);
        }
        else
        {
            eax = raise_error(&port, entry, cinfo, 0x1b, ebx, esi, edi);
        }
    }
    else if (eax == 4)
    {
        ebx = port_u32(&port, cinfo, 0x28);
        port_set32(&port, cinfo, 0x78, eax);
        if (ebx == 5)
        {
            port_set32(&port, converter, 4, 0x4bb510);
            eax =
                port_call_with(&port, 0x4bb170, cinfo, converter, ebx, cinfo, esi, edi, entry->ebp);
        }
        else if (ebx == eax)
        {
            port_set32(&port, converter, 4, 0x4bb3d0);
        }
        else
        {
            eax = raise_error(&port, entry, cinfo, 0x1b, ebx, esi, edi);
        }
    }
    else if (port_u32(&port, cinfo, 0x2c) == port_u32(&port, cinfo, 0x28))
    {
        eax = port_u32(&port, cinfo, 0x24);
        port_set32(&port, cinfo, 0x78, eax);
        port_set32(&port, converter, 4, 0x4bb3d0);
    }
    else
    {
        eax = raise_error(&port, entry, cinfo, 0x1b, ebx, esi, edi);
    }
    if (port_u32(&port, cinfo, 0x54) == 0)
    {
        eax = port_u32(&port, cinfo, 0x78);
        port_set32(&port, cinfo, 0x7c, eax);
        return port_return(&port, eax, entry->edx);
    }
    port_set32(&port, cinfo, 0x7c, 1);
    return port_return(&port, eax, entry->edx);
}
