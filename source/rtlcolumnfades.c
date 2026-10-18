#include "rtlcolumnfades.h"

/* Screens faded in column by column. */

/* The registers 0x422c50 carries from call to call. */
typedef struct WipeRegisters
{
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t esi;
    uint32_t edi;
    uint32_t ebp;
} WipeRegisters;

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

static uint32_t call(Port *port, WipeRegisters *r, uint32_t target, const uint32_t *stack,
                     unsigned count)
{
    r->eax = call_frame(port, target, r->eax, r->edx, r->ebx, r->ecx, r->esi, r->edi, r->ebp, stack,
                        count);
    r->edx = vertrix_lift_edx;
    return r->eax;
}

/* Original 0x422c50 (guarded 0x5141fc): the level screen eax faded in across: the first time
 * (0x5405cc 0) 0x5405cc 1, the shown width 0x5405d0 0, 0x4b7cd0, 0x472020 and 0x41d640; then
 * 0x4b7d10, 0x41d670 with 2, 0x472350, the target width the +0x58 of 0x4b5eb0 of 0x54676c (or
 * 0), and the display locked (0x486d00 of 0x5b9c50); with none shown the whole old picture
 * 0x558c80 copied (0x47ce10). Short of the target, the old picture's next columns (0x4f9d94 of
 * them, to its width +4) are copied when the screen's +0xc8 is set, then the new picture 0x558c88
 * from the shown width to the target; with +0xc8 set each of those 0x4f9d94 columns becomes a
 * sprite (0x4723a0 of the new picture's height with 1) across at the column, given by +0xc8 2 the
 * fade +0x4e 100 less its step, 3 the fade 0 and +0x48 100 less its step, 4 +0x48 its step (steps
 * of 100 / (0x4f9d94 + 1)), and +0x93/+0x94/+0x95 1; then 0x472460 of the screen and 0x472440.
 * Then 0x41d6d0, the display unlocked (0x486da0, 0x487020, 0x486ed0), the shown width the target,
 * 0x41d660, 0x41de80, 0x41ddf0, and when done (0x472360 1) 0x472330, 0x41ac80, 0x418830 and
 * 0x5405cc 0. eax the restored chain, edx kept. */
