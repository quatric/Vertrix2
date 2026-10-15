#include "port_huffstarts.h"

/* The Huffman decoder's pass start. */

/* Original 0x4bba40: the Huffman decoder +0x1bc of the decoder eax starts a sequential pass: a
 * scan other than 0..63 with no approximation (+0x190, +0x194, +0x198, +0x19c) warns 0x7a (the
 * error manager [eax]'s method +4 with -1). Each scan component (+0x148 of them, +0x14c on) has
 * its DC (+0x14) and AC (+0x18) tables derived (0x4bbc00 into +0x28 and +0x38 by number) and its
 * last DC value (+0x14 on) cleared; each block of the MCU (+0x164 of them, its component by
 * +0x168 on) takes its tables (+0x48, +0x70 on), whether it is needed (+0x98, from +0x30) and
 * whether its AC is (+0xc0, more than one coefficient +0x24). The bit buffer +8..+0x10 is cleared
 * and the restart count +0x24 set to +0x114, which is eax; edx kept. */
uint32_t vertrix_port_huffman_start_pass_4bba40(PORT_SIGNATURE)
{
    Port port;
    uint32_t cinfo = entry->eax;
    uint32_t entropy;
    uint32_t error;
    uint32_t component;
    uint32_t place;
    uint32_t dc;
    uint32_t ac;
    uint32_t ci;
    uint32_t block;
    uint32_t edi = entry->edi;
    uint32_t value;
    port_open(&port, calls, services, globals, entry);
    entropy = port_u32(&port, cinfo, 0x1bc);
    if (port_u32(&port, cinfo, 0x190) != 0 || port_u32(&port, cinfo, 0x194) != 0x3f ||
        port_u32(&port, cinfo, 0x198) != 0 || port_u32(&port, cinfo, 0x19c) != 0)
    {
        port_set32(&port, port_u32(&port, cinfo, 0), 0x14, 0x7a);
        error = port_u32(&port, cinfo, 0);
        port_call_with(&port, port_u32(&port, error, 4), cinfo, 0xffffffffu, entry->ebx, error,
                       cinfo, edi, entry->esp - 4);
    }
    ci = 0;
    if ((int32_t)port_u32(&port, cinfo, 0x148) > 0)
    {
        place = cinfo;
        dc = entropy;
        do
        {
            component = port_u32(&port, place, 0x14c);
            value = port_u32(&port, component, 0x14);
            edi = port_u32(&port, component, 0x18);
            port_call_with(&port, 0x4bbc00, cinfo, 1, value, entropy + 0x28 + value * 4, cinfo, edi,
                           entry->esp - 4);
            ac = edi;
            port_call_with(&port, 0x4bbc00, cinfo, 0, ac, entropy + 0x38 + ac * 4, cinfo, ci,
                           entry->esp - 4);
            ci++;
            edi = ci;
            port_set32(&port, dc, 0x14, 0);
            dc += 4;
            place += 4;
        } while ((int32_t)ci < (int32_t)port_u32(&port, cinfo, 0x148) && !port.env.failed);
    }
    if ((int32_t)port_u32(&port, cinfo, 0x164) > 0)
    {
        place = entropy;
        block = 0;
        do
        {
            component =
                port_u32(&port, cinfo, port_u32(&port, cinfo + block * 4, 0x168) * 4 + 0x14c);
            port_set32(&port, place, 0x48,
                       port_u32(&port, port_u32(&port, component, 0x14) * 4 + entropy, 0x28));
            port_set32(&port, place, 0x70,
                       port_u32(&port, port_u32(&port, component, 0x18) * 4 + entropy, 0x38));
            if (port_u32(&port, component, 0x30) != 0)
            {
                port_set32(&port, place, 0x98, 1);
                port_set32(&port, place, 0xc0, (int32_t)port_u32(&port, component, 0x24) > 1);
            }
            else
            {
                port_set32(&port, place, 0xc0, 0);
                port_set32(&port, place, 0x98, 0);
            }
            place += 4;
            block++;
        } while ((int32_t)block < (int32_t)port_u32(&port, cinfo, 0x164) && !port.env.failed);
    }
    port_set32(&port, entropy, 0x10, 0);
    port_set32(&port, entropy, 0xc, 0);
    port_set32(&port, entropy, 8, 0);
    value = port_u32(&port, cinfo, 0x114);
    port_set32(&port, entropy, 0x24, value);
    return port_return(&port, value, entry->edx);
}
