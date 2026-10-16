#include "port_rtlgamescreenbuilds.h"

/* 0x46c9d0 builds the game screen's actors. */

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

/* Original 0x46c9d0: 0x46c9d0 builds the game screen's actors. It allocates two 0x4ec-byte players
 * with get_memory (0x4ca000) and gives them ids 1 and 2. It calls player_set_side 0x43aab0 with 0
 * and 1, sets each player's update to 0x450f60 and stores it at 0x540f88[id]. It loads each
 * player's +0x488 from 0x532a68/0x532a6c and its +0x174 from 0x532aa4/0x532aa8, writes key words
 * 0xc8-0xcf, and links the two players through +0x3b0. It then builds a piece/board actor for each
 * player (0x429880, 0x42a200; stored at +0x3b8), plus previews, a marquee (0x46e8b0), menu items
 * and many other actors. Each actor is passed to list_delete 0x4b5e70 on list 0x54671c. The only
 * caller is lifted_f424360 at 0x42459b. Evidence: calls 0x4ca000, 0x43aab0, 0x4adf20, 0x4ac8f0,
 * 0x43bae0, 0x43ab30, 0x4b5e70, 0x43a6f0, 0x429880, 0x429bf0, 0x42a200, 0x43d3f0, 0x4b5700,
 * 0x4123d0, 0x4ae110, 0x4abd70, 0x4710d0, 0x4ac7b0, 0x4adfa0, 0x4b5580, 0x4b58a0, 0x42b150,
 * 0x4ac7d0, 0x4ac860 and 16 more; reads 0x532a68, 0x532a7c, 0x532aa4, 0x532a6c, 0x532a80, 0x532aa8,
 * 0x4f8ac2, 0x4f8abe, 0x4f8acc, 0x4f8ac8, 0x4f9060, 0x4f9064, 0x532a65, 0x4f8ad2, 0x4f8ace,
 * 0x4f8adc and more. Register-for-register from the listing (0x46c9d9..0x46e8ab); labels are the
 * original addresses. */
static void run(Regs *r)
{
    wr32(r, r->ebp - 0x5c, r->eax);
    wr32(r, r->ebp - 0x58, r->edx);
    wr32(r, r->ebp - 0x54, r->ebx);
    r->eax = r->ebp - 0x74;
    r->edx = 0x4ec1ec;
    r->ecx = 0x516018;
    push(r, r->port->env.chain);
    wr32(r, r->eax, r->stack[--r->pushed]);
    r->port->env.chain = r->eax;
    r->ebx = 0;
    r->eax = 0x4ec;
    wr32(r, r->ebp - 0x70, r->edx);
    wr32(r, r->ebp - 0x6c, r->ecx);
    wr32(r, r->ebp - 0x68, r->ebx);
    call(r, 0x4ca000, 0);
    if (r->eax != 0)
    {
        goto at_46e6ab;
    }
    r->esi = r->ebx;
at_46ca1d:
    r->eax = r->esi;
    r->edx = 0;
    wr32(r, r->esi, 0x1);
    call(r, 0x43aab0, 0);
    push(r, 0x0);
    push(r, 0x0);
    push(r, 0x0);
    push(r, 0x0);
    r->ecx = 0;
    r->ebx = 0;
    push(r, 0x0);
    r->eax = r->esi;
    r->edx = 0;
    call(r, 0x4adf20, 5);
    r->edx = 0x450f60;
    r->eax = r->esi;
    call(r, 0x4ac8f0, 0);
    r->eax = rd32(r, 0x532a68);
    r->edx = 0;
    wr32(r, r->esi + 0x488, r->eax);
    r->eax = r->esi;
    call(r, 0x43bae0, 0);
    r->eax = rd32(r, r->esi);
    wr32(r, r->esi + 0x470, 0x3);
    wr32(r, r->eax * 4 + 0x540f88, r->esi);
    wr16(r, r->esi + 0x168, 0xca);
    wr16(r, r->esi + 0x16a, 0xcb);
    r->edi = r->esi;
    wr16(r, r->esi + 0x16c, 0xc8);
    r->eax = rd32(r, 0x532a7c);
    wr16(r, r->esi + 0x16e, 0xc9);
    if (r->eax != 0x1)
    {
        goto at_46e6c5;
    }
    wr16(r, r->esi + 0x160, 0x0);
    wr16(r, r->esi + 0x162, 0x0);
    wr16(r, r->esi + 0x164, 0x0);
    wr16(r, r->esi + 0x166, 0x0);
at_46cace:
    r->eax = r->edi;
    call(r, 0x43ab30, 0);
    r->eax = rd32(r, 0x532aa4);
    r->edx = r->edi;
    wr32(r, r->edi + 0x174, r->eax);
    r->eax = 0x54671c;
    call(r, 0x4b5e70, 0);
    r->eax = rd32(r, r->edi + 0x15c);
    r->edx = rd32(r, r->ebp - 0x58);
    wr32(r, r->eax + 0xce4, r->edx);
    r->eax = 0x4ec;
    wr32(r, r->ebp - 0x4c, r->edi);
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_46cb21;
    }
    r->ebx = 0x3;
    wr32(r, r->ebp - 0x3c, r->eax);
    r->esi = 0;
    wr32(r, r->ebp - 0x68, r->ebx);
    call(r, 0x43a6f0, 0);
    wr32(r, r->ebp - 0x68, r->esi);
at_46cb21:
    r->esi = r->eax;
    r->edx = 0x1;
    r->eax = r->esi;
    wr32(r, r->esi, 0x2);
    call(r, 0x43aab0, 0);
    push(r, 0x0);
    push(r, 0x0);
    push(r, 0x0);
    push(r, 0x0);
    r->ecx = 0;
    r->ebx = 0;
    push(r, 0x0);
    r->eax = r->esi;
    r->edx = 0;
    call(r, 0x4adf20, 5);
    r->edx = 0x450f60;
    r->eax = r->esi;
    call(r, 0x4ac8f0, 0);
    r->eax = rd32(r, 0x532a6c);
    r->edx = 0;
    wr32(r, r->esi + 0x488, r->eax);
    r->eax = r->esi;
    call(r, 0x43bae0, 0);
    r->eax = rd32(r, r->esi);
    wr32(r, r->esi + 0x470, 0x3);
    wr32(r, r->eax * 4 + 0x540f88, r->esi);
    wr16(r, r->esi + 0x168, 0xce);
    wr16(r, r->esi + 0x16a, 0xcf);
    r->edi = r->esi;
    wr16(r, r->esi + 0x16c, 0xcc);
    r->eax = rd32(r, 0x532a80);
    wr16(r, r->esi + 0x16e, 0xcd);
    if (r->eax != 0x1)
    {
        goto at_46e743;
    }
    wr16(r, r->esi + 0x160, 0x0);
    wr16(r, r->esi + 0x162, 0x0);
    wr16(r, r->esi + 0x164, 0x0);
    wr16(r, r->esi + 0x166, 0x0);
at_46cbd7:
    r->eax = r->edi;
    call(r, 0x43ab30, 0);
    r->eax = rd32(r, 0x532aa8);
    r->edx = r->edi;
    wr32(r, r->edi + 0x174, r->eax);
    r->eax = 0x54671c;
    call(r, 0x4b5e70, 0);
    r->eax = rd32(r, r->edi + 0x15c);
    r->edx = rd32(r, r->ebp - 0x54);
    wr32(r, r->eax + 0xce4, r->edx);
    r->eax = rd32(r, r->ebp - 0x4c);
    wr32(r, r->eax + 0x3b0, r->edi);
    wr32(r, r->edi + 0x3b0, r->eax);
    r->eax = 0x284;
    wr32(r, r->ebp - 0x48, r->edi);
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_46cc39;
    }
    r->ebx = 0x5;
    wr32(r, r->ebp - 0x3c, r->eax);
    r->esi = 0;
    wr32(r, r->ebp - 0x68, r->ebx);
    call(r, 0x429880, 0);
    wr32(r, r->ebp - 0x68, r->esi);
at_46cc39:
    r->esi = r->eax;
    push(r, 0x0);
    r->ebx = rd32(r, 0x4f8ac2);
    push(r, 0x0);
    r->edx = rd32(r, 0x4f8abe);
    r->eax = r->esi;
    push(r, 0x0);
    wr32(r, r->esi, 0x3);
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    push(r, 0x0);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    wr32(r, r->esi + 0x4, 0x1);
    call(r, 0x4adf20, 5);
    r->edx = rd32(r, 0x4f8acc);
    r->eax = rd32(r, 0x4f8ac8);
    r->ecx = rd32(r, 0x4f9060);
    r->edi = rd32(r, 0x4f9064);
    r->eax = r->eax - r->ecx;
    r->edx = r->edx - r->edi;
    wr32(r, r->esi + 0x27c, r->eax);
    wr32(r, r->esi + 0x280, r->edx);
    r->edx = rd32(r, 0x532a65);
    r->eax = r->esi;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x18);
    call(r, 0x429bf0, 0);
    r->eax = r->esi;
    call(r, 0x42a200, 0);
    r->edx = r->esi;
    r->eax = 0x54671c;
    call(r, 0x4b5e70, 0);
    r->eax = rd32(r, r->ebp - 0x4c);
    wr32(r, r->eax + 0x3b8, r->esi);
    r->eax = 0x284;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_46cce3;
    }
    r->ebx = 0x7;
    wr32(r, r->ebp - 0x3c, r->eax);
    r->esi = 0;
    wr32(r, r->ebp - 0x68, r->ebx);
    call(r, 0x429880, 0);
    wr32(r, r->ebp - 0x68, r->esi);
