#include "children.h"

/* The piece's child kinds, the object chain pick, the colour table, and the hover, fade and
 * label states of the menu actors. */

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
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

static uint32_t sign16(uint32_t value)
{
    return (uint32_t)(int32_t)(int16_t)value;
}

/* The child `child` takes the kind `kind`: the image 0x544ac0 + kind * 28 (0x4ac8d0), +0x15c the
 * kind, the state `state` (0x4ac8f0), +0x58 0 and 0x4ac510. */
static uint32_t child_kind(Port *port, uint32_t child, uint32_t kind, uint32_t state, uint32_t ebx,
                           uint32_t esi, uint32_t edi, uint32_t ebp)
{
    uint32_t image = 0x544ac0 + (uint32_t)(int32_t)(int8_t)kind * 0x1c;
    port_call_with(port, 0x4ac8d0, child, image, ebx, child, esi, edi, ebp);
    port_set8(port, child, 0x15c, kind);
    port_call_with(port, 0x4ac8f0, child, state, ebx, child, esi, edi, ebp);
    port_set32(port, child, 0x58, 0);
    return port_call_with(port, 0x4ac510, child, vertrix_lift_edx, ebx, child, esi, edi, ebp);
}

/* Original 0x43a410: the piece's three children (+0x15c, +0x160, +0x164) take the kinds dl, bl
 * and cl with the states 0x44c4c0, 0x44c3e0 and 0x44c450. */
uint32_t vertrix_port_piece_children_setup_43a410(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0xc
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t piece = entry->eax;
    uint32_t ebx = (entry->ebx & 0xffff0000u) | ((entry->ebx & 0xff) << 8) | (entry->ecx & 0xff);
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set8(&port, ebp, -8u, entry->edx);
    child_kind(&port, port_u32(&port, piece, 0x15c), entry->edx & 0xff, 0x44c4c0, ebx, piece,
               entry->edi, ebp);
    child_kind(&port, port_u32(&port, piece, 0x160), entry->ebx & 0xff, 0x44c3e0, ebx, piece,
               entry->edi, ebp);
    return port_return(&port,
                       child_kind(&port, port_u32(&port, piece, 0x164), entry->ecx & 0xff, 0x44c450,
                                  ebx, piece, entry->edi, ebp),
                       vertrix_lift_edx);
}

/* Original 0x43a5f0: as 0x43a410 for the children whose stack flag is 1, all with the state
 * 0x44c4c0. */
uint32_t vertrix_port_piece_children_setup_selected_43a5f0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0xc
    };
    Port port;
    uint8_t stack[BELOW + 8 + 0xc];
    uint32_t ebp = entry->esp - 4;
    uint32_t piece = entry->eax;
    uint32_t ebx = (entry->ebx & 0xffff0000u) | ((entry->ebx & 0xff) << 8) | (entry->ecx & 0xff);
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 3);
    port_set8(&port, ebp, -8u, entry->edx);
    if (port_u32(&port, ebp, 8) == 1)
    {
        eax = child_kind(&port, port_u32(&port, piece, 0x15c), entry->edx & 0xff, 0x44c4c0, ebx,
                         piece, entry->edi, ebp);
        edx = vertrix_lift_edx;
    }
    if (port_u32(&port, ebp, 0xc) == 1)
    {
        eax = child_kind(&port, port_u32(&port, piece, 0x160), entry->ebx & 0xff, 0x44c4c0, ebx,
                         piece, entry->edi, ebp);
        edx = vertrix_lift_edx;
    }
    if (port_u32(&port, ebp, 0x10) == 1)
    {
        eax = child_kind(&port, port_u32(&port, piece, 0x164), entry->ecx & 0xff, 0x44c4c0, ebx,
                         piece, entry->edi, ebp);
        edx = vertrix_lift_edx;
    }
    return port_return(&port, eax, edx);
}

/* Original 0x43ac00: the chain's object pick: after 0x43d320, a first pick (+0x474 not 1) takes
 * one of 5 (0x417fc0, 0x418000) of the set +0x488 with the list 0x4f81cc, a repeat one of
 * 0x532ca4[set]; the pick goes to 0x43d330 as the entry 0x544f90 + set * 280 + pick * 28, a
 * repeat with none picked as 0. */
