#include "port_labels.h"

/* The menu tags of the picked piece and the grid click states. */

enum
{
    BELOW = 0x34
};

static void guard_record(Port *port, uint32_t record, uint32_t guard)
{
    port_set32(port, record, 0, port->env.chain);
    port_set32(port, record, 4, 0x4ec1ec);
    port_set32(port, record, 8, guard);
    port_set32(port, record, 0xc, 0);
}

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

static uint32_t sign16(uint32_t value)
{
    return (uint32_t)(int32_t)(int16_t)value;
}

/* The tag's opening: under a guard record the actor bobs when due (0x4ac500, 0x4ac520, 0x4ac540,
 * 0x4ac5b0; with +0x48 set +0x4a 0, +0x4c 5, 0x4ad530, 0x4adfe0); its text +0x15c is taken
 * (0x4ca280) and a new text made (0x4ca070). */
static void tag_open(Port *port, const LiftEntry *entry, uint32_t guard)
{
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t eax;
    guard_record(port, ebp - 0x30, guard);
    port_call_with(port, 0x4ac500, actor, 0x4ec1ec, guard, actor, 0, entry->edi, ebp);
    if (port_call_with(port, 0x4ac520, actor, vertrix_lift_edx, actor, actor, 0, entry->edi, ebp) ==
        1)
    {
        eax = port_call_with(port, 0x4ac540, actor, vertrix_lift_edx, actor, actor, 0, entry->edi,
                             ebp);
        port_call_with(port, 0x4ac5b0, actor, eax, actor, actor, 0, entry->edi, ebp);
        if (port_u16(port, actor, 0x48) != 0)
        {
            port_set16(port, actor, 0x4a, 0);
            port_set16(port, actor, 0x4c, 5);
            port_call_with(port, 0x4ad530, actor, vertrix_lift_edx, actor, actor, 0, entry->edi,
                           ebp);
            port_call_with(port, 0x4adfe0, actor, vertrix_lift_edx, actor, actor, 0, entry->edi,
                           ebp);
        }
    }
    port_call_with(port, 0x4ca280, ebp - 0x1c, port_u32(port, actor, 0x15c), actor, actor, 0, 1,
                   ebp);
    port_set32(port, ebp, -0x24u, 1);
    port_call_with(port, 0x4ca070, ebp - 0x18, vertrix_lift_edx, actor, actor, 0, 1, ebp);
    port_set32(port, ebp, -0x24u, 2);
}

/* Original 0x44b340: the piece tag eax (guard 0x5152c8): its text becomes 0x50e1a5 (0x4ca370),
 * or the entry of 0x534588 for the pick 0x532a6c (0x4ca310) when it is set and, with 0x532a84
 * and 0x532a80 both 1, the pick is ready (0x418130); a change from the tag's text (0x4ccfe0)
 * ends the bob (0x4adfe0), is taken in (0x4ca370) and bobs at 80. The temporaries are released
 * (0x4cda10); the guard record's chain. */
uint32_t vertrix_port_piece_tag_step_44b340(PORT_SIGNATURE)
{
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t edi = 1;
    uint32_t index;
    uint32_t eax;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    tag_open(&port, entry, 0x5152c8);
    eax = port_call_with(&port, 0x4ca370, ebp - 0x18, 0x50e1a5, actor, actor, 0, edi, ebp);
    index = 0xffffffffu;
    if (port_u32(&port, 0, 0x532a84) == 1 && port_u32(&port, 0, 0x532a80) == 1)
    {
        if (port_call_with(&port, 0x418130, eax, vertrix_lift_edx, actor, actor, 0, edi, ebp) == 1)
        {
            index = port_u32(&port, 0, 0x532a6c);
        }
    }
    else
    {
        edi = port_u32(&port, 0, 0x532a6c);
        index = edi;
    }
    if (index != 0xffffffffu)
    {
        port_call_with(&port, 0x4ca310, ebp - 0x18, 0x534588 + index * 4, actor, actor, 0, edi,
                       ebp);
    }
    eax = port_call_with(&port, 0x4ccfe0, port_u32(&port, ebp, -0x1cu),
                         port_u32(&port, ebp, -0x18u), actor, actor, 0, edi, ebp);
    if (eax != 0)
    {
        port_call_with(&port, 0x4adfe0, actor, vertrix_lift_edx, actor, actor, 0, edi, ebp);
        eax = port_call_with(&port, 0x4ca370, actor + 0x15c, port_u32(&port, ebp, -0x18u), actor,
                             actor, 0, edi, ebp);
        port_set16(&port, actor, 0x48, 0x50);
    }
    port_call_with(&port, 0x4cda10, eax, vertrix_lift_edx, actor, actor, 0, edi, ebp);
    return port_return(&port, port_u32(&port, ebp, -0x30u), entry->edx);
}

