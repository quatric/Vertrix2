#include "port_rtlleveltitleletters.h"

/* For the level index at [0x532a64], it reads the line count from 0x53bd0c and walks 36-byte
 * strings from 0x53bdfc. */

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
    uint32_t fa;
    uint32_t fb;
    unsigned fk;
    unsigned fw;
    uint32_t fc;
} Regs;

/* The kinds of the last flag-setting instruction: a subtraction or compare of fa and fb, an
 * addition, a logical result fa (CF and OF clear), and inc / dec of the result fa (CF kept). */
enum
{
    F_SUB,
    F_ADD,
    F_LOGIC,
    F_INC,
    F_DEC
};

/* The conditions of the jumps and sets. */
enum
{
    CC_E,
    CC_NE,
    CC_B,
    CC_AE,
    CC_BE,
    CC_A,
    CC_L,
    CC_GE,
    CC_LE,
    CC_G,
    CC_S,
    CC_NS
};

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

static uint32_t rd8(Regs *r, uint32_t address)
{
    return port_u8(r->port, address, 0);
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

static void set_low8(uint32_t *reg, uint32_t value)
{
    *reg = (*reg & 0xffffff00u) | (value & 0xff);
}

static void set_low16(uint32_t *reg, uint32_t value)
{
    *reg = (*reg & 0xffff0000u) | (value & 0xffff);
}

/* idiv and div of edx:eax as the original's (a zero divisor or an overflowing quotient leaves
 * both registers). */
static void idiv32(Regs *r, uint32_t value)
{
    LiftFlags flags;
    memset(&flags, 0, sizeof flags);
    lift_idiv1(32, value, &r->eax, &r->edx, &flags);
}

/* The last value pushed taken back. */
static uint32_t pop(Regs *r)
{
    return r->pushed != 0 ? r->stack[--r->pushed] : 0;
}

/* Original 0x46f440: For the level index at [0x532a64], it reads the line count from 0x53bd0c and
 * walks 36-byte strings from 0x53bdfc. Each line is copied, upper-cased (vertrix_port_string_upper)
 * and measured (vertrix_port_text_measure at 0x440610), then centred in 640x480. For each character
 * it allocates an actor (get_memory 0x15c, actor_initialize) and sets its glyph (font_glyph
 * 0x43f420, actor_set_b4), with randomized position and motion (random_below, actor_randomize_d0,
 * actor_orbit_point, point_heading/point_distance). The callers are
 * vertrix_port_level_screen_setup_41f9b0 (0x41fa9f) and lifted_f41fe10 (0x41ff24). Evidence: calls
 * 0x4ca070, 0x4ca310, 0x4ca710, 0x440610, 0x4ca000, 0x4adf20, 0x4826c0, 0x43f420, 0x4ac950,
 * 0x4ac810, 0x4ac7d0, 0x4ac910, 0x4b5e70, 0x4abd70, 0x4ac8d0, 0x4ac710, 0x4ac8a0, 0x4ac7b0,
 * 0x4ac470, 0x4ac7e0, 0x4ac8f0, 0x4ca210, 0x484680, 0x4ad510 and 3 more; reads 0x532a64, 0x54001b.
 * Register-for-register from the listing (0x46f44b..0x470956); labels are the original addresses.
 */
static void run(Regs *r)
{
    r->eax = r->ebp - 0x88;
    r->edx = 0x4ec1ec;
    r->ecx = 0x5161ec;
    push(r, r->port->env.chain);
    wr32(r, r->eax, pop(r));
    r->port->env.chain = r->eax;
    r->ebx = 0;
    r->eax = rd32(r, 0x532a64);
    wr32(r, r->ebp - 0x84, r->edx);
    wr32(r, r->ebp - 0x30, r->eax);
    wr32(r, r->ebp - 0x80, r->ecx);
    r->edx = rd32(r, r->ebp - 0x30);
    r->eax = r->ebp - 0x60;
    r->edx = r->edx << 0x2;
    wr32(r, r->ebp - 0x7c, r->ebx);
    call(r, 0x4ca070, 0);
    r->eax = rd32(r, r->edx + 0x4f9b50);
    wr32(r, r->ebp - 0x2c, r->eax);
    r->eax = rd32(r, r->edx + 0x4f9ba0);
    r->ecx = rd32(r, r->edx + 0x53bd0c);
    wr32(r, r->ebp - 0x40, r->eax);
    r->eax = r->ecx * 4;
    r->eax = r->eax - r->ecx;
    r->eax = r->eax << 0x3;
    r->eax = r->eax + r->ecx;
    r->eax = r->eax + r->eax;
    r->eax = r->eax - 0x14;
    wr32(r, r->ebp - 0x58, r->eax);
    r->eax = 0x1e0;
    r->eax = r->eax - rd32(r, r->ebp - 0x58);
    r->esi = 0x1;
    r->eax = r->eax >> 0x1;
    wr32(r, r->ebp - 0x44, r->ebx);
    r->eax = r->eax + 0xf;
    r->ecx = rd32(r, r->ebp - 0x30);
    wr32(r, r->ebp - 0x38, r->eax);
    r->eax = r->ecx * 8;
    wr32(r, r->ebp - 0x54, r->ebx);
    r->eax = r->eax + r->ecx;
    wr32(r, r->ebp - 0x7c, r->esi);
    r->eax = r->eax << 0x2;
    wr32(r, r->ebp - 0x24, r->edx);
    r->eax = r->eax + 0x53bdfc;
    r->ebx = rd32(r, r->edx + 0x53bd0c);
    wr32(r, r->ebp - 0x6c, r->eax);
    if (r->ebx == 0)
    {
        goto at_46f79d;
    }
at_46f502:
    r->edx = rd32(r, r->ebp - 0x6c);
    r->eax = r->ebp - 0x60;
    r->ecx = r->ebp - 0x5c;
    call(r, 0x4ca310, 0);
    r->eax = r->ebp - 0x60;
    r->ebx = 0x10;
    call(r, 0x4ca710, 0);
    r->esi = rd32(r, r->ebp - 0x60);
    r->eax = r->ebp - 0x58;
    r->edx = rd32(r, r->ebp - 0x60);
    push(r, r->eax);
    r->eax = rd32(r, 0x54001b);
    r->esi = r->esi - 0xc;
    r->eax = (uint32_t)((int32_t)r->eax >> 0x18);
    r->esi = rd32(r, r->esi + 0x4);
    call(r, 0x440610, 1);
    r->eax = 0x280;
    r->eax = r->eax - rd32(r, r->ebp - 0x5c);
    r->eax = r->eax + 1;
    r->edi = 0;
    r->eax = r->eax >> 0x1;
    wr32(r, r->ebp - 0x3c, r->edi);
    r->eax = r->eax + 0x11;
    wr32(r, r->ebp - 0x28, r->esi);
    wr32(r, r->ebp - 0x20, r->eax);
    if (r->esi == 0)
    {
        goto at_46f773;
    }
    r->eax = rd32(r, r->ebp - 0x54);
    r->eax = r->eax & 0x1;
    r->esi = r->esi >> 0x1;
    wr32(r, r->ebp - 0x68, r->eax);
    r->eax = r->esi;
    r->eax = 0u - r->eax;
    wr32(r, r->ebp - 0x34, r->esi);
    wr32(r, r->ebp - 0x48, r->eax);
at_46f570:
    r->eax = 0x15c;
    call(r, 0x4ca000, 0);
    if (r->eax != 0)
    {
        goto at_46faaa;
    }
at_46f582:
    r->esi = r->eax;
    r->ebx = rd32(r, r->ebp - 0x2c);
    r->edi = r->esi;
    if (r->ebx != 0)
    {
        goto at_46fb1d;
    }
    push(r, r->ebx);
    r->eax = 0x458150;
    push(r, r->eax);
    push(r, r->ebx);
    push(r, r->ebx);
    r->ecx = 0;
    push(r, r->ebx);
    r->edx = 0;
    r->eax = r->esi;
    call(r, 0x4adf20, 5);
    r->eax = rd32(r, r->ebp - 0x3c);
    r->eax = r->eax + rd32(r, r->ebp - 0x60);
    set_low8(&r->eax, rd8(r, r->eax));
    r->eax = r->eax & 0xff;
    r->edx = 0x2;
    wr32(r, r->edi + 0x58, r->eax);
    r->eax = 0x598d30;
    call(r, 0x4826c0, 0);
    r->eax = r->eax & 0xffff;
    wr32(r, r->edi + 0x64, r->eax);
    r->edx = 0;
    r->eax = rd32(r, r->edi + 0x61);
    set_low8(&r->edx, rd8(r, r->edi + 0x58));
    r->eax = (uint32_t)((int32_t)r->eax >> 0x18);
    call(r, 0x43f420, 0);
    r->edx = r->eax;
    r->eax = r->edi;
    call(r, 0x4ac950, 0);
    r->eax = rd32(r, r->ebp - 0x20);
    wr32(r, r->edi + 0xd4, 0x64);
    wr16(r, r->edi + 0x8, (r->eax & 0xffff));
    r->eax = rd32(r, r->ebp - 0x38);
    r->edx = 0x4;
    wr16(r, r->edi + 0xa, (r->eax & 0xffff));
    r->eax = r->edi;
    wr32(r, r->edi + 0xd8, 0x64);
    call(r, 0x4ac810, 0);
    r->eax = 0x598d30;
    wr16(r, r->edi + 0xc, 0x0);
    call(r, 0x4826c0, 0);
    r->eax = r->eax & 0xffff;
    if (r->eax != 0)
    {
        goto at_46fab4;
    }
    r->edx = 0x280;
    r->eax = 0x598d30;
    call(r, 0x4826c0, 0);
    wr16(r, r->edi + 0x16, 0xffce);
at_46f644:
    wr16(r, r->edi + 0xe, (r->eax & 0xffff));
at_46f648:
    r->eax = rd32(r, r->ebp - 0x20);
    wr16(r, r->edi + 0x10, (r->eax & 0xffff));
    r->eax = rd32(r, r->ebp - 0x38);
    wr16(r, r->edi + 0x18, (r->eax & 0xffff));
    set_low16(&r->eax, rd16(r, r->edi + 0xe));
    wr16(r, r->edi + 0x8, (r->eax & 0xffff));
    set_low16(&r->eax, rd16(r, r->edi + 0x16));
    wr16(r, r->edi + 0xa, (r->eax & 0xffff));
    r->edx = rd32(r, r->edi + 0xe);
    r->eax = rd32(r, r->edi + 0x6);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->edx = r->edx - r->eax;
    wr16(r, r->edi + 0x12, 0x1);
    r->eax = r->edx;
    wr16(r, r->edi + 0x1a, 0x1);
    r->edx = (int32_t)r->eax < 0 ? 0xffffffffu : 0;
    r->eax = r->eax ^ r->edx;
    r->eax = r->eax - r->edx;
    r->esi = r->eax;
    r->ebx = r->eax;
    r->edx = rd32(r, r->edi + 0x16);
    r->eax = rd32(r, r->edi + 0x8);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->edx = r->edx - r->eax;
    r->eax = r->edx;
    r->edx = (int32_t)r->eax < 0 ? 0xffffffffu : 0;
    r->eax = r->eax ^ r->edx;
    r->eax = r->eax - r->edx;
    r->ecx = r->eax;
    if ((int32_t)r->esi <= (int32_t)0x280)
    {
        goto at_46f6af;
    }
    r->ebx = 0x280;
at_46f6af:
    if ((int32_t)r->ecx <= (int32_t)0x1e0)
    {
        goto at_46f6bc;
    }
    r->ecx = 0x1e0;
at_46f6bc:
    r->edx = r->ebx + r->ebx * 4;
    r->ebx = 0x280;
    r->eax = r->edx;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    idiv32(r, r->ebx);
    r->edx = r->ecx + r->ecx * 4;
    r->eax = r->eax + 1;
    r->ecx = 0x1e0;
    wr16(r, r->edi + 0x12, (r->eax & 0xffff));
at_46f6d8:
    r->eax = r->edx;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    idiv32(r, r->ecx);
    r->eax = r->eax + 1;
    r->edx = 0xa;
    wr16(r, r->edi + 0x1a, (r->eax & 0xffff));
    r->eax = r->edi;
at_46f6eb:
    call(r, 0x4ac7d0, 0);
    wr8(r, r->edi + 0x95, 0x4);
    wr8(r, r->edi + 0x93, 0x1);
    r->edx = 0x5;
    wr8(r, r->edi + 0x44, 0x0);
    r->eax = 0x598d30;
    wr32(r, r->edi + 0x80, 0x0);
    call(r, 0x4826c0, 0);
    r->eax = r->eax & 0xffff;
    wr8(r, r->edi + 0x8c, 0x0);
    r->eax = r->eax + 1;
at_46f728:
    wr32(r, r->edi + 0x88, r->eax);
at_46f72e:
    r->eax = rd32(r, r->ebp - 0x40);
    if (r->eax != 0)
    {
        goto at_4708d2;
    }
    r->edx = 0x4589e0;
at_46f73e:
    r->eax = r->edi;
at_46f740:
    call(r, 0x4ac910, 0);
    r->eax = 0x546744;
    r->edx = r->edi;
    r->ecx = rd32(r, r->ebp - 0x28);
    call(r, 0x4b5e70, 0);
    r->edi = rd32(r, r->ebp - 0x20);
    r->eax = rd32(r, r->ebp - 0x48);
    r->edx = rd32(r, r->ebp - 0x3c);
    r->edi = r->edi + 0x23;
    r->eax = r->eax + 1;
    r->edx = r->edx + 1;
    wr32(r, r->ebp - 0x20, r->edi);
    wr32(r, r->ebp - 0x48, r->eax);
    wr32(r, r->ebp - 0x3c, r->edx);
    if (r->edx < r->ecx && !r->port->env.failed)
    {
        goto at_46f570;
    }
at_46f773:
    r->esi = rd32(r, r->ebp - 0x38);
    r->edi = rd32(r, r->ebp - 0x6c);
    r->eax = rd32(r, r->ebp - 0x54);
    r->edx = rd32(r, r->ebp - 0x24);
    r->esi = r->esi + 0x32;
    r->edi = r->edi + 0x4;
    r->eax = r->eax + 1;
    r->ecx = rd32(r, r->edx + 0x53bd0c);
    wr32(r, r->ebp - 0x38, r->esi);
    wr32(r, r->ebp - 0x6c, r->edi);
    wr32(r, r->ebp - 0x54, r->eax);
    if (r->eax < r->ecx && !r->port->env.failed)
    {
        goto at_46f502;
    }
at_46f79d:
    r->edi = 0;
at_46f79f:
    r->eax = 0x15c;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_46f7b2;
    }
    call(r, 0x4abd70, 0);
at_46f7b2:
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
    r->edx = 0x280;
    r->eax = 0x598d30;
    call(r, 0x4826c0, 0);
    r->edx = 0x1e0;
    wr16(r, r->esi + 0xe, (r->eax & 0xffff));
    r->eax = 0x598d30;
    call(r, 0x4826c0, 0);
    r->edx = 0x544c48;
    wr16(r, r->esi + 0x16, (r->eax & 0xffff));
    r->eax = r->esi;
    call(r, 0x4ac8d0, 0);
    r->eax = r->esi;
    r->edx = 0;
    call(r, 0x4ac710, 0);
    r->eax = r->esi;
    r->edx = 0x3;
    call(r, 0x4ac8a0, 0);
    r->eax = 0x598d30;
    call(r, 0x4826c0, 0);
    r->edx = 0;
    set_low16(&r->edx, (r->eax & 0xffff));
    r->edx = r->edx + 1;
    r->eax = r->esi;
    call(r, 0x4ac7b0, 0);
    r->edx = 0xa;
    r->eax = 0x598d30;
    call(r, 0x4826c0, 0);
    r->edx = 0;
    set_low16(&r->edx, (r->eax & 0xffff));
    r->edx = r->edx + 0x2;
    r->eax = r->esi;
    call(r, 0x4ac470, 0);
    wr32(r, r->esi + 0xc4, 0x3e8);
    r->eax = r->esi;
    wr32(r, r->esi + 0xc8, 0x3e8);
    call(r, 0x4ac7e0, 0);
    wr8(r, r->esi + 0x93, 0x1);
    r->edi = r->edi + 1;
    wr8(r, r->esi + 0x4e, 0x0);
    r->edx = 0x4597e0;
    wr32(r, r->esi + 0x58, 0x0);
    r->eax = r->esi;
    wr32(r, r->esi + 0x5c, 0x1);
    call(r, 0x4ac8f0, 0);
    r->eax = 0x546744;
    r->edx = r->esi;
    wr8(r, r->esi + 0x95, 0x4);
    call(r, 0x4b5e70, 0);
    if (r->edi < 0x50 && !r->port->env.failed)
    {
        goto at_46f79f;
    }
    r->eax = rd32(r, r->ebp - 0x30);
    if (r->eax == 0x7)
    {
        goto at_46f8b5;
    }
    if (r->eax != 0x8)
    {
        goto at_46fa82;
    }
at_46f8b5:
    r->eax = 0x15c;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_46f8db;
    }
    r->ecx = 0x2;
    r->ebx = 0x1;
    wr32(r, r->ebp - 0x50, r->eax);
    wr32(r, r->ebp - 0x7c, r->ecx);
    call(r, 0x4abd70, 0);
    wr32(r, r->ebp - 0x7c, r->ebx);