uint32_t vertrix_port_object_chain_select_43ac00(PORT_SIGNATURE)
{
    Port port;
    uint32_t chain = entry->eax;
    uint32_t count = 5;
    uint32_t list;
    uint32_t pick;
    uint32_t set;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, chain, 0x474, 1);
    port_call_with(&port, 0x43d320, chain, entry->edx, entry->ebx, entry->ecx, chain, entry->edi,
                   entry->ebp);
    if (port_u32(&port, chain, 0x474) == 1)
    {
        port_set32(&port, chain, 0x474, 0);
        count = 1;
        list = port_u32(&port, port_u32(&port, chain, 0x488) * 4, 0x532ca4);
    }
    else
    {
        list = port_u32(&port, 0, 0x4f81cc);
        port_set32(&port, chain, 0x474, 1);
    }
    if (port_call_with(&port, 0x417fc0, port_u32(&port, chain, 0x488), count, entry->ebx, count,
                       chain, list, entry->ebp) == 0)
    {
        if (count == 5)
        {
            return port_return(&port, 0, entry->edx);
        }
        return port_return(
            &port, port_call_with(&port, 0x43d330, chain, 0, list, 0, chain, list, entry->ebp),
            entry->edx);
    }
    pick = port_call_with(&port, 0x418000, port_u32(&port, chain, 0x488), count, 0, count, chain,
                          list, entry->ebp);
    set = port_u32(&port, chain, 0x488);
    return port_return(&port,
                       port_call_with(&port, 0x43d330, chain, pick * 0x1c + 0x544f90 + set * 0x118,
                                      list, 0, chain, list, entry->ebp),
                       entry->edx);
}

/* Original 0x441e30: the colour table: a palette builder (0x481b20) on the masks 0xff0000, 0xff00,
 * 0xff and 0xff000000 (0x481bc0) maps the 7 by 3 colours of 0x4fb9f0 for the screen eax
 * (0x481e10) into 0x5440f8; released by 0x481b30. The guard record's chain. */
uint32_t vertrix_port_color_table_build_full_441e30(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x5c
    };
    static const uint32_t alpha[1] = {0xff000000u};
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t screen = entry->eax;
    uint32_t builder = ebp - 0x58;
    uint32_t outer;
    uint32_t inner;
    uint32_t index = 1;
    uint32_t ebx = 0xff00;
    uint32_t ecx = 0xff;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    guard_record(&port, ebp - 0x2c, 0x515120);
    port_call_with(&port, 0x481b20, builder, 0x4ec1ec, 0, 0x515120, 1, screen, ebp);
    port_set32(&port, ebp, -0x20u, 1);
    if (call_frame(&port, 0x481bc0, builder, 0xff0000, 0xff00, 0xff, 1, screen, ebp, alpha, 1) == 0)
    {
        port_call_with(&port, 0x481b30, builder, 0, 0xff00, 0xff, 1, screen, ebp);
        return port_return(&port, port_u32(&port, ebp, -0x2cu), entry->edx);
    }
    port_set32(&port, ebp, -0x18u, 0);
    while (port_u16(&port, ebp, -0x18u) < 7)
    {
        outer = port_u16(&port, ebp, -0x18u);
        for (inner = 0; (inner & 0xffff) < 3;)
        {
            index = outer * 0xc + (inner & 0xffff) * 4;
            ebx = port_u32(&port, index, 0x4fb9f0);
            inner++;
            ecx = inner;
            port_set32(
                &port, index, 0x5440f8,
                port_call_with(&port, 0x481e10, builder, screen, ebx, inner, index, screen, ebp));
        }
        port_set32(&port, ebp, -0x18u, port_u32(&port, ebp, -0x18u) + 1);
    }
    port_set32(&port, ebp, -0x20u, 0);
    port_call_with(&port, 0x481b30, builder, 0, ebx, ecx, index, 0, ebp);
    port_set32(&port, ebp, -0x20u, 0);
    return port_return(&port, port_u32(&port, ebp, -0x2cu), entry->edx);
}

/* The pointer (0x558944, 0x558946; 0x7d00 while 0x558958 is set) hit test 0x4b0b70 of the actor;
 * `pointer` gets 0x558958. */
