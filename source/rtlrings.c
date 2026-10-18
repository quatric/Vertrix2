#include "rtlrings.h"

/* The sound ring buffer refill. */

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

/* Original 0x40b490: up to eax samples (doubled for 16-bit 0x52f16b and stereo 0x52f16a, at most
 * the ring size 0x52f164) written into the sound buffer 0x52f158 behind its play position (its
 * method +0x10) from the write position 0x52f160, rounded down to four and less 128: the part
 * locked (+0x2c; on failure restored by +0x50), filled by the mixer 0x52f15c or cleared
 * (0x4eb5c0), unlocked (+0x4c) and the write position advanced round the ring. eax 0, edx kept.
 */
uint32_t vertrix_port_sound_ring_fill_40b490(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x34
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t want = entry->eax;
    uint32_t buffer;
    uint32_t vtable;
    uint32_t eax;
    uint32_t ecx = entry->ecx;
    uint32_t length;
    uint32_t position;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    if (port_u8(&port, 0, 0x52f16b) & 1)
    {
        want += want;
    }
    if (port_u8(&port, 0, 0x52f16a) & 1)
    {
        want += want;
    }
    if (want == 0 || want >= port_u32(&port, 0, 0x52f164))
    {
        want = port_u32(&port, 0, 0x52f164);
    }
    buffer = port_u32(&port, 0, 0x52f158);
    vtable = port_u32(&port, buffer, 0);
    {
        uint32_t args[3] = {buffer, ebp - 0x20, ebp - 0x1c};
        eax = call_frame(&port, port_u32(&port, vtable, 0x10), buffer, ebp - 0x20, want, vtable,
                         entry->esi, entry->edi, ebp, args, 3);
    }
    if (eax != 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    ecx = port_u32(&port, 0, 0x52f160);
    length = port_u32(&port, ebp, -0x20u) - ecx;
    port_set32(&port, ebp, -0x18u, length);
    if ((int32_t)length < 0)
    {
        port_set32(&port, ebp, -0x18u, length + port_u32(&port, 0, 0x52f164));
    }
    if (want < port_u32(&port, ebp, -0x18u))
    {
        port_set32(&port, ebp, -0x18u, want);
    }
    port_set8(&port, ebp, -0x18u, port_u8(&port, ebp, -0x18u) & 0xfc);
    length = port_u32(&port, ebp, -0x18u) - 0x80;
    port_set32(&port, ebp, -0x18u, length);
    if ((int32_t)length <= 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    buffer = port_u32(&port, 0, 0x52f158);
    vtable = port_u32(&port, buffer, 0);
    position = port_u32(&port, 0, 0x52f160);
    {
        uint32_t args[8] = {buffer,     position,   length,     ebp - 0x30,
                            ebp - 0x28, ebp - 0x2c, ebp - 0x24, 0};
        eax = call_frame(&port, port_u32(&port, vtable, 0x2c), buffer, ebp - 0x30, vtable, ecx,
                         length, position, ebp, args, 8);
    }
    if (eax != 0)
    {
        uint32_t args[1] = {buffer};
        buffer = port_u32(&port, 0, 0x52f158);
        vtable = port_u32(&port, buffer, 0);
        args[0] = buffer;
        call_frame(&port, port_u32(&port, vtable, 0x50), buffer, vtable, vtable, ecx, length,
                   position, ebp, args, 1);
        return port_return(&port, 0, entry->edx);
    }
    if (port_u32(&port, 0, 0x52f15c) == 0)
    {
        call_frame(&port, 0x4eb5c0, port_u32(&port, ebp, -0x30u), 0, port_u32(&port, ebp, -0x28u),
                   ecx, length, position, ebp, NULL, 0);
        if (port_u32(&port, ebp, -0x2cu) != 0)
        {
            call_frame(&port, 0x4eb5c0, port_u32(&port, ebp, -0x2cu), 0,
                       port_u32(&port, ebp, -0x24u), ecx, length, position, ebp, NULL, 0);
        }
    }
    else
    {
        call_frame(&port, port_u32(&port, 0, 0x52f15c), port_u32(&port, ebp, -0x30u),
                   port_u32(&port, ebp, -0x28u), vtable, ecx, length, position, ebp, NULL, 0);
        ecx = port_u32(&port, ebp, -0x2cu);
        if (ecx != 0)
        {
            call_frame(&port, port_u32(&port, 0, 0x52f15c), ecx, port_u32(&port, ebp, -0x24u),
                       vtable, ecx, length, position, ebp, NULL, 0);
        }
    }
    buffer = port_u32(&port, 0, 0x52f158);
    vtable = port_u32(&port, buffer, 0);
    {
        uint32_t args[5] = {buffer, port_u32(&port, ebp, -0x30u), port_u32(&port, ebp, -0x28u),
                            port_u32(&port, ebp, -0x2cu), port_u32(&port, ebp, -0x24u)};
        call_frame(&port, port_u32(&port, vtable, 0x4c), buffer, args[2], vtable, args[1], args[4],
                   args[3], ebp, args, 5);
    }
    position = port_u32(&port, 0, 0x52f160) + port_u32(&port, ebp, -0x18u);
    port_set32(&port, 0, 0x52f160, position);
    if (position >= port_u32(&port, 0, 0x52f164))
    {
        port_set32(&port, 0, 0x52f160, position - port_u32(&port, 0, 0x52f164));
    }
    return port_return(&port, 0, entry->edx);
}