at_46cce3:
    r->esi = r->eax;
    push(r, 0x0);
    r->ebx = rd32(r, 0x4f8ad2);
    push(r, 0x0);
    r->edx = rd32(r, 0x4f8ace);
    r->eax = r->esi;
    push(r, 0x0);
    wr32(r, r->esi, 0x4);
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    push(r, 0x0);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    wr32(r, r->esi + 0x4, 0x2);
    call(r, 0x4adf20, 5);
    r->edx = rd32(r, 0x4f8adc);
    r->eax = rd32(r, 0x4f8ad8);
    r->ecx = rd32(r, 0x4f9060);
    r->edi = rd32(r, 0x4f9064);
    r->eax = r->eax - r->ecx;
    r->edx = r->edx - r->edi;
    wr32(r, r->esi + 0x27c, r->eax);
    wr32(r, r->esi + 0x280, r->edx);
    r->edx = rd32(r, 0x532a69);
    r->eax = r->esi;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x18);
    wr32(r, r->esi + 0x278, 0x0);
    call(r, 0x429bf0, 0);
    r->eax = r->esi;
    call(r, 0x42a200, 0);
    r->edx = r->esi;
    r->eax = 0x54671c;
    r->edi = 0;
    call(r, 0x4b5e70, 0);
    r->eax = rd32(r, r->ebp - 0x48);
    wr32(r, r->ebp - 0x2c, r->edi);
    wr32(r, r->eax + 0x3b8, r->esi);
at_46cd79:
    r->eax = 0x194;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_46cd8c;
    }
    call(r, 0x43d3f0, 0);
at_46cd8c:
    r->esi = r->eax;
    if (r->edi != 0)
    {
        goto at_46e7fa;
    }
    wr32(r, r->eax, 0xb);
    wr32(r, r->eax + 0x4, 0x1);
at_46cda3:
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
    set_low16(&r->eax, rd16(r, 0x4f8a1c));
    set_low16(&r->eax, (r->eax & 0xffff) + rd16(r, 0x4f8a14));
    r->eax = r->eax - 1;
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    set_low16(&r->ebx, rd16(r, 0x4f8a10));
    push(r, r->eax);
    r->eax = rd32(r, 0x4f8a1a);
    r->ecx = rd32(r, 0x4f8a16);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    wr32(r, r->esi + 0x184, 0x0);
    push(r, r->eax);
    set_low16(&r->eax, rd16(r, 0x4f8a18));
    wr32(r, r->esi + 0x188, 0x2);
    r->eax = r->eax + r->ebx;
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    r->eax = r->eax - 1;
    r->edx = 0;
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    r->ebx = rd32(r, r->edi + 0x54682d);
    push(r, r->eax);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x18);
    r->eax = r->esi;
    call(r, 0x4b5700, 3);
    r->edx = rd32(r, r->ebp - 0x2c);
    r->eax = rd32(r, r->ebp - 0x5c);
    r->ebx = r->esi;
    r->edx = rd32(r, r->edx + 0x4fd608);
    call(r, 0x4123d0, 0);
    wr32(r, r->esi + 0x124, 0x1);
    if (r->edi != 0)
    {
        goto at_46e806;
    }
    r->eax = rd32(r, 0x4f8a14);
    r->ecx = rd32(r, 0x4f8a10);
    r->ebx = rd32(r, 0x4f8a1a);
    r->edx = rd32(r, 0x4f8a16);
    push(r, r->eax);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = r->esi;
    call(r, 0x4ae110, 1);
at_46ce5e:
    r->eax = 0x54671c;
    r->edx = r->esi;
    wr16(r, r->esi + 0x148, 0x2);
    call(r, 0x4b5e70, 0);
    r->edx = rd32(r, r->ebp - 0x2c);
    r->edx = r->edx + 0x4;
    r->edi = r->edi + 1;
    wr32(r, r->ebp - 0x2c, r->edx);
    if (r->edi < 0x4 && !r->port->env.failed)
    {
        goto at_46cd79;
    }
    r->eax = 0x15c;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_46cea9;
    }
    r->ecx = 0x9;
    wr32(r, r->ebp - 0x3c, r->eax);
    r->ebx = 0;
    wr32(r, r->ebp - 0x68, r->ecx);
    call(r, 0x4abd70, 0);
    wr32(r, r->ebp - 0x68, r->ebx);
at_46cea9:
    r->esi = r->eax;
    r->ecx = rd32(r, 0x4fbf60);
    r->ebx = rd32(r, 0x4f8a1a);
    r->edx = rd32(r, 0x4f8a16);
    r->eax = r->esi;
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    call(r, 0x4710d0, 0);
    wr32(r, r->esi + 0x4, 0xb);
    wr16(r, r->esi + 0x48, 0xff9c);
    wr8(r, r->esi + 0x4e, 0x32);
    r->edx = 0x1;
    wr8(r, r->esi + 0x93, 0x1);
    r->eax = r->esi;
    wr8(r, r->esi + 0x95, 0x4);
    call(r, 0x4ac7b0, 0);
    r->eax = r->esi;
    r->edx = 0;
    call(r, 0x4adfa0, 0);
    r->edx = 0x44fc60;
    r->eax = r->esi;
    r->edi = 0;
    call(r, 0x4ac8f0, 0);
    r->eax = 0x54671c;
    r->edx = r->esi;
    wr32(r, r->ebp - 0x40, r->edi);
    call(r, 0x4b5e70, 0);
at_46cf1b:
    r->eax = 0x194;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_46cf2e;
    }
    call(r, 0x43d3f0, 0);
at_46cf2e:
    r->esi = r->eax;
    if (r->edi != 0)
    {
        goto at_46e821;
    }
    wr32(r, r->eax, 0x9);
    wr32(r, r->eax + 0x4, 0x1);
at_46cf45:
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
    set_low16(&r->eax, rd16(r, 0x4f8a24));
    set_low16(&r->eax, (r->eax & 0xffff) + rd16(r, 0x4f8a14));
    r->eax = r->eax - 1;
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    set_low16(&r->edx, rd16(r, 0x4f8a10));
    push(r, r->eax);
    r->eax = rd32(r, 0x4f8a22);
    wr32(r, r->esi + 0x184, 0x0);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    wr32(r, r->esi + 0x188, 0x2);
    push(r, r->eax);
    set_low16(&r->eax, rd16(r, 0x4f8a20));
    r->ebx = rd32(r, r->edi + 0x54682d);
    r->eax = r->eax + r->edx;
    r->ecx = rd32(r, 0x4f8a1e);
    r->eax = r->eax - 1;
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x18);
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    push(r, r->eax);
    r->edx = rd32(r, 0x532bc0);
    r->eax = r->esi;
    call(r, 0x4b5700, 3);
    r->edx = rd32(r, r->ebp - 0x40);
    r->eax = rd32(r, r->ebp - 0x5c);
    r->ebx = r->esi;
    r->edx = rd32(r, r->edx + 0x4fd628);
    call(r, 0x4123d0, 0);
    wr32(r, r->esi + 0x124, 0x1);
    if (r->edi != 0)
    {
        goto at_46e82d;
    }
    r->eax = rd32(r, 0x4f8a14);
    r->ecx = rd32(r, 0x4f8a10);
    r->ebx = rd32(r, 0x4f8a22);
    r->edx = rd32(r, 0x4f8a1e);
    push(r, r->eax);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = r->esi;
    call(r, 0x4ae110, 1);
at_46d004:
    r->eax = 0x54671c;
    r->edx = r->esi;
    wr16(r, r->esi + 0x148, 0x4);
    call(r, 0x4b5e70, 0);
    r->edx = rd32(r, r->ebp - 0x40);
    r->edx = r->edx + 0x4;
    r->edi = r->edi + 1;
    wr32(r, r->ebp - 0x40, r->edx);
    if (r->edi < 0x4 && !r->port->env.failed)
    {
        goto at_46cf1b;
    }
    r->eax = 0x15c;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_46d04f;
    }
    r->ecx = 0xb;
    wr32(r, r->ebp - 0x3c, r->eax);
    r->ebx = 0;
    wr32(r, r->ebp - 0x68, r->ecx);
    call(r, 0x4abd70, 0);
    wr32(r, r->ebp - 0x68, r->ebx);
at_46d04f:
    r->esi = r->eax;
    r->ecx = rd32(r, 0x4fbf60);
    r->ebx = rd32(r, 0x4f8a22);
    r->edx = rd32(r, 0x4f8a1e);
    r->eax = r->esi;
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    call(r, 0x4710d0, 0);
    wr32(r, r->esi + 0x4, 0x9);
    wr16(r, r->esi + 0x48, 0xff9c);
    wr8(r, r->esi + 0x4e, 0x32);
    r->edx = 0x1;
    wr8(r, r->esi + 0x93, 0x1);
    r->eax = r->esi;
    wr8(r, r->esi + 0x95, 0x4);
    call(r, 0x4ac7b0, 0);
    r->eax = r->esi;
    r->edx = 0;
    call(r, 0x4adfa0, 0);
    r->edx = 0x44fad0;
    r->eax = r->esi;
    r->edi = 0;
    call(r, 0x4ac8f0, 0);
    r->eax = 0x54671c;
    r->edx = r->esi;
    wr32(r, r->ebp - 0x30, r->edi);
    call(r, 0x4b5e70, 0);
at_46d0c1:
    r->eax = 0x194;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_46d0d4;
    }
    call(r, 0x43d3f0, 0);
at_46d0d4:
    r->esi = r->eax;
    if (r->edi != 0)
    {
        goto at_46e848;
    }
    wr32(r, r->eax, 0xc);
    wr32(r, r->eax + 0x4, 0x2);
