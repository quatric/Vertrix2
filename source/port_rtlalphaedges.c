#include "port_rtlalphaedges.h"

/* For a 32-bit image (+0x27 = 4) with alpha (+0x26 = 1): points the level tables 0x55f1f0/0x55f1f4
 * at rows edx and 100 - edx of 0x558cf0, copies the pixels, and gives each opaque pixel the average
 * colour of itself and its opaque neighbours above, below, left and right. */

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
    uint32_t esp;
    uint32_t tmp;
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

/* A call that pops nothing (cdecl, or no stack arguments): every value pushed passed and left for
 * the caller's add esp. */
static void call_keep(Regs *r, uint32_t target)
{
    call_with_stack(r, target, r->pushed, 1);
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

static void div32(Regs *r, uint32_t value)
{
    LiftFlags flags;
    memset(&flags, 0, sizeof flags);
    lift_div1(32, value, &r->eax, &r->edx, &flags);
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

/* Original 0x483790: For a 32-bit image (+0x27 = 4) with alpha (+0x26 = 1): points the level tables
 * 0x55f1f0/0x55f1f4 at rows edx and 100 - edx of 0x558cf0, copies the pixels, and gives each opaque
 * pixel the average colour of itself and its opaque neighbours above, below, left and right.
 * Evidence: calls 0x4ec160, 0x4ea190; reads 0x55f1f0, 0x55f1f4; writes 0x55f1f0, 0x55f1f4.
 * Register-for-register from the listing (0x48379a..0x483cd4); labels are the original addresses.
 */
static void run(Regs *r)
{
    r->ebx = r->eax;
    r->eax = rd32(r, r->eax + 0x4);
    r->ecx = 0x64;
    wr32(r, r->ebp - 0x34, r->eax);
    r->eax = rd32(r, r->ebx + 0x8);
    r->ecx = r->ecx - r->edx;
    wr32(r, r->ebp - 0x54, r->eax);
    set_low8(&r->eax, rd8(r, r->ebx + 0x27));
    wr32(r, r->ebp - 0x2c, r->ecx);
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x4)
    {
        goto at_4837c2;
    }
    r->edi = rd32(r, r->ebp - 0x10);
    r->esi = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4837c2:
    r->ecx = 0x558cf0;
    r->edx = r->edx << 0x8;
    r->ecx = r->ecx + r->edx;
    r->edx = rd32(r, r->ebp - 0x2c);
    wr32(r, 0x55f1f0, r->ecx);
    r->ecx = 0x558cf0;
    r->edx = r->edx << 0x8;
    r->ecx = r->ecx + r->edx;
    wr32(r, 0x55f1f4, r->ecx);
    r->edx = rd32(r, r->ebx);
    r->ecx = rd32(r, r->ebp - 0x54);
    wr32(r, r->ebp - 0x50, r->edx);
    r->edx = rd32(r, r->ebp - 0x34);
    r->edx = r->edx * r->ecx;
    r->ecx = 0;
    set_low8(&r->ecx, (r->eax & 0xff));
    r->ecx = r->ecx * r->edx;
    r->edx = 0x1;
    r->eax = r->ecx;
    call_keep(r, 0x4ec160);
    r->edx = r->eax;
    r->edi = r->eax;
    r->esi = rd32(r, r->ebx);
    wr32(r, r->ebp - 0x58, r->eax);
    push(r, r->edi);
    r->eax = r->ecx;
    r->ecx = r->ecx >> 0x2;
    rep_movs(r, 4);
    set_low8(&r->ecx, (r->eax & 0xff));
    set_low8(&r->ecx, (r->ecx & 0xff) & 0x3);
    rep_movs(r, 1);
    r->edi = pop(r);
    r->ecx = rd32(r, r->ebp - 0x54);
    r->esi = rd32(r, r->ebp - 0x34);
    r->eax = rd32(r, r->ebp - 0x34);
    wr32(r, r->ebp - 0x4c, r->edx);
    r->ecx = r->ecx - 1;
    r->esi = r->esi - 1;
    set_low8(&r->edx, rd8(r, r->ebx + 0x26));
    r->eax = r->eax << 0x2;
    if ((uint8_t)((r->edx & 0xff)) != (uint8_t)0x1)
    {
        goto at_483ae3;
    }
    r->edx = 0;
    r->ebx = rd32(r, r->ebp - 0x54);
    wr32(r, r->ebp - 0x68, r->edx);
    if (r->ebx == 0)
    {
        goto at_483a81;
    }
    wr32(r, r->ebp - 0x44, r->esi);
    wr32(r, r->ebp - 0x40, r->eax);
    wr32(r, r->ebp - 0x3c, r->ecx);
    wr32(r, r->ebp - 0x6c, r->eax);
at_483858:
    r->eax = 0;
    wr32(r, r->ebp - 0x20, r->eax);
    r->eax = rd32(r, r->ebp - 0x50);
    wr32(r, r->ebp - 0x24, r->eax);
    r->eax = rd32(r, r->ebp - 0x4c);
    r->edx = rd32(r, r->ebp - 0x34);
    wr32(r, r->ebp - 0x18, r->eax);
    if (r->edx == 0)
    {
        goto at_483a5c;
    }
at_483874:
    r->eax = rd32(r, r->ebp - 0x18);
    r->edx = rd32(r, r->ebp - 0x6c);
    r->ebx = 0;
    r->ecx = 0;
    r->esi = 0;
    r->eax = r->eax - r->edx;
    r->edx = rd32(r, r->ebp - 0x68);
    r->edi = 0;
    if (r->edx == 0)
    {
        goto at_4838b1;
    }
    r->edx = rd32(r, r->eax);
    r->edx = r->edx >> 0x18;
    wr32(r, r->ebp - 0x5c, r->edx);
    set_low8(&r->edx, rd8(r, r->ebp - 0x5c));
    if ((uint8_t)((r->edx & 0xff)) == 0)
    {
        goto at_4838b1;
    }
    r->ecx = rd32(r, r->eax);
    r->ecx = r->ecx >> 0x10;
    r->esi = (r->ecx & 0xff);
    r->ecx = 0;
    r->edi = 0x1;
    set_low16(&r->ecx, rd16(r, r->eax));
    set_low8(&r->ebx, rd8(r, r->eax));
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x8);
at_4838b1:
    r->eax = rd32(r, r->ebp - 0x18);
    r->eax = r->eax + rd32(r, r->ebp - 0x40);
    r->edx = rd32(r, r->ebp - 0x68);
    if (r->edx >= rd32(r, r->ebp - 0x3c))
    {
        goto at_4838f7;
    }
    r->edx = rd32(r, r->eax);
    r->edx = r->edx >> 0x18;
    wr32(r, r->ebp - 0x5c, r->edx);
    set_low8(&r->edx, rd8(r, r->ebp - 0x5c));
    if ((uint8_t)((r->edx & 0xff)) == 0)
    {
        goto at_4838f7;
    }
    r->edx = rd32(r, r->eax);
    r->edx = r->edx >> 0x10;
    wr32(r, r->ebp - 0x5c, r->edx);
    set_low8(&r->edx, rd8(r, r->ebp - 0x5c));
    wr8(r, r->ebp - 0x14, (r->edx & 0xff));
    r->edx = 0;
    set_low8(&r->edx, rd8(r, r->ebp - 0x14));
    r->esi = r->esi + r->edx;
    r->edx = 0;
    set_low16(&r->edx, rd16(r, r->eax));
    r->edx = (uint32_t)((int32_t)r->edx >> 0x8);
    set_low8(&r->eax, rd8(r, r->eax));
    r->ecx = r->ecx + r->edx;
    r->eax = r->eax & 0xff;
    r->edi = r->edi + 1;
    r->ebx = r->ebx + r->eax;
at_4838f7:
    r->eax = rd32(r, r->ebp - 0x18);
    r->edx = rd32(r, r->ebp - 0x20);
    r->eax = r->eax - 0x4;
    if (r->edx == 0)
    {
        goto at_48393c;
    }
    r->edx = rd32(r, r->eax);
    r->edx = r->edx >> 0x18;
    wr32(r, r->ebp - 0x5c, r->edx);
    set_low8(&r->edx, rd8(r, r->ebp - 0x5c));
    if ((uint8_t)((r->edx & 0xff)) == 0)
    {
        goto at_48393c;
    }
    r->edx = rd32(r, r->eax);
    r->edx = r->edx >> 0x10;
    wr32(r, r->ebp - 0x5c, r->edx);
    set_low8(&r->edx, rd8(r, r->ebp - 0x5c));
    wr8(r, r->ebp - 0x14, (r->edx & 0xff));
    r->edx = 0;
    set_low8(&r->edx, rd8(r, r->ebp - 0x14));
    r->esi = r->esi + r->edx;
    r->edx = 0;
    set_low16(&r->edx, rd16(r, r->eax));
    r->edx = (uint32_t)((int32_t)r->edx >> 0x8);
    set_low8(&r->eax, rd8(r, r->eax));
    r->ecx = r->ecx + r->edx;
    r->eax = r->eax & 0xff;
    r->edi = r->edi + 1;
    r->ebx = r->ebx + r->eax;
at_48393c:
    r->eax = rd32(r, r->ebp - 0x18);
    r->edx = rd32(r, r->ebp - 0x20);
    r->eax = r->eax + 0x4;
    if (r->edx >= rd32(r, r->ebp - 0x44))
    {
        goto at_483982;
    }
    r->edx = rd32(r, r->eax);
    r->edx = r->edx >> 0x18;
    wr32(r, r->ebp - 0x5c, r->edx);
    set_low8(&r->edx, rd8(r, r->ebp - 0x5c));
    if ((uint8_t)((r->edx & 0xff)) == 0)
    {
        goto at_483982;
    }
    r->edx = rd32(r, r->eax);
    r->edx = r->edx >> 0x10;
    wr32(r, r->ebp - 0x5c, r->edx);
    set_low8(&r->edx, rd8(r, r->ebp - 0x5c));
    wr8(r, r->ebp - 0x14, (r->edx & 0xff));
    r->edx = 0;
    set_low8(&r->edx, rd8(r, r->ebp - 0x14));
    r->esi = r->esi + r->edx;
    r->edx = 0;
    set_low16(&r->edx, rd16(r, r->eax));
    r->edx = (uint32_t)((int32_t)r->edx >> 0x8);
    set_low8(&r->eax, rd8(r, r->eax));
    r->ecx = r->ecx + r->edx;
    r->eax = r->eax & 0xff;
    r->edi = r->edi + 1;
    r->ebx = r->ebx + r->eax;
at_483982:
    if (r->edi == 0)
    {
        goto at_483a38;
    }
    r->eax = rd32(r, r->ebp - 0x18);
    r->eax = rd32(r, r->eax);
    r->eax = r->eax >> 0x18;
    wr32(r, r->ebp - 0x5c, r->eax);
    set_low8(&r->eax, rd8(r, r->ebp - 0x5c));
    if ((uint8_t)((r->eax & 0xff)) == 0)
    {
        goto at_483a92;
    }
    r->eax = r->esi;
    r->edx = 0;
    div32(r, r->edi);
    r->esi = r->eax;
    r->edx = 0;
    r->eax = r->ecx;
    div32(r, r->edi);
    r->ecx = r->eax;
    r->edx = 0;
    r->eax = r->ebx;
    div32(r, r->edi);
    r->esi = r->esi << 0x10;
    r->ecx = r->ecx << 0x8;
    r->ecx = r->ecx | r->esi;
    r->ebx = r->eax;
    r->eax = rd32(r, r->ebp - 0x18);
    r->ebx = r->ebx | r->ecx;
    r->eax = rd32(r, r->eax);
    r->ecx = 0;
    r->eax = r->eax >> 0x10;
    set_low8(&r->ecx, (r->eax & 0xff));
    r->eax = rd32(r, 0x55f1f0);
    r->edi = rd8(r, r->ecx + r->eax);
    r->ecx = r->ebx;
    r->ecx = r->ecx >> 0x10;
    r->esi = (r->ecx & 0xff);
    r->ecx = rd32(r, 0x55f1f4);
    r->esi = rd8(r, r->ecx + r->esi);
    r->esi = r->esi + r->edi;
    r->esi = r->esi << 0x10;
    r->esi = r->esi | 0xff000000u;
    r->edx = rd32(r, r->ebp - 0x18);
    wr32(r, r->ebp - 0x5c, r->esi);
    r->esi = 0;
    set_low16(&r->esi, rd16(r, r->edx));
    r->esi = (uint32_t)((int32_t)r->esi >> 0x8);
    r->edi = rd8(r, r->esi + r->eax);
    r->esi = 0;
    set_low16(&r->esi, (r->ebx & 0xffff));
    r->esi = (uint32_t)((int32_t)r->esi >> 0x8);
    r->esi = rd8(r, r->ecx + r->esi);
    r->esi = r->esi + r->edi;
    r->edi = rd32(r, r->ebp - 0x5c);
    r->esi = r->esi << 0x8;
    r->edi = r->edi | r->esi;
    r->esi = rd8(r, r->edx);
    r->esi = rd8(r, r->esi + r->eax);
    r->eax = 0;
    set_low8(&r->eax, (r->ebx & 0xff));
    set_low8(&r->eax, rd8(r, r->ecx + r->eax));
    r->eax = r->eax & 0xff;
    r->eax = r->eax + r->esi;
    r->edx = rd32(r, r->ebp - 0x24);
    r->eax = r->eax | r->edi;
    wr32(r, r->edx, r->eax);
at_483a38:
    r->ecx = rd32(r, r->ebp - 0x24);
    r->ebx = rd32(r, r->ebp - 0x18);
    r->esi = rd32(r, r->ebp - 0x20);
    r->edi = rd32(r, r->ebp - 0x34);
    r->ecx = r->ecx + 0x4;
    r->ebx = r->ebx + 0x4;
    r->esi = r->esi + 1;
    wr32(r, r->ebp - 0x24, r->ecx);
    wr32(r, r->ebp - 0x18, r->ebx);
    wr32(r, r->ebp - 0x20, r->esi);
    if (r->esi < r->edi && !r->port->env.failed)
    {
        goto at_483874;
    }
at_483a5c:
    r->eax = rd32(r, r->ebp - 0x6c);
    r->ecx = rd32(r, r->ebp - 0x4c);
    r->ebx = rd32(r, r->ebp - 0x50);
    r->esi = rd32(r, r->ebp - 0x68);
    r->edi = rd32(r, r->ebp - 0x54);
    r->esi = r->esi + 1;
    r->ecx = r->ecx + r->eax;
    r->ebx = r->ebx + r->eax;
    wr32(r, r->ebp - 0x4c, r->ecx);
    wr32(r, r->ebp - 0x50, r->ebx);
    wr32(r, r->ebp - 0x68, r->esi);
    if (r->esi < r->edi && !r->port->env.failed)
    {
        goto at_483858;
    }
at_483a81:
    r->eax = rd32(r, r->ebp - 0x58);
    call_keep(r, 0x4ea190);
    r->edi = rd32(r, r->ebp - 0x10);
    r->esi = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_483a92:
    r->eax = r->esi;
    r->edx = 0;
    div32(r, r->edi);
    r->eax = r->eax * rd32(r, r->ebp - 0x2c);
    r->edx = 0;
    r->esi = 0x64;
    div32(r, r->esi);
    r->esi = r->eax;
    r->edx = 0;
    r->eax = r->ecx;
    div32(r, r->edi);
    r->eax = r->eax * rd32(r, r->ebp - 0x2c);
    r->ecx = 0x64;
    r->edx = 0;
    div32(r, r->ecx);
    r->ecx = r->eax;
    r->edx = 0;
    r->eax = r->ebx;
    div32(r, r->edi);
    r->eax = r->eax * rd32(r, r->ebp - 0x2c);
    r->edx = 0;
    r->ebx = 0x64;
    div32(r, r->ebx);
    r->esi = r->esi << 0x10;
    r->ecx = r->ecx << 0x8;
    r->ecx = r->ecx | r->esi;
    r->ecx = r->ecx | r->eax;
    r->eax = rd32(r, r->ebp - 0x24);
    wr32(r, r->eax, r->ecx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_483a38;
at_483ae3:
    r->ebx = 0;
    r->edi = rd32(r, r->ebp - 0x54);
    wr32(r, r->ebp - 0x30, r->ebx);
    if (r->edi == 0 && !r->port->env.failed)
    {
        goto at_483a81;
    }
    wr32(r, r->ebp - 0x48, r->esi);
    wr32(r, r->ebp - 0x60, r->eax);
    wr32(r, r->ebp - 0x38, r->ecx);
    wr32(r, r->ebp - 0x70, r->eax);
at_483afb:
    r->eax = rd32(r, r->ebp - 0x50);
    r->ebx = rd32(r, r->ebp - 0x34);
    r->ecx = 0;
    wr32(r, r->ebp - 0x28, r->eax);
    r->eax = rd32(r, r->ebp - 0x4c);
    wr32(r, r->ebp - 0x64, r->ecx);
    wr32(r, r->ebp - 0x1c, r->eax);
    if (r->ebx == 0)
    {
        goto at_483c7b;
    }
at_483b17:
    r->eax = rd32(r, r->ebp - 0x30);
    r->esi = 0;
    r->ebx = 0;
    r->ecx = 0;
    r->edi = 0;
    if (r->eax == 0)
    {
        goto at_483b45;
    }
    r->eax = rd32(r, r->ebp - 0x1c);
    r->eax = r->eax - rd32(r, r->ebp - 0x70);
    r->ecx = rd32(r, r->eax);
    r->ecx = r->ecx >> 0x10;
    r->edi = 0x1;
    r->ecx = r->ecx & 0xff;
    set_low16(&r->ebx, rd16(r, r->eax));
    r->esi = rd8(r, r->eax);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x8);
at_483b45:
    r->eax = rd32(r, r->ebp - 0x30);
    if (r->eax < rd32(r, r->ebp - 0x38))
    {
        goto at_483ca5;
    }
at_483b51:
    if (rd32(r, r->ebp - 0x64) <= 0x0)
    {
        goto at_483b88;
    }
    r->eax = rd32(r, r->ebp - 0x1c);
    r->edx = rd32(r, r->eax - 0x4);
    r->edx = r->edx >> 0x10;
    wr32(r, r->ebp - 0x5c, r->edx);
    set_low8(&r->edx, rd8(r, r->ebp - 0x5c));
    wr8(r, r->ebp - 0x14, (r->edx & 0xff));
    r->edx = 0;
    set_low8(&r->edx, rd8(r, r->ebp - 0x14));
    r->ecx = r->ecx + r->edx;
    r->edx = 0;
    set_low16(&r->edx, rd16(r, r->eax - 0x4));
    r->eax = r->eax - 0x4;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x8);
    set_low8(&r->eax, rd8(r, r->eax));
    r->ebx = r->ebx + r->edx;
    r->eax = r->eax & 0xff;
    r->edi = r->edi + 1;
    r->esi = r->esi + r->eax;