/* Original 0x44b810: the piece number tag eax (guard 0x515318): its text is printed (0x4cdfb0) by
 * 0x50e1c3 with 0x50e1c0 and 19, or by 0x50e1ca with the pick 0x532a6c plus 1 when it is set and,
 * with 0x532a84 and 0x532a80 both 1, ready (0x418130), or otherwise by 0x50e1d3; a change from
 * the tag's text (0x4ccfe0) is taken in (0x4ca370), bobs at 80 and ends the bob (0x4adfe0). The
 * temporaries are released (0x4cda10); the guard record's chain. */
uint32_t vertrix_port_piece_number_tag_44b810(PORT_SIGNATURE)
{
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t edi = 1;
    uint32_t edx;
    uint32_t index;
    uint32_t format = 0;
    uint32_t eax;
    uint32_t args[4];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    tag_open(&port, entry, 0x515318);
    args[0] = ebp - 0x18;
    args[1] = 0x50e1c3;
    args[2] = 0x50e1c0;
    args[3] = 0x13;
    eax = call_frame(&port, 0x4cdfb0, ebp - 0x18, vertrix_lift_edx, actor, actor, 0, edi, ebp, args,
                     4);
    edx = port_u32(&port, 0, 0x532a84);
    index = 0xffffffffu;
    if (edx == 1 && port_u32(&port, 0, 0x532a80) == 1)
    {
        if (port_call_with(&port, 0x418130, eax, edx, actor, actor, 0, edi, ebp) == 1)
        {
            index = port_u32(&port, 0, 0x532a6c);
            format = 0x50e1ca;
            edx = vertrix_lift_edx;
        }
    }
    else
    {
        edi = port_u32(&port, 0, 0x532a6c);
        index = edi;
        format = 0x50e1d3;
    }
    if (index != 0xffffffffu)
    {
        args[0] = ebp - 0x18;
        args[1] = format;
        args[2] = index + 1;
        args[3] = 0x13;
        call_frame(&port, 0x4cdfb0, ebp - 0x18, edx, actor, actor, 0, edi, ebp, args, 4);
    }
    eax = port_call_with(&port, 0x4ccfe0, port_u32(&port, ebp, -0x1cu),
                         port_u32(&port, ebp, -0x18u), actor, actor, 0, edi, ebp);
    if (eax != 0)
    {
        port_call_with(&port, 0x4ca370, actor + 0x15c, port_u32(&port, ebp, -0x18u), actor, actor,
                       0, edi, ebp);
        port_set16(&port, actor, 0x48, 0x50);
        eax = port_call_with(&port, 0x4adfe0, actor, vertrix_lift_edx, actor, actor, 0, edi, ebp);
    }
    port_call_with(&port, 0x4cda10, eax, vertrix_lift_edx, actor, actor, 0, edi, ebp);
    return port_return(&port, port_u32(&port, ebp, -0x30u), entry->edx);
}

/* The grid click shared by 0x444c80 and 0x4451d0: under a guard record the actor eax moves and
 * bobs when due (0x4ac500, 0x4ac520, 0x4ac540, 0x4ac5b0; +0x4a 0, +0x4c 5; 0x4ad530); the
 * pointer 0x558944 and 0x558946 (0x7d00 each while 0x558958) over it (0x4b0b70) gives +0x48 35;
 * a click of 0x74 (0x476480 on 0x54d640) on it (0x4764a0, 0x4b0b70) is taken (0x476320), opens
 * the entry 0x5588f8 at 100 (0x477e30), marks the grid (0x4b4510 with 1) at the click's cell
 * (0x4b4780), gives the state `next` with +0x52 10 and holds the keys (0x4766b0 with 1). The
 * guard record's chain. */
