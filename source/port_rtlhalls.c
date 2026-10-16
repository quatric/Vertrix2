#include "port_rtlhalls.h"

/* The level select screen and its room refresh. */

/* Original 0x41f9b0 (guarded 0x514120): the level screen eax set up: the level 0x532bbc of the
 * set 0x532a68 opened (0x415180), 0x45e720, the eight level pictures named by 0x4fc5a8 with the
 * names from 0x5334a0 at 0x513c24 on (0x45f540) loaded (0x423d70), set (0x45e750) and released
 * (0x478d80); its title from 0x4fc290 with the name 0x5332c0 of the set's kind (0x53d948 by
 * 0x532a64) set (0x41a960), its font 0x4f8528 (0x4191b0), 0x45f770, 0x471340, the tune 0x13 of
 * 0x598d30 (0x4826c0) played (0x4713c0), 0x46f440, the keys 0x54d640 reset (0x476090, 0x4760c0),
 * 0x4b7cd0, 0x5588f8 cleared (0x477d70), 0x532a98 kept at 0x532a58, the screen readied
 * (0x41aa20, 0x471a70, 0x471a80, 0x41ab00, 0x41ab60, 0x41aaa0 with the painter 0x423600, +0xc8
 * 1, 0x418840) and handed its step 0x41fb40 (0x418820). eax the restored chain. */
uint32_t vertrix_port_level_screen_setup_41f9b0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x130
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t record = ebp - 0x28;
    uint32_t screen = entry->eax;
    uint32_t eax;
    uint32_t ebx = 0;
    uint32_t ecx = 0x514120;
    uint32_t esi = 0;
#define CALL(target, a, d) port_call_with(&port, target, a, d, ebx, ecx, esi, screen, ebp)
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    port_set32(&port, record, 0, port.env.chain);
    port.env.chain = record;
    port_set32(&port, ebp, -0x24u, 0x4ec1ec);
    port_set32(&port, ebp, -0x20u, 0x514120);
    port_set32(&port, ebp, -0x1cu, 0);
    eax = CALL(0x415180, port_u32(&port, 0, 0x532bbc), port_u32(&port, 0, 0x532a68));
    CALL(0x45e720, eax, vertrix_lift_edx);
    do
    {
        eax = port_u8(&port, 0, 0x513c24) + esi;
        ebx = port_u32(&port, eax * 4 + 0x5334a0, 0);
        CALL(0x45f540, ebp - 0x12c, 0x4fc5a8);
        eax = CALL(0x423d70, ebp - 0x12c, vertrix_lift_edx);
        ecx = eax;
        if (eax != 0)
        {
            CALL(0x45e750, esi, eax);
            CALL(0x478d80, ecx, vertrix_lift_edx);
        }
        esi++;
    } while (esi < 8 && !port.env.failed);
    eax = port_u32(&port, port_u32(&port, 0, 0x532a64) * 4 + 0x53d948, 0);
    ebx = port_u32(&port, eax * 4 + 0x5332c0, 0);
    CALL(0x45f540, ebp - 0x12c, 0x4fc290);
    CALL(0x41a960, screen, ebp - 0x12c);
    ebx = 0;
    eax = CALL(0x4191b0, screen, port_u32(&port, 0, 0x4f8528));
    eax = CALL(0x45f770, eax, vertrix_lift_edx);
    CALL(0x471340, eax, vertrix_lift_edx);
    eax = CALL(0x4826c0, 0x598d30, 0x13);
    eax = CALL(0x4713c0, eax & 0xffff, vertrix_lift_edx);
    CALL(0x46f440, eax, vertrix_lift_edx);
    CALL(0x476090, 0x54d640, vertrix_lift_edx);
    eax = CALL(0x4760c0, 0x54d640, vertrix_lift_edx);
    CALL(0x4b7cd0, eax, vertrix_lift_edx);
    CALL(0x477d70, 0x5588f8, vertrix_lift_edx);
    port_set32(&port, 0, 0x532a58, port_u32(&port, 0, 0x532a98));
    eax = CALL(0x41aa20, screen, vertrix_lift_edx);
    eax = CALL(0x471a70, eax, vertrix_lift_edx);
    CALL(0x471a80, eax, vertrix_lift_edx);
    CALL(0x41ab00, screen, vertrix_lift_edx);
    CALL(0x41ab60, screen, vertrix_lift_edx);
    CALL(0x41aaa0, screen, 0x423600);
    port_set8(&port, screen, 0xc8, 1);
    CALL(0x418840, screen, vertrix_lift_edx);
    CALL(0x418820, screen, 0x41fb40);
#undef CALL
    eax = port_u32(&port, record, 0);
    port.env.chain = eax;
    return port_return(&port, eax, entry->edx);
}

