#include "lettercalls.h"

/* The title letters that call out the count and the digits. */

/* The guard record (0x4ec1ec, `guard`) of a frame routine at `record`. */
static void guard_record(Port *port, uint32_t record, uint32_t guard)
{
    port_set32(port, record, 0, port->env.chain);
    port_set32(port, record, 4, 0x4ec1ec);
    port_set32(port, record, 8, guard);
    port_set32(port, record, 0xc, 0);
}

/* Original 0x459be0: the title letter eax (guarded 0x51536c) when due (0x4ac500, 0x4ac520) takes
 * its stride (0x4ac540, 0x4ac5b0), moves (0x4ad060) and is placed (0x4ad260 into ebp-0x18 and
 * ebp-0x1c). Its height +0x28 above its fall (the word +0x30) leaves it dark (+0x44 0, +0x48 0);
 * otherwise its depth +0x44 is 0x10 less 16 parts of the fall of the height (0 to 0x10). Its turn
 * +0x2a falls by +0x32 times the stride (0 when the height is below 0), it bobs (0x4ad530) and
 * takes its place at +8, +0xa. Landed (height 0), it stands at +0x2c, +0x2e lit (+0x44 0x10), the
 * channel 0x4f81b8 + its +0x58 less 1 takes its volume (0x417290 for a letter +4 of 1, 0x417260
 * otherwise) and the letter takes the state 0x459ec0 (0x4ac8f0). It is centred on its anchor
 * (0x457890) in the end; the registers but eax kept, eax the guard's link. */
uint32_t vertrix_port_title_letter_count_call_459be0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x34
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t letter = entry->eax;
    uint32_t guard = 0x51536c;
    uint32_t ebx = guard;
    uint32_t esi = 0;
    uint32_t edi;
    uint32_t height;
    uint32_t depth;
    uint32_t channel;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    guard_record(&port, ebp - 0x30, guard);
    edi = port_u32(&port, letter, 0x2e);
    port_call_with(&port, 0x4ac500, letter, 0x4ec1ec, ebx, letter, esi, edi, ebp);
    edi = (uint32_t)((int32_t)edi >> 16);
    if (port_call_with(&port, 0x4ac520, letter, vertrix_lift_edx, ebx, letter, esi, edi, ebp) == 1)
    {
        esi = port_call_with(&port, 0x4ac540, letter, vertrix_lift_edx, ebx, letter, esi, edi, ebp);
        port_call_with(&port, 0x4ac5b0, letter, esi, ebx, letter, esi, edi, ebp);
        ebx = ebp - 0x1c;
        port_call_with(&port, 0x4ad060, letter, vertrix_lift_edx, ebx, letter, esi, edi, ebp);
        port_call_with(&port, 0x4ad260, letter, ebp - 0x18, ebx, letter, esi, edi, ebp);
        height = (uint32_t)((int32_t)port_u32(&port, letter, 0x28) >> 16);
        ebx = height;
        if (height > edi)
        {
            port_set8(&port, letter, 0x44, 0);
            port_set16(&port, letter, 0x48, 0);
        }
        else
        {
            /* The original's div leaves the dividend for a zero fall (and the height is 0 then). */
            depth = 0x10 - (edi != 0 ? (height << 4) / edi : height << 4);
            port_set8(&port, letter, 0x44, (int32_t)depth >= 0x10 ? 0x10 : depth);
        }
        port_set16(&port, letter, 0x2a,
                   port_u16(&port, letter, 0x2a) - port_u16(&port, letter, 0x32) * esi);
        if ((int32_t)port_u32(&port, letter, 0x28) < 0)
        {
            port_set16(&port, letter, 0x2a, 0);
        }
        port_call_with(&port, 0x4ad530, letter, esi, ebx, letter, esi, edi, ebp);
        port_set16(&port, letter, 8, port_u32(&port, ebp, -0x18u));
        port_set16(&port, letter, 0xa, port_u32(&port, ebp, -0x1cu));
        if (height == 0)
        {
            port_set8(&port, letter, 0x44, 0x10);
            port_set16(&port, letter, 8, port_u16(&port, letter, 0x2c));
            edi = port_u32(&port, letter, 4);
            port_set16(&port, letter, 0xa, port_u16(&port, letter, 0x2e));
            channel = port_u32(&port, 0, 0x4f81b8) + port_u32(&port, letter, 0x58);
            port_call_with(&port, edi == 1 ? 0x417290 : 0x417260, channel - 1, channel, ebx, letter,
                           esi, edi, ebp);
            port_call_with(&port, 0x4ac8f0, letter, 0x459ec0, ebx, letter, esi, edi, ebp);
        }
    }
    port_call_with(&port, 0x457890, letter, vertrix_lift_edx, ebx, letter, esi, edi, ebp);
    return port_return(&port, port_u32(&port, ebp, -0x30u), entry->edx);
}

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

static uint32_t sign16(uint32_t value)
{
    return (uint32_t)(int32_t)(int16_t)value;
}

/* Original 0x459ec0: the title letter eax (guarded 0x515378) when due (0x4ac500, 0x4ac520) takes
 * its stride (0x4ac540, 0x4ac5b0), moves (0x4ad060) and is placed (0x4ad260 into ebp-0x18 and
 * ebp-0x1c); its depth +0x44 is as in 0x459be0 (dark above its fall, the word +0x30). It is
 * centred on its place by its size (0x4b14c0), its turn +0x2a rises by +0x32 times the stride and
 * it bobs (0x4ad530). Dark, unless 0x4ad6e0 with 1 holds it its owner (the table 0x540f88 at its
 * +4) is asked (0x450f80; 0 sets 0x532a3c) and it takes the state 0; held, the text of its +0x58
 * (0x4cdfb0 of 0x50e21d into a temporary, 0x4ca070 and 0x4ca210) gives its first character's
 * image (0x43f420 with the font byte 0x4f9c05) to 0x4ac950, and it turns (0x4ac8a0 of 0x459be0)
 * and takes the state that leaves. The registers but eax kept, eax the guard's link. */
