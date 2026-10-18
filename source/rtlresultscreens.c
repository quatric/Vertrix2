#include "rtlresultscreens.h"

/* The results screen's texts and actors. */

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
} Screen;

/* A call (with count stack arguments, nearest first) of the tracked registers. */
static void screen_call(Screen *s, uint32_t target, const uint32_t *stack, unsigned count)
{
    s->eax = port_call_registers(s->port, target, s->eax, s->edx, s->ebx, s->ecx, s->esi, s->edi,
                                 s->ebp, stack, count);
    s->edx = vertrix_lift_edx;
}

static void call_with(Screen *s, uint32_t target, uint32_t eax)
{
    s->eax = eax;
    screen_call(s, target, NULL, 0);
}

static uint32_t local(Screen *s, uint32_t offset)
{
    return port_u32(s->port, s->ebp, offset);
}

static void set_local(Screen *s, uint32_t offset, uint32_t value)
{
    port_set32(s->port, s->ebp, offset, value);
}

static uint32_t word(Screen *s, uint32_t address)
{
    return port_u16(s->port, 0, address);
}

/* The dword at address shifted down 16 (the signed word above it). */
static uint32_t high(Screen *s, uint32_t address)
{
    return (uint32_t)((int32_t)port_u32(s->port, 0, address) >> 16);
}

static uint32_t sign16(uint32_t value)
{
    return (uint32_t)(int32_t)(int16_t)value;
}

static uint32_t low_word(uint32_t reg, uint32_t value)
{
    return (reg & 0xffff0000u) | (value & 0xffff);
}

/* An actor of size made (0x4ca000) and, when there is one, built by maker; with a state register
 * pair (before, after) those are set first and the state at ebp - 0x6c set around the call. */
static void make(Screen *s, uint32_t size, uint32_t maker, uint32_t *before_reg, uint32_t before,
                 uint32_t *after_reg, uint32_t after)
{
    call_with(s, 0x4ca000, size);
    if (s->eax != 0)
    {
        if (before_reg != NULL)
        {
            *before_reg = before;
            *after_reg = after;
            set_local(s, -0x40u, s->eax);
            set_local(s, -0x6cu, before);
        }
        screen_call(s, maker, NULL, 0);
        if (before_reg != NULL)
        {
            set_local(s, -0x6cu, after);
        }
    }
}

/* The actor at eax reset (0x4adf20 with five 0s). */
static void reset(Screen *s, uint32_t actor)
{
    static const uint32_t zeros[5] = {0, 0, 0, 0, 0};
    s->eax = actor;
    s->ecx = 0;
    s->ebx = 0;
    s->edx = 0;
    screen_call(s, 0x4adf20, zeros, 5);
}

/* The actor placed (0x4b54d0) with the stack value. */
static void place(Screen *s, uint32_t actor, uint32_t value)
{
    uint32_t args[1];
    args[0] = value;
    s->eax = actor;
    screen_call(s, 0x4b54d0, args, 1);
}

/* The actor shown (0x4ac7b0 with 2). */
static void show(Screen *s, uint32_t actor)
{
    s->edx = 2;
    s->eax = actor;
    screen_call(s, 0x4ac7b0, NULL, 0);
}

/* The actor added to the list 0x54671c (0x4b5e70). */
static void add(Screen *s, uint32_t actor)
{
    s->edx = actor;
    s->eax = 0x54671c;
    screen_call(s, 0x4b5e70, NULL, 0);
}

static void flags(Screen *s, uint32_t actor, uint32_t first, uint32_t last)
{
    port_set8(s->port, actor, 0x94, first);
    port_set8(s->port, actor, 0x95, first);
    port_set8(s->port, actor, 0x110, last);
}

/* A header picture actor (0x4b5400 with the states) at the rectangle from the table at table,
 * raised 24 in the one-player game (0x532a84 1, read into the register test), shown, flagged and
 * keyed (0x4ac4e0 0xffffff) and added. */