uint32_t vertrix_port_screen_wipe_in_422c50(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x48
    };
    Port port;
    uint8_t stack[BELOW + 8];
    WipeRegisters r;
    uint32_t ebp = entry->esp - 4;
    uint32_t record = ebp - 0x44;
    uint32_t screen = entry->eax;
    uint32_t target;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    port_set32(&port, ebp, -0x24u, screen);
    port_set32(&port, record, 0, port.env.chain);
    port.env.chain = record;
    r.eax = (record & 0xffff00ffu) | (port_u8(&port, 0, 0x5405cc) << 8);
    r.edx = 0x4ec1ec;
    r.ebx = 0;
    r.ecx = 0x5141fc;
    r.esi = entry->esi;
    r.edi = entry->edi;
    r.ebp = ebp;
    port_set32(&port, ebp, -0x40u, 0x4ec1ec);
    port_set32(&port, ebp, -0x3cu, 0x5141fc);
    port_set32(&port, ebp, -0x38u, 0);
    if (port_u8(&port, 0, 0x5405cc) == 0)
    {
        r.edx = (r.edx & 0xffffff00u) | 1;
        port_set32(&port, 0, 0x5405d0, 0);
        port_set8(&port, 0, 0x5405cc, 1);
        call(&port, &r, 0x4b7cd0, NULL, 0);
        call(&port, &r, 0x472020, NULL, 0);
        r.eax = screen;
        call(&port, &r, 0x41d640, NULL, 0);
    }
    call(&port, &r, 0x4b7d10, NULL, 0);
    r.eax = screen;
    r.edx = 2;
    call(&port, &r, 0x41d670, NULL, 0);
    call(&port, &r, 0x472350, NULL, 0);
    r.eax = 0x54676c;
    if (call(&port, &r, 0x4b5eb0, NULL, 0) != 0)
    {
        r.eax = port_u32(&port, r.eax, 0x58);
    }
    port_set32(&port, ebp, -0x2cu, r.eax);
    r.eax = 0x5b9c50;
    call(&port, &r, 0x486d00, NULL, 0);
    if (port_u32(&port, 0, 0x5405d0) == 0)
    {
        uint32_t picture = port_u32(&port, 0, 0x558c80);
        uint32_t args[4];
        args[0] = 0;
        args[1] = 0;
        args[2] = port_u32(&port, picture, 4);
        args[3] = port_u32(&port, picture, 8);
        r.eax = port_u32(&port, 0, 0x558c7c);
        r.edx = picture;
        r.ebx = 0;
        r.ecx = 0;
        call(&port, &r, 0x47ce10, args, 4);
    }
    target = port_u32(&port, ebp, -0x2cu);
    r.esi = target;
    if (target != port_u32(&port, 0, 0x5405d0))
    {
        if (port_u8(&port, screen, 0xc8) != 0)
        {
            uint32_t old = port_u32(&port, 0, 0x558c80);
            uint32_t shown = port_u32(&port, 0, 0x5405d0);
            uint32_t end;
            uint32_t args[4];
            r.edi = port_u32(&port, 0, 0x4f9d94);
            end = shown + r.edi;
            if (end >= port_u32(&port, old, 4))
            {
                end = port_u32(&port, old, 4);
            }
            args[0] = shown;
            args[1] = 0;
            args[2] = end - shown;
            args[3] = port_u32(&port, old, 8);
            r.esi = shown;
            r.eax = port_u32(&port, 0, 0x558c7c);
            r.edx = old;
            r.ebx = shown;
            r.ecx = 0;
            call(&port, &r, 0x47ce10, args, 4);
        }
        {
            uint32_t shown = port_u32(&port, 0, 0x5405d0);
            uint32_t args[4];
            args[0] = shown;
            args[1] = 0;
            args[2] = port_u32(&port, ebp, -0x2cu) - shown;
            args[3] = port_u32(&port, port_u32(&port, 0, 0x558c80), 8);
            r.eax = port_u32(&port, 0, 0x558c7c);
            r.edx = port_u32(&port, 0, 0x558c88);
            r.ebx = shown;
            r.ecx = 0;
            call(&port, &r, 0x47ce10, args, 4);
        }
        if (port_u8(&port, screen, 0xc8) != 0)
        {
            uint32_t step;
            LiftFlags flags = {0};
            r.ebx = port_u32(&port, 0, 0x4f9d94) + 1;
            r.eax = 0x64;
            r.edx = 0;
            lift_div1(32, r.ebx, &r.eax, &r.edx, &flags);
            step = r.eax;
            r.esi = port_u32(&port, ebp, -0x2cu);
            r.edi = 0;
            r.ecx = port_u32(&port, 0, 0x4f9d94);
            port_set32(&port, ebp, -0x30u, 0);
            port_set32(&port, ebp, -0x28u, 0);
            r.edx = step;
            if (r.ecx != 0)
            {
                r.edi = step;
                port_set32(&port, ebp, -0x20u, step);
                port_set8(&port, ebp, -0x18u, step);
                r.eax = (step & 0xffff0000u) | (step & 0xff);
                port_set8(&port, ebp, -0x1cu, step);
                do
                {
                    if (r.esi < port_u32(&port, port_u32(&port, 0, 0x558c80), 4))
                    {
                        uint32_t args[1];
                        uint32_t sprite;
                        r.eax = port_u32(&port, 0, 0x558c88);
                        args[0] = port_u32(&port, r.eax, 8);
                        r.ecx = 1;
                        r.edx = r.esi;
                        r.ebx = 0;
                        sprite = call(&port, &r, 0x4723a0, args, 1);
                        r.edx = sprite;
                        if (sprite != 0)
                        {
                            uint32_t kind;
                            r.ebx = port_u32(&port, ebp, -0x30u);
                            port_set16(&port, sprite, 0x16, r.ebx);
                            r.ebx = screen;
                            port_set16(&port, sprite, 0xe, r.esi);
                            kind = port_u8(&port, screen, 0xc8);
                            r.ecx = (r.ecx & 0xffffff00u) | kind;
                            if (kind == 2)
                            {
                                uint32_t fade = port_u8(&port, ebp, -0x1cu);
                                r.ebx = (r.ebx & 0xffffff00u) | ((0x64 - fade) & 0xff);
                                r.ecx = (r.ecx & 0xffff00ffu) | (fade << 8);
                                port_set8(&port, sprite, 0x93, 1);
                                port_set8(&port, sprite, 0x4e, 0x64 - fade);
                            }
                            else if (kind == 3)
                            {
                                port_set8(&port, sprite, 0x4e, 0);
                                r.ebx = 0x64 - r.edi;
                                port_set8(&port, sprite, 0x93, 1);
                                port_set16(&port, sprite, 0x48, r.ebx);
                            }
                            else if (kind == 4)
                            {
                                port_set16(&port, sprite, 0x48, r.edi);
                            }
                            port_set8(&port, sprite, 0x94, 1);
                            port_set8(&port, sprite, 0x95, 1);
                        }
                    }
                    {
                        uint32_t fade =
                            (port_u8(&port, ebp, -0x1cu) + port_u8(&port, ebp, -0x18u)) & 0xff;
                        r.eax = (r.eax & 0xffffff00u) | port_u8(&port, ebp, -0x18u);
                        r.edx = port_u32(&port, ebp, -0x20u);
                        r.esi++;
                        port_set8(&port, ebp, -0x1cu, fade);
                        r.ebx = port_u32(&port, ebp, -0x28u) + 1;
                        r.edi += r.edx;
                        r.edx = port_u32(&port, 0, 0x4f9d94);
                        port_set32(&port, ebp, -0x28u, r.ebx);
                    }
                } while (r.ebx < r.edx && !port.env.failed);
            }
            r.eax = port_u32(&port, 0, 0x558c7c);
            call(&port, &r, 0x472460, NULL, 0);
            call(&port, &r, 0x472440, NULL, 0);
        }
    }
    r.eax = screen;
    call(&port, &r, 0x41d6d0, NULL, 0);
    r.eax = 0x5b9c50;
    call(&port, &r, 0x486da0, NULL, 0);
    r.eax = 0x5b9c50;
    call(&port, &r, 0x487020, NULL, 0);
    r.eax = 0x5b9c50;
    call(&port, &r, 0x486ed0, NULL, 0);
    port_set32(&port, 0, 0x5405d0, port_u32(&port, ebp, -0x2cu));
    r.eax = screen;
    call(&port, &r, 0x41d660, NULL, 0);
    r.eax = screen;
    call(&port, &r, 0x41de80, NULL, 0);
    r.eax = screen;
    call(&port, &r, 0x41ddf0, NULL, 0);
    if (call(&port, &r, 0x472360, NULL, 0) == 1)
    {
        call(&port, &r, 0x472330, NULL, 0);
        r.eax = screen;
        call(&port, &r, 0x41ac80, NULL, 0);
        r.eax = screen;
        call(&port, &r, 0x418830, NULL, 0);
        port_set8(&port, 0, 0x5405cc, 0);
    }
    port.env.chain = port_u32(&port, record, 0);
    return port_return(&port, port_u32(&port, record, 0), entry->edx);
}
