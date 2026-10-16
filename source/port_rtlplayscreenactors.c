#include "port_rtlplayscreenactors.h"

/* The play screen's text actors set up. */

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
    uint32_t stack[32];
    unsigned pushed;
} Regs;

/* A value pushed for the next call. */
static void push(Regs *r, uint32_t value)
{
    if (r->pushed < 32)
    {
        r->stack[r->pushed++] = value;
    }
}

/* A call of the tracked registers taking the last count values pushed (nearest first) and, unless
 * kept, popping them as the callee's ret does. */
static void call_with_stack(Regs *r, uint32_t target, unsigned count, int keep)
{
    uint32_t args[32] = {0};
    unsigned i;
    if (count > r->pushed)
    {
        count = r->pushed;
    }
    for (i = 0; i < count; i++)
    {
        args[i] = r->stack[r->pushed - 1 - i];
    }
    if (!keep)
    {
        r->pushed -= count;
    }
    vertrix_lift_in_esi = r->esi;
    vertrix_lift_in_edi = r->edi;
    vertrix_lift_in_ebp = r->ebp;
    r->eax =
        lift_call_arguments(&r->port->env, target, r->eax, r->edx, r->ebx, r->ecx, args, count);
    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    r->edx = vertrix_lift_edx;
}

static void call(Regs *r, uint32_t target, unsigned count)
{
    call_with_stack(r, target, count, 0);
}

static uint32_t rd16(Regs *r, uint32_t address)
{
    return port_u16(r->port, address, 0);
}

static uint32_t rd32(Regs *r, uint32_t address)
{
    return port_u32(r->port, address, 0);
}

static void wr8(Regs *r, uint32_t address, uint32_t value)
{
    port_set8(r->port, address, 0, value);
}

static void wr16(Regs *r, uint32_t address, uint32_t value)
{
    port_set16(r->port, address, 0, value);
}

static void wr32(Regs *r, uint32_t address, uint32_t value)
{
    port_set32(r->port, address, 0, value);
}

static void set_low16(uint32_t *reg, uint32_t value)
{
    *reg = (*reg & 0xffff0000u) | (value & 0xffff);
}

/* Original 0x469480 (eax the replay flag, edx the owner): the play screen's actors made inside a
 * try/finally (record at ebp - 0x4c, handler 0x4ec1ec / 0x515e94, the text at ebp - 0x30 made by
 * 0x4ca070 and freed by 0x4ca210): each actor allocated (0x4ca000 of 0x180, made by 0x4b6350 when
 * given), set up (0x4adf20), its caption picked by the replay flag [ebp - 0x24] and the options
 * 0x532a84 / 0x532a74 / 0x532a78 (0x4ca370, 0x4ac8f0), placed from the layout words at 0x4f87xx
 * and 0x533d3x (0x4b65d0, 0x4ae110), shown (0x4ac7b0, 0x4ac910) and added to the list 0x54671c
 * (0x4b5e70); the per-player rows built in the loop at 0x469f9a over 0x4f9c10 entries. Without the
 * replay flag the finally runs 0x46a410. eax the restored chain. Register-for-register from the
 * listing (0x46948a..0x46a3fe); labels are the original addresses. */
static void build(Regs *r)
{
    wr32(r, r->ebp - 0x24, r->eax);
    wr32(r, r->ebp - 0x28, r->edx);
    r->eax = r->ebp - 0x4c;
    r->edx = 0x4ec1ec;
    r->ecx = 0x515e94;
    r->esi = 0x1;
    push(r, r->port->env.chain);
    wr32(r, r->eax, r->stack[--r->pushed]);
    r->port->env.chain = r->eax;
    r->ebx = 0;
    r->eax = r->ebp - 0x30;
    wr32(r, r->ebp - 0x48, r->edx);
    wr32(r, r->ebp - 0x44, r->ecx);
    wr32(r, r->ebp - 0x40, r->ebx);
    call(r, 0x4ca070, 0);
    r->eax = 0x532c24;
    wr32(r, r->ebp - 0x40, r->esi);
    call(r, 0x4b7830, 0);
    r->eax = 0x180;
    call(r, 0x4ca000, 0);
    if (r->eax != 0)
    {
        goto at_46a05e;
    }
    r->edi = r->ebx;
at_4694e5:
    push(r, 0x0);
    push(r, 0x0);
    push(r, 0x0);
    push(r, 0x0);
    r->eax = r->edi;
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = 0;
    r->edx = 0;
    call(r, 0x4adf20, 5);
    r->ecx = rd32(r, r->ebp - 0x24);
    r->esi = r->edi;
    if (r->ecx != 0)
    {
        goto at_46a0dd;
    }
    if ((rd32(r, 0x532a84)) != 0x1)
    {
        goto at_46a078;
    }
    r->edx = 0x50e53b;
    r->eax = r->ebp - 0x30;
    call(r, 0x4ca370, 0);
    r->edx = 0x447af0;
    r->eax = r->edi;
    call(r, 0x4ac8f0, 0);
    push(r, 0x1);
    set_low16(&r->eax, rd16(r, 0x533d38));
    set_low16(&r->edx, rd16(r, 0x4f8740));
    r->ecx = rd32(r, 0x533d36);
    r->ebx = rd32(r, 0x540017);
    wr8(r, r->edi + 0x44, 0x9);
    r->eax = r->eax + r->edx;
    push(r, 0x1);
    r->eax = r->eax - 1;
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x18);
    push(r, r->eax);
    r->edx = rd32(r, r->ebp - 0x30);
at_46955e:
    r->eax = r->edi;
