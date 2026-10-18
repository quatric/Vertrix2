#include "screens.h"

/* The sound buffer making and channel volume, the filled table check, the notice call, and the
 * menu screens' cycles. */

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

/* Original 0x40bba0: the sound record eax's buffer: none is 2; a mono PCM format of the rate at
 * +0x14 in 16 bits (bit 0 of +0x16) or 8, a description (20 bytes, flags 0x140e8, the size at +8)
 * and CreateSoundBuffer of the sound device 0x52f170 (method +0xc); its failure is 8, otherwise
 * the buffer goes to +4 and 0. */
uint32_t vertrix_port_sound_buffer_make_40bba0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x40
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t sound = entry->eax;
    uint32_t rate;
    uint32_t device;
    uint32_t methods;
    uint32_t args[4];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    if (sound == 0)
    {
        return port_return(&port, 2, entry->edx);
    }
    port_set32(&port, sound, 4, 0);
    port_set16(&port, ebp, -0x28u, 1);
    port_set16(&port, ebp, -0x26u, 1);
    port_set16(&port, ebp, -0x1au, (port_u8(&port, sound, 0x16) & 1) != 0 ? 0x10 : 8);
    rate = port_u16(&port, sound, 0x14);
    port_set32(&port, ebp, -0x24u, rate);
    port_set32(&port, ebp, -0x20u, rate);
    port_set16(&port, ebp, -0x1cu, 1);
    port_set16(&port, ebp, -0x18u, 0);
    if ((port_u8(&port, sound, 0x16) & 1) != 0)
    {
        port_set32(&port, ebp, -0x20u, rate * 2);
        port_set16(&port, ebp, -0x1cu, 2);
    }
    port_set32(&port, ebp, -0x3cu, 0x14);
    port_set32(&port, ebp, -0x38u, 0x140e8);
    port_set32(&port, ebp, -0x34u, port_u32(&port, sound, 8));
    port_set32(&port, ebp, -0x30u, 0);
    port_set32(&port, ebp, -0x2cu, ebp - 0x28);
    device = port_u32(&port, 0, 0x52f170);
    methods = port_u32(&port, device, 0);
    args[0] = device;
    args[1] = ebp - 0x3c;
    args[2] = ebp - 0x14;
    args[3] = 0;
    if (call_frame(&port, port_u32(&port, methods, 0xc), device, ebp - 0x3c, sound, methods,
                   entry->esi, 0, ebp, args, 4) != 0)
    {
        return port_return(&port, 8, entry->edx);
    }
    port_set32(&port, sound, 4, port_u32(&port, ebp, -0x14u));
    return port_return(&port, 0, entry->edx);
}

/* Original 0x40c020: the volume edx of the sound channel eax: a channel of 32 or more is 1, a
 * volume of 255 or more 2; the volume goes to 0x52f880 and the channel's buffer at 0x52f178 (if
 * any) takes the level of the table 0x52f300 (SetVolume, method +0x40). 0. */
uint32_t vertrix_port_sound_channel_volume_40c020(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 8
    };
    Port port;
    uint32_t channel = entry->eax;
    uint32_t volume = entry->edx;
    uint32_t buffer;
    uint32_t methods;
    uint32_t level;
    uint32_t args[2];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    if (channel >= 0x20)
    {
        return port_return(&port, 1, entry->edx);
    }
    if (volume >= 0xff)
    {
        return port_return(&port, 2, entry->edx);
    }
    port_set32(&port, 0, 0x52f880 + channel * 4, volume);
    buffer = port_u32(&port, 0, 0x52f178 + channel * 4);
    if (buffer == 0)
    {
        return port_return(&port, 0, 0);
    }
    methods = port_u32(&port, buffer, 0);
    level = port_u32(&port, 0, 0x52f300 + volume * 4);
    args[0] = buffer;
    args[1] = level;
    call_frame(&port, port_u32(&port, methods, 0x40), volume, methods, level, buffer, entry->esi,
               entry->edi, entry->ebp, args, 2);
    return port_return(&port, 0, vertrix_lift_edx);
}

