#include "port_rtlactorsets.h"

/* Copies six 7-dword tables (0x4fd560..0x4fd5ec) to the stack, draws seven values with
 * random_in_range (0x415470), then runs four 7-pass loops. */

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

/* The last value pushed taken back. */
static uint32_t pop(Regs *r)
{
    return r->pushed != 0 ? r->stack[--r->pushed] : 0;
}

/* movs and rep movs of size bytes from esi to edi, forwards. */
static void movs(Regs *r, unsigned size)
{
    if (size == 1)
    {
        wr8(r, r->edi, rd8(r, r->esi));
    }
    else if (size == 2)
    {
        wr16(r, r->edi, rd16(r, r->esi));
    }
    else
    {
        wr32(r, r->edi, rd32(r, r->esi));
    }
    r->esi += size;
    r->edi += size;
}

static void rep_movs(Regs *r, unsigned size)
{
    for (; r->ecx != 0 && !r->port->env.failed; r->ecx--)
    {
        movs(r, size);
    }
}

/* Original 0x46a410: Copies six 7-dword tables (0x4fd560..0x4fd5ec) to the stack, draws seven
 * values with random_in_range (0x415470), then runs four 7-pass loops. Each pass allocates actors
 * (get_memory 0x4ca000, then actor_reset 0x4abd70 or block_construct_full 0x42bb00), sets them up
 * (actor_initialize, set_d0, set_time_scale, attach, set_frame_index/lookup_image, set_f0), and
 * passes each one to 0x4b5e70 with list 0x54671c. The base position is (0xd7,0xa), or (0xd7,0x13)
 * when [0x532a84]==1. The listing shows no callers. Evidence: calls 0x415470, 0x4ca000, 0x4abd70,
 * 0x4adf20, 0x4ac490, 0x4ac7b0, 0x4ac8d0, 0x4ac710, 0x4ac8a0, 0x4ac930, 0x4b5e70, 0x42bb00; reads
 * 0x532a84. Register-for-register from the listing (0x46a41e..0x46a9b7); labels are the original
 * addresses. */
static void run(Regs *r)
{
    r->eax = r->ebp - 0x44;
    r->ecx = 0x515f08;
    r->edi = r->ebp - 0xd0;
    push(r, r->port->env.chain);
    wr32(r, r->eax, pop(r));
    r->port->env.chain = r->eax;
    r->esi = 0x4fd560;
    wr32(r, r->ebp - 0x3c, r->ecx);
    r->ecx = 0x7;
    rep_movs(r, 4);
    r->ecx = 0x7;
    r->edi = r->ebp - 0xb4;
    r->esi = 0x4fd57c;
    rep_movs(r, 4);
    r->ecx = 0x7;
    r->edi = r->ebp - 0x124;
    r->esi = 0x4fd598;
    rep_movs(r, 4);
    r->ecx = 0x7;
    r->edi = r->ebp - 0x108;
    r->esi = 0x4fd5b4;
    rep_movs(r, 4);
    r->ecx = 0x7;
    r->edi = r->ebp - 0x7c;
    r->esi = 0x4fd5d0;
    rep_movs(r, 4);
    r->ecx = 0x7;
    r->edi = r->ebp - 0x98;
    r->esi = 0x4fd5ec;
    r->edx = 0x4ec1ec;
    r->ebx = 0;
    rep_movs(r, 4);
    wr32(r, r->ebp - 0x40, r->edx);
    r->esi = rd32(r, 0x532a84);
    wr32(r, r->ebp - 0x38, r->ebx);
    if (r->esi == 0x1)
    {
        goto at_46a9a7;
    }
    r->edi = 0xd7;
    r->eax = 0xa;
    wr32(r, r->ebp - 0x30, r->edi);
    wr32(r, r->ebp - 0x24, r->eax);
at_46a4cd:
    r->ebx = 0x3;
    r->esi = 0;
at_46a4d4:
    r->eax = rd32(r, r->esi + r->ebp - 0xd0);
    r->esi = r->esi + 0x4;
    call(r, 0x415470, 0);
    wr32(r, r->esi + r->ebp - 0xf0, r->eax);
    wr32(r, r->esi + r->ebp - 0x64, r->ebx);
    if (r->esi != 0x1c && !r->port->env.failed)
    {
        goto at_46a4d4;
    }
    r->eax = rd32(r, r->ebp - 0x30);
    r->eax = r->eax + 0xc;
    wr32(r, r->ebp - 0x28, r->eax);
    r->eax = rd32(r, r->ebp - 0x24);
    r->eax = r->eax + 0xc;
    wr32(r, r->ebp - 0x20, r->eax);
    r->eax = rd32(r, r->ebp - 0x20);
    r->eax = r->eax + 0x5;
    r->edi = 0;
    wr16(r, r->ebp - 0x1c, (r->eax & 0xffff));
at_46a513:
    r->eax = 0x15c;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_46a536;
    }
    r->esi = 0x1;
    wr32(r, r->ebp - 0x2c, r->eax);
    r->edx = 0;
    wr32(r, r->ebp - 0x38, r->esi);
    call(r, 0x4abd70, 0);
    wr32(r, r->ebp - 0x38, r->edx);
