#include "rtlmenus2.h"

/* Menu entries picked by their keys. */

/* Original 0x45ad20: the menu actor eax restarted (0x4ac510, 0x4ac380) and the keys 0x3b..0x44
 * (F1..F10) checked in the key table 0x54d640 (0x476480; a pressed one cleared by 0x4762e0): the
 * first pressed one below the slot's entry count 0x534f10 picks entry i of the slot 0x532a68 (the
 * record 0x544f90 + 280 * slot + 28 * i, its kind at 0x534c18 + 76 * i + 4 * slot): the actor shown
 * on it (0x4ac490, 0x4ac8d0, 0x4ac700, 0x4ac4a0, 0x4ac8a0 with 0x45aea0, 0x4ac8f0) and the kind's
 * sound (0x532ca4 or 0x532cf0 for kinds 1 and 2) played (0x417260, 0x417290) unless it is the
 * default 0x4f81cc. edx kept. */
uint32_t vertrix_port_menu_key_pick_45ad20(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t eax;
    uint32_t ebx = 0;
    uint32_t ecx = entry->ecx;
    uint32_t esi;
    uint32_t edi;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    port_set32(&port, ebp, -0x18u, actor);
#define CALL(target, a, d) port_call_with(&port, target, a, d, ebx, ecx, esi, edi, ebp)
    esi = entry->esi;
    edi = entry->edi;
    ebx = entry->ebx;
    CALL(0x4ac510, actor, entry->edx);
    ebx = 0;
    eax = CALL(0x4ac380, actor, vertrix_lift_edx);
    esi = 0x3b;
    edi = port_u32(&port, port_u32(&port, 0, 0x532a68) * 4, 0x534f10);
    do
    {
        ecx = esi & 0xffff;
        eax = CALL(0x476480, 0x54d640, ecx);
        if (eax != 0)
        {
            eax = CALL(0x4762e0, 0x54d640, ecx);
            if (ebx < edi)
            {
                uint32_t slot = port_u32(&port, 0, 0x532a68);
                uint32_t kind = port_u32(&port, slot * 4 + ebx * 76, 0x534c18);
                uint32_t record;
                int shown = 1;
                edi = ebx * 28;
                record = 0x544f90 + slot * 280 + edi;
                ecx = port_u32(&port, 0, 0x4f81cc);
                if (kind == 1)
                {
                    ecx = port_u32(&port, slot * 4, 0x532ca4);
                }
                else if (kind == 2)
                {
                    ecx = port_u32(&port, slot * 4, 0x532cf0);
                }
                else if (kind != 0 && kind != 3 && kind != 4 && kind != 5)
                {
                    shown = 0;
                }
                ebx = record;
                if (shown && record != 0)
                {
                    CALL(0x4ac490, actor, 0);
                    CALL(0x4ac8d0, actor, record);
                    CALL(0x4ac700, actor, vertrix_lift_edx);
                    CALL(0x4ac4a0, actor, vertrix_lift_edx);
                    CALL(0x4ac8a0, actor, 0x45aea0);
                    eax = CALL(0x4ac8f0, actor, vertrix_lift_edx);
                }
                if (ecx != port_u32(&port, 0, 0x4f81cc))
                {
                    CALL(0x417260, ecx, vertrix_lift_edx);
                    eax = CALL(0x417290, ecx, vertrix_lift_edx);
                }
                return port_return(&port, eax, entry->edx);
            }
        }
        ebx++;
        esi++;
    } while (ebx != 10 && !port.env.failed);
#undef CALL
    return port_return(&port, eax, entry->edx);
}