at_483b88:
    r->eax = rd32(r, r->ebp - 0x64);
    if (r->eax >= rd32(r, r->ebp - 0x48))
    {
        goto at_483bbf;
    }
    r->eax = rd32(r, r->ebp - 0x1c);
    r->edx = rd32(r, r->eax + 0x4);
    r->edx = r->edx >> 0x10;
    wr32(r, r->ebp - 0x5c, r->edx);
    set_low8(&r->edx, rd8(r, r->ebp - 0x5c));
    wr8(r, r->ebp - 0x14, (r->edx & 0xff));
    r->edx = 0;
    set_low8(&r->edx, rd8(r, r->ebp - 0x14));
    r->ecx = r->ecx + r->edx;
    r->edx = 0;
    set_low16(&r->edx, rd16(r, r->eax + 0x4));
    r->edx = (uint32_t)((int32_t)r->edx >> 0x8);
    set_low8(&r->eax, rd8(r, r->eax + 0x4));
    r->ebx = r->ebx + r->edx;
    r->eax = r->eax & 0xff;
    r->edi = r->edi + 1;
    r->esi = r->esi + r->eax;
at_483bbf:
    r->eax = r->ecx;
    r->edx = 0;
    div32(r, r->edi);
    r->ecx = r->eax;
    r->edx = 0;
    r->eax = r->ebx;
    div32(r, r->edi);
    r->ebx = r->eax;
    r->edx = 0;
    r->eax = r->esi;
    div32(r, r->edi);
    r->ecx = r->ecx << 0x10;
    r->ebx = r->ebx << 0x8;
    r->ecx = r->ecx | r->ebx;
    r->ecx = r->ecx | r->eax;
    r->eax = rd32(r, r->ebp - 0x1c);
    r->eax = rd32(r, r->eax);
    r->eax = r->eax >> 0x10;
    r->ebx = rd32(r, 0x55f1f0);
    r->eax = r->eax & 0xff;
    r->edi = rd8(r, r->ebx + r->eax);
    r->eax = r->ecx;
    r->eax = r->eax >> 0x10;
    r->esi = (r->eax & 0xff);
    r->eax = rd32(r, 0x55f1f4);
    r->esi = rd8(r, r->esi + r->eax);
    r->esi = r->esi + r->edi;
    r->esi = r->esi << 0x10;
    r->esi = r->esi | 0xff000000u;
    r->edx = rd32(r, r->ebp - 0x1c);
    wr32(r, r->ebp - 0x5c, r->esi);
    r->esi = 0;
    set_low16(&r->esi, rd16(r, r->edx));
    r->esi = (uint32_t)((int32_t)r->esi >> 0x8);
    r->edi = rd8(r, r->esi + r->ebx);
    r->esi = 0;
    set_low16(&r->esi, (r->ecx & 0xffff));
    r->esi = (uint32_t)((int32_t)r->esi >> 0x8);
    r->esi = rd8(r, r->esi + r->eax);
    r->esi = r->esi + r->edi;
    r->edi = rd32(r, r->ebp - 0x5c);
    r->esi = r->esi << 0x8;
    r->edi = r->edi | r->esi;
    r->esi = rd8(r, r->edx);
    set_low8(&r->ebx, rd8(r, r->esi + r->ebx));
    r->ebx = r->ebx & 0xff;
    r->ecx = r->ecx & 0xff;
    set_low8(&r->eax, rd8(r, r->ecx + r->eax));
    r->eax = r->eax & 0xff;
    r->eax = r->eax + r->ebx;
    r->edi = r->edi | r->eax;
    r->eax = rd32(r, r->ebp - 0x28);
    r->esi = r->eax + 0x4;
    wr32(r, r->eax, r->edi);
    r->eax = rd32(r, r->ebp - 0x64);
    r->edi = r->edx + 0x4;
    wr32(r, r->ebp - 0x28, r->esi);
    r->edx = rd32(r, r->ebp - 0x34);
    r->eax = r->eax + 1;
    wr32(r, r->ebp - 0x1c, r->edi);
    wr32(r, r->ebp - 0x64, r->eax);
    if (r->eax < r->edx && !r->port->env.failed)
    {
        goto at_483b17;
    }