at_46f8db:
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
    r->edx = 0x5464e4;
    wr16(r, r->edi + 0xe, 0x14);
    r->eax = r->edi;
    wr16(r, r->edi + 0x16, 0x14);
    call(r, 0x4ac8d0, 0);
    r->eax = rd32(r, r->ebp - 0x30);
    r->esi = r->edi;
    if (r->eax != 0x7)
    {
        goto at_470935;
    }
    wr32(r, r->edi + 0x64, 0x0);
    wr32(r, r->edi + 0x68, 0x4);
at_46f928:
    r->eax = r->esi;
    r->edx = rd32(r, r->esi + 0x64);
    call(r, 0x4ac710, 0);
    r->eax = r->esi;
    r->edx = 0x1;
    call(r, 0x4ac8a0, 0);
    r->eax = r->esi;
    call(r, 0x4ac7b0, 0);
    r->edx = 0x1;
    r->eax = r->esi;
    call(r, 0x4ac470, 0);
    wr8(r, r->esi + 0x93, 0x0);
    wr8(r, r->esi + 0x4e, 0x64);
    r->edx = 0x459a30;
    wr16(r, r->esi + 0x50, 0x1);
    r->eax = r->esi;
    wr32(r, r->esi + 0x60, 0x1);
    call(r, 0x4ac8f0, 0);
    r->edx = 0x4599e0;
    r->eax = r->esi;
    wr8(r, r->esi + 0x95, 0x1);
    call(r, 0x4ac910, 0);
    r->eax = 0x546744;
    r->edx = r->esi;
    call(r, 0x4b5e70, 0);
    r->eax = 0x15c;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_46f9ba;
    }
    r->edx = 0x4;
    r->ecx = 0x1;
    wr32(r, r->ebp - 0x50, r->eax);
    wr32(r, r->ebp - 0x7c, r->edx);
    call(r, 0x4abd70, 0);
    wr32(r, r->ebp - 0x7c, r->ecx);