at_46d0eb:
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
    set_low16(&r->eax, rd16(r, 0x4f8a34));
    set_low16(&r->eax, (r->eax & 0xffff) + rd16(r, 0x4f8a14));
    r->eax = r->eax - 1;
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    set_low16(&r->ecx, rd16(r, 0x4f8a10));
    push(r, r->eax);
    r->eax = rd32(r, 0x4f8a32);
    wr32(r, r->esi + 0x184, 0x0);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    wr32(r, r->esi + 0x188, 0x2);
    push(r, r->eax);
    set_low16(&r->eax, rd16(r, 0x4f8a30));
    r->edx = 0;
    r->eax = r->eax + r->ecx;
    r->ebx = rd32(r, r->edi + 0x54682d);
    r->eax = r->eax - 1;
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x18);
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    r->ecx = rd32(r, 0x4f8a2e);
    push(r, r->eax);
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    r->eax = r->esi;
    call(r, 0x4b5700, 3);
    r->edx = rd32(r, r->ebp - 0x30);
    r->eax = rd32(r, r->ebp - 0x5c);
    r->ebx = r->esi;
    r->edx = rd32(r, r->edx + 0x4fd618);
    call(r, 0x4123d0, 0);
    wr32(r, r->esi + 0x124, 0x1);
    if (r->edi != 0)
    {
        goto at_46e854;
    }
    r->eax = rd32(r, 0x4f8a14);
    r->ecx = rd32(r, 0x4f8a10);
    r->ebx = rd32(r, 0x4f8a32);
    r->edx = rd32(r, 0x4f8a2e);
    push(r, r->eax);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = r->esi;
    call(r, 0x4ae110, 1);
at_46d1a6:
    r->eax = 0x54671c;
    r->edx = r->esi;
    wr16(r, r->esi + 0x148, 0x3);
    call(r, 0x4b5e70, 0);
    r->edx = rd32(r, r->ebp - 0x30);
    r->edx = r->edx + 0x4;
    r->edi = r->edi + 1;
    wr32(r, r->ebp - 0x30, r->edx);
    if (r->edi < 0x4 && !r->port->env.failed)
    {
        goto at_46d0c1;
    }
    r->eax = 0x15c;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_46d1f1;
    }
    r->ecx = 0xd;
    wr32(r, r->ebp - 0x3c, r->eax);
    r->ebx = 0;
    wr32(r, r->ebp - 0x68, r->ecx);
    call(r, 0x4abd70, 0);
    wr32(r, r->ebp - 0x68, r->ebx);
at_46d1f1:
    r->esi = r->eax;
    r->ecx = rd32(r, 0x4fbf60);
    r->ebx = rd32(r, 0x4f8a32);
    r->edx = rd32(r, 0x4f8a2e);
    r->eax = r->esi;
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    call(r, 0x4710d0, 0);
    wr32(r, r->esi + 0x4, 0xc);
    wr16(r, r->esi + 0x48, 0xff9c);
    wr8(r, r->esi + 0x4e, 0x32);
    r->edx = 0x1;
    wr8(r, r->esi + 0x93, 0x1);
    r->eax = r->esi;
    wr8(r, r->esi + 0x95, 0x4);
    call(r, 0x4ac7b0, 0);
    r->eax = r->esi;
    r->edx = 0;
    call(r, 0x4adfa0, 0);
    r->edx = 0x44fc60;
    r->eax = r->esi;
    r->edi = 0;
    call(r, 0x4ac8f0, 0);
    r->eax = 0x54671c;
    r->edx = r->esi;
    wr32(r, r->ebp - 0x28, r->edi);
    call(r, 0x4b5e70, 0);
at_46d263:
    r->eax = 0x194;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_46d276;
    }
    call(r, 0x43d3f0, 0);
at_46d276:
    r->esi = r->eax;
    if (r->edi != 0)
    {
        goto at_46e86f;
    }
    wr32(r, r->eax, 0xa);
    wr32(r, r->eax + 0x4, 0x2);
at_46d28d:
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
    set_low16(&r->eax, rd16(r, 0x4f8a2c));
    set_low16(&r->eax, (r->eax & 0xffff) + rd16(r, 0x4f8a14));
    r->eax = r->eax - 1;
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    set_low16(&r->ebx, rd16(r, 0x4f8a10));
    push(r, r->eax);
    r->eax = rd32(r, 0x4f8a2a);
    r->ecx = rd32(r, 0x4f8a26);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    wr32(r, r->esi + 0x184, 0x0);
    push(r, r->eax);
    set_low16(&r->eax, rd16(r, 0x4f8a28));
    wr32(r, r->esi + 0x188, 0x2);
    r->eax = r->eax + r->ebx;
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    r->eax = r->eax - 1;
    r->edx = rd32(r, 0x532bc0);
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    r->ebx = rd32(r, r->edi + 0x54682d);
    push(r, r->eax);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x18);
    r->eax = r->esi;
    call(r, 0x4b5700, 3);
    r->edx = rd32(r, r->ebp - 0x28);
    r->eax = rd32(r, r->ebp - 0x5c);
    r->ebx = r->esi;
    r->edx = rd32(r, r->edx + 0x4fd638);
    call(r, 0x4123d0, 0);
    wr32(r, r->esi + 0x124, 0x1);
    if (r->edi != 0)
    {
        goto at_46e87b;
    }
    r->eax = rd32(r, 0x4f8a14);
    r->ecx = rd32(r, 0x4f8a10);
    r->ebx = rd32(r, 0x4f8a2a);
    r->edx = rd32(r, 0x4f8a26);
    push(r, r->eax);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = r->esi;
    call(r, 0x4ae110, 1);
at_46d34c:
    r->eax = 0x54671c;
    r->edx = r->esi;
    wr16(r, r->esi + 0x148, 0x5);
    call(r, 0x4b5e70, 0);
    r->edx = rd32(r, r->ebp - 0x28);
    r->edx = r->edx + 0x4;
    r->edi = r->edi + 1;
    wr32(r, r->ebp - 0x28, r->edx);
    if (r->edi < 0x4 && !r->port->env.failed)
    {
        goto at_46d263;
    }
    r->eax = 0x15c;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_46d397;
    }
    r->ecx = 0xf;
    wr32(r, r->ebp - 0x3c, r->eax);
    r->ebx = 0;
    wr32(r, r->ebp - 0x68, r->ecx);
    call(r, 0x4abd70, 0);
    wr32(r, r->ebp - 0x68, r->ebx);
at_46d397:
    r->esi = r->eax;
    r->ecx = rd32(r, 0x4fbf60);
    r->ebx = rd32(r, 0x4f8a2a);
    r->edx = rd32(r, 0x4f8a26);
    r->eax = r->esi;
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    call(r, 0x4710d0, 0);
    wr32(r, r->esi + 0x4, 0xa);
    wr16(r, r->esi + 0x48, 0xff9c);
    wr8(r, r->esi + 0x4e, 0x32);
    r->edx = 0x1;
    wr8(r, r->esi + 0x93, 0x1);
    r->eax = r->esi;
    wr8(r, r->esi + 0x95, 0x4);
    call(r, 0x4ac7b0, 0);
    r->eax = r->esi;
    r->edx = 0;
    call(r, 0x4adfa0, 0);
    r->edx = 0x44fad0;
    r->eax = r->esi;
    call(r, 0x4ac8f0, 0);
    r->eax = 0x54671c;
    r->edx = r->esi;
    call(r, 0x4b5e70, 0);
    r->eax = 0x194;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_46d427;
    }
    r->esi = 0x11;
    wr32(r, r->ebp - 0x3c, r->eax);
    r->edi = 0;
    wr32(r, r->ebp - 0x68, r->esi);
    call(r, 0x4b5580, 0);
    wr32(r, r->ebp - 0x68, r->edi);
at_46d427:
    r->esi = r->eax;
    push(r, 0x0);
    push(r, 0x0);
    push(r, 0x0);
    r->eax = r->esi;
    wr32(r, r->esi, 0x7);
    push(r, 0x0);
    r->ecx = 0;
    r->ebx = 0;
    push(r, 0x0);
    r->edx = 0;
    wr32(r, r->esi + 0x4, 0x1);
    call(r, 0x4adf20, 5);
    set_low16(&r->eax, rd16(r, 0x4f8ae4));
    set_low16(&r->eax, (r->eax & 0xffff) + rd16(r, 0x4f8aec));
    r->eax = r->eax - 1;
    set_low16(&r->edi, rd16(r, 0x4f8ae8));
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    r->ebx = rd32(r, 0x4f9c09);
    push(r, r->eax);
    r->eax = rd32(r, 0x4f8ae2);
    wr32(r, r->esi + 0x184, 0x1);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    wr32(r, r->esi + 0x188, 0x8);
    push(r, r->eax);
    set_low16(&r->eax, rd16(r, 0x4f8ae0));
    r->edx = 0;
    r->eax = r->eax + r->edi;
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x18);
    r->eax = r->eax - 1;
    r->ecx = rd32(r, 0x4f8ade);
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    push(r, r->eax);
    r->eax = r->esi;
    wr8(r, r->esi + 0x44, 0x10);
    call(r, 0x4b5700, 3);
    r->edx = 0x450cd0;
    r->eax = r->esi;
    call(r, 0x4ac8f0, 0);
    r->edx = 0x5;
    r->eax = r->esi;
    r->ebx = r->esi;
    call(r, 0x4ac7b0, 0);
    r->edx = 0x28;
    r->eax = rd32(r, r->ebp - 0x5c);
    call(r, 0x4123d0, 0);
    r->eax = rd32(r, 0x4f8aec);
    r->ecx = rd32(r, 0x4f8ae8);
    r->ebx = rd32(r, 0x4f8ae2);
    r->edx = rd32(r, 0x4f8ade);
    push(r, r->eax);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = r->esi;
    wr32(r, r->esi + 0x124, 0x1);
    call(r, 0x4ae110, 1);
    r->edx = rd32(r, 0x532aa4);
    r->eax = r->esi;
    call(r, 0x4b58a0, 0);
    r->eax = 0x54671c;
    r->edx = r->esi;
    call(r, 0x4b5e70, 0);
    r->eax = 0x194;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_46d53d;
    }
    r->edx = 0x13;
    wr32(r, r->ebp - 0x3c, r->eax);
    r->ecx = 0;
    wr32(r, r->ebp - 0x68, r->edx);
    call(r, 0x4b5580, 0);
    wr32(r, r->ebp - 0x68, r->ecx);
