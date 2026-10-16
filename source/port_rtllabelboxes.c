#include "port_rtllabelboxes.h"

/* Framed text labels. */

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

static uint32_t sign16(uint32_t value)
{
    return (uint32_t)(int32_t)(int16_t)value;
}

/* Original 0x45fb00 (five stack arguments, popped: the word for 0x4b3210, its second value, the
 * text value, the font byte and the +0x44 byte; guarded 0x515750): a box from across eax, down dx,
 * ebx wide and ecx high, inset by 2. Its sprite (0x170 bytes, 0x4ca000; 0x4b3100 makes it) is
 * placed (0x4adf20 at 0), sized (0x4b54d0) to the inset box, given 0x4ac7b0 2, +0x110 0 and
 * +0x94 1. A text sprite (0x180 bytes, 0x4b6350) is placed at 0, given the text in the font
 * (0x4b65d0), 0x4ac7b0 2 and the +0x44 byte, and handed to the box (0x4b3210 with the word,
 * the second value and 1). eax the box sprite. */
uint32_t vertrix_port_label_frame_45fb00(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x34
    };
    Port port;
    uint8_t stack[BELOW + 8 + 5 * 4];
    uint32_t ebp = entry->esp - 4;
    uint32_t record = ebp - 0x30;
    uint32_t zeros[5] = {0, 0, 0, 0, 0};
    uint32_t eax;
    uint32_t ebx = 0;
    uint32_t ecx = 0x515750;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->eax + 2;
    uint32_t box;
    uint32_t sprite;
#define CALL(target, a, d) port_call_with(&port, target, a, d, ebx, ecx, esi, edi, ebp)
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 5);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->esi);
    port_set32(&port, ebp, -8u, entry->edi);
    port_set16(&port, ebp, -0x14u, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->ebx);
    port_set32(&port, ebp, -0xcu, entry->ecx);
    port_set32(&port, record, 0, port.env.chain);
    port.env.chain = record;
    port_set32(&port, ebp, -0x2cu, 0x4ec1ec);
    port_set32(&port, ebp, -0x28u, 0x515750);
    port_set32(&port, ebp, -0x24u, 0);
    eax = CALL(0x4ca000, 0x170, 0x4ec1ec);
    port_set16(&port, ebp, -0x14u, port_u32(&port, ebp, -0x14u) + 2);
    ebx = port_u32(&port, ebp, -0x10u) - 4;
    ecx = port_u32(&port, ebp, -0xcu) - 4;
    port_set32(&port, ebp, -0x10u, ebx);
    port_set32(&port, ebp, -0xcu, ecx);
    if (eax != 0)
    {
        esi = 1;
        port_set32(&port, ebp, -0x1cu, eax);
        port_set32(&port, ebp, -0x24u, 1);
        eax = CALL(0x4b3100, eax, 0);
        port_set32(&port, ebp, -0x24u, vertrix_lift_edx);
    }
    box = eax;
    esi = box;
    call_frame(&port, 0x4adf20, box, 0, 0, 0, esi, edi, ebp, zeros, 5);
    ebx = sign16(port_u16(&port, ebp, -0x14u));
    ecx = port_u16(&port, ebp, -0x10u);
    {
        uint32_t args[1] = {port_u16(&port, ebp, -0xcu)};
        call_frame(&port, 0x4b54d0, box, sign16(edi), ebx, ecx, esi, edi, ebp, args, 1);
    }
    port_set32(&port, ebp, -0x18u, box);
    CALL(0x4ac7b0, box, 2);
    port_set8(&port, box, 0x110, 0);
    port_set8(&port, box, 0x94, 1);
    eax = CALL(0x4ca000, 0x180, vertrix_lift_edx);
    if (eax != 0)
    {
        ecx = 3;
        port_set32(&port, ebp, -0x1cu, eax);
        ebx = 0;
        port_set32(&port, ebp, -0x24u, 3);
        eax = CALL(0x4b6350, eax, vertrix_lift_edx);
        port_set32(&port, ebp, -0x24u, 0);
    }
    sprite = eax;
    esi = sprite;
    call_frame(&port, 0x4adf20, sprite, 0, 0, 0, esi, edi, ebp, zeros, 5);
    ebx = (uint32_t)(int32_t)(int8_t)port_u8(&port, ebp, 0x14);
    ecx = 0;
    call_frame(&port, 0x4b65d0, sprite, port_u32(&port, ebp, 0x10), ebx, 0, esi, edi, ebp, zeros,
               3);
    edi = port_u32(&port, ebp, 0xc);
    CALL(0x4ac7b0, sprite, 2);
    port_set8(&port, sprite, 0x44, port_u8(&port, ebp, 0x18));
    {
        uint32_t args[2] = {edi, 1};
        call_frame(&port, 0x4b3210, port_u32(&port, ebp, -0x18u), sprite, port_u16(&port, ebp, 8),
                   0, esi, edi, ebp, args, 2);
    }
#undef CALL
    port.env.chain = port_u32(&port, record, 0);
    return port_return(&port, port_u32(&port, ebp, -0x18u), vertrix_lift_edx);
}
