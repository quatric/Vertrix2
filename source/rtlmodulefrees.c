#include "rtlmodulefrees.h"

/* Music modules freed. */

/* Original 0x40ef90: the module eax freed (0x4ea190 for each block): with patterns (+0x150, 0xc
 * bytes each, +0x28 of them) each one's data +8, then the list; with instruments (+0x154, 0xfc
 * bytes each, +0x2a of them) each one's samples (+0xf8, 0x3c bytes each, +0x80 of them; each from
 * +0x24 freed by 0x40aca0) and their list, then the list; then the module. The walks step edx on
 * from what each call leaves in it. eax 0, or 2 with no module; edx kept. */
uint32_t vertrix_port_module_free_40ef90(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t module = entry->eax;
    uint32_t edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
#define CALL(target, a)                                                                            \
    (port_call_with(&port, target, a, edx, ebx, ecx, esi, edi, ebp), edx = vertrix_lift_edx)
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    port_set32(&port, ebp, -0x18u, module);
    if (module == 0)
    {
        return port_return(&port, 2, entry->edx);
    }
    edx = port_u32(&port, module, 0x150);
    if (edx != 0)
    {
        for (ecx = 0;; ecx++, edx += 0xc)
        {
            ebx = module;
            if (ecx >= port_u16(&port, module, 0x28) || port.env.failed)
            {
                break;
            }
            ebx = port_u32(&port, edx, 8);
            if (ebx != 0)
            {
                CALL(0x4ea190, ebx);
            }
        }
        CALL(0x4ea190, port_u32(&port, module, 0x150));
    }
    esi = port_u32(&port, module, 0x154);
    if (esi != 0)
    {
        for (edi = 0;; edi++, esi += 0xfc)
        {
            edx = module;
            if (edi >= port_u16(&port, module, 0x2a) || port.env.failed)
            {
                break;
            }
            ebx = port_u32(&port, esi, 0xf8);
            edx = ebx + 0x24;
            for (ecx = 0; ecx < port_u16(&port, esi, 0x80) && !port.env.failed; ecx++)
            {
                CALL(0x40aca0, edx);
                edx += 0x3c;
                ebx += 0x3c;
            }
            CALL(0x4ea190, port_u32(&port, esi, 0xf8));
        }
        CALL(0x4ea190, port_u32(&port, module, 0x154));
    }
    CALL(0x4ea190, module);
#undef CALL
    return port_return(&port, 0, entry->edx);
}
