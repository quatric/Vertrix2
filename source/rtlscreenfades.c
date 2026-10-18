#include "rtlscreenfades.h"

/* Screens faded in row by row. */

/* The registers 0x4220d0 carries from call to call. */
typedef struct FadeRegisters
{
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t esi;
    uint32_t edi;
    uint32_t ebp;
} FadeRegisters;

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

static uint32_t call(Port *port, FadeRegisters *r, uint32_t target, const uint32_t *stack,
                     unsigned count)
{
    r->eax = call_frame(port, target, r->eax, r->edx, r->ebx, r->ecx, r->esi, r->edi, r->ebp, stack,
                        count);
    r->edx = vertrix_lift_edx;
    return r->eax;
}

/* The screen 0x558c7c copied (0x47ce10) from the picture `from` for the rows `first` on,
 * `rows` many, at the width +4 of 0x558c80. */
static void copy_rows(Port *port, FadeRegisters *r, uint32_t from, uint32_t first, uint32_t rows)
{
    uint32_t stack[4];
    stack[0] = 0;
    stack[1] = first;
    stack[2] = r->esi;
    stack[3] = rows;
    r->eax = port_u32(port, 0, 0x558c7c);
    r->edx = from;
    r->ebx = 0;
    r->ecx = first;
    call(port, r, 0x47ce10, stack, 4);
}

/* Original 0x4220d0 (guarded 0x5141f0): the level screen eax faded in: the first time
 * (0x5405b6 0) 0x5405b6 1, the shown height 0x5405b8 0, 0x4b7cd0, 0x4721e0 and 0x41d640; then
 * 0x4b7d10, 0x41d670 with 3, 0x472350, the target height the +0x58 of 0x4b5eb0 of 0x54676c (or
 * 0), and the display locked (0x486d00 of 0x5b9c50); with none shown the whole old picture
 * 0x558c80 copied (0x47ce10). Short of the target, the old picture's next rows (0x4f9d90 of
 * them, to its height +8) are copied when the screen's +0xc8 is set, then the new picture
 * 0x558c88 from the shown height to the target; with +0xc8 set each of those 0x4f9d90 rows
 * becomes a sprite (0x4723a0 of the new picture's width with 1) at down the row, given by +0xc8
 * 2 the fade +0x4e 100 less its step, 3 the fade 0 and +0x48 100 less its step, 4 +0x48 its step
 * (steps of 100 / (0x4f9d90 + 1)), and +0x93/+0x94/+0x95 1; then 0x472460 of the screen and
 * 0x472440. Then 0x41d6d0, the display unlocked (0x486da0, 0x487020, 0x486ed0), the shown height
 * the target, 0x41d660, 0x41de80, 0x41ddf0, and when done (0x472360 1) 0x472330, 0x41ac80,
 * 0x418830 and 0x5405b6 0. eax the restored chain, edx kept. */