static uint32_t pointer_hit(Port *port, uint32_t actor, uint32_t *ebx, uint32_t *pointer,
                            uint32_t esi, uint32_t edi, uint32_t ebp)
{
    uint32_t y = port_u32(port, 0, 0x558958) != 0 ? 0x7d00 : port_u16(port, 0, 0x558946);
    uint32_t x;
    *pointer = port_u32(port, 0, 0x558958);
    x = *pointer != 0 ? 0x7d00 : port_u16(port, 0, 0x558944);
    *ebx = sign16(y);
    return port_call_with(port, 0x4b0b70, actor, sign16(x), *ebx, *pointer, esi, edi, ebp);
}

/* Original 0x445900: the actor's look +0x52 is 10 while the flag 0x5bb254 (0x47f410) is 1,
 * otherwise 9; a pointer hit while it is 0 sets the height 35. With the key 0x54d640 0x74 down
 * (0x476480 1), a press there (0x4764a0, 0x4b0b70) releases it (0x476320) and runs the actor's
 * handler +0x178 on the item of its child +0x160. */
uint32_t vertrix_port_menu_item_pointer_445900(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t edi = entry->edi;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t result;
    uint32_t handler;
    uint32_t press[1];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    result =
        port_call_with(&port, 0x47f410, 0x5bb254, actor, entry->ebx, entry->ecx, actor, edi, ebp);
    port_set8(&port, vertrix_lift_edx, 0x52, (result == 1) + 9);
    if ((pointer_hit(&port, actor, &ebx, &ecx, actor, edi, ebp) & 0xff) != 0 &&
        port_call_with(&port, 0x47f410, 0x5bb254, vertrix_lift_edx, ebx, ecx, actor, edi, ebp) == 0)
    {
        port_set16(&port, actor, 0x48, 0x23);
    }
    result = port_call_with(&port, 0x476480, 0x54d640, 0x74, ebx, ecx, actor, edi, ebp);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    press[0] = ebp - 0x14;
    call_frame(&port, 0x4764a0, 0x54d640, 0x74, ebp - 0x1c, ebp - 0x18, actor, edi, ebp, press, 1);
    ebx = sign16(port_u16(&port, ebp, -0x18u));
    result = port_call_with(&port, 0x4b0b70, actor, sign16(port_u16(&port, ebp, -0x1cu)), ebx,
                            ebp - 0x18, actor, edi, ebp);
    if ((result & 0xff) == 0)
    {
        return port_return(&port, result, entry->edx);
    }
    result = port_call_with(&port, 0x476320, 0x54d640, 0x74, ebx, ebp - 0x18, actor, edi, ebp);
    handler = port_u32(&port, actor, 0x178);
    if (handler == 0)
    {
        return port_return(&port, result, entry->edx);
    }
    result = port_call_with(&port, handler, port_u32(&port, port_u32(&port, actor, 0x160), 0x15c),
                            actor, handler, ebp - 0x18, actor, edi, ebp);
    return port_return(&port, result, entry->edx);
}

/* Original 0x446b10: when due (0x4ac500, 0x4ac520 on the edx after the call) the timer restarts
 * (0x4ac510) and, at the step +0x70 0 or 2, the owner +0x10c shows (0x4b3740) or hides (0x4b37e0)
 * before its handler +0x178 runs on its child +0x160's item; then, unless the key 0x54d640 0x74 is
 * down, the pointer hit sets the hover (0x4ac710) and the state 0x446850 (0x4ac8a0, 0x4ac8f0), and
 * 0x4ac7b0 with 1. */