at_46f9ba:
    r->edi = r->eax;
    push(r, 0x0);
    push(r, 0x0);
    push(r, 0x0);
    r->eax = r->edi;
    push(r, 0x0);
    r->ecx = 0;
    r->ebx = 0;
    push(r, 0x0);
    r->edx = 0;
    r->esi = r->edi;
    call(r, 0x4adf20, 5);
    r->edx = 0x5464e4;
    r->ebx = rd32(r, r->ebp - 0x30);
    wr16(r, r->edi + 0xe, 0x14);
    r->eax = r->edi;
    wr16(r, r->edi + 0x16, 0x14);
    call(r, 0x4ac8d0, 0);
    if (r->ebx != 0x7)
    {
        goto at_470948;
    }
    wr32(r, r->edi + 0x64, 0x1);
    wr32(r, r->edi + 0x68, 0x4);
at_46fa07:
    r->eax = r->esi;
    r->edx = rd32(r, r->esi + 0x64);
    call(r, 0x4ac710, 0);
    r->eax = r->esi;
    r->edx = 0x1;
    call(r, 0x4ac8a0, 0);
    r->eax = r->esi;
    call(r, 0x4ac7b0, 0);
    r->edx = 0x2;
    r->eax = r->esi;
    call(r, 0x4ac470, 0);
    wr8(r, r->esi + 0x93, 0x1);
    wr8(r, r->esi + 0x4e, 0x0);
    r->edx = 0x459b00;
    wr16(r, r->esi + 0x50, 0x1);
    r->eax = r->esi;
    wr32(r, r->esi + 0x60, 0x1);
    call(r, 0x4ac8f0, 0);
    r->edx = 0x4599e0;
    r->eax = r->esi;
    wr8(r, r->esi + 0x95, 0x1);
    call(r, 0x4ac910, 0);
    r->eax = 0x546744;
    r->edx = r->esi;
    wr32(r, r->esi + 0x58, 0x0);
    r->esi = 0x1;
    call(r, 0x4b5e70, 0);
    wr32(r, r->ebp - 0x7c, r->esi);
at_46fa82:
    r->eax = r->ebp - 0x60;
    r->ecx = 0;
    r->edx = 0;
    wr32(r, r->ebp - 0x7c, r->ecx);
    call(r, 0x4ca210, 0);
    r->eax = rd32(r, r->ebp - 0x88);
    wr32(r, r->ebp - 0x7c, r->ecx);
    r->port->env.chain = r->eax;
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_46faaa:
    call(r, 0x4abd70, 0);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_46f582;
at_46fab4:
    if (r->eax == 0x1)
    {
        goto at_46fae5;
    }
    if (r->eax == 0x2)
    {
        goto at_46fb03;
    }
    if (r->eax != 0x3 && !r->port->env.failed)
    {
        goto at_46f648;
    }
    r->edx = 0x1e0;
    r->eax = 0x598d30;
    wr16(r, r->edi + 0xe, 0x2b2);
    call(r, 0x4826c0, 0);
    wr16(r, r->edi + 0x16, (r->eax & 0xffff));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_46f648;
at_46fae5:
    r->edx = 0x1e0;
    r->eax = 0x598d30;
    wr16(r, r->edi + 0xe, 0xffce);
    call(r, 0x4826c0, 0);
    wr16(r, r->edi + 0x16, (r->eax & 0xffff));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_46f648;
at_46fb03:
    r->edx = 0x280;
    r->eax = 0x598d30;
    call(r, 0x4826c0, 0);
    wr16(r, r->edi + 0x16, 0x212);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_46f644;