uint32_t vertrix_port_screen_fade_in_4220d0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x48
    };
    Port port;
    uint8_t stack[BELOW + 8];
    FadeRegisters r;
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
    r.eax = (record & 0xffff00ffu) | (port_u8(&port, 0, 0x5405b6) << 8);
    r.edx = 0x4ec1ec;
    r.ebx = 0;
    r.ecx = 0x5141f0;
    r.esi = entry->esi;
    r.edi = entry->edi;
    r.ebp = ebp;
    port_set32(&port, ebp, -0x40u, 0x4ec1ec);
    port_set32(&port, ebp, -0x3cu, 0x5141f0);
    port_set32(&port, ebp, -0x38u, 0);
    if (port_u8(&port, 0, 0x5405b6) == 0)
    {
        r.edx = (r.edx & 0xffffff00u) | 1;
        port_set32(&port, 0, 0x5405b8, 0);
        port_set8(&port, 0, 0x5405b6, 1);
        call(&port, &r, 0x4b7cd0, NULL, 0);
        call(&port, &r, 0x4721e0, NULL, 0);
        r.eax = screen;
        call(&port, &r, 0x41d640, NULL, 0);
    }
    call(&port, &r, 0x4b7d10, NULL, 0);
    r.eax = screen;
    r.edx = 3;
    call(&port, &r, 0x41d670, NULL, 0);
    call(&port, &r, 0x472350, NULL, 0);
    r.eax = 0x54676c;
    if (call(&port, &r, 0x4b5eb0, NULL, 0) != 0)
    {
        r.eax = port_u32(&port, r.eax, 0x58);
    }
    port_set32(&port, ebp, -0x30u, r.eax);
    r.eax = 0x5b9c50;
    call(&port, &r, 0x486d00, NULL, 0);
    if (port_u32(&port, 0, 0x5405b8) == 0)
    {
        uint32_t picture = port_u32(&port, 0, 0x558c80);
        uint32_t stack[4];
        stack[0] = 0;
        stack[1] = 0;
        stack[2] = port_u32(&port, picture, 4);
        stack[3] = port_u32(&port, picture, 8);
        r.eax = port_u32(&port, 0, 0x558c7c);
        r.edx = picture;
        r.ebx = 0;
        r.ecx = 0;
        call(&port, &r, 0x47ce10, stack, 4);
    }
    target = port_u32(&port, ebp, -0x30u);
    r.esi = target;
    if (target != port_u32(&port, 0, 0x5405b8))
    {
        if (port_u8(&port, screen, 0xc8) != 0)
        {
            uint32_t old = port_u32(&port, 0, 0x558c80);
            uint32_t shown = port_u32(&port, 0, 0x5405b8);
            uint32_t end;
            r.edi = port_u32(&port, 0, 0x4f9d90);
            end = shown + r.edi;
            if (end >= port_u32(&port, old, 8))
            {
                end = port_u32(&port, old, 8);
            }
            r.esi = port_u32(&port, old, 4);
            copy_rows(&port, &r, old, shown, end - shown);
        }
        {
            uint32_t shown = port_u32(&port, 0, 0x5405b8);
            uint32_t rows = port_u32(&port, ebp, -0x30u) - shown;
            uint32_t stack[4];
            stack[0] = 0;
            stack[1] = shown;
            stack[2] = port_u32(&port, port_u32(&port, 0, 0x558c80), 4);
            stack[3] = rows;
            r.eax = port_u32(&port, 0, 0x558c7c);
            r.edx = port_u32(&port, 0, 0x558c88);
            r.ebx = 0;
            r.ecx = shown;
            call(&port, &r, 0x47ce10, stack, 4);
        }
        if (port_u8(&port, screen, 0xc8) != 0)
        {
            uint32_t step;
            LiftFlags flags = {0};
            r.ecx = port_u32(&port, 0, 0x4f9d90) + 1;
            r.eax = 0x64;
            r.edx = 0;
            lift_div1(32, r.ecx, &r.eax, &r.edx, &flags);
            step = r.eax;
            port_set32(&port, ebp, -0x2cu, 0);
            port_set32(&port, ebp, -0x28u, 0);
            r.edi = 0;
            r.edx = step;
            r.eax = port_u32(&port, 0, 0x4f9d90);
            r.esi = port_u32(&port, ebp, -0x30u);
            if (r.eax != 0)
            {
                r.eax = (r.eax & 0xffff0000u) | (step & 0xff);
                r.edi = step;
                port_set32(&port, ebp, -0x20u, step);
                port_set8(&port, ebp, -0x1cu, step);
                port_set8(&port, ebp, -0x18u, step);
                do
                {
                    if (r.esi < port_u32(&port, port_u32(&port, 0, 0x558c80), 8))
                    {
                        uint32_t one[1] = {1};
                        uint32_t sprite;
                        r.eax = port_u32(&port, 0, 0x558c88);
                        r.ebx = r.esi;
                        r.edx = 0;
                        r.ecx = port_u32(&port, r.eax, 4);
                        sprite = call(&port, &r, 0x4723a0, one, 1);
                        r.edx = sprite;
                        if (sprite != 0)
                        {
                            uint32_t kind;
                            r.ecx = port_u32(&port, ebp, -0x2cu);
                            port_set16(&port, sprite, 0xe, r.ecx);
                            r.ecx = screen;
                            port_set16(&port, sprite, 0x16, r.esi);
                            kind = port_u8(&port, screen, 0xc8);
                            r.ebx = (r.ebx & 0xffffff00u) | kind;
                            if (kind == 2)
                            {
                                uint32_t fade = port_u8(&port, ebp, -0x18u);
                                r.ecx = (r.ecx & 0xffffff00u) | ((0x64 - fade) & 0xff);
                                r.ebx = (r.ebx & 0xffff00ffu) | (fade << 8);
                                port_set8(&port, sprite, 0x93, 1);
                                port_set8(&port, sprite, 0x4e, 0x64 - fade);
                            }
                            else if (kind == 3)
                            {
                                port_set8(&port, sprite, 0x4e, 0);
                                r.ecx = 0x64 - r.edi;
                                port_set8(&port, sprite, 0x93, 1);
                                port_set16(&port, sprite, 0x48, r.ecx);
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
                            (port_u8(&port, ebp, -0x18u) + port_u8(&port, ebp, -0x1cu)) & 0xff;
                        r.edx = port_u32(&port, ebp, -0x20u);
                        r.eax = (r.eax & 0xffffff00u) | port_u8(&port, ebp, -0x1cu);
                        r.ecx = port_u32(&port, 0, 0x4f9d90);
                        r.esi++;
                        r.edi += r.edx;
                        r.edx = port_u32(&port, ebp, -0x28u) + 1;
                        r.ebx = (r.ebx & 0xffff00ffu) | (fade << 8);
                        port_set8(&port, ebp, -0x18u, fade);
                        port_set32(&port, ebp, -0x28u, r.edx);
                    }
                } while (r.edx < r.ecx && !port.env.failed);
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
    port_set32(&port, 0, 0x5405b8, port_u32(&port, ebp, -0x30u));
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
        r.ecx &= 0xffffff00u;
        call(&port, &r, 0x418830, NULL, 0);
        port_set8(&port, 0, 0x5405b6, 0);
    }
    port.env.chain = port_u32(&port, record, 0);
    return port_return(&port, port_u32(&port, record, 0), entry->edx);
}