uint32_t vertrix_port_menu_item_owner_step_446b10(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t owner;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esi = entry->esi;
    uint32_t ebx;
    uint32_t pointer;
    uint32_t result;
    uint32_t hit;
    uint32_t x;
    uint32_t y;
    port_open(&port, calls, services, globals, entry);
    owner = port_u32(&port, actor, 0x10c);
    ebx = owner;
    port_call_with(&port, 0x4ac500, actor, actor, ebx, actor, esi, edi, ebp);
    if (port_call_with(&port, 0x4ac520, vertrix_lift_edx, vertrix_lift_edx, ebx, actor, esi, edi,
                       ebp) == 1)
    {
        uint32_t handler;
        port_call_with(&port, 0x4ac510, vertrix_lift_edx, vertrix_lift_edx, ebx, actor, esi, edi,
                       ebp);
        esi = port_u32(&port, vertrix_lift_edx, 0x70);
        if (esi == 0)
        {
            port_call_with(&port, 0x4b3740, owner, vertrix_lift_edx, ebx, actor, esi, edi, ebp);
        }
        else if (esi == 2)
        {
            port_call_with(&port, 0x4b37e0, owner, vertrix_lift_edx, ebx, actor, esi, edi, ebp);
        }
        handler = port_u32(&port, owner, 0x178);
        if (handler != 0)
        {
            port_call_with(&port, handler, port_u32(&port, port_u32(&port, owner, 0x160), 0x15c),
                           owner, ebx, actor, esi, edi, ebp);
        }
    }
    result = port_call_with(&port, 0x476480, 0x54d640, 0x74, ebx, actor, esi, edi, ebp);
    if (result != 0)
    {
        return port_return(&port, result, entry->edx);
    }
    y = port_u32(&port, 0, 0x558958) != 0 ? 0x7d00 : port_u16(&port, 0, 0x558946);
    ebx = sign16(y);
    pointer = port_u32(&port, 0, 0x558958);
    x = pointer != 0 ? 0x7d00 : port_u16(&port, 0, 0x558944);
    hit = port_call_with(&port, 0x4b0b70, actor, sign16(x), ebx, actor, pointer, edi, ebp);
    port_call_with(&port, 0x4ac710, actor, (hit & 0xff) != 0, ebx, actor, pointer, edi, ebp);
    port_call_with(&port, 0x4ac8a0, actor, 0x446850, ebx, actor, pointer, edi, ebp);
    port_call_with(&port, 0x4ac8f0, actor, vertrix_lift_edx, ebx, actor, pointer, edi, ebp);
    result = port_call_with(&port, 0x4ac7b0, actor, 1, ebx, actor, pointer, edi, ebp);
    return port_return(&port, result, entry->edx);
}

/* Original 0x447740: when due (0x4ac500, 0x4ac520) the actor steps (0x4ac540, 0x4ac5b0) and grows
 * (+0x45 16, +0x46 1, 0x4acc10); once that is done it takes the state 0x4473b0. */
uint32_t vertrix_port_actor_grow_wait_447740(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t amount;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x4ac500, actor, entry->edx, entry->ebx, actor);
    result = port_forward(&port, entry, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    amount = port_forward(&port, entry, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor);
    port_forward(&port, entry, 0x4ac5b0, actor, amount, entry->ebx, actor);
    port_set8(&port, actor, 0x45, 0x10);
    port_set16(&port, actor, 0x46, 1);
    result = port_forward(&port, entry, 0x4acc10, actor, vertrix_lift_edx, entry->ebx, actor);
    if (result != 0)
    {
        return port_return(&port, result, entry->edx);
    }
    result = port_forward(&port, entry, 0x4ac8f0, actor, 0x4473b0, entry->ebx, actor);
    return port_return(&port, result, entry->edx);
}

/* Original 0x4478f0: as 0x447600 with the path done when 0x4ac980 meets 0x4b6590's place and the
 * fade at speed 10; the state is then cleared (0x4ac8f0 with 0). */
uint32_t vertrix_port_actor_path_fade_4478f0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x24
    };
    static const uint32_t three[1] = {3};
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t amount;
    uint32_t result;
    uint32_t place;
    uint32_t ebx = entry->ebx;
    uint32_t ecx;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x18u, actor);
    port_call_with(&port, 0x4ac500, actor, entry->edx, ebx, entry->ecx, actor, entry->edi, ebp);
    result = port_call_with(&port, 0x4ac520, actor, vertrix_lift_edx, ebx, entry->ecx, actor,
                            entry->edi, ebp);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    amount = port_call_with(&port, 0x4ac540, actor, vertrix_lift_edx, ebx, entry->ecx, actor,
                            entry->edi, ebp);
    port_set32(&port, ebp, -0x1cu, amount);
    port_call_with(&port, 0x4ac5b0, actor, amount, ebx, entry->ecx, actor, entry->edi, ebp);
    result =
        port_call_with(&port, 0x4b6590, actor, vertrix_lift_edx, ebx, 1, actor, entry->edi, ebp);
    place = sign16(result);
    port_set32(&port, ebp, -0x20u, 1);
    result =
        call_frame(&port, 0x4b65a0, actor, vertrix_lift_edx, ebx, 1, actor, place, ebp, three, 1);
    ebx = sign16(result);
    ecx = call_frame(&port, 0x4ac980, actor, vertrix_lift_edx, ebx, place, actor, place, ebp, three,
                     1);
    call_frame(&port, 0x4b6540, actor, sign16(ecx), ebx, ecx, actor, place, ebp, three, 1);
    if (ecx == place)
    {
        ebx = 0;
        port_set32(&port, ebp, -0x20u, 0);
    }
    port_set8(&port, actor, 0x4f, 0);
    port_set16(&port, actor, 0x50, 0xa);
    result = call_frame(&port, 0x4ad580, actor, port_u32(&port, ebp, -0x1cu), ebx, ecx,
                        port_u32(&port, ebp, -0x20u), place, ebp, three, 1);
    if (port_u32(&port, ebp, -0x20u) != 0 || result != 0)
    {
        return port_return(&port, result, entry->edx);
    }
    result = call_frame(&port, 0x4ac8f0, port_u32(&port, ebp, -0x18u), 0, ebx, ecx, 0, place, ebp,
                        three, 1);
    return port_return(&port, result, entry->edx);
}