static void header(Screen *s, uint32_t *before_reg, uint32_t before, uint32_t *after_reg,
                   uint32_t table, int test_in_eax)
{
    uint32_t actor;
    uint32_t mode;
    make(s, 0x160, 0x4b5400, before_reg, before, after_reg, 7);
    actor = s->eax;
    s->edi = actor;
    reset(s, actor);
    mode = port_u32(s->port, 0, 0x532a84);
    if (test_in_eax)
    {
        s->eax = mode;
    }
    else
    {
        s->ebx = mode;
    }
    s->esi = actor;
    s->ebx = high(s, table + 4);
    s->edx = high(s, table);
    s->ecx = word(s, table + 0xa);
    if (mode == 1)
    {
        s->eax = (low_word(s->eax, word(s, table + 0xe)) - 0x18) & 0xffff;
    }
    else
    {
        s->eax = word(s, table + 0xe);
    }
    place(s, actor, s->eax);
    s->edx = 2;
    s->eax = actor;
    port_set16(s->port, actor, 0x48, 0);
    screen_call(s, 0x4ac7b0, NULL, 0);
    s->ebx = 0;
    s->edx = 0xffffff;
    s->eax = actor;
    flags(s, actor, 1, 1);
    screen_call(s, 0x4ac4e0, NULL, 0);
    add(s, actor);
}

/* A name picture actor at the rectangle from the table at table (its width ecx), raised to the
 * front (+0x48 40, +0x52 8), shown, flagged and keyed (0x4ac4e0 0xff) and added. */
static void name(Screen *s, uint32_t actor, uint32_t table, uint32_t width)
{
    s->esi = actor;
    reset(s, actor);
    s->ebx = high(s, table + 4);
    s->edx = high(s, table);
    s->eax = word(s, table + 0xe);
    s->ecx = width;
    place(s, actor, s->eax);
    s->edx = 2;
    port_set16(s->port, actor, 0x48, 0x28);
    s->eax = actor;
    port_set8(s->port, actor, 0x52, 8);
    screen_call(s, 0x4ac7b0, NULL, 0);
    s->ebx = 0;
    s->edx = 0xff;
    s->eax = actor;
    flags(s, actor, 1, 1);
    screen_call(s, 0x4ac4e0, NULL, 0);
}

/* A bar actor (0x4b5400 with the registers as they are) at the row 0x533d44 + offset across the
 * screen (640, 1), layered at di, shown and added; the actor kept at ebp + slot. */
static void bar(Screen *s, uint32_t slot, uint32_t offset)
{
    uint32_t actor;
    uint32_t args[1] = {1};
    make(s, 0x160, 0x4b5400, NULL, 0, NULL, 0);
    actor = s->eax;
    set_local(s, slot, actor);
    reset(s, actor);
    s->eax = low_word(s->eax, word(s, 0x533d44)) + offset;
    s->ecx = 0x280;
    s->edx = 0;
    s->ebx = sign16(s->eax);
    s->eax = actor;
    screen_call(s, 0x4b54d0, args, 1);
    port_set8(s->port, actor, 0x52, 8);
    s->edx = 2;
    port_set16(s->port, actor, 0x48, s->edi);
    s->eax = actor;
    screen_call(s, 0x4ac7b0, NULL, 0);
}

/* A ramp actor at the row 0x4f885c + offset in the column 0x4f8856 (width 0x4f8860), layered at
 * di, shown and added; kept at ebp + slot. */
static void ramp(Screen *s, uint32_t slot, uint32_t offset)
{
    uint32_t actor;
    uint32_t args[1] = {1};
    make(s, 0x160, 0x4b5400, NULL, 0, NULL, 0);
    actor = s->eax;
    set_local(s, slot, actor);
    reset(s, actor);
    s->eax = low_word(s->eax, word(s, 0x4f885c)) + offset;
    s->ecx = word(s, 0x4f8860);
    s->edx = high(s, 0x4f8856);
    s->ebx = sign16(s->eax);
    s->eax = actor;
    screen_call(s, 0x4b54d0, args, 1);
    port_set8(s->port, actor, 0x52, 8);
    flags(s, actor, 0, 0);
    s->edx = 2;
    port_set16(s->port, actor, 0x48, s->edi);
    s->eax = actor;
    screen_call(s, 0x4ac7b0, NULL, 0);
    add(s, actor);
}

/* A text actor (0x4b6350, 0x180) with the text edx at the rectangle from the table (the line height
 * high at table + 4 twice, the width register's word added to the left less one) in the colour
 * 0x4f9c03 (0x4b65d0), shown, styled (+0x52 7, +0x44 16, +0x4e 70, +0x93 1, 0x4ac910) and added. */
