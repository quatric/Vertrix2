#include "rtlshadows.h"

/* Shadowed text laid out as sprites. */

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

/* Original 0x440d50 (four stack arguments, popped: the down place, the text, the template
 * sprite and the word for +0x48; guarded 0x514f5c): each character of the text laid out for the
 * owner eax from across ecx in the font dl with its shadow font bl. A space is a sprite (0x15c
 * bytes, 0x4ca000; 0x4abd70 makes it) placed (0x4adf20) with the template's +0x44/+0x91 and the
 * font's space size (0x541988 + 0x20c per font) at +0xf4/+0xf8, measured (0x4b14c0) to advance
 * by its width plus 1, and freed (its class +0 with 2). Any other with both glyphs (0x43f420) is
 * a sprite placed with the first glyph, +0x8f 1, +0x95 4, +0x93 1, the template's +0x8e, +0x44,
 * +0x91 and clip +0xa8..+0xae, +0x48 the word; measured, given the shadow glyph (0x4ac950) and
 * measured again, handed the owner (its class +8) advancing by its width plus 1, and freed. eax
 * the restored chain. */
uint32_t vertrix_port_text_shadow_row_440d50(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x4c
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4 * 4];
    uint32_t ebp = entry->esp - 4;
    uint32_t record = ebp - 0x48;
    uint32_t zeros[5] = {0, 0, 0, 0, 0};
    uint32_t eax;
    uint32_t edx = 0x4ec1ec;
    uint32_t ebx = 0;
    uint32_t ecx = 0x514f5c;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->ecx;
    uint32_t text;
    uint32_t sprite;
    uint32_t glyph;
    uint32_t font;