at_469560:
    call(r, 0x4b65d0, 3);
    r->edx = 0x2;
    r->eax = r->esi;
    call(r, 0x4ac7b0, 0);
    wr8(r, r->esi + 0x52, 0x9);
    wr8(r, r->esi + 0x4e, 0x0);
    r->eax = r->esi;
    wr8(r, r->esi + 0x93, 0x1);
    r->edx = 0;
    wr32(r, r->esi + 0x4, 0x1);
    call(r, 0x4ac910, 0);
    r->eax = 0x54671c;
    r->edx = r->esi;
    call(r, 0x4b5e70, 0);
    r->eax = 0x180;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_4695c2;
    }
    r->ecx = 0x4;
    r->ebx = 0x1;
    wr32(r, r->ebp - 0x2c, r->eax);
    wr32(r, r->ebp - 0x40, r->ecx);
    call(r, 0x4b6350, 0);
    wr32(r, r->ebp - 0x40, r->ebx);
at_4695c2:
    r->edi = r->eax;
    push(r, 0x0);
    push(r, 0x0);
    push(r, 0x0);
    push(r, 0x0);
    r->eax = r->edi;
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = 0;
    r->edx = 0;
    call(r, 0x4adf20, 5);
    r->eax = rd32(r, r->ebp - 0x24);
    r->esi = r->edi;
    if (r->eax != 0)
    {
        goto at_46a20a;
    }
    r->ebx = rd32(r, 0x532a84);
    if (r->ebx != 0x1)
    {
        goto at_46a1a5;
    }
    r->edx = 0x50e55f;
    r->eax = r->ebp - 0x30;
    call(r, 0x4ca370, 0);
    r->edx = 0x447af0;
    r->eax = r->edi;
    call(r, 0x4ac8f0, 0);
    set_low16(&r->eax, rd16(r, 0x4f8744));
    set_low16(&r->edx, rd16(r, 0x4f874c));
    push(r, r->ebx);
    r->ecx = rd32(r, 0x4f8742);
    wr8(r, r->edi + 0x44, 0x9);
    push(r, r->ebx);
    r->eax = r->eax + r->edx;
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    r->eax = r->eax - 1;
    r->edx = rd32(r, r->ebp - 0x30);
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    r->ebx = rd32(r, 0x540017);
    push(r, r->eax);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x18);
at_46963d:
    r->eax = r->edi;
at_46963f:
    call(r, 0x4b65d0, 3);
    r->edx = 0x2;
    r->eax = r->esi;
    call(r, 0x4ac7b0, 0);
    wr8(r, r->esi + 0x52, 0x9);
    wr8(r, r->esi + 0x4e, 0x0);
    r->eax = r->esi;
    wr8(r, r->esi + 0x93, 0x1);
    r->edx = 0;
    wr32(r, r->esi + 0x4, 0x2);
    call(r, 0x4ac910, 0);
    r->eax = 0x54671c;
    r->edx = r->esi;
    call(r, 0x4b5e70, 0);
    if ((rd32(r, 0x532a84)) != 0x1)
    {
        goto at_4697ac;
    }
    r->eax = 0x180;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_46969b;
    }
    call(r, 0x4b6350, 0);
at_46969b:
    r->esi = r->eax;
    push(r, 0x0);
    push(r, 0x0);
    push(r, 0x0);
    push(r, 0x0);
    r->eax = r->esi;
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = 0;
    r->edx = 0;
    call(r, 0x4adf20, 5);
    set_low16(&r->eax, rd16(r, 0x4f8804));
    r->eax = r->eax - 0x5;
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    push(r, r->eax);
    set_low16(&r->eax, rd16(r, 0x4f8804));
    r->eax = r->eax - 0x18;
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    push(r, r->eax);
    set_low16(&r->eax, rd16(r, 0x4f8800));
    r->edx = 0x50e583;
    r->eax = r->eax + 0x2;
    r->ebx = rd32(r, 0x4f9bf8);
    r->ecx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x18);
    push(r, r->ecx);
    r->eax = r->esi;
    wr8(r, r->esi + 0x44, 0x10);
    call(r, 0x4b65d0, 3);
    r->edx = 0x2;
    r->eax = r->esi;
    call(r, 0x4ac7b0, 0);
    r->eax = 0x54671c;
    r->edx = r->esi;
    wr8(r, r->esi + 0x4e, 0x0);
    call(r, 0x4b5e70, 0);
    r->eax = rd32(r, 0x4f8810);
    r->edx = rd32(r, 0x4f8818);
    r->ecx = rd32(r, 0x4f8800);
    r->eax = r->eax + r->edx;
    r->edx = rd32(r, 0x4f9bf8);
    r->eax = r->eax - 1;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x18);
    r->eax = r->eax - r->ecx;
    push(r, r->edx);
    r->eax = r->eax + 1;
    push(r, 0x56);
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    set_low16(&r->eax, rd16(r, 0x4f8804));
    r->ecx = 0x14;
    r->eax = r->eax - 0x18;
    push(r, 0x50e58a);
    r->edx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = rd32(r, 0x4f87fe);
    push(r, 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x470960, 4);
    r->edx = 0x4451d0;
    r->ecx = r->eax;
    wr32(r, r->eax + 0x184, 0x416990);
    call(r, 0x4ac8f0, 0);
    r->eax = r->ecx;
    r->edx = 0;
    r->ebx = 0;
    call(r, 0x4b4510, 0);
    r->edx = 0x50e58b;
    r->eax = r->ecx + 0x18c;
    wr32(r, r->ecx + 0x178, 0x27);
    call(r, 0x4ca370, 0);
    r->edx = 0x7f;
    r->eax = r->ecx;
    call(r, 0x4ac4e0, 0);
    r->eax = 0x54671c;
    r->edx = r->ecx;
    call(r, 0x4b5e70, 0);
at_4697ac:
    r->eax = 0x180;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_4697d2;
    }
    r->ebx = 0x6;
    r->esi = 0x1;
    wr32(r, r->ebp - 0x2c, r->eax);
    wr32(r, r->ebp - 0x40, r->ebx);
    call(r, 0x4b6350, 0);
    wr32(r, r->ebp - 0x40, r->esi);
