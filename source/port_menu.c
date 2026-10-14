#include "port_menu.h"

/* Menu key, sound tick, score table, scene change and mixer helpers. */

/* A call handing the callee esi, edi and ebp as given. */
static uint32_t call_registers(Port *port, uint32_t target, uint32_t eax, uint32_t edx,
                               uint32_t ebx, uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp)
{
    uint32_t result;
    vertrix_lift_in_esi = esi;
    vertrix_lift_in_edi = edi;
    vertrix_lift_in_ebp = ebp;
    result = lift_call_arguments(&port->env, target, eax, edx, ebx, ecx, NULL, 0);
    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    return result;
}

/* The guard record (0x4ec1ec, `guard`) of a frame routine at ebp -0x24. */
static void guard_record(Port *port, uint32_t ebp, uint32_t guard)
{
    port_set32(port, ebp, -0x24u, port->env.chain);
    port_set32(port, ebp, -0x20u, 0x4ec1ec);
    port_set32(port, ebp, -0x1cu, guard);
    port_set32(port, ebp, -0x18u, 0);
}

/* Original 0x40cff0: the portamento of the channel eax. Outside a tick (0x531b4c 0) the step +0x60
 * (four times byte +4, when set) and the target +0x64 (0x40ce80 on byte +7, +0xc and +8) are
 * taken and byte +1 loses bits 0 and 3; on a tick the period +0x24 moves by the step toward the
 * target, not past it, +0x28 follows and byte +1 gains bit 0. */
uint32_t vertrix_port_mixer_portamento_40cff0(PORT_SIGNATURE)
{
    Port port;
    uint32_t channel = entry->eax;
    int32_t period;
    int32_t target;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, 0, 0x531b4c) == 0)
    {
        if (port_u8(&port, channel, 4) != 0)
        {
            port_set32(&port, channel, 0x60, port_u8(&port, channel, 4) << 2);
        }
        result = port_forward(&port, entry, 0x40ce80, port_u8(&port, channel, 7),
                              port_u32(&port, channel, 0xc), port_u32(&port, channel, 8), channel);
        port_set32(&port, channel, 0x64, result);
        port_set8(&port, channel, 1, port_u8(&port, channel, 1) & 0xf6);
        return port_return(&port, result, entry->edx);
    }
    period = (int32_t)port_u32(&port, channel, 0x24);
    target = (int32_t)port_u32(&port, channel, 0x64);
    if (period < target)
    {
        period += (int32_t)port_u32(&port, channel, 0x60);
        port_set32(&port, channel, 0x24, (uint32_t)period);
        if (period > (int32_t)port_u32(&port, channel, 0x64))
        {
            port_set32(&port, channel, 0x24, port_u32(&port, channel, 0x64));
        }
    }
    else if (target < period)
    {
        period -= (int32_t)port_u32(&port, channel, 0x60);
        port_set32(&port, channel, 0x24, (uint32_t)period);
        if (period < (int32_t)port_u32(&port, channel, 0x64))
        {
            port_set32(&port, channel, 0x24, port_u32(&port, channel, 0x64));
        }
    }
    result = port_u32(&port, channel, 0x24);
    port_set32(&port, channel, 0x28, result);
    port_set8(&port, channel, 1, port_u8(&port, channel, 1) | 1);
    return port_return(&port, result, entry->edx);
}

/* One default record of the table: bytes 0, 1, 50, words 0, bytes 13 and 2, byte 0 at +8 and word
 * 0 at +0xa. */
static void record_default(Port *port, uint32_t record)
{
    port_set8(port, record, 0, 0);
    port_set8(port, record, 7, 2);
    port_set8(port, record, 1, 1);
    port_set16(port, record, 4, 0);
    port_set8(port, record, 6, 0xd);
    port_set8(port, record, 2, 0x32);
    port_set16(port, record, 0xa, 0);
}

/* Original 0x4120a0: the table eax: +0x7b4 0x5132e4, +0x5b8 1 and +0x5bc edx, the 122 records
 * of 12 bytes and the one at +0x5c0 set to the defaults, and the 122 dwords from +0x5cc 1. edx
 * past the records. */