at_46d53d:
    r->esi = r->eax;
    push(r, 0x0);
    push(r, 0x0);
    push(r, 0x0);
    r->eax = r->esi;
    wr32(r, r->esi, 0x8);
    push(r, 0x0);
    r->ecx = 0;
    r->ebx = 0;
    push(r, 0x0);
    r->edx = 0;
    wr32(r, r->esi + 0x4, 0x2);
    call(r, 0x4adf20, 5);
    set_low16(&r->eax, rd16(r, 0x4f8af4));
    set_low16(&r->eax, (r->eax & 0xffff) + rd16(r, 0x4f8afc));
    r->eax = r->eax - 1;
    set_low16(&r->ebx, rd16(r, 0x4f8af8));
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    r->ecx = rd32(r, 0x4f8aee);
    push(r, r->eax);
    r->eax = rd32(r, 0x4f8af2);
    wr32(r, r->esi + 0x184, 0x1);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    wr32(r, r->esi + 0x188, 0x8);
    push(r, r->eax);
    set_low16(&r->eax, rd16(r, 0x4f8af0));
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    r->eax = r->eax + r->ebx;
    r->edx = 0;
    r->eax = r->eax - 1;
    r->ebx = rd32(r, 0x4f9c09);
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x18);
    push(r, r->eax);
    r->eax = r->esi;
    wr8(r, r->esi + 0x44, 0x10);
    call(r, 0x4b5700, 3);
    r->edx = 0x450cd0;
    r->eax = r->esi;
    call(r, 0x4ac8f0, 0);
    r->edx = 0x5;
    r->eax = r->esi;
    r->ebx = r->esi;
    call(r, 0x4ac7b0, 0);
    r->edx = 0x29;
    r->eax = rd32(r, r->ebp - 0x5c);
    call(r, 0x4123d0, 0);
    r->ebx = rd32(r, 0x4f8afc);
    r->ecx = rd32(r, 0x4f8af8);
    r->edx = rd32(r, 0x4f8aee);
    r->eax = r->esi;
    push(r, r->ebx);
    r->ebx = rd32(r, 0x4f8af2);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    wr32(r, r->esi + 0x124, 0x1);
    call(r, 0x4ae110, 1);
    r->edx = rd32(r, 0x532aa8);
    r->eax = r->esi;
    call(r, 0x4b58a0, 0);
    r->eax = 0x54671c;
    r->edx = r->esi;
    call(r, 0x4b5e70, 0);
    r->eax = 0x174;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_46d654;
    }
    r->esi = 0x15;
    wr32(r, r->ebp - 0x3c, r->eax);
    r->edi = 0;
    wr32(r, r->ebp - 0x68, r->esi);
    call(r, 0x42b150, 0);
    wr32(r, r->ebp - 0x68, r->edi);
at_46d654:
    r->ecx = r->eax;
    r->edx = 0x44fe80;
    wr32(r, r->ecx, 0xd);
    r->eax = r->ecx;
    wr32(r, r->ecx + 0x4, 0x1);
    call(r, 0x4ac8f0, 0);
    r->eax = r->ecx;
    r->edx = 0;
    call(r, 0x4adfa0, 0);
    r->edx = 0x1f4;
    r->eax = r->ecx;
    call(r, 0x4ac7d0, 0);
    r->edx = 0x1f4;
    r->eax = r->ecx;
    call(r, 0x4ac860, 0);
    r->eax = r->ecx;
    r->edx = 0;
    call(r, 0x42b370, 0);
    r->eax = 0x54671c;
    r->edx = r->ecx;
    call(r, 0x4b5e70, 0);
    r->eax = 0x174;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_46d6c8;
    }
    r->edx = 0x17;
    wr32(r, r->ebp - 0x3c, r->eax);
    r->ecx = 0;
    wr32(r, r->ebp - 0x68, r->edx);
    call(r, 0x42b150, 0);
    wr32(r, r->ebp - 0x68, r->ecx);
at_46d6c8:
    r->ecx = r->eax;
    r->edx = 0x44fe80;
    wr32(r, r->ecx, 0xe);
    r->eax = r->ecx;
    wr32(r, r->ecx + 0x4, 0x2);
    call(r, 0x4ac8f0, 0);
    r->eax = r->ecx;
    r->edx = 0;
    call(r, 0x4adfa0, 0);
    r->edx = 0x1f4;
    r->eax = r->ecx;
    call(r, 0x4ac7d0, 0);
    r->edx = 0x1f4;
    r->eax = r->ecx;
    call(r, 0x4ac860, 0);
    r->edx = 0x1;
    r->eax = r->ecx;
    call(r, 0x42b370, 0);
    r->eax = 0x54671c;
    r->edx = r->ecx;
    call(r, 0x4b5e70, 0);
    r->edx = 0x5;
    r->eax = 0x598d30;
    call(r, 0x4826c0, 0);
    r->edx = 0x5;
    wr8(r, r->ebp - 0x14, (r->eax & 0xff));
    r->eax = 0x598d30;
    call(r, 0x4826c0, 0);
    r->edx = 0x5;
    wr8(r, r->ebp - 0x18, (r->eax & 0xff));
    r->eax = 0x598d30;
    call(r, 0x4826c0, 0);
    wr8(r, r->ebp - 0x10, (r->eax & 0xff));
    r->eax = 0x16c;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_46d765;
    }
    call(r, 0x43a160, 0);
at_46d765:
    r->edi = r->eax;
    push(r, 0x0);
    push(r, 0x0);
    push(r, 0x0);
    wr32(r, r->ebp - 0x50, r->edi);
    r->eax = r->edi;
    push(r, 0x0);
    r->ecx = 0;
    r->ebx = 0;
    push(r, 0x0);
    r->edx = 0;
    wr32(r, r->edi, 0x5);
    call(r, 0x4adf20, 5);
    push(r, 0xc);
    r->eax = rd32(r, 0x4f8b0e);
    r->ecx = rd32(r, 0x4f8b06);
    r->ebx = rd32(r, 0x4f8b02);
    r->edx = rd32(r, 0x4f8afe);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    push(r, r->eax);
    r->eax = rd32(r, 0x4f8b0a);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    push(r, r->eax);
    r->eax = r->edi;
    r->esi = r->edi;
    call(r, 0x43a310, 3);
    r->ebx = 0x44c3d0;
    r->ecx = r->edi + 0xc;
at_46d7c7:
    r->edx = r->ebx;
    r->eax = rd32(r, r->esi + 0x15c);
    r->esi = r->esi + 0x4;
    call(r, 0x4ac8f0, 0);
    if (r->esi != r->ecx && !r->port->env.failed)
    {
        goto at_46d7c7;
    }
    r->ecx = rd32(r, r->ebp - 0x13);
    r->ebx = rd32(r, r->ebp - 0x1b);
    r->edx = rd32(r, r->ebp - 0x17);
    r->eax = rd32(r, r->ebp - 0x50);
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x18);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x18);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x18);
    call(r, 0x43a4f0, 0);
    r->eax = rd32(r, r->ebp - 0x50);
    r->edx = 0x5;
    call(r, 0x43a520, 0);
    r->eax = 0x598d30;
    call(r, 0x4826c0, 0);
    r->edx = 0x5;
    r->ebx = r->eax;
    r->eax = 0x598d30;
    call(r, 0x4826c0, 0);
    r->edx = 0x5;
    wr16(r, r->ebp - 0x1c, (r->eax & 0xffff));
    r->eax = 0x598d30;
    call(r, 0x4826c0, 0);
    r->ecx = (uint32_t)(int32_t)(int8_t)(r->eax & 0xff);
    r->eax = rd32(r, r->ebp - 0x1f);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x18);
    r->edx = (uint32_t)(int32_t)(int8_t)(r->ebx & 0xff);
    r->ebx = r->eax;
    r->eax = rd32(r, r->ebp - 0x50);
    call(r, 0x43a4f0, 0);
    r->edx = rd32(r, r->ebp - 0x50);
    r->eax = 0x54671c;
    call(r, 0x4b5e70, 0);
    r->edx = rd32(r, r->ebp - 0x4c);
    r->eax = rd32(r, r->ebp - 0x50);
    wr32(r, r->edx + 0x3b4, r->eax);
    r->eax = 0x16c;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_46d872;
    }
    call(r, 0x43a160, 0);
at_46d872:
    wr32(r, r->ebp - 0x38, r->eax);
    push(r, 0x0);
    push(r, 0x0);
    push(r, 0x0);
    r->edi = rd32(r, r->ebp - 0x38);
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = 0;
    r->edx = 0;
    push(r, 0x0);
    r->eax = r->edi;
    wr32(r, r->edi, 0x6);
    call(r, 0x4adf20, 5);
    push(r, 0xc);
    r->eax = rd32(r, 0x4f8b22);
    r->ecx = rd32(r, 0x4f8b1a);
    r->ebx = rd32(r, 0x4f8b16);
    r->edx = rd32(r, 0x4f8b12);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    push(r, r->eax);
    r->eax = rd32(r, 0x4f8b1e);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    push(r, r->eax);
    r->eax = r->edi;
    r->esi = r->edi;
    call(r, 0x43a310, 3);
    r->ebx = 0x44c3d0;
    r->ecx = r->edi + 0xc;