at_46fb1d:
    if (r->ebx == 0x1)
    {
        goto at_46fd15;
    }
    if (r->ebx == 0x2)
    {
        goto at_46fe6e;
    }
    if (r->ebx == 0x3)
    {
        goto at_46ff87;
    }
    if (r->ebx == 0x4)
    {
        goto at_470077;
    }
    if (r->ebx == 0x5)
    {
        goto at_4701f0;
    }
    if (r->ebx == 0x6)
    {
        goto at_470318;
    }
    if (r->ebx == 0x7)
    {
        goto at_470464;
    }
    if (r->ebx == 0x8)
    {
        goto at_470522;
    }
    if (r->ebx == 0x9)
    {
        goto at_47061b;
    }
    if (r->ebx == 0xa)
    {
        goto at_4706de;
    }
    if (r->ebx == 0xb)
    {
        goto at_4707f5;
    }
    if (r->ebx != 0xc && !r->port->env.failed)
    {
        goto at_46f72e;
    }
    push(r, 0x0);
    push(r, 0x458880);
    push(r, 0x0);
    push(r, 0x0);
    r->eax = r->esi;
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = 0;
    r->edx = 0;
    call(r, 0x4adf20, 5);
    r->eax = rd32(r, r->ebp - 0x60);
    r->eax = r->eax + rd32(r, r->ebp - 0x3c);
    set_low8(&r->eax, rd8(r, r->eax));
    r->eax = r->eax & 0xff;
    r->edx = 0x2;
    wr32(r, r->esi + 0x58, r->eax);
    r->eax = 0x598d30;
    call(r, 0x4826c0, 0);
    r->eax = r->eax & 0xffff;
    wr32(r, r->esi + 0x64, r->eax);
    r->edx = 0;
    r->eax = rd32(r, r->esi + 0x61);
    set_low8(&r->edx, rd8(r, r->esi + 0x58));
    r->eax = (uint32_t)((int32_t)r->eax >> 0x18);
    call(r, 0x43f420, 0);
    r->edx = r->eax;
    r->eax = r->esi;
    call(r, 0x4ac950, 0);
    r->edx = 0xd;
    r->eax = 0x598d30;
    call(r, 0x4826c0, 0);
    wr8(r, r->esi + 0x52, (r->eax & 0xff));
    r->eax = rd32(r, r->ebp - 0x20);
    wr16(r, r->esi + 0x8, (r->eax & 0xffff));
    r->eax = rd32(r, r->ebp - 0x38);
    r->ecx = 0x140;
    wr16(r, r->esi + 0xa, (r->eax & 0xffff));
    r->eax = rd32(r, r->ebp - 0x20);
    wr32(r, r->ebp - 0x64, r->ecx);
    wr16(r, r->esi + 0x10, (r->eax & 0xffff));
    r->eax = rd32(r, r->ebp - 0x38);
    r->ebx = rd32(r, r->esi + 0x6);
    wr16(r, r->esi + 0x18, (r->eax & 0xffff));
    r->eax = 0xf0;
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    r->ecx = rd32(r, r->esi + 0x8);
    wr32(r, r->ebp - 0x74, r->eax);
    r->eax = rd32(r, r->ebp - 0x66);
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->edx = rd32(r, r->ebp - 0x74);
    wr32(r, r->ebp - 0x70, r->eax);
    call(r, 0x484680, 0);
    r->ecx = rd32(r, r->ebp - 0x74);
    wr32(r, r->ebp - 0x4c, r->eax);
    r->ebx = rd32(r, r->ebp - 0x70);
    r->edx = rd32(r, r->ebp - 0x4e);
    r->eax = r->esi;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    call(r, 0x4ad510, 0);
    r->edx = rd32(r, r->ebp - 0x74);
    r->eax = rd32(r, r->ebp - 0x70);
    r->ecx = rd32(r, r->esi + 0x8);
    r->ebx = rd32(r, r->esi + 0x6);
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    call(r, 0x484700, 0);
    r->edx = 0;
    r->ecx = 0x168;
    set_low16(&r->edx, (r->eax & 0xffff));
    wr16(r, r->esi + 0x24, (r->eax & 0xffff));
    r->eax = r->edx;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    idiv32(r, r->ecx);
    wr16(r, r->esi + 0x24, (r->edx & 0xffff));
    r->eax = rd32(r, r->ebp - 0x4c);
    wr16(r, r->esi + 0x28, 0x0);
    r->ebx = r->ebp - 0x1c;
    wr16(r, r->esi + 0x2a, 0x240);
    r->edx = r->ebp - 0x18;
    wr16(r, r->esi + 0x30, (r->eax & 0xffff));
    r->eax = r->esi;
    wr16(r, r->esi + 0x32, 0x50);
    call(r, 0x4ad260, 0);
    wr32(r, r->esi + 0x70, 0x0);
    r->edx = 0xa;
    wr32(r, r->esi + 0x74, 0x6);
    r->eax = r->esi;
    wr32(r, r->esi + 0x78, 0x1);
    call(r, 0x4ac7d0, 0);
    wr32(r, r->esi + 0xd4, 0x64);
    r->eax = r->esi;
    wr32(r, r->esi + 0xd8, 0x64);
    call(r, 0x4ac810, 0);
    wr16(r, r->esi + 0xc, 0x0);
    r->eax = rd32(r, r->ebp - 0x18);
    wr16(r, r->esi + 0xe, (r->eax & 0xffff));
    r->eax = rd32(r, r->ebp - 0x1c);
    wr16(r, r->esi + 0x16, (r->eax & 0xffff));
    r->eax = rd32(r, r->ebp - 0x18);
    wr16(r, r->esi + 0x8, (r->eax & 0xffff));
    r->eax = rd32(r, r->ebp - 0x1c);
    wr16(r, r->esi + 0xa, (r->eax & 0xffff));
    r->eax = r->esi;
    call(r, 0x4ac510, 0);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_46f72e;
at_46fd15:
    push(r, 0x0);
    r->eax = 0x458150;
    push(r, r->eax);
    push(r, 0x0);
    push(r, 0x0);
    r->ecx = 0;
    r->ebx = 0;
    push(r, 0x0);
    r->edx = 0;
    r->eax = r->esi;
    call(r, 0x4adf20, 5);
    r->eax = rd32(r, r->ebp - 0x3c);
    r->eax = r->eax + rd32(r, r->ebp - 0x60);
    set_low8(&r->eax, rd8(r, r->eax));
    r->eax = r->eax & 0xff;
    r->edx = 0x2;
    wr32(r, r->esi + 0x58, r->eax);
    r->eax = 0x598d30;
    call(r, 0x4826c0, 0);
    r->eax = r->eax & 0xffff;
    wr32(r, r->esi + 0x64, r->eax);
    r->edx = 0;
    r->eax = rd32(r, r->esi + 0x61);
    set_low8(&r->edx, rd8(r, r->esi + 0x58));
    r->eax = (uint32_t)((int32_t)r->eax >> 0x18);
    call(r, 0x43f420, 0);
    r->edx = r->eax;
    r->eax = r->esi;
    call(r, 0x4ac950, 0);
    r->eax = rd32(r, r->ebp - 0x20);
    wr32(r, r->esi + 0xd4, 0x64);
    wr16(r, r->esi + 0x8, (r->eax & 0xffff));
    r->eax = rd32(r, r->ebp - 0x38);
    r->edx = 0x2;
    wr16(r, r->esi + 0xa, (r->eax & 0xffff));
    r->eax = r->esi;
    wr32(r, r->esi + 0xd8, 0x64);
    call(r, 0x4ac810, 0);
    r->eax = 0x598d30;
    wr16(r, r->esi + 0xc, 0x0);
    call(r, 0x4826c0, 0);
    r->eax = r->eax & 0xffff;
    if (r->eax != 0)
    {
        goto at_46fe57;
    }
    r->eax = rd32(r, r->ebp - 0x38);
    wr16(r, r->esi + 0xe, 0xffce);
at_46fdc2:
    wr16(r, r->esi + 0x16, (r->eax & 0xffff));
at_46fdc6:
    r->eax = rd32(r, r->ebp - 0x20);
    wr16(r, r->edi + 0x10, (r->eax & 0xffff));
    r->eax = rd32(r, r->ebp - 0x38);
    wr16(r, r->edi + 0x18, (r->eax & 0xffff));
    set_low16(&r->eax, rd16(r, r->edi + 0xe));
    wr16(r, r->edi + 0x8, (r->eax & 0xffff));
    set_low16(&r->eax, rd16(r, r->edi + 0x16));
    wr16(r, r->edi + 0xa, (r->eax & 0xffff));
    r->edx = rd32(r, r->edi + 0x6);
    r->eax = rd32(r, r->edi + 0xe);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    wr16(r, r->edi + 0x12, 0x1);
    r->eax = r->eax - r->edx;
    wr16(r, r->edi + 0x1a, 0x1);
    r->edx = (int32_t)r->eax < 0 ? 0xffffffffu : 0;
    r->eax = r->eax ^ r->edx;
    r->eax = r->eax - r->edx;
    r->esi = r->eax;
    r->ebx = r->eax;
    r->edx = rd32(r, r->edi + 0x8);
    r->eax = rd32(r, r->edi + 0x16);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->eax = r->eax - r->edx;
    r->edx = (int32_t)r->eax < 0 ? 0xffffffffu : 0;
    r->eax = r->eax ^ r->edx;
    r->eax = r->eax - r->edx;
    r->ecx = r->eax;
    if ((int32_t)r->esi <= (int32_t)0x280)
    {
        goto at_46fe29;
    }
    r->ebx = 0x280;
at_46fe29:
    if ((int32_t)r->ecx <= (int32_t)0x1e0)
    {
        goto at_46fe36;
    }
    r->ecx = 0x1e0;
at_46fe36:
    r->edx = r->ebx * 0xa;
    r->ebx = 0x280;
    r->eax = r->edx;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    idiv32(r, r->ebx);
    r->edx = r->ecx * 0xa;
    r->eax = r->eax + 1;
    wr16(r, r->edi + 0x12, (r->eax & 0xffff));
    r->ecx = 0x1e0;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_46f6d8;
at_46fe57:
    if (r->eax != 0x1 && !r->port->env.failed)
    {
        goto at_46fdc6;
    }
    r->eax = rd32(r, r->ebp - 0x38);
    wr16(r, r->esi + 0xe, 0x2b2);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_46fdc2;
