#include "finishes.h"

/* The flagged finish of a run of frame resources. */

/* Original 0x45f250: for each of the ebx frames (edi counting up, ecx 1 then 0x31 more each time)
 * the frame resource (0x4877f0 of 0x544d60 when edx is set, else 0x544d44) is drawn to eax
 * (0x482e10), mirrored (0x483ce0) when edx is 1 and colour ordered (0x483ed0 of 0x5b9c60 with
 * ebx). eax and edx are the last call's, or the entry's for no frames; ecx, esi and edi kept. */
uint32_t vertrix_port_resource_flagged_finish_45f250(PORT_SIGNATURE)
{
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t target = entry->eax;
    uint32_t flag = entry->edx;
    uint32_t count = entry->ebx;
    uint32_t counter = 1;
    uint32_t esi = entry->esi;
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t edi;
    port_open(&port, calls, services, globals, entry);
    for (edi = 0; edi < count; edi++)
    {
        esi = port_call_with(&port, 0x4877f0, flag != 0 ? 0x544d60 : 0x544d44, edi, 1, counter, esi,
                             edi, ebp);
        port_call_with(&port, 0x482e10, esi, target, 1, counter, esi, edi, ebp);
        if (flag == 1)
        {
            port_call_with(&port, 0x483ce0, esi, vertrix_lift_edx, 1, counter, esi, edi, ebp);
        }
        eax = port_call_with(&port, 0x483ed0, esi, 0x5b9c60, count, counter, esi, edi, ebp);
        edx = vertrix_lift_edx;
        counter += 0x31;
    }
    return port_return(&port, eax, edx);
}