at_46a536:
    r->esi = r->eax;
    push(r, 0x0);
    r->ebx = rd32(r, r->ebp - 0x1e);
    push(r, 0x45c210);
    r->eax = rd32(r, r->ebp - 0x28);
    set_low16(&r->edx, rd16(r, r->edi + r->ebp - 0xb4));
    push(r, 0x0);
    r->ecx = 0;
    r->eax = r->eax + r->edx;
    push(r, 0x0);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    r->eax = r->eax + 0x5;
    push(r, 0x0);
    r->edx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = r->esi;
    call(r, 0x4adf20, 5);
    r->eax = r->esi;
    r->edx = rd32(r, r->edi + r->ebp - 0xec);
    call(r, 0x4ac490, 0);
    r->eax = r->esi;
    r->edx = rd32(r, r->edi + r->ebp - 0x60);
    call(r, 0x4ac7b0, 0);
    r->edx = 0x546650;
    r->eax = r->esi;
    call(r, 0x4ac8d0, 0);
    r->eax = r->esi;
    r->edx = rd32(r, r->edi + r->ebp - 0x108);
    call(r, 0x4ac710, 0);
    r->eax = r->esi;
    call(r, 0x4ac8a0, 0);
    wr8(r, r->esi + 0x93, 0x1);
    wr8(r, r->esi + 0x95, 0x1);
    wr8(r, r->esi + 0x4e, 0x0);
    wr16(r, r->esi + 0x48, 0xffd8);
    wr32(r, r->esi + 0x64, 0x0);
    r->eax = rd32(r, r->edi + r->ebp - 0x124);
    r->edx = 0x45c1b0;
    wr32(r, r->esi + 0x68, r->eax);
    r->eax = r->esi;
    wr32(r, r->esi + 0x6c, 0x1);
    call(r, 0x4ac930, 0);
    r->eax = 0x54671c;
    r->edx = r->esi;
    call(r, 0x4b5e70, 0);
    r->eax = 0x160;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_46a60e;
    }
    r->ecx = 0x3;
    wr32(r, r->ebp - 0x2c, r->eax);
    r->ebx = 0;
    wr32(r, r->ebp - 0x38, r->ecx);
    call(r, 0x42bb00, 0);
    wr32(r, r->ebp - 0x38, r->ebx);
at_46a60e:
    r->esi = r->eax;
    push(r, 0x0);
    r->ebx = rd32(r, r->ebp - 0x22);
    push(r, 0x45c210);
    r->eax = rd32(r, r->ebp - 0x28);
    set_low16(&r->ecx, rd16(r, r->edi + r->ebp - 0xb4));
    push(r, 0x0);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    r->eax = r->eax + r->ecx;
    push(r, 0x0);
    r->edx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    push(r, 0x0);
    r->ecx = 0;
    r->eax = r->esi;
    call(r, 0x4adf20, 5);
    r->eax = r->esi;
    r->edx = rd32(r, r->edi + r->ebp - 0xec);
    call(r, 0x4ac490, 0);
    r->eax = r->esi;
    r->edx = rd32(r, r->edi + r->ebp - 0x60);
    call(r, 0x4ac7b0, 0);
    r->edx = 0x546650;
    r->eax = r->esi;
    call(r, 0x4ac8d0, 0);
    r->eax = r->esi;
    r->edx = rd32(r, r->edi + r->ebp - 0x108);
    call(r, 0x4ac710, 0);
    r->eax = r->esi;
    call(r, 0x4ac8a0, 0);
    wr8(r, r->esi + 0x93, 0x1);
    wr8(r, r->esi + 0x95, 0x0);
    wr8(r, r->esi + 0x4e, 0x64);
    r->edi = r->edi + 0x4;
    wr32(r, r->esi + 0x64, 0x0);
    r->eax = rd32(r, r->edi + r->ebp - 0x128);
    r->edx = 0x45c150;
    wr32(r, r->esi + 0x68, r->eax);
    r->eax = r->esi;
    wr32(r, r->esi + 0x6c, 0x1);
    call(r, 0x4ac930, 0);
    r->eax = 0x54671c;
    r->edx = r->esi;
    r->esi = 0;
    call(r, 0x4b5e70, 0);
    wr32(r, r->ebp - 0x38, r->esi);
    if (r->edi != 0x1c && !r->port->env.failed)
    {
        goto at_46a513;
    }
    r->eax = rd32(r, r->ebp - 0x30);
    wr32(r, r->ebp - 0x28, r->eax);
    r->eax = rd32(r, r->ebp - 0x24);
    wr32(r, r->ebp - 0x20, r->eax);
    r->eax = rd32(r, r->ebp - 0x20);
    r->eax = r->eax + 0x5;
    r->edi = 0;
    wr16(r, r->ebp - 0x18, (r->eax & 0xffff));