at_4697d2:
    r->esi = r->eax;
    push(r, 0x0);
    push(r, 0x44bba0);
    push(r, 0x0);
    push(r, 0x0);
    r->eax = r->esi;
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = 0;
    r->edx = 0;
    call(r, 0x4adf20, 5);
    set_low16(&r->eax, rd16(r, 0x4f8798));
    set_low16(&r->eax, (r->eax & 0xffff) + rd16(r, 0x4f87a0));
    r->eax = r->eax - 1;
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    push(r, r->eax);
    r->eax = rd32(r, 0x4f8796);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    set_low16(&r->ecx, rd16(r, 0x4f879c));
    push(r, r->eax);
    set_low16(&r->eax, rd16(r, 0x4f8794));
    r->edx = 0x50e58c;
    r->eax = r->eax + r->ecx;
    r->ebx = rd32(r, 0x4f9c00);
    r->eax = r->eax - 1;
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x18);
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    r->ecx = rd32(r, 0x4f8792);
    push(r, r->eax);
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    r->eax = r->esi;
    call(r, 0x4b65d0, 3);
    r->edx = 0x2;
    r->eax = r->esi;
    call(r, 0x4ac7b0, 0);
    wr8(r, r->esi + 0x44, 0x0);
    wr8(r, r->esi + 0x4e, 0x50);
    wr8(r, r->esi + 0x94, 0x0);
    r->eax = rd32(r, 0x4f7bb8);
    wr8(r, r->esi + 0x95, 0x3);
    r->edx = 0;
    wr32(r, r->esi + 0x14c, r->eax);
    r->eax = r->esi;
    wr16(r, r->esi + 0x172, 0x1);
    call(r, 0x4ac910, 0);
    r->edx = rd32(r, 0x4f9c01);
    r->eax = r->esi;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x18);
    wr8(r, r->esi + 0x93, 0x1);
    call(r, 0x4b6530, 0);
    r->edx = 0xffffffb0u;
    r->eax = r->esi;
    call(r, 0x4b6540, 0);
    r->eax = r->esi;
    r->edx = 0xffffffb0u;
    call(r, 0x4b65b0, 0);
    r->eax = r->esi;
    call(r, 0x4b6550, 0);
    r->eax = rd32(r, 0x4f87a0);
    r->eax = r->eax + 0x8;
    push(r, r->eax);
    set_low16(&r->eax, rd16(r, 0x4f8798));
    r->eax = r->eax - 0x4;
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    set_low16(&r->eax, rd16(r, 0x4f8794));
    r->ecx = rd32(r, 0x4f879c);
    r->eax = r->eax - 0x4;
    r->ecx = r->ecx + 0x8;
    r->edx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = r->esi;
    wr32(r, r->esi + 0x124, 0x1);
    call(r, 0x4ae110, 1);
    r->eax = 0x54671c;
    r->edx = r->esi;
    call(r, 0x4b5e70, 0);
    r->eax = 0x180;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_469919;
    }
    r->edi = 0x8;
    r->edx = 0x1;
    wr32(r, r->ebp - 0x2c, r->eax);
    wr32(r, r->ebp - 0x40, r->edi);
    call(r, 0x4b6350, 0);
    wr32(r, r->ebp - 0x40, r->edx);
at_469919:
    r->esi = r->eax;
    push(r, 0x0);
    push(r, 0x44bba0);
    push(r, 0x0);
    push(r, 0x0);
    r->eax = r->esi;
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = 0;
    r->edx = 0;
    call(r, 0x4adf20, 5);
    set_low16(&r->eax, rd16(r, 0x4f87a8));
    set_low16(&r->eax, (r->eax & 0xffff) + rd16(r, 0x4f87b0));
    r->eax = r->eax - 1;
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    push(r, r->eax);
    r->eax = rd32(r, 0x4f87a6);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    set_low16(&r->edx, rd16(r, 0x4f87ac));
    push(r, r->eax);
    set_low16(&r->eax, rd16(r, 0x4f87a4));
    r->ecx = rd32(r, 0x4f87a2);
    r->eax = r->eax + r->edx;
    r->ebx = rd32(r, 0x4f9c00);
    r->eax = r->eax - 1;
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x18);
    push(r, r->eax);
    r->edx = 0x50e590;
    r->eax = r->esi;
    call(r, 0x4b65d0, 3);
    r->edx = 0x2;
    r->eax = r->esi;
    call(r, 0x4ac7b0, 0);
    wr8(r, r->esi + 0x44, 0x0);
    wr8(r, r->esi + 0x4e, 0x50);
    wr8(r, r->esi + 0x93, 0x1);
    r->eax = rd32(r, 0x4f7bbc);
    wr8(r, r->esi + 0x94, 0x0);
    r->edx = 0;
    wr32(r, r->esi + 0x14c, r->eax);
    r->eax = r->esi;
    wr8(r, r->esi + 0x95, 0x3);
    call(r, 0x4ac910, 0);
    r->edx = rd32(r, 0x4f9c01);
    r->eax = r->esi;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x18);
    call(r, 0x4b6530, 0);
    r->edx = 0xffffffb0u;
    r->eax = r->esi;
    call(r, 0x4b6540, 0);
    r->eax = r->esi;
    r->edx = 0xffffffb0u;
    call(r, 0x4b65b0, 0);
    r->eax = r->esi;
    call(r, 0x4b6550, 0);
    r->eax = rd32(r, 0x4f87b0);
    r->eax = r->eax + 0x8;
    push(r, r->eax);
    set_low16(&r->eax, rd16(r, 0x4f87a8));
    r->eax = r->eax - 0x4;
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    set_low16(&r->eax, rd16(r, 0x4f87a4));
    r->ecx = rd32(r, 0x4f87ac);
    r->eax = r->eax - 0x4;
    r->ecx = r->ecx + 0x8;
    r->edx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = r->esi;
    wr32(r, r->esi + 0x124, 0x1);
    call(r, 0x4ae110, 1);
    r->eax = 0x54671c;
    r->edx = r->esi;
    call(r, 0x4b5e70, 0);
    r->eax = 0x180;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_469a57;
    }
    r->ecx = 0xa;
    r->ebx = 0x1;
    wr32(r, r->ebp - 0x2c, r->eax);
    wr32(r, r->ebp - 0x40, r->ecx);
    call(r, 0x4b6350, 0);
    wr32(r, r->ebp - 0x40, r->ebx);