uint32_t vertrix_port_title_letter_digit_call_459ec0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x40
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t letter = entry->eax;
    uint32_t guard = 0x515378;
    uint32_t ebx = guard;
    uint32_t esi = 0;
    uint32_t edi;
    uint32_t height;
    uint32_t depth;
    uint32_t edx;
    uint32_t args[3];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    guard_record(&port, ebp - 0x3c, guard);
    edi = port_u32(&port, letter, 0x2e);
    port_call_with(&port, 0x4ac500, letter, 0x4ec1ec, ebx, letter, esi, edi, ebp);
    edi = (uint32_t)((int32_t)edi >> 16);
    if (port_call_with(&port, 0x4ac520, letter, vertrix_lift_edx, ebx, letter, esi, edi, ebp) != 1)
    {
        return port_return(&port, port_u32(&port, ebp, -0x3cu), entry->edx);
    }
    esi = port_call_with(&port, 0x4ac540, letter, vertrix_lift_edx, ebx, letter, esi, edi, ebp);
    port_call_with(&port, 0x4ac5b0, letter, esi, ebx, letter, esi, edi, ebp);
    ebx = ebp - 0x1c;
    port_call_with(&port, 0x4ad060, letter, vertrix_lift_edx, ebx, letter, esi, edi, ebp);
    port_call_with(&port, 0x4ad260, letter, ebp - 0x18, ebx, letter, esi, edi, ebp);
    height = (uint32_t)((int32_t)port_u32(&port, letter, 0x28) >> 16);
    if (height > edi)
    {
        port_set8(&port, letter, 0x44, 0);
        port_set16(&port, letter, 0x48, 0);
    }
    else
    {
        /* The original's div leaves the dividend for a zero fall (and the height is 0 then). */
        depth = 0x10 - (edi != 0 ? (height << 4) / edi : height << 4);
        port_set8(&port, letter, 0x44, (int32_t)depth >= 0x10 ? 0x10 : depth);
    }
    ebx = ebp - 0x24;
    edi = 0;
    port_set32(&port, ebp, -0x28u, 0);
    port_set32(&port, ebp, -0x24u, 0);
    port_call_with(&port, 0x4b14c0, letter, ebp - 0x28, ebx, letter, esi, edi, ebp);
    port_set16(&port, letter, 0xe,
               sign16(port_u16(&port, ebp, -0x18u)) - (port_u32(&port, ebp, -0x28u) >> 1));
    edx = sign16(port_u16(&port, ebp, -0x1cu)) - (port_u32(&port, ebp, -0x24u) >> 1);
    port_set16(&port, letter, 0x16, edx);
    port_set16(&port, letter, 0x2a,
               port_u16(&port, letter, 0x2a) + port_u16(&port, letter, 0x32) * esi);
    port_call_with(&port, 0x4ad530, letter, esi, ebx, letter, esi, edi, ebp);
    if (port_u8(&port, letter, 0x44) != 0)
    {
        return port_return(&port, port_u32(&port, ebp, -0x3cu), entry->edx);
    }
    if (port_call_with(&port, 0x4ad6e0, letter, 1, ebx, letter, esi, edi, ebp) == 0)
    {
        if (port_call_with(&port, 0x450f80,
                           port_u32(&port, port_u32(&port, letter, 4) * 4, 0x540f88),
                           vertrix_lift_edx, ebx, letter, esi, edi, ebp) == 0)
        {
            port_set32(&port, 0, 0x532a3c, 1);
        }
        port_call_with(&port, 0x4ac8f0, letter, 0, ebx, letter, esi, edi, ebp);
        return port_return(&port, port_u32(&port, ebp, -0x3cu), entry->edx);
    }
    port_call_with(&port, 0x4ca070, ebp - 0x20, 1, ebx, letter, esi, edi, ebp);
    port_set32(&port, ebp, -0x30u, vertrix_lift_edx);
    ebx = port_u32(&port, letter, 0x58);
    args[0] = ebp - 0x20;
    args[1] = 0x50e21d;
    args[2] = ebx;
    call_frame(&port, 0x4cdfb0, ebp - 0x20, vertrix_lift_edx, ebx, letter, esi, edi, ebp, args, 3);
    edx =
        port_call_with(&port, 0x43f420, (uint32_t)((int32_t)port_u32(&port, 0, 0x4f9c02) >> 24),
                       port_u8(&port, port_u32(&port, ebp, -0x20u), 0), ebx, letter, esi, edi, ebp);
    port_call_with(&port, 0x4ac950, letter, edx, ebx, letter, esi, edi, ebp);
    port_call_with(&port, 0x4ac8a0, letter, 0x459be0, ebx, letter, esi, edi, ebp);
    port_call_with(&port, 0x4ac8f0, letter, vertrix_lift_edx, ebx, letter, esi, edi, ebp);
    port_set32(&port, ebp, -0x30u, edi);
    port_call_with(&port, 0x4ca210, ebp - 0x20, 0, ebx, letter, esi, edi, ebp);
    port_set32(&port, ebp, -0x30u, edi);
    return port_return(&port, port_u32(&port, ebp, -0x3cu), entry->edx);
}