static void text(Screen *s, uint32_t table, uint32_t text_edx, uint32_t *width_reg)
{
    uint32_t actor = s->eax;
    uint32_t args[3];
    s->esi = actor;
    reset(s, actor);
    s->eax = high(s, table + 4);
    args[1] = s->eax;
    args[2] = s->eax;
    *width_reg = low_word(*width_reg, word(s, table + 0xa));
    s->eax = low_word(s->eax, word(s, table + 2));
    s->eax = sign16(s->eax + *width_reg - 1);
    s->edx = text_edx;
    s->ebx = (uint32_t)((int32_t)port_u32(s->port, 0, 0x4f9c00) >> 24);
    s->ecx = high(s, table);
    args[0] = s->eax;
    s->eax = actor;
    screen_call(s, 0x4b65d0, args, 3);
    show(s, actor);
    port_set8(s->port, actor, 0x52, 7);
    port_set8(s->port, actor, 0x44, 0x10);
    port_set8(s->port, actor, 0x4e, 0x46);
    port_set8(s->port, actor, 0x94, 0);
    port_set8(s->port, actor, 0x95, 0);
    s->eax = actor;
    port_set8(s->port, actor, 0x93, 1);
    s->edx = 0;
    port_set16(s->port, actor, 0x48, 0);
    screen_call(s, 0x4ac910, NULL, 0);
    add(s, actor);
}

/* Original 0x46a9c0 (guarded 0x515f24): the results screen for the players eax and the outcome
 * edx. The texts made (0x4ca070), the two players' names (0x417790 of 0x532aa4, 0x532aa8) printed
 * with their scores 0x532aac and 0x532ab0 (0x4ca090, 0x4cdfb0). Its labels set (0x4ca370) and the
 * two results (+0x2c, +0x24) chosen: for two players by the outcome (0x417d10, 0x417d40, 0x417d70
 * of 0x532a68 and 0x532a6c; cleared in the one-player game 0x532a84), for one player 0, else by
 * 0x417cf0. Two header pictures (0x4b5400, 0x4b54d0, 0x4ac4e0) and the one or two name pictures
 * added to 0x54671c; the results handed to 0x470d20. Then two runs of bars (0x4f8848 long, 640
 * across from 0x533d44, layered up then down by 4), a ramp of 30 (0x4f885c) and its second ramp,
 * a backdrop, and four text actors (0x4b6350, 0x4b65d0) of the two scores, the labels and the
 * prompt 0x50e603; the frame ended (0x4cda10). eax the restored chain, edx 0x4cda10's. */