at_469a57:
    r->esi = r->eax;
    push(r, 0x0);
    push(r, 0x45d690);
    push(r, 0x0);
    push(r, 0x0);
    r->eax = r->esi;
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = 0;
    r->edx = 0;
    call(r, 0x4adf20, 5);
    set_low16(&r->eax, rd16(r, 0x4f87c4));
    set_low16(&r->eax, (r->eax & 0xffff) + rd16(r, 0x4f87cc));
    r->eax = r->eax - 1;
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    push(r, r->eax);
    r->eax = rd32(r, 0x4f87c2);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    set_low16(&r->ecx, rd16(r, 0x4f87c8));
    push(r, r->eax);
    set_low16(&r->eax, rd16(r, 0x533d40));
    r->edx = 0x50e593;
    r->eax = r->eax + r->ecx;
    r->ebx = rd32(r, 0x4f9c00);
    r->eax = r->eax - 1;
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x18);
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    r->ecx = rd32(r, 0x533d3e);
    push(r, r->eax);
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    r->eax = r->esi;
    call(r, 0x4b65d0, 3);
    r->edx = 0x3;
    r->eax = r->esi;
    call(r, 0x4ac7b0, 0);
    wr8(r, r->esi + 0x44, 0x10);
    wr8(r, r->esi + 0x4e, 0x0);
    wr8(r, r->esi + 0x93, 0x1);
    r->edx = 0x9;
    wr8(r, r->esi + 0x94, 0x1);
    r->eax = r->esi;
    wr8(r, r->esi + 0x95, 0x1);
    call(r, 0x4b6530, 0);
    r->edx = 0xffffffb0u;
    r->eax = r->esi;
    call(r, 0x4b6540, 0);
    r->eax = r->esi;
    r->edx = 0xffffffb0u;
    call(r, 0x4b65b0, 0);
    r->eax = r->esi;
    call(r, 0x4b6550, 0);
    r->eax = r->esi;
    r->edx = 0;
    wr32(r, r->esi + 0x64, 0x1);
    call(r, 0x4ac910, 0);
    r->eax = 0x54671c;
    r->edx = r->esi;
    call(r, 0x4b5e70, 0);
    r->eax = 0x15c;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_469b52;
    }
    r->esi = 0xc;
    r->edi = 0x1;
    wr32(r, r->ebp - 0x2c, r->eax);
    wr32(r, r->ebp - 0x40, r->esi);
    call(r, 0x4abd70, 0);
    wr32(r, r->ebp - 0x40, r->edi);
at_469b52:
    r->esi = r->eax;
    push(r, 0x0);
    r->eax = rd32(r, 0x4f877c);
    r->edx = rd32(r, 0x4f8774);
    push(r, 0x0);
    r->eax = r->eax >> 0x1;
    push(r, 0x0);
    r->edx = r->edx + r->eax;
    push(r, 0x0);
    r->eax = rd32(r, 0x4f8780);
    wr32(r, r->ebp - 0x38, r->edx);
    r->edx = rd32(r, 0x4f8778);
    r->eax = r->eax >> 0x1;
    r->ecx = 0;
    r->edx = r->edx + r->eax;
    push(r, 0x0);
    wr32(r, r->ebp - 0x34, r->edx);
    r->eax = r->esi;
    r->ebx = rd32(r, r->ebp - 0x36);
    r->edx = rd32(r, r->ebp - 0x3a);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    call(r, 0x4adf20, 5);
    r->eax = r->esi;
    r->edx = 0;
    wr32(r, r->esi, 0x13);
    call(r, 0x4ac910, 0);
    r->edx = 0x544a34;
    r->eax = r->esi;
    call(r, 0x4ac8d0, 0);
    r->edx = rd32(r, 0x532a68);
    r->eax = r->esi;
    call(r, 0x4ac710, 0);
    r->eax = r->esi;
    r->edx = 0x1;
    call(r, 0x4ac8a0, 0);
    r->eax = r->esi;
    call(r, 0x4ac860, 0);
    wr32(r, r->esi + 0x150, 0x1);
    wr16(r, r->esi + 0xe, 0xff38);
    r->eax = rd32(r, r->ebp - 0x34);
    wr16(r, r->esi + 0x12, 0x1);
    wr16(r, r->esi + 0x16, (r->eax & 0xffff));
    r->eax = rd32(r, r->ebp - 0x38);
    wr16(r, r->esi + 0x10, (r->eax & 0xffff));
    r->eax = rd32(r, r->ebp - 0x34);
    wr16(r, r->esi + 0x18, (r->eax & 0xffff));
    r->eax = rd32(r, r->ebp - 0x38);
    wr16(r, r->esi + 0x8, (r->eax & 0xffff));
    r->eax = rd32(r, r->ebp - 0x34);
    r->edx = 0x168;
    wr16(r, r->esi + 0xa, (r->eax & 0xffff));
    r->eax = 0x598d30;
    wr16(r, r->esi + 0x1a, 0x1);
    call(r, 0x4826c0, 0);
    r->edx = 0x2;
    wr16(r, r->esi + 0x24, (r->eax & 0xffff));
    r->eax = 0x598d30;
    call(r, 0x4826c0, 0);
    r->eax = r->eax + 1;
    r->edx = 0x5;
    wr16(r, r->esi + 0x28, (r->eax & 0xffff));
    r->eax = 0x598d30;
    r->edi = r->esi;
    call(r, 0x4826c0, 0);
    set_low16(&r->edx, rd16(r, 0x4f877c));
    set_low16(&r->ebx, rd16(r, 0x4f8780));
    wr16(r, r->esi + 0x30, (r->eax & 0xffff));
    set_low16(&r->eax, rd16(r, 0x4f8774));
    r->ecx = rd32(r, 0x532a84);
    r->edx = r->edx + r->eax;
    set_low16(&r->eax, rd16(r, 0x4f8778));
    r->edx = r->edx - 1;
    r->eax = r->eax + r->ebx;
    if (r->ecx != 0x1)
    {
        goto at_46a2d2;
    }
    set_low16(&r->ebx, rd16(r, 0x4f8778));
    r->ecx = r->eax;
    wr16(r, r->esi + 0xaa, (r->edx & 0xffff));
    set_low16(&r->eax, rd16(r, 0x4f8774));
    wr16(r, r->esi + 0xac, (r->ebx & 0xffff));
    r->ecx = r->ecx - 0x19;
    wr16(r, r->esi + 0xa8, (r->eax & 0xffff));
    wr16(r, r->esi + 0xae, (r->ecx & 0xffff));