at_46fe6e:
    push(r, 0x0);
    r->eax = 0x458150;
    push(r, r->eax);
    push(r, 0x0);
    push(r, 0x0);
    r->ecx = 0;
    r->ebx = 0;
    push(r, 0x0);
    r->edx = 0;
    r->eax = r->esi;
    call(r, 0x4adf20, 5);
    r->eax = rd32(r, r->ebp - 0x3c);
    r->eax = r->eax + rd32(r, r->ebp - 0x60);
    set_low8(&r->eax, rd8(r, r->eax));
    r->eax = r->eax & 0xff;
    r->edx = 0x2;
    wr32(r, r->esi + 0x58, r->eax);
    r->eax = 0x598d30;
    call(r, 0x4826c0, 0);
    r->eax = r->eax & 0xffff;
    wr32(r, r->esi + 0x64, r->eax);
    r->edx = 0;
    r->eax = rd32(r, r->esi + 0x61);
    set_low8(&r->edx, rd8(r, r->esi + 0x58));
    r->eax = (uint32_t)((int32_t)r->eax >> 0x18);
    call(r, 0x43f420, 0);
    r->edx = r->eax;
    r->eax = r->esi;
    call(r, 0x4ac950, 0);
    r->eax = rd32(r, r->ebp - 0x20);
    wr32(r, r->esi + 0xd4, 0x64);
    wr16(r, r->esi + 0x8, (r->eax & 0xffff));
    r->eax = rd32(r, r->ebp - 0x38);
    wr16(r, r->esi + 0xa, (r->eax & 0xffff));
    r->eax = r->esi;
    wr32(r, r->esi + 0xd8, 0x64);
    call(r, 0x4ac810, 0);
    wr16(r, r->esi + 0xc, 0x0);
    wr16(r, r->esi + 0x16, 0x212);
    wr16(r, r->esi + 0x12, 0x1);
    wr16(r, r->esi + 0x1a, 0x1);
    r->eax = rd32(r, r->ebp - 0x20);
    wr16(r, r->esi + 0x12, 0x8);
    wr16(r, r->esi + 0xe, (r->eax & 0xffff));
    wr16(r, r->esi + 0x10, (r->eax & 0xffff));
    r->eax = rd32(r, r->ebp - 0x38);
    wr16(r, r->esi + 0x18, (r->eax & 0xffff));
    set_low16(&r->eax, rd16(r, r->esi + 0xe));
    wr16(r, r->esi + 0x8, (r->eax & 0xffff));
    set_low16(&r->eax, rd16(r, r->esi + 0x16));
    r->edx = 0xa;
    wr16(r, r->esi + 0xa, (r->eax & 0xffff));
    r->eax = r->esi;
    wr16(r, r->esi + 0x1a, 0x8);
    call(r, 0x4ac7d0, 0);
    wr8(r, r->esi + 0x95, 0x4);
    wr8(r, r->esi + 0x93, 0x1);
    r->edx = 0x5;
    wr8(r, r->esi + 0x44, 0x0);
    r->eax = 0x598d30;
    wr32(r, r->esi + 0x80, 0x0);
    call(r, 0x4826c0, 0);
    r->eax = r->eax & 0xffff;
    wr8(r, r->esi + 0x8c, 0x0);
    r->eax = r->eax + 1;
    wr32(r, r->esi + 0x88, r->eax);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_46f72e;
at_46ff87:
    push(r, 0x0);
    r->eax = 0x458150;
    push(r, r->eax);
    push(r, 0x0);
    push(r, 0x0);
    r->ecx = 0;
    r->ebx = 0;
    push(r, 0x0);
    r->edx = 0;
    r->eax = r->esi;
    call(r, 0x4adf20, 5);
    r->eax = rd32(r, r->ebp - 0x3c);
    r->eax = r->eax + rd32(r, r->ebp - 0x60);
    set_low8(&r->eax, rd8(r, r->eax));
    r->eax = r->eax & 0xff;
    r->edx = 0x2;
    wr32(r, r->esi + 0x58, r->eax);
    r->eax = 0x598d30;
    call(r, 0x4826c0, 0);
    r->eax = r->eax & 0xffff;
    wr32(r, r->esi + 0x64, r->eax);
    r->edx = 0;
    r->eax = rd32(r, r->esi + 0x61);
    set_low8(&r->edx, rd8(r, r->esi + 0x58));
    r->eax = (uint32_t)((int32_t)r->eax >> 0x18);
    call(r, 0x43f420, 0);
    r->edx = r->eax;
    r->eax = r->esi;
    call(r, 0x4ac950, 0);
    r->eax = rd32(r, r->ebp - 0x20);
    wr32(r, r->esi + 0xd4, 0x64);
    wr16(r, r->esi + 0x8, (r->eax & 0xffff));
    r->eax = rd32(r, r->ebp - 0x38);
    wr16(r, r->esi + 0xa, (r->eax & 0xffff));
    r->eax = r->esi;
    wr32(r, r->esi + 0xd8, 0x64);
    call(r, 0x4ac810, 0);
    r->eax = rd32(r, r->ebp - 0x68);
    wr16(r, r->esi + 0xc, 0x0);
    if (r->eax != 0)
    {
        goto at_470067;
    }
    r->eax = rd32(r, r->ebp - 0x38);
    wr16(r, r->esi + 0xe, 0xffce);
at_470021:
    wr16(r, r->esi + 0x16, (r->eax & 0xffff));
at_470025:
    wr16(r, r->edi + 0x12, 0x1);
    wr16(r, r->edi + 0x1a, 0x1);
    r->eax = rd32(r, r->ebp - 0x20);
    wr16(r, r->edi + 0x12, 0x6);
    wr16(r, r->edi + 0x10, (r->eax & 0xffff));
    r->eax = rd32(r, r->ebp - 0x38);
    wr16(r, r->edi + 0x18, (r->eax & 0xffff));
    set_low16(&r->eax, rd16(r, r->edi + 0xe));
    wr16(r, r->edi + 0x8, (r->eax & 0xffff));
    set_low16(&r->eax, rd16(r, r->edi + 0x16));
    r->edx = 0xa;
    wr16(r, r->edi + 0xa, (r->eax & 0xffff));
    r->eax = r->edi;
    wr16(r, r->edi + 0x1a, 0x6);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_46f6eb;
at_470067:
    if (r->eax != 0x1 && !r->port->env.failed)
    {
        goto at_470025;
    }
    r->eax = rd32(r, r->ebp - 0x38);
    wr16(r, r->esi + 0xe, 0x2b2);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_470021;
at_470077:
    push(r, 0x0);
    push(r, 0x458150);
    push(r, 0x0);
    push(r, 0x0);
    r->eax = r->esi;
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = 0;
    r->edx = 0;
    call(r, 0x4adf20, 5);
    r->eax = rd32(r, r->ebp - 0x60);
    r->eax = r->eax + rd32(r, r->ebp - 0x3c);
    set_low8(&r->eax, rd8(r, r->eax));
    r->eax = r->eax & 0xff;
    r->edx = 0x2;
    wr32(r, r->esi + 0x58, r->eax);
    r->eax = 0x598d30;
    call(r, 0x4826c0, 0);
    r->eax = r->eax & 0xffff;
    wr32(r, r->esi + 0x64, r->eax);
    r->edx = 0;
    r->eax = rd32(r, r->esi + 0x61);
    set_low8(&r->edx, rd8(r, r->esi + 0x58));
    r->eax = (uint32_t)((int32_t)r->eax >> 0x18);
    call(r, 0x43f420, 0);
    r->edx = r->eax;
    r->eax = r->esi;
    call(r, 0x4ac950, 0);
    r->eax = rd32(r, r->ebp - 0x20);
    wr32(r, r->esi + 0xd4, 0x64);
    wr16(r, r->esi + 0x8, (r->eax & 0xffff));
    r->eax = rd32(r, r->ebp - 0x38);
    wr16(r, r->esi + 0xa, (r->eax & 0xffff));
    r->eax = r->esi;
    wr32(r, r->esi + 0xd8, 0x64);
    call(r, 0x4ac810, 0);
    r->eax = rd32(r, r->ebp - 0x20);
    wr16(r, r->esi + 0xe, (r->eax & 0xffff));
    r->eax = rd32(r, r->ebp - 0x38);
    wr16(r, r->esi + 0x16, (r->eax & 0xffff));
    r->eax = rd32(r, r->ebp - 0x44);
    wr16(r, r->esi + 0xc, 0x0);
    r->eax = r->eax & 0x3;
    if (r->eax != 0)
    {
        goto at_4701ad;
    }
    r->eax = rd32(r, r->ebp - 0x38);
    r->eax = r->eax - 0x212;
