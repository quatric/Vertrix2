#include "spawners.h"

/* Bob picks, a path wobble, the panel and banner spawns, the palette cube, the event stack push,
 * the scratch pair and the sound device release. */

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

/* The bob of 0x44ad20 and 0x44add0: when due words +0x4a `height` and +0x4c 5 (0x4ad530, which
 * when done hands over to `next`) and the fade (+0x4f 100, +0x50 7, 0x4ad580); once that is done
 * +0x93 is 0. While 0x532a7c is 1, 0x418110 matching the edx it leaves keeps (and returns) the
 * actor's +0x14c in 0x532a50. */
static uint32_t actor_bob_pick(PORT_SIGNATURE, uint32_t height, uint32_t next)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t esi = entry->esi;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x4ac500, actor, entry->edx, actor, actor);
    result = port_forward(&port, entry, 0x4ac520, actor, vertrix_lift_edx, actor, actor);
    if (result == 1)
    {
        esi = port_forward(&port, entry, 0x4ac540, actor, vertrix_lift_edx, actor, actor);
        port_forward_esi(&port, entry, 0x4ac5b0, actor, esi, actor, actor, esi);
        port_set16(&port, actor, 0x4a, height);
        port_set16(&port, actor, 0x4c, 5);
        if (port_forward_esi(&port, entry, 0x4ad530, actor, vertrix_lift_edx, actor, actor, esi) ==
            0)
        {
            port_forward_esi(&port, entry, 0x4ac8f0, actor, next, actor, actor, esi);
        }
        port_set8(&port, actor, 0x4f, 0x64);
        port_set16(&port, actor, 0x50, 7);
        result = port_forward_esi(&port, entry, 0x4ad580, actor, esi, actor, actor, esi);
        if (result == 0)
        {
            port_set8(&port, actor, 0x93, 0);
        }
    }
    if (port_u32(&port, 0, 0x532a7c) != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    result = port_forward_esi(&port, entry, 0x418110, result, 1, actor, actor, esi);
    if (result == vertrix_lift_edx)
    {
        result = port_u32(&port, actor, 0x14c);
        port_set32(&port, 0, 0x532a50, result);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x44ad20: height 0, next 0x44add0. */
uint32_t vertrix_port_actor_bob_pick_44ad20(PORT_SIGNATURE)
{
    return actor_bob_pick(calls, services, globals, entry, 0, 0x44add0);
}

/* Original 0x44add0: height 35, next 0x44ad20. */
uint32_t vertrix_port_actor_bob_pick_44add0(PORT_SIGNATURE)
{
    return actor_bob_pick(calls, services, globals, entry, 0x23, 0x44ad20);
}

/* Original 0x45d690: the actor shown (+0x93 1); when due it follows its path (0x4b65a0 with 10
 * left on the stack, 0x4ac980, 0x4b6540), turning about (+0x64 1 less itself) at the end, and
 * fades (+0x4f 50, +0x50 5, 0x4ad580); once that is done the state 0x45d740. */
uint32_t vertrix_port_actor_path_turn_45d690(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    static const uint32_t ten[1] = {0xa};
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t amount;
    uint32_t result;
    uint32_t ebx;
    uint32_t ecx;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set8(&port, actor, 0x93, 1);
    port_call_with(&port, 0x4ac500, actor, entry->edx, entry->ebx, entry->ecx, actor, actor, ebp);
    result = port_call_with(&port, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, entry->ecx, actor,
                            actor, ebp);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    amount = port_call_with(&port, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, entry->ecx, actor,
                            actor, ebp);
    port_set32(&port, ebp, -0x18u, amount);
    port_call_with(&port, 0x4ac5b0, actor, amount, entry->ebx, entry->ecx, actor, actor, ebp);
    result = call_frame(&port, 0x4b65a0, actor, vertrix_lift_edx, entry->ebx, 0, actor, actor, ebp,
                        ten, 1);
    ebx = sign16(result);
    ecx = call_frame(&port, 0x4ac980, actor, vertrix_lift_edx, ebx, 0, actor, actor, ebp, ten, 1);
    call_frame(&port, 0x4b6540, actor, sign16(ecx), ebx, ecx, actor, actor, ebp, ten, 1);
    if (ecx == 0)
    {
        port_set32(&port, actor, 0x64, 1 - port_u32(&port, actor, 0x64));
    }
    port_set8(&port, actor, 0x4f, 0x32);
    port_set16(&port, actor, 0x50, 5);
    result = call_frame(&port, 0x4ad580, actor, port_u32(&port, ebp, -0x18u), ebx, ecx, actor,
                        actor, ebp, ten, 1);
    if (result != 0)
    {
        return port_return(&port, result, entry->edx);
    }
    result = call_frame(&port, 0x4ac8f0, actor, 0x45d740, ebx, ecx, actor, actor, ebp, ten, 1);
    return port_return(&port, result, entry->edx);
}

/* Original 0x471020: a panel (0x308 bytes, 0x4ca000 and 0x4b2400) placed by 0x4adf20 at 0, set
 * up by 0x4b25b0 for the owner eax with the frame of 0x4f87fe (its x, y, width and height less
 * 14, the byte depth of 0x4f9bff and 2, 2, 0, 0, 1, 1, 1); 0x4b2d90 gives the result and the
 * panel is destroyed (method +0 with 2). */
uint32_t vertrix_port_panel_spawn_471020(PORT_SIGNATURE)
{
    static const uint32_t zeros[5] = {0, 0, 0, 0, 0};
    Port port;
    uint32_t owner = entry->eax;
    uint32_t panel;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t setup[10];
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    panel = port_call_with(&port, 0x4ca000, 0x308, entry->edx, entry->ebx, entry->ecx, entry->esi,
                           owner, entry->ebp);
    if (panel != 0)
    {
        panel = port_call_with(&port, 0x4b2400, panel, vertrix_lift_edx, entry->ebx, entry->ecx,
                               entry->esi, owner, entry->ebp);
    }
    call_frame(&port, 0x4adf20, panel, 0, 0, 0, panel, owner, entry->ebp, zeros, 5);
    setup[0] = sign16(port_u16(&port, 0, 0x4f8804));
    setup[1] = sign16(port_u16(&port, 0, 0x4f8808));
    setup[2] = sign16(port_u16(&port, 0, 0x4f880c) - 0xe);
    setup[3] = 2;
    setup[4] = 2;
    setup[5] = 0;
    setup[6] = 0;
    setup[7] = 1;
    setup[8] = 1;
    setup[9] = 1;
    ecx = sign16(port_u16(&port, 0, 0x4f8800));
    ebx = (uint32_t)(int32_t)(int8_t)port_u8(&port, 0, 0x4f9c02);
    call_frame(&port, 0x4b25b0, panel, owner, ebx, ecx, panel, owner, entry->ebp, setup, 10);
    result = port_call_with(&port, 0x4b2d90, panel, vertrix_lift_edx, ebx, ecx, panel, owner,
                            entry->ebp);
    if (panel != 0)
    {
        uint32_t methods = port_u32(&port, panel, 0x158);
        port_call_with(&port, port_u32(&port, methods, 0), panel, 2, ebx, methods, panel, result,
                       entry->ebp);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x472620: the banner actor (0x15c bytes, 0x4ca000 and 0x4abd70) placed by 0x4adf20 at
 * 320, 240, of kind 19 with the image 0x544a34 (0x4ac8d0), the frame 0x532a68, the speed 70, +0x4e
 * 100, hidden (+0x93 0), 0x4ac7b0, +0x150 1 and the state 0x45ad20, added to the list 0x54671c
 * (0x4b5e70). */
uint32_t vertrix_port_banner_actor_spawn_472620(PORT_SIGNATURE)
{
    static const uint32_t zeros[5] = {0, 0, 0, 0, 0};
    Port port;
    uint32_t banner;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    banner = port_forward(&port, entry, 0x4ca000, 0x15c, entry->edx, entry->ebx, entry->ecx);
    if (banner != 0)
    {
        banner =
            port_forward(&port, entry, 0x4abd70, banner, vertrix_lift_edx, entry->ebx, entry->ecx);
    }
    call_frame(&port, 0x4adf20, banner, 0x140, 0xf0, 0, banner, entry->edi, entry->ebp, zeros, 5);
    port_set32(&port, banner, 0, 0x13);
    port_forward_esi(&port, entry, 0x4ac8d0, banner, 0x544a34, 0xf0, 0, banner);
    port_forward_esi(&port, entry, 0x4ac710, banner, port_u32(&port, 0, 0x532a68), 0xf0, 0, banner);
    port_forward_esi(&port, entry, 0x4ac8a0, banner, 0x46, 0xf0, 0, banner);
    port_set8(&port, banner, 0x4e, 0x64);
    port_set8(&port, banner, 0x93, 0);
    port_forward_esi(&port, entry, 0x4ac7b0, banner, vertrix_lift_edx, 0xf0, 0, banner);
    port_set32(&port, banner, 0x150, 1);
    port_forward_esi(&port, entry, 0x4ac8f0, banner, 0x45ad20, 0xf0, 0, banner);
    result = port_forward_esi(&port, entry, 0x4b5e70, 0x54671c, banner, 0xf0, 0, banner);
    return port_return(&port, result, entry->edx);
}

/* Original 0x480ca0: the 3-3-2 palette cube at eax: the colour red, green and blue indexes
 * (r * 32 | g * 4 | b) hold r * 8, g * 8 and b * 16. */
uint32_t vertrix_port_palette_cube_480ca0(PORT_SIGNATURE)
{
    Port port;
    uint32_t palette = entry->eax;
    uint32_t red;
    uint32_t green;
    uint32_t blue;
    port_open(&port, calls, services, globals, entry);
    for (red = 0; red < 8; red++)
    {
        for (green = 0; green < 8; green++)
        {
            for (blue = 0; blue < 4; blue++)
            {
                uint32_t index = (red * 0x20 | green * 4 | blue) * 3;
                port_set8(&port, palette, index, red * 8);
                port_set8(&port, palette, index + 1, green * 8);
                port_set8(&port, palette, index + 2, blue * 0x10);
            }
        }
    }
    return port_return(&port, 0x4004, entry->edx);
}

/* Original 0x482060: the event stack (+0x208 the count, below 9) gets another 0x34-byte event:
 * dl, bl and ecx, then the eleven stack arguments (bytes, dwords and two words) as laid out. */
uint32_t vertrix_port_event_stack_push_482060(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 8
    };
    Port port;
    uint8_t stack[BELOW + 8 + 0x2c];
    uint32_t events = entry->eax;
    uint32_t count;
    uint32_t slot;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 11);
    port_set8(&port, entry->esp, -8u, entry->edx);
    count = port_u8(&port, events, 0x208);
    if ((int32_t)count >= 9)
    {
        return port_return(&port, count, entry->edx);
    }
    count = (count + 1) & 0xff;
    port_set8(&port, events, 0x208, count);
    slot = events + count * 0x34;
    port_set8(&port, slot, 1, entry->ebx);
    port_set32(&port, slot, 4, entry->ecx);
    port_set8(&port, slot, 0, entry->edx);
    port_set8(&port, slot, 8, port_u8(&port, entry->esp, 4));
    port_set32(&port, slot, 0xc, port_u32(&port, entry->esp, 8));
    port_set32(&port, slot, 0x10, port_u32(&port, entry->esp, 0xc));
    port_set8(&port, slot, 0x14, port_u8(&port, entry->esp, 0x10));
    port_set32(&port, slot, 0x2c, port_u32(&port, entry->esp, 0x14));
    port_set32(&port, slot, 0x18, port_u32(&port, entry->esp, 0x18));
    port_set32(&port, slot, 0x1c, port_u32(&port, entry->esp, 0x1c));
    port_set16(&port, slot, 0x20, port_u16(&port, entry->esp, 0x20));
    port_set16(&port, slot, 0x22, port_u16(&port, entry->esp, 0x24));
    port_set32(&port, slot, 0x24, port_u32(&port, entry->esp, 0x28));
    port_set32(&port, slot, 0x28, port_u32(&port, entry->esp, 0x2c));
    return port_return(&port, count * 0xd, port_u32(&port, entry->esp, 0x2c));
}

/* Original 0x482610: 0x482640 on eax with the scratch 0x4ec1a0 makes in the frame. */
uint32_t vertrix_port_scratch_pair_call_482610(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x10
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t scratch;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    scratch = port_call_with(&port, 0x4ec1a0, ebp - 0xc, entry->edx, entry->ebx, entry->eax,
                             entry->esi, entry->edi, ebp);
    result = port_call_with(&port, 0x482640, entry->eax, scratch, entry->ebx, entry->eax,
                            entry->esi, entry->edi, ebp);
    return port_return(&port, result, entry->edx);
}