at_46d8d5:
    r->edx = r->ebx;
    r->eax = rd32(r, r->esi + 0x15c);
    r->esi = r->esi + 0x4;
    call(r, 0x4ac8f0, 0);
    if (r->esi != r->ecx && !r->port->env.failed)
    {
        goto at_46d8d5;
    }
    r->ecx = rd32(r, r->ebp - 0x13);
    r->ebx = rd32(r, r->ebp - 0x1b);
    r->edx = rd32(r, r->ebp - 0x17);
    r->eax = r->edi;
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x18);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x18);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x18);
    call(r, 0x43a4f0, 0);
    r->eax = r->edi;
    r->edx = 0x5;
    call(r, 0x43a520, 0);
    r->eax = 0x598d30;
    call(r, 0x4826c0, 0);
    r->edx = 0x5;
    r->ecx = r->eax;
    r->eax = 0x598d30;
    call(r, 0x4826c0, 0);
    r->edx = 0x5;
    r->ebx = r->eax;
    r->eax = 0x598d30;
    call(r, 0x4826c0, 0);
    r->ebx = (uint32_t)(int32_t)(int8_t)(r->ebx & 0xff);
    r->eax = (uint32_t)(int32_t)(int8_t)(r->eax & 0xff);
    r->edx = (uint32_t)(int32_t)(int8_t)(r->ecx & 0xff);
    r->ecx = r->eax;
    r->eax = r->edi;
    call(r, 0x43a4f0, 0);
    r->eax = 0x54671c;
    r->edx = r->edi;
    call(r, 0x4b5e70, 0);
    r->eax = rd32(r, r->ebp - 0x48);
    wr32(r, r->eax + 0x3b4, r->edi);
    r->edi = 0;
at_46d963:
    r->ecx = rd32(r, 0x4f8b0c);
    r->ecx = r->ecx * r->edi;
    r->edx = rd32(r, 0x4f8b08);
    r->ebx = rd32(r, 0x4f8b00);
    r->eax = rd32(r, 0x4f8b0c);
    r->esi = rd32(r, 0x4f8b04);
    r->eax = r->eax >> 0x1;
    r->ecx = r->ecx + r->esi;
    r->edx = r->edx >> 0x1;
    r->ecx = r->ecx + r->eax;
    r->eax = 0x15c;
    r->edx = r->edx + r->ebx;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_46d9a0;
    }
    call(r, 0x4abd70, 0);
at_46d9a0:
    r->esi = r->eax;
    push(r, 0x0);
    push(r, 0x457170);
    push(r, 0x0);
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->ecx & 0xffff);
    push(r, 0x0);
    r->edx = (uint32_t)(int32_t)(int16_t)(r->edx & 0xffff);
    push(r, 0x0);
    r->eax = r->esi;
    r->ecx = 0;
    call(r, 0x4adf20, 5);
    r->eax = r->esi;
    r->edx = 0;
    call(r, 0x4ac910, 0);
    r->eax = r->edi + 0x64;
    r->edx = 0x1;
    wr32(r, r->esi, r->eax);
    r->eax = r->esi;
    call(r, 0x4ac470, 0);
    r->edx = 0x1;
    r->eax = r->esi;
    call(r, 0x4ac7b0, 0);
    wr8(r, r->esi + 0x4e, 0x28);
    r->edi = r->edi + 1;
    wr8(r, r->esi + 0x93, 0x1);
    r->eax = 0x54671c;
    wr8(r, r->esi + 0x94, 0x1);
    r->edx = r->esi;
    wr8(r, r->esi + 0x95, 0x2);
    call(r, 0x4b5e70, 0);
    if (r->edi < 0x3 && !r->port->env.failed)
    {
        goto at_46d963;
    }
    r->edi = 0;
at_46da15:
    r->edx = rd32(r, 0x4f8b1c);
    r->eax = rd32(r, 0x4f8b14);
    r->edx = r->edx >> 0x1;
    r->edx = r->edx + r->eax;
    r->eax = rd32(r, 0x4f8b20);
    r->eax = r->eax * r->edi;
    r->eax = r->eax + rd32(r, 0x4f8b18);
    r->ecx = rd32(r, 0x4f8b20);
    r->ecx = r->ecx >> 0x1;
    r->ecx = r->ecx + r->eax;
    r->eax = 0x15c;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_46da4f;
    }
    call(r, 0x4abd70, 0);
at_46da4f:
    r->esi = r->eax;
    push(r, 0x0);
    push(r, 0x4572b0);
    push(r, 0x0);
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->ecx & 0xffff);
    push(r, 0x0);
    r->edx = (uint32_t)(int32_t)(int16_t)(r->edx & 0xffff);
    push(r, 0x0);
    r->eax = r->esi;
    r->ecx = 0;
    call(r, 0x4adf20, 5);
    r->eax = r->esi;
    r->edx = 0;
    call(r, 0x4ac910, 0);
    r->eax = r->edi + 0x67;
    r->edx = 0x1;
    wr32(r, r->esi, r->eax);
    r->eax = r->esi;
    call(r, 0x4ac470, 0);
    r->edx = 0x1;
    r->eax = r->esi;
    call(r, 0x4ac7b0, 0);
    wr8(r, r->esi + 0x4e, 0x28);
    r->edi = r->edi + 1;
    wr8(r, r->esi + 0x93, 0x1);
    r->eax = 0x54671c;
    wr8(r, r->esi + 0x94, 0x1);
    r->edx = r->esi;
    wr8(r, r->esi + 0x95, 0x2);
    call(r, 0x4b5e70, 0);
    if (r->edi < 0x3 && !r->port->env.failed)
    {
        goto at_46da15;
    }
    r->eax = 0x15c;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_46dae5;
    }
    r->ebx = 0x19;
    wr32(r, r->ebp - 0x3c, r->eax);
    r->esi = 0;
    wr32(r, r->ebp - 0x68, r->ebx);
    call(r, 0x4abd70, 0);
    wr32(r, r->ebp - 0x68, r->esi);
at_46dae5:
    r->esi = r->eax;
    push(r, 0x0);
    push(r, 0x0);
    r->ebx = rd32(r, 0x4f8982);
    r->edx = rd32(r, 0x4f897e);
    push(r, 0x0);
    r->eax = r->esi;
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    push(r, 0x0);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    call(r, 0x4adf20, 5);
    r->edx = 0x1;
    wr32(r, r->esi, 0xf);
    r->eax = r->esi;
    wr32(r, r->esi + 0x4, 0x1);
    call(r, 0x4ac7b0, 0);
    r->edx = 0x44c5a0;
    r->eax = r->esi;
    call(r, 0x4ac8f0, 0);
    r->eax = r->esi;
    r->edx = 0;
    call(r, 0x4ac910, 0);
    wr8(r, r->esi + 0x4e, 0x0);
    wr8(r, r->esi + 0x93, 0x1);
    r->eax = r->esi;
    wr8(r, r->esi + 0x94, 0x1);
    r->edx = 0;
    wr8(r, r->esi + 0x95, 0x1);
    call(r, 0x4ac8d0, 0);
    r->eax = r->esi;
    r->edx = 0;
    call(r, 0x4ac710, 0);
    r->eax = r->esi;
    r->edx = 0;
    r->ecx = 0x140;
    call(r, 0x4ac950, 0);
    r->eax = 0x54671c;
    r->edx = r->esi;
    wr32(r, r->esi + 0x58, 0x0);
    call(r, 0x4b5e70, 0);
    push(r, 0x0);
    r->ebx = rd32(r, 0x4f898c);
    r->edi = rd32(r, 0x4f8984);
    r->edx = rd32(r, 0x4f8988);
    r->eax = rd32(r, 0x4f8980);
    r->ebx = r->ebx >> 0x1;
    r->edx = r->edx >> 0x1;
    r->ebx = r->ebx + r->edi;
    r->edx = r->edx + r->eax;
    r->eax = 0xf;
    r->ebx = r->ebx - 1;
    call(r, 0x46e8b0, 1);
    r->eax = 0x15c;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_46dbd5;
    }
    r->edx = 0x1b;
    wr32(r, r->ebp - 0x3c, r->eax);
    r->ecx = 0;
    wr32(r, r->ebp - 0x68, r->edx);
    call(r, 0x4abd70, 0);
    wr32(r, r->ebp - 0x68, r->ecx);
at_46dbd5:
    r->esi = r->eax;
    push(r, 0x0);
    push(r, 0x0);
    r->ebx = rd32(r, 0x4f8992);
    r->edx = rd32(r, 0x4f898e);
    push(r, 0x0);
    r->eax = r->esi;
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    push(r, 0x0);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    call(r, 0x4adf20, 5);
    r->edx = 0x1;
    wr32(r, r->esi, 0x10);
    r->eax = r->esi;
    wr32(r, r->esi + 0x4, 0x2);
    call(r, 0x4ac7b0, 0);
    r->edx = 0x44c5a0;
    r->eax = r->esi;
    call(r, 0x4ac8f0, 0);
    r->eax = r->esi;
    r->edx = 0;
    call(r, 0x4ac910, 0);
    wr8(r, r->esi + 0x4e, 0x0);
    wr8(r, r->esi + 0x93, 0x1);
    r->eax = r->esi;
    wr8(r, r->esi + 0x94, 0x1);
    r->edx = 0;
    wr8(r, r->esi + 0x95, 0x1);
    call(r, 0x4ac8d0, 0);
    r->eax = r->esi;
    r->edx = 0;
    call(r, 0x4ac710, 0);
    r->eax = r->esi;
    r->edx = 0;
    r->ecx = 0x140;
    call(r, 0x4ac950, 0);
    r->eax = 0x54671c;
    r->edx = r->esi;
    wr32(r, r->esi + 0x58, 0x0);
    call(r, 0x4b5e70, 0);
    push(r, 0x1);
    r->eax = rd32(r, 0x4f899c);
    r->ebx = rd32(r, 0x4f8994);
    r->edx = rd32(r, 0x4f8998);
    r->eax = r->eax >> 0x1;
    r->esi = rd32(r, 0x4f8990);
    r->eax = r->eax + r->ebx;
    r->edx = r->edx >> 0x1;
    r->ebx = r->eax - 0x1;
    r->edx = r->edx + r->esi;
    r->eax = 0x10;
    call(r, 0x46e8b0, 1);
    r->eax = 0x15c;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_46dcc7;
    }
    r->edi = 0x1d;
    wr32(r, r->ebp - 0x3c, r->eax);
    r->edx = 0;
    wr32(r, r->ebp - 0x68, r->edi);
    call(r, 0x4abd70, 0);
    wr32(r, r->ebp - 0x68, r->edx);
