#include "rtllettergrids.h"

/* Screens of lettered lines. */

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

/* Original 0x46eda0 (guarded 0x5161c8): the lettered screen eax: its line count from 0x540000
 * and its texts from 0x53fe20 (4 per screen, 0xc per line), each line 0x32 below the last from
 * 0x1a4. A line's text is taken into a temporary (0x4ca070, 0x4ca310) and measured (0x440610 in
 * the font 0x4f9c0d) to centre it across 0x280 from 0x11, each letter 0x23 on: a sprite (0x15c
 * bytes, 0x4ca000; 0x4abd70 makes it) placed (0x4adf20 with 0x4578f0), given its glyph (0x43f420,
 * 0x4ac950; 0x4ac8a0), set at its place (+8/+0xe/+0x10 across, +0xa/+0x16 down, +0xc 0, +0x18
 * -40); on the last three lines it drops in (0x4ac8f0 with 0x457e40; +0x52 9, +0x94 1, +0x95 4,
 * +0x93 1, +0x4e 0x32, +0x18 to its row of the block centred down 0x1e0). Each is stepped by
 * 0x458410 (0x4ac910), +0x12 and +0x1a 1, +0x44 0, 0x4ac7d0 with 0x14, and added to 0x54671c
 * (0x4b5e70). The temporary released. eax the restored chain, edx kept. */
uint32_t vertrix_port_letter_grid_46eda0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x60
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t record = ebp - 0x5c;
    uint32_t text = ebp - 0x38;
    uint32_t zeros[5] = {0, 0, 0, 0x4578f0, 0};
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx = 0x5161c8;
    uint32_t ecx = 0x4ec1ec;
    uint32_t esi = 0;
    uint32_t edi = entry->edi;
    uint32_t lines;
    uint32_t line;
#define CALL(target, a, d) port_call_with(&port, target, a, d, ebx, ecx, esi, edi, ebp)
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    port_set32(&port, record, 0, port.env.chain);
    port.env.chain = record;
    port_set32(&port, ebp, -0x58u, 0x4ec1ec);
    port_set32(&port, ebp, -0x54u, 0x5161c8);
    port_set32(&port, ebp, -0x50u, 0);
    CALL(0x4ca070, text, entry->eax);
    eax = vertrix_lift_edx * 4;
    edi = 1;
    port_set32(&port, ebp, -0x18u, 0);
    lines = port_u32(&port, eax, 0x540000);
    port_set32(&port, ebp, -0x50u, 1);
    port_set32(&port, ebp, -0x1cu, lines);
    port_set32(&port, ebp, -0x2cu, 0x1a4);
    ebx = lines;
    if (lines != 0)
    {
        port_set32(&port, ebp, -0x28u, eax + 0x53fe20);
        port_set32(&port, ebp, -0x44u, lines - 3);
        port_set32(&port, ebp, -0x48u, 3 - lines);
        line = 0;
        do
        {
            uint32_t length;
            uint32_t letter;
            ebx = 0x10;
            ecx = ebp - 0x34;
            CALL(0x4ca310, text, port_u32(&port, ebp, -0x28u));
            length = port_u32(&port, port_u32(&port, text, 0) - 0xc, 4);
            esi = length;
            {
                uint32_t args[1] = {ebp - 0x30};
                call_frame(&port, 0x440610, (uint32_t)(int32_t)(int8_t)port_u8(&port, 0, 0x4f9c0d),
                           port_u32(&port, text, 0), ebx, ecx, esi, edi, ebp, args, 1);
            }
            edx = vertrix_lift_edx;
            edi = 0;
            port_set32(&port, ebp, -0x24u, 0);
            port_set32(&port, ebp, -0x20u, length);
            port_set32(&port, ebp, -0x3cu,
                       ((0x280 - port_u32(&port, ebp, -0x34u) + 1) >> 1) + 0x11);
            for (letter = 0; letter < length && !port.env.failed; letter++)
            {
                uint32_t sprite;
                uint32_t glyph;
                uint32_t across = port_u32(&port, ebp, -0x3cu);
                uint32_t down = port_u32(&port, ebp, -0x2cu);
                port_set32(&port, ebp, -0x40u, port_u32(&port, ebp, -0x48u));
                eax = CALL(0x4ca000, 0x15c, edx);
                if (eax != 0)
                {
                    eax = CALL(0x4abd70, eax, vertrix_lift_edx);
                }
                sprite = eax;
                esi = sprite;
                ebx = 0;
                ecx = 0;
                call_frame(&port, 0x4adf20, sprite, 0, 0, 0, esi, edi, ebp, zeros, 5);
                glyph = CALL(0x43f420, (uint32_t)(int32_t)(int8_t)port_u8(&port, 0, 0x4f9c0d),
                             port_u8(&port, port_u32(&port, text, 0) + letter, 0));
                CALL(0x4ac950, sprite, glyph);
                CALL(0x4ac8a0, sprite, vertrix_lift_edx);
                port_set16(&port, sprite, 0xc, 0);
                port_set16(&port, sprite, 8, across);
                port_set16(&port, sprite, 0xa, down);
                port_set16(&port, sprite, 0xe, across);
                port_set16(&port, sprite, 0x16, down);
                edi = sprite;
                port_set16(&port, sprite, 0x10, across);
                port_set16(&port, sprite, 0x18, 0xffd8);
                if (line >= port_u32(&port, ebp, -0x44u))
                {
                    uint32_t height;
                    uint32_t top;
                    CALL(0x4ac8f0, sprite, 0x457e40);
                    height = port_u32(&port, ebp, -0x30u);
                    top = (0x1e0 - (height * 3 + 0x28)) >> 1;
                    ecx = port_u32(&port, ebp, -0x40u);
                    top += (height + 0x14) * ecx;
                    port_set8(&port, sprite, 0x52, 9);
                    port_set8(&port, sprite, 0x94, 1);
                    port_set8(&port, sprite, 0x95, 4);
                    port_set8(&port, sprite, 0x93, 1);
                    port_set8(&port, sprite, 0x4e, 0x32);
                    port_set16(&port, sprite, 0x18, (height >> 1) + top);
                }
                CALL(0x4ac910, sprite, 0x458410);
                port_set16(&port, sprite, 0x12, 1);
                port_set16(&port, sprite, 0x1a, 1);
                port_set8(&port, sprite, 0x44, 0);
                CALL(0x4ac7d0, sprite, 0x14);
                ecx = length;
                CALL(0x4b5e70, 0x54671c, sprite);
                port_set32(&port, ebp, -0x3cu, across + 0x23);
                port_set32(&port, ebp, -0x24u, letter + 1);
                edx = letter + 1;
            }
            esi = port_u32(&port, ebp, -0x2cu) + 0x32;
            edi = port_u32(&port, ebp, -0x28u) + 0xc;
            port_set32(&port, ebp, -0x2cu, esi);
            port_set32(&port, ebp, -0x28u, edi);
            port_set32(&port, ebp, -0x48u, port_u32(&port, ebp, -0x48u) + 1);
            line++;
            port_set32(&port, ebp, -0x18u, line);
            ecx = lines;
        } while (line < lines && !port.env.failed);
    }
    ebx = 0;
    port_set32(&port, ebp, -0x50u, 0);
    CALL(0x4ca210, text, 0);
    port_set32(&port, ebp, -0x50u, 0);
#undef CALL
    port.env.chain = port_u32(&port, record, 0);
    return port_return(&port, port_u32(&port, record, 0), entry->edx);
}
