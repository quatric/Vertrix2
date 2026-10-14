#include "port_arrows.h"

/* Spawn placement, the level label, the pointer hover, actor settle waits and the list count
 * arrows. */

/* The guard record (0x4ec1ec, `guard`) of a frame routine at `record`. */
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

/* Original 0x43e920: the spawn's kind +0x95 is 5 when +0xb8 is 1, otherwise 4. With +0xb8 2 its x
 * (+0xe) is a draw (0x4826c0 on 0x598d30) below the word +8 and its y (+0x16) 0x136 plus a draw
 * below the word +0xa less 0x136; otherwise one of five places (the words of 0x4fb93c and
 * 0x4fb950, copied into the frame) is drawn. */
uint32_t vertrix_port_spawn_place_full_43e920(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x3c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t eax;
    uint32_t index;
    uint32_t i;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ecx);
    port_set32(&port, ebp, -8u, entry->edx);
    port_set32(&port, ebp, -0xcu, entry->esi);
    port_set32(&port, ebp, -0x10u, entry->edi);
    for (i = 0; i < 5; i++)
    {
        port_set32(&port, ebp - 0x38, i * 4, port_u32(&port, 0, 0x4fb93c + i * 4));
    }
    for (i = 0; i < 5; i++)
    {
        port_set32(&port, ebp - 0x24, i * 4, port_u32(&port, 0, 0x4fb950 + i * 4));
    }
    port_set8(&port, actor, 0x95, (port_u32(&port, actor, 0xb8) == 1) + 4);
    if (port_u32(&port, actor, 0xb8) != 2)
    {
        eax = port_call_with(&port, 0x4826c0, 0x598d30, 5, entry->ebx, actor, 0x4fb964, ebp - 0x10,
                             ebp);
        index = eax & 0xffff;
        eax = (eax & 0xffff0000u) | port_u16(&port, ebp + index * 4, -0x38u);
        port_set16(&port, actor, 0xe, eax);
        eax = (eax & 0xffff0000u) | port_u16(&port, ebp + index * 4, -0x24u);
        port_set16(&port, actor, 0x16, eax);
        return port_return(&port, eax, entry->edx);
    }
    eax = port_call_with(&port, 0x4826c0, 0x598d30, port_u16(&port, actor, 8), entry->ebx, actor,
                         0x4fb964, ebp - 0x10, ebp);
    port_set16(&port, actor, 0xe, eax);
    eax = ((eax & 0xffff0000u) | port_u16(&port, actor, 0xa)) - 0x136;
    eax = port_call_with(&port, 0x4826c0, 0x598d30, eax & 0xffff, entry->ebx, actor, 0x4fb964,
                         ebp - 0x10, ebp);
    eax += 0x136;
    port_set16(&port, actor, 0x16, eax);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x446440: the label of the actor's board (+0x160, its text +0x15c) is set (0x4ca370,
 * guarded 0x515210): the level +0x70, plus 0x532c2c less 4 when that is above 4, names a string
 * of 0x532c24 (0x4b7710 into the frame, released by 0x4ca210); a negative level gives 0x50e16d. */
uint32_t vertrix_port_actor_level_label_446440(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x2c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t guard = 0x515210;
    uint32_t level;
    uint32_t label;
    uint32_t text;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    guard_record(&port, ebp - 0x28, guard);
    level = port_u32(&port, 0, 0x532c2c);
    label = port_u32(&port, actor, 0x160) + 0x15c;
    if ((int32_t)level > 4)
    {
        level = level - 4 + port_u32(&port, actor, 0x70);
    }
    else
    {
        level = port_u32(&port, actor, 0x70);
    }
    if ((int32_t)level < 0)
    {
        port_call_with(&port, 0x4ca370, label, 0x50e16d, guard, label, 0, entry->edi, ebp);
        return port_return(&port, port_u32(&port, ebp, -0x28u), entry->edx);
    }
    text = port_call_with(&port, 0x4b7710, 0x532c24, ebp - 0x14, level, label, 0, entry->edi, ebp);
    port_set32(&port, ebp, -0x1cu, 1);
    port_call_with(&port, 0x4ca370, label, port_u32(&port, text, 0), level, label, 0, entry->edi,
                   ebp);
    port_set32(&port, ebp, -0x1cu, 0);
    port_call_with(&port, 0x4ca210, ebp - 0x14, 0, level, 0, 0, entry->edi, ebp);
    port_set32(&port, ebp, -0x1cu, 0);
    return port_return(&port, port_u32(&port, ebp, -0x28u), entry->edx);
}

