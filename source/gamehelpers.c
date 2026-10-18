#include "gamehelpers.h"

/* Device mode, timer, file, button, table and scene helpers. */

/* A call handing the callee esi, edi and ebp as given, and `count` stack arguments (the nearest
 * to the stack pointer first). */
static uint32_t call_registers(Port *port, uint32_t target, uint32_t eax, uint32_t edx,
                               uint32_t ebx, uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                               const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

/* Original 0x40afc0: switch the device mode 0x52f148 to eax: the lock state by 0x40ef40 into a
 * local, the mode kept (the edx that call leaves), then 0x40ede0 to lock in mode 1 when unlocked
 * or 0x40ee30 to unlock otherwise when locked. */
uint32_t vertrix_port_mode_switch_call_40afc0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0xc
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t mode = entry->eax;
    uint32_t result;
    uint32_t locked;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    if (mode == port_u32(&port, 0, 0x52f148))
    {
        return port_return(&port, mode, entry->edx);
    }
    result = call_registers(&port, 0x40ef40, ebp - 8, mode, entry->ebx, entry->ecx, entry->esi,
                            entry->edi, ebp, NULL, 0);
    port_set32(&port, 0, 0x52f148, vertrix_lift_edx);
    locked = port_u32(&port, ebp, -8u);
    if (port_u32(&port, 0, 0x52f148) == 1)
    {
        if (locked == 0)
        {
            result = call_registers(&port, 0x40ede0, result, vertrix_lift_edx, entry->ebx,
                                    entry->ecx, entry->esi, entry->edi, ebp, NULL, 0);
        }
    }
    else if (locked == 1)
    {
        result = call_registers(&port, 0x40ee30, result, vertrix_lift_edx, entry->ebx, entry->ecx,
                                entry->esi, entry->edi, ebp, NULL, 0);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x40b980: the timer tick: the time since 0x52f900 (the import 0x4f1bf8) added to
 * 0x52f904; a whole period 0x52f908 is taken off and calls the handler 0x52f1f8 when set; the time
 * kept (the edx the handler leaves). 0. */
uint32_t vertrix_port_timer_tick_40b980(PORT_SIGNATURE)
{
    Port port;
    uint32_t now;
    uint32_t elapsed;
    uint32_t total;
    uint32_t period;
    port_open(&port, calls, services, globals, entry);
    now = port_forward(&port, entry, 0x4f1bf8, entry->eax, entry->edx, entry->ebx, entry->ecx);
    elapsed = now - port_u32(&port, 0, 0x52f900);
    total = port_u32(&port, 0, 0x52f904) + elapsed;
    port_set32(&port, 0, 0x52f904, total);
    period = port_u32(&port, 0, 0x52f908);
    if ((int32_t)total >= (int32_t)period)
    {
        port_set32(&port, 0, 0x52f904, total - period);
        if (port_u32(&port, 0, 0x52f1f8) != 0)
        {
            call_registers(&port, port_u32(&port, 0, 0x52f1f8), elapsed, now, total, entry->ecx,
                           period, total - period, entry->ebp, NULL, 0);
            now = vertrix_lift_edx;
        }
    }
    port_set32(&port, 0, 0x52f900, now);
    return port_return(&port, 0, entry->edx);
}

/* Original 0x40bac0: 2 for a value over 32, otherwise 0. */
uint32_t vertrix_port_value_over_32_40bac0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, entry->eax > 0x20 ? 2 : 0, entry->edx);
}

/* Original 0x40c220: read edx bytes into eax from the file 0x52f90c by 0x4ebec0; a short read
 * clears them by 0x4eb5c0. 0. */
uint32_t vertrix_port_file_read_exact_40c220(PORT_SIGNATURE)
{
    Port port;
    uint32_t buffer = entry->eax;
    uint32_t size = entry->edx;
    uint32_t file;
    port_open(&port, calls, services, globals, entry);
    file = port_u32(&port, 0, 0x52f90c);
    if (call_registers(&port, 0x4ebec0, buffer, 1, size, file, size, buffer, entry->ebp, NULL, 0) !=
        size)
    {
        call_registers(&port, 0x4eb5c0, buffer, 0, size, file, size, buffer, entry->ebp, NULL, 0);
    }
    return port_return(&port, 0, vertrix_lift_edx);
}