at_46dcc7:
    r->ecx = r->eax;
    r->edx = 0xa;
    r->eax = r->ecx;
    call(r, 0x4ac7b0, 0);
    r->edx = 0x450df0;
    r->eax = r->ecx;
    call(r, 0x4ac8f0, 0);
    r->eax = 0x54671c;
    r->edx = r->ecx;
    call(r, 0x4b5e70, 0);
    r->eax = 0x15c;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_46dd10;
    }
    r->ecx = 0x1f;
    wr32(r, r->ebp - 0x3c, r->eax);
    r->ebx = 0;
    wr32(r, r->ebp - 0x68, r->ecx);
    call(r, 0x4abd70, 0);
    wr32(r, r->ebp - 0x68, r->ebx);
at_46dd10:
    r->esi = r->eax;
    push(r, 0x0);
    push(r, 0x0);
    r->ebx = rd32(r, 0x4f8a02);
    r->edx = rd32(r, 0x4f89fe);
    push(r, 0x0);
    r->eax = r->esi;
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    push(r, 0x0);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    call(r, 0x4adf20, 5);
    r->edx = 0x1;
    wr32(r, r->esi, 0x11);
    r->eax = r->esi;
    wr32(r, r->esi + 0x4, 0x1);
    call(r, 0x4ac7b0, 0);
    r->edx = 0x450d40;
    r->eax = r->esi;
    call(r, 0x4ac8f0, 0);
    r->eax = r->esi;
    r->edx = 0;
    call(r, 0x4ac910, 0);
    wr8(r, r->esi + 0x93, 0x0);
    wr8(r, r->esi + 0x94, 0x1);
    wr8(r, r->esi + 0x95, 0x2);
    wr16(r, r->esi + 0xa8, 0x0);
    wr16(r, r->esi + 0xaa, 0x0);
    wr16(r, r->esi + 0xac, 0x0);
    r->edx = 0x5449fc;
    wr16(r, r->esi + 0xae, 0x0);
    r->eax = r->esi;
    wr8(r, r->esi + 0x8e, 0x3);
    call(r, 0x4ac8d0, 0);
    r->edx = rd32(r, 0x4fbf80);
    r->eax = r->esi;
    call(r, 0x4ac710, 0);
    r->eax = 0x54671c;
    r->edx = r->esi;
    call(r, 0x4b5e70, 0);
    r->eax = 0x15c;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_46dded;
    }
    r->esi = 0x21;
    wr32(r, r->ebp - 0x3c, r->eax);
    r->edi = 0;
    wr32(r, r->ebp - 0x68, r->esi);
    call(r, 0x4abd70, 0);
    wr32(r, r->ebp - 0x68, r->edi);
at_46dded:
    r->esi = r->eax;
    push(r, 0x0);
    push(r, 0x0);
    r->ebx = rd32(r, 0x4f8a0a);
    r->edx = rd32(r, 0x4f8a06);
    push(r, 0x0);
    r->eax = r->esi;
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    push(r, 0x0);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    call(r, 0x4adf20, 5);
    r->edx = 0x1;
    wr32(r, r->esi, 0x12);
    r->eax = r->esi;
    wr32(r, r->esi + 0x4, 0x2);
    call(r, 0x4ac7b0, 0);
    r->edx = 0x450d40;
    r->eax = r->esi;
    call(r, 0x4ac8f0, 0);
    r->eax = r->esi;
    r->edx = 0;
    call(r, 0x4ac910, 0);
    wr8(r, r->esi + 0x93, 0x0);
    wr8(r, r->esi + 0x94, 0x1);
    wr8(r, r->esi + 0x95, 0x2);
    wr16(r, r->esi + 0xa8, 0x0);
    wr16(r, r->esi + 0xaa, 0x0);
    wr16(r, r->esi + 0xac, 0x0);
    r->edx = 0x5449fc;
    wr16(r, r->esi + 0xae, 0x0);
    r->eax = r->esi;
    wr8(r, r->esi + 0x8e, 0x3);
    call(r, 0x4ac8d0, 0);
    r->edx = rd32(r, 0x4fbf80);
    r->eax = r->esi;
    call(r, 0x4ac710, 0);
    r->eax = 0x54671c;
    r->edx = r->esi;
    call(r, 0x4b5e70, 0);
    r->eax = 0x15c;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_46deca;
    }
    r->edx = 0x23;
    wr32(r, r->ebp - 0x3c, r->eax);
    r->ecx = 0;
    wr32(r, r->ebp - 0x68, r->edx);
    call(r, 0x4abd70, 0);
    wr32(r, r->ebp - 0x68, r->ecx);
at_46deca:
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
    r->edx = 0x3e8;
    wr32(r, r->esi, 0x17);
    r->eax = r->esi;
    wr32(r, r->esi + 0x4, 0x1);
    call(r, 0x4ac7d0, 0);
    r->edx = 0x96;
    r->eax = r->esi;
    call(r, 0x4ac860, 0);
    wr32(r, r->esi + 0x58, 0x0);
    r->edx = 0x450750;
    wr32(r, r->esi + 0x64, 0xc);
    r->eax = r->esi;
    wr32(r, r->esi + 0x70, 0xc);
    call(r, 0x4ac8f0, 0);
    r->eax = r->esi;
    r->edx = 0;
    call(r, 0x4ac910, 0);
    r->eax = 0x54671c;
    r->edx = r->esi;
    call(r, 0x4b5e70, 0);
    r->eax = 0x15c;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_46df61;
    }
    r->ebx = 0x25;
    wr32(r, r->ebp - 0x3c, r->eax);
    r->esi = 0;
    wr32(r, r->ebp - 0x68, r->ebx);
    call(r, 0x4abd70, 0);
    wr32(r, r->ebp - 0x68, r->esi);
at_46df61:
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
    r->edx = 0x3e8;
    wr32(r, r->esi, 0x18);
    r->eax = r->esi;
    wr32(r, r->esi + 0x4, 0x2);
    call(r, 0x4ac7d0, 0);
    r->edx = 0x96;
    r->eax = r->esi;
    call(r, 0x4ac860, 0);
    wr32(r, r->esi + 0x58, 0x0);
    r->edx = 0x450750;
    wr32(r, r->esi + 0x64, 0xc);
    r->eax = r->esi;
    wr32(r, r->esi + 0x70, 0xc);
    call(r, 0x4ac8f0, 0);
    r->eax = r->esi;
    r->edx = 0;
    r->edi = 0;
    call(r, 0x4ac910, 0);
    r->eax = 0x54671c;
    r->edx = r->esi;
    wr32(r, r->ebp - 0x34, r->edi);
    call(r, 0x4b5e70, 0);
    r->eax = 0x40;
    r->edx = 0x1b9;
    wr32(r, r->ebp - 0x24, r->eax);
    wr32(r, r->ebp - 0x20, r->edx);
at_46dfea:
    r->ecx = rd32(r, r->ebp - 0x5c);
    set_low16(&r->eax, rd16(r, r->edi + 0x4f8bb8));
    push(r, r->ecx);
    set_low16(&r->ecx, rd16(r, 0x533d74));
    r->ebx = rd32(r, 0x4fbfac);
    r->eax = r->eax + r->ecx;
    set_low16(&r->esi, rd16(r, 0x533d70));
    r->edx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    set_low16(&r->eax, rd16(r, r->edi + 0x4f8b88));
    push(r, 0xffffffffu);
    r->eax = r->eax + r->esi;
    r->ecx = rd32(r, r->ebp - 0x24);
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    call(r, 0x471100, 2);
    r->ebx = rd32(r, 0x4f8c4c);
    wr32(r, r->eax + 0x4, 0x17);
    set_low16(&r->edx, rd16(r, 0x533d74));
    wr32(r, r->eax + 0x124, 0x0);
    r->esi = r->eax;
    set_low16(&r->eax, rd16(r, r->edi + 0x4f8bb8));
    push(r, r->ebx);
    r->eax = r->eax + r->edx;
    set_low16(&r->edx, rd16(r, 0x533d70));
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    set_low16(&r->eax, rd16(r, r->edi + 0x4f8b88));
    r->eax = r->eax + r->edx;
    r->ecx = rd32(r, 0x4f8c48);
    r->edx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = r->esi;
    call(r, 0x4ae110, 1);
    r->eax = r->esi;
    r->edx = 0;
    call(r, 0x4adfa0, 0);
    r->eax = rd32(r, r->ebp - 0x34);
    r->eax = r->eax + 1;
    r->edx = 0xa;
    wr32(r, r->esi + 0x58, r->eax);
    r->eax = r->esi;
    call(r, 0x4ac7d0, 0);
    r->edx = 0x1f4;
    r->eax = r->esi;
    call(r, 0x4ac860, 0);
    r->edx = 0x450860;
    r->eax = r->esi;
    call(r, 0x4ac8f0, 0);
    r->eax = 0x15c;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_46e0c6;
    }
    r->esi = 0x27;
    wr32(r, r->ebp - 0x3c, r->eax);
    r->edx = 0;
    wr32(r, r->ebp - 0x68, r->esi);
    call(r, 0x4abd70, 0);
    wr32(r, r->ebp - 0x68, r->edx);
