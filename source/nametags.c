#include "nametags.h"

/* The player name tag. */

static void guard_record(Port *port, uint32_t record, uint32_t guard)
{
    port_set32(port, record, 0, port->env.chain);
    port_set32(port, record, 4, 0x4ec1ec);
    port_set32(port, record, 8, guard);
    port_set32(port, record, 0xc, 0);
}

/* Original 0x44b170: the player tag eax under a guard record (0x5152b4) bobs when due (0x4ac500,
 * 0x4ac520, 0x4ac540, 0x4ac5b0; with +0x48 set +0x4a 0, +0x4c 5, 0x4ad530, 0x4adfe0); its text
 * +0x15c (0x4ca280) is compared (0x4ccfe0) with 0x50e1a1 (0x4ca370), or the player 0x532a6c's
 * name of 0x53453c (0x4ca310) when that is not -1 and, with 0x532a84 and 0x532a80 both 1, the
 * import 0x418130 gives 1; a change is taken in (0x4ca370) and, unless it is 0x50e1a3, bobs at
 * 80 with +0x7c 1 (0x4ac610), and ends the bob (0x4adfe0). With +0x7c 1 the tag, once its count
 * is done (0x4ac600, 0x4ac620), stops (0x4ac610), plays the player (0x43abd0 with 2), waits 800
 * (0x4ac860) and clears +0x7c. The temporaries are released (0x4cda10); the guard record's
 * chain. */
uint32_t vertrix_port_player_tag_step_44b170(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x34
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t edi = entry->edi;
    uint32_t index;
    uint32_t eax;
    uint32_t edx;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    guard_record(&port, ebp - 0x30, 0x5152b4);
    port_call_with(&port, 0x4ac500, actor, 0x4ec1ec, 0x5152b4, actor, 0, edi, ebp);
    if (port_call_with(&port, 0x4ac520, actor, vertrix_lift_edx, actor, actor, 0, edi, ebp) == 1)
    {
        eax = port_call_with(&port, 0x4ac540, actor, vertrix_lift_edx, actor, actor, 0, edi, ebp);
        port_call_with(&port, 0x4ac5b0, actor, eax, actor, actor, 0, edi, ebp);
        if (port_u16(&port, actor, 0x48) != 0)
        {
            port_set16(&port, actor, 0x4a, 0);
            port_set16(&port, actor, 0x4c, 5);
            port_call_with(&port, 0x4ad530, actor, vertrix_lift_edx, actor, actor, 0, edi, ebp);
            port_call_with(&port, 0x4adfe0, actor, vertrix_lift_edx, actor, actor, 0, edi, ebp);
        }
    }
    edi = 1;
    port_call_with(&port, 0x4ca280, ebp - 0x1c, port_u32(&port, actor, 0x15c), actor, actor, 0, edi,
                   ebp);
    port_set32(&port, ebp, -0x24u, 1);
    port_call_with(&port, 0x4ca070, ebp - 0x18, vertrix_lift_edx, actor, actor, 0, edi, ebp);
    port_set32(&port, ebp, -0x24u, 2);
    eax = port_call_with(&port, 0x4ca370, ebp - 0x18, 0x50e1a1, actor, actor, 0, edi, ebp);
    if (port_u32(&port, 0, 0x532a84) == 1 && port_u32(&port, 0, 0x532a80) == 1)
    {
        if (port_call_with(&port, 0x418130, eax, vertrix_lift_edx, actor, actor, 0, edi, ebp) == 1)
        {
            index = port_u32(&port, 0, 0x532a6c);
            if (index != 0xffffffffu)
            {
                port_call_with(&port, 0x4ca310, ebp - 0x18, 0x53453c + index * 4, actor, actor, 0,
                               edi, ebp);
            }
        }
    }
    else
    {
        edi = port_u32(&port, 0, 0x532a6c);
        if (edi != 0xffffffffu)
        {
            port_call_with(&port, 0x4ca310, ebp - 0x18, 0x53453c + edi * 4, actor, actor, 0, edi,
                           ebp);
        }
    }
    eax = port_call_with(&port, 0x4ccfe0, port_u32(&port, ebp, -0x1cu),
                         port_u32(&port, ebp, -0x18u), actor, actor, 0, edi, ebp);
    if (eax != 0)
    {
        port_call_with(&port, 0x4ca370, actor + 0x15c, port_u32(&port, ebp, -0x18u), actor, actor,
                       0, edi, ebp);
        if (port_call_with(&port, 0x4ccfe0, port_u32(&port, ebp, -0x18u), 0x50e1a3, actor, actor, 0,
                           edi, ebp) != 0)
        {
            port_set16(&port, actor, 0x48, 0x50);
            port_set32(&port, actor, 0x7c, 1);
            port_call_with(&port, 0x4ac610, actor, vertrix_lift_edx, actor, actor, 0, edi, ebp);
        }
        eax = port_call_with(&port, 0x4adfe0, actor, vertrix_lift_edx, actor, actor, 0, edi, ebp);
    }
    edx = port_u32(&port, actor, 0x7c);
    if (edx == 1)
    {
        port_call_with(&port, 0x4ac600, actor, edx, actor, actor, 0, edi, ebp);
        eax = port_call_with(&port, 0x4ac620, actor, vertrix_lift_edx, actor, actor, 0, edi, ebp);
        edx = vertrix_lift_edx;
        if (eax == edx)
        {
            port_call_with(&port, 0x4ac610, actor, edx, actor, actor, 0, edi, ebp);
            port_call_with(&port, 0x43abd0, 2, port_u32(&port, 0, 0x532a6c), actor, actor, 0, edi,
                           ebp);
            eax = port_call_with(&port, 0x4ac860, actor, 0x320, actor, actor, 0, edi, ebp);
            edx = vertrix_lift_edx;
            port_set32(&port, actor, 0x7c, 0);
        }
    }
    port_call_with(&port, 0x4cda10, eax, edx, actor, actor, 0, edi, ebp);
    return port_return(&port, port_u32(&port, ebp, -0x30u), entry->edx);
}
