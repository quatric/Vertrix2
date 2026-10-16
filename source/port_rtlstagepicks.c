#include "port_rtlstagepicks.h"

/* The stage picker screen. */

typedef struct
{
    Port *port;
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t esi;
    uint32_t edi;
    uint32_t ebp;
} Picker;

/* A call (with count stack arguments, nearest first) of the tracked registers. */
static void picker_call(Picker *p, uint32_t target, const uint32_t *stack, unsigned count)
{
    vertrix_lift_in_esi = p->esi;
    vertrix_lift_in_edi = p->edi;
    vertrix_lift_in_ebp = p->ebp;
    p->eax =
        lift_call_arguments(&p->port->env, target, p->eax, p->edx, p->ebx, p->ecx, stack, count);
    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    p->edx = vertrix_lift_edx;
}

static void call_with(Picker *p, uint32_t target, uint32_t eax)
{
    p->eax = eax;
    picker_call(p, target, NULL, 0);
}

/* Whether the key is down (0x476480 of the keyboard 0x54d640). */
static uint32_t key_down(Picker *p, uint32_t key)
{
    p->edx = key;
    call_with(p, 0x476480, 0x54d640);
    return p->eax;
}

/* The key's press taken (0x476320 of the keyboard). */
static void key_release(Picker *p, uint32_t key)
{
    p->edx = key;
    call_with(p, 0x476320, 0x54d640);
}

/* The key's press cleared (0x4762e0 of the keyboard). */
static void key_clear(Picker *p, uint32_t key)
{
    p->edx = key;
    call_with(p, 0x4762e0, 0x54d640);
}

/* The text at esi copied (two bytes a step, with its 0) into 0x5404b0; esi left past it. */
static void copy_line(Picker *p)
{
    uint32_t edi = 0x5404b0;
    uint8_t value;
    p->edi = edi;
    for (;;)
    {
        value = port_u8(p->port, p->esi, 0);
        port_set8(p->port, edi, 0, value);
        if (value == 0 || p->port->env.failed)
        {
            break;
        }
        value = port_u8(p->port, p->esi, 1);
        p->esi += 2;
        port_set8(p->port, edi, 1, value);
        edi += 2;
        if (value == 0)
        {
            break;
        }
    }
    p->eax = (p->eax & 0xffffff00u) | value;
}

/* The checkered strip (0x47bd80) at the column edx of the row 0x54059c, ecx wide and 14 high in
 * the colours 0x54d5f4/0x54d5f8. */
static void strip(Picker *p, uint32_t column, uint32_t width)
{
    uint32_t args[3];
    args[0] = 0xe;
    args[1] = port_u32(p->port, 0, 0x54d5f8);
    args[2] = port_u32(p->port, 0, 0x54d5f4);
    p->ecx = width;
    p->edx = column;
    p->ebx = port_u32(p->port, 0, 0x54059c);
    p->eax = port_u32(p->port, 0, 0x558c7c);
    picker_call(p, 0x47bd80, args, 3);
}

/* The level 0x5405a0 stepped down when above 0. */
static void level_down(Picker *p)
{
    p->ebx = port_u32(p->port, 0, 0x5405a0);
    if (p->ebx != 0)
    {
        p->esi = p->ebx - 1;
        port_set32(p->port, 0, 0x5405a0, p->esi);
    }
}

/* The level 0x5405a0 (loaded into *level) stepped up into *result while below the stage set's
 * count +0x5bc of 0x532928 (eax its count less one). */
static void level_up(Picker *p, uint32_t *level, uint32_t *result)
{
    p->eax = port_u32(p->port, port_u32(p->port, 0, 0x532928), 0x5bc) - 1;
    *level = port_u32(p->port, 0, 0x5405a0);
    if (p->eax > *level)
    {
        *result = *level + 1;
        port_set32(p->port, 0, 0x5405a0, *result);
    }
}

/* The stage set's entry at the level 0x5405a0 and line 0x5405a4 changed by target (0x412510 or
 * 0x412430). */
static void change(Picker *p, uint32_t target)
{
    p->ebx = port_u32(p->port, 0, 0x5405a4);
    p->edx = port_u32(p->port, 0, 0x5405a0);
    call_with(p, target, port_u32(p->port, 0, 0x532928));
}

