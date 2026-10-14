#include "port_voices.h"

/* Sound buffer fill, channel buffer setup and play, the swapped word read, the option record
 * steps, the high score name, the clock text and the game teardown. */

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

/* Original 0x40bcc0: ebx bytes of the sample (its data +0, buffer +4, size +8) from edx go to
 * its sound buffer: Lock (method +0x2c; on failure Restore, method +0x50, and 2), a copy
 * (0x4eb5e0 when +0x16 bit 0, otherwise with the sign bit flipped) and Unlock (method +0x4c).
 * 1 without a sample, 2 past its end, otherwise 0. */
uint32_t vertrix_port_sound_buffer_fill_40bcc0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x24
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t sample = entry->eax;
    uint32_t offset = entry->edx;
    uint32_t size = entry->ebx;
    uint32_t buffer;
    uint32_t methods;
    uint32_t stack[8];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    if (sample == 0 || port_u32(&port, sample, 4) == 0 || port_u32(&port, sample, 0) == 0)
    {
        return port_return(&port, 1, entry->edx);
    }
    if (offset + size > port_u32(&port, sample, 8))
    {
        return port_return(&port, 2, entry->edx);
    }
    buffer = port_u32(&port, sample, 4);
    port_set32(&port, ebp, -0x10u, buffer);
    methods = port_u32(&port, buffer, 0);
    stack[0] = buffer;
    stack[1] = offset;
    stack[2] = size;
    stack[3] = ebp - 0x20;
    stack[4] = ebp - 0x18;
    stack[5] = ebp - 0x1c;
    stack[6] = ebp - 0x14;
    stack[7] = 0;
    if (call_frame(&port, port_u32(&port, methods, 0x2c), methods, ebp - 0x20, size, buffer, offset,
                   sample, ebp, stack, 8) != 0)
    {
        buffer = port_u32(&port, ebp, -0x10u);
        methods = port_u32(&port, buffer, 0);
        stack[0] = buffer;
        call_frame(&port, port_u32(&port, methods, 0x50), methods, vertrix_lift_edx, buffer, buffer,
                   offset, sample, ebp, stack, 1);
        return port_return(&port, 2, vertrix_lift_edx);
    }
    if ((port_u8(&port, sample, 0x16) & 1) != 0)
    {
        port_call_with(&port, 0x4eb5e0, port_u32(&port, ebp, -0x20u),
                       port_u32(&port, sample, 0) + offset, port_u32(&port, ebp, -0x18u), buffer,
                       offset, sample, ebp);
    }
    else
    {
        uint32_t index;
        for (index = 0; index < port_u32(&port, ebp, -0x18u); index++)
        {
            uint32_t value = port_u8(&port, offset, port_u32(&port, sample, 0)) ^ 0x80;
            offset++;
            port_set8(&port, port_u32(&port, ebp, -0x20u), index, value);
        }
    }
    buffer = port_u32(&port, ebp, -0x10u);
    methods = port_u32(&port, buffer, 0);
    stack[0] = buffer;
    stack[1] = port_u32(&port, ebp, -0x20u);
    stack[2] = port_u32(&port, ebp, -0x18u);
    stack[3] = port_u32(&port, ebp, -0x1cu);
    stack[4] = port_u32(&port, ebp, -0x14u);
    call_frame(&port, port_u32(&port, methods, 0x4c), methods, stack[1], stack[4], buffer, stack[3],
               stack[2], ebp, stack, 5);
    return port_return(&port, 0, vertrix_lift_edx);
}

/* Original 0x40bdb0: channel eax (below 32) takes a new sound buffer for the description edx:
 * the old one (0x52f178) stops (method +0x48) and is released (+8); CreateSoundBuffer on
 * 0x52f170 (method +0x14; failure 8), then position 0, the channel's volume (0x52f780), pan
 * (0x52f1fc by 0x52f800) and frequency (0x52f300 by 0x52f880), and its flags 0x52f700 the
 * description's word +0x16. 1 for a bad channel. */