at_46e0c6:
    r->esi = r->eax;
    push(r, 0x0);
    set_low16(&r->ebx, rd16(r, 0x533d74));
    set_low16(&r->eax, rd16(r, r->edi + 0x4f8bb8));
    push(r, 0x0);
    set_low16(&r->ecx, rd16(r, 0x533d70));
    r->eax = r->eax + r->ebx;
    push(r, 0x0);
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    set_low16(&r->eax, rd16(r, r->edi + 0x4f8b88));
    push(r, 0x0);
    r->eax = r->eax + r->ecx;
    push(r, 0x0);
    r->edx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->ecx = 0;
    r->eax = r->esi;
    call(r, 0x4adf20, 5);
    r->edx = 0xa;
    r->eax = r->esi;
    wr32(r, r->esi + 0x4, 0x17);
    call(r, 0x4ac7d0, 0);
    r->edx = rd32(r, r->ebp - 0x20);
    r->eax = r->esi;
    call(r, 0x4ac860, 0);
    r->edx = 0x450a10;
    r->eax = r->esi;
    call(r, 0x4ac8f0, 0);
    r->eax = r->esi;
    r->edx = 0;
    call(r, 0x4adfa0, 0);
    r->eax = rd32(r, r->ebp - 0x34);
    r->edx = 0x546618;
    wr32(r, r->esi + 0x7c, 0x0);
    r->eax = r->eax + 1;
    wr8(r, r->esi + 0x93, 0x1);
    wr32(r, r->ebp - 0x44, r->eax);
    wr32(r, r->esi + 0x58, r->eax);
    r->eax = r->esi;
    wr8(r, r->esi + 0x95, 0x4);
    call(r, 0x4ac8d0, 0);
    r->eax = r->esi;
    r->edx = 0;
    call(r, 0x4ac710, 0);
    r->eax = r->esi;
    call(r, 0x4ac8a0, 0);
    r->edx = r->esi;
    r->eax = 0x54671c;
    r->ecx = rd32(r, r->ebp - 0x5c);
    call(r, 0x4b5e70, 0);
    r->ebx = rd32(r, 0x4fbfac);
    set_low16(&r->esi, rd16(r, 0x533d74));
    set_low16(&r->eax, rd16(r, r->edi + 0x4f8c18));
    push(r, r->ecx);
    r->eax = r->eax + r->esi;
    set_low16(&r->ecx, rd16(r, 0x533d70));
    r->edx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    set_low16(&r->eax, rd16(r, r->edi + 0x4f8be8));
    push(r, 0xffffffffu);
    r->eax = r->eax + r->ecx;
    r->ecx = rd32(r, r->ebp - 0x24);
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    call(r, 0x471100, 2);
    r->esi = r->eax;
    wr32(r, r->eax + 0x4, 0x18);
    r->ebx = rd32(r, 0x4f8c4c);
    wr32(r, r->eax + 0x124, 0x0);
    set_low16(&r->edx, rd16(r, 0x533d74));
    set_low16(&r->eax, rd16(r, r->edi + 0x4f8c18));
    push(r, r->ebx);
    r->eax = r->eax + r->edx;
    set_low16(&r->edx, rd16(r, 0x533d70));
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    set_low16(&r->eax, rd16(r, r->edi + 0x4f8be8));
    r->eax = r->eax + r->edx;
    r->ecx = rd32(r, 0x4f8c48);
    r->edx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = r->esi;
    call(r, 0x4ae110, 1);
    r->eax = r->esi;
    r->edx = 0;
    call(r, 0x4adfa0, 0);
    r->eax = rd32(r, r->ebp - 0x44);
    r->edx = 0xa;
    wr32(r, r->esi + 0x58, r->eax);
    r->eax = r->esi;
    call(r, 0x4ac7d0, 0);
    r->edx = 0x1f4;
    r->eax = r->esi;
    call(r, 0x4ac860, 0);
    r->edx = 0x450860;
    r->eax = r->esi;
    call(r, 0x4ac8f0, 0);
    r->eax = 0x15c;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_46e255;
    }
    r->esi = 0x29;
    wr32(r, r->ebp - 0x3c, r->eax);
    r->edx = 0;
    wr32(r, r->ebp - 0x68, r->esi);
    call(r, 0x4abd70, 0);
    wr32(r, r->ebp - 0x68, r->edx);
at_46e255:
    r->esi = r->eax;
    push(r, 0x0);
    set_low16(&r->ebx, rd16(r, 0x533d74));
    set_low16(&r->eax, rd16(r, r->edi + 0x4f8c18));
    push(r, 0x0);
    set_low16(&r->ecx, rd16(r, 0x533d70));
    r->eax = r->eax + r->ebx;
    push(r, 0x0);
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    set_low16(&r->eax, rd16(r, r->edi + 0x4f8be8));
    push(r, 0x0);
    r->eax = r->eax + r->ecx;
    push(r, 0x0);
    r->edx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->ecx = 0;
    r->eax = r->esi;
    call(r, 0x4adf20, 5);
    r->edx = 0xa;
    r->eax = r->esi;
    wr32(r, r->esi + 0x4, 0x18);
    call(r, 0x4ac7d0, 0);
    r->edx = rd32(r, r->ebp - 0x20);
    r->eax = r->esi;
    call(r, 0x4ac860, 0);
    r->edx = 0x450a10;
    r->eax = r->esi;
    r->edi = r->edi + 0x4;
    call(r, 0x4ac8f0, 0);
    r->eax = r->esi;
    r->edx = 0;
    r->ecx = rd32(r, r->ebp - 0x34);
    call(r, 0x4adfa0, 0);
    wr32(r, r->esi + 0x7c, 0x0);
    r->ecx = r->ecx + 1;
    wr8(r, r->esi + 0x93, 0x1);
    r->edx = 0x546618;
    wr8(r, r->esi + 0x95, 0x4);
    r->eax = r->esi;
    wr32(r, r->esi + 0x58, r->ecx);
    call(r, 0x4ac8d0, 0);
    r->eax = r->esi;
    r->edx = 0;
    r->ebx = 0;
    call(r, 0x4ac710, 0);
    r->eax = r->esi;
    wr32(r, r->ebp - 0x34, r->ecx);
    call(r, 0x4ac8a0, 0);
    r->edx = r->esi;
    r->eax = 0x54671c;
    r->esi = rd32(r, r->ebp - 0x24);
    call(r, 0x4b5e70, 0);
    r->eax = rd32(r, r->ebp - 0x20);
    wr32(r, r->ebp - 0x68, r->ebx);
    r->esi = r->esi + 1;
    r->eax = r->eax - 0x28;
    wr32(r, r->ebp - 0x24, r->esi);
    wr32(r, r->ebp - 0x20, r->eax);
    if (r->ecx < 0xc && !r->port->env.failed)
    {
        goto at_46dfea;
    }
    r->edx = rd32(r, r->ebp - 0x5c);
    r->ecx = 0x4c;
    r->ebx = rd32(r, 0x4fbfa8);
    r->eax = rd32(r, 0x4f8c4e);
    push(r, r->edx);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->edx = rd32(r, 0x4f8c52);
    push(r, 0xffffffffu);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = rd32(r, r->ebp - 0x5c);
    r->ebx = rd32(r, 0x4fbfa8);
    r->edx = rd32(r, 0x4f8c5a);
    r->eax = rd32(r, 0x4f8c56);
    push(r, r->ecx);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    push(r, 0xffffffffu);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->ecx = 0x4d;
    call(r, 0x471100, 2);
    r->eax = 0x15c;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_46e39b;
    }
    r->ebx = 0x2b;
    wr32(r, r->ebp - 0x3c, r->eax);
    r->esi = 0;
    wr32(r, r->ebp - 0x68, r->ebx);
    call(r, 0x4abd70, 0);
    wr32(r, r->ebp - 0x68, r->esi);
at_46e39b:
    r->esi = r->eax;
    push(r, 0x0);
    push(r, 0x0);
    push(r, 0x0);
    r->eax = r->esi;
    push(r, 0x0);
    r->ecx = 0;
    r->ebx = 0;
    push(r, 0x0);
    r->edx = 0;
    wr32(r, r->esi + 0x4, 0x1);
    call(r, 0x4adf20, 5);
    r->edx = 0x45aa70;
    r->eax = r->esi;
    call(r, 0x4ac8f0, 0);
    r->eax = 0x54671c;
    r->edx = r->esi;
    call(r, 0x4b5e70, 0);
    r->eax = 0x15c;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_46e3f6;
    }
    r->edi = 0x2d;
    wr32(r, r->ebp - 0x3c, r->eax);
    r->edx = 0;
    wr32(r, r->ebp - 0x68, r->edi);
    call(r, 0x4abd70, 0);
    wr32(r, r->ebp - 0x68, r->edx);
at_46e3f6:
    r->esi = r->eax;
    push(r, 0x0);
    r->ebx = rd32(r, 0x4f8a5a);
    push(r, 0x0);
    r->edx = rd32(r, 0x4f8a56);
    r->eax = r->esi;
    push(r, 0x0);
    wr32(r, r->esi, 0x13);
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    push(r, 0x0);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    wr32(r, r->esi + 0x4, 0x1);
    call(r, 0x4adf20, 5);
    set_low16(&r->eax, rd16(r, 0x533d68));
    wr8(r, r->esi + 0x8e, 0x3);
    set_low16(&r->ecx, rd16(r, 0x4f8a60));
    wr16(r, r->esi + 0xa8, (r->eax & 0xffff));
    set_low16(&r->edx, rd16(r, 0x4f8a68));
    wr16(r, r->esi + 0xaa, (r->ecx & 0xffff));
    set_low16(&r->ebx, rd16(r, 0x4f8a64));
    wr16(r, r->esi + 0xae, (r->edx & 0xffff));
    r->edx = 0x544a34;
    r->eax = r->esi;
    wr16(r, r->esi + 0xac, (r->ebx & 0xffff));
    call(r, 0x4ac8d0, 0);
    r->edx = rd32(r, 0x532a68);
    r->eax = r->esi;
    call(r, 0x4ac710, 0);
    r->eax = r->esi;
    call(r, 0x4ac8a0, 0);
    wr8(r, r->esi + 0x4e, 0x64);
    r->edx = 0x46;
    wr8(r, r->esi + 0x93, 0x1);
    r->eax = r->esi;
    wr32(r, r->esi + 0x150, 0x1);
    call(r, 0x4ac7b0, 0);
    r->edx = 0x45abd0;
    r->eax = r->esi;
    call(r, 0x4ac8f0, 0);
    r->ecx = rd32(r, 0x4f8a74);
    r->ebx = rd32(r, 0x4f8a6a);
    r->edx = rd32(r, 0x533d6a);
    r->eax = r->esi;
    push(r, r->ecx);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->ecx = rd32(r, 0x4f8a70);
    wr32(r, r->esi + 0x124, 0x1);
    call(r, 0x4ae110, 1);
    r->eax = 0x54671c;
    r->edx = r->esi;
    wr32(r, r->esi + 0x13c, 0x0);
    call(r, 0x4b5e70, 0);
    r->eax = 0x15c;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_46e51e;
    }
    r->ebx = 0x2f;
    wr32(r, r->ebp - 0x3c, r->eax);
    r->esi = 0;
    wr32(r, r->ebp - 0x68, r->ebx);
    call(r, 0x4abd70, 0);
    wr32(r, r->ebp - 0x68, r->esi);