at_483c7b:
    r->eax = rd32(r, r->ebp - 0x70);
    r->esi = rd32(r, r->ebp - 0x4c);
    r->edi = rd32(r, r->ebp - 0x50);
    r->edx = rd32(r, r->ebp - 0x54);
    r->esi = r->esi + r->eax;
    r->edi = r->edi + r->eax;
    r->eax = rd32(r, r->ebp - 0x30);
    wr32(r, r->ebp - 0x4c, r->esi);
    r->eax = r->eax + 1;
    wr32(r, r->ebp - 0x50, r->edi);
    wr32(r, r->ebp - 0x30, r->eax);
    if (r->eax >= r->edx && !r->port->env.failed)
    {
        goto at_483a81;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_483afb;
at_483ca5:
    r->eax = rd32(r, r->ebp - 0x1c);
    r->eax = r->eax + rd32(r, r->ebp - 0x60);
    r->edx = rd32(r, r->eax);
    r->edx = r->edx >> 0x10;
    wr32(r, r->ebp - 0x5c, r->edx);
    set_low8(&r->edx, rd8(r, r->ebp - 0x5c));
    wr8(r, r->ebp - 0x14, (r->edx & 0xff));
    r->edx = 0;
    set_low8(&r->edx, rd8(r, r->ebp - 0x14));
    r->ecx = r->ecx + r->edx;
    r->edx = 0;
    set_low16(&r->edx, rd16(r, r->eax));
    r->edx = (uint32_t)((int32_t)r->edx >> 0x8);
    set_low8(&r->eax, rd8(r, r->eax));
    r->ebx = r->ebx + r->edx;
    r->eax = r->eax & 0xff;
    r->edi = r->edi + 1;
    r->esi = r->esi + r->eax;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_483b51;
}

uint32_t vertrix_port_image_alpha_edge_smooth_483790(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x74
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
    port_set32(&port, r.ebp, -0xcu, entry->esi);
    port_set32(&port, r.ebp, -0x10u, entry->edi);
    run(&r);
    return port_return(&port, r.eax, r.edx);
}
