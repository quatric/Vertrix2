#include "coefreads.h"

/* The image decoder's coefficient input. */

/* Original 0x4ba220: one input row of the decoder eax (coefficient controller +0x1ac) into its
 * whole-image arrays: each scan component (+0x148 of them, +0x14c on) has its rows got by the
 * memory manager +4's method +0x20 (the array +0x48 by the index +4, from the input row +0x94
 * times the vertical factor +0xc, writable) into a frame list; then for each MCU row from +0x18
 * below +0x1c and each MCU from +0x14 below +0x15c the block pointers (the MCU width +0x34 by
 * height +0x38, 0x80 bytes a block) fill the controller's +0x20 list and the entropy decoder
 * +0x1bc's method +4 takes them. A refusal keeps the place (+0x18, +0x14) and gives 0. After the
 * last row, the next row (+0x94) is 3 (0x4b9d70 restarts the row) or, past +0x140, 4 (the input
 * controller +0x1b4's method +0xc). The frame is the original's: a list longer than four runs
 * over its locals and saved registers, edx comes back from its slot. */
uint32_t vertrix_port_coefficient_consume_4ba220(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x64
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t eax = entry->eax;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t edx;
    uint32_t esi;
    uint32_t edi = entry->edi;
    uint32_t args[1] = {1};
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    port_set32(&port, ebp, -0x38u, eax);
    port_set32(&port, ebp, -0x1cu, port_u32(&port, eax, 0x1ac));
    eax = port_u32(&port, ebp, -0x38u);
    edx = port_u32(&port, eax, 0x148);
    esi = 0;
    if ((int32_t)edx > 0)
    {
        port_set32(&port, ebp, -0x4cu, eax);
        do
        {
            port_set32(&port, ebp, -0x50u, esi * 4);
            eax = port_u32(&port, port_u32(&port, ebp, -0x4cu), 0x14c);
            ebx = port_u32(&port, port_u32(&port, ebp, -0x38u), 0x94);
            ecx = port_u32(&port, eax, 0xc);
            ebx *= ecx;
            edx = (port_u32(&port, eax, 4) << 2) + port_u32(&port, ebp, -0x1cu);
            edi = port_u32(&port, port_u32(&port, ebp, -0x38u), 4);
            eax = port_u32(&port, ebp, -0x38u);
            edx = port_u32(&port, edx, 0x48);
            eax = port_call_registers(&port, port_u32(&port, edi, 0x20), eax, edx, ebx, ecx, esi,
                                      edi, ebp, args, 1);
            edx = port_u32(&port, ebp, -0x50u);
            port_set32(&port, edx + ebp, -0x60u, eax);
            edx = port_u32(&port, ebp, -0x4cu);
            eax = port_u32(&port, ebp, -0x38u);
            esi++;
            edx += 4;
            ecx = port_u32(&port, eax, 0x148);
            port_set32(&port, ebp, -0x4cu, edx);
        } while ((int32_t)esi < (int32_t)ecx && !port.env.failed);
    }
    eax = port_u32(&port, ebp, -0x1cu);
    edx = eax;
    eax = port_u32(&port, eax, 0x18);
    ebx = port_u32(&port, edx, 0x1c);
    port_set32(&port, ebp, -0x48u, eax);
    if ((int32_t)eax < (int32_t)ebx)
    {
        port_set32(&port, ebp, -0x44u, edx + 0x20);
        port_set32(&port, ebp, -0x40u, port_u32(&port, ebp, -0x48u) << 2);
        do
        {
            eax = port_u32(&port, port_u32(&port, ebp, -0x1cu), 0x14);
            edx = port_u32(&port, ebp, -0x38u);
            edi = port_u32(&port, edx, 0x15c);
            port_set32(&port, ebp, -0x3cu, eax);
            if (eax < edi)
            {
                do
                {
                    eax = port_u32(&port, ebp, -0x38u);
                    ebx = 0;
                    edi = port_u32(&port, eax, 0x148);
                    port_set32(&port, ebp, -0x30u, 0);
                    if ((int32_t)edi > 0)
                    {
                        port_set32(&port, ebp, -0x34u, eax);
                        do
                        {
                            edx = port_u32(&port, port_u32(&port, ebp, -0x34u), 0x14c);
                            port_set32(&port, ebp, -0x18u, edx);
                            ecx = port_u32(&port, ebp, -0x18u);
                            edx = port_u32(&port, ebp, -0x3cu) * port_u32(&port, ecx, 0x34);
                            eax = port_u32(&port, ebp, -0x30u) << 2;
                            edi = 0;
                            esi = port_u32(&port, ecx, 0x38);
                            port_set32(&port, ebp, -0x24u, 0);
                            if ((int32_t)esi > 0)
                            {
                                port_set32(&port, ebp, -0x2cu, eax);
                                port_set32(&port, ebp, -0x28u, edx << 7);
                                port_set32(&port, ebp, -0x20u, port_u32(&port, ebp, -0x40u));
                                do
                                {
                                    eax =
                                        port_u32(&port, port_u32(&port, ebp, -0x2cu) + ebp, -0x60u);
                                    esi = port_u32(&port, ebp, -0x20u);
                                    edi = port_u32(&port, ebp, -0x28u);
                                    eax += esi;
                                    ecx = port_u32(&port, ebp, -0x18u);
                                    edx = 0;
                                    eax = port_u32(&port, eax, 0);
                                    esi = port_u32(&port, ecx, 0x34);
                                    eax += edi;
                                    if ((int32_t)esi > 0)
                                    {
                                        ecx = ebx * 4;
                                        do
                                        {
                                            edi = port_u32(&port, ebp, -0x1cu);
                                            port_set32(&port, ebp, -0x50u, ecx);
                                            esi = eax;
                                            edi += port_u32(&port, ebp, -0x50u);
                                            ebx++;
                                            edx++;
                                            port_set32(&port, edi, 0x20, esi);
                                            esi = port_u32(&port, ebp, -0x18u);
                                            eax += 0x80;
                                            edi = port_u32(&port, esi, 0x34);
                                            ecx += 4;
                                        } while ((int32_t)edx < (int32_t)edi && !port.env.failed);
                                    }
                                    edi = port_u32(&port, ebp, -0x20u) + 4;
                                    eax = port_u32(&port, ebp, -0x24u) + 1;
                                    edx = port_u32(&port, ebp, -0x18u);
                                    ecx = port_u32(&port, edx, 0x38);
                                    port_set32(&port, ebp, -0x20u, edi);
                                    port_set32(&port, ebp, -0x24u, eax);
                                } while ((int32_t)eax < (int32_t)ecx && !port.env.failed);
                            }
                            eax = port_u32(&port, ebp, -0x34u) + 4;
                            edx = port_u32(&port, ebp, -0x30u) + 1;
                            port_set32(&port, ebp, -0x34u, eax);
                            port_set32(&port, ebp, -0x30u, edx);
                            eax = edx;
                            edx = port_u32(&port, ebp, -0x38u);
                        } while ((int32_t)eax < (int32_t)port_u32(&port, edx, 0x148) &&
                                 !port.env.failed);
                    }
                    ecx = port_u32(&port, port_u32(&port, ebp, -0x38u), 0x1bc);
                    edx = port_u32(&port, ebp, -0x44u);
                    eax =
                        port_call_with(&port, port_u32(&port, ecx, 4), port_u32(&port, ebp, -0x38u),
                                       edx, ebx, ecx, esi, edi, ebp);
                    if (eax == 0)
                    {
                        edx = port_u32(&port, ebp, -0x1cu);
                        port_set32(&port, edx, 0x18, port_u32(&port, ebp, -0x48u));
                        port_set32(&port, edx, 0x14, port_u32(&port, ebp, -0x3cu));
                        return port_return(&port, 0, port_u32(&port, ebp, -0xcu));
                    }
                    eax = port_u32(&port, ebp, -0x3cu) + 1;
                    edx = port_u32(&port, ebp, -0x38u);
                    ecx = port_u32(&port, edx, 0x15c);
                    port_set32(&port, ebp, -0x3cu, eax);
                } while (eax < ecx && !port.env.failed);
            }
            eax = port_u32(&port, ebp, -0x1cu);
            esi = port_u32(&port, ebp, -0x40u) + 4;
            edi = port_u32(&port, ebp, -0x48u) + 1;
            port_set32(&port, eax, 0x14, 0);
            ecx = port_u32(&port, eax, 0x1c);
            port_set32(&port, ebp, -0x40u, esi);
            port_set32(&port, ebp, -0x48u, edi);
        } while ((int32_t)edi < (int32_t)ecx && !port.env.failed);
    }
    eax = port_u32(&port, ebp, -0x38u);
    ebx = port_u32(&port, eax, 0x94) + 1;
    esi = port_u32(&port, eax, 0x140);
    port_set32(&port, eax, 0x94, ebx);
    if (ebx >= esi)
    {
        edx = port_u32(&port, eax, 0x1b4);
        port_call_with(&port, port_u32(&port, edx, 0xc), eax, edx, ebx, ecx, esi, edi, ebp);
        return port_return(&port, 4, port_u32(&port, ebp, -0xcu));
    }
    port_call_with(&port, 0x4b9d70, eax, edx, ebx, ecx, esi, edi, ebp);
    return port_return(&port, 3, port_u32(&port, ebp, -0xcu));
}