/* Original 0x415c30: 1 when the 19 words of 0x5344f0 are all set, otherwise 0. */
uint32_t vertrix_port_table_all_filled_415c30(PORT_SIGNATURE)
{
    Port port;
    uint32_t index;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, 0, 0x5344f0) == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    for (index = 1; index < 0x13; ++index)
    {
        if (port_u32(&port, 0, 0x5344f0 + index * 4) == 0)
        {
            return port_return(&port, 0, entry->edx);
        }
    }
    return port_return(&port, 1, entry->edx);
}

/* Original 0x416010: the notice call: 0x532c40 is set; when 0x532bf8 is 0x4f8160's value, a
 * notice of 0x5bb254 (0x47f9b0) of 1 shows the text 0x50d3c9 (0x4b76d0 on 0x532c24), otherwise
 * the texts 0x50d3f4 and 0x50d40d; each text is made (0x4ca280) and released (0x4ca210). The
 * guard record's chain. */
uint32_t vertrix_port_notice_call_full_416010(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x38
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t record = ebp - 0x34;
    uint32_t edi;
    uint32_t text;
    uint32_t esi = 1;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    guard_record(&port, record, 0x513a2c);
    edi = port_u32(&port, 0, 0x4f8160);
    port_set32(&port, 0, 0x532c40, 1);
    if (port_u32(&port, 0, 0x532bf8) != edi)
    {
        return port_return(&port, port_u32(&port, record, 0), entry->edx);
    }
    if (port_call_with(&port, 0x47f9b0, 0x5bb254, 0x4ec1ec, 0, 0x513a2c, esi, edi, ebp) == 1)
    {
        text = port_call_with(&port, 0x4ca280, ebp - 0x20, 0x50d3c9, 0, 0x513a2c, esi, edi, ebp);
        port_set32(&port, ebp, -0x28u, 1);
        port_call_with(&port, 0x4b76d0, 0x532c24, text, 0, 0x513a2c, esi, edi, ebp);
        port_set32(&port, ebp, -0x28u, 0);
        port_call_with(&port, 0x4ca210, ebp - 0x20, 0, 0, 0x513a2c, esi, edi, ebp);
        port_set32(&port, 0, 0x532c40, 1);
        port_set32(&port, ebp, -0x28u, 0);
        return port_return(&port, port_u32(&port, record, 0), entry->edx);
    }
    text = port_call_with(&port, 0x4ca280, ebp - 0x1c, 0x50d3f4, 0, 0x513a2c, esi, edi, ebp);
    port_set32(&port, ebp, -0x28u, 3);
    esi = 5;
    port_call_with(&port, 0x4b76d0, 0x532c24, text, 0, 0x513a2c, esi, edi, ebp);
    port_set32(&port, ebp, -0x28u, 0);
    port_call_with(&port, 0x4ca210, ebp - 0x1c, 0, 0, 0x513a2c, esi, edi, ebp);
    port_set32(&port, ebp, -0x28u, 0);
    text = port_call_with(&port, 0x4ca280, ebp - 0x18, 0x50d40d, 0, 0x513a2c, esi, edi, ebp);
    port_set32(&port, ebp, -0x28u, esi);
    port_call_with(&port, 0x4b76d0, 0x532c24, text, 0, 0x513a2c, esi, edi, ebp);
    port_set32(&port, ebp, -0x28u, 0);
    port_call_with(&port, 0x4ca210, ebp - 0x18, 0, 0, 0x513a2c, esi, edi, ebp);
    port_set32(&port, ebp, -0x28u, 0);
    return port_return(&port, port_u32(&port, record, 0), entry->edx);
}

/* The menu screen's cycle shared by 0x41f210, 0x41f350, 0x41f800 and 0x41fb40: the step
 * (0x4b7d10), the screen's input and parts (0x41d670, 0x41dec0, 0x419490, 0x471a70, 0x471a80,
 * 0x41aaf0), the view 0x5b9c50 (0x486d00), the scene 0x558c7c (0x471aa0 and 0x4719f0, the other
 * order when `drawn_first`), the screen's draws (0x41d6d0, 0x41dd60), the view's draws (0x486da0,
 * 0x487020) and the screen's ends (0x41d660, 0x41de80). The last result. */