at_469ca9:
    push(r, 0x0);
    r->eax = r->edi;
    wr8(r, r->edi + 0x8e, 0x3);
    r->ecx = 0;
    r->ebx = 0;
    r->edx = 0;
    wr32(r, r->edi + 0x124, 0x1);
    call(r, 0x4ae110, 1);
    r->ebx = rd32(r, r->ebp - 0x24);
    wr32(r, r->edi + 0x13c, 0x0);
    if (r->ebx != 0x1)
    {
        goto at_46a33e;
    }
    r->esi = rd32(r, r->ebp - 0x28);
    if (r->esi != r->ebx)
    {
        goto at_46a303;
    }
    r->edx = 0x64;
    r->eax = r->edi;
    call(r, 0x4ac7d0, 0);
    wr32(r, r->edi + 0x68, 0x5);
    wr32(r, r->edi + 0x64, r->ebx);
at_469d00:
    r->eax = rd32(r, 0x532a68);
    wr32(r, r->edi + 0x70, 0x1);
    wr32(r, r->edi + 0x58, r->eax);
at_469d0f:
    r->edx = 0x45af40;
    r->eax = r->edi;
    call(r, 0x4ac8f0, 0);
    r->eax = 0x54671c;
    r->edx = r->edi;
    call(r, 0x4b5e70, 0);
    r->eax = 0x15c;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_469d4d;
    }
    r->edx = 0xe;
    r->ecx = 0x1;
    wr32(r, r->ebp - 0x2c, r->eax);
    wr32(r, r->ebp - 0x40, r->edx);
    call(r, 0x4abd70, 0);
    wr32(r, r->ebp - 0x40, r->ecx);
at_469d4d:
    r->esi = r->eax;
    push(r, 0x0);
    r->eax = rd32(r, 0x4f878c);
    r->edx = rd32(r, 0x4f8784);
    push(r, 0x448ca0);
    r->eax = r->eax >> 0x1;
    push(r, 0x0);
    r->edx = r->edx + r->eax;
    push(r, 0x0);
    r->eax = rd32(r, 0x4f8790);
    wr32(r, r->ebp - 0x38, r->edx);
    r->edx = rd32(r, 0x4f8788);
    r->eax = r->eax >> 0x1;
    r->ecx = 0;
    r->edx = r->edx + r->eax;
    push(r, 0x0);
    wr32(r, r->ebp - 0x34, r->edx);
    r->eax = r->esi;
    r->ebx = rd32(r, r->ebp - 0x36);
    r->edx = rd32(r, r->ebp - 0x3a);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    call(r, 0x4adf20, 5);
    r->eax = r->esi;
    r->edx = 0;
    wr32(r, r->esi, 0x14);
    call(r, 0x4ac910, 0);
    r->edx = 0x544a34;
    r->eax = r->esi;
    call(r, 0x4ac8d0, 0);
    r->edx = rd32(r, 0x532a6c);
    r->eax = r->esi;
    call(r, 0x4ac710, 0);
    r->eax = r->esi;
    r->edx = 0x1;
    call(r, 0x4ac8a0, 0);
    r->eax = r->esi;
    call(r, 0x4ac860, 0);
    wr32(r, r->esi + 0x150, 0x1);
    set_low16(&r->eax, rd16(r, 0x5b9c8e));
    wr16(r, r->esi + 0x12, 0x1);
    r->eax = r->eax + 0xc7;
    wr16(r, r->esi + 0xe, (r->eax & 0xffff));
    r->eax = rd32(r, r->ebp - 0x34);
    wr16(r, r->esi + 0x16, (r->eax & 0xffff));
    r->eax = rd32(r, r->ebp - 0x38);
    wr16(r, r->esi + 0x10, (r->eax & 0xffff));
    r->eax = rd32(r, r->ebp - 0x34);
    wr16(r, r->esi + 0x18, (r->eax & 0xffff));
    r->eax = rd32(r, r->ebp - 0x38);
    wr16(r, r->esi + 0x8, (r->eax & 0xffff));
    r->eax = rd32(r, r->ebp - 0x34);
    r->edx = 0x168;
    wr16(r, r->esi + 0xa, (r->eax & 0xffff));
    r->eax = 0x598d30;
    wr16(r, r->esi + 0x1a, 0x1);
    call(r, 0x4826c0, 0);
    r->edx = 0x2;
    wr16(r, r->esi + 0x24, (r->eax & 0xffff));
    r->eax = 0x598d30;
    call(r, 0x4826c0, 0);
    r->eax = r->eax + 1;
    r->edx = 0x5;
    wr16(r, r->esi + 0x28, (r->eax & 0xffff));
    r->eax = 0x598d30;
    r->edi = r->esi;
    call(r, 0x4826c0, 0);
    set_low16(&r->ebx, rd16(r, 0x4f8784));
    set_low16(&r->ecx, rd16(r, 0x4f878c));
    set_low16(&r->edx, rd16(r, 0x4f8790));
    wr16(r, r->esi + 0x30, (r->eax & 0xffff));
    set_low16(&r->eax, rd16(r, 0x4f8788));
    r->ebx = r->ebx + r->ecx;
    r->edx = r->edx + r->eax;
    r->eax = r->ebx;
    r->ebx = rd32(r, 0x532a84);
    r->eax = r->eax - 1;
    if (r->ebx != 0x1)
    {
        goto at_46a36c;
    }
    set_low16(&r->ebx, rd16(r, 0x4f8788));
    r->ecx = r->edx;
    wr16(r, r->esi + 0xaa, (r->eax & 0xffff));
    set_low16(&r->edx, rd16(r, 0x4f8784));
    wr16(r, r->esi + 0xac, (r->ebx & 0xffff));
    r->ecx = r->ecx - 0x19;
