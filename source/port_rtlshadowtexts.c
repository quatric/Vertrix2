#include "port_rtlshadowtexts.h"

/* Shadowed text placed by its layout. */

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    uint32_t result;
    vertrix_lift_in_esi = esi;
    vertrix_lift_in_edi = edi;
    vertrix_lift_in_ebp = ebp;
    result = lift_call_arguments(&port->env, target, eax, edx, ebx, ecx, stack, count);
    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    return result;
}

/* Original 0x440fc0 (six stack arguments, popped: three words for 0x4408e0, the text, the
 * template sprite and the word for +0x48; guarded 0x514f68): the text in the font dl with its
 * shadow font bl laid out for the owner eax: 0x4408e0 given the font, cx, the three words, the
 * text and the template's +0x44 finds its start, then the row is laid out by 0x440d50 from the
 * start's down word and across word.
 * eax the restored chain. */
uint32_t vertrix_port_text_shadow_place_440fc0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x38
    };
    Port port;
    uint8_t stack[BELOW + 8 + 6 * 4];
    uint32_t ebp = entry->esp - 4;
    uint32_t record = ebp - 0x34;
    uint32_t font = (uint32_t)(int32_t)(int8_t)entry->edx;
    uint32_t owner = entry->eax;
    uint32_t align = (uint32_t)(int32_t)(int16_t)entry->ecx;
    uint32_t text;
    uint32_t sprite;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 6);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->esi);
    port_set32(&port, ebp, -8u, entry->edi);
    port_set8(&port, ebp, -0xcu, entry->ebx);
    port_set32(&port, record, 0, port.env.chain);
    port.env.chain = record;
    port_set32(&port, ebp, -0x28u, 0);
    port_set32(&port, ebp, -0x30u, 0x4ec1ec);
    port_set32(&port, ebp, -0x2cu, 0x514f68);
    port_set32(&port, ebp, -0x18u, align);
    text = port_u32(&port, ebp, 0x14);
    sprite = port_u32(&port, ebp, 0x18);
    {
        uint32_t args[7] = {(uint32_t)(int32_t)(int16_t)port_u32(&port, ebp, 0x10),
                            text,
                            port_u8(&port, sprite, 0x44),
                            ebp - 0x20,
                            ebp - 0x1c,
                            ebp - 0x14,
                            ebp - 0x10};
        call_frame(
            &port, 0x4408e0, font, align, (uint32_t)(int32_t)(int16_t)port_u32(&port, ebp, 8),
            (uint32_t)(int32_t)(int16_t)port_u32(&port, ebp, 0xc), font, owner, ebp, args, 7);
    }
    {
        uint32_t args[4] = {(uint32_t)(int32_t)(int16_t)port_u32(&port, ebp, -0x10u),
                            port_u32(&port, ebp, 0x14), port_u32(&port, ebp, 0x18),
                            (uint32_t)(int32_t)(int16_t)port_u32(&port, ebp, 0x1c)};
        call_frame(
            &port, 0x440d50, owner, font, (uint32_t)(int32_t)(int8_t)port_u8(&port, ebp, -0xcu),
            (uint32_t)(int32_t)(int16_t)port_u32(&port, ebp, -0x14u), font, owner, ebp, args, 4);
    }
    port.env.chain = port_u32(&port, record, 0);
    return port_return(&port, port_u32(&port, record, 0), vertrix_lift_edx);
}