/* The key pair (0x5f/0x60) changing the entry by target: twice with shift (0x2a or 0x36), once with
 * ctrl (0x1d) or 0x57 moving the level instead (down for 0x5f, up for 0x60). */
static void change_keys(Picker *p, uint32_t key, uint32_t target, int up)
{
    if (key_down(p, key) == 0)
    {
        return;
    }
    if (key_down(p, 0x2a) != 0 || key_down(p, 0x36) != 0)
    {
        p->ecx = 0;
        do
        {
            p->ecx++;
            change(p, target);
        } while (p->ecx < 2 && !p->port->env.failed);
        return;
    }
    if (key_down(p, 0x1d) == 0 && key_down(p, 0x57) == 0)
    {
        change(p, target);
        key_release(p, key);
        return;
    }
    if (up)
    {
        level_up(p, &p->edi, &p->eax);
    }
    else
    {
        level_down(p);
    }
    key_release(p, key);
}

/* Original 0x4212a0 (guarded 0x5141b4): the stage picker screen of the screen object eax. Once
 * (0x4d66cd of 0x5405a8) the eight line names 0x540578.. set (0x4ca280) and 0x4f9d80 registered
 * (0x4ec1f7); on its first showing (0x540598 clear) the level 0x5405a0 and line 0x5405a4 cleared
 * (0x4b7cd0). The screen prepared (0x4b7d10, 0x41dec0, 0x471e10, 0x419490, 0x471a70, 0x41aaf0,
 * 0x486d00 of 0x5b9c50, 0x4719f0) and the eight lines drawn 18 apart from row 0 (0x54059c, line
 * 0x5404a4): a strip, the name (0x4429a0, style 2 for the chosen line), a strip and the stage
 * set's entry (0x4125e0 into 0x5404a8, printed with 0x50dde8). Then finished (0x4194b0, 0x486da0,
 * 0x487020 with 0x5d) and the keys read (0x476480 of 0x54d640): 0x5d/0x62 the line down/up (with
 * ctrl or 0x57 the level), 0x5f/0x60 the entry changed (0x412510/0x412430), 2..9 the line picked,
 * 0x3d 0x4192a0 and escape (1) leaving (0x540598 cleared, 0x418840 with 0x421ac0). eax the
 * restored chain, edx kept. */
