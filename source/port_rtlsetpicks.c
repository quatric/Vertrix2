#include "port_rtlsetpicks.h"

/* The stage set picker screen. */

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

static uint32_t g32(Picker *p, uint32_t address)
{
    return port_u32(p->port, 0, address);
}

static void s32(Picker *p, uint32_t address, uint32_t value)
{
    port_set32(p->port, 0, address, value);
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

/* The text at esi copied (two bytes a step, with its 0) into 0x5403a0; esi left past it. */
static void copy_line(Picker *p)
{
    uint32_t edi = 0x5403a0;
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

/* The line 0x5403a0 drawn (0x4429a0) at the column ecx of the row 0x54048c + 2 in the style
 * ebx. */
static void draw_line(Picker *p, uint32_t column, uint32_t style)
{
    uint32_t row[1];
    row[0] = g32(p, 0x54048c) + 2;
    p->ecx = column;
    p->ebx = style;
    p->edx = p->edi;
    p->eax = g32(p, 0x558c7c);
    picker_call(p, 0x4429a0, row, 1);
}

/* The checkered strip (0x47bd80) at the column edx of the row 0x54048c, ecx wide and 14 high in
 * the colours 0x54d5f4/0x54d5f8. */
static void strip(Picker *p, uint32_t column, uint32_t width)
{
    uint32_t args[3];
    args[0] = 0xe;
    args[1] = g32(p, 0x54d5f8);
    args[2] = g32(p, 0x54d5f4);
    p->ecx = width;
    p->edx = column;
    p->ebx = g32(p, 0x54048c);
    p->eax = g32(p, 0x558c7c);
    picker_call(p, 0x47bd80, args, 3);
}

/* The number printed (0x4ca070, 0x4cdfb0 with the format) into the text at ebp - slot and copied
 * to 0x5403a0: the header's with the value in ebx and ecx 2, a line's with it in edx. */
static void print_number(Picker *p, uint32_t slot, uint32_t format, uint32_t value, int header)
{
    uint32_t args[3];
    call_with(p, 0x4ca070, p->ebp - slot);
    args[0] = p->ebp - slot;
    args[1] = format;
    args[2] = value;
    if (header)
    {
        p->ebx = value;
        p->ecx = 2;
    }
    else
    {
        p->edx = value;
    }
    port_set32(p->port, p->ebp, -0x34u, header ? 2 : 4);
    p->eax = p->ebp - slot;
    picker_call(p, 0x4cdfb0, args, 3);
    p->edi = 0x5403a0;
    p->esi = port_u32(p->port, p->ebp, -slot);
    copy_line(p);
}

/* The row 0x54048c moved down 18 and the text at ebp - slot cleared (0x4ca210). */
static void next_row(Picker *p, uint32_t slot)
{
    p->ecx = 1;
    p->ebx = g32(p, 0x54048c) + 0x12;
    p->edx = 0;
    port_set32(p->port, p->ebp, -0x34u, p->ecx);
    s32(p, 0x54048c, p->ebx);
    call_with(p, 0x4ca210, p->ebp - slot);
}

/* The set's entry at the stage 0x540490 and line 0x540498 changed by target (0x412510 or
 * 0x412430). */
static void change(Picker *p, uint32_t target)
{
    p->ebx = g32(p, 0x540498);
    p->edx = g32(p, 0x540490);
    call_with(p, target, g32(p, 0x532928));
}

/* The stage set's stage count +0x5bc of 0x532928. */
static uint32_t stage_count(Picker *p)
{
    return port_u32(p->port, g32(p, 0x532928), 0x5bc);
}

/* The key pair (0x5f/0x60) changing the entry by target: twice with shift (0x2a or 0x36), with
 * ctrl (0x1d) or 0x57 the stage 0x540494 moved by one and with 0x38 by four (round the count). */
static void change_keys(Picker *p, uint32_t key, uint32_t target, int up)
{
    uint32_t count;
    uint32_t stage;
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
    if (key_down(p, 0x1d) != 0 || key_down(p, 0x57) != 0)
    {
        if (up)
        {
            stage = g32(p, 0x540494) + 1;
            p->esi = stage;
            count = stage_count(p);
            p->eax = count;
            s32(p, 0x540494, stage);
            if (count <= stage)
            {
                p->edx = stage - count;
                s32(p, 0x540494, p->edx);
            }
        }
        else
        {
            p->ebx = g32(p, 0x540494) - 1;
            s32(p, 0x540494, p->ebx);
            if ((int32_t)p->ebx < 0)
            {
                p->eax = stage_count(p);
                p->edi = p->ebx + p->eax;
                s32(p, 0x540494, p->edi);
            }
        }
    }
    else if (key_down(p, 0x38) != 0)
    {
        if (up)
        {
            stage = g32(p, 0x540494) + 4;
            p->edx = stage;
            count = stage_count(p);
            p->eax = count;
            s32(p, 0x540494, stage);
            if (count <= stage)
            {
                p->ebx = stage - count;
                s32(p, 0x540494, p->ebx);
            }
        }
        else
        {
            p->eax = g32(p, 0x540494) - 4;
            s32(p, 0x540494, p->eax);
            if ((int32_t)p->eax < 0)
            {
                p->eax = stage_count(p);
                p->ecx = g32(p, 0x540494) + p->eax;
                s32(p, 0x540494, p->ecx);
            }
        }
    }
    else
    {
        change(p, target);
    }
    key_release(p, key);
}

/* Original 0x4202a0 (guarded 0x514154): the stage set picker screen of the screen object eax.
 * Once (0x4d66cd of 0x5404a0) the eight line names 0x540468.. set (0x4ca280) and 0x4f9d70
 * registered (0x4ec1f7); on its first showing (0x540488 clear) the stage 0x540494, its number
 * 0x540490 and the line 0x540498 cleared (0x4b7cd0) and the header 0x54049c shown. The screen
 * prepared (0x4b7d10, 0x41dec0; the stage's number from 0x4f9c48 into 0x540490 and handed to
 * 0x46c5d0, -1 without the header; 0x419490, 0x471a70, 0x41aaf0, 0x486d00, 0x4719f0). With the
 * header: rows from 100 18 apart (0x54048c) of strips (0x47bd80) and texts (0x4429a0): the stage
 * (0x50dd98), whether it is in use (0x4126f0) and the eight lines (0x540394) with their entries
 * (0x4125e0 into 0x540398, 0x50ddaa), then 0x4194b0. Then finished (0x486da0, 0x487020 with 0x39,
 * 0x4719e0) and the keys read (0x476480 of 0x54d640): 0x39 0x4126d0, 0x16 the header toggled,
 * 0x5d/0x62 the line, 0x5f/0x60 the entry or stage, 0x2e 0x412650, 0x2f 0x412690, 2..9 the line
 * picked, 0x3d 0x4192a0 and escape (1) leaving (0x540488 cleared, 0x418840 with 0x420e10). eax
 * the restored chain, edx kept. */
uint32_t vertrix_port_set_picker_4202a0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x44
    };
    Port port;
    uint8_t stack[BELOW + 8];
    Picker p;
    uint32_t record;
    uint32_t screen;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    p.port = &port;
    p.ebp = entry->esp - 4;
    screen = entry->eax;
    record = p.ebp - 0x40;
    port_set32(&port, p.ebp, 0, entry->ebp);
    port_set32(&port, p.ebp, -4u, entry->ebx);
    port_set32(&port, p.ebp, -8u, entry->ecx);
    port_set32(&port, p.ebp, -0xcu, entry->edx);
    port_set32(&port, p.ebp, -0x10u, entry->esi);
    port_set32(&port, p.ebp, -0x14u, entry->edi);
    port_set32(&port, p.ebp, -0x18u, screen);
    port_set32(&port, record, 0, port.env.chain);
    port.env.chain = record;
    p.ecx = 0x514154;
    p.ebx = 0x540468;
    p.esi = 0x513e60;
    p.edi = 1;
    port_set32(&port, p.ebp, -0x3cu, 0x4ec1ec);
    port_set32(&port, p.ebp, -0x38u, p.ecx);
    port_set32(&port, p.ebp, -0x2cu, p.ebx);
    port_set32(&port, p.ebp, -0x28u, p.esi);
    port_set32(&port, p.ebp, -0x24u, 0);
    p.edx = p.edi;
    port_set32(&port, p.ebp, -0x34u, p.edi);
    call_with(&p, 0x4d66cd, 0x5404a0);
    if (p.eax == 0)
    {
        p.edx = 0x50dd5b;
        p.ecx = 2;
        p.esi = 4;
        call_with(&p, 0x4ca280, p.ebx);
        p.edx = 0x50dd62;
        p.ebx = 3;
        port_set32(&port, p.ebp, -0x24u, p.edi);
        call_with(&p, 0x4ca280, 0x54046c);
        p.edx = 0x50dd67;
        p.edi = 5;
        port_set32(&port, p.ebp, -0x24u, p.ecx);
        call_with(&p, 0x4ca280, 0x540470);
        p.edx = 0x50dd6f;
        port_set32(&port, p.ebp, -0x24u, p.ebx);
        call_with(&p, 0x4ca280, 0x540474);
        p.edx = 0x50dd79;
        port_set32(&port, p.ebp, -0x24u, p.esi);
        call_with(&p, 0x4ca280, 0x540478);
        p.edx = 0x50dd80;
        port_set32(&port, p.ebp, -0x24u, p.edi);
        call_with(&p, 0x4ca280, 0x54047c);
        p.edx = 0x50dd85;
        port_set32(&port, p.ebp, -0x24u, 6);
        call_with(&p, 0x4ca280, 0x540480);
        port_set32(&port, p.ebp, -0x24u, 7);
        p.edx = 0x50dd8e;
        p.ecx = 8;
        call_with(&p, 0x4ca280, 0x540484);
        port_set32(&port, p.ebp, -0x24u, p.ecx);
        call_with(&p, 0x4ec1f7, 0x4f9d70);
    }
    if (port_u8(&port, 0, 0x540488) == 0)
    {
        p.ebx = 0;
        p.edx = (p.edx & 0xffffff00u) | 1;
        s32(&p, 0x540498, 0);
        s32(&p, 0x540494, 0);
        s32(&p, 0x540490, 0);
        picker_call(&p, 0x4b7cd0, NULL, 0);
        p.eax = 1;
        port_set8(&port, 0, 0x540488, p.edx);
        s32(&p, 0x54049c, p.eax);
    }
    picker_call(&p, 0x4b7d10, NULL, 0);
    call_with(&p, 0x41dec0, screen);
    p.eax = port_u8(&port, 0, g32(&p, 0x540494) + 0x4f9c48);
    p.edx = g32(&p, 0x54049c);
    s32(&p, 0x540490, p.eax);
    p.edx = p.edx == 1 ? p.eax : 0xffffffffu;
    call_with(&p, 0x46c5d0, g32(&p, 0x532928));
    call_with(&p, 0x419490, screen);
    picker_call(&p, 0x471a70, NULL, 0);
    call_with(&p, 0x41aaf0, screen);
    call_with(&p, 0x486d00, 0x5b9c50);
    call_with(&p, 0x4719f0, g32(&p, 0x558c7c));
    if (g32(&p, 0x54049c) == 1)
    {
        s32(&p, 0x54048c, 0x64);
        strip(&p, 0, 0x46);
        p.esi = 0x50dd95;
        copy_line(&p);
        draw_line(&p, 2, 3);
        strip(&p, 0x48, 0x2d);
        print_number(&p, 0x20, 0x50dd98, g32(&p, 0x540494), 1);
        p.esi = 1;
        draw_line(&p, 0x4a, 2);
        p.edi = g32(&p, 0x54048c) + 0x12;
        port_set32(&port, p.ebp, -0x34u, p.esi);
        p.edx = 0;
        s32(&p, 0x54048c, p.edi);
        call_with(&p, 0x4ca210, p.ebp - 0x20);
        p.edi = 0x5403a0;
        port_set32(&port, p.ebp, -0x34u, p.esi);
        p.esi = 0x50dd9b;
        strip(&p, 0, 0x46);
        copy_line(&p);
        draw_line(&p, 2, 3);
        strip(&p, 0x48, 0x2d);
        p.edx = g32(&p, 0x540490);
        call_with(&p, 0x4126f0, g32(&p, 0x532928));
        {
            int used = p.eax == 1;
            p.esi = used ? 0x50dda3 : 0x50dda7;
            copy_line(&p);
            draw_line(&p, 0x4a, used ? 3 : 2);
        }
        p.edi = 0;
        s32(&p, 0x540394, p.edi);
        s32(&p, 0x54048c, g32(&p, 0x54048c) + 0x12);
        do
        {
            strip(&p, 0, 0x46);
            p.esi = g32(&p, 0x540468 + g32(&p, 0x540394) * 4);
            copy_line(&p);
            draw_line(&p, 2, g32(&p, 0x540394) == g32(&p, 0x540498) ? 2 : 0);
            p.esi = g32(&p, 0x54d5f4);
            p.edi = g32(&p, 0x54d5f8);
            strip(&p, 0x48, 0x2d);
            p.ebx = g32(&p, 0x540394);
            p.edx = g32(&p, 0x540490);
            call_with(&p, 0x4125e0, g32(&p, 0x532928));
            s32(&p, 0x540398, p.eax);
            print_number(&p, 0x1c, 0x50ddaa, g32(&p, 0x540398), 0);
            draw_line(&p, 0x4a, 3);
            next_row(&p, 0x1c);
            p.edi = g32(&p, 0x540394) + p.ecx;
            port_set32(&port, p.ebp, -0x34u, p.ecx);
            s32(&p, 0x540394, p.edi);
        } while ((int32_t)p.edi < 8 && !port.env.failed);
        call_with(&p, 0x4194b0, screen);
    }
    call_with(&p, 0x486da0, 0x5b9c50);
    p.edx = 0x39;
    call_with(&p, 0x487020, 0x5b9c50);
    picker_call(&p, 0x4719e0, NULL, 0);
    call_with(&p, 0x476480, 0x54d640);
    if (p.eax != 0)
    {
        key_release(&p, 0x39);
        p.edx = g32(&p, 0x540490);
        call_with(&p, 0x4126d0, g32(&p, 0x532928));
    }
    if (key_down(&p, 0x16) != 0)
    {
        key_release(&p, 0x16);
        p.edx = g32(&p, 0x54049c);
        p.eax = 1 - p.edx;
        s32(&p, 0x54049c, p.eax);
    }
    if (key_down(&p, 0x5d) != 0)
    {
        key_release(&p, 0x5d);
        p.ecx = g32(&p, 0x540498);
        if (p.ecx != 0)
        {
            p.ebx = p.ecx - 1;
            s32(&p, 0x540498, p.ebx);
        }
    }
    if (key_down(&p, 0x62) != 0)
    {
        key_release(&p, 0x62);
        p.esi = g32(&p, 0x540498);
        if (p.esi < 7)
        {
            p.edi = p.esi + 1;
            s32(&p, 0x540498, p.edi);
        }
    }
    change_keys(&p, 0x5f, 0x412510, 0);
    change_keys(&p, 0x60, 0x412430, 1);
    if (key_down(&p, 0x2e) != 0)
    {
        p.edx = g32(&p, 0x540490);
        call_with(&p, 0x412650, g32(&p, 0x532928));
        key_clear(&p, 0x2e);
    }
    if (key_down(&p, 0x2f) != 0)
    {
        p.edx = g32(&p, 0x540490);
        call_with(&p, 0x412690, g32(&p, 0x532928));
        key_clear(&p, 0x2f);
    }
    if (key_down(&p, 2) != 0)
    {
        p.ecx = 0;
        key_clear(&p, 2);
        s32(&p, 0x540498, p.ecx);
    }
    if (key_down(&p, 3) != 0)
    {
        p.ebx = 1;
        key_clear(&p, 3);
        s32(&p, 0x540498, p.ebx);
    }
    if (key_down(&p, 4) != 0)
    {
        p.esi = 2;
        key_clear(&p, 4);
        s32(&p, 0x540498, p.esi);
    }
    if (key_down(&p, 5) != 0)
    {
        p.edi = 3;
        key_clear(&p, 5);
        s32(&p, 0x540498, p.edi);
    }
    if (key_down(&p, 6) != 0)
    {
        key_clear(&p, 6);
        s32(&p, 0x540498, 4);
    }
    if (key_down(&p, 7) != 0)
    {
        key_clear(&p, 7);
        s32(&p, 0x540498, 5);
    }
    if (key_down(&p, 8) != 0)
    {
        p.ecx = 6;
        key_clear(&p, 8);
        s32(&p, 0x540498, p.ecx);
    }
    if (key_down(&p, 9) != 0)
    {
        p.ebx = 7;
        key_clear(&p, 9);
        s32(&p, 0x540498, p.ebx);
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
        port_set8(&port, 0, 0x540488, p.edx >> 8);
        p.edx = 0x420e10;
        call_with(&p, 0x418840, screen);
    }
    port.env.chain = port_u32(&port, record, 0);
    return port_return(&port, port.env.chain, entry->edx);
}