at_469ea6:
    wr16(r, r->esi + 0xa8, (r->edx & 0xffff));
    wr16(r, r->esi + 0xae, (r->ecx & 0xffff));
    push(r, 0x0);
    r->esi = rd32(r, r->ebp - 0x24);
    r->eax = r->edi;
    wr8(r, r->edi + 0x8e, 0x3);
    r->ecx = 0;
    r->ebx = 0;
    r->edx = 0;
    wr32(r, r->edi + 0x124, 0x1);
    call(r, 0x4ae110, 1);
    wr32(r, r->edi + 0x13c, 0x0);
    if (r->esi != 0x1)
    {
        goto at_46a3cb;
    }
    r->eax = rd32(r, r->ebp - 0x28);
    if (r->eax != 0x2)
    {
        goto at_46a390;
    }
    r->edx = 0x64;
    r->eax = r->edi;
    call(r, 0x4ac7d0, 0);
    wr32(r, r->edi + 0x68, 0x5);
    wr32(r, r->edi + 0x64, r->esi);
at_469f0c:
    r->eax = rd32(r, 0x532a6c);
    wr32(r, r->edi + 0x70, 0x2);
    wr32(r, r->edi + 0x58, r->eax);
at_469f1b:
    r->edx = 0x45af40;
    r->eax = r->edi;
    call(r, 0x4ac8f0, 0);
    r->eax = 0x54671c;
    r->edx = r->edi;
    call(r, 0x4b5e70, 0);
    r->ecx = rd32(r, 0x532a84);
    if (r->ecx != 0x1)
    {
        goto at_46a030;
    }
    r->eax = rd32(r, 0x4f8810);
    r->ebx = rd32(r, 0x4f8818);
    r->esi = rd32(r, 0x4f8800);
    set_low16(&r->edx, rd16(r, 0x4f8800));
    r->eax = r->eax + r->ebx;
    r->edi = rd32(r, 0x4f9c10);
    r->eax = r->eax - r->ecx;
    set_low16(&r->ebx, rd16(r, 0x4f8804));
    r->eax = r->eax - r->esi;
    wr32(r, r->ebp - 0x14, r->ebx);
    r->eax = r->eax + r->ecx;
    r->esi = 0;
    if (r->edi == 0)
    {
        goto at_46a030;
    }
    r->ecx = 0x18;
    r->eax = r->eax + 0x4;
    r->edx = r->edx - 0x2;
    r->edi = r->ebx;
    wr16(r, r->ebp - 0x18, (r->ecx & 0xffff));
    wr16(r, r->ebp - 0x1c, (r->eax & 0xffff));
    wr16(r, r->ebp - 0x20, (r->edx & 0xffff));
    r->edi = r->edi - 0x2;
at_469f9a:
    push(r, 0x0);
    r->ecx = rd32(r, r->ebp - 0x1a);
    r->ebx = rd32(r, r->ebp - 0x1e);
    r->eax = rd32(r, r->ebp - 0x22);
    push(r, 0x2);
    r->edx = (uint32_t)(int32_t)(int16_t)(r->edi & 0xffff);
    push(r, 0x10);
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    push(r, 0x5);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    push(r, 0x50e596);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x45fc80, 5);
    r->edx = 0x446500;
    r->ecx = r->eax;
    call(r, 0x4ac8f0, 0);
    wr8(r, r->ecx + 0x110, 0x0);
    r->eax = rd32(r, r->ecx + 0x160);
    wr32(r, r->ecx + 0x70, r->esi);
    wr8(r, r->eax + 0x93, 0x1);
    r->eax = rd32(r, r->ecx + 0x160);
    r->edi = r->edi + 0x14;
    r->ebx = rd32(r, r->ebp - 0x14);
    wr8(r, r->eax + 0x95, 0x5);
    r->edx = r->ecx;
    r->eax = rd32(r, r->ecx + 0x160);
    wr8(r, r->ecx + 0x52, 0xd);
    r->ebx = r->ebx + 0x14;
    wr8(r, r->eax + 0x52, 0xd);
    r->eax = 0x54671c;
    r->esi = r->esi + 1;
    call(r, 0x4b5e70, 0);
    r->eax = rd32(r, 0x4f9c10);
    wr32(r, r->ebp - 0x14, r->ebx);
    if (r->esi < r->eax && !r->port->env.failed)
    {
        goto at_469f9a;
    }
at_46a030:
    if ((rd32(r, r->ebp - 0x24)) == 0x0)
    {
        goto at_46a3f9;
    }
at_46a03a:
    r->eax = r->ebp - 0x30;
    r->ecx = 0;
    r->edx = 0;
    wr32(r, r->ebp - 0x40, r->ecx);
    call(r, 0x4ca210, 0);
    r->eax = rd32(r, r->ebp - 0x4c);
    wr32(r, r->ebp - 0x40, r->ecx);
    r->port->env.chain = r->eax;
    return;
