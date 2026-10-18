#include "virtarrays.h"

/* The image decoder memory manager's virtual arrays. */

/* `xor edx, edx; div divisor`: the quotient, the dividend unchanged when it would fault. */
static uint32_t divide(uint32_t dividend, uint32_t divisor)
{
    return divisor != 0 ? dividend / divisor : dividend;
}

/* Original 0x4c5200: the memory manager +4 of the decoder eax realizes its virtual sample (+0x44)
 * and block (+0x48, 0x80 bytes a sample) arrays, each chained by +0x2c. Those not yet made
 * (+0) count their least (access +0xc by width +8) and whole (rows +4 by width) space; with any
 * least space, the memory available (0x4c5bf0 with the total +0x4c) bounds the row groups
 * (1000000000, or that over the least space and at least 1). An array needing more groups keeps
 * that many access rows (+0x10) and opens backing store (0x4c5c00 into +0x30, +0x28 set), else
 * keeps all its rows; its rows are made (0x4c4f60, 0x4c5030 for blocks) and the chunk +0x14 (the
 * manager's +0x50) set, +0x18, +0x1c and +0x24 cleared. edx kept. */
uint32_t vertrix_port_virtual_arrays_realize_4c5200(PORT_SIGNATURE)
{
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t cinfo = entry->eax;
    uint32_t mem;
    uint32_t least = 0;
    uint32_t most = 0;
    uint32_t groups;
    uint32_t eax;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t edx = 0;
    uint32_t esi;
    uint32_t height;
    port_open(&port, calls, services, globals, entry);
    mem = port_u32(&port, cinfo, 4);
    for (esi = port_u32(&port, mem, 0x44); esi != 0 && !port.env.failed;
         esi = port_u32(&port, esi, 0x2c))
    {
        if (port_u32(&port, esi, 0) == 0)
        {
            edx = port_u32(&port, esi, 8);
            ecx = least + port_u32(&port, esi, 0xc) * edx;
            edx = most + port_u32(&port, esi, 4) * edx;
            least = ecx;
            most = edx;
        }
    }
    for (eax = port_u32(&port, mem, 0x48); eax != 0 && !port.env.failed;
         eax = port_u32(&port, eax, 0x2c))
    {
        if (port_u32(&port, eax, 0) == 0)
        {
            ebx = port_u32(&port, eax, 8);
            ecx = least + ((port_u32(&port, eax, 8) * port_u32(&port, eax, 0xc)) << 7);
            edx = most + ((port_u32(&port, eax, 4) * ebx) << 7);
            least = ecx;
            most = edx;
        }
    }
    if ((int32_t)least <= 0)
    {
        return port_return(&port, eax, entry->edx);
    }
    eax = port_call_with(&port, 0x4c5bf0, cinfo, least, most, port_u32(&port, mem, 0x4c), 0, cinfo,
                         ebp);
    ebx = most;
    if ((int32_t)eax < (int32_t)most)
    {
        LiftFlags flags = {0, 0, 0, 0, 0, 0};
        edx = (uint32_t)((int32_t)eax >> 31);
        lift_idiv1(32, least, &eax, &edx, &flags);
        groups = (int32_t)eax > 0 ? eax : 1;
    }
    else
    {
        groups = 1000000000;
    }
    for (esi = port_u32(&port, mem, 0x44); esi != 0 && !port.env.failed;
         esi = port_u32(&port, esi, 0x2c))
    {
        if (port_u32(&port, esi, 0) != 0)
        {
            continue;
        }
        ebx = port_u32(&port, esi, 0xc);
        eax = divide(port_u32(&port, esi, 4) - 1, ebx) + 1;
        if ((int32_t)eax > (int32_t)groups)
        {
            port_set32(&port, esi, 0x10, groups * ebx);
            ecx = port_u32(&port, esi, 8);
            ebx = port_u32(&port, esi, 4) * ecx;
            port_call_with(&port, 0x4c5c00, cinfo, esi + 0x30, ebx, ecx, esi, cinfo, ebp);
            port_set32(&port, esi, 0x28, 1);
        }
        else
        {
            port_set32(&port, esi, 0x10, port_u32(&port, esi, 4));
        }
        ecx = port_u32(&port, esi, 0x10);
        ebx = port_u32(&port, esi, 8);
        port_set32(&port, esi, 0,
                   port_call_with(&port, 0x4c4f60, cinfo, 1, ebx, ecx, esi, cinfo, ebp));
        eax = port_u32(&port, mem, 0x50);
        port_set32(&port, esi, 0x18, 0);
        port_set32(&port, esi, 0x1c, 0);
        port_set32(&port, esi, 0x24, 0);
        port_set32(&port, esi, 0x14, eax);
    }
    for (esi = port_u32(&port, mem, 0x48); esi != 0 && !port.env.failed;
         esi = port_u32(&port, esi, 0x2c))
    {
        if (port_u32(&port, esi, 0) != 0)
        {
            continue;
        }
        ecx = port_u32(&port, esi, 0xc);
        eax = divide(port_u32(&port, esi, 4) - 1, ecx) + 1;
        if ((int32_t)eax > (int32_t)groups)
        {
            height = groups * ecx;
            port_set32(&port, esi, 0x10, height);
            ebx = (port_u32(&port, esi, 4) * port_u32(&port, esi, 8)) << 7;
            port_call_with(&port, 0x4c5c00, cinfo, esi + 0x30, ebx, ecx, esi, cinfo, ebp);
            port_set32(&port, esi, 0x28, 1);
        }
        else
        {
            port_set32(&port, esi, 0x10, port_u32(&port, esi, 4));
        }
        ecx = port_u32(&port, esi, 0x10);
        ebx = port_u32(&port, esi, 8);
        port_set32(&port, esi, 0,
                   port_call_with(&port, 0x4c5030, cinfo, 1, ebx, ecx, esi, cinfo, ebp));
        eax = port_u32(&port, mem, 0x50);
        port_set32(&port, esi, 0x18, 0);
        port_set32(&port, esi, 0x1c, 0);
        port_set32(&port, esi, 0x24, 0);
        port_set32(&port, esi, 0x14, eax);
    }
    return port_return(&port, eax, entry->edx);
}

