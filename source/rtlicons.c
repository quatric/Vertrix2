#include "rtlicons.h"

/* The two board icons. */

/* A call (with count stack arguments, nearest first) that leaves its eax and edx in *eax and
 * *edx; the eax. */
static uint32_t icon_call(Port *port, uint32_t *eax, uint32_t *edx, uint32_t target, uint32_t a,
                          uint32_t d, uint32_t ebx, uint32_t ecx, uint32_t esi, uint32_t edi,
                          uint32_t ebp, const uint32_t *stack, unsigned count)
{
    *eax = port_call_registers(port, target, a, d, ebx, ecx, esi, edi, ebp, stack, count);
    *edx = vertrix_lift_edx;
    return *eax;
}

/* Original 0x4731a0 (guarded 0x51628c): the two board icons made, the first with the picture
 * eax and the second with edx: each an actor of 0x15c bytes (0x4ca000, made by 0x4abd70) placed
 * at 0x3b or 0x23d by 0x5a (0x4adf20; the second with 0x448ca0 among its five stack arguments),
 * kind 0x13 or 0x14 (+0), 0x4ac910 with 0, the palette 0x544a34 (0x4ac8d0), its picture
 * (0x4ac710 and +0x58), drawn (0x4ac8a0); random +0x24 (of 0x168), +0x28 (1..2) and +0x30 (of
 * 5) from 0x598d30 (0x4826c0), 0x4ac860 with 10, +0x150 1, +0x64 0, +0x68 0, +0x70 1 or 2,
 * 0x4ac7d0 with 500, +0x124 1 (0x4ae110 with 0), +0x13c 0, +0x140 1, handed 0x45d140 (0x4ac8f0)
 * and added to 0x546730 (0x4b5e70). The first also +0x8e 0, +0x8f 1 and its row +0xa 0x5a; the
 * second +0x144 0. eax the restored chain. */
uint32_t vertrix_port_icons_build_4731a0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x34
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t record = ebp - 0x30;
    uint32_t eax;
    uint32_t edx = 0x4ec1ec;
    uint32_t ebx = 0;
    uint32_t ecx = 0x51628c;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edx;
    uint32_t args[5] = {0, 0, 0, 0, 0};
    uint32_t zero = 0;
#define CALL(target, a, d)                                                                         \
    icon_call(&port, &eax, &edx, target, a, d, ebx, ecx, esi, edi, ebp, NULL, 0)
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->esi);
    port_set32(&port, ebp, -0x10u, entry->edi);
    port_set32(&port, ebp, -0x14u, entry->eax);
    port_set32(&port, record, 0, port.env.chain);
    port.env.chain = record;
    port_set32(&port, ebp, -0x2cu, edx);
    port_set32(&port, ebp, -0x28u, ecx);
    port_set32(&port, ebp, -0x24u, ebx);
    if (CALL(0x4ca000, 0x15c, edx) != 0)
    {
        esi = 1;
        port_set32(&port, ebp, -0x18u, eax);
        port_set32(&port, ebp, -0x24u, esi);
        CALL(0x4abd70, eax, edx);
        port_set32(&port, ebp, -0x24u, ebx);
        esi = eax;
    }
    else
    {
        esi = ebx;
    }
    ecx = 0x5a;
    port_set32(&port, ebp, -0x1cu, ecx);
    ebx = (uint32_t)(int32_t)(int16_t)port_u16(&port, ebp, -0x1cu);
    ecx = 0;
    icon_call(&port, &eax, &edx, 0x4adf20, esi, 0x3b, ebx, ecx, esi, edi, ebp, args, 5);
    port_set32(&port, esi, 0, 0x13);
    CALL(0x4ac910, esi, 0);
    CALL(0x4ac8d0, esi, 0x544a34);
    CALL(0x4ac710, esi, port_u32(&port, ebp, -0x14u));
    CALL(0x4ac8a0, esi, edx);
    port_set8(&port, esi, 0x8e, 0);
    port_set16(&port, esi, 0xa, port_u32(&port, ebp, -0x1cu));
    port_set8(&port, esi, 0x8f, 1);
    port_set16(&port, esi, 0x24, CALL(0x4826c0, 0x598d30, 0x168));
    port_set16(&port, esi, 0x28, CALL(0x4826c0, 0x598d30, 2) + 1);
    port_set16(&port, esi, 0x30, CALL(0x4826c0, 0x598d30, 5));
    CALL(0x4ac860, esi, 0xa);
    port_set32(&port, esi, 0x150, 1);
    ecx = 0;
    port_set32(&port, esi, 0x64, 0);
    port_set32(&port, esi, 0x70, 1);
    port_set32(&port, esi, 0x58, port_u32(&port, ebp, -0x14u));
    port_set32(&port, esi, 0x68, 0);
    CALL(0x4ac7d0, esi, 0x1f4);
    ebx = 0;
    CALL(0x4ac8f0, esi, 0x45d140);
    port_set32(&port, esi, 0x124, 1);
    icon_call(&port, &eax, &edx, 0x4ae110, esi, 0, ebx, ecx, esi, edi, ebp, &zero, 1);
    port_set32(&port, esi, 0x13c, 0);
    port_set32(&port, esi, 0x140, 1);
    CALL(0x4b5e70, 0x546730, esi);
    if (CALL(0x4ca000, 0x15c, edx) != 0)
    {
        ebx = 3;
        port_set32(&port, ebp, -0x18u, eax);
        esi = 0;
        port_set32(&port, ebp, -0x24u, ebx);
        CALL(0x4abd70, eax, edx);
        port_set32(&port, ebp, -0x24u, esi);
    }
    esi = eax;
    port_set32(&port, ebp, -0x1cu, 0x5a);
    ecx = 0;
    ebx = (uint32_t)(int32_t)(int16_t)port_u16(&port, ebp, -0x1cu);
    args[3] = 0x448ca0;
    icon_call(&port, &eax, &edx, 0x4adf20, esi, 0x23d, ebx, ecx, esi, edi, ebp, args, 5);
    port_set32(&port, esi, 0, 0x14);
    CALL(0x4ac910, esi, 0);
    CALL(0x4ac8d0, esi, 0x544a34);
    CALL(0x4ac710, esi, edi);
    CALL(0x4ac8a0, esi, 0x168);
    port_set16(&port, esi, 0x24, CALL(0x4826c0, 0x598d30, edx));
    port_set16(&port, esi, 0x28, CALL(0x4826c0, 0x598d30, 2) + 1);
    port_set16(&port, esi, 0x30, CALL(0x4826c0, 0x598d30, 5));
    CALL(0x4ac860, esi, 0xa);
    port_set32(&port, esi, 0x150, 1);
    ecx = 0;
    port_set32(&port, esi, 0x64, 0);
    ebx = 0;
    port_set32(&port, esi, 0x70, 2);
    port_set32(&port, esi, 0x68, 0);
    port_set32(&port, esi, 0x58, edi);
    CALL(0x4ac7d0, esi, 0x1f4);
    port_set32(&port, esi, 0x124, 1);
    icon_call(&port, &eax, &edx, 0x4ae110, esi, 0, ebx, ecx, esi, edi, ebp, &zero, 1);
    port_set32(&port, esi, 0x13c, 0);
    port_set32(&port, esi, 0x140, 1);
    port_set32(&port, esi, 0x144, 0);
    CALL(0x4ac8f0, esi, 0x45d140);
    CALL(0x4b5e70, 0x546730, esi);
#undef CALL
    eax = port_u32(&port, record, 0);
    port.env.chain = eax;
    return port_return(&port, eax, edx);
}