/* Original 0x4469c0: after the timer step (at a beat 0x4ac510 with 10, 0x4ac7d0 and the state
 * 0x446b10), unless the key 0x54d640 0x74 is down, the pointer (0x558944, 0x558946; 0x7d00 while
 * 0x558958 is set) hit test 0x4b0b70 sets the hover (0x4ac710) and the state 0x446850 (0x4ac8a0,
 * 0x4ac8f0), then 0x4ac7b0 with 1. */
uint32_t vertrix_port_actor_pointer_hover_4469c0(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t ebx = entry->ebx;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t pointer;
    uint32_t x;
    uint32_t y;
    uint32_t hit;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_call_with(&port, 0x4ac500, actor, entry->edx, ebx, actor, actor, edi, ebp);
    if (port_call_with(&port, 0x4ac520, actor, vertrix_lift_edx, ebx, actor, actor, edi, ebp) == 1)
    {
        port_call_with(&port, 0x4ac510, actor, 0xa, ebx, actor, actor, edi, ebp);
        port_call_with(&port, 0x4ac7d0, actor, vertrix_lift_edx, ebx, actor, actor, edi, ebp);
        port_call_with(&port, 0x4ac8f0, actor, 0x446b10, ebx, actor, actor, edi, ebp);
    }
    result = port_call_with(&port, 0x476480, 0x54d640, 0x74, ebx, actor, actor, edi, ebp);
    if (result != 0)
    {
        return port_return(&port, result, entry->edx);
    }
    y = port_u32(&port, 0, 0x558958) != 0 ? 0x7d00 : port_u16(&port, 0, 0x558946);
    pointer = port_u32(&port, 0, 0x558958);
    x = pointer != 0 ? 0x7d00 : port_u16(&port, 0, 0x558944);
    ebx = sign16(y);
    hit = port_call_with(&port, 0x4b0b70, actor, sign16(x), ebx, pointer, actor, edi, ebp);
    port_call_with(&port, 0x4ac710, actor, (hit & 0xff) != 0, ebx, pointer, actor, edi, ebp);
    port_call_with(&port, 0x4ac8a0, actor, 0x446850, ebx, pointer, actor, edi, ebp);
    port_call_with(&port, 0x4ac8f0, actor, vertrix_lift_edx, ebx, pointer, actor, edi, ebp);
    result = port_call_with(&port, 0x4ac7b0, actor, 1, ebx, pointer, actor, edi, ebp);
    return port_return(&port, result, entry->edx);
}

/* Original 0x447600: when due (0x4ac500, 0x4ac520) the actor follows its path (0x4b6590,
 * 0x4b65a0 with 3, 0x4ac980 and 0x4b6540) and fades (+0x4f 0, +0x50 10, 0x4ad580); once the path
 * ends (0x4b6560 1) and the fade is done it takes the state 0x4476b0. */
