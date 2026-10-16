#include "port_rtlshots.h"

/* Screenshots. */

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

/* Original 0x4192a0 (guarded 0x513f94): with the word 0x5b9ca6 at 4, the screen 0x558c7c is
 * saved (0x473e60) to the first name not taken (0x4895e0): 0x50d7d4 printed (0x4cdfb0) with 0,
 * then 0x50d7e0 with 1, 2, ... into a temporary (0x4ca070); the player's (0x4f81a8) sounds from
 * 0x533164 are played on channels 0 and 4 (0x482a60 with 0x532b9c), the screen shown (0x472c10)
 * and the temporary released (0x4ca210). eax the restored chain, edx kept. */
uint32_t vertrix_port_screen_shot_save_4192a0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x30
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t record = ebp - 0x2c;
    uint32_t text = ebp - 0x18;
    uint32_t edx;
    uint32_t ebx = 0;
    uint32_t ecx = 0x513f94;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
#define CALL(target, a, d) port_call_with(&port, target, a, d, ebx, ecx, esi, edi, ebp)
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    port_set32(&port, record, 0, port.env.chain);
    port.env.chain = record;
    port_set32(&port, ebp, -0x28u, 0x4ec1ec);
    port_set32(&port, ebp, -0x24u, 0x513f94);
    port_set32(&port, ebp, -0x20u, 0);
    edx = (0x4ec1ecu & 0xffff0000u) | port_u16(&port, 0, 0x5b9ca6);
    if (port_u16(&port, 0, 0x5b9ca6) != 4)
    {
        port.env.chain = port_u32(&port, record, 0);
        return port_return(&port, port_u32(&port, record, 0), entry->edx);
    }
    CALL(0x4ca070, text, edx);
    esi = 1;
    port_set32(&port, ebp, -0x20u, 1);
    {
        uint32_t args[3] = {text, 0x50d7d4, 0};
        call_frame(&port, 0x4cdfb0, text, 0, ebx, ecx, esi, edi, ebp, args, 3);
    }
    while (CALL(0x4895e0, port_u32(&port, text, 0), vertrix_lift_edx) == 1 && !port.env.failed)
    {
        uint32_t args[3] = {text, 0x50d7e0, vertrix_lift_edx + 1};
        call_frame(&port, 0x4cdfb0, text, args[2], ebx, ecx, esi, edi, ebp, args, 3);
    }
    CALL(0x473e60, port_u32(&port, text, 0), port_u32(&port, 0, 0x558c7c));
    ebx = port_u32(&port, 0, 0x532b9c);
    CALL(0x482a60, 0, port_u32(&port, port_u32(&port, 0, 0x4f81a8) * 4, 0x533164));
    ebx = port_u32(&port, 0, 0x532b9c);
    CALL(0x482a60, 4, port_u32(&port, port_u32(&port, 0, 0x4f81a8) * 4, 0x533164));
    edi = 0;
    CALL(0x472c10, port_u32(&port, 0, 0x558c7c), vertrix_lift_edx);
    port_set32(&port, ebp, -0x20u, 0);
    CALL(0x4ca210, text, 0);
    port_set32(&port, ebp, -0x20u, 0);
#undef CALL
    port.env.chain = port_u32(&port, record, 0);
    return port_return(&port, port_u32(&port, record, 0), entry->edx);
}