/* Original 0x40c2a0: read a word into eax from the file 0x52f90c, cleared on a short read. 0. */
uint32_t vertrix_port_file_read_word_40c2a0(PORT_SIGNATURE)
{
    Port port;
    uint32_t buffer = entry->eax;
    uint32_t file;
    port_open(&port, calls, services, globals, entry);
    file = port_u32(&port, 0, 0x52f90c);
    if (call_registers(&port, 0x4ebec0, buffer, 1, 2, file, buffer, entry->edi, entry->ebp, NULL,
                       0) != 2)
    {
        call_registers(&port, 0x4eb5c0, buffer, 0, 2, file, buffer, entry->edi, entry->ebp, NULL,
                       0);
    }
    return port_return(&port, 0, entry->edx);
}

/* Original 0x40caa0: mark the channel eax (24 bytes each from 0x52f914) by bit 0 of its byte
 * +0x1a; 1 past the count 0x52fc18, otherwise 0. */
uint32_t vertrix_port_channel_mark_40caa0(PORT_SIGNATURE)
{
    Port port;
    uint32_t channel = entry->eax;
    port_open(&port, calls, services, globals, entry);
    if (channel >= port_u32(&port, 0, 0x52fc18))
    {
        return port_return(&port, 1, entry->edx);
    }
    port_set8(&port, channel * 24, 0x52f92e, port_u8(&port, channel * 24, 0x52f92e) | 1);
    return port_return(&port, 0, entry->edx);
}

/* Original 0x40ed70: with bit 7 of 0x531b44, stop (0x40add0) and release (0x40ad50) each of the
 * 0x531b48 handles of 0x531ac4 (the count going on from the edx each release leaves), clear
 * 0x53043c (0x1744 bytes by 0x4eb5c0), then 0x40ac10 with 0 and 0x40ac20 with 125; 0, or 3. */
uint32_t vertrix_port_flagged_table_call_40ed70(PORT_SIGNATURE)
{
    Port port;
    uint32_t index = 0;
    uint32_t offset = 0;
    port_open(&port, calls, services, globals, entry);
    if ((port_u8(&port, 0, 0x531b44) & 0x80) == 0)
    {
        return port_return(&port, 3, entry->edx);
    }
    if ((int32_t)port_u32(&port, 0, 0x531b48) > 0)
    {
        do
        {
            port_forward(&port, entry, 0x40add0, port_u32(&port, offset, 0x531ac4), index, offset,
                         entry->ecx);
            port_forward(&port, entry, 0x40ad50, port_u32(&port, offset, 0x531ac4),
                         vertrix_lift_edx, offset, entry->ecx);
            offset += 4;
            index = vertrix_lift_edx + 1;
        } while ((int32_t)index < (int32_t)port_u32(&port, 0, 0x531b48));
    }
    port_forward(&port, entry, 0x4eb5c0, 0x53043c, 0, 0x1744, entry->ecx);
    port_forward(&port, entry, 0x40ac10, 0, vertrix_lift_edx, 0x1744, entry->ecx);
    port_forward(&port, entry, 0x40ac20, 0x7d, vertrix_lift_edx, 0x1744, entry->ecx);
    return port_return(&port, 0, entry->edx);
}

/* Original 0x4125e0: the field ebx of the record edx (12 bytes each) of the table eax: 0 and 1
 * signed bytes, 2 a byte, 3 the signed word +4, 4 the byte +6, 5 the signed byte +7, 6 the
 * signed byte +8, 7 the word +0xa; 0 for others. edx the record. */
uint32_t vertrix_port_record_field_4125e0(PORT_SIGNATURE)
{
    Port port;
    uint32_t record = entry->eax + entry->edx * 12;
    uint32_t value = 0;
    port_open(&port, calls, services, globals, entry);
    switch (entry->ebx)
    {
        case 0:
            value = (uint32_t)(int32_t)(int8_t)port_u8(&port, record, 0);
            break;
        case 1:
            value = (uint32_t)(int32_t)(int8_t)port_u8(&port, record, 1);
            break;
        case 2:
            value = port_u8(&port, record, 2);
            break;
        case 3:
            value = (uint32_t)((int32_t)port_u32(&port, record, 2) >> 16);
            break;
        case 4:
            value = port_u8(&port, record, 6);
            break;
        case 5:
            value = (uint32_t)((int32_t)port_u32(&port, record, 4) >> 24);
            break;
        case 6:
            value = (uint32_t)((int32_t)port_u32(&port, record, 5) >> 24);
            break;
        case 7:
            value = port_u16(&port, record, 0xa);
            break;
        default:
            break;
    }
    return port_return(&port, value, record);
}

