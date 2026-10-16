#include "port_rtlplayers.h"

/* Player objects constructed. */

/* Original 0x43a6f0 (guarded 0x514bd0): the player object eax made (0x4abd70), its +0x19c part
 * made (0x481f30), its class +0x158 0x514cb4; its board (0xd00 bytes, 0x42e870) at +0x15c, its
 * AI (0x218 bytes, 0x425e20) at +0x450, its list (0x14 bytes, 0x487920) at +0x468 and its record
 * (0x20 bytes, 0x425d30) at +0x46c, each made only when allocated (0x4ca000); its state cleared
 * (+0x180 0xc, +0x4c5 1, +0x4dc 2, +0x474 1, the rest 0) and +0x17c from 0x532bc0. The object
 * carried in edx through the calls. eax the object, edx kept. */
uint32_t vertrix_port_player_construct_43a6f0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x3c
    };
    static const uint16_t zero32[] = {0x170, 0x174, 0x178, 0x18c, 0x488, 0x4c8, 0x194, 0x198,
                                      0x3b0, 0x3b4, 0x4d0, 0x4d4, 0x4d8, 0x184, 0x4e0, 0x3f4,
                                      0x44c, 0x454, 0x464, 0x4e4, 0x3f8, 0x4e8, 0x3ac};
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t record = ebp - 0x38;
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx = 0x514bd0;
    uint32_t ecx = 0x4ec1ec;
    uint32_t esi = 0;
    uint32_t edi = 1;
    unsigned index;
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
    port_set32(&port, ebp, -0x34u, 0x4ec1ec);
    port_set32(&port, ebp, -0x30u, 0x514bd0);
    port_set32(&port, ebp, -0x2cu, 0);
    port_set8(&port, ebp, -0x20u, 0);
    port_set32(&port, ebp, -0x24u, entry->eax);
    eax = CALL(0x4abd70, entry->eax, entry->eax);
    port_set32(&port, ebp, -0x2cu, 1);
    eax = CALL(0x481f30, eax + 0x19c, vertrix_lift_edx);
    edx = eax - 0x19c;
    port_set32(&port, ebp, -0x2cu, 2);
    port_set32(&port, edx, 0x158, 0x514cb4);
    eax = CALL(0x4ca000, 0xd00, edx);
    edx = vertrix_lift_edx;
    if (eax != 0)
    {
        ecx = 3;
        ebx = 2;
        port_set32(&port, ebp, -0x18u, eax);
        port_set32(&port, ebp, -0x2cu, 3);
        eax = CALL(0x42e870, eax, edx);
        edx = vertrix_lift_edx;
        port_set32(&port, ebp, -0x2cu, 2);
    }
    port_set32(&port, edx, 0x15c, eax);
    eax = CALL(0x4ca000, 0x218, edx);
    edx = vertrix_lift_edx;
    if (eax != 0)
    {
        esi = 5;
        edi = 2;
        port_set32(&port, ebp, -0x18u, eax);
        port_set32(&port, ebp, -0x2cu, 5);
        eax = CALL(0x425e20, eax, edx);
        edx = vertrix_lift_edx;
        port_set32(&port, ebp, -0x2cu, 2);
    }
    port_set32(&port, edx, 0x450, eax);
    eax = CALL(0x4ca000, 0x14, edx);
    edx = vertrix_lift_edx;
    if (eax != 0)
    {
        ecx = 7;
        ebx = 2;
        port_set32(&port, ebp, -0x18u, eax);
        port_set32(&port, ebp, -0x2cu, 7);
        eax = CALL(0x487920, eax, edx);
        edx = vertrix_lift_edx;
        port_set32(&port, ebp, -0x2cu, 2);
    }
    port_set32(&port, edx, 0x468, eax);
    eax = CALL(0x4ca000, 0x20, edx);
    edx = vertrix_lift_edx;
    if (eax != 0)
    {
        esi = 9;
        edi = 2;
        port_set32(&port, ebp, -0x18u, eax);
        port_set32(&port, ebp, -0x2cu, 9);
        eax = CALL(0x425d30, eax, edx);
        edx = vertrix_lift_edx;
        port_set32(&port, ebp, -0x2cu, 2);
    }
#undef CALL
    port_set8(&port, edx, 0x190, 0);
    port_set32(&port, edx, 0x180, 0xc);
    port_set8(&port, edx, 0x4c4, 0);
    port_set8(&port, edx, 0x4c5, 1);
    port_set8(&port, edx, 0x4cc, 0);
    port_set8(&port, edx, 0x4cd, 0);
    port_set8(&port, edx, 0x4dc, 2);
    for (index = 0; index < sizeof zero32 / sizeof zero32[0]; index++)
    {
        port_set32(&port, edx, zero32[index], 0);
    }
    port_set32(&port, edx, 0x474, 1);
    port_set32(&port, edx, 0x46c, eax);
    port_set32(&port, edx, 0x17c, port_u32(&port, 0, 0x532bc0));
    port.env.chain = port_u32(&port, record, 0);
    return port_return(&port, edx, entry->edx);
}
