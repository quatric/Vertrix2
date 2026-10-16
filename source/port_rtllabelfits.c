#include "port_rtllabelfits.h"

/* Number labels laid out in their box. */

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

/* Original 0x43d4d0: the number label eax (guarded 0x514d1c) refreshed (0x4ae150) and its text
 * made in a temporary (0x4ca070): +0x180 printed (0x4cdfb0) by 0x50e0ea, or with +0x184 1 by
 * 0x50e0e4 into a second temporary, the first starting 0x50e0e7 (0x4ca370) and padded with
 * 0x50e0e8 (0x4ca600) while +0x188 exceeds the number's length, then the number appended
 * (0x4ca650) and the second released (0x4ca210). The text is stored at +0x15c (0x4ca310); unless
 * it equals 0x50e0ed (0x4ccfe0) its start across and down found by 0x4408e0 from the font +0x160,
 * the box words +0x162..+0x168, the text and +0x44 are kept at +0xf4/+0xf8 and their words at
 * +0xe/+0x16. The temporary released. eax the restored chain, edx kept. */
uint32_t vertrix_port_number_label_fit_43d4d0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x44
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t record = ebp - 0x40;
    uint32_t label = entry->eax;
    uint32_t ebx = 0;
    uint32_t ecx = 0x514d1c;
    uint32_t edi = entry->edi;
#define CALL(target, a, d) port_call_with(&port, target, a, d, ebx, ecx, label, edi, ebp)
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    port_set32(&port, record, 0, port.env.chain);
    port.env.chain = record;
    port_set32(&port, ebp, -0x3cu, 0x4ec1ec);
    port_set32(&port, ebp, -0x38u, 0x514d1c);
    port_set32(&port, ebp, -0x34u, 0);
    CALL(0x4ae150, label, 0x4ec1ec);
    edi = 1;
    CALL(0x4ca070, ebp - 0x2c, vertrix_lift_edx);
    port_set32(&port, ebp, -0x34u, 1);
    if (port_u32(&port, label, 0x184) != 1)
    {
        uint32_t args[3] = {ebp - 0x2c, 0x50e0ea, port_u32(&port, label, 0x180)};
        call_frame(&port, 0x4cdfb0, ebp - 0x2c, args[2], ebx, ecx, label, edi, ebp, args, 3);
    }
    else
    {
        uint32_t length;
        ecx = 2;
        CALL(0x4ca070, ebp - 0x20, vertrix_lift_edx);
        port_set32(&port, ebp, -0x34u, 2);
        ebx = port_u32(&port, label, 0x180);
        {
            uint32_t args[3] = {ebp - 0x20, 0x50e0e4, ebx};
            call_frame(&port, 0x4cdfb0, ebp - 0x20, vertrix_lift_edx, ebx, ecx, label, edi, ebp,
                       args, 3);
        }
        CALL(0x4ca370, ebp - 0x2c, 0x50e0e7);
        length = port_u32(&port, port_u32(&port, ebp, -0x20u) - 0xc, 4);
        ecx = port_u32(&port, label, 0x188);
        ebx = length;
        while (ecx > ebx && !port.env.failed)
        {
            ecx--;
            CALL(0x4ca600, ebp - 0x2c, 0x50e0e8);
        }
        CALL(0x4ca650, ebp - 0x2c, ebp - 0x20);
        port_set32(&port, ebp, -0x34u, 1);
        CALL(0x4ca210, ebp - 0x20, 0);
        port_set32(&port, ebp, -0x34u, 1);
    }
    ecx = label + 0x15c;
    CALL(0x4ca310, ecx, ebp - 0x2c);
    if (CALL(0x4ccfe0, port_u32(&port, ecx, 0), 0x50e0ed) != 0)
    {
        uint32_t args[7] = {sign16(port_u32(&port, label, 0x166) >> 16),
                            port_u32(&port, ecx, 0),
                            port_u8(&port, label, 0x44),
                            ebp - 0x28,
                            ebp - 0x24,
                            ebp - 0x1c,
                            ebp - 0x18};
        ebx = sign16(port_u32(&port, label, 0x162) >> 16);
        call_frame(&port, 0x4408e0, (uint32_t)(int32_t)(int8_t)port_u8(&port, label, 0x160),
                   sign16(port_u32(&port, label, 0x160) >> 16), ebx,
                   sign16(port_u32(&port, label, 0x164) >> 16), label, edi, ebp, args, 7);
        port_set16(&port, label, 0xe, port_u32(&port, ebp, -0x1cu));
        port_set16(&port, label, 0x16, port_u32(&port, ebp, -0x18u));
        port_set32(&port, label, 0xf4, port_u32(&port, ebp, -0x28u));
        port_set32(&port, label, 0xf8, port_u32(&port, ebp, -0x24u));
        ecx = 0;
        port_set32(&port, ebp, -0x34u, 0);
        CALL(0x4ca210, ebp - 0x2c, 0);
        port_set32(&port, ebp, -0x34u, 0);
    }
    else
    {
        CALL(0x4ca210, ebp - 0x2c, 0);
    }
#undef CALL
    port.env.chain = port_u32(&port, record, 0);
    return port_return(&port, port_u32(&port, record, 0), entry->edx);
}