/* The guard record (0x4ec1ec, `guard`) of a frame routine at ebp -0x24. */
static void guard_record(Port *port, uint32_t ebp, uint32_t guard)
{
    port_set32(port, ebp, -0x24u, port->env.chain);
    port_set32(port, ebp, -0x20u, 0x4ec1ec);
    port_set32(port, ebp, -0x1cu, guard);
    port_set32(port, ebp, -0x18u, 0);
}

/* Original 0x416900: 0x416500 on eax inside the critical section 0x558c9c (the imports 0x4f1b48
 * and 0x4f1c40) under the guard record 0x513b84; eax the chain it restores. */
uint32_t vertrix_port_locked_call_416900(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t object = entry->eax;
    uint32_t pushed[1] = {0x558c9c};
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    guard_record(&port, ebp, 0x513b84);
    call_registers(&port, 0x4f1b48, ebp - 0x24, 0x4ec1ec, object, 0x513b84, 0, entry->edi, ebp,
                   pushed, 1);
    result = call_registers(&port, 0x416500, object, vertrix_lift_edx, object, 0x513b84, 0,
                            entry->edi, ebp, NULL, 0);
    call_registers(&port, 0x4f1c40, result, vertrix_lift_edx, object, 0x513b84, 0, entry->edi, ebp,
                   pushed, 1);
    return port_return(&port, port_u32(&port, ebp, -0x24u), entry->edx);
}

/* Original 0x417350: the two keys of the player eax (0x533164) read by 0x4829c0 (0 and 1, with
 * 0x532b9c); 0x482a40 with 0 when the first is down and with 1 when the second is (the second
 * check on the edx the first call leaves). */
uint32_t vertrix_port_player_keys_check_417350(PORT_SIGNATURE)
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
    port_set8(&port, ebp, -0x14u, 1);
    first =
        call_registers(&port, 0x4829c0, 0, port_u32(&port, offset, 0x533164),
                       port_u32(&port, 0, 0x532b9c), offset, entry->esi, entry->edi, ebp, NULL, 0);
    second = call_registers(&port, 0x4829c0, 1, port_u32(&port, offset, 0x533164),
                            port_u32(&port, 0, 0x532b9c), offset, first, entry->edi, ebp, NULL, 0);
    result = second;
    if (first == 1)
    {
        result = call_registers(&port, 0x482a40, 0, second, port_u32(&port, 0, 0x532b9c), offset,
                                first, entry->edi, ebp, NULL, 0);
        second = vertrix_lift_edx;
    }
    if (second == 1)
    {
        result =
            call_registers(&port, 0x482a40, port_u8(&port, ebp, -0x14u), second,
                           port_u32(&port, 0, 0x532b9c), offset, first, entry->edi, ebp, NULL, 0);
    }
    return port_return(&port, result, entry->edx);
}

/* The first of the four buttons from `first` that 0x4828a0 finds pressed (the button al first,
 * unless it is `first`; the others skipped while dh, kept in the edx each call leaves, names
 * them); al that button, or `first` + 1 when none is. */
static uint32_t button_pick(PORT_SIGNATURE, uint32_t first)
{
    Port port;
    uint32_t eax = entry->eax;
    uint32_t edx = (entry->edx & 0xffff0000u) | ((entry->eax & 0xff) << 8) | (first + 1);
    uint32_t button;
    port_open(&port, calls, services, globals, entry);
    for (button = first; button < first + 4; button++)
    {
        uint32_t named = button == first ? (eax & 0xff) : ((edx >> 8) & 0xff);
        if (named == button)
        {
            continue;
        }
        eax = port_forward(&port, entry, 0x4828a0, button, edx, entry->ebx, entry->ecx);
        edx = vertrix_lift_edx;
        if (eax == 1)
        {
            edx = (edx & 0xffffff00u) | button;
            break;
        }
    }
    return port_return(&port, (eax & 0xffffff00u) | (edx & 0xff), entry->edx);
}

