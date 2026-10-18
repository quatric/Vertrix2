#include "rtlmoduleloads.h"

/* A music module read. */

/* A call with the tracked registers that leaves its eax and edx in *eax and *edx. */
static void module_call(Port *port, uint32_t *eax, uint32_t *edx, uint32_t target, uint32_t ebx,
                        uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp)
{
    *eax = port_call_registers(port, target, *eax, *edx, ebx, ecx, esi, edi, ebp, NULL, 0);
    *edx = vertrix_lift_edx;
}

/* Original 0x40f360: a four-channel module read into a new song (0x4ec160 of 0x158 bytes) kept at
 * edx. The reader eax checked (0x40c1c0, any answer 10) and started from ebx (0x40c1f0); the
 * title (20 bytes at 0x531b8c), 31 sample headers (30 bytes from 0x531ba0: the name 22, the
 * length and loop as words 0x40c360, the tune and volume bytes 0x40c320), the order length and
 * restart (0x531f42/43), 128 orders (0x531f44) and the tag (0x531fc4) read (0x40c220). The tag
 * looked up in 0x4f7594 (8 a tag, 0x4ec180) gives the channels +0x26 (none: 11). The song: its
 * title, +0x20 0x8000, the order length and restart +0x22/+0x24, 31 samples +0x2a, +0x2c 6, the
 * tempo +0x2e 125, the orders +0x30 and their highest pattern +0x28 (plus one), the channel pans
 * +0x130 (0, 0xff, 0xff, 0); the patterns +0x150 (12 a pattern) each read (0x40f1a0) and the
 * instruments +0x154 (0xfc each): the header copied (0x4eb5e0 to 0x531fc8, 0x4eb860), and with a
 * length a sample (0x4ec160 of 0x3c) at +0xf8, +0x80 1: its length, loop (a loop longer than one
 * past its start, clipped to the length, flag 0x10), rate 8363, volume (at most 64) and fine tune;
 * its data allocated (0x40ac50), read (0x40c220) and converted (0x40acd0). A failure frees the
 * song (0x40ef90) and the reader (0x40c1e0) and answers 8 (or the step's answer); else the reader
 * freed, the song kept, eax 0. */
