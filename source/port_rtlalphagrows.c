#include "port_rtlalphagrows.h"

/* Picture alpha masks grown. */

/* Original 0x483400: the alpha mask of the 32-bit picture eax (a copy of it first, 0x483110,
 * when ebx is 0) grown edx times into a copy (0x483110) whose alpha is first cleared: each pass
 * marks (alpha 0xff) every pixel of the copy whose source pixel is set and, past the first row,
 * is an edge - on the last row, the first or last column, or beside a clear pixel above, below,
 * left or right (with ecx 1 also the four diagonal pixels); then clears the source's alpha under
 * every marked pixel of the copy. The copy of the source made here is freed (0x4830f0). eax the
 * grown copy. */
uint32_t vertrix_port_alpha_grow_483400(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x44
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t width;
    uint32_t height;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->esi);
    port_set32(&port, ebp, -8u, entry->edi);
    port_set32(&port, ebp, -0x28u, eax);
    port_set32(&port, ebp, -0x24u, edx);
    port_set32(&port, ebp, -0x30u, ebx);
    port_set32(&port, ebp, -0x38u, ecx);
    if (ebx == 0)
    {
        eax = port_call_with(&port, 0x483110, eax, edx, ebx, ecx, esi, edi, ebp);
        edx = vertrix_lift_edx;
        port_set32(&port, ebp, -0x28u, eax);
    }
    width = port_u32(&port, port_u32(&port, ebp, -0x28u), 4);
    port_set32(&port, ebp, -0xcu, width);
    height = port_u32(&port, port_u32(&port, ebp, -0x28u), 8);
    ecx = 0;
    port_set32(&port, ebp, -0x1cu, height);
    ebx = height;
    eax =
        port_call_with(&port, 0x483110, port_u32(&port, ebp, -0x28u), edx, ebx, ecx, esi, edi, ebp);
    edx = vertrix_lift_edx;
    port_set32(&port, ebp, -0x2cu, eax);
    eax = port_u32(&port, eax, 0);
    if (ebx != 0)
    {
        ebx = width;
        edi = width;
        esi = height;
        do
        {
            edx = 0;
            if (edi != 0)
            {
                do
                {
                    eax += 4;
                    edx++;
                    port_set8(&port, eax, -1u, 0);
                } while (edx < ebx && !port.env.failed);
            }
            ecx++;
        } while (ecx < esi && !port.env.failed);
    }
    port_set32(&port, ebp, -0x3cu, width - 1);
    port_set32(&port, ebp, -0x18u, height - 1);
    eax = width << 2;
    port_set32(&port, ebp, -0x20u, eax);
    port_set32(&port, ebp, -0x40u, eax);
    while (port_u32(&port, ebp, -0x24u) != 0 && !port.env.failed)
    {
        edx = 0;
        ecx = height;
        port_set32(&port, ebp, -0x10u, 0);
        eax = port_u32(&port, port_u32(&port, ebp, -0x28u), 0);
        edi = port_u32(&port, port_u32(&port, ebp, -0x2cu), 0);
        if (ecx != 0)
        {
            do
            {
                ecx = width;
                edx = 0;
                if (ecx != 0)
                {
                    esi = eax - port_u32(&port, ebp, -0x40u);
                    ecx = port_u32(&port, ebp, -0x20u) + eax;
                    do
                    {
                        int mark = 0;
                        ebx = port_u32(&port, eax, 0) >> 24;
                        port_set32(&port, ebp, -0x34u, ebx);
                        if ((ebx & 0xff) != 0)
                        {
                            port_set32(&port, ebp, -0x14u, 1);
                            mark = 1;
                            if (port_u32(&port, ebp, -0x10u) != 0)
                            {
                                static const int8_t above_below[4] = {-4, 4, -4, 4};
                                unsigned index;
                                mark = 0;
                                ebx = port_u32(&port, esi, 0) >> 24;
                                port_set32(&port, ebp, -0x34u, ebx);
                                if ((ebx & 0xff) == 0)
                                {
                                    mark = 1;
                                }
                                else if ((ebx = port_u32(&port, ebp, -0x10u)) ==
                                         port_u32(&port, ebp, -0x18u))
                                {
                                    mark = 1;
                                }
                                else if ((ebx = port_u32(&port, ecx, 0) >> 24,
                                          port_set32(&port, ebp, -0x34u, ebx), ebx & 0xff) == 0)
                                {
                                    mark = 1;
                                }
                                else if (edx == 0)
                                {
                                    mark = 1;
                                }
                                else if ((ebx = port_u32(&port, eax, -4u) >> 24,
                                          port_set32(&port, ebp, -0x34u, ebx), ebx & 0xff) == 0)
                                {
                                    mark = 1;
                                }
                                else if (edx == port_u32(&port, ebp, -0x3cu))
                                {
                                    mark = 1;
                                }
                                else if ((ebx = port_u32(&port, eax, 4) >> 24,
                                          port_set32(&port, ebp, -0x34u, ebx), ebx & 0xff) == 0)
                                {
                                    mark = 1;
                                }
                                else if (port_u32(&port, ebp, -0x38u) == 1)
                                {
                                    for (index = 0; index < 4 && !mark; index++)
                                    {
                                        uint32_t row = index < 2 ? esi : ecx;
                                        ebx = port_u32(&port, row,
                                                       (uint32_t)(int32_t)above_below[index]) >>
                                              24;
                                        port_set32(&port, ebp, -0x34u, ebx);
                                        if ((ebx & 0xff) == 0)
                                        {
                                            mark = 1;
                                        }
                                    }
                                }
                                if (!mark && port_u32(&port, ebp, -0x14u) == 0)
                                {
                                    mark = 1;
                                }
                            }
                            if (mark)
                            {
                                port_set8(&port, edi, 3, 0xff);
                            }
                        }
                        ebx = width;
                        esi += 4;
                        ecx += 4;
                        eax += 4;
                        edx++;
                        edi += 4;
                    } while (edx < ebx && !port.env.failed);
                }
                ebx = port_u32(&port, ebp, -0x10u) + 1;
                esi = height;
                port_set32(&port, ebp, -0x10u, ebx);
            } while (ebx < esi && !port.env.failed);
        }
        edx = port_u32(&port, port_u32(&port, ebp, -0x28u), 0);
        ecx = port_u32(&port, port_u32(&port, ebp, -0x2cu), 0);
        edi = height;
        esi = 0;
        if (edi != 0)
        {
            do
            {
                ebx = width;
                eax = 0;
                if (ebx != 0)
                {
                    edi = width;
                    do
                    {
                        ebx = port_u32(&port, ecx, 0) >> 24;
                        if ((ebx & 0xff) != 0)
                        {
                            port_set8(&port, edx, 3, 0);
                        }
                        edx += 4;
                        eax++;
                        ecx += 4;
                    } while (eax < edi && !port.env.failed);
                }
                edi = height;
                esi++;
            } while (esi < edi && !port.env.failed);
        }
        port_set32(&port, ebp, -0x24u, port_u32(&port, ebp, -0x24u) - 1);
    }
    if (port_u32(&port, ebp, -0x30u) == 0)
    {
        port_call_with(&port, 0x4830f0, port_u32(&port, ebp, -0x28u), edx, ebx, ecx, esi, edi, ebp);
        edx = vertrix_lift_edx;
    }
    return port_return(&port, port_u32(&port, ebp, -0x2cu), edx);
}