at_46a6e3:
    r->eax = 0x160;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_46a6f6;
    }
    call(r, 0x42bb00, 0);
at_46a6f6:
    r->esi = r->eax;
    push(r, 0x0);
    r->ebx = rd32(r, r->ebp - 0x1a);
    push(r, 0x45c060);
    r->eax = rd32(r, r->ebp - 0x28);
    set_low16(&r->edx, rd16(r, r->edi + r->ebp - 0xb4));
    push(r, 0x0);
    r->ecx = 0;
    r->eax = r->eax + r->edx;
    push(r, 0x0);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    r->eax = r->eax + 0x5;
    push(r, 0x0);
    r->edx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = r->esi;
    call(r, 0x4adf20, 5);
    r->eax = r->esi;
    r->edx = rd32(r, r->edi + r->ebp - 0xec);
    call(r, 0x4ac490, 0);
    r->eax = r->esi;
    r->edx = rd32(r, r->edi + r->ebp - 0x60);
    call(r, 0x4ac7b0, 0);
    r->edx = rd32(r, r->edi + r->ebp - 0xd0) * 0x1c;
    r->edx = r->edx + 0x544ac0;
    r->eax = r->esi;
    call(r, 0x4ac8d0, 0);
    wr8(r, r->esi + 0x93, 0x1);
    wr8(r, r->esi + 0x95, 0x1);
    wr8(r, r->esi + 0x4e, 0x0);
    wr16(r, r->esi + 0x48, 0x0);
    set_low8(&r->eax, rd8(r, r->edi + r->ebp - 0xd0));
    r->edx = 0x45c0e0;
    wr8(r, r->esi + 0x15c, (r->eax & 0xff));
    r->eax = r->esi;
    r->edi = r->edi + 0x4;
    call(r, 0x4ac930, 0);
    wr32(r, r->esi + 0x64, 0x0);
    r->eax = rd32(r, r->edi + r->ebp - 0x128);
    wr32(r, r->esi + 0x6c, 0x1);
    r->edx = r->esi;
    wr32(r, r->esi + 0x68, r->eax);
    r->eax = 0x54671c;
    wr32(r, r->esi + 0x70, 0xffffffffu);
    call(r, 0x4b5e70, 0);
    if (r->edi != 0x1c && !r->port->env.failed)
    {
        goto at_46a6e3;
    }
    r->eax = rd32(r, r->ebp - 0x30);
    wr32(r, r->ebp - 0x28, r->eax);
    r->eax = rd32(r, r->ebp - 0x24);
    r->edi = 0;
    wr32(r, r->ebp - 0x20, r->eax);
at_46a7cd:
    r->eax = 0x160;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_46a7e0;
    }
    call(r, 0x42bb00, 0);