at_470123:
    wr16(r, r->esi + 0x16, (r->eax & 0xffff));
at_470127:
    wr16(r, r->edi + 0x12, 0x1);
    wr16(r, r->edi + 0x1a, 0x1);
    r->eax = rd32(r, r->ebp - 0x20);
    wr16(r, r->edi + 0x12, 0x8);
    wr16(r, r->edi + 0x10, (r->eax & 0xffff));
    r->eax = rd32(r, r->ebp - 0x38);
    wr16(r, r->edi + 0x18, (r->eax & 0xffff));
    set_low16(&r->eax, rd16(r, r->edi + 0xe));
    wr16(r, r->edi + 0x8, (r->eax & 0xffff));
    set_low16(&r->eax, rd16(r, r->edi + 0x16));
    r->edx = 0xa;
    wr16(r, r->edi + 0xa, (r->eax & 0xffff));
    r->eax = r->edi;
    wr16(r, r->edi + 0x1a, 0x8);
    call(r, 0x4ac7d0, 0);
    wr8(r, r->edi + 0x95, 0x4);
    wr8(r, r->edi + 0x93, 0x1);
    r->edx = 0x5;
    wr8(r, r->edi + 0x44, 0x0);
    r->eax = 0x598d30;
    wr32(r, r->edi + 0x80, 0x0);
    call(r, 0x4826c0, 0);
    r->esi = rd32(r, r->ebp - 0x44);
    r->eax = r->eax & 0xffff;
    wr8(r, r->edi + 0x8c, 0x0);
    r->esi = r->esi + 1;
    r->eax = r->eax + 1;
    wr32(r, r->ebp - 0x44, r->esi);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_46f728;
at_4701ad:
    if (r->eax != 0x1)
    {
        goto at_4701c4;
    }
    r->eax = rd32(r, r->ebp - 0x20);
    r->eax = r->eax - 0x2b2;
    wr16(r, r->esi + 0xe, (r->eax & 0xffff));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_470127;
at_4701c4:
    if (r->eax != 0x2)
    {
        goto at_4701d6;
    }
    r->eax = rd32(r, r->ebp - 0x38);
    r->eax = r->eax + 0x212;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_470123;
at_4701d6:
    if (r->eax != 0x3 && !r->port->env.failed)
    {
        goto at_470127;
    }
    r->eax = rd32(r, r->ebp - 0x20);
    r->eax = r->eax + 0x2b2;
    wr16(r, r->esi + 0xe, (r->eax & 0xffff));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_470127;
at_4701f0:
    push(r, 0x0);
    push(r, 0x4585c0);
    push(r, 0x0);
    push(r, 0x0);
    r->eax = r->esi;
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = 0;
    r->edx = 0;
    call(r, 0x4adf20, 5);
    r->eax = rd32(r, r->ebp - 0x60);
    r->eax = r->eax + rd32(r, r->ebp - 0x3c);
    set_low8(&r->eax, rd8(r, r->eax));
    r->eax = r->eax & 0xff;
    r->edx = 0x2;
    wr32(r, r->esi + 0x58, r->eax);
    r->eax = 0x598d30;
    call(r, 0x4826c0, 0);
    r->eax = r->eax & 0xffff;
    wr32(r, r->esi + 0x64, r->eax);
    r->edx = 0;
    r->eax = rd32(r, r->esi + 0x61);
    set_low8(&r->edx, rd8(r, r->esi + 0x58));
    r->eax = (uint32_t)((int32_t)r->eax >> 0x18);
    call(r, 0x43f420, 0);
    r->edx = r->eax;
    r->eax = r->esi;
    call(r, 0x4ac950, 0);
    r->eax = rd32(r, r->ebp - 0x20);
    wr32(r, r->esi + 0xd4, 0x64);
    wr16(r, r->esi + 0x8, (r->eax & 0xffff));
    r->eax = rd32(r, r->ebp - 0x38);
    r->edx = 0xa0;
    wr16(r, r->esi + 0xa, (r->eax & 0xffff));
    r->eax = r->esi;
    wr32(r, r->esi + 0xd8, 0x64);
    call(r, 0x4ac810, 0);
    r->eax = rd32(r, r->ebp - 0x20);
    r->ecx = rd32(r, r->esi + 0x8);
    r->ebx = rd32(r, r->esi + 0x6);
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    wr16(r, r->esi + 0xe, (r->eax & 0xffff));
    r->eax = rd32(r, r->ebp - 0x38);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    wr16(r, r->esi + 0x16, (r->eax & 0xffff));
    r->eax = r->esi;
    wr16(r, r->esi + 0xc, 0x0);
    call(r, 0x4ad510, 0);
    r->edx = 0x8;
    wr16(r, r->esi + 0x30, 0xa0);
    r->eax = 0x598d30;
    wr16(r, r->esi + 0x24, 0x0);
    call(r, 0x4826c0, 0);
    wr32(r, r->esi + 0x70, 0x0);
    wr32(r, r->esi + 0x74, 0x1);
    r->eax = r->eax + 0x3;
    wr32(r, r->esi + 0x78, 0x1);
    r->edx = 0xa;
    wr16(r, r->esi + 0x28, (r->eax & 0xffff));
    r->eax = r->esi;
    wr16(r, r->esi + 0x32, 0x1);
    call(r, 0x4ac7d0, 0);
    r->eax = r->esi;
    call(r, 0x4ac510, 0);
    wr16(r, r->esi + 0x48, 0x96);
    r->edx = 0xa;
    wr16(r, r->esi + 0x4a, 0x0);
    r->eax = r->esi;
    wr16(r, r->esi + 0x4c, 0x1);
    call(r, 0x4ac7d0, 0);
    wr8(r, r->esi + 0x44, 0x0);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_46f72e;
at_470318:
    push(r, 0x0);
    push(r, 0x4585c0);
    push(r, 0x0);
    push(r, 0x0);
    r->eax = r->esi;
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = 0;
    r->edx = 0;
    call(r, 0x4adf20, 5);
    r->eax = rd32(r, r->ebp - 0x60);
    r->eax = r->eax + rd32(r, r->ebp - 0x3c);
    set_low8(&r->eax, rd8(r, r->eax));
    r->eax = r->eax & 0xff;
    r->edx = 0x2;
    wr32(r, r->esi + 0x58, r->eax);
    r->eax = 0x598d30;
    call(r, 0x4826c0, 0);
    r->eax = r->eax & 0xffff;
    wr32(r, r->esi + 0x64, r->eax);
    r->edx = 0;
    r->eax = rd32(r, r->esi + 0x61);
    set_low8(&r->edx, rd8(r, r->esi + 0x58));
    r->eax = (uint32_t)((int32_t)r->eax >> 0x18);
    call(r, 0x43f420, 0);
    r->edx = r->eax;
    r->eax = r->esi;
    call(r, 0x4ac950, 0);
    r->eax = rd32(r, r->ebp - 0x20);
    wr32(r, r->esi + 0xd4, 0x64);
    wr16(r, r->esi + 0x8, (r->eax & 0xffff));
    r->eax = rd32(r, r->ebp - 0x38);
    r->edx = 0xa0;
    wr16(r, r->esi + 0xa, (r->eax & 0xffff));
    r->eax = r->esi;
    wr32(r, r->esi + 0xd8, 0x64);
    call(r, 0x4ac810, 0);
    r->eax = rd32(r, r->ebp - 0x20);
    r->ecx = rd32(r, r->esi + 0x8);
    r->ebx = rd32(r, r->esi + 0x6);
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    wr16(r, r->esi + 0xe, (r->eax & 0xffff));
    r->eax = rd32(r, r->ebp - 0x38);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    wr16(r, r->esi + 0x16, (r->eax & 0xffff));
    r->eax = r->esi;
    wr16(r, r->esi + 0xc, 0x0);
    call(r, 0x4ad510, 0);
    r->edx = 0x8;
    wr16(r, r->esi + 0x30, 0xa0);
    r->eax = 0x598d30;
    wr16(r, r->esi + 0x24, 0x0);
    call(r, 0x4826c0, 0);
    r->eax = r->eax + 0x3;
    r->edx = 0x2;
    wr16(r, r->esi + 0x28, (r->eax & 0xffff));
    r->eax = 0x598d30;
    call(r, 0x4826c0, 0);
    if ((uint16_t)((r->eax & 0xffff)) != 0)
    {
        goto at_47040f;
    }
    set_low16(&r->edx, rd16(r, r->esi + 0x28));
    wr16(r, r->esi + 0x24, 0xb4);
    r->edx = 0u - r->edx;
    wr16(r, r->esi + 0x28, (r->edx & 0xffff));