uint32_t vertrix_port_results_screen_46a9c0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x7c
    };
    Port port;
    uint8_t stack[BELOW + 8];
    Screen s;
    uint32_t record;
    uint32_t actor;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    s.port = &port;
    s.ebp = entry->esp - 4;
    record = s.ebp - 0x78;
    port_set32(&port, s.ebp, 0, entry->ebp);
    port_set32(&port, s.ebp, -4u, entry->ebx);
    port_set32(&port, s.ebp, -8u, entry->ecx);
    port_set32(&port, s.ebp, -0xcu, entry->esi);
    port_set32(&port, s.ebp, -0x10u, entry->edi);
    port_set32(&port, record, 0, port.env.chain);
    port.env.chain = record;
    s.ebx = entry->eax;
    s.ecx = entry->edx;
    s.edx = 0x4ec1ec;
    s.esi = 0x515f24;
    s.edi = 0;
    set_local(&s, -0x74u, s.edx);
    set_local(&s, -0x70u, s.esi);
    set_local(&s, -0x6cu, s.edi);
    call_with(&s, 0x4ca070, s.ebp - 0x64);
    s.edx = 2;
    s.esi = 3;
    set_local(&s, -0x6cu, 1);
    s.edi = 4;
    call_with(&s, 0x4ca070, s.ebp - 0x60);
    set_local(&s, -0x6cu, s.edx);
    call_with(&s, 0x4ca070, s.ebp - 0x5c);
    set_local(&s, -0x6cu, s.esi);
    call_with(&s, 0x4ca070, s.ebp - 0x58);
    set_local(&s, -0x6cu, s.edi);
    call_with(&s, 0x4ca070, s.ebp - 0x54);
    s.edx = 6;
    set_local(&s, -0x6cu, 5);
    s.esi = 7;
    call_with(&s, 0x4ca070, s.ebp - 0x50);
    set_local(&s, -0x6cu, s.edx);
    call_with(&s, 0x4ca070, s.ebp - 0x4c);
    s.edx = s.ebp - 0x50;
    set_local(&s, -0x6cu, s.esi);
    call_with(&s, 0x417790, port_u32(&port, 0, 0x532aa4));
    s.edx = s.ebp - 0x4c;
    call_with(&s, 0x417790, port_u32(&port, 0, 0x532aa8));
    s.edi = port_u32(&port, 0, 0x532aac);
    s.edx = s.ebp - 0x50;
    call_with(&s, 0x4ca090, s.ebp - 0x48);
    set_local(&s, -0x6cu, 8);
    {
        uint32_t args[4] = {s.ebp - 0x58, 0x50e597, port_u32(&port, s.eax, 0), s.edi};
        s.edi = 7;
        s.eax = s.ebp - 0x58;
        s.edx = 0;
        s.esi = 0xa;
        screen_call(&s, 0x4cdfb0, args, 4);
    }
    set_local(&s, -0x6cu, s.edi);
    call_with(&s, 0x4ca210, s.ebp - 0x48);
    {
        uint32_t score = port_u32(&port, 0, 0x532ab0);
        uint32_t args[4];
        s.edx = s.ebp - 0x4c;
        set_local(&s, -0x6cu, s.edi);
        call_with(&s, 0x4ca090, s.ebp - 0x44);
        set_local(&s, -0x6cu, s.esi);
        s.edi = port_u32(&port, s.eax, 0);
        args[0] = s.ebp - 0x54;
        args[1] = 0x50e5aa;
        args[2] = s.edi;
        args[3] = score;
        s.eax = s.ebp - 0x54;
        s.edx = 0;
        screen_call(&s, 0x4cdfb0, args, 4);
    }
    set_local(&s, -0x6cu, 7);
    call_with(&s, 0x4ca210, s.ebp - 0x44);
    set_local(&s, -0x6cu, 7);
    if (s.ebx == 1)
    {
        s.edx = 0x50e5bd;
        call_with(&s, 0x4ca370, s.ebp - 0x60);
        if (s.ecx == s.ebx || s.ecx == 2 || s.ecx == 0)
        {
            uint32_t first = s.ecx == 1 ? 0x417d10 : s.ecx == 2 ? 0x417d40 : 0x417d70;
            uint32_t second = s.ecx == 1 ? 0x417d40 : s.ecx == 2 ? 0x417d10 : 0x417d70;
            uint32_t label = s.ecx == 1 ? 0x50e5bf : s.ecx == 2 ? 0x50e5cc : 0x50e5d9;
            uint32_t last = s.ecx == 1 ? 0x50e5c6 : s.ecx == 2 ? 0x50e5d2 : 0x50e5df;
            call_with(&s, first, port_u32(&port, 0, 0x532a68));
            set_local(&s, -0x2cu, s.eax);
            s.edx = label;
            call_with(&s, second, port_u32(&port, 0, 0x532a6c));
            set_local(&s, -0x24u, s.eax);
            call_with(&s, 0x4ca370, s.ebp - 0x64);
            s.edx = last;
            call_with(&s, 0x4ca370, s.ebp - 0x5c);
        }
        if (port_u32(&port, 0, 0x532a84) == 1)
        {
            s.eax = 0;
            set_local(&s, -0x2cu, 0);
            set_local(&s, -0x24u, 0);
        }
    }
    else if (port_u32(&port, 0, 0x532a84) != 1)
    {
        s.edx = port_u32(&port, 0, 0x532a6c);
        call_with(&s, 0x417cf0, port_u32(&port, 0, 0x532a68));
        s.edx = port_u32(&port, 0, 0x532a68);
        set_local(&s, -0x2cu, s.eax);
        call_with(&s, 0x417cf0, port_u32(&port, 0, 0x532a6c));
        s.edx = 0x50e5f3;
        set_local(&s, -0x24u, s.eax);
        call_with(&s, 0x4ca370, s.ebp - 0x64);
        s.edx = 0x50e5f9;
        call_with(&s, 0x4ca370, s.ebp - 0x60);
        s.edx = 0x50e5fc;
        call_with(&s, 0x4ca370, s.ebp - 0x5c);
    }
    else
    {
        s.edx = 0x50e5e5;
        call_with(&s, 0x4ca370, s.ebp - 0x64);
        s.ebx = 0;
        s.edx = 0x50e5e9;
        set_local(&s, -0x2cu, s.ebx);
        call_with(&s, 0x4ca370, s.ebp - 0x60);
        s.edx = 0x50e5ed;
        set_local(&s, -0x24u, s.ebx);
        call_with(&s, 0x4ca370, s.ebp - 0x5c);
    }
    header(&s, &s.ecx, 0xc, &s.ebx, 0x4f8772, 1);
    header(&s, &s.edx, 0xe, &s.ecx, 0x4f8782, 0);
    s.esi = port_u32(&port, 0, 0x532a84);
    if (s.esi == 1)
    {
        s.edi = port_u32(&port, 0, 0x4f8810) + port_u32(&port, 0, 0x4f8818) - 1 -
                port_u32(&port, 0, 0x4f8800);
        call_with(&s, 0x4ca000, 0x160);
        s.edi += s.esi;
        if (s.eax != 0)
        {
            screen_call(&s, 0x4b5400, NULL, 0);
        }
        actor = s.eax;
        name(&s, actor, 0x4f87fe, s.edi & 0xffff);
        add(&s, actor);
    }
    else
    {
        make(&s, 0x160, 0x4b5400, &s.edi, 0x10, &s.edx, 7);
        actor = s.eax;
        name(&s, actor, 0x4f87fe, word(&s, 0x4f8808));
        add(&s, actor);
        make(&s, 0x160, 0x4b5400, &s.ecx, 0x12, &s.ebx, 7);
        actor = s.eax;
        name(&s, actor, 0x4f880e, word(&s, 0x4f8818));
        s.edx = actor;
        s.eax = 0x54671c;
        s.esi = 7;
        screen_call(&s, 0x4b5e70, NULL, 0);
        set_local(&s, -0x6cu, s.esi);
    }
    s.ecx = local(&s, -0x54u);
    s.ebx = local(&s, -0x58u);
    s.edx = local(&s, -0x24u);
    call_with(&s, 0x470d20, local(&s, -0x2cu));
    set_local(&s, -0x20u, port_u32(&port, 0, 0x4f8848) >> 1);
    s.edx = local(&s, -0x20u);
    s.eax = port_u32(&port, 0, 0x4f8848) - s.edx;
    s.edi = 0xffffffe2u;
    s.esi = 0;
    set_local(&s, -0x14u, s.eax);
    if (s.edx != 0)
    {
        do
        {
            bar(&s, -0x34u, s.esi);
            actor = local(&s, -0x34u);
            s.eax = actor;
            s.esi++;
            port_set8(&port, actor, 0x94, 1);
            s.ebx = local(&s, -0x20u);
            port_set8(&port, actor, 0x95, 1);
            s.edx = actor;
            port_set8(&port, actor, 0x110, 0);
            s.eax = 0x54671c;
            s.edi += 4;
            screen_call(&s, 0x4b5e70, NULL, 0);
        } while (s.esi < s.ebx && !port.env.failed);
    }
    s.eax = local(&s, -0x14u);
    s.esi = 0;
    if (s.eax != 0)
    {
        do
        {
            bar(&s, -0x18u, local(&s, -0x20u) + s.esi);
            actor = local(&s, -0x18u);
            s.eax = actor;
            flags(&s, actor, 1, 0);
            s.edx = actor;
            s.eax = 0x54671c;
            s.esi++;
            screen_call(&s, 0x4b5e70, NULL, 0);
            s.edx = local(&s, -0x14u);
            s.edi -= 4;
        } while (s.esi < s.edx && !port.env.failed);
    }
    s.edi = 0xffffffa6u;
    s.ecx = 0x1e;
    s.ebx = 0x14;
    s.eax = port_u32(&port, 0, 0x4f8864) - 0x3c;
    s.esi = 0;
    set_local(&s, -0x20u, s.ecx);
    set_local(&s, -0x38u, s.ebx);
    set_local(&s, -0x28u, s.esi);
    set_local(&s, -0x14u, s.eax);
    do
    {
        ramp(&s, -0x30u, s.esi);
        s.edi += local(&s, -0x38u);
        if ((int32_t)s.edi > 0x50)
        {
            s.edi = 0x50;
        }
        s.edx = local(&s, -0x38u);
        if (s.edx <= 5)
        {
            set_local(&s, -0x28u, local(&s, -0x28u) + 1);
        }
        else
        {
            s.ebx = s.edx - 1;
            set_local(&s, -0x38u, s.ebx);
        }
        s.esi++;
    } while (s.esi < 0x1e && !port.env.failed);
    make(&s, 0x160, 0x4b5400, &s.esi, 0x14, &s.edx, 7);
    actor = s.eax;
    s.esi = actor;
    reset(&s, actor);
    s.ebx = local(&s, -0x20u);
    {
        uint32_t below = port_u16(&port, s.ebp, -0x14u);
        s.edx = high(&s, 0x4f8856);
        s.eax = low_word(below, word(&s, 0x4f885c)) + s.ebx;
        s.ecx = word(&s, 0x4f8860);
        s.ebx = sign16(s.eax);
        place(&s, actor, below);
    }
    port_set8(&port, actor, 0x52, 8);
    port_set8(&port, actor, 0x94, 0);
    s.edx = 2;
    port_set8(&port, actor, 0x95, 0);
    s.ecx = 5;
    port_set8(&port, actor, 0x110, 0);
    s.eax = actor;
    port_set16(&port, actor, 0x48, s.edi);
    screen_call(&s, 0x4ac7b0, NULL, 0);
    s.ebx = local(&s, -0x20u);
    add(&s, actor);
    set_local(&s, -0x3cu, s.ecx);
    s.esi = 0;
    if (s.ebx != 0)
    {
        do
        {
            ramp(&s, -0x1cu, s.esi + local(&s, -0x20u) + local(&s, -0x14u));
            s.edi -= local(&s, -0x3cu);
            if ((int32_t)s.edi < -0x5a)
            {
                s.edi = 0xffffffa6u;
            }
            s.edx = local(&s, -0x28u);
            if (s.edx != 0)
            {
                s.ecx = s.edx - 1;
                set_local(&s, -0x28u, s.ecx);
            }
            else
            {
                s.ebx = local(&s, -0x3cu);
                if (s.ebx < 0x14)
                {
                    s.eax = s.ebx + 1;
                    set_local(&s, -0x3cu, s.eax);
                }
            }
            s.edx = local(&s, -0x20u);
            s.esi++;
        } while (s.esi < s.edx && !port.env.failed);
    }
    make(&s, 0x160, 0x4b5400, &s.ecx, 0x16, &s.ebx, 7);
    actor = s.eax;
    s.esi = actor;
    reset(&s, actor);
    s.ebx = high(&s, 0x4f885a);
    s.edx = high(&s, 0x4f8856);
    s.eax = word(&s, 0x4f8864);
    s.ecx = word(&s, 0x4f8860);
    place(&s, actor, s.eax);
    port_set8(&port, actor, 0x94, 0);
    s.eax = actor;
    port_set8(&port, actor, 0x95, 0);
    s.ebx = 0;
    s.edx = 0;
    port_set8(&port, actor, 0x110, 1);
    screen_call(&s, 0x4ac4e0, NULL, 0);
    show(&s, actor);
    add(&s, actor);
    make(&s, 0x180, 0x4b6350, &s.esi, 0x18, &s.edi, 7);
    text(&s, 0x4f87ce, local(&s, -0x64u), &s.ecx);
    make(&s, 0x180, 0x4b6350, &s.edx, 0x1a, &s.ecx, 7);
    text(&s, 0x4f87de, local(&s, -0x60u), &s.edi);
    make(&s, 0x180, 0x4b6350, &s.ebx, 0x1c, &s.esi, 7);
    text(&s, 0x4f87ee, local(&s, -0x5cu), &s.edx);
    make(&s, 0x180, 0x4b6350, &s.edi, 0x1e, &s.edx, 7);
    text(&s, 0x4f87b2, 0x50e603, &s.ebx);
    screen_call(&s, 0x4cda10, NULL, 0);
    port.env.chain = port_u32(&port, record, 0);
    return port_return(&port, port.env.chain, s.edx);
}