/* The decoder's error `code` raised by the error manager [cinfo]'s method +0 (eax cinfo, edx and
 * ebx as given, ecx the manager, left in *ecx); its edx. */
static uint32_t raise_error(Port *port, uint32_t cinfo, uint32_t code, uint32_t edx, uint32_t ebx,
                            uint32_t *ecx, uint32_t esi, uint32_t ebp)
{
    uint32_t error = port_u32(port, cinfo, 0);
    port_set32(port, error, 0x14, code);
    error = port_u32(port, cinfo, 0);
    *ecx = error;
    port_call_with(port, port_u32(port, error, 0), cinfo, edx, ebx, error, esi, cinfo, ebp);
    return vertrix_lift_edx;
}

/* Rows ebx..+ecx of the virtual array edx (rows +4, access +0xc, buffer +0, first row in memory
 * +0x18 of +0x10, first undefined +0x1c, zeroed +0x20, dirty +0x24, backing store open +0x28,
 * width +8) for the decoder eax, writable when the stack argument is set (ret 4): out of range is
 * error 0x16; rows outside the window swap through backing store (`io`: writing a dirty window
 * with 1, reading the new one from 0x18 with 0; no store is error 0x45). Undefined rows reached
 * become defined when writing, zeroed (0x4c98f0, the width shifted by `shift`) when +0x20 is set
 * (reading them otherwise is error 0x16), and a write leaves the window dirty. eax is the first
 * row's place in the buffer. */