uint32_t vertrix_port_actor_settle_wait_447600(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    static const uint32_t three[1] = {3};
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t amount;
    uint32_t result;
    uint32_t ebx;
    uint32_t ecx;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_call_with(&port, 0x4ac500, actor, entry->edx, entry->ebx, entry->ecx, actor, entry->edi,
                   ebp);
    result = port_call_with(&port, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, entry->ecx, actor,
                            entry->edi, ebp);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    amount = port_call_with(&port, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, entry->ecx, actor,
                            entry->edi, ebp);
    port_call_with(&port, 0x4ac5b0, actor, amount, entry->ebx, entry->ecx, actor, amount, ebp);
    result =
        port_call_with(&port, 0x4b6590, actor, vertrix_lift_edx, 1, entry->ecx, actor, amount, ebp);
    ecx = sign16(result);
    port_set32(&port, ebp, -0x18u, 1);
    result =
        call_frame(&port, 0x4b65a0, actor, vertrix_lift_edx, 1, ecx, actor, amount, ebp, three, 1);
    ebx = sign16(result);
    result = call_frame(&port, 0x4ac980, actor, vertrix_lift_edx, ebx, ecx, actor, amount, ebp,
                        three, 1);
    call_frame(&port, 0x4b6540, actor, sign16(result), ebx, ecx, actor, amount, ebp, three, 1);
    if (call_frame(&port, 0x4b6560, actor, vertrix_lift_edx, ebx, ecx, actor, amount, ebp, three,
                   1) == 1)
    {
        port_set32(&port, ebp, -0x18u, 0);
    }
    port_set8(&port, actor, 0x4f, 0);
    port_set16(&port, actor, 0x50, 0xa);
    result = call_frame(&port, 0x4ad580, actor, amount, ebx, ecx, actor, amount, ebp, three, 1);
    if (port_u32(&port, ebp, -0x18u) != 0 || result != 0)
    {
        return port_return(&port, result, entry->edx);
    }
    result = call_frame(&port, 0x4ac8f0, actor, 0x4476b0, ebx, ecx, actor, amount, ebp, three, 1);
    return port_return(&port, result, entry->edx);
}

/* Original 0x447830: when due the actor bobs to height 0 at speed 5 (0x4ad530) and fades (+0x4f
 * 0, +0x50 3, 0x4ad580); when that is done its state is cleared (0x4ac8f0 with 0). */
uint32_t vertrix_port_actor_bob_settle_447830(PORT_SIGNATURE)
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
    port_forward(&port, entry, 0x4ac5b0, actor, vertrix_lift_edx, amount, actor);
    port_set16(&port, actor, 0x4a, 0);
    port_set16(&port, actor, 0x4c, 5);
    port_forward(&port, entry, 0x4ad530, actor, amount, amount, actor);
    port_set8(&port, actor, 0x4f, 0);
    port_set16(&port, actor, 0x50, 3);
    result = port_forward(&port, entry, 0x4ad580, actor, amount, amount, actor);
    if (result != 0)
    {
        return port_return(&port, result, entry->edx);
    }
    result = port_forward(&port, entry, 0x4ac8f0, actor, 0, amount, actor);
    return port_return(&port, result, entry->edx);
}

/* Original 0x447e80: when due (guarded 0x515250) the actor fades (+0x4f 0, +0x50 5, 0x4ad580);
 * when done its text (+0x15c) is 0x50e174, +0x4a 0 and it takes the state 0x447af0. */
uint32_t vertrix_port_actor_label_settle_447e80(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t guard = 0x515250;
    uint32_t amount;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    guard_record(&port, ebp - 0x24, guard);
    port_call_with(&port, 0x4ac500, actor, 0x4ec1ec, guard, actor, 0, entry->edi, ebp);
    result =
        port_call_with(&port, 0x4ac520, actor, vertrix_lift_edx, guard, actor, 0, entry->edi, ebp);
    if (result != 1)
    {
        return port_return(&port, port_u32(&port, ebp, -0x24u), entry->edx);
    }
    amount =
        port_call_with(&port, 0x4ac540, actor, vertrix_lift_edx, guard, actor, 0, entry->edi, ebp);
    port_call_with(&port, 0x4ac5b0, actor, amount, guard, actor, 0, entry->edi, ebp);
    port_set8(&port, actor, 0x4f, 0);
    port_set16(&port, actor, 0x50, 5);
    result =
        port_call_with(&port, 0x4ad580, actor, vertrix_lift_edx, guard, actor, 0, entry->edi, ebp);
    if (result != 0)
    {
        return port_return(&port, port_u32(&port, ebp, -0x24u), entry->edx);
    }
    port_call_with(&port, 0x4ca370, actor + 0x15c, 0x50e174, guard, actor, 0, entry->edi, ebp);
    port_set16(&port, actor, 0x4a, 0);
    result = port_call_with(&port, 0x4ac8f0, actor, 0x447af0, guard, actor, 0, entry->edi, ebp);
    return port_return(&port, port_u32(&port, ebp, -0x24u), entry->edx);
}