uint32_t vertrix_port_sound_channel_buffer_40bdb0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x18
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t channel = entry->eax;
    uint32_t description = entry->edx;
    uint32_t slot;
    uint32_t buffer;
    uint32_t methods;
    uint32_t ecx = entry->ecx;
    uint32_t stack[3];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    if (channel >= 0x20 || description == 0)
    {
        return port_return(&port, 1, entry->edx);
    }
    port_set32(&port, ebp, -0x14u, port_u32(&port, description, 4));
    slot = channel * 4;
    buffer = port_u32(&port, slot, 0x52f178);
    if (buffer != 0)
    {
        methods = port_u32(&port, buffer, 0);
        stack[0] = buffer;
        call_frame(&port, port_u32(&port, methods, 0x48), buffer, methods, channel, ecx,
                   description, slot, ebp, stack, 1);
        buffer = port_u32(&port, slot, 0x52f178);
        methods = port_u32(&port, buffer, 0);
        stack[0] = buffer;
        call_frame(&port, port_u32(&port, methods, 8), buffer, methods, channel, ecx, description,
                   slot, ebp, stack, 1);
        ecx = 0;
        port_set32(&port, slot, 0x52f178, 0);
    }
    {
        uint32_t sound = port_u32(&port, 0, 0x52f170);
        methods = port_u32(&port, sound, 0);
        stack[0] = sound;
        stack[1] = port_u32(&port, ebp, -0x14u);
        stack[2] = 0x52f178 + slot;
        if (call_frame(&port, port_u32(&port, methods, 0x14), sound, methods, slot, ecx,
                       description, stack[1], ebp, stack, 3) != 0)
        {
            return port_return(&port, 8, vertrix_lift_edx);
        }
    }
    buffer = port_u32(&port, slot, 0x52f178);
    methods = port_u32(&port, buffer, 0);
    stack[0] = buffer;
    stack[1] = 0;
    call_frame(&port, port_u32(&port, methods, 0x34), buffer, vertrix_lift_edx, slot, ecx,
               description, methods, ebp, stack, 2);
    buffer = port_u32(&port, slot, 0x52f178);
    methods = port_u32(&port, buffer, 0);
    ecx = port_u32(&port, slot, 0x52f780);
    stack[0] = buffer;
    stack[1] = ecx;
    call_frame(&port, port_u32(&port, methods, 0x44), buffer, methods, slot, ecx, description,
               methods, ebp, stack, 2);
    buffer = port_u32(&port, slot, 0x52f178);
    methods = port_u32(&port, buffer, 0);
    {
        uint32_t pan = port_u32(&port, slot, 0x52f800);
        ecx = port_u32(&port, pan * 4, 0x52f1fc);
        stack[0] = buffer;
        stack[1] = ecx;
        call_frame(&port, port_u32(&port, methods, 0x3c), buffer, methods, slot, ecx, description,
                   pan, ebp, stack, 2);
    }
    buffer = port_u32(&port, slot, 0x52f178);
    methods = port_u32(&port, buffer, 0);
    {
        uint32_t rate = port_u32(&port, slot, 0x52f880);
        ecx = port_u32(&port, rate * 4, 0x52f300);
        stack[0] = buffer;
        stack[1] = ecx;
        call_frame(&port, port_u32(&port, methods, 0x40), buffer, rate, slot, ecx, description,
                   methods, ebp, stack, 2);
    }
    port_set32(&port, slot, 0x52f700, port_u16(&port, description, 0x16));
    return port_return(&port, 0, vertrix_lift_edx);
}

/* Original 0x40beb0: channel eax's buffer (0x52f178) plays (method +0x30, looping with its flags
 * 0x52f700 bit 4); 0 when it plays, otherwise (or a bad channel) 1, and 0 without a buffer. */