uint32_t vertrix_port_record_table_init_4120a0(PORT_SIGNATURE)
{
    Port port;
    uint32_t table = entry->eax;
    uint32_t k;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, table, 0x7b4, 0x5132e4);
    port_set32(&port, table, 0x5b8, 1);
    port_set32(&port, table, 0x5bc, entry->edx);
    for (k = 0; k < 0x7a; k++)
    {
        record_default(&port, table + k * 0xc);
        port_set8(&port, table + k * 0xc, 8, 0);
        port_set32(&port, table + (k + 1) * 4, 0x5c8, 1);
    }
    record_default(&port, table + 0x5c0);
    port_set8(&port, table + 0x5c0, 8, 0);
    return port_return(&port, table, table + 0x1e8);
}

/* The pair of the sets 0x53bcd0 (8 bytes a slot) of 0x415350 and 0x4153e0: for the kind below 5
 * its two entries of the column `column` (rows of 80 bytes from 0x5336ac), for 6 those of
 * 0x5339cc and 0x533a1c, for 5 those of 0x533a6c and 0x533abc; nothing for other kinds. */
static uint32_t pair_select(Port *port, uint32_t column, uint32_t kind, uint32_t slot)
{
    uint32_t offset = column * 4;
    uint32_t first;
    uint32_t second;
    if (kind < 5)
    {
        first = offset + kind * 2 * 0x50 + 0x5336ac;
        second = offset + (kind * 2 + 1) * 0x50 + 0x5336ac;
    }
    else if (kind == 6)
    {
        first = offset + 0x5339cc;
        second = offset + 0x533a1c;
    }
    else if (kind == 5)
    {
        first = offset + 0x533a6c;
        second = offset + 0x533abc;
    }
    else
    {
        return kind;
    }
    port_set32(port, slot, 0x53bcd0, port_u32(port, first, 0));
    second = port_u32(port, second, 0);
    port_set32(port, slot, 0x53bcd4, second);
    return second;
}

/* Original 0x415350: the column eax and kind edx into the slot edx. */
uint32_t vertrix_port_table_pair_select_415350(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = pair_select(&port, entry->eax, entry->edx, entry->edx * 8);
    return port_return(&port, result, entry->edx * 8);
}

/* Original 0x4153e0: the column eax and kind edx into the slot ebx. */
uint32_t vertrix_port_table_pair_select_4153e0(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = pair_select(&port, entry->eax, entry->edx, entry->ebx * 8);
    return port_return(&port, result, entry->ebx * 8);
}

/* The sound tick of 0x417060 and 0x417150: the sound 0x532bb0 played by 0x482a60 on the channel of
 * the player `player` (0x533164) at the volume 0x532b9c; the sound counts on modulo 8. */
static uint32_t sound_tick(Port *port, const LiftEntry *entry, uint32_t player, uint32_t ecx)
{
    uint32_t result;
    uint32_t next;
    result = port_forward(port, entry, 0x482a60, port_u8(port, 0, 0x532bb0),
                          port_u32(port, port_u32(port, 0, player) * 4, 0x533164),
                          port_u32(port, 0, 0x532b9c), ecx);
    next = port_u32(port, 0, 0x532bb0) + 1;
    port_set32(port, 0, 0x532bb0, next);
    if (next == 8)
    {
        port_set32(port, 0, 0x532bb0, 0);
    }
    return result;
}

/* Original 0x417060: the volume 0x532bb8 from 0x4ce080, 0x532b9c it scaled to 64 over 100, then
 * 0x4828f0, and the tick on the player 0x532d88. */
uint32_t vertrix_port_sound_volume_tick_417060(PORT_SIGNATURE)
{
    Port port;
    uint32_t volume;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    volume = port_forward(&port, entry, 0x4ce080, entry->eax, entry->edx, entry->ebx, entry->ecx);
    port_set32(&port, 0, 0x532bb8, volume);
    port_set32(&port, 0, 0x532b9c, (volume << 6) / 0x64);
    port_forward(&port, entry, 0x4828f0, (volume << 6) / 0x64, (volume << 6) % 0x64, 0x64,
                 entry->ecx);
    result = sound_tick(&port, entry, 0x532d88, entry->ecx);
    return port_return(&port, result, entry->edx);
}

/* Original 0x417150: the tick on the player 0x532bac. */
uint32_t vertrix_port_sound_tick_417150(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = sound_tick(&port, entry, 0x532bac, entry->ecx);
    return port_return(&port, result, entry->edx);
}