uint32_t vertrix_port_module_load_40f360(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t song;
    uint32_t sample;
#define CALL(target) module_call(&port, &eax, &edx, target, ebx, ecx, esi, edi, ebp)
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ecx);
    port_set32(&port, ebp, -8u, entry->esi);
    port_set32(&port, ebp, -0xcu, entry->edi);
    port_set32(&port, ebp, -0x14u, entry->edx);
    CALL(0x40c1c0);
    if (eax != 0)
    {
        return port_return(&port, 0xa, edx);
    }
    edx = 0;
    eax = ebx;
    CALL(0x40c1f0);
    edx = 0x158;
    eax = 1;
    CALL(0x4ec160);
    esi = eax;
    song = eax;
    if (song == 0)
    {
        CALL(0x40c1e0);
        return port_return(&port, 8, edx);
    }
    edx = 0x14;
    eax = 0x531b8c;
    CALL(0x40c220);
    for (ecx = 0; ecx < 0x1f && !port.env.failed; ecx++)
    {
        ebx = 0x531ba0 + ecx * 0x1e;
        edx = 0x16;
        eax = ebx;
        CALL(0x40c220);
        eax = ebx + 0x16;
        CALL(0x40c360);
        eax = ebx + 0x18;
        CALL(0x40c320);
        eax = ebx + 0x19;
        CALL(0x40c320);
        eax = ebx + 0x1a;
        CALL(0x40c360);
        eax = ebx + 0x1c;
        CALL(0x40c360);
    }
    eax = 0x531f42;
    CALL(0x40c320);
    eax = 0x531f43;
    CALL(0x40c320);
    edx = 0x80;
    eax = 0x531f44;
    CALL(0x40c220);
    edx = 4;
    eax = 0x531fc4;
    CALL(0x40c220);
    for (ecx = 0; ecx < 0x14 && !port.env.failed; ecx++)
    {
        edi = ecx * 8;
        edx = 0x4f7594 + edi;
        ebx = 4;
        eax = 0x531fc4;
        CALL(0x4ec180);
        if (eax == 0)
        {
            eax = (eax & 0xffff0000u) | port_u16(&port, edi, 0x4f7598);
            port_set16(&port, song, 0x26, eax);
            break;
        }
    }
    if (port_u16(&port, song, 0x26) == 0)
    {
        eax = song;
        CALL(0x40ef90);
        CALL(0x40c1e0);
        return port_return(&port, 0xb, edx);
    }
    ebx = 0x14;
    edx = 0x531b8c;
    eax = song;
    CALL(0x4eb860);
    port_set16(&port, song, 0x20, 0x8000);
    eax = (eax & 0xffff0000u) | port_u8(&port, 0, 0x531f42);
    port_set16(&port, song, 0x22, eax);
    eax = (eax & 0xffff0000u) | port_u8(&port, 0, 0x531f43);
    port_set16(&port, song, 0x24, eax);
    port_set16(&port, song, 0x2a, 0x1f);
    port_set16(&port, song, 0x2c, 6);
    port_set16(&port, song, 0x2e, 0x7d);
    for (ecx = 0; ecx < 0x80; ecx++)
    {
        uint32_t order = port_u8(&port, 0, 0x531f44 + ecx);
        port_set8(&port, song + ecx, 0x30, order);
        if ((int32_t)port_u16(&port, song, 0x28) < (int32_t)order)
        {
            port_set16(&port, song, 0x28, order);
        }
    }
    port_set16(&port, song, 0x28, port_u16(&port, song, 0x28) + 1);
    for (ecx = 0; ecx < port_u16(&port, song, 0x26); ecx++)
    {
        uint32_t pan = 0;
        if ((ecx & 3) != 0 && (ecx & 3) != 3)
        {
            pan = 0xff;
        }
        port_set8(&port, song + ecx, 0x130, pan);
    }
    eax = port_u16(&port, song, 0x28);
    edx = 0xc;
    CALL(0x4ec160);
    port_set32(&port, song, 0x150, eax);
    if (eax == 0)
    {
        eax = song;
        CALL(0x40ef90);
        CALL(0x40c1e0);
        return port_return(&port, 8, edx);
    }
    eax = port_u16(&port, song, 0x2a);
    edx = 0xfc;
    CALL(0x4ec160);
    port_set32(&port, song, 0x154, eax);
    if (eax == 0)
    {
        eax = song;
        CALL(0x40ef90);
        CALL(0x40c1e0);
        return port_return(&port, 8, edx);
    }
    edi = port_u32(&port, song, 0x150);
    for (ecx = 0; ecx < port_u16(&port, song, 0x28) && !port.env.failed; ecx++, edi += 0xc)
    {
        eax = port_u16(&port, song, 0x26);
        edx = edi;
        CALL(0x40f1a0);
        edx = eax;
        if (eax != 0)
        {
            eax = song;
            CALL(0x40ef90);
            CALL(0x40c1e0);
            return port_return(&port, edx, edx);
        }
    }
    edi = port_u32(&port, song, 0x154);
    for (ecx = 0; ecx < port_u16(&port, song, 0x2a) && !port.env.failed; ecx++, edi += 0xfc)
    {
        uint32_t length;
        uint32_t volume;
        edx = 0x531ba0 + ecx * 0x1e;
        ebx = 0x1e;
        eax = 0x531fc8;
        CALL(0x4eb5e0);
        ebx = 0x16;
        edx = 0x531fc8;
        eax = edi;
        CALL(0x4eb860);
        if (port_u16(&port, 0, 0x531fde) == 0)
        {
            continue;
        }
        edx = 0x3c;
        eax = 1;
        CALL(0x4ec160);
        ebx = eax;
        sample = eax;
        if (sample == 0)
        {
            eax = song;
            CALL(0x40ef90);
            CALL(0x40c1e0);
            return port_return(&port, 8, edx);
        }
        port_set16(&port, edi, 0x80, 1);
        port_set32(&port, edi, 0xf8, sample);
        port_set16(&port, sample, 0x3a, 0);
        length = port_u16(&port, 0, 0x531fde) * 2;
        edx = length;
        port_set32(&port, sample, 0x2c, length);
        port_set16(&port, sample, 0x38, 0x20ab);
        if (port_u16(&port, 0, 0x531fe4) > 1)
        {
            port_set32(&port, ebp, -0x1cu, port_u16(&port, 0, 0x531fe2));
            port_set32(&port, ebp, -0x18u, port_u16(&port, 0, 0x531fde));
            edx = port_u16(&port, 0, 0x531fe2);
            if ((int32_t)edx < (int32_t)port_u16(&port, 0, 0x531fde))
            {
                port_set8(&port, sample, 0x3a, port_u8(&port, sample, 0x3a) | 0x10);
                port_set32(&port, sample, 0x30, port_u16(&port, 0, 0x531fe2) * 2);
                port_set32(&port, sample, 0x34, port_u16(&port, 0, 0x531fe2) * 2);
                port_set32(&port, sample, 0x34,
                           port_u32(&port, sample, 0x34) + port_u16(&port, 0, 0x531fe4) * 2);
                edx = port_u32(&port, sample, 0x34);
                if (edx > port_u32(&port, sample, 0x2c))
                {
                    edx = port_u32(&port, sample, 0x2c);
                    port_set32(&port, sample, 0x34, edx);
                }
            }
        }
        volume = port_u8(&port, 0, 0x531fe1);
        edx = (edx & 0xffff00ffu) | (volume << 8);
        eax = volume > 0x40 ? 0x40 : volume;
        port_set8(&port, sample, 0x20, eax);
        eax = (eax & ~0xffu) | ((port_u8(&port, 0, 0x531fe0) & 0xf) << 4);
        port_set8(&port, sample, 0x23, eax);
        port_set8(&port, sample, 0x21, 0x80);
        eax = sample + 0x24;
        port_set32(&port, ebp, -0x10u, eax);
        CALL(0x40ac50);
        edx = eax;
        if (eax != 0)
        {
            eax = song;
            CALL(0x40ef90);
            CALL(0x40c1e0);
            return port_return(&port, edx, edx);
        }
        edx = port_u32(&port, sample, 0x2c);
        eax = port_u32(&port, sample, 0x24);
        CALL(0x40c220);
        ebx = port_u32(&port, sample, 0x2c);
        edx = 0;
        eax = sample + 0x24;
        CALL(0x40acd0);
    }
    eax = port_u16(&port, song, 0x2a);
    CALL(0x40c1e0);
    port_set32(&port, entry->edx, 0, song);
#undef CALL
    return port_return(&port, 0, edx);
}
