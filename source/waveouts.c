#include "waveouts.h"

/* The sound output device's opening. */

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

/* Original 0x410fa0: the sound output of the settings eax: the state 0x532500 (0x78 bytes) is
 * cleared (0x4eb5c0); when the mapper's capabilities are read (waveOutGetDevCapsA 0x4f173c)
 * without stereo formats (0xaaa) +5 bit 0 is cleared, without 16 bit ones (0xccc) +4 bit 0, and
 * without 44 kHz ones the rate +6 is held to 22050; the format (PCM, stereo by +5, 16 bit by +4,
 * the rate +6; its last word is the saved edi) is opened (waveOutOpen 0x4f1744 into 0x532500,
 * 5 on failure), and three buffers of a twentieth of a second (in 16 bytes) are allocated and
 * locked (GlobalAlloc 0x4f1c0c of 0x2002, GlobalLock 0x4f1c24) into the handles 0x532504 and the
 * headers 0x532510 (32 bytes each, marked done). 0. */
uint32_t vertrix_port_sound_output_open_410fa0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x5c
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t settings = entry->eax;
    uint32_t edx;
    uint32_t ebx = 0x78;
    uint32_t ecx = entry->ecx;
    uint32_t rate;
    uint32_t size;
    uint32_t eax;
    uint32_t index;
    uint32_t args[6];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    port_call_with(&port, 0x4eb5c0, 0x532500, 0, 0x78, ecx, settings, entry->edi, ebp);
    args[0] = 0xffffffffu;
    args[1] = ebp - 0x58;
    args[2] = 0x34;
    if (call_frame(&port, 0x4f173c, ebp - 0x58, vertrix_lift_edx, 0x78, ecx, settings, entry->edi,
                   ebp, args, 3) != 0)
    {
        if ((port_u16(&port, ebp, -0x30u) & 0xaaa) == 0)
        {
            port_set8(&port, settings, 5, port_u8(&port, settings, 5) & 0xfe);
        }
        if ((port_u16(&port, ebp, -0x30u) & 0xccc) == 0)
        {
            port_set8(&port, settings, 4, port_u8(&port, settings, 4) & 0xfe);
        }
        if ((port_u8(&port, ebp, -0x2fu) & 0xf) == 0 && port_u16(&port, settings, 6) > 0x5622)
        {
            port_set16(&port, settings, 6, 0x5622);
        }
    }
    edx = vertrix_lift_edx;
    port_set16(&port, ebp, -0x24u, 1);
    port_set16(&port, ebp, -0x22u, (port_u8(&port, settings, 5) & 1) + 1);
    port_set16(&port, ebp, -0x16u, (port_u8(&port, settings, 4) & 1) != 0 ? 0x10 : 8);
    port_set32(&port, ebp, -0x20u, port_u16(&port, settings, 6));
    port_set32(&port, ebp, -0x1cu, port_u16(&port, settings, 6));
    port_set16(&port, ebp, -0x18u, 1);
    if ((port_u8(&port, settings, 5) & 1) != 0)
    {
        edx = port_u32(&port, ebp, -0x1cu) * 2;
        port_set32(&port, ebp, -0x1cu, edx);
        port_set16(&port, ebp, -0x18u, 2);
    }
    if ((port_u8(&port, settings, 4) & 1) != 0)
    {
        ecx = port_u32(&port, ebp, -0x1cu) * 2;
        port_set32(&port, ebp, -0x1cu, ecx);
        ebx = port_u32(&port, ebp, -0x18u) * 2;
        port_set16(&port, ebp, -0x18u, ebx);
    }
    args[0] = 0x532500;
    args[1] = 0xffffffffu;
    args[2] = ebp - 0x24;
    args[3] = 0;
    args[4] = 0;
    args[5] = 0;
    if (call_frame(&port, 0x4f1744, ebp - 0x24, edx, ebx, ecx, settings, entry->edi, ebp, args,
                   6) != 0)
    {
        return port_return(&port, 5, entry->edx);
    }
    rate = port_u16(&port, settings, 6);
    eax = rate / 0x14;
    edx = rate % 0x14;
    size = rate / 0x14;
    if ((port_u8(&port, settings, 4) & 1) != 0)
    {
        size += size;
    }
    if ((port_u8(&port, settings, 5) & 1) != 0)
    {
        size += size;
    }
    size += 0xf;
    size = (size & 0xffff0000u) | (size & 0xfff0);
    for (index = 0; index < 3; ++index)
    {
        args[0] = 0x2002;
        args[1] = size;
        eax =
            call_frame(&port, 0x4f1c0c, eax, edx, index * 0x20, ecx, index * 4, size, ebp, args, 2);
        port_set32(&port, 0, 0x532504 + index * 4, eax);
        args[0] = eax;
        eax = call_frame(&port, 0x4f1c24, eax, vertrix_lift_edx, index * 0x20, ecx, index * 4, size,
                         ebp, args, 1);
        edx = vertrix_lift_edx;
        port_set32(&port, 0, 0x532510 + index * 0x20, eax);
        port_set32(&port, 0, 0x532514 + index * 0x20, size);
        port_set32(&port, 0, 0x532520 + index * 0x20, 1);
        ecx = 0;
        port_set32(&port, 0, 0x532524 + index * 0x20, 0);
        port_set32(&port, 0, 0x53251c + index * 0x20, 0);
    }
    return port_return(&port, 0, entry->edx);
}