/* The count arrows of 0x4495b0, 0x449710, 0x449b50 and 0x449cb0: 1 when 0x449460 restarts with the
 * dword at `table`; otherwise 0x4493d0 with 0x74 and, unless the key 0x54d640 is down (or, with
 * +0x70, the key of the word +0x64), the state `next` and the count at `counter` stepping back
 * (wrapping to 18) or on (wrapping to 0 at 18) with the sound 0x5bb254 (0x48c2b0) while `sound` is
 * 1; then 0x449390 with the dword after `table`. */
static uint32_t list_count_step(PORT_SIGNATURE, uint32_t table, uint32_t next, uint32_t counter,
                                uint32_t sound, int forward)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t ebx = entry->ebx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call_with(&port, 0x449460, actor, port_u32(&port, 0, table), ebx, actor, esi, edi,
                            ebp);
    if (result == 1)
    {
        return port_return(&port, result, entry->edx);
    }
    port_call_with(&port, 0x4493d0, actor, 0x74, ebx, actor, esi, edi, ebp);
    if (port_call_with(&port, 0x476480, 0x54d640, vertrix_lift_edx, ebx, actor, esi, edi, ebp) ==
            0 &&
        (port_u32(&port, actor, 0x70) == 0 ||
         port_call_with(&port, 0x476480, 0x54d640, port_u16(&port, actor, 0x64), ebx, actor, esi,
                        edi, ebp) == 0))
    {
        uint32_t count;
        port_call_with(&port, 0x4ac8f0, actor, next, ebx, actor, esi, edi, ebp);
        count = port_u32(&port, 0, counter);
        ebx = count;
        if (forward)
        {
            if (count >= 0x12)
            {
                esi = 0;
                port_set32(&port, 0, counter, 0);
            }
            else
            {
                edi = count + 1;
                port_set32(&port, 0, counter, edi);
            }
        }
        else if ((int32_t)count <= 0)
        {
            port_set32(&port, 0, counter, 0x12);
        }
        else
        {
            edi = count - 1;
            port_set32(&port, 0, counter, edi);
        }
        if (port_u32(&port, 0, sound) == 1)
        {
            port_call_with(&port, 0x48c2b0, 0x5bb254, vertrix_lift_edx, ebx, actor, esi, edi, ebp);
        }
    }
    result = port_call_with(&port, 0x449390, actor, port_u32(&port, 0, table + 4), ebx, actor, esi,
                            edi, ebp);
    return port_return(&port, result, entry->edx);
}

/* Original 0x4495b0: the table 0x4fbed0, the state 0x449500, the count 0x532a68 back, the sound
 * flag 0x532a80. */
uint32_t vertrix_port_list_count_back_4495b0(PORT_SIGNATURE)
{
    return list_count_step(calls, services, globals, entry, 0x4fbed0, 0x449500, 0x532a68, 0x532a80,
                           0);
}

/* Original 0x449710: the table 0x4fbee0, the state 0x449660, the count 0x532a68 on, the sound
 * flag 0x532a80. */
uint32_t vertrix_port_list_count_forward_449710(PORT_SIGNATURE)
{
    return list_count_step(calls, services, globals, entry, 0x4fbee0, 0x449660, 0x532a68, 0x532a80,
                           1);
}

/* Original 0x449b50: the table 0x4fbee8, the state 0x449aa0, the count 0x532a6c back, the sound
 * flag 0x532a7c. */
uint32_t vertrix_port_list_count_back_449b50(PORT_SIGNATURE)
{
    return list_count_step(calls, services, globals, entry, 0x4fbee8, 0x449aa0, 0x532a6c, 0x532a7c,
                           0);
}

/* Original 0x449cb0: the table 0x4fbef8, the state 0x449c00, the count 0x532a6c on, the sound
 * flag 0x532a7c. */
uint32_t vertrix_port_list_count_forward_449cb0(PORT_SIGNATURE)
{
    return list_count_step(calls, services, globals, entry, 0x4fbef8, 0x449c00, 0x532a6c, 0x532a7c,
                           1);
}