at_46a05e:
    r->edi = 0x2;
    wr32(r, r->ebp - 0x2c, r->eax);
    wr32(r, r->ebp - 0x40, r->edi);
    call(r, 0x4b6350, 0);
    wr32(r, r->ebp - 0x40, r->esi);
    r->edi = r->eax;
    goto at_4694e5;
at_46a078:
    if ((rd32(r, 0x532a74)) != 0x1)
    {
        goto at_46a0d6;
    }
    r->edx = 0x50e53c;
at_46a086:
    r->eax = r->ebp - 0x30;
    call(r, 0x4ca370, 0);
    r->edx = 0x4479f0;
    r->eax = r->esi;
    call(r, 0x4ac8f0, 0);
    r->eax = rd32(r, 0x4f874e);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    push(r, r->eax);
    set_low16(&r->ecx, rd16(r, 0x4f8754));
    r->ebx = rd32(r, 0x540017);
    push(r, r->eax);
    set_low16(&r->eax, rd16(r, 0x533d3c));
    wr8(r, r->esi + 0x44, 0x9);
    r->eax = r->eax + r->ecx;
    r->edx = rd32(r, r->ebp - 0x30);
    r->eax = r->eax - 1;
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x18);
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    r->ecx = rd32(r, 0x533d3a);
    push(r, r->eax);
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    r->eax = r->esi;
    goto at_469560;
at_46a0d6:
    r->edx = 0x50e544;
    goto at_46a086;
at_46a0dd:
    if ((rd32(r, 0x532a84)) == 0x1)
    {
        goto at_46a148;
    }
    if ((rd32(r, 0x532a74)) != 0x1)
    {
        goto at_46a19b;
    }
    r->edx = 0x50e54e;
at_46a0f8:
    r->eax = r->ebp - 0x30;
    call(r, 0x4ca370, 0);
    r->edx = 0x4479f0;
    r->eax = r->esi;
    call(r, 0x4ac8f0, 0);
    r->eax = rd32(r, 0x4f873a);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    push(r, r->eax);
    set_low16(&r->edx, rd16(r, 0x4f8740));
    r->ecx = rd32(r, 0x533d36);
    push(r, r->eax);
    set_low16(&r->eax, rd16(r, 0x533d38));
    r->ebx = rd32(r, 0x4f9c00);
    r->eax = r->eax + r->edx;
    wr8(r, r->esi + 0x44, 0x10);
    r->eax = r->eax - 1;
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x18);
    push(r, r->eax);
    r->edx = rd32(r, r->ebp - 0x30);
    r->eax = r->esi;
    goto at_469560;
at_46a148:
    r->edx = 0x50e54d;
    r->eax = r->ebp - 0x30;
    call(r, 0x4ca370, 0);
    r->edx = 0x447af0;
    r->eax = r->edi;
    call(r, 0x4ac8f0, 0);
    r->eax = rd32(r, 0x4f874e);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    push(r, r->eax);
    set_low16(&r->ebx, rd16(r, 0x4f8740));
    r->ecx = rd32(r, 0x533d36);
    push(r, r->eax);
    set_low16(&r->eax, rd16(r, 0x533d38));
    wr8(r, r->edi + 0x44, 0x9);
    r->eax = r->eax + r->ebx;
    r->edx = rd32(r, r->ebp - 0x30);
    r->eax = r->eax - 1;
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    r->ebx = rd32(r, 0x540017);
    push(r, r->eax);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x18);
    goto at_46955e;
at_46a19b:
    r->edx = 0x50e556;
    goto at_46a0f8;
at_46a1a5:
    if ((rd32(r, 0x532a78)) != 0x1)
    {
        goto at_46a203;
    }
    r->edx = 0x50e560;
at_46a1b3:
    r->eax = r->ebp - 0x30;
    call(r, 0x4ca370, 0);
    r->edx = 0x4479f0;
    r->eax = r->esi;
    call(r, 0x4ac8f0, 0);
    r->eax = rd32(r, 0x4f875a);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    push(r, r->eax);
    set_low16(&r->edi, rd16(r, 0x4f8760));
    r->ecx = rd32(r, 0x4f8756);
    push(r, r->eax);
    set_low16(&r->eax, rd16(r, 0x4f8758));
    r->ebx = rd32(r, 0x540017);
    r->eax = r->eax + r->edi;
    wr8(r, r->esi + 0x44, 0x9);
    r->eax = r->eax - 1;
    r->edx = rd32(r, r->ebp - 0x30);
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    push(r, r->eax);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x18);
    r->eax = r->esi;
    goto at_46963f;
at_46a203:
    r->edx = 0x50e568;
    goto at_46a1b3;
at_46a20a:
    if ((rd32(r, 0x532a84)) == 0x1)
    {
        goto at_46a275;
    }
    if ((rd32(r, 0x532a78)) != 0x1)
    {
        goto at_46a2c8;
    }
    r->edx = 0x50e572;
at_46a225:
    r->eax = r->ebp - 0x30;
    call(r, 0x4ca370, 0);
    r->edx = 0x4479f0;
    r->eax = r->esi;
    call(r, 0x4ac8f0, 0);
    r->eax = rd32(r, 0x4f8746);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    push(r, r->eax);
    set_low16(&r->ebx, rd16(r, 0x4f874c));
    r->ecx = rd32(r, 0x4f8742);
    push(r, r->eax);
    set_low16(&r->eax, rd16(r, 0x4f8744));
    wr8(r, r->esi + 0x44, 0x10);
    r->eax = r->eax + r->ebx;
    r->edx = rd32(r, r->ebp - 0x30);
    r->eax = r->eax - 1;
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    r->ebx = rd32(r, 0x4f9c00);
    push(r, r->eax);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x18);
    r->eax = r->esi;
    goto at_46963f;
