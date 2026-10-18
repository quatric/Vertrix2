#include "rtlsampleattaches.h"

/* A module instrument's sample attached. */

/* Original 0x40f910: the instrument record edx copied into the instrument eax (0x4eb860, 22
 * bytes); a record with a length +0x18 gets a 60-byte sample (0x4ec160; 8 when it fails) set at
 * +0xf8 with +0x80 1: its length +0x2c, volume +0x20 (+0x25), +0x23 (+0x24), +0x21 128, and when
 * the loop start +0x1c and end +0x20 are at least 2 apart and inside it, looping (+0x3a 0x10, +0x30
 * and +0x34). The data buffer +0x24 made (0x40ac50, whose failure is returned), read (0x40c220),
 * turned from signed to unsigned and finished (0x40acd0). eax 0. */
uint32_t vertrix_port_instrument_sample_attach_40f910(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x10
    };
    Port port;
    uint32_t object = entry->eax;
    uint32_t record = entry->edx;
    uint32_t sample;
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, entry->esp, -4u, entry->ebx);
    port_set32(&port, entry->esp, -8u, entry->ecx);
    port_set32(&port, entry->esp, -0xcu, entry->esi);
    port_set32(&port, entry->esp, -0x10u, entry->edi);
#define CALL(target, a, d, b, s)                                                                   \
    port_call_with(&port, target, a, d, b, record, s, object, entry->ebp)
    CALL(0x4eb860, object, record, 0x16, entry->esi);
    edx = vertrix_lift_edx;
    if (port_u32(&port, record, 0x18) == 0)
    {
        return port_return(&port, 0, edx);
    }
    sample = CALL(0x4ec160, 1, 0x3c, 0x16, entry->esi);
    edx = vertrix_lift_edx;
    if (sample == 0)
    {
        return port_return(&port, 8, edx);
    }
    port_set16(&port, object, 0x80, 1);
    port_set32(&port, object, 0xf8, sample);
    port_set16(&port, sample, 0x3a, 0);
    port_set32(&port, sample, 0x2c, port_u32(&port, record, 0x18));
    port_set8(&port, sample, 0x20, port_u8(&port, record, 0x25));
    port_set8(&port, sample, 0x23, port_u8(&port, record, 0x24));
    port_set8(&port, sample, 0x21, 0x80);
    edx = port_u32(&port, record, 0x1c) + 2;
    ebx = port_u32(&port, record, 0x20);
    if (edx < ebx && ebx <= port_u32(&port, record, 0x18))
    {
        port_set8(&port, sample, 0x3a, port_u8(&port, sample, 0x3a) | 0x10);
        port_set32(&port, sample, 0x30, port_u32(&port, record, 0x1c));
        edx = port_u32(&port, record, 0x20);
        port_set32(&port, sample, 0x34, edx);
    }
    eax = CALL(0x40ac50, sample + 0x24, edx, ebx, sample);
    edx = vertrix_lift_edx;
    if (eax != 0)
    {
        return port_return(&port, eax, edx);
    }
    CALL(0x40c220, port_u32(&port, sample, 0x24), port_u32(&port, sample, 0x2c), ebx, sample);
    eax = port_u32(&port, sample, 0x24);
    for (ebx = port_u32(&port, sample, 0x2c) - 1; ebx != 0xffffffffu && !port.env.failed; ebx--)
    {
        port_set8(&port, eax, 0, port_u8(&port, eax, 0) ^ 0x80);
        eax++;
    }
    CALL(0x40acd0, sample + 0x24, 0, port_u32(&port, sample, 0x2c), sample);
#undef CALL
    return port_return(&port, 0, vertrix_lift_edx);
}