#define CALL(target, a, d) port_call_with(&port, target, a, d, ebx, ecx, esi, edi, ebp)
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 4);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->esi);
    port_set32(&port, ebp, -8u, entry->edi);
    port_set32(&port, ebp, -0x34u, entry->eax);
    port_set8(&port, ebp, -0x10u, entry->edx);
    port_set8(&port, ebp, -0xcu, entry->ebx);
    port_set32(&port, record, 0, port.env.chain);
    port.env.chain = record;
    port_set32(&port, ebp, -0x44u, 0x4ec1ec);
    port_set32(&port, ebp, -0x40u, 0x514f5c);
    port_set32(&port, ebp, -0x3cu, 0);
    text = port_u32(&port, ebp, 0xc);
    if (port_u8(&port, text, 0) != 0)
    {
        do
        {
            uint32_t tmpl = port_u32(&port, ebp, 0x10);
            text = port_u32(&port, ebp, 0xc);
            ebx = (ebx & 0xffffff00u) | port_u8(&port, text, 0);
            if ((ebx & 0xff) == 0x20)
            {
                eax = CALL(0x4ca000, 0x15c, edx);
                if (eax != 0)
                {
                    eax = CALL(0x4abd70, eax, vertrix_lift_edx);
                }
                esi = eax;
                ecx = 0;
                ebx = 0;
                call_frame(&port, 0x4adf20, esi, 0, 0, 0, esi, edi, ebp, zeros, 5);
                tmpl = port_u32(&port, ebp, 0x10);
                port_set8(&port, esi, 0x44, port_u8(&port, tmpl, 0x44));
                port_set8(&port, esi, 0x91, port_u8(&port, tmpl, 0x91));
                font = (uint32_t)((int32_t)port_u32(&port, ebp, -0x13u) >> 24) * 0x20c + 0x541988;
                port_set32(&port, esi, 0xf4, port_u32(&port, font, 0));
                ebx = ebp - 0x2c;
                port_set32(&port, esi, 0xf8, port_u32(&port, font, 4));
                port_set32(&port, ebp, -0x14u, esi);
                eax = CALL(0x4b14c0, esi, ebp - 0x30);
                edx = vertrix_lift_edx;
                if (eax != 0)
                {
                    edi += port_u32(&port, ebp, -0x30u);
                    edi++;
                }
                eax = port_u32(&port, ebp, -0x14u);
                if (eax != 0)
                {
                    ebx = port_u32(&port, eax, 0x158);
                    CALL(port_u32(&port, ebx, 0), eax, 2);
                    edx = vertrix_lift_edx;
                }
            }
            else
            {
                font = (uint32_t)((int32_t)port_u32(&port, ebp, -0x13u) >> 24);
                esi = CALL(0x43f420, font, ebx & 0xff);
                ebx = esi;
                font = (uint32_t)((int32_t)port_u32(&port, ebp, -0xfu) >> 24);
                glyph = CALL(0x43f420, font, port_u8(&port, text, 0));
                edx = vertrix_lift_edx;
                port_set32(&port, ebp, -0x1cu, glyph);
                if (esi != 0 && glyph != 0)
                {
                    eax = CALL(0x4ca000, 0x15c, vertrix_lift_edx);
                    if (eax != 0)
                    {
                        port_set32(&port, ebp, -0x20u, eax);
                        ecx = 0;
                        port_set32(&port, ebp, -0x3cu, 1);
                        eax = CALL(0x4abd70, eax, 1);
                        port_set32(&port, ebp, -0x3cu, ecx);
                    }
                    esi = eax;
                    zeros[2] = ebx;
                    ecx = 0;
                    ebx = (uint32_t)((int32_t)port_u32(&port, ebp, 6) >> 16);
                    call_frame(&port, 0x4adf20, esi, (uint32_t)(int32_t)(int16_t)edi, ebx, ecx, esi,
                               edi, ebp, zeros, 5);
                    zeros[2] = 0;
                    tmpl = port_u32(&port, ebp, 0x10);
                    port_set8(&port, esi, 0x8f, 1);
                    port_set8(&port, esi, 0x95, 4);
                    port_set8(&port, esi, 0x8e, port_u8(&port, tmpl, 0x8e));
                    port_set16(&port, esi, 0x48, port_u32(&port, ebp, 0x14));
                    port_set8(&port, esi, 0x93, 1);
                    port_set8(&port, esi, 0x44, port_u8(&port, tmpl, 0x44));
                    port_set8(&port, esi, 0x91, port_u8(&port, tmpl, 0x91));
                    port_set16(&port, esi, 0xa8, port_u16(&port, tmpl, 0xa8));
                    port_set16(&port, esi, 0xaa, port_u16(&port, tmpl, 0xaa));
                    port_set16(&port, esi, 0xac, port_u16(&port, tmpl, 0xac));
                    ebx = ebp - 0x2c;
                    port_set16(&port, esi, 0xae, port_u16(&port, tmpl, 0xae));
                    port_set32(&port, ebp, -0x18u, esi);
                    eax = CALL(0x4b14c0, esi, ebp - 0x30);
                    if (eax != 0)
                    {
                        ebx = ebp - 0x24;
                        CALL(0x4ac950, esi, port_u32(&port, ebp, -0x1cu));
                        eax = CALL(0x4b14c0, esi, ebp - 0x28);
                        if (eax != 0)
                        {
                            ebx = port_u32(&port, esi, 0x158);
                            CALL(port_u32(&port, ebx, 8), esi, port_u32(&port, ebp, -0x34u));
                            edi += port_u32(&port, ebp, -0x30u);
                            edi++;
                        }
                    }
                    ebx = port_u32(&port, ebp, -0x18u);
                    if (ebx != 0)
                    {
                        sprite = ebx;
                        ebx = port_u32(&port, sprite, 0x158);
                        CALL(port_u32(&port, ebx, 0), sprite, 2);
                    }
                    edx = vertrix_lift_edx;
                    esi = 0;
                    port_set32(&port, ebp, -0x3cu, 0);
                }
            }
            esi = port_u32(&port, ebp, 0xc) + 1;
            edx = (edx & 0xffff00ffu) | (port_u8(&port, esi, 0) << 8);
            port_set32(&port, ebp, 0xc, esi);
        } while (port_u8(&port, esi, 0) != 0 && !port.env.failed);
    }
#undef CALL
    eax = port_u32(&port, record, 0);
    port.env.chain = eax;
    return port_return(&port, eax, edx);
}