static uint32_t screen_cycle(Port *port, uint32_t screen, uint32_t eax, uint32_t edx, uint32_t ebx,
                             uint32_t edi, uint32_t ebp, int drawn_first)
{
    port_call_with(port, 0x4b7d10, eax, edx, ebx, screen, 0, edi, ebp);
    port_call_with(port, 0x41d670, screen, vertrix_lift_edx, ebx, screen, 0, edi, ebp);
    port_call_with(port, 0x41dec0, screen, vertrix_lift_edx, ebx, screen, 0, edi, ebp);
    eax = port_call_with(port, 0x419490, screen, vertrix_lift_edx, ebx, screen, 0, edi, ebp);
    eax = port_call_with(port, 0x471a70, eax, vertrix_lift_edx, ebx, screen, 0, edi, ebp);
    port_call_with(port, 0x471a80, eax, vertrix_lift_edx, ebx, screen, 0, edi, ebp);
    port_call_with(port, 0x41aaf0, screen, vertrix_lift_edx, ebx, screen, 0, edi, ebp);
    port_call_with(port, 0x486d00, 0x5b9c50, vertrix_lift_edx, ebx, screen, 0, edi, ebp);
    port_call_with(port, drawn_first ? 0x4719f0 : 0x471aa0, port_u32(port, 0, 0x558c7c),
                   vertrix_lift_edx, ebx, screen, 0, edi, ebp);
    port_call_with(port, drawn_first ? 0x471aa0 : 0x4719f0, port_u32(port, 0, 0x558c7c),
                   vertrix_lift_edx, ebx, screen, 0, edi, ebp);
    port_call_with(port, 0x41d6d0, screen, vertrix_lift_edx, ebx, screen, 0, edi, ebp);
    port_call_with(port, 0x41dd60, screen, vertrix_lift_edx, ebx, screen, 0, edi, ebp);
    port_call_with(port, 0x486da0, 0x5b9c50, vertrix_lift_edx, ebx, screen, 0, edi, ebp);
    port_call_with(port, 0x487020, 0x5b9c50, vertrix_lift_edx, ebx, screen, 0, edi, ebp);
    port_call_with(port, 0x41d660, screen, vertrix_lift_edx, ebx, screen, 0, edi, ebp);
    return port_call_with(port, 0x41de80, screen, vertrix_lift_edx, ebx, screen, 0, edi, ebp);
}

/* The start of a menu screen's state (BELOW 0x28, guard at ebp-0x24): the flag byte at `flag`
 * read into ah of the record's address; with `opens` an unset flag is set and the screen opened
 * (0x41d640 with dl 1). The cycle's step's eax and edx come back through `eax` and `edx`. */
static void screen_start(Port *port, const LiftEntry *entry, uint32_t flag, uint32_t guard,
                         int opens, uint32_t *eax, uint32_t *edx)
{
    uint32_t ebp = entry->esp - 4;
    uint32_t value = port_u8(port, 0, flag);
    guard_record(port, ebp - 0x24, guard);
    *eax = ((ebp - 0x24) & 0xffff00ffu) | (value << 8);
    *edx = 0x4ec1ec;
    if (value == 0)
    {
        port_set8(port, 0, flag, 1);
        if (opens)
        {
            *eax = port_call_with(port, 0x41d640, entry->eax, 0x4ec101, guard, entry->eax, 0,
                                  entry->edi, ebp);
            *edx = vertrix_lift_edx;
        }
    }
}

/* Original 0x41f210: a menu screen state (flag 0x54038c, opening when unset): the cycle, the
 * demo 0x41aca0 when 0x532a38 is 1, and the key wait of 0x54d640 (0x476530); a key clears the
 * flag, moves to 0x41f350 (0x418840), and is acknowledged (0x476320, 0x471bb0). The guard
 * record's chain. */
uint32_t vertrix_port_screen_state_41f210(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t screen = entry->eax;
    uint32_t eax;
    uint32_t edx;
    uint32_t key;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    screen_start(&port, entry, 0x54038c, 0x514104, 1, &eax, &edx);
    screen_cycle(&port, screen, eax, edx, 0x514104, entry->edi, ebp, 0);
    if (port_u32(&port, 0, 0x532a38) == 1)
    {
        port_call_with(&port, 0x41aca0, screen, vertrix_lift_edx, 0x514104, screen, 0, entry->edi,
                       ebp);
    }
    key = port_call_with(&port, 0x476530, 0x54d640, 0, 0x514104, screen, 0, entry->edi, ebp);
    if ((key & 0xffff) == 0)
    {
        return port_return(&port, port_u32(&port, ebp, -0x24u), entry->edx);
    }
    port_set8(&port, 0, 0x54038c, 0);
    port_call_with(&port, 0x418840, screen, 0x41f350, key, screen, 0, entry->edi, ebp);
    eax = port_call_with(&port, 0x476320, 0x54d640, key & 0xffff, key, screen, 0, entry->edi, ebp);
    port_call_with(&port, 0x471bb0, eax, vertrix_lift_edx, key, screen, 0, entry->edi, ebp);
    return port_return(&port, port_u32(&port, ebp, -0x24u), entry->edx);
}