at_46a7e0:
    r->esi = r->eax;
    push(r, 0x0);
    r->ebx = rd32(r, r->ebp - 0x22);
    push(r, 0x45c060);
    r->eax = rd32(r, r->ebp - 0x28);
    set_low16(&r->ecx, rd16(r, r->edi + r->ebp - 0xb4));
    push(r, 0x0);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    r->eax = r->eax + r->ecx;
    push(r, 0x0);
    r->edx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    push(r, 0x0);
    r->ecx = 0;
    r->eax = r->esi;
    call(r, 0x4adf20, 5);
    r->eax = r->esi;
    r->edx = rd32(r, r->edi + r->ebp - 0xec);
    call(r, 0x4ac490, 0);
    r->eax = r->esi;
    r->edx = rd32(r, r->edi + r->ebp - 0x60);
    call(r, 0x4ac7b0, 0);
    r->edx = rd32(r, r->edi + r->ebp - 0xd0) * 0x1c;
    r->eax = r->esi;
    r->edx = r->edx + 0x544ac0;
    call(r, 0x4ac8d0, 0);
    wr8(r, r->esi + 0x95, 0x1);
    r->edx = 0x45bff0;
    wr8(r, r->esi + 0x93, 0x1);
    r->eax = r->esi;
    wr8(r, r->esi + 0x4e, 0x0);
    call(r, 0x4ac930, 0);
    wr32(r, r->esi + 0x64, 0x0);
    r->eax = rd32(r, r->edi + r->ebp - 0x124);
    wr32(r, r->esi + 0x6c, 0x1);
    wr32(r, r->esi + 0x68, r->eax);
    set_low8(&r->eax, rd8(r, r->edi + r->ebp - 0xd0));
    wr8(r, r->esi + 0x15c, (r->eax & 0xff));
    r->eax = rd32(r, r->edi + r->ebp - 0x7c);
    r->edx = r->esi;
    wr32(r, r->esi + 0x70, r->eax);
    r->eax = 0x54671c;
    r->edi = r->edi + 0x4;
    call(r, 0x4b5e70, 0);
    if (r->edi != 0x1c && !r->port->env.failed)
    {
        goto at_46a7cd;
    }
    r->eax = rd32(r, r->ebp - 0x30);
    wr32(r, r->ebp - 0x28, r->eax);
    r->eax = rd32(r, r->ebp - 0x24);
    r->edi = 0;
    wr32(r, r->ebp - 0x20, r->eax);
at_46a8ac:
    r->eax = 0x160;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_46a8bf;
    }
    call(r, 0x42bb00, 0);
at_46a8bf:
    r->esi = r->eax;
    push(r, 0x0);
    push(r, 0x45c060);
    r->ebx = rd32(r, r->ebp - 0x22);
    r->eax = rd32(r, r->ebp - 0x28);
    push(r, 0x0);
    set_low16(&r->edx, rd16(r, r->edi + r->ebp - 0xb4));
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    r->eax = r->eax + r->edx;
    push(r, 0x0);
    r->edx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = r->esi;
    call(r, 0x4adf20, 5);
    r->eax = r->esi;
    r->edx = rd32(r, r->edi + r->ebp - 0xec);
    call(r, 0x4ac490, 0);
    r->eax = r->esi;
    r->edx = rd32(r, r->edi + r->ebp - 0x60);
    call(r, 0x4ac7b0, 0);
    r->edx = rd32(r, r->edi + r->ebp - 0xd0) * 0x1c;
    r->eax = r->esi;
    r->edx = r->edx + 0x546554;
    call(r, 0x4ac8d0, 0);
    r->edx = 0x45beb0;
    r->eax = r->esi;
    call(r, 0x4ac930, 0);
    wr32(r, r->esi + 0x64, 0x0);
    r->eax = rd32(r, r->edi + r->ebp - 0x124);
    wr32(r, r->esi + 0x6c, 0x1);
    wr32(r, r->esi + 0x68, r->eax);
    set_low8(&r->eax, rd8(r, r->edi + r->ebp - 0xd0));
    wr16(r, r->esi + 0x48, 0xffb0);
    wr8(r, r->esi + 0x95, 0x4);
    wr8(r, r->esi + 0x94, 0x0);
    wr8(r, r->esi + 0x93, 0x1);
    wr8(r, r->esi + 0x4e, 0x32);
    r->edi = r->edi + 0x4;
    wr8(r, r->esi + 0x15c, (r->eax & 0xff));
    set_low8(&r->eax, rd8(r, r->edi + r->ebp - 0x9c));
    r->edx = r->esi;
    wr8(r, r->esi + 0x52, (r->eax & 0xff));
    r->eax = 0x54671c;
    wr32(r, r->esi + 0x70, 0xffffffffu);
    call(r, 0x4b5e70, 0);
    if (r->edi != 0x1c && !r->port->env.failed)
    {
        goto at_46a8ac;
    }
    r->eax = rd32(r, r->ebp - 0x44);
    r->port->env.chain = r->eax;
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_46a9a7:
    r->edx = 0xd7;
    r->ecx = 0x13;
    wr32(r, r->ebp - 0x30, r->edx);
    wr32(r, r->ebp - 0x24, r->ecx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_46a4cd;
}

uint32_t vertrix_port_spawn_random_actor_set_46a410(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x128
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