at_47040f:
    wr32(r, r->edi + 0x70, 0x0);
    wr32(r, r->edi + 0x74, 0x1);
    r->edx = 0xa;
    wr32(r, r->edi + 0x78, 0x1);
    r->eax = r->edi;
    wr16(r, r->edi + 0x32, 0x1);
    call(r, 0x4ac7d0, 0);
    r->eax = r->edi;
    call(r, 0x4ac510, 0);
    wr16(r, r->edi + 0x48, 0x96);
    r->edx = 0xa;
    wr16(r, r->edi + 0x4a, 0x0);
    r->eax = r->edi;
    wr16(r, r->edi + 0x4c, 0x1);
    call(r, 0x4ac7d0, 0);
    wr8(r, r->edi + 0x44, 0x0);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_46f72e;
at_470464:
    push(r, 0x0);
    push(r, 0x458710);
    push(r, 0x0);
    push(r, 0x0);
    r->eax = r->esi;
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = 0;
    r->edx = 0;
    call(r, 0x4adf20, 5);
    r->eax = rd32(r, r->ebp - 0x60);
    r->eax = r->eax + rd32(r, r->ebp - 0x3c);
    set_low8(&r->eax, rd8(r, r->eax));
    r->eax = r->eax & 0xff;
    r->edx = 0x2;
    wr32(r, r->esi + 0x58, r->eax);
    r->eax = 0x598d30;
    call(r, 0x4826c0, 0);
    r->eax = r->eax & 0xffff;
    wr32(r, r->esi + 0x64, r->eax);
    r->edx = 0;
    r->eax = rd32(r, r->esi + 0x61);
    set_low8(&r->edx, rd8(r, r->esi + 0x58));
    r->eax = (uint32_t)((int32_t)r->eax >> 0x18);
    call(r, 0x43f420, 0);
    r->edx = r->eax;
    r->eax = r->esi;
    call(r, 0x4ac950, 0);
    r->eax = rd32(r, r->ebp - 0x20);
    wr32(r, r->esi + 0xd4, 0x64);
    wr16(r, r->esi + 0x8, (r->eax & 0xffff));
    r->eax = rd32(r, r->ebp - 0x38);
    r->edx = 0x28;
    wr16(r, r->esi + 0xa, (r->eax & 0xffff));
    r->eax = r->esi;
    wr32(r, r->esi + 0xd8, 0x64);
    call(r, 0x4ac810, 0);
    r->eax = r->esi;
    wr16(r, r->esi + 0xc, 0x0);
    call(r, 0x4ac7d0, 0);
    r->edx = rd32(r, r->ebp - 0x44);
    r->edx = r->edx + r->edx;
    r->eax = r->esi;
    r->edx = r->edx + 0xa;
    r->ebx = rd32(r, r->ebp - 0x44);
    call(r, 0x4ac7d0, 0);
    wr8(r, r->esi + 0x44, 0x0);
    r->ebx = r->ebx + 1;
    wr8(r, r->esi + 0x45, 0x10);
    wr32(r, r->ebp - 0x44, r->ebx);
    wr16(r, r->esi + 0x46, 0x1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_46f72e;
at_470522:
    push(r, 0x0);
    push(r, 0x458150);
    push(r, 0x0);
    push(r, 0x0);
    r->eax = r->esi;
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = 0;
    r->edx = 0;
    call(r, 0x4adf20, 5);
    r->eax = rd32(r, r->ebp - 0x60);
    r->ebx = rd32(r, r->ebp - 0x3c);
    r->eax = r->eax + r->ebx;
    set_low8(&r->eax, rd8(r, r->eax));
    r->eax = r->eax & 0xff;
    r->edx = 0x2;
    wr32(r, r->esi + 0x58, r->eax);
    r->eax = 0x598d30;
    call(r, 0x4826c0, 0);
    r->eax = r->eax & 0xffff;
    wr32(r, r->esi + 0x64, r->eax);
    r->edx = 0;
    r->eax = rd32(r, r->esi + 0x61);
    set_low8(&r->edx, rd8(r, r->esi + 0x58));
    r->eax = (uint32_t)((int32_t)r->eax >> 0x18);
    call(r, 0x43f420, 0);
    r->edx = r->eax;
    r->eax = r->esi;
    call(r, 0x4ac950, 0);
    r->eax = rd32(r, r->ebp - 0x20);
    wr32(r, r->esi + 0xd4, 0x64);
    wr16(r, r->esi + 0x8, (r->eax & 0xffff));
    r->eax = rd32(r, r->ebp - 0x38);
    wr16(r, r->esi + 0xa, (r->eax & 0xffff));
    r->eax = r->esi;
    wr32(r, r->esi + 0xd8, 0x64);
    call(r, 0x4ac810, 0);
    r->eax = rd32(r, r->ebp - 0x20);
    wr16(r, r->esi + 0xc, 0x0);
    wr16(r, r->esi + 0xe, (r->eax & 0xffff));
    r->eax = rd32(r, r->ebp - 0x38);
    r->edx = rd32(r, r->ebp - 0x34);
    wr16(r, r->esi + 0x16, (r->eax & 0xffff));
    if (r->ebx > r->edx)
    {
        goto at_470611;
    }
    r->eax = rd32(r, r->ebp - 0x20);
    r->eax = r->eax - 0x172;
at_4705cb:
    wr16(r, r->esi + 0xe, (r->eax & 0xffff));
    wr16(r, r->edi + 0x12, 0x1);
    wr16(r, r->edi + 0x1a, 0x1);
    r->eax = rd32(r, r->ebp - 0x20);
    wr16(r, r->edi + 0x12, 0x8);
    wr16(r, r->edi + 0x10, (r->eax & 0xffff));
    r->eax = rd32(r, r->ebp - 0x38);
    wr16(r, r->edi + 0x18, (r->eax & 0xffff));
    set_low16(&r->eax, rd16(r, r->edi + 0xe));
    wr16(r, r->edi + 0x8, (r->eax & 0xffff));
    set_low16(&r->eax, rd16(r, r->edi + 0x16));
    r->edx = 0xa;
    wr16(r, r->edi + 0xa, (r->eax & 0xffff));
    r->eax = r->edi;
    wr16(r, r->edi + 0x1a, 0x8);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_46f6eb;
at_470611:
    r->eax = rd32(r, r->ebp - 0x20);
    r->eax = r->eax + 0x172;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4705cb;
at_47061b:
    push(r, 0x0);
    push(r, 0x458710);
    push(r, 0x0);
    push(r, 0x0);
    r->eax = r->esi;
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = 0;
    r->edx = 0;
    call(r, 0x4adf20, 5);
    r->eax = rd32(r, r->ebp - 0x60);
    r->eax = r->eax + rd32(r, r->ebp - 0x3c);
    set_low8(&r->eax, rd8(r, r->eax));
    r->eax = r->eax & 0xff;
    r->edx = 0x2;
    wr32(r, r->esi + 0x58, r->eax);
    r->eax = 0x598d30;
    call(r, 0x4826c0, 0);
    r->eax = r->eax & 0xffff;
    wr32(r, r->esi + 0x64, r->eax);
    r->edx = 0;
    r->eax = rd32(r, r->esi + 0x61);
    set_low8(&r->edx, rd8(r, r->esi + 0x58));
    r->eax = (uint32_t)((int32_t)r->eax >> 0x18);
    call(r, 0x43f420, 0);
    r->edx = r->eax;
    r->eax = r->esi;
    call(r, 0x4ac950, 0);
    r->eax = rd32(r, r->ebp - 0x20);
    wr32(r, r->esi + 0xd4, 0x64);
    wr16(r, r->esi + 0x8, (r->eax & 0xffff));
    r->eax = rd32(r, r->ebp - 0x38);
    wr16(r, r->esi + 0xa, (r->eax & 0xffff));
    r->eax = r->esi;
    wr32(r, r->esi + 0xd8, 0x64);
    call(r, 0x4ac810, 0);
    r->eax = rd32(r, r->ebp - 0x48);
    wr16(r, r->esi + 0xc, 0x0);
    r->edx = (int32_t)r->eax < 0 ? 0xffffffffu : 0;
    r->eax = r->eax ^ r->edx;
    r->eax = r->eax - r->edx;
    r->edx = 0x28;
    r->ecx = r->eax;
    r->eax = r->esi;
    call(r, 0x4ac7d0, 0);
    r->edx = r->ecx * 8;
    r->eax = r->esi;
    r->edx = r->edx + 0xa;
    call(r, 0x4ac7d0, 0);
    wr8(r, r->esi + 0x44, 0x0);
    wr8(r, r->esi + 0x45, 0x10);
    wr16(r, r->esi + 0x46, 0x1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_46f72e;
at_4706de:
    push(r, 0x0);
    push(r, 0x4585c0);
    push(r, 0x0);
    push(r, 0x0);
    r->eax = r->esi;
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = 0;
    r->edx = 0;
    call(r, 0x4adf20, 5);
    r->eax = rd32(r, r->ebp - 0x60);
    r->eax = r->eax + rd32(r, r->ebp - 0x3c);
    set_low8(&r->eax, rd8(r, r->eax));
    r->eax = r->eax & 0xff;
    r->edx = 0x2;
    wr32(r, r->esi + 0x58, r->eax);
    r->eax = 0x598d30;
    call(r, 0x4826c0, 0);
    r->eax = r->eax & 0xffff;
    wr32(r, r->esi + 0x64, r->eax);
    r->edx = 0;
    r->eax = rd32(r, r->esi + 0x61);
    set_low8(&r->edx, rd8(r, r->esi + 0x58));
    r->eax = (uint32_t)((int32_t)r->eax >> 0x18);
    call(r, 0x43f420, 0);
    r->edx = r->eax;
    r->eax = r->esi;
    call(r, 0x4ac950, 0);
    r->eax = rd32(r, r->ebp - 0x20);
    wr32(r, r->esi + 0xd4, 0x64);
    wr16(r, r->esi + 0x8, (r->eax & 0xffff));
    r->eax = rd32(r, r->ebp - 0x38);
    r->edx = 0x140;
    wr16(r, r->esi + 0xa, (r->eax & 0xffff));
    r->eax = r->esi;
    wr32(r, r->esi + 0xd8, 0x64);
    call(r, 0x4ac810, 0);
    r->eax = rd32(r, r->ebp - 0x20);
    r->ecx = rd32(r, r->esi + 0x8);
    r->ebx = rd32(r, r->esi + 0x6);
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    wr16(r, r->esi + 0xe, (r->eax & 0xffff));
    r->eax = rd32(r, r->ebp - 0x38);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    wr16(r, r->esi + 0x16, (r->eax & 0xffff));
    r->eax = r->esi;
    wr16(r, r->esi + 0xc, 0x0);
    call(r, 0x4ad510, 0);
    r->edx = 0x168;
    r->eax = 0x598d30;
    wr16(r, r->esi + 0x30, 0x140);
    call(r, 0x4826c0, 0);
    wr16(r, r->esi + 0x28, 0x4);
    wr32(r, r->esi + 0x70, 0x0);
    wr32(r, r->esi + 0x74, 0x1);
    wr32(r, r->esi + 0x78, 0x1);
    r->edx = 0xa;
    wr16(r, r->esi + 0x24, (r->eax & 0xffff));
    r->eax = r->esi;
    wr16(r, r->esi + 0x32, 0x3);
    call(r, 0x4ac7d0, 0);
    r->eax = r->esi;
    call(r, 0x4ac510, 0);
    wr16(r, r->esi + 0x48, 0x96);
    wr16(r, r->esi + 0x4a, 0x0);
    wr16(r, r->esi + 0x4c, 0x1);
    wr8(r, r->esi + 0x44, 0x0);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_46f72e;
at_4707f5:
    push(r, 0x0);
    push(r, 0x4587a0);
    push(r, 0x0);
    push(r, 0x0);
    r->eax = r->esi;
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = 0;
    r->edx = 0;
    call(r, 0x4adf20, 5);
    r->eax = rd32(r, r->ebp - 0x60);
    r->eax = r->eax + rd32(r, r->ebp - 0x3c);
    set_low8(&r->eax, rd8(r, r->eax));
    r->eax = r->eax & 0xff;
    r->edx = 0x2;
    wr32(r, r->esi + 0x5c, r->eax);
    r->eax = 0x598d30;
    wr32(r, r->esi + 0x58, 0x20);
    call(r, 0x4826c0, 0);
    r->eax = r->eax & 0xffff;
    wr32(r, r->esi + 0x64, r->eax);
    r->edx = 0;
    r->eax = rd32(r, r->esi + 0x61);
    set_low8(&r->edx, rd8(r, r->esi + 0x58));
    r->eax = (uint32_t)((int32_t)r->eax >> 0x18);
    call(r, 0x43f420, 0);
    r->edx = r->eax;
    r->eax = r->esi;
    call(r, 0x4ac950, 0);
    r->eax = rd32(r, r->ebp - 0x20);
    wr32(r, r->esi + 0xd4, 0x64);
    wr16(r, r->esi + 0x8, (r->eax & 0xffff));
    r->eax = rd32(r, r->ebp - 0x38);
    wr16(r, r->esi + 0xa, (r->eax & 0xffff));
    r->eax = r->esi;
    wr32(r, r->esi + 0xd8, 0x64);
    call(r, 0x4ac810, 0);
    wr16(r, r->esi + 0xc, 0x0);
    wr32(r, r->esi + 0x70, 0x0);
    r->eax = rd32(r, r->ebp - 0x20);
    wr32(r, r->esi + 0x74, 0x32);
    wr16(r, r->esi + 0xe, (r->eax & 0xffff));
    r->eax = rd32(r, r->ebp - 0x38);
    r->edx = 0x14;
    wr16(r, r->esi + 0x16, (r->eax & 0xffff));
    r->eax = 0x598d30;
    wr32(r, r->esi + 0x78, 0x1);
    call(r, 0x4826c0, 0);
    r->edx = 0;
    set_low16(&r->edx, (r->eax & 0xffff));
    r->edx = r->edx + 0xa;
    r->eax = r->esi;
    call(r, 0x4ac7d0, 0);
    r->eax = r->esi;
    call(r, 0x4ac510, 0);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_46f72e;
at_4708d2:
    if (r->eax == 0x1)
    {
        goto at_4708fa;
    }
    if (r->eax == 0x2)
    {
        goto at_470904;
    }
    if (r->eax == 0x3)
    {
        goto at_47090e;
    }
    if (r->eax == 0x4)
    {
        goto at_470918;
    }
    if (r->eax == 0x5)
    {
        goto at_470922;
    }
    if (r->eax != 0x6)
    {
        goto at_47092c;
    }
    r->edx = 0x458490;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_46f73e;
at_4708fa:
    r->edx = 0x458410;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_46f73e;
at_470904:
    r->edx = 0x458d40;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_46f73e;
at_47090e:
    r->edx = 0x458f00;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_46f73e;
at_470918:
    r->edx = 0x4590a0;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_46f73e;
at_470922:
    r->edx = 0x459200;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_46f73e;
at_47092c:
    r->eax = r->edi;
    r->edx = 0;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_46f740;
at_470935:
    wr32(r, r->edi + 0x64, 0x4);
    wr32(r, r->edi + 0x68, 0x8);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_46f928;
at_470948:
    wr32(r, r->edi + 0x64, 0x5);
    wr32(r, r->edi + 0x68, 0x8);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_46fa07;
}

uint32_t vertrix_port_level_title_letter_actors_46f440(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x8c
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
    port_set32(&port, r.ebp, -0x4u, entry->ebx);
    port_set32(&port, r.ebp, -0x8u, entry->ecx);
    port_set32(&port, r.ebp, -0xcu, entry->edx);
    port_set32(&port, r.ebp, -0x10u, entry->esi);
    port_set32(&port, r.ebp, -0x14u, entry->edi);
    run(&r);
    return port_return(&port, r.eax, r.edx);
}