/* Original 0x447af0: the actor's caption: after 0x4ac510, the text (0x4ca280, empty 0x50e16e)
 * is 0x532c1c at the step +4 1 or 0x532c20 at 2 (0x4ca310); unless it is empty (0x4ccfe0 with
 * 0x50e16f) it goes to +0x15c (0x4ca370) and the actor takes the state 0x447bc0. The text is
 * released (0x4ca210); the guard record's chain. */
uint32_t vertrix_port_actor_step_caption_447af0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x30
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t text = ebp - 0x18;
    uint32_t step;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    guard_record(&port, ebp - 0x2c, 0x515228);
    port_call_with(&port, 0x4ca280, text, 0x50e16e, 0x515228, actor, 0, 1, ebp);
    port_set32(&port, ebp, -0x20u, 1);
    port_call_with(&port, 0x4ac510, actor, vertrix_lift_edx, 0x515228, actor, 0, 1, ebp);
    step = port_u32(&port, actor, 4);
    if (step == 1 || step == 2)
    {
        port_call_with(&port, 0x4ca310, text, step == 1 ? 0x532c1c : 0x532c20, actor, actor, 0, 1,
                       ebp);
    }
    if (port_call_with(&port, 0x4ccfe0, port_u32(&port, ebp, -0x18u), 0x50e16f, actor, actor, 0, 1,
                       ebp) != 0)
    {
        port_call_with(&port, 0x4ca370, actor + 0x15c, port_u32(&port, ebp, -0x18u), actor, actor,
                       0, 1, ebp);
        port_call_with(&port, 0x4ac8f0, actor, 0x447bc0, actor, actor, 0, 1, ebp);
    }
    port_set32(&port, ebp, -0x20u, 0);
    port_call_with(&port, 0x4ca210, text, 0, actor, 0, 0, 1, ebp);
    port_set32(&port, ebp, -0x20u, 0);
    return port_return(&port, port_u32(&port, ebp, -0x2cu), entry->edx);
}

/* Original 0x447f40: when due the actor steps and bobs to height 0 at speed 5 (0x4ad530); a
 * pointer hit then sets the height 35. */
uint32_t vertrix_port_actor_bob_hover_447f40(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t amount;
    uint32_t result;
    uint32_t ebx;
    uint32_t pointer;
    port_open(&port, calls, services, globals, entry);
    port_call_with(&port, 0x4ac500, actor, entry->edx, entry->ebx, actor, actor, entry->edi,
                   entry->ebp);
    if (port_call_with(&port, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor, actor,
                       entry->edi, entry->ebp) == 1)
    {
        amount = port_call_with(&port, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor, actor,
                                entry->edi, entry->ebp);
        port_call_with(&port, 0x4ac5b0, actor, amount, entry->ebx, actor, actor, entry->edi,
                       entry->ebp);
        port_set16(&port, actor, 0x4a, 0);
        port_set16(&port, actor, 0x4c, 5);
        port_call_with(&port, 0x4ad530, actor, vertrix_lift_edx, entry->ebx, actor, actor,
                       entry->edi, entry->ebp);
    }
    result = pointer_hit(&port, actor, &ebx, &pointer, actor, entry->edi, entry->ebp);
    if ((result & 0xff) != 0)
    {
        port_set16(&port, actor, 0x48, 0x23);
    }
    return port_return(&port, result, entry->edx);
}
