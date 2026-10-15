#include "port_dcfirsts.h"

/* The progressive decoder's first DC scan. */

/* Original 0x4c2780: one MCU of a first DC scan for the decoder eax into the blocks edx: past a
 * due restart (+0x114, the entropy decoder +0x1bc's count +0x28; 0x4c26f0, 0 when it fails) and
 * unless the data ran out (+8), the bit reader (the source +0x18's place and count, the buffer
 * +0xc and its bits +0x10) and the saved state (+0x14, 20 bytes) are copied into the frame. For
 * each block (+0x164 of them, component by +0x168) the DC table (+0x2c by +0x14) decodes a size
 * (the 8-bit lookahead +0x90/+0x490, else 0x4bc050 from 9 bits), its bits (0x4bbf30 to fill) are
 * sign extended (0x4ffd3c, 0x4ffd7c) and added to the component's last DC; that shifted by +0x19c
 * is the block's first word. Any failure gives 0; otherwise the reader and state go back, the
 * restart count drops and eax is 1. The frame is the original's, the last DCs indexed by the
 * component number; edx is the bit buffer (the call's after a failure). */
uint32_t vertrix_port_decode_dc_first_4c2780(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x5c
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t cinfo = entry->eax;
    uint32_t entropy;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx;
    uint32_t eax;
    uint32_t esi;
    uint32_t edi;
    uint32_t table;
    uint32_t ci;
    uint32_t size;
    uint32_t i;
    uint32_t args[1];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->esi);
    port_set32(&port, ebp, -0x10u, entry->edi);
    port_set32(&port, ebp, -0x24u, cinfo);
    ecx = entry->edx;
    entropy = port_u32(&port, cinfo, 0x1bc);
    port_set32(&port, ebp, -0x2cu, entropy);
    port_set32(&port, ebp, -0x30u, port_u32(&port, cinfo, 0x19c));
    if (port_u32(&port, cinfo, 0x114) != 0)
    {
        ebx = port_u32(&port, entropy, 0x28);
        if (ebx == 0)
        {
            eax =
                port_call_with(&port, 0x4c26f0, cinfo, edx, ebx, ecx, entry->esi, entry->edi, ebp);
            edx = vertrix_lift_edx;
            if (eax == 0)
            {
                return port_return(&port, ebx, edx);
            }
        }
    }
    if (port_u32(&port, entropy, 8) == 0)
    {
        port_set32(&port, ebp, -0x34u, cinfo);
        port_set32(&port, ebp, -0x44u, port_u32(&port, port_u32(&port, cinfo, 0x18), 0));
        port_set32(&port, ebp, -0x40u, port_u32(&port, port_u32(&port, cinfo, 0x18), 4));
        edx = port_u32(&port, entropy, 0xc);
        ebx = port_u32(&port, entropy, 0x10);
        for (i = 0; i < 0x14; i += 4)
        {
            port_set32(&port, ebp - 0x58 + i, 0, port_u32(&port, entropy + 0x14 + i, 0));
        }
        esi = port_u32(&port, cinfo, 0x164);
        edi = 0;
        if ((int32_t)esi > 0)
        {
            port_set32(&port, ebp, -0x18u, cinfo);
            port_set32(&port, ebp, -0x1cu, ecx);
            do
            {
                port_set32(&port, ebp, -0x28u, port_u32(&port, port_u32(&port, ebp, -0x1cu), 0));
                ci = port_u32(&port, port_u32(&port, ebp, -0x18u), 0x168);
                port_set32(&port, ebp, -0x20u, ci);
                eax = port_u32(&port, port_u32(&port, ci * 4 + port_u32(&port, ebp, -0x24u), 0x14c),
                               0x14);
                table = port_u32(&port, eax * 4 + port_u32(&port, ebp, -0x2cu), 0x2c);
                esi = table;
                size = 9;
                if ((int32_t)ebx < 8)
                {
                    eax = port_call_with(&port, 0x4bbf30, ebp - 0x44, edx, ebx, 0, esi, edi, ebp);
                    if (eax == 0)
                    {
                        return port_return(&port, 0, vertrix_lift_edx);
                    }
                    ebx = port_u32(&port, ebp, -0x38u);
                    edx = port_u32(&port, ebp, -0x3cu);
                    if ((int32_t)ebx < 8)
                    {
                        size = 1;
                        goto slow;
                    }
                }
                ecx = ((int32_t)edx >> ((ebx - 8) & 31)) & 0xff;
                eax = port_u32(&port, table + ecx * 4, 0x90);
                if (eax != 0)
                {
                    esi = table + ecx;
                    ebx -= eax;
                    port_set32(&port, ebp, -0x14u, port_u8(&port, esi, 0x490));
                    goto sized;
                }
            slow:
                args[0] = size;
                vertrix_lift_in_esi = esi;
                vertrix_lift_in_edi = edi;
                vertrix_lift_in_ebp = ebp;
                eax =
                    lift_call_arguments(&port.env, 0x4bc050, ebp - 0x44, edx, ebx, table, args, 1);
                vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
                port_set32(&port, ebp, -0x14u, eax);
                if ((int32_t)eax < 0)
                {
                    return port_return(&port, 0, vertrix_lift_edx);
                }
                edx = port_u32(&port, ebp, -0x3cu);
                ebx = port_u32(&port, ebp, -0x38u);
            sized:
                esi = port_u32(&port, ebp, -0x14u);
                if (esi != 0)
                {
                    if ((int32_t)ebx < (int32_t)esi)
                    {
                        eax = port_call_with(&port, 0x4bbf30, ebp - 0x44, edx, ebx, esi, esi, edi,
                                             ebp);
                        if (eax == 0)
                        {
                            return port_return(&port, 0, vertrix_lift_edx);
                        }
                        edx = port_u32(&port, ebp, -0x3cu);
                        ebx = port_u32(&port, ebp, -0x38u);
                    }
                    size = port_u32(&port, ebp, -0x14u);
                    ebx -= size;
                    eax = (uint32_t)((int32_t)edx >> (ebx & 31));
                    eax &= (1u << (size & 31)) - 1;
                    if ((int32_t)eax < (int32_t)port_u32(&port, size * 4, 0x4ffd3c))
                    {
                        eax += port_u32(&port, size * 4, 0x4ffd7c);
                    }
                    port_set32(&port, ebp, -0x14u, eax);
                }
                ci = port_u32(&port, ebp, -0x20u);
                esi = port_u32(&port, ebp, -0x14u) + port_u32(&port, ci * 4 + ebp, -0x54u);
                port_set32(&port, ebp, -0x14u, esi);
                port_set32(&port, ci * 4 + ebp, -0x54u, esi);
                eax = port_u32(&port, ebp, -0x14u) << (port_u8(&port, ebp, -0x30u) & 31);
                port_set16(&port, port_u32(&port, ebp, -0x28u), 0, eax);
                port_set32(&port, ebp, -0x18u, port_u32(&port, ebp, -0x18u) + 4);
                port_set32(&port, ebp, -0x1cu, port_u32(&port, ebp, -0x1cu) + 4);
                edi++;
                esi = port_u32(&port, port_u32(&port, ebp, -0x24u), 0x164);
            } while ((int32_t)edi < (int32_t)esi && !port.env.failed);
        }
        cinfo = port_u32(&port, ebp, -0x24u);
        port_set32(&port, port_u32(&port, cinfo, 0x18), 0, port_u32(&port, ebp, -0x44u));
        cinfo = port_u32(&port, ebp, -0x24u);
        port_set32(&port, port_u32(&port, cinfo, 0x18), 4, port_u32(&port, ebp, -0x40u));
        entropy = port_u32(&port, ebp, -0x2cu);
        port_set32(&port, entropy, 0xc, edx);
        port_set32(&port, entropy, 0x10, ebx);
        for (i = 0; i < 0x14; i += 4)
        {
            port_set32(&port, entropy + 0x14 + i, 0, port_u32(&port, ebp - 0x58 + i, 0));
        }
    }
    entropy = port_u32(&port, ebp, -0x2cu);
    port_set32(&port, entropy, 0x28, port_u32(&port, entropy, 0x28) - 1);
    return port_return(&port, 1, edx);
}