uint32_t vertrix_port_sound_channel_play_40beb0(PORT_SIGNATURE)
{
    Port port;
    uint32_t channel = entry->eax;
    uint32_t buffer;
    uint32_t methods;
    uint32_t looping;
    uint32_t stack[4];
    port_open(&port, calls, services, globals, entry);
    if (channel >= 0x20)
    {
        return port_return(&port, 1, entry->edx);
    }
    if (port_u32(&port, channel * 4, 0x52f178) == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    looping = (port_u8(&port, channel * 4, 0x52f700) & 0x10) != 0;
    buffer = port_u32(&port, channel * 4, 0x52f178);
    methods = port_u32(&port, buffer, 0);
    stack[0] = buffer;
    stack[1] = 0;
    stack[2] = 0;
    stack[3] = looping;
    if (port_forward_stack(&port, entry, port_u32(&port, methods, 0x30), buffer, looping,
                           entry->ebx, methods, entry->esi, stack, 4) == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    return port_return(&port, 1, entry->edx);
}

/* Original 0x40c360: a big-endian word read from the file 0x52f90c (0x4ebec0; a short read
 * clears it, 0x4eb5c0) and swapped in place. 0. */
uint32_t vertrix_port_file_read_word_swapped_40c360(PORT_SIGNATURE)
{
    Port port;
    uint32_t word = entry->eax;
    uint32_t file;
    uint32_t value;
    port_open(&port, calls, services, globals, entry);
    file = port_u32(&port, 0, 0x52f90c);
    if (port_forward_esi(&port, entry, 0x4ebec0, word, 1, 2, file, word) != 2)
    {
        port_forward_esi(&port, entry, 0x4eb5c0, word, 0, 2, file, word);
    }
    value = port_u16(&port, word, 0);
    port_set16(&port, word, 0, ((value & 0xff) << 8) | (value >> 8));
    return port_return(&port, 0, entry->edx);
}

/* Original 0x412430: field ebx of option record edx (12 bytes from eax) steps up to its limit:
 * 0 below 1, 1 below 10, 2 below 100, 3 below 200, 4 below 13, 5 below 2, 6 below 1 and 7
 * wrapping from 254 to 0. The record; edx as the field's test leaves it. */
uint32_t vertrix_port_option_record_step_up_412430(PORT_SIGNATURE)
{
    Port port;
    uint32_t record = entry->eax + entry->edx * 0xc;
    uint32_t edx = entry->edx;
    uint32_t value;
    port_open(&port, calls, services, globals, entry);
    switch (entry->ebx)
    {
        case 0:
            value = port_u8(&port, record, 0);
            edx = (edx & 0xffff00ffu) | (value << 8);
            if ((int8_t)value < 1)
            {
                port_set8(&port, record, 0, value + 1);
            }
            break;
        case 1:
            edx = (uint32_t)(int32_t)(int8_t)port_u8(&port, record, 1);
            if ((int32_t)edx < 0xa)
            {
                port_set8(&port, record, 1, edx + 1);
            }
            break;
        case 2:
            edx = port_u8(&port, record, 2);
            if (edx < 0x64)
            {
                port_set8(&port, record, 2, edx + 1);
            }
            break;
        case 3:
            edx = (uint32_t)(int32_t)(int16_t)port_u16(&port, record, 4);
            if ((int32_t)edx < 0xc8)
            {
                port_set16(&port, record, 4, edx + 1);
            }
            break;
        case 4:
            edx = port_u8(&port, record, 6);
            if (edx < 0xd)
            {
                port_set8(&port, record, 6, edx + 1);
            }
            break;
        case 5:
            value = port_u8(&port, record, 7);
            if ((int8_t)value < 2)
            {
                port_set8(&port, record, 7, value + 1);
            }
            break;
        case 7:
            edx = port_u16(&port, record, 0xa);
            if (edx < 0xfe)
            {
                edx++;
                port_set16(&port, record, 0xa, edx);
            }
            else
            {
                port_set16(&port, record, 0xa, 0);
            }
            break;
        case 6:
            value = port_u8(&port, record, 8);
            edx = (edx & 0xffffff00u) | value;
            if ((int8_t)value < 1)
            {
                edx = (edx & 0xffff00ffu) | (((value + 1) & 0xff) << 8);
                port_set8(&port, record, 8, value + 1);
            }
            break;
        default:
            break;
    }
    return port_return(&port, record, edx);
}

/* Original 0x412510: field ebx of option record edx steps down to its floor: 0 to 4 and 6 above
 * 0, 3 above -200 and 7 wrapping from 0 to 254. The record; edx as the field's test leaves it. */
uint32_t vertrix_port_option_record_step_down_412510(PORT_SIGNATURE)
{
    Port port;
    uint32_t record = entry->eax + entry->edx * 0xc;
    uint32_t edx = entry->edx;
    uint32_t value;
    port_open(&port, calls, services, globals, entry);
    switch (entry->ebx)
    {
        case 0:
            value = port_u8(&port, record, 0);
            edx = (edx & 0xffff00ffu) | (value << 8);
            if ((int8_t)value > 0)
            {
                port_set8(&port, record, 0, value - 1);
            }
            break;
        case 1:
            edx = (uint32_t)(int32_t)(int8_t)port_u8(&port, record, 1);
            if ((int32_t)edx > 0)
            {
                port_set8(&port, record, 1, edx - 1);
            }
            break;
        case 2:
            edx = port_u8(&port, record, 2);
            if (edx != 0)
            {
                port_set8(&port, record, 2, edx - 1);
            }
            break;
        case 3:
            edx = (uint32_t)(int32_t)(int16_t)port_u16(&port, record, 4);
            if ((int32_t)edx > -200)
            {
                port_set16(&port, record, 4, edx - 1);
            }
            break;
        case 4:
            edx = port_u8(&port, record, 6);
            if (edx != 0)
            {
                port_set8(&port, record, 6, edx - 1);
            }
            break;
        case 5:
            value = port_u8(&port, record, 7);
            if ((int8_t)value > 0)
            {
                port_set8(&port, record, 7, value - 1);
            }
            break;
        case 7:
            edx = port_u16(&port, record, 0xa);
            if (edx != 0)
            {
                edx--;
                port_set16(&port, record, 0xa, edx);
            }
            else
            {
                port_set16(&port, record, 0xa, 0xfe);
            }
            break;
        case 6:
            value = port_u8(&port, record, 8);
            edx = (edx & 0xffffff00u) | value;
            if ((int8_t)value > 0)
            {
                edx = (edx & 0xffff00ffu) | (((value - 1) & 0xff) << 8);
                port_set8(&port, record, 8, value - 1);
            }
            break;
        default:
            break;
    }
    return port_return(&port, record, edx);
}

/* Original 0x416990: unless the object (a text) is 0x50d63f (0x4ccfe0), it is formatted with
 * 0x50d640 (0x4cdfb0) into a text the high score list 0x532c24 takes (0x4b76d0 with its copy,
 * 0x4ca090) and, formatted with 0x50d649, the sound 0x5bb254 says (0x47faf0); guarded 0x513b88. */
uint32_t vertrix_port_high_score_name_416990(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x34
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t object = entry->eax;
    uint32_t guard = 0x513b88;
    uint32_t copy;
    uint32_t stack[3];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    guard_record(&port, ebp - 0x30, guard);
    if (port_call_with(&port, 0x4ccfe0, object, 0x50d63f, guard, object, 0, entry->edi, ebp) == 0)
    {
        return port_return(&port, port_u32(&port, ebp, -0x30u), entry->edx);
    }
    port_call_with(&port, 0x4ca070, ebp - 0x1c, vertrix_lift_edx, guard, object, 0, entry->edi,
                   ebp);
    port_set32(&port, ebp, -0x24u, 1);
    stack[0] = ebp - 0x1c;
    stack[1] = 0x50d640;
    stack[2] = object;
    call_frame(&port, 0x4cdfb0, ebp - 0x1c, vertrix_lift_edx, guard, object, 0, 1, ebp, stack, 3);
    copy = port_call_with(&port, 0x4ca090, ebp - 0x18, ebp - 0x1c, guard, object, 0, 1, ebp);
    port_set32(&port, ebp, -0x24u, 2);
    port_call_with(&port, 0x4b76d0, 0x532c24, copy, guard, object, 0, 1, ebp);
    port_set32(&port, ebp, -0x24u, 1);
    port_call_with(&port, 0x4ca210, ebp - 0x18, 0, guard, object, 0, 1, ebp);
    port_set32(&port, ebp, -0x24u, 1);
    stack[1] = 0x50d649;
    call_frame(&port, 0x4cdfb0, ebp - 0x1c, vertrix_lift_edx, guard, object, 0, 1, ebp, stack, 3);
    port_call_with(&port, 0x47faf0, 0x5bb254, port_u32(&port, ebp, -0x1cu), guard, object, 0, 1,
                   ebp);
    port_set32(&port, ebp, -0x24u, 0);
    port_call_with(&port, 0x4ca210, ebp - 0x1c, 0, guard, object, 0, 1, ebp);
    port_set32(&port, ebp, -0x24u, 0);
    return port_return(&port, port_u32(&port, ebp, -0x30u), entry->edx);
}

/* Original 0x418170: the clock text of edx tenths: the seconds (0x50d7bd) and the tenth
 * (0x50d7c1) formatted (0x4cdfb0) and joined by 0x50d7c5 (0x4ca4a0, 0x4ca430) into the text eax
 * (0x4ca310); guarded 0x513bf4 with the temporaries released by 0x4cda12 and 0x4cda10. */
uint32_t vertrix_port_clock_text_418170(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x38
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t text = entry->eax;
    uint32_t tenths = entry->edx;
    uint32_t seconds;
    uint32_t rest;
    uint32_t joined;
    uint32_t stack[4];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    guard_record(&port, ebp - 0x34, 0x513bf4);
    port_call_with(&port, 0x4ca070, text, 0x4ec1ec, text, tenths, 0x513bf4, 0, ebp);
    port_call_with(&port, 0x4ca070, ebp - 0x20, vertrix_lift_edx, text, tenths, 0x513bf4, 0, ebp);
    port_set32(&port, ebp, -0x28u, 1);
    port_call_with(&port, 0x4ca070, ebp - 0x1c, 2, text, tenths, 0xa, 0, ebp);
    port_set32(&port, ebp, -0x28u, vertrix_lift_edx);
    seconds = tenths / 0xa;
    rest = tenths - seconds * 0xa;
    stack[0] = ebp - 0x20;
    stack[1] = 0x50d7bd;
    stack[2] = seconds;
    call_frame(&port, 0x4cdfb0, ebp - 0x20, seconds, text, rest, 0xa, 0, ebp, stack, 3);
    stack[0] = ebp - 0x1c;
    stack[1] = 0x50d7c1;
    stack[2] = rest;
    call_frame(&port, 0x4cdfb0, ebp - 0x1c, vertrix_lift_edx, text, rest, 0xa, 0, ebp, stack, 3);
    stack[0] = ebp - 0x18;
    stack[1] = ebp - 0x20;
    stack[2] = 0x50d7c5;
    stack[3] = ebp - 0x1c;
    joined = call_frame(&port, 0x4ca4a0, ebp - 0x18, vertrix_lift_edx, text, rest, 0xa, 0, ebp,
                        stack, 3);
    port_set32(&port, ebp, -0x28u, 3);
    stack[0] = ebp - 0x14;
    stack[1] = joined;
    stack[2] = ebp - 0x1c;
    joined =
        call_frame(&port, 0x4ca430, ebp - 0x14, vertrix_lift_edx, text, 3, 4, 0, ebp, stack, 3);
    port_set32(&port, ebp, -0x28u, 4);
    port_call_with(&port, 0x4ca310, text, joined, text, 3, 4, 0, ebp);
    joined = port_call_with(&port, 0x4cda12, 2, vertrix_lift_edx, text, 3, 4, 0, ebp);
    port_call_with(&port, 0x4cda10, joined, vertrix_lift_edx, text, 3, 4, 0, ebp);
    return port_return(&port, text, vertrix_lift_edx);
}

/* Original 0x41fd20: the game's teardown (guarded 0x51412c): its parts close in order (0x4b7d10
 * on the guard record,
 * 0x41d670, 0x41dec0, 0x419490, 0x471a70, 0x471a80, 0x41aaf0, the music 0x5b9c50 0x486d00, the
 * voice 0x558c7c 0x4719f0 and 0x471aa0, 0x41d6d0, 0x41dd60, 0x486da0, 0x487020, 0x41d660,
 * 0x41de80); when 0x471d10 gives 1 the game takes the state 0x41fe10 (0x418840). */
uint32_t vertrix_port_game_teardown_41fd20(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t game = entry->eax;
    uint32_t guard = 0x51412c;
    uint32_t eax;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    guard_record(&port, ebp - 0x24, guard);
#define CALL(target, value)                                                                        \
    port_call_with(&port, (target), (value), vertrix_lift_edx, guard, game, 0, entry->edi, ebp)
    port_call_with(&port, 0x4b7d10, ebp - 0x24, 0x4ec1ec, guard, game, 0, entry->edi, ebp);
    CALL(0x41d670, game);
    CALL(0x41dec0, game);
    eax = CALL(0x419490, game);
    eax = CALL(0x471a70, eax);
    CALL(0x471a80, eax);
    CALL(0x41aaf0, game);
    CALL(0x486d00, 0x5b9c50);
    CALL(0x4719f0, port_u32(&port, 0, 0x558c7c));
    CALL(0x471aa0, port_u32(&port, 0, 0x558c7c));
    CALL(0x41d6d0, game);
    CALL(0x41dd60, game);
    CALL(0x486da0, 0x5b9c50);
    CALL(0x487020, 0x5b9c50);
    CALL(0x41d660, game);
    eax = CALL(0x41de80, game);
    if (CALL(0x471d10, eax) == 1)
    {
        port_call_with(&port, 0x418840, game, 0x41fe10, guard, game, 0, entry->edi, ebp);
    }
#undef CALL
    return port_return(&port, port_u32(&port, ebp, -0x24u), entry->edx);
}