/* The menu screen state of 0x41f350 and 0x41f800: the cycle, the demo 0x41aca0 when 0x532a38
 * is 1, and when the scene is done (0x471c90 of 1) the flag is cleared and the screen moves on
 * (0x418840 to `next`). The guard record's chain. */
static uint32_t screen_pass(PORT_SIGNATURE, uint32_t flag, uint32_t guard, uint32_t next)
{
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t screen = entry->eax;
    uint32_t eax;
    uint32_t edx;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    screen_start(&port, entry, flag, guard, 0, &eax, &edx);
    eax = screen_cycle(&port, screen, eax, edx, guard, entry->edi, ebp, 0);
    if (port_u32(&port, 0, 0x532a38) == 1)
    {
        eax = port_call_with(&port, 0x41aca0, screen, vertrix_lift_edx, guard, screen, 0,
                             entry->edi, ebp);
    }
    if (port_call_with(&port, 0x471c90, eax, vertrix_lift_edx, guard, screen, 0, entry->edi, ebp) ==
        1)
    {
        port_set8(&port, 0, flag, 0);
        port_call_with(&port, 0x418840, screen, next, guard, screen, 0, entry->edi, ebp);
    }
    return port_return(&port, port_u32(&port, ebp, -0x24u), entry->edx);
}

/* Original 0x41f350: the screen state of flag 0x54038d moving to 0x41f460. */
uint32_t vertrix_port_screen_state_41f350(PORT_SIGNATURE)
{
    return screen_pass(calls, services, globals, entry, 0x54038d, 0x514108, 0x41f460);
}

/* Original 0x41f800: the screen state of flag 0x54038f moving to 0x41f910. */
uint32_t vertrix_port_screen_state_41f800(PORT_SIGNATURE)
{
    return screen_pass(calls, services, globals, entry, 0x54038f, 0x514118, 0x41f910);
}

/* Original 0x41fb40: a menu screen state (flag 0x540390, opening when unset): the cycle (scene
 * drawn first); when 0x532a58 differs from 0x532a98 it becomes it, the flag being cleared and
 * the screen moving to 0x41fc70 when it was 0x4f7bd4's value, or the sound stopped (0x471d90)
 * and the screen moving to 0x41fd20 when it was 0x4f7bd8's. The guard record's chain. */
uint32_t vertrix_port_screen_state_41fb40(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t screen = entry->eax;
    uint32_t eax;
    uint32_t edx;
    uint32_t mode;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    screen_start(&port, entry, 0x540390, 0x514124, 1, &eax, &edx);
    screen_cycle(&port, screen, eax, edx, 0x514124, entry->edi, ebp, 1);
    mode = port_u32(&port, 0, 0x532a58);
    if (mode == port_u32(&port, 0, 0x532a98))
    {
        return port_return(&port, port_u32(&port, ebp, -0x24u), entry->edx);
    }
    if (mode == port_u32(&port, 0, 0x4f7bd4))
    {
        port_set8(&port, 0, 0x540390, 0);
        port_call_with(&port, 0x418840, screen, 0x41fc70, 0x514100, screen, 0, entry->edi, ebp);
    }
    else if (mode == port_u32(&port, 0, 0x4f7bd8))
    {
        port_set8(&port, 0, 0x540390, 0);
        port_call_with(&port, 0x471d90, mode, vertrix_lift_edx & 0xffff00ffu, 0x514124, screen, 0,
                       entry->edi, ebp);
        port_call_with(&port, 0x418840, screen, 0x41fd20, 0x514124, screen, 0, entry->edi, ebp);
    }
    port_set32(&port, 0, 0x532a58, port_u32(&port, 0, 0x532a98));
    return port_return(&port, port_u32(&port, ebp, -0x24u), entry->edx);
}