at_46e51e:
    r->esi = r->eax;
    push(r, 0x0);
    push(r, 0x0);
    push(r, 0x0);
    r->eax = r->esi;
    push(r, 0x0);
    r->ecx = 0;
    r->ebx = 0;
    push(r, 0x0);
    r->edx = 0;
    wr32(r, r->esi + 0x4, 0x2);
    call(r, 0x4adf20, 5);
    r->edx = 0x45aa70;
    r->eax = r->esi;
    call(r, 0x4ac8f0, 0);
    r->eax = 0x54671c;
    r->edx = r->esi;
    call(r, 0x4b5e70, 0);
    r->eax = 0x15c;
    call(r, 0x4ca000, 0);
    if (r->eax != 0)
    {
        goto at_46e896;
    }
at_46e568:
    r->esi = r->eax;
    push(r, 0x0);
    r->ebx = rd32(r, 0x4f8a7a);
    push(r, 0x0);
    r->edx = rd32(r, 0x4f8a76);
    r->eax = r->esi;
    push(r, 0x0);
    wr32(r, r->esi, 0x14);
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    push(r, 0x0);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    wr32(r, r->esi + 0x4, 0x2);
    call(r, 0x4adf20, 5);
    set_low16(&r->eax, rd16(r, 0x4f8a80));
    wr8(r, r->esi + 0x8e, 0x3);
    set_low16(&r->edx, rd16(r, 0x4f8a84));
    wr16(r, r->esi + 0xa8, (r->eax & 0xffff));
    set_low16(&r->ebx, rd16(r, 0x4f8a88));
    wr16(r, r->esi + 0xaa, (r->edx & 0xffff));
    set_low16(&r->ecx, rd16(r, 0x4f8a8c));
    wr16(r, r->esi + 0xac, (r->ebx & 0xffff));
    r->edx = 0x544a34;
    r->eax = r->esi;
    wr16(r, r->esi + 0xae, (r->ecx & 0xffff));
    call(r, 0x4ac8d0, 0);
    r->edx = rd32(r, 0x532a6c);
    r->eax = r->esi;
    call(r, 0x4ac710, 0);
    r->eax = r->esi;
    call(r, 0x4ac8a0, 0);
    wr8(r, r->esi + 0x4e, 0x64);
    wr16(r, r->esi + 0x4a, 0x64);
    wr16(r, r->esi + 0x4c, 0x32);
    r->edx = 0x46;
    wr8(r, r->esi + 0x93, 0x1);
    r->eax = r->esi;
    wr32(r, r->esi + 0x150, 0x1);
    call(r, 0x4ac7b0, 0);
    r->edx = 0x45abd0;
    r->eax = r->esi;
    call(r, 0x4ac8f0, 0);
    r->ecx = rd32(r, 0x4f8a9c);
    r->ebx = rd32(r, 0x4f8a92);
    r->edx = rd32(r, 0x4f8a8e);
    r->eax = r->esi;
    push(r, r->ecx);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->ecx = rd32(r, 0x4f8a98);
    wr32(r, r->esi + 0x124, 0x1);
    call(r, 0x4ae110, 1);
    r->eax = 0x54671c;
    r->edx = r->esi;
    wr32(r, r->esi + 0x13c, 0x0);
    call(r, 0x4b5e70, 0);
    call(r, 0x4726d0, 0);
    r->eax = rd32(r, r->ebp - 0x4c);
    r->eax = rd32(r, r->eax + 0x3b8);
    call(r, 0x429d50, 0);
    r->eax = rd32(r, r->ebp - 0x48);
    r->eax = rd32(r, r->eax + 0x3b8);
    call(r, 0x429d50, 0);
    r->eax = rd32(r, r->ebp - 0x74);
    r->port->env.chain = r->eax;
    return;
at_46e6ab:
    r->esi = 0x1;
    wr32(r, r->ebp - 0x3c, r->eax);
    wr32(r, r->ebp - 0x68, r->esi);
    call(r, 0x43a6f0, 0);
    wr32(r, r->ebp - 0x68, r->ebx);
    r->esi = r->eax;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_46ca1d;
at_46e6c5:
    if ((rd32(r, 0x532a80)) != 0x1)
    {
        goto at_46e707;
    }
at_46e6ce:
    set_low16(&r->eax, rd16(r, 0x532b6c));
    wr16(r, r->esi + 0x160, (r->eax & 0xffff));
    set_low16(&r->eax, rd16(r, 0x532b6e));
    wr16(r, r->esi + 0x162, (r->eax & 0xffff));
    set_low16(&r->eax, rd16(r, 0x532b70));
    wr16(r, r->esi + 0x164, (r->eax & 0xffff));
    set_low16(&r->eax, rd16(r, 0x532b72));
    wr16(r, r->esi + 0x166, (r->eax & 0xffff));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_46cace;
at_46e707:
    if ((rd32(r, 0x532a74)) != 0x0 && !r->port->env.failed)
    {
        goto at_46e6ce;
    }
    wr32(r, r->esi + 0x454, 0x1);
    wr16(r, r->esi + 0x160, 0x6e);
    wr16(r, r->esi + 0x162, 0x6f);
    wr16(r, r->esi + 0x164, 0x6c);
    wr16(r, r->esi + 0x166, 0x6d);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_46cace;
at_46e743:
    if ((rd32(r, 0x532a7c)) != 0x1)
    {
        goto at_46e785;
    }
    set_low16(&r->eax, rd16(r, 0x532b6c));
    wr16(r, r->esi + 0x160, (r->eax & 0xffff));
    set_low16(&r->eax, rd16(r, 0x532b6e));
    wr16(r, r->esi + 0x162, (r->eax & 0xffff));
    set_low16(&r->eax, rd16(r, 0x532b70));
    wr16(r, r->esi + 0x164, (r->eax & 0xffff));
    set_low16(&r->eax, rd16(r, 0x532b72));
    wr16(r, r->esi + 0x166, (r->eax & 0xffff));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_46cbd7;
at_46e785:
    if ((rd32(r, 0x532a78)) != 0x0)
    {
        goto at_46e7c1;
    }
    wr32(r, r->esi + 0x454, 0x1);
    wr16(r, r->esi + 0x160, 0xc6);
    wr16(r, r->esi + 0x162, 0xc7);
    wr16(r, r->esi + 0x164, 0xc4);
    wr16(r, r->esi + 0x166, 0xc5);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_46cbd7;
at_46e7c1:
    set_low16(&r->eax, rd16(r, 0x532b74));
    wr16(r, r->esi + 0x160, (r->eax & 0xffff));
    set_low16(&r->eax, rd16(r, 0x532b76));
    wr16(r, r->esi + 0x162, (r->eax & 0xffff));
    set_low16(&r->eax, rd16(r, 0x532b78));
    wr16(r, r->esi + 0x164, (r->eax & 0xffff));
    set_low16(&r->eax, rd16(r, 0x532b7a));
    wr16(r, r->esi + 0x166, (r->eax & 0xffff));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_46cbd7;
at_46e7fa:
    wr32(r, r->eax + 0x4, 0xb);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_46cda3;
at_46e806:
    r->edx = 0x44fc00;
    r->eax = r->esi;
    wr32(r, r->esi + 0x138, 0x0);
    call(r, 0x4ac8f0, 0);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_46ce5e;
at_46e821:
    wr32(r, r->eax + 0x4, 0x9);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_46cf45;
at_46e82d:
    r->edx = 0x44fa70;
    r->eax = r->esi;
    wr32(r, r->esi + 0x138, 0x0);
    call(r, 0x4ac8f0, 0);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_46d004;
at_46e848:
    wr32(r, r->eax + 0x4, 0xc);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_46d0eb;
at_46e854:
    r->edx = 0x44fc00;
    r->eax = r->esi;
    wr32(r, r->esi + 0x138, 0x0);
    call(r, 0x4ac8f0, 0);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_46d1a6;
at_46e86f:
    wr32(r, r->eax + 0x4, 0xa);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_46d28d;
at_46e87b:
    r->edx = 0x44fa70;
    r->eax = r->esi;
    wr32(r, r->esi + 0x138, 0x0);
    call(r, 0x4ac8f0, 0);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_46d34c;
at_46e896:
    r->edi = 0x31;
    wr32(r, r->ebp - 0x3c, r->eax);
    r->edx = 0;
    wr32(r, r->ebp - 0x68, r->edi);
    call(r, 0x4abd70, 0);
    wr32(r, r->ebp - 0x68, r->edx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_46e568;
}

uint32_t vertrix_port_game_screen_build_actors_46c9d0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x78
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
    port_set32(&port, r.ebp, -0x4u, entry->ecx);
    port_set32(&port, r.ebp, -0x8u, entry->esi);
    port_set32(&port, r.ebp, -0xcu, entry->edi);
    run(&r);
    return port_return(&port, r.eax, r.edx);
}
