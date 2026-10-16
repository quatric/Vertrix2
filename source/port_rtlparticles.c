#include "port_rtlparticles.h"

/* Board particles and sparks set up. */

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

/* Original 0x43e4d0: the particles of the board eax set up from the mask picture named edx
 * (0x4816f0 with 0): with the mask, up to 30 of its set points (0x478f10) kept as places
 * (+0x870/+0x8e8 on) with the count at +0x964, and three sparks (+0x864 on; 0x15c bytes,
 * 0x4ca000; 0x4abd70 makes them) placed (0x4adf20) at 0, given 0x544c48 (0x4ac8d0), frame 0
 * (0x4ac710), 0x4ac8a0 with 1, shown (0x4ac7b0), a speed of 2 to 11 (0x4826c0 of 0x598d30,
 * 0x4ac470), +0x64 30, +0x70 180, +0x58 0, +0x60 1, +0x5c a random angle (0x482750), +0x93 1,
 * +0x4e 0, handed 0x457330 and +0x95 4, the mask released (0x478d80); then 450 particles
 * (+0x15c on) made, placed, set up by 0x43e740 with a random +0x58 below 200, and one more at
 * +0x870 with +0x94 1 and +0x95 4 set up by 0x43e840; +0x968 0. eax the board. */
uint32_t vertrix_port_board_particles_setup_43e4d0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x30
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t zeros[5] = {0, 0, 0, 0, 0};
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t mask;
#define CALL(target, a, d) port_call_with(&port, target, a, d, ebx, ecx, esi, edi, ebp)
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->esi);
    port_set32(&port, ebp, -0x10u, entry->edi);
    port_set32(&port, ebp, -0x18u, board);
    mask = CALL(0x4816f0, entry->edx, 0);
    edx = vertrix_lift_edx;
    port_set32(&port, ebp, -0x14u, mask);
    if (mask != 0)
    {
        uint32_t width = port_u32(&port, mask, 4);
        uint32_t height = port_u32(&port, mask, 8);
        port_set32(&port, ebp, -0x1cu, width);
        port_set32(&port, ebp, -0x28u, height);
        port_set32(&port, ebp, -0x2cu, 0);
        edi = 0;
        ecx = width;
        edx = 0;
        if (width != 0)
        {
            do
            {
                esi = height;
                ecx = 0;
                if (height != 0)
                {
                    esi = port_u32(&port, ebp, -0x2cu) * 4 + board;
                    do
                    {
                        ebx = ecx;
                        eax = CALL(0x478f10, mask, edi);
                        if (eax != 0 && port_u32(&port, ebp, -0x2cu) < 0x1e)
                        {
                            eax = port_u32(&port, ebp, -0x2cu);
                            esi += 4;
                            port_set32(&port, esi, 0x870, edi);
                            port_set32(&port, esi, 0x8e8, ecx);
                            port_set32(&port, ebp, -0x2cu, eax + 1);
                        }
                        edx = height;
                        ecx++;
                    } while (ecx < height && !port.env.failed);
                }
                ebx = width;
                edi++;
            } while (edi < width && !port.env.failed);
        }
        edx = board;
        edi = board;
        port_set32(&port, board, 0x964, port_u32(&port, ebp, -0x2cu));
        port_set32(&port, ebp, -0x24u, board + 0xc);
        do
        {
            uint32_t spark;
            eax = CALL(0x4ca000, 0x15c, edx);
            if (eax != 0)
            {
                eax = CALL(0x4abd70, eax, vertrix_lift_edx);
            }
            spark = eax;
            esi = spark;
            ecx = 0;
            ebx = 0;
            port_set32(&port, edi, 0x864, spark);
            call_frame(&port, 0x4adf20, spark, 0, 0, 0, esi, edi, ebp, zeros, 5);
            port_set16(&port, spark, 0xe, 0);
            port_set16(&port, spark, 0x16, 0);
            CALL(0x4ac8d0, spark, 0x544c48);
            CALL(0x4ac710, spark, 0);
            CALL(0x4ac8a0, spark, 1);
            CALL(0x4ac7b0, spark, vertrix_lift_edx);
            eax = CALL(0x4826c0, 0x598d30, 0xa);
            edi += 4;
            CALL(0x4ac470, spark, (eax & 0xffff) + 2);
            port_set32(&port, spark, 0x64, 0x1e);
            port_set32(&port, spark, 0x70, 0xb4);
            port_set32(&port, spark, 0x58, 0);
            ebx = port_u16(&port, spark, 0x70);
            port_set32(&port, spark, 0x60, 1);
            eax = CALL(0x482750, 0x598d30, port_u16(&port, spark, 0x64));
            port_set8(&port, spark, 0x93, 1);
            port_set32(&port, spark, 0x5c, eax);
            port_set8(&port, spark, 0x4e, 0);
            CALL(0x4ac8f0, spark, 0x457330);
            edx = vertrix_lift_edx;
            port_set8(&port, spark, 0x95, 4);
        } while (edi != port_u32(&port, ebp, -0x24u) && !port.env.failed);
        CALL(0x478d80, mask, edx);
        edx = vertrix_lift_edx;
    }
    edi = board;
    port_set32(&port, ebp, -0x20u, board + 0x708);
    do
    {
        uint32_t particle;
        eax = CALL(0x4ca000, 0x15c, edx);
        if (eax != 0)
        {
            eax = CALL(0x4abd70, eax, vertrix_lift_edx);
        }
        particle = eax;
        esi = particle;
        ecx = 0;
        ebx = 0;
        call_frame(&port, 0x4adf20, particle, 0, 0, 0, esi, edi, ebp, zeros, 5);
        CALL(0x43e740, board, particle);
        eax = CALL(0x4826c0, 0x598d30, 0xc8);
        edx = vertrix_lift_edx;
        edi += 4;
        port_set32(&port, particle, 0x58, eax & 0xffff);
        ecx = port_u32(&port, ebp, -0x20u);
        port_set32(&port, edi, 0x158, particle);
    } while (edi != ecx && !port.env.failed);
    edi = board;
    eax = CALL(0x4ca000, 0x15c, edx);
    if (eax != 0)
    {
        eax = CALL(0x4abd70, eax, vertrix_lift_edx);
    }
    esi = eax;
    ecx = 0;
    ebx = 0;
    call_frame(&port, 0x4adf20, esi, 0, 0, 0, esi, edi, ebp, zeros, 5);
    port_set8(&port, esi, 0x94, 1);
    port_set8(&port, esi, 0x95, 4);
    CALL(0x43e840, board, esi);
    port_set32(&port, edi, 0x870, esi);
    port_set32(&port, board, 0x968, 0);
#undef CALL
    return port_return(&port, board, vertrix_lift_edx);
}