at_46a275:
    r->edx = 0x50e571;
    r->eax = r->ebp - 0x30;
    call(r, 0x4ca370, 0);
    r->edx = 0x447af0;
    r->eax = r->edi;
    call(r, 0x4ac8f0, 0);
    r->eax = rd32(r, 0x4f875a);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    push(r, r->eax);
    set_low16(&r->ecx, rd16(r, 0x4f874c));
    r->ebx = rd32(r, 0x540017);
    push(r, r->eax);
    set_low16(&r->eax, rd16(r, 0x4f8744));
    wr8(r, r->edi + 0x44, 0x9);
    r->eax = r->eax + r->ecx;
    r->edx = rd32(r, r->ebp - 0x30);
    r->eax = r->eax - 1;
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x18);
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    r->ecx = rd32(r, 0x4f8742);
    push(r, r->eax);
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    goto at_46963d;
at_46a2c8:
    r->edx = 0x50e57a;
    goto at_46a225;
at_46a2d2:
    set_low16(&r->ecx, rd16(r, 0x4f8774));
    r->ebx = r->eax;
    wr16(r, r->esi + 0xaa, (r->edx & 0xffff));
    set_low16(&r->eax, rd16(r, 0x4f8778));
    wr16(r, r->esi + 0xa8, (r->ecx & 0xffff));
    r->ebx = r->ebx - 1;
    wr16(r, r->esi + 0xac, (r->eax & 0xffff));
    wr16(r, r->esi + 0xae, (r->ebx & 0xffff));
    goto at_469ca9;
at_46a303:
    wr32(r, r->edi + 0x64, 0x2);
    if (r->esi != 0)
    {
        goto at_46a326;
    }
    r->edx = 0x64;
    r->eax = r->edi;
    call(r, 0x4ac7d0, 0);
    wr32(r, r->edi + 0x68, 0x4);
    goto at_469d00;
at_46a326:
    r->edx = 0x640;
    r->eax = r->edi;
    call(r, 0x4ac7d0, 0);
    wr32(r, r->edi + 0x68, 0x3);
    goto at_469d00;
at_46a33e:
    wr32(r, r->edi + 0x64, 0x0);
    r->eax = rd32(r, 0x532a68);
    wr32(r, r->edi + 0x70, 0x1);
    r->edx = 0x1f4;
    wr32(r, r->edi + 0x58, r->eax);
    r->eax = r->edi;
    wr32(r, r->edi + 0x68, 0x0);
    call(r, 0x4ac7d0, 0);
    goto at_469d0f;
at_46a36c:
    set_low16(&r->ebx, rd16(r, 0x4f8788));
    r->ecx = r->edx;
    wr16(r, r->esi + 0xaa, (r->eax & 0xffff));
    set_low16(&r->edx, rd16(r, 0x4f8784));
    wr16(r, r->esi + 0xac, (r->ebx & 0xffff));
    r->ecx = r->ecx - 1;
    goto at_469ea6;
at_46a390:
    wr32(r, r->edi + 0x64, 0x2);
    if (r->eax != 0)
    {
        goto at_46a3b3;
    }
    r->edx = 0x64;
    r->eax = r->edi;
    call(r, 0x4ac7d0, 0);
    wr32(r, r->edi + 0x68, 0x4);
    goto at_469f0c;
at_46a3b3:
    r->edx = 0x640;
    r->eax = r->edi;
    call(r, 0x4ac7d0, 0);
    wr32(r, r->edi + 0x68, 0x3);
    goto at_469f0c;
at_46a3cb:
    wr32(r, r->edi + 0x64, 0x0);
    r->eax = rd32(r, 0x532a6c);
    wr32(r, r->edi + 0x70, 0x2);
    r->edx = 0x1f4;
    wr32(r, r->edi + 0x58, r->eax);
    r->eax = r->edi;
    wr32(r, r->edi + 0x68, 0x0);
    call(r, 0x4ac7d0, 0);
    goto at_469f1b;
at_46a3f9:
    call(r, 0x46a410, 0);
    goto at_46a03a;
}

/* Builds the play screen's actor set inside a try/finally. It clears string list 0x532c24 and
 * allocates 0x180-byte actors (0x4ca000, 0x4b6350, initialized by 0x4adf20). On those it sets
 * captions taken from the 'PLAYER1'/'PLAYER2'/'COMPUTER'/'MSG : '/'YES' strings
 * (0x50e53c..0x50e58c), choosing them by the argument in eax and by option 0x532a84. It places them
 * from layout words at 0x4f87xx/0x533d3x via actor_set_text 0x4b65d0. It also creates a menu item
 * (0x470960), randomized sprite actors attached to 0x544a34, and one text panel (0x45fc80) for each
 * of the 0x4f9c10 entries, adding everything to actor list 0x54671c via 0x4b5e70. It finishes with
 * f46a410 when the argument is 0. It is called from f41cc30 (0x41cea6) and f41e780 (0x41e9c7). */
uint32_t vertrix_port_play_screen_actors_build_469480(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x50
    };
    Port port;
    uint8_t stack[BELOW + 8];
    Regs r;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    memset(&r, 0, sizeof r);
    r.port = &port;
    r.eax = entry->eax;
    r.edx = entry->edx;
    r.ebx = entry->ebx;
    r.ecx = entry->ecx;
    r.esi = entry->esi;
    r.edi = entry->edi;
    r.ebp = entry->esp - 4;
    port_set32(&port, r.ebp, 0, entry->ebp);
    port_set32(&port, r.ebp, -4u, entry->ebx);
    port_set32(&port, r.ebp, -8u, entry->ecx);
    port_set32(&port, r.ebp, -0xcu, entry->esi);
    port_set32(&port, r.ebp, -0x10u, entry->edi);
    build(&r);
    return port_return(&port, r.eax, r.edx);
}
