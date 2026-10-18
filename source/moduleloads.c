#include "moduleloads.h"

/* The music module's load and start. */

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

/* Original 0x478910: the module of the path eax (guarded 0x516830; 0x5589d4 0, 0x598d60 0,
 * 0x598da8 and 0x5589dc 1). With sound on (0x5589e0) the path's part (0x489640 into a temporary,
 * 0x4ca070 and 0x4ca210) is checked not empty (0x4ccfe0 of 0x50e8b6), the file present
 * (0x45f590) and read (0x4b8187 into 0x5589d8; a failure goes to 0x478c90); the module's +0x20
 * is 0x8000, its ramp built (0x478b70), 0x598d60 the flag edx and the audio opened (0x40ab60) for
 * its channels +0x26 (8 more with the flag). With the flag the eight voices 0x598d88 (and
 * 0x598d68) are cleared and opened (0x40acf0) and 0x482930 follows. The module starts
 * (0x40ec40); if it fails 0x5589d4 is 1, else with the flag the voices close (0x40ad50) and
 * 0x598d60 is cleared, the handles shut (0x40aba0) and the module is freed (0x40ef90). Returns the
 * guard's link; the voice loops count in dl across their calls, as the original's do. */
uint32_t vertrix_port_module_load_478910(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x2c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t path = entry->eax;
    uint32_t flag = entry->edx;
    uint32_t ecx = 1;
    uint32_t eax;
    uint32_t edx;
    uint32_t pushed[1];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->esi);
    port_set32(&port, ebp, -0x10u, entry->edi);
    port_set32(&port, ebp, -0x28u, port.env.chain);
    port_set32(&port, ebp, -0x24u, 0x4ec1ec);
    port_set32(&port, ebp, -0x20u, 0x516830);
    port_set32(&port, ebp, -0x1cu, 0);
    port_set32(&port, 0, 0x5589d4, 0);
    port_set32(&port, 0, 0x598d60, 0);
    port_set32(&port, 0, 0x598da8, 1);
    port_set32(&port, 0, 0x5589dc, 1);
    if (port_u32(&port, 0, 0x5589e0) == 0)
    {
        return port_return(&port, port_u32(&port, ebp, -0x28u), 0x4ec1ec);
    }
    port_call_with(&port, 0x4ca070, ebp - 0x14, 0x4ec1ec, 0, ecx, path, flag, ebp);
    port_set32(&port, ebp, -0x1cu, ecx);
    ecx = ebp - 0x14;
    pushed[0] = 0;
    call_frame(&port, 0x489640, path, 0, 0, ecx, path, flag, ebp, pushed, 1);
    if (port_call_with(&port, 0x4ccfe0, port_u32(&port, ebp, -0x14u), 0x50e8b6, 0, ecx, path, flag,
                       ebp) == 0 ||
        port_call_with(&port, 0x45f590, path, vertrix_lift_edx, 0, ecx, path, flag, ebp) == 0)
    {
        port_call_with(&port, 0x4ca210, ebp - 0x14, 0, 0, ecx, path, flag, ebp);
        return port_return(&port, port_u32(&port, ebp, -0x28u), vertrix_lift_edx);
    }
    eax = port_call_with(&port, 0x4b8187, path, 0x5589d8, 0, ecx, path, flag, ebp);
    if (eax != 0)
    {
        port_call_with(&port, 0x478c90, eax, vertrix_lift_edx, 0, ecx, path, flag, ebp);
        port_call_with(&port, 0x4ca210, ebp - 0x14, 0, 0, ecx, path, flag, ebp);
        return port_return(&port, port_u32(&port, ebp, -0x28u), vertrix_lift_edx);
    }
    eax = port_u32(&port, 0, 0x5589d8);
    port_set16(&port, eax, 0x20, 0x8000);
    port_call_with(&port, 0x478b70, eax, vertrix_lift_edx, 0, ecx, path, flag, ebp);
    port_set32(&port, 0, 0x598d60, flag);
    eax = port_u16(&port, port_u32(&port, 0, 0x5589d8), 0x26);
    if (flag != 0)
    {
        eax += 8;
    }
    port_call_with(&port, 0x40ab60, eax, vertrix_lift_edx, 0, ecx, path, flag, ebp);
    edx = vertrix_lift_edx;
    if (port_u32(&port, 0, 0x598d60) == 1)
    {
        edx &= 0xffffff00u;
        ecx = 0;
        for (;;)
        {
            eax = edx & 0xff;
            if (eax >= 8)
            {
                break;
            }
            port_set32(&port, eax * 4, 0x598d68, 0);
            port_set32(&port, eax * 4, 0x598d88, 0);
            edx = (edx & 0xffffff00u) | ((edx + 1) & 0xff);
            port_call_with(&port, 0x40acf0, eax * 4 + 0x598d88, edx, 0, 0, path, flag, ebp);
            edx = vertrix_lift_edx;
        }
        port_call_with(&port, 0x482930, eax, edx, 0, 0, path, flag, ebp);
    }
    eax = port_call_with(&port, 0x40ec40, port_u32(&port, 0, 0x5589d8), vertrix_lift_edx, 0, ecx,
                         path, flag, ebp);
    if (eax == 0)
    {
        port_set32(&port, ebp, -0x1cu, 0);
        port_set32(&port, 0, 0x5589d4, 1);
        port_call_with(&port, 0x4ca210, ebp - 0x14, 0, 1, ecx, path, 0, ebp);
        port_set32(&port, ebp, -0x1cu, 0);
        return port_return(&port, port_u32(&port, ebp, -0x28u), vertrix_lift_edx);
    }
    edx = vertrix_lift_edx;
    if (port_u32(&port, 0, 0x598d60) == 1)
    {
        edx &= 0xffffff00u;
        for (;;)
        {
            eax = edx & 0xff;
            if (eax >= 8)
            {
                break;
            }
            port_call_with(&port, 0x40ad50, port_u32(&port, 0, eax * 4 + 0x598d88), edx, 0, ecx,
                           path, flag, ebp);
            edx = (vertrix_lift_edx & 0xffffff00u) | ((vertrix_lift_edx + 1) & 0xff);
        }
        edx = 0;
        port_set32(&port, 0, 0x598d60, 0);
    }
    port_call_with(&port, 0x40aba0, eax, edx, 0, ecx, path, flag, ebp);
    port_call_with(&port, 0x40ef90, port_u32(&port, 0, 0x5589d8), vertrix_lift_edx, 0, ecx, path,
                   flag, ebp);
    port_call_with(&port, 0x4ca210, ebp - 0x14, 0, 0, ecx, path, flag, ebp);
    return port_return(&port, port_u32(&port, ebp, -0x28u), vertrix_lift_edx);
}