/* Original 0x4175b0: the buttons 0 to 3. */
uint32_t vertrix_port_button_pick_4175b0(PORT_SIGNATURE)
{
    return button_pick(calls, services, globals, entry, 0);
}

/* Original 0x417620: the buttons 4 to 7. */
uint32_t vertrix_port_button_pick_417620(PORT_SIGNATURE)
{
    return button_pick(calls, services, globals, entry, 4);
}

/* Original 0x417f50: feed the character of the text [eax] (after 0x4ca710; the text the edx each
 * call leaves) to the matcher at 0x540010 (position 0x540014): a mismatch restarts it
 * (0x417f40) and tries again; 1 with 0x417f40 when the whole word matched, otherwise 0. */
uint32_t vertrix_port_matcher_feed_417f50(PORT_SIGNATURE)
{
    Port port;
    uint32_t text;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t position;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x4ca710, entry->eax, entry->eax, entry->ebx, entry->ecx);
    text = vertrix_lift_edx;
    ebx = port_u32(&port, text, 0);
    ebx = (ebx & 0xffffff00u) | port_u8(&port, ebx, 0);
    position = port_u32(&port, 0, 0x540014);
    ecx = port_u32(&port, 0, 0x540010);
    ecx = (ecx & 0xffffff00u) | port_u8(&port, ecx + position, 0);
    if ((ebx & 0xff) != (ecx & 0xff))
    {
        uint32_t character;
        port_forward(&port, entry, 0x417f40, position, text, ebx, ecx);
        text = vertrix_lift_edx;
        ebx = (ebx & 0xffffff00u) | port_u8(&port, port_u32(&port, text, 0), 0);
        character = port_u8(&port, port_u32(&port, 0, 0x540010) + port_u32(&port, 0, 0x540014), 0);
        if ((ebx & 0xff) != character)
        {
            goto check;
        }
    }
    port_set32(&port, 0, 0x540014, port_u32(&port, 0, 0x540014) + 1);
check:
    position = port_u32(&port, 0, 0x540014);
    if (position == port_u32(&port, port_u32(&port, 0, 0x540010) - 0xc, 4))
    {
        port_forward(&port, entry, 0x417f40, port_u32(&port, 0, 0x540010) - 0xc, position, ebx,
                     ecx);
        return port_return(&port, 1, entry->edx);
    }
    return port_return(&port, 0, entry->edx);
}

/* Original 0x418970: 0x4d4990 on the scene eax under the guard record 0x513f80; unless it gives
 * -1, the handler 0x41a080 by 0x418870 and 0x418840, and 0. */
uint32_t vertrix_port_scene_open_418970(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t scene = entry->eax;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    guard_record(&port, ebp, 0x513f80);
    result = call_registers(&port, 0x4d4990, scene, entry->edx, 0x4ec1ec, scene, 0x513f80, 0, ebp,
                            NULL, 0);
    if (result == 0xffffffffu)
    {
        return port_return(&port, result, vertrix_lift_edx);
    }
    call_registers(&port, 0x418870, scene, 0x41a080, 0x4ec1ec, scene, 0x513f80, 0, ebp, NULL, 0);
    call_registers(&port, 0x418840, scene, vertrix_lift_edx, 0x4ec1ec, scene, 0x513f80, 0, ebp,
                   NULL, 0);
    return port_return(&port, 0, vertrix_lift_edx);
}

/* Original 0x419ef0: the game teardown: 0x4b7c90, then the devices, sounds, palettes and tables
 * released in turn (each call on the edx the one before leaves). */