/* Original 0x423bc0: the level screen eax refreshed under the guard record 0x514214 as 0x4237d0
 * with the flag 0x540604 and the count 0x540608, but the entries from the old count to the new
 * added (0x479e50 with 0x558c88) counting down from a third of twice 0x5b9c8e less the old count
 * while above 0. eax the restored chain, edx kept. */
uint32_t vertrix_port_level_room_refresh_423bc0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x34
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t record = ebp - 0x30;
    uint32_t screen = entry->eax;
    uint32_t eax;
    uint32_t edx = 0x4ec1ec;
    uint32_t ebx = 0;
    uint32_t ecx = 0x514214;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t flag;
    uint32_t count;
#define CALL(target, a, d) port_call_with(&port, target, a, d, ebx, ecx, esi, edi, ebp)
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    port_set32(&port, ebp, -0x18u, screen);
    port_set32(&port, record, 0, port.env.chain);
    port.env.chain = record;
    flag = port_u8(&port, 0, 0x540604);
    eax = (record & 0xffff00ffu) | (flag << 8);
    port_set32(&port, ebp, -0x2cu, 0x4ec1ec);
    port_set32(&port, ebp, -0x28u, 0x514214);
    port_set32(&port, ebp, -0x24u, 0);
    if (flag == 0)
    {
        edx = (edx & 0xffffff00u) | 1;
        port_set32(&port, 0, 0x540608, 0);
        port_set8(&port, 0, 0x540604, 1);
        eax = CALL(0x4b7cd0, eax, edx);
        CALL(0x472100, eax, vertrix_lift_edx);
        eax = CALL(0x41d640, screen, vertrix_lift_edx);
        edx = vertrix_lift_edx;
    }
    CALL(0x4b7d10, eax, edx);
    eax = CALL(0x41d670, screen, 7);
    CALL(0x472350, eax, vertrix_lift_edx);
    eax = CALL(0x4b5eb0, 0x54676c, vertrix_lift_edx);
    if (eax != 0)
    {
        eax = port_u32(&port, eax, 0x58);
    }
    port_set32(&port, ebp, -0x1cu, eax);
    CALL(0x486d00, 0x5b9c50, vertrix_lift_edx);
    edx = vertrix_lift_edx;
    eax = port_u32(&port, 0, 0x540608);
    if (eax == 0)
    {
        uint32_t size = port_u32(&port, 0, 0x558c80);
        uint32_t args[4] = {0, 0, port_u32(&port, size, 4), port_u32(&port, size, 8)};
        ecx = 0;
        ebx = 0;
        vertrix_lift_in_esi = esi;
        vertrix_lift_in_edi = edi;
        vertrix_lift_in_ebp = ebp;
        lift_call_arguments(&port.env, 0x47ce10, port_u32(&port, 0, 0x558c7c), size, 0, 0, args, 4);
        vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
        edx = vertrix_lift_edx;
    }
    esi = port_u32(&port, ebp, -0x1cu);
    if (esi != port_u32(&port, 0, 0x540608))
    {
        LiftFlags flags = {0};
        uint32_t third = port_u16(&port, 0, 0x5b9c8e) * 2;
        edx = 0;
        ecx = 3;
        lift_div1(32, ecx, &third, &edx, &flags);
        edi = port_u32(&port, ebp, -0x1cu);
        esi = port_u32(&port, 0, 0x540608);
        if (esi <= edi)
        {
            ecx = third - esi;
            edi = third - edi;
            do
            {
                if ((int32_t)ecx > 0)
                {
                    ebx = ecx;
                    CALL(0x479e50, port_u32(&port, 0, 0x558c7c), port_u32(&port, 0, 0x558c88));
                    edx = vertrix_lift_edx;
                }
                ecx--;
                esi++;
            } while ((int32_t)ecx >= (int32_t)edi && !port.env.failed);
        }
    }
    CALL(0x41d6d0, screen, edx);
    CALL(0x486da0, 0x5b9c50, vertrix_lift_edx);
    CALL(0x487020, 0x5b9c50, vertrix_lift_edx);
    CALL(0x486ed0, 0x5b9c50, vertrix_lift_edx);
    count = port_u32(&port, ebp, -0x1cu);
    port_set32(&port, 0, 0x540608, count);
    CALL(0x41d660, screen, vertrix_lift_edx);
    CALL(0x41de80, screen, vertrix_lift_edx);
    eax = CALL(0x41ddf0, screen, vertrix_lift_edx);
    eax = CALL(0x472360, eax, vertrix_lift_edx);
    if (eax == 1)
    {
        CALL(0x472330, eax, vertrix_lift_edx);
        CALL(0x41ac80, screen, vertrix_lift_edx);
        CALL(0x418830, screen, vertrix_lift_edx & 0xffff00ffu);
        port_set8(&port, 0, 0x540604, vertrix_lift_edx >> 8);
    }
#undef CALL
    eax = port_u32(&port, record, 0);
    port.env.chain = eax;
    return port_return(&port, eax, entry->edx);
}