static uint32_t access_virtual(PORT_SIGNATURE, uint32_t io, unsigned shift)
{
    enum
    {
        BELOW = 0
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4];
    uint32_t ebp = entry->esp - 4;
    uint32_t cinfo = entry->eax;
    uint32_t array = entry->edx;
    uint32_t start = entry->ebx;
    uint32_t end;
    uint32_t writable;
    uint32_t eax;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t edx;
    uint32_t edi = cinfo;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 1);
    writable = port_u32(&port, entry->esp, 4);
    end = start + entry->ecx;
    edx = port_u32(&port, array, 4);
    if (end > edx || entry->ecx > port_u32(&port, array, 0xc) || port_u32(&port, array, 0) == 0)
    {
        edx = raise_error(&port, cinfo, 0x16, edx, ebx, &ecx, array, ebp);
    }
    edx = port_u32(&port, array, 0x18);
    if (start >= edx)
    {
        ecx = port_u32(&port, array, 0x10);
        ebx = end;
    }
    if (start < edx || edx + ecx < end)
    {
        if (port_u32(&port, array, 0x28) == 0)
        {
            edx = raise_error(&port, cinfo, 0x45, edx, ebx, &ecx, array, ebp);
        }
        if (port_u32(&port, array, 0x24) != 0)
        {
            ebx = 1;
            port_call_with(&port, io, cinfo, array, ebx, ecx, array, edi, ebp);
            port_set32(&port, array, 0x24, 0);
        }
        eax = start;
        if (start <= port_u32(&port, array, 0x18))
        {
            eax = end - port_u32(&port, array, 0x10);
            if ((int32_t)eax < 0)
            {
                eax = 0;
            }
        }
        port_set32(&port, array, 0x18, eax);
        ebx = 0;
        port_call_with(&port, io, cinfo, array, ebx, ecx, array, edi, ebp);
    }
    edx = end;
    eax = port_u32(&port, array, 0x1c);
    if (eax < end)
    {
        if (eax >= start)
        {
            ecx = eax;
        }
        else
        {
            if (writable != 0)
            {
                edx = raise_error(&port, cinfo, 0x16, edx, ebx, &ecx, array, ebp);
            }
            ecx = start;
        }
        if (writable != 0)
        {
            port_set32(&port, array, 0x1c, end);
        }
        if (port_u32(&port, array, 0x20) == 0)
        {
            if (writable == 0)
            {
                edx = raise_error(&port, cinfo, 0x16, edx, ebx, &ecx, array, ebp);
            }
        }
        else
        {
            ebx = port_u32(&port, array, 0x18);
            edi = port_u32(&port, array, 8) << shift;
            edx = end - ebx;
            ecx -= ebx;
            end = edx;
            if (ecx < edx)
            {
                ebx = ecx * 4;
                do
                {
                    eax = port_u32(&port, port_u32(&port, array, 0) + ebx, 0);
                    ecx++;
                    port_call_with(&port, 0x4c98f0, eax, edi, ebx, ecx, array, edi, ebp);
                    edx = vertrix_lift_edx;
                    ebx += 4;
                } while (ecx < end && !port.env.failed);
            }
        }
    }
    if (writable != 0)
    {
        port_set32(&port, array, 0x24, 1);
    }
    eax = ((start - port_u32(&port, array, 0x18)) << 2) + port_u32(&port, array, 0);
    return port_return(&port, eax, edx);
}

/* Original 0x4c55a0: access_virtual for a sample array (0x4c5400). */
uint32_t vertrix_port_virtual_sample_access_4c55a0(PORT_SIGNATURE)
{
    return access_virtual(calls, services, globals, entry, 0x4c5400, 0);
}

/* Original 0x4c5740: access_virtual for a block array (0x4c54d0, rows of 0x80-byte blocks). */
uint32_t vertrix_port_virtual_block_access_4c5740(PORT_SIGNATURE)
{
    return access_virtual(calls, services, globals, entry, 0x4c54d0, 7);
}