uint32_t vertrix_port_game_teardown_419ef0(PORT_SIGNATURE)
{
    static const uint32_t steps[][2] = {
        {0x4856d0, 0x5b9c50}, {0x45e260, 0},        {0x477320, 0x55608c}, {0x43f3f0, 0},
        {0x442110, 0},        {0x477d10, 0x5588f8}, {0x482740, 0x598d30}, {0x482740, 0x598d48},
        {0x476cc0, 0x5536c8}, {0x476cc0, 0x553798}, {0x486e20, 0x5b9c50}};
    Port port;
    uint32_t result;
    unsigned step;
    port_open(&port, calls, services, globals, entry);
    result = port_forward(&port, entry, 0x4b7c90, entry->eax, entry->eax, entry->ebx, entry->ecx);
    for (step = 0; step < sizeof steps / sizeof steps[0]; step++)
    {
        result =
            port_forward(&port, entry, steps[step][0], steps[step][1] ? steps[step][1] : result,
                         vertrix_lift_edx, entry->ebx, entry->ecx);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x41a240: show the language 0x532b50 by 0x418ce0 on the thread window's control
 * (0x4ce740 +4 +0x1c); keep it at 0x532b4c when that works, otherwise show 0x532b4c again; then
 * the handler 0x41a540 by 0x418840. */
uint32_t vertrix_port_language_apply_41a240(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t language;
    uint32_t window;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    language = port_u8(&port, 0, 0x532b50);
    window =
        port_forward_esi(&port, entry, 0x4ce740, object, entry->edx, object, entry->ecx, language);
    result =
        port_forward_esi(&port, entry, 0x418ce0, port_u32(&port, port_u32(&port, window, 4), 0x1c),
                         language, object, entry->ecx, language);
    if (result != 0)
    {
        port_set32(&port, 0, 0x532b4c, port_u32(&port, 0, 0x532b50));
    }
    else
    {
        language = port_u8(&port, 0, 0x532b4c);
        window = port_forward_esi(&port, entry, 0x4ce740, result, vertrix_lift_edx, object,
                                  entry->ecx, language);
        port_forward_esi(&port, entry, 0x418ce0, port_u32(&port, port_u32(&port, window, 4), 0x1c),
                         language, object, entry->ecx, language);
    }
    result =
        port_forward_esi(&port, entry, 0x418840, object, 0x41a540, object, entry->ecx, language);
    return port_return(&port, result, entry->edx);
}

/* Original 0x41c390: under the guard record 0x51403c, byte +0xc8 set, the handlers 0x423bc0 by
 * 0x418840 and 0x41c400 by 0x418820; eax the chain it restores. */
uint32_t vertrix_port_scene_enter_41c390(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t scene = entry->eax;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    guard_record(&port, ebp, 0x51403c);
    port_set8(&port, scene, 0xc8, 1);
    call_registers(&port, 0x418840, scene, 0x423bc0, 0x51403c, scene, 0, entry->edi, ebp, NULL, 0);
    call_registers(&port, 0x418820, scene, 0x41c400, 0x51403c, scene, 0, entry->edi, ebp, NULL, 0);
    return port_return(&port, port_u32(&port, ebp, -0x24u), entry->edx);
}

/* Original 0x41cbb0: under the guard record 0x514054, 0x41ab90, 0x41ac20, the handler 0x421f10
 * by 0x41a9e0, 0x4719e0, 0x45f9f0, 0x418840 and 0x41d5b0 (each on the edx the one before leaves);
 * eax the chain it restores. */
uint32_t vertrix_port_scene_restart_41cbb0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t scene = entry->eax;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    guard_record(&port, ebp, 0x514054);
    call_registers(&port, 0x41ab90, scene, 0x4ec1ec, 0x514054, scene, 0, entry->edi, ebp, NULL, 0);
    call_registers(&port, 0x41ac20, scene, vertrix_lift_edx, 0x514054, scene, 0, entry->edi, ebp,
                   NULL, 0);
    result = call_registers(&port, 0x41a9e0, scene, 0x421f10, 0x514054, scene, 0, entry->edi, ebp,
                            NULL, 0);
    result = call_registers(&port, 0x4719e0, result, vertrix_lift_edx, 0x514054, scene, 0,
                            entry->edi, ebp, NULL, 0);
    call_registers(&port, 0x45f9f0, result, vertrix_lift_edx, 0x514054, scene, 0, entry->edi, ebp,
                   NULL, 0);
    call_registers(&port, 0x418840, scene, vertrix_lift_edx, 0x514054, scene, 0, entry->edi, ebp,
                   NULL, 0);
    call_registers(&port, 0x41d5b0, scene, vertrix_lift_edx, 0x514054, scene, 0, entry->edi, ebp,
                   NULL, 0);
    return port_return(&port, port_u32(&port, ebp, -0x24u), entry->edx);
}