/* The two keys of 0x4172c0 and 0x4173d0: the key `key` gives (from 0x4174f0 or 0x417550) and its
 * pair (0x4175b0 or 0x417620), read on the player eax's channel (0x533164) by 0x4829c0 at the
 * volume 0x532b9c; 0x482a40 with the first when it is down and with the pair when it is (the
 * second check on the edx the first call leaves). */
static uint32_t player_key_pair(PORT_SIGNATURE, uint32_t key, uint32_t pair)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t player = entry->eax;
    uint32_t first;
    uint32_t down;
    uint32_t other;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    first = call_registers(&port, key, player, entry->edx, entry->ebx, 0, player, entry->edi, ebp) &
            0xff;
    result = call_registers(&port, pair, first, vertrix_lift_edx, entry->ebx, first, player,
                            entry->edi, ebp);
    port_set8(&port, ebp, -0x1cu, result);
    port_set8(&port, ebp, -0x18u, result);
    down = call_registers(&port, 0x4829c0, first, port_u32(&port, player * 4, 0x533164),
                          port_u32(&port, 0, 0x532b9c), first, player, entry->edi, ebp);
    other = call_registers(&port, 0x4829c0, port_u8(&port, ebp, -0x1cu),
                           port_u32(&port, player * 4, 0x533164), port_u32(&port, 0, 0x532b9c),
                           first, player, down, ebp);
    result = other;
    if (down == 1)
    {
        result = call_registers(&port, 0x482a40, first, other, port_u32(&port, 0, 0x532b9c), first,
                                player, down, ebp);
        other = vertrix_lift_edx;
    }
    if (other == 1)
    {
        result = call_registers(&port, 0x482a40, port_u8(&port, ebp, -0x18u), other,
                                port_u32(&port, 0, 0x532b9c), first, player, down, ebp);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x4172c0: the keys of 0x4174f0 and 0x4175b0. */
uint32_t vertrix_port_player_key_pair_4172c0(PORT_SIGNATURE)
{
    return player_key_pair(calls, services, globals, entry, 0x4174f0, 0x4175b0);
}

/* Original 0x4173d0: the keys of 0x417550 and 0x417620. */
uint32_t vertrix_port_player_key_pair_4173d0(PORT_SIGNATURE)
{
    return player_key_pair(calls, services, globals, entry, 0x417550, 0x417620);
}

/* Original 0x417460: the keys 4 and 5 of the player eax, as 0x417350. */
uint32_t vertrix_port_player_keys_check_417460(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x18
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t offset = entry->eax * 4;
    uint32_t first;
    uint32_t second;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set8(&port, ebp, -0x14u, 5);
    first = call_registers(&port, 0x4829c0, 4, port_u32(&port, offset, 0x533164),
                           port_u32(&port, 0, 0x532b9c), offset, entry->esi, entry->edi, ebp);
    second = call_registers(&port, 0x4829c0, 5, port_u32(&port, offset, 0x533164),
                            port_u32(&port, 0, 0x532b9c), offset, first, entry->edi, ebp);
    result = second;
    if (first == 1)
    {
        result = call_registers(&port, 0x482a40, 4, second, port_u32(&port, 0, 0x532b9c), offset,
                                first, entry->edi, ebp);
        second = vertrix_lift_edx;
    }
    if (second == 1)
    {
        result = call_registers(&port, 0x482a40, port_u8(&port, ebp, -0x14u), second,
                                port_u32(&port, 0, 0x532b9c), offset, first, entry->edi, ebp);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x4177b0: the place of the score eax in the high score table (five dwords from
 * 0x533294, names from 0x5332a8): the first it beats; the lower entries move down one (names by
 * 0x4ca310), the place gets the score and the empty name 0x50d678 (0x4ca370). al the place, or
 * 0xff when it beats none. */
uint32_t vertrix_port_high_score_insert_4177b0(PORT_SIGNATURE)
{
    Port port;
    uint32_t score = entry->eax;
    int8_t place = 0;
    int8_t below;
    uint32_t ebx;
    uint32_t offset;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    while (place < 5 && score <= port_u32(&port, (uint32_t)(int32_t)place * 4, 0x533294))
    {
        place++;
    }
    if (place >= 5)
    {
        return port_return(&port, 0xff, entry->edx);
    }
    for (below = 3; below >= place; below--)
    {
        offset = (uint32_t)(int32_t)below * 4;
        ebx = (entry->ebx & 0xffff0000u) | ((uint32_t)(uint8_t)below << 8) | (uint8_t)place;
        port_forward(&port, entry, 0x4ca310, offset + 4 + 0x5332a8, offset + 0x5332a8, ebx, offset);
        port_set32(&port, offset, 0x533298, port_u32(&port, offset, 0x533294));
    }
    offset = (uint32_t)(int32_t)place * 4;
    ebx = (entry->ebx & 0xffff0000u) | ((uint32_t)(uint8_t)below << 8) | (uint8_t)place;
    result = port_forward(&port, entry, 0x4ca370, offset + 0x5332a8, 0x50d678, ebx, offset);
    port_set32(&port, offset, 0x533294, score);
    return port_return(&port, (result & 0xffffff00u) | (uint8_t)place, entry->edx);
}

/* Original 0x419f80: 0x4cf850 on the window eax; with the edx it leaves 1 and the game not running
 * (0x5328bc): 0x4ccdd0 with 3, 0x4b7cd0, the game running (0x5328bc and 0x532a38 1), the import
 * 0x4f1a9c with 0, the cursor hidden (0x4f1ae4 with 0 until it goes negative) and 0x40afc0 with
 * 0; with another edx and the game running: not running, 0x4ccdd0 with 7 and 0x40afc0 with 1. */
uint32_t vertrix_port_window_activate_419f80(PORT_SIGNATURE)
{
    Port port;
    uint32_t window = entry->eax;
    uint32_t zero[1] = {0};
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_forward(&port, entry, 0x4cf850, window, entry->edx, entry->ebx, window);
    if (vertrix_lift_edx == 1)
    {
        uint32_t running = port_u32(&port, 0, 0x5328bc);
        if (running != 0)
        {
            return port_return(&port, result, vertrix_lift_edx);
        }
        result = port_call_with(&port, 0x4ccdd0, window, 3, entry->ebx, window, 0, 1, entry->ebp);
        result = port_call_with(&port, 0x4b7cd0, result, vertrix_lift_edx, entry->ebx, window, 0, 1,
                                entry->ebp);
        port_set32(&port, 0, 0x5328bc, 1);
        port_set32(&port, 0, 0x532a38, 1);
        vertrix_lift_in_esi = 0;
        vertrix_lift_in_edi = 1;
        vertrix_lift_in_ebp = entry->ebp;
        result = lift_call_arguments(&port.env, 0x4f1a9c, result, vertrix_lift_edx, entry->ebx,
                                     window, zero, 1);
        do
        {
            vertrix_lift_in_esi = 0;
            vertrix_lift_in_edi = 1;
            vertrix_lift_in_ebp = entry->ebp;
            result = lift_call_arguments(&port.env, 0x4f1ae4, result, vertrix_lift_edx, 0, window,
                                         zero, 1);
        } while ((int32_t)result >= 0 && !port.env.failed);
        vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
        result = port_call_with(&port, 0x40afc0, 0, vertrix_lift_edx, 0, window, 0, 1, entry->ebp);
        return port_return(&port, result, vertrix_lift_edx);
    }
    if (port_u32(&port, 0, 0x5328bc) != 1)
    {
        return port_return(&port, result, vertrix_lift_edx);
    }
    port_set32(&port, 0, 0x5328bc, 0);
    port_forward(&port, entry, 0x4ccdd0, window, 7, 0, window);
    result = port_forward(&port, entry, 0x40afc0, 1, vertrix_lift_edx, 0, window);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x41b5e0: under the guard record 0x514004, the scene eax handed to 0x41c400 (0x418840)
 * when 0x532a34 is 1; otherwise 0x41b310 with 0x423600, byte +0xc8 1, 0x418840 and 0x418820 with
 * 0x41b820. eax the chain it restores. */
uint32_t vertrix_port_scene_enter_41b5e0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t scene = entry->eax;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    guard_record(&port, ebp, 0x514004);
    if (port_u8(&port, 0, 0x532a34) == 1)
    {
        call_registers(&port, 0x418840, scene, 0x41c400, 0x514004, scene, 0, entry->edi, ebp);
    }
    else
    {
        call_registers(&port, 0x41b310, scene, 0x423600, 0x514004, scene, 0, entry->edi, ebp);
        port_set8(&port, scene, 0xc8, 1);
        call_registers(&port, 0x418840, scene, vertrix_lift_edx, 0x514004, scene, 0, entry->edi,
                       ebp);
        call_registers(&port, 0x418820, scene, 0x41b820, 0x514004, scene, 0, entry->edi, ebp);
    }
    return port_return(&port, port_u32(&port, ebp, -0x24u), entry->edx);
}

/* The scene ends of 0x41d470 and 0x41d510 under the guard record `guard`: 0x41ab90, 0x41ac20 and
 * 0x41a9e0 on the scene, 0x4719e0, the panels (0x45f9f0), 0x45e8f0, 0x45e910, 0x45ea80, 0x477ed0
 * on 0x5588f8 with 0, 0x4766b0 on 0x54d640, the next scene `next` (0x418840), and 0x41d5b0 for
 * `after`. eax the chain it restores. */
static uint32_t scene_leave(PORT_SIGNATURE, uint32_t guard, uint32_t next, int after)
{
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t scene = entry->eax;
    uint32_t result;
    static const uint32_t chain[] = {0x4719e0, 0x45f9f0, 0x45e8f0, 0x45e910, 0x45ea80};
    unsigned k;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    guard_record(&port, ebp, guard);
    call_registers(&port, 0x41ab90, scene, 0x4ec1ec, guard, scene, 0, entry->edi, ebp);
    call_registers(&port, 0x41ac20, scene, vertrix_lift_edx, guard, scene, 0, entry->edi, ebp);
    result =
        call_registers(&port, 0x41a9e0, scene, vertrix_lift_edx, guard, scene, 0, entry->edi, ebp);
    for (k = 0; k < 5; k++)
    {
        result = call_registers(&port, chain[k], result, vertrix_lift_edx, guard, scene, 0,
                                entry->edi, ebp);
    }
    call_registers(&port, 0x477ed0, 0x5588f8, 0, guard, scene, 0, entry->edi, ebp);
    call_registers(&port, 0x4766b0, 0x54d640, vertrix_lift_edx, guard, scene, 0, entry->edi, ebp);
    call_registers(&port, 0x418840, scene, next, guard, scene, 0, entry->edi, ebp);
    if (after)
    {
        call_registers(&port, 0x41d5b0, scene, vertrix_lift_edx, guard, scene, 0, entry->edi, ebp);
    }
    return port_return(&port, port_u32(&port, ebp, -0x24u), entry->edx);
}

/* Original 0x41d470: guard 0x514080, next 0x421f10, then 0x41d5b0. */
uint32_t vertrix_port_scene_leave_41d470(PORT_SIGNATURE)
{
    return scene_leave(calls, services, globals, entry, 0x514080, 0x421f10, 1);
}

/* Original 0x41d510: guard 0x514084, next 0x41c6d0. */
uint32_t vertrix_port_scene_leave_41d510(PORT_SIGNATURE)
{
    return scene_leave(calls, services, globals, entry, 0x514084, 0x41c6d0, 0);
}

/* Original 0x4122f0: under the guard record 0x5132b8, a reader on the frame (0x48a620); when
 * 0x48a710 opens it, 0x4121e0 reads the object eax from it and 0x48a8c0 closes it; 0x48a670 ends
 * it. eax the chain it restores. */
uint32_t vertrix_port_object_load_4122f0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x13c
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t object = entry->eax;
    uint32_t reader = ebp - 0x138;
    uint32_t ebx;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    guard_record(&port, ebp, 0x5132b8);
    call_registers(&port, 0x48a620, reader, entry->edx, 0x4ec1ec, object, 0x5132b8, 0, ebp);
    port_set32(&port, ebp, -0x18u, 1);
    ebx = port_u32(&port, 0, 0x5466c8);
    if (call_registers(&port, 0x48a710, reader, vertrix_lift_edx, ebx, object, 0x5132b8, 0, ebp) ==
        1)
    {
        call_registers(&port, 0x4121e0, object, reader, ebx, object, 0x5132b8, 0, ebp);
        call_registers(&port, 0x48a8c0, reader, vertrix_lift_edx, ebx, object, 0x5132b8, 0, ebp);
    }
    port_set32(&port, ebp, -0x18u, 0);
    call_registers(&port, 0x48a670, reader, 0, ebx, 0, 0x5132b8, 0, ebp);
    port_set32(&port, ebp, -0x18u, 0);
    return port_return(&port, port_u32(&port, ebp, -0x24u), vertrix_lift_edx);
}
