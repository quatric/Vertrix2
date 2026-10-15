#include "port_jpegdefaults.h"

/* The JPEG decoder's default parameters. */

/* The message `code` (+0x14 of the error manager [cinfo]) with the byte +0x128 as its word, shown
 * at level -1 (method +4); the call's eax. */
static uint32_t warn_transform(Port *port, const LiftEntry *entry, uint32_t cinfo, uint32_t code)
{
    uint32_t error = port_u32(port, cinfo, 0);
    port_set32(port, error, 0x14, code);
    port_set32(port, port_u32(port, cinfo, 0), 0x18, port_u8(port, cinfo, 0x128));
    error = port_u32(port, cinfo, 0);
    return port_call_with(port, port_u32(port, error, 4), cinfo, 0xffffffffu, error, cinfo,
                          entry->esi, entry->edi, entry->ebp);
}

/* Original 0x4b9330: the colour spaces of the decompressor eax by its component count +0x24: 1 is
 * grey (1, 1); 3 is YCbCr (3, 2) unless the JFIF mark +0x118 is clear and the Adobe mark +0x124
 * is set with transform byte +0x128 0 (RGB 2, 2) or other than 1 (message 0x72); without either
 * mark the component ids (+0xd8, 0x54 apart) 1 2 3 give YCbCr, 'R' 'G' 'B' RGB, others message
 * 0x6f (the ids in the words) and YCbCr. 4 is CMYK (4, 4), or YCCK (5, 4) with an Adobe transform
 * 2 (0 keeps CMYK, others message 0x72); other counts are unknown (0, 0). The spaces go to +0x28
 * and +0x2c and the defaults to +0x30..+0x6c and +0x88. eax is the last value tested; edx kept. */
uint32_t vertrix_port_jpeg_default_parms_4b9330(PORT_SIGNATURE)
{
    Port port;
    uint32_t cinfo = entry->eax;
    uint32_t count;
    uint32_t eax;
    uint32_t error;
    uint32_t esi;
    uint32_t components;
    uint32_t first;
    uint32_t third;
    port_open(&port, calls, services, globals, entry);
    count = port_u32(&port, cinfo, 0x24);
    eax = count;
    if (count == 1)
    {
        port_set32(&port, cinfo, 0x28, 1);
        port_set32(&port, cinfo, 0x2c, 1);
    }
    else if (count == 3)
    {
        if (port_u32(&port, cinfo, 0x118) == 0)
        {
            if (port_u32(&port, cinfo, 0x124) != 0)
            {
                eax = port_u8(&port, cinfo, 0x128);
                if (eax == 0)
                {
                    port_set32(&port, cinfo, 0x28, 2);
                    port_set32(&port, cinfo, 0x2c, 2);
                    goto defaults;
                }
                if (eax != 1)
                {
                    eax = warn_transform(&port, entry, cinfo, 0x72);
                }
            }
            else
            {
                components = port_u32(&port, cinfo, 0xd8);
                first = port_u32(&port, components, 0);
                eax = port_u32(&port, components, 0x54);
                third = port_u32(&port, components, 0xa8);
                if (first == 0x52 && eax == 0x47 && third == 0x42)
                {
                    port_set32(&port, cinfo, 0x28, 2);
                    port_set32(&port, cinfo, 0x2c, 2);
                    goto defaults;
                }
                if (!(first == 1 && eax == 2 && third == 3))
                {
                    esi = port_u32(&port, cinfo, 0);
                    port_set32(&port, esi, 0x18, first);
                    port_set32(&port, esi, 0x1c, eax);
                    port_set32(&port, esi, 0x20, third);
                    port_set32(&port, port_u32(&port, cinfo, 0), 0x14, 0x6f);
                    error = port_u32(&port, cinfo, 0);
                    eax = port_call_with(&port, port_u32(&port, error, 4), cinfo, 1, error, cinfo,
                                         esi, entry->edi, entry->ebp);
                }
            }
        }
        port_set32(&port, cinfo, 0x28, 3);
        port_set32(&port, cinfo, 0x2c, 2);
    }
    else if (count == 4)
    {
        if (port_u32(&port, cinfo, 0x124) == 0)
        {
            port_set32(&port, cinfo, 0x28, 4);
            port_set32(&port, cinfo, 0x2c, 4);
            goto defaults;
        }
        eax = port_u8(&port, cinfo, 0x128);
        if (eax == 0)
        {
            port_set32(&port, cinfo, 0x28, 4);
            port_set32(&port, cinfo, 0x2c, 4);
            goto defaults;
        }
        if (eax != 2)
        {
            eax = warn_transform(&port, entry, cinfo, 0x72);
        }
        port_set32(&port, cinfo, 0x28, 5);
        port_set32(&port, cinfo, 0x2c, 4);
    }
    else
    {
        port_set32(&port, cinfo, 0x28, 0);
        port_set32(&port, cinfo, 0x2c, 0);
    }
defaults:
    port_set32(&port, cinfo, 0x30, 1);
    port_set32(&port, cinfo, 0x34, 1);
    port_set32(&port, cinfo, 0x38, 0);
    port_set32(&port, cinfo, 0x3c, 0x3ff00000);
    port_set32(&port, cinfo, 0x40, 0);
    port_set32(&port, cinfo, 0x44, 0);
    port_set32(&port, cinfo, 0x48, 0);
    port_set32(&port, cinfo, 0x4c, 1);
    port_set32(&port, cinfo, 0x50, 1);
    port_set32(&port, cinfo, 0x54, 0);
    port_set32(&port, cinfo, 0x58, 2);
    port_set32(&port, cinfo, 0x5c, 1);
    port_set32(&port, cinfo, 0x60, 0x100);
    port_set32(&port, cinfo, 0x88, 0);
    port_set32(&port, cinfo, 0x64, 0);
    port_set32(&port, cinfo, 0x68, 0);
    port_set32(&port, cinfo, 0x6c, 0);
    return port_return(&port, eax, entry->edx);
}