static uint32_t grid_click(PORT_SIGNATURE, uint32_t guard, uint32_t next)
{
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t eax;
    uint32_t x;
    uint32_t y;
    uint32_t args[1];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    guard_record(&port, ebp - 0x30, guard);
    port_call_with(&port, 0x4ac500, actor, 0x4ec1ec, guard, actor, 0, entry->edi, ebp);
    if (port_call_with(&port, 0x4ac520, actor, vertrix_lift_edx, guard, actor, actor, entry->edi,
                       ebp) == 1)
    {
        eax = port_call_with(&port, 0x4ac540, actor, vertrix_lift_edx, guard, actor, actor,
                             entry->edi, ebp);
        port_call_with(&port, 0x4ac5b0, actor, eax, guard, actor, actor, entry->edi, ebp);
        port_set16(&port, actor, 0x4a, 0);
        port_set16(&port, actor, 0x4c, 5);
        port_call_with(&port, 0x4ad530, actor, vertrix_lift_edx, guard, actor, actor, entry->edi,
                       ebp);
    }
    y = sign16(port_u32(&port, 0, 0x558958) != 0 ? 0x7d00 : port_u16(&port, 0, 0x558946));
    x = sign16(port_u32(&port, 0, 0x558958) != 0 ? 0x7d00 : port_u16(&port, 0, 0x558944));
    eax = port_call_with(&port, 0x4b0b70, actor, x, y, actor, actor, entry->edi, ebp);
    if ((eax & 0xff) != 0)
    {
        port_set16(&port, actor, 0x48, 0x23);
    }
    if (port_call_with(&port, 0x476480, 0x54d640, 0x74, y, actor, actor, entry->edi, ebp) != 1)
    {
        return port_return(&port, port_u32(&port, ebp, -0x30u), entry->edx);
    }
    args[0] = ebp - 0x14;
    call_frame(&port, 0x4764a0, 0x54d640, 0x74, ebp - 0x1c, ebp - 0x18, actor, entry->edi, ebp,
               args, 1);
    y = sign16(port_u16(&port, ebp, -0x18u));
    x = sign16(port_u16(&port, ebp, -0x1cu));
    eax = port_call_with(&port, 0x4b0b70, actor, x, y, ebp - 0x18, actor, entry->edi, ebp);
    if ((eax & 0xff) == 0)
    {
        return port_return(&port, port_u32(&port, ebp, -0x30u), entry->edx);
    }
    port_call_with(&port, 0x476320, 0x54d640, 0x74, 0x32, ebp - 0x18, actor, entry->edi, ebp);
    port_call_with(&port, 0x477e30, 0x5588f8, 0x64, 0x32, ebp - 0x18, actor, entry->edi, ebp);
    port_call_with(&port, 0x4b4510, actor, 1, 0x32, ebp - 0x18, actor, entry->edi, ebp);
    y = port_u32(&port, ebp, -0x18u);
    port_call_with(&port, 0x4b4780, actor, port_u32(&port, ebp, -0x1cu), y, ebp - 0x18, actor,
                   entry->edi, ebp);
    port_call_with(&port, 0x4ac8f0, actor, next, y, ebp - 0x18, actor, entry->edi, ebp);
    port_set8(&port, actor, 0x52, 0xa);
    port_call_with(&port, 0x4766b0, 0x54d640, 1, y, ebp - 0x18, actor, entry->edi, ebp);
    return port_return(&port, port_u32(&port, ebp, -0x30u), entry->edx);
}

/* Original 0x444c80: the grid click to the state 0x445090. */
uint32_t vertrix_port_grid_click_444c80(PORT_SIGNATURE)
{
    return grid_click(calls, services, globals, entry, 0x51515c, 0x445090);
}

/* Original 0x4451d0: the grid click to the state 0x445630. */
uint32_t vertrix_port_grid_click_4451d0(PORT_SIGNATURE)
{
    return grid_click(calls, services, globals, entry, 0x51518c, 0x445630);
}