uint32_t vertrix_port_stage_picker_4212a0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x40
    };
    Port port;
    Picker p;
    uint32_t record;
    uint32_t screen;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    p.port = &port;
    p.ebp = entry->esp - 4;
    screen = entry->eax;
    record = p.ebp - 0x3c;
    port_set32(&port, p.ebp, 0, entry->ebp);
    port_set32(&port, p.ebp, -4u, entry->ebx);
    port_set32(&port, p.ebp, -8u, entry->ecx);
    port_set32(&port, p.ebp, -0xcu, entry->edx);
    port_set32(&port, p.ebp, -0x10u, entry->esi);
    port_set32(&port, p.ebp, -0x14u, entry->edi);
    port_set32(&port, p.ebp, -0x18u, screen);
    port_set32(&port, record, 0, port.env.chain);
    port.env.chain = record;
    p.ecx = 0x5141b4;
    p.ebx = 0x540578;
    p.esi = 0x513e60;
    p.edi = 1;
    port_set32(&port, p.ebp, -0x38u, 0x4ec1ec);
    port_set32(&port, p.ebp, -0x34u, p.ecx);
    port_set32(&port, p.ebp, -0x28u, p.ebx);
    port_set32(&port, p.ebp, -0x24u, p.esi);
    port_set32(&port, p.ebp, -0x20u, 0);
    p.edx = p.edi;
    port_set32(&port, p.ebp, -0x30u, p.edi);
    call_with(&p, 0x4d66cd, 0x5405a8);
    if (p.eax == 0)
    {
        p.edx = 0x50ddae;
        p.ecx = 2;
        p.esi = 4;
        call_with(&p, 0x4ca280, p.ebx);
        p.edx = 0x50ddb5;
        p.ebx = 3;
        port_set32(&port, p.ebp, -0x20u, p.edi);
        call_with(&p, 0x4ca280, 0x54057c);
        p.edx = 0x50ddba;
        p.edi = 5;
        port_set32(&port, p.ebp, -0x20u, p.ecx);
        call_with(&p, 0x4ca280, 0x540580);
        p.edx = 0x50ddc2;
        port_set32(&port, p.ebp, -0x20u, p.ebx);
        call_with(&p, 0x4ca280, 0x540584);
        p.edx = 0x50ddcc;
        port_set32(&port, p.ebp, -0x20u, p.esi);
        call_with(&p, 0x4ca280, 0x540588);
        p.edx = 0x50ddd3;
        port_set32(&port, p.ebp, -0x20u, p.edi);
        call_with(&p, 0x4ca280, 0x54058c);
        p.edx = 0x50ddd8;
        port_set32(&port, p.ebp, -0x20u, 6);
        call_with(&p, 0x4ca280, 0x540590);
        port_set32(&port, p.ebp, -0x20u, 7);
        p.edx = 0x50dde1;
        p.ecx = 8;
        call_with(&p, 0x4ca280, 0x540594);
        port_set32(&port, p.ebp, -0x20u, p.ecx);
        call_with(&p, 0x4ec1f7, 0x4f9d80);
    }
    if (port_u8(&port, 0, 0x540598) == 0)
    {
        p.ebx = 0;
        p.edx = (p.edx & 0xffffff00u) | 1;
        port_set32(&port, 0, 0x5405a4, 0);
        port_set32(&port, 0, 0x5405a0, 0);
        picker_call(&p, 0x4b7cd0, NULL, 0);
        port_set8(&port, 0, 0x540598, p.edx);
    }
    picker_call(&p, 0x4b7d10, NULL, 0);
    call_with(&p, 0x41dec0, screen);
    call_with(&p, 0x471e10, port_u32(&port, 0, 0x532928));
    call_with(&p, 0x419490, screen);
    picker_call(&p, 0x471a70, NULL, 0);
    call_with(&p, 0x41aaf0, screen);
    call_with(&p, 0x486d00, 0x5b9c50);
    p.edi = 0;
    call_with(&p, 0x4719f0, port_u32(&port, 0, 0x558c7c));
    port_set32(&port, 0, 0x54059c, p.edi);
    port_set32(&port, 0, 0x5404a4, p.edi);
    do
    {
        uint32_t row[1];
        strip(&p, 0, 0x46);
        p.esi = port_u32(&port, 0, 0x540578 + port_u32(&port, 0, 0x5404a4) * 4);
        copy_line(&p);
        row[0] = port_u32(&port, 0, 0x54059c) + 2;
        p.ecx = 2;
        p.edx = p.edi;
        p.ebx = port_u32(&port, 0, 0x5404a4) == port_u32(&port, 0, 0x5405a4) ? p.ecx : 0;
        p.eax = port_u32(&port, 0, 0x558c7c);
        picker_call(&p, 0x4429a0, row, 1);
        p.esi = port_u32(&port, 0, 0x54d5f4);
        p.edi = port_u32(&port, 0, 0x54d5f8);
        strip(&p, 0x48, 0x2d);
        p.ebx = port_u32(&port, 0, 0x5404a4);
        p.edx = port_u32(&port, 0, 0x5405a0);
        call_with(&p, 0x4125e0, port_u32(&port, 0, 0x532928));
        port_set32(&port, 0, 0x5404a8, p.eax);
        call_with(&p, 0x4ca070, p.ebp - 0x1c);
        {
            uint32_t args[3] = {p.ebp - 0x1c, 0x50dde8, port_u32(&port, 0, 0x5404a8)};
            p.edx = args[2];
            port_set32(&port, p.ebp, -0x30u, 2);
            p.eax = p.ebp - 0x1c;
            picker_call(&p, 0x4cdfb0, args, 3);
        }
        p.esi = port_u32(&port, p.ebp, -0x1cu);
        copy_line(&p);
        row[0] = port_u32(&port, 0, 0x54059c) + 2;
        p.ecx = 0x4a;
        p.ebx = 3;
        p.edx = p.edi;
        p.eax = port_u32(&port, 0, 0x558c7c);
        picker_call(&p, 0x4429a0, row, 1);
        p.ecx = 1;
        p.ebx = port_u32(&port, 0, 0x54059c) + 0x12;
        p.edx = 0;
        port_set32(&port, p.ebp, -0x30u, p.ecx);
        port_set32(&port, 0, 0x54059c, p.ebx);
        call_with(&p, 0x4ca210, p.ebp - 0x1c);
        p.edi = port_u32(&port, 0, 0x5404a4) + p.ecx;
        port_set32(&port, p.ebp, -0x30u, p.ecx);
        port_set32(&port, 0, 0x5404a4, p.edi);
    } while ((int32_t)p.edi < 8 && !port.env.failed);
    call_with(&p, 0x4194b0, screen);
    call_with(&p, 0x486da0, 0x5b9c50);
    p.edx = 0x5d;
    call_with(&p, 0x487020, 0x5b9c50);
    call_with(&p, 0x476480, 0x54d640);
    if (p.eax != 0)
    {
        if (key_down(&p, 0x1d) != 0 || key_down(&p, 0x57) != 0)
        {
            level_down(&p);
            key_release(&p, 0x5d);
        }
        else
        {
            key_release(&p, 0x5d);
            p.edx = port_u32(&port, 0, 0x5405a4);
            if (p.edx != 0)
            {
                p.ecx = p.edx - 1;
                port_set32(&port, 0, 0x5405a4, p.ecx);
            }
        }
    }
    if (key_down(&p, 0x62) != 0)
    {
        if (key_down(&p, 0x1d) != 0 || key_down(&p, 0x57) != 0)
        {
            level_up(&p, &p.edx, &p.ecx);
            key_release(&p, 0x62);
        }
        else
        {
            key_release(&p, 0x62);
            p.edi = port_u32(&port, 0, 0x5405a4);
            if (p.edi < 7)
            {
                p.eax = p.edi + 1;
                port_set32(&port, 0, 0x5405a4, p.eax);
            }
        }
    }
    change_keys(&p, 0x5f, 0x412510, 0);
    change_keys(&p, 0x60, 0x412430, 1);
    if (key_down(&p, 2) != 0)
    {
        key_clear(&p, 2);
        p.edx = 0;
        port_set32(&port, 0, 0x5405a4, p.edx);
    }
    if (key_down(&p, 3) != 0)
    {
        p.ecx = 1;
        key_clear(&p, 3);
        port_set32(&port, 0, 0x5405a4, p.ecx);
    }
    if (key_down(&p, 4) != 0)
    {
        p.ebx = 2;
        key_clear(&p, 4);
        port_set32(&port, 0, 0x5405a4, p.ebx);
    }
    if (key_down(&p, 5) != 0)
    {
        p.esi = 3;
        key_clear(&p, 5);
        port_set32(&port, 0, 0x5405a4, p.esi);
    }
    if (key_down(&p, 6) != 0)
    {
        p.edi = 4;
        key_clear(&p, 6);
        port_set32(&port, 0, 0x5405a4, p.edi);
    }
    if (key_down(&p, 7) != 0)
    {
        key_clear(&p, 7);
        port_set32(&port, 0, 0x5405a4, 5);
    }
    if (key_down(&p, 8) != 0)
    {
        key_clear(&p, 8);
        port_set32(&port, 0, 0x5405a4, 6);
    }
    if (key_down(&p, 9) != 0)
    {
        p.ecx = 7;
        key_clear(&p, 9);
        port_set32(&port, 0, 0x5405a4, p.ecx);
    }
    if (key_down(&p, 0x3d) != 0)
    {
        key_clear(&p, 0x3d);
        call_with(&p, 0x4192a0, screen);
    }
    if (key_down(&p, 1) != 0)
    {
        key_clear(&p, 1);
        p.edx &= 0xffff00ffu;
        port_set8(&port, 0, 0x540598, p.edx >> 8);
        p.edx = 0x421ac0;
        call_with(&p, 0x418840, screen);
    }
    port.env.chain = port_u32(&port, record, 0);
    return port_return(&port, port.env.chain, entry->edx);
}
