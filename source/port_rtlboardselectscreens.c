#include "port_rtlboardselectscreens.h"

/* Only called from board_screen_setup_41c410 (0x41c590). */

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

/* The last value pushed taken back. */
static uint32_t pop(Regs *r)
{
    return r->pushed != 0 ? r->stack[--r->pushed] : 0;
}

/* Original 0x466d60: Only called from board_screen_setup_41c410 (0x41c590). It clears 0x532a9c,
 * then takes one of two paths. When 0x532a7c==0 and 0x532a80==1 it reads the words at
 * 0x532b6c..0x532b78. When 0x532a7c==1 and 0x532a80==0 it reads the same words in swapped order
 * (0x468bd1). On both paths it tests the words with sound_key_is_control (0x476650) and then builds
 * the screen's actors, mostly labeled boxes (0x4b6350, text from 0x50e528), each linked into the
 * list at 0x54671c (0x4b5e70). It finishes with an 'EXIT' menu item (0x4602a0, 0x50e536) whose
 * update handler is 0x445d80. Evidence: calls 0x476650, 0x4ca000, 0x4b6350, 0x4adf20, 0x4b65d0,
 * 0x4ac7b0, 0x4ac910, 0x4b5e70, 0x4abd70, 0x4ae110, 0x4ac7d0, 0x4ac8d0, 0x4ac710, 0x4ac8a0,
 * 0x4ac470, 0x4b6690, 0x4b6530, 0x4b6540, 0x4b65b0, 0x4b6550, 0x429670, 0x4ac860, 0x4b5400,
 * 0x4b54d0 and 3 more; reads 0x532a7c, 0x532a80, 0x532b6c, 0x532b6e, 0x532b70, 0x532b74, 0x532b76,
 * 0x532b78, 0x532b72, 0x532a84, 0x4f86a4, 0x558c7c, 0x540017, 0x4f85f8, 0x4f85e8, 0x4f85fc and
 * more; writes 0x532a9c. Register-for-register from the listing (0x466d6b..0x469478); labels are
 * the original addresses. */
static void run(Regs *r)
{
    r->eax = r->ebp - 0x4c;
    r->edx = 0x4ec1ec;
    r->ecx = 0x515be8;
    push(r, r->port->env.chain);
    wr32(r, r->eax, pop(r));
    r->port->env.chain = r->eax;
    r->ebx = 0;
    r->edi = rd32(r, 0x532a7c);
    wr32(r, r->ebp - 0x48, r->edx);
    wr32(r, r->ebp - 0x44, r->ecx);
    wr32(r, r->ebp - 0x40, r->ebx);
    wr32(r, 0x532a9c, r->ebx);
    if (r->edi != 0)
    {
        goto at_468bd1;
    }
    if (rd32(r, 0x532a80) != 0x1)
    {
        goto at_468bd1;
    }
    r->eax = 0;
    set_low16(&r->eax, rd16(r, 0x532b6c));
    wr32(r, r->ebp - 0x1c, r->eax);
    r->eax = 0;
    set_low16(&r->eax, rd16(r, 0x532b6e));
    wr32(r, r->ebp - 0x2c, r->eax);
    r->eax = 0;
    set_low16(&r->eax, rd16(r, 0x532b70));
    wr32(r, r->ebp - 0x20, r->eax);
    r->eax = 0;
    set_low16(&r->eax, rd16(r, 0x532b74));
    wr32(r, r->ebp - 0x28, r->eax);
    r->eax = 0;
    set_low16(&r->eax, rd16(r, 0x532b76));
    wr32(r, r->ebp - 0x30, r->eax);
    r->eax = 0;
    set_low16(&r->eax, rd16(r, 0x532b78));
    wr32(r, r->ebp - 0x18, r->eax);
    r->eax = 0;
    set_low16(&r->eax, rd16(r, r->ebp - 0x1c));
    set_low16(&r->edi, rd16(r, 0x532b72));
    call(r, 0x476650, 0);
    if (r->eax != 0x1)
    {
        goto at_468b8c;
    }
at_466e10:
    r->edi = 0;
at_466e12:
    r->edx = 0;
    wr32(r, r->ebp - 0x24, r->edx);
at_466e17:
    r->ecx = rd32(r, 0x532a84);
    if (r->ecx != 0x1)
    {
        goto at_466f7f;
    }
    r->eax = 0x180;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_466e44;
    }
    wr32(r, r->ebp - 0x40, r->ecx);
    wr32(r, r->ebp - 0x34, r->eax);
    r->esi = 0;
    call(r, 0x4b6350, 0);
    wr32(r, r->ebp - 0x40, r->esi);
at_466e44:
    r->esi = r->eax;
    push(r, 0x0);
    push(r, 0x447af0);
    push(r, 0x0);
    push(r, 0x0);
    r->eax = r->esi;
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = 0;
    r->edx = 0;
    call(r, 0x4adf20, 5);
    set_low16(&r->eax, rd16(r, 0x4f86a4));
    r->eax = r->eax - 1;
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    push(r, r->eax);
    r->eax = rd32(r, 0x558c7c);
    r->eax = rd32(r, r->eax + 0x4);
    r->edx = 0x50e528;
    r->eax = r->eax >> 0x1;
    r->ebx = rd32(r, 0x540017);
    r->eax = r->eax - 1;
    push(r, 0x0);
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    r->ecx = 0;
    push(r, r->eax);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x18);
    r->eax = r->esi;
    call(r, 0x4b65d0, 3);
    r->edx = 0x2;
    r->eax = r->esi;
    call(r, 0x4ac7b0, 0);
    wr8(r, r->esi + 0x52, 0x9);
    wr8(r, r->esi + 0x44, 0x9);
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
        goto at_466eed;
    }
    r->edx = 0x3;
    wr32(r, r->ebp - 0x34, r->eax);
    r->ecx = 0;
    wr32(r, r->ebp - 0x40, r->edx);
    call(r, 0x4b6350, 0);
    wr32(r, r->ebp - 0x40, r->ecx);
at_466eed:
    r->esi = r->eax;
    push(r, 0x0);
    push(r, 0x447af0);
    push(r, 0x0);
    push(r, 0x0);
    r->eax = r->esi;
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = 0;
    r->edx = 0;
    call(r, 0x4adf20, 5);
    set_low16(&r->eax, rd16(r, 0x4f86a4));
    r->eax = r->eax - 1;
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    r->ebx = rd32(r, 0x540017);
    push(r, r->eax);
    r->eax = rd32(r, 0x558c7c);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x18);
    set_low16(&r->edx, rd16(r, r->eax + 0x4));
    push(r, 0x0);
    r->edx = r->edx - 1;
    r->eax = rd32(r, r->eax + 0x4);
    r->edx = (uint32_t)(int32_t)(int16_t)(r->edx & 0xffff);
    r->eax = r->eax >> 0x1;
    push(r, r->edx);
    r->ecx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->edx = 0x50e529;
    r->eax = r->esi;
    call(r, 0x4b65d0, 3);
    r->edx = 0x2;
    r->eax = r->esi;
    call(r, 0x4ac7b0, 0);
    wr8(r, r->esi + 0x52, 0x9);
    wr8(r, r->esi + 0x44, 0x9);
    wr8(r, r->esi + 0x4e, 0x0);
    r->eax = r->esi;
    wr8(r, r->esi + 0x93, 0x1);
    r->edx = 0;
    wr32(r, r->esi + 0x4, 0x2);
    call(r, 0x4ac910, 0);
    r->eax = 0x54671c;
    r->edx = r->esi;
    r->ebx = 0;
    call(r, 0x4b5e70, 0);
    wr32(r, r->ebp - 0x40, r->ebx);
at_466f7f:
    r->eax = 0x15c;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_466fa2;
    }
    r->esi = 0x5;
    wr32(r, r->ebp - 0x34, r->eax);
    r->edx = 0;
    wr32(r, r->ebp - 0x40, r->esi);
    call(r, 0x4abd70, 0);
    wr32(r, r->ebp - 0x40, r->edx);
at_466fa2:
    r->esi = r->eax;
    push(r, 0x0);
    r->eax = rd32(r, 0x4f85f8);
    r->ecx = rd32(r, 0x4f85e8);
    r->edx = rd32(r, 0x4f85fc);
    r->ebx = rd32(r, 0x4f85ec);
    push(r, 0x448d30);
    r->eax = r->eax >> 0x1;
    r->edx = r->edx >> 0x1;
    push(r, 0x0);
    r->eax = r->eax + r->ecx;
    r->edx = r->edx + r->ebx;
    push(r, 0x0);
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->edx & 0xffff);
    r->ecx = 0;
    push(r, 0x0);
    r->edx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = r->esi;
    call(r, 0x4adf20, 5);
    r->edx = 0x8;
    r->eax = r->esi;
    call(r, 0x4ac7b0, 0);
    wr8(r, r->esi + 0x44, 0x10);
    wr8(r, r->esi + 0x95, 0x4);
    r->eax = r->esi;
    wr8(r, r->esi + 0x93, 0x1);
    r->edx = 0;
    wr16(r, r->esi + 0x48, 0xff9c);
    call(r, 0x4ac910, 0);
    set_low16(&r->ecx, rd16(r, 0x4f85ec));
    set_low16(&r->edx, rd16(r, 0x4f85fc));
    set_low16(&r->eax, rd16(r, 0x4f85e8));
    set_low16(&r->ebx, rd16(r, 0x4f85f8));
    wr8(r, r->esi + 0x8e, 0x3);
    r->ecx = r->ecx + r->edx;
    r->ebx = r->ebx + r->eax;
    wr16(r, r->esi + 0xa8, (r->eax & 0xffff));
    r->ebx = r->ebx - 1;
    set_low16(&r->edx, rd16(r, 0x4f85ec));
    wr16(r, r->esi + 0xaa, (r->ebx & 0xffff));
    r->ecx = r->ecx - 1;
    wr16(r, r->esi + 0xac, (r->edx & 0xffff));
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    wr16(r, r->esi + 0xae, (r->ecx & 0xffff));
    r->ecx = rd32(r, 0x4f85fc);
    r->edx = (uint32_t)(int32_t)(int16_t)(r->edx & 0xffff);
    push(r, r->ecx);
    r->ebx = r->edx;
    r->ecx = rd32(r, 0x4f85f8);
    r->edx = r->eax;
    r->eax = r->esi;
    wr32(r, r->esi + 0x124, 0x1);
    call(r, 0x4ae110, 1);
    r->eax = 0x54671c;
    r->edx = r->esi;
    wr16(r, r->esi + 0x148, 0x0);
    call(r, 0x4b5e70, 0);
    r->eax = 0x15c;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_4670b5;
    }
    r->ebx = 0x7;
    wr32(r, r->ebp - 0x34, r->eax);
    r->esi = 0;
    wr32(r, r->ebp - 0x40, r->ebx);
    call(r, 0x4abd70, 0);
    wr32(r, r->ebp - 0x40, r->esi);
at_4670b5:
    r->esi = r->eax;
    push(r, 0x0);
    r->eax = rd32(r, 0x4f85f8);
    r->edx = rd32(r, 0x4f85e8);
    r->ecx = rd32(r, 0x4f85ec);
    r->eax = r->eax >> 0x1;
    push(r, 0x448c20);
    r->eax = r->eax + r->edx;
    r->edx = rd32(r, 0x4f85fc);
    push(r, 0x0);
    r->edx = r->edx >> 0x1;
    push(r, 0x0);
    r->edx = r->edx + r->ecx;
    push(r, 0x0);
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->edx & 0xffff);
    r->ecx = 0;
    r->edx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = r->esi;
    call(r, 0x4adf20, 5);
    r->edx = 0x2;
    r->eax = r->esi;
    wr32(r, r->esi, 0x13);
    call(r, 0x4ac7b0, 0);
    r->eax = r->esi;
    r->edx = 0;
    wr8(r, r->esi + 0x44, 0x10);
    call(r, 0x4ac910, 0);
    wr8(r, r->esi + 0x8e, 0x3);
    set_low16(&r->eax, rd16(r, 0x4f85ec));
    wr32(r, r->esi + 0x150, 0x1);
    set_low16(&r->ecx, rd16(r, 0x4f85fc));
    wr32(r, r->esi + 0x138, 0x0);
    set_low16(&r->edx, rd16(r, 0x4f85f8));
    wr32(r, r->esi + 0x124, 0x1);
    set_low16(&r->ebx, rd16(r, 0x4f85ec));
    wr16(r, r->esi + 0x148, 0x0);
    r->ecx = r->ecx + r->eax;
    wr16(r, r->esi + 0xac, (r->ebx & 0xffff));
    set_low16(&r->eax, rd16(r, 0x4f85e8));
    r->ecx = r->ecx - 1;
    r->edx = r->edx + r->eax;
    wr16(r, r->esi + 0xa8, (r->eax & 0xffff));
    r->edx = r->edx - 1;
    r->eax = 0x54671c;
    wr16(r, r->esi + 0xaa, (r->edx & 0xffff));
    r->edx = r->esi;
    wr16(r, r->esi + 0xae, (r->ecx & 0xffff));
    call(r, 0x4b5e70, 0);
    r->eax = 0x15c;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_4671b1;
    }
    r->ebx = 0x9;
    wr32(r, r->ebp - 0x34, r->eax);
    r->esi = 0;
    wr32(r, r->ebp - 0x40, r->ebx);
    call(r, 0x4abd70, 0);
    wr32(r, r->ebp - 0x40, r->esi);
at_4671b1:
    r->esi = r->eax;
    push(r, 0x0);
    r->eax = rd32(r, 0x4f85f8);
    r->edx = rd32(r, 0x4f85e8);
    r->ecx = rd32(r, 0x4f85ec);
    r->eax = r->eax >> 0x1;
    push(r, 0x449090);
    r->eax = r->eax + r->edx;
    r->edx = rd32(r, 0x4f85fc);
    push(r, 0x0);
    r->edx = r->edx >> 0x1;
    push(r, 0x0);
    r->edx = r->edx + r->ecx;
    push(r, 0x0);
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->edx & 0xffff);
    r->ecx = 0;
    r->edx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = r->esi;
    call(r, 0x4adf20, 5);
    r->edx = 0x2;
    r->eax = r->esi;
    call(r, 0x4ac7b0, 0);
    r->eax = r->esi;
    r->edx = 0;
    call(r, 0x4ac910, 0);
    wr8(r, r->esi + 0x8e, 0x3);
    wr8(r, r->esi + 0x93, 0x1);
    wr8(r, r->esi + 0x95, 0x0);
    set_low16(&r->edx, rd16(r, 0x4f85ec));
    wr8(r, r->esi + 0x4e, 0x46);
    set_low16(&r->ebx, rd16(r, 0x4f85fc));
    wr32(r, r->esi + 0x138, 0x0);
    set_low16(&r->ecx, rd16(r, 0x4f85f8));
    wr32(r, r->esi + 0x124, 0x1);
    set_low16(&r->eax, rd16(r, 0x4f85e8));
    wr16(r, r->esi + 0x148, 0x0);
    r->edx = r->edx + r->ebx;
    wr16(r, r->esi + 0xa8, (r->eax & 0xffff));
    r->eax = 0x54671c;
    set_low16(&r->ebx, rd16(r, 0x4f85e8));
    r->edx = r->edx - 1;
    r->ebx = r->ebx + r->ecx;
    wr16(r, r->esi + 0xae, (r->edx & 0xffff));
    r->ebx = r->ebx - 1;
    set_low16(&r->ecx, rd16(r, 0x4f85ec));
    wr16(r, r->esi + 0xaa, (r->ebx & 0xffff));
    r->edx = r->esi;
    wr16(r, r->esi + 0xac, (r->ecx & 0xffff));
    call(r, 0x4b5e70, 0);
    r->eax = 0x15c;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_4672b3;
    }
    r->ebx = 0xb;
    wr32(r, r->ebp - 0x34, r->eax);
    r->esi = 0;
    wr32(r, r->ebp - 0x40, r->ebx);
    call(r, 0x4abd70, 0);
    wr32(r, r->ebp - 0x40, r->esi);
at_4672b3:
    r->esi = r->eax;
    push(r, 0x0);
    push(r, 0x44a610);
    r->ebx = rd32(r, 0x4f85ea);
    r->edx = rd32(r, 0x4f85e6);
    push(r, 0x0);
    r->eax = r->esi;
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    push(r, 0x0);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    call(r, 0x4adf20, 5);
    r->edx = 0x64;
    r->eax = r->esi;
    call(r, 0x4ac7d0, 0);
    r->eax = r->esi;
    r->edx = 0;
    call(r, 0x4ac910, 0);
    wr8(r, r->esi + 0x93, 0x1);
    r->edx = 0x544a18;
    wr8(r, r->esi + 0x95, 0x5);
    r->eax = r->esi;
    wr8(r, r->esi + 0x4e, 0x32);
    call(r, 0x4ac8d0, 0);
    r->edx = rd32(r, 0x4fbf24);
    r->eax = r->esi;
    call(r, 0x4ac710, 0);
    r->eax = r->esi;
    call(r, 0x4ac8a0, 0);
    wr32(r, r->esi + 0x138, 0x0);
    r->eax = rd32(r, 0x4f85e8);
    wr32(r, r->esi + 0x124, 0x0);
    wr32(r, r->esi + 0x58, r->eax);
    r->eax = rd32(r, 0x4f85ec);
    r->edx = r->esi;
    wr32(r, r->esi + 0x64, r->eax);
    r->eax = 0x54671c;
    wr16(r, r->esi + 0x148, 0x0);
    call(r, 0x4b5e70, 0);
    if (rd32(r, 0x532a7c) != 0x1)
    {
        goto at_468d80;
    }
    r->eax = 0x15c;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_46738d;
    }
    r->edi = 0xd;
    wr32(r, r->ebp - 0x34, r->eax);
    r->edx = 0;
    wr32(r, r->ebp - 0x40, r->edi);
    call(r, 0x4abd70, 0);
    wr32(r, r->ebp - 0x40, r->edx);
at_46738d:
    r->esi = r->eax;
    push(r, 0x0);
    push(r, 0x0);
    r->eax = rd32(r, 0x4f8618);
    push(r, 0x0);
    r->edx = rd32(r, 0x4f861c);
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->edx & 0xffff);
    push(r, 0x0);
    r->edx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = r->esi;
    call(r, 0x4adf20, 5);
    r->edx = 0x2;
    r->eax = r->esi;
    call(r, 0x4ac7b0, 0);
    r->eax = r->esi;
    r->edx = 0;
    call(r, 0x4ac910, 0);
    r->edx = 0x544a18;
    r->eax = r->esi;
    call(r, 0x4ac8d0, 0);
    r->edx = rd32(r, 0x4fbed0);
    r->eax = r->esi;
    r->ecx = 0;
    call(r, 0x4ac710, 0);
    r->eax = r->esi;
    r->ebx = 0;
    call(r, 0x4ac8a0, 0);
    r->edx = 0;
    wr8(r, r->esi + 0x52, 0x0);
    push(r, 0x0);
    wr8(r, r->esi + 0x94, 0x0);
    r->eax = r->esi;
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
        goto at_467445;
    }
    r->ecx = 0xf;
    wr32(r, r->ebp - 0x34, r->eax);
    r->ebx = 0;
    wr32(r, r->ebp - 0x40, r->ecx);
    call(r, 0x4abd70, 0);
    wr32(r, r->ebp - 0x40, r->ebx);
at_467445:
    r->esi = r->eax;
    push(r, 0x0);
    push(r, 0x0);
    r->eax = rd32(r, 0x4f8628);
    push(r, 0x0);
    r->edx = rd32(r, 0x4f862c);
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->edx & 0xffff);
    push(r, 0x0);
    r->edx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = r->esi;
    call(r, 0x4adf20, 5);
    r->edx = 0x2;
    r->eax = r->esi;
    call(r, 0x4ac7b0, 0);
    r->eax = r->esi;
    r->edx = 0;
    call(r, 0x4ac910, 0);
    r->edx = 0x544a18;
    r->eax = r->esi;
    call(r, 0x4ac8d0, 0);
    r->edx = rd32(r, 0x4fbee0);
    r->eax = r->esi;
    r->ecx = 0;
    call(r, 0x4ac710, 0);
    r->eax = r->esi;
    r->ebx = 0;
    call(r, 0x4ac8a0, 0);
    r->edx = 0;
    wr8(r, r->esi + 0x52, 0x0);
    push(r, 0x0);
    wr8(r, r->esi + 0x94, 0x0);
    r->eax = r->esi;
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
        goto at_4674fd;
    }
    r->esi = 0x11;
    wr32(r, r->ebp - 0x34, r->eax);
    r->edi = 0;
    wr32(r, r->ebp - 0x40, r->esi);
    call(r, 0x4abd70, 0);
    wr32(r, r->ebp - 0x40, r->edi);
at_4674fd:
    r->esi = r->eax;
    push(r, 0x0);
    push(r, 0x0);
    r->eax = rd32(r, 0x4f8620);
    push(r, 0x0);
    r->edx = rd32(r, 0x4f8624);
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->edx & 0xffff);
    push(r, 0x0);
    r->edx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = r->esi;
    call(r, 0x4adf20, 5);
    r->edx = 0x2;
    r->eax = r->esi;
    call(r, 0x4ac7b0, 0);
    r->edx = 0xa;
    r->eax = r->esi;
    call(r, 0x4ac470, 0);
    r->eax = r->esi;
    r->edx = 0;
    call(r, 0x4ac910, 0);
    r->edx = 0x544a18;
    r->eax = r->esi;
    call(r, 0x4ac8d0, 0);
    r->edx = rd32(r, 0x4fbed8);
    r->eax = r->esi;
    r->ecx = 0;
    call(r, 0x4ac710, 0);
    r->eax = r->esi;
    r->ebx = 0;
    call(r, 0x4ac8a0, 0);
    r->edx = 0;
    wr8(r, r->esi + 0x52, 0x0);
    push(r, 0x0);
    wr8(r, r->esi + 0x94, 0x0);
    r->eax = r->esi;
    wr32(r, r->esi + 0x124, 0x1);
    call(r, 0x4ae110, 1);
    r->eax = 0x54671c;
    r->edx = r->esi;
    wr32(r, r->esi + 0x13c, 0x0);
    call(r, 0x4b5e70, 0);
    r->eax = 0;
    wr32(r, r->ebp - 0x40, r->eax);
at_4675a3:
    r->eax = 0x15c;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_4675c6;
    }
    r->edx = 0x19;
    wr32(r, r->ebp - 0x34, r->eax);
    r->ecx = 0;
    wr32(r, r->ebp - 0x40, r->edx);
    call(r, 0x4abd70, 0);
    wr32(r, r->ebp - 0x40, r->ecx);
at_4675c6:
    r->esi = r->eax;
    push(r, 0x0);
    r->eax = rd32(r, 0x4f85f8);
    r->ebx = rd32(r, 0x4f85f0);
    r->edx = rd32(r, 0x4f85fc);
    r->edi = rd32(r, 0x4f85f4);
    r->ecx = 0;
    push(r, 0x448ed0);
    r->eax = r->eax >> 0x1;
    r->edx = r->edx >> 0x1;
    push(r, 0x0);
    r->eax = r->eax + r->ebx;
    r->edx = r->edx + r->edi;
    push(r, 0x0);
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->edx & 0xffff);
    push(r, 0x0);
    r->edx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = r->esi;
    call(r, 0x4adf20, 5);
    r->edx = 0x8;
    r->eax = r->esi;
    call(r, 0x4ac7b0, 0);
    wr8(r, r->esi + 0x44, 0x10);
    wr8(r, r->esi + 0x95, 0x4);
    r->eax = r->esi;
    wr8(r, r->esi + 0x93, 0x1);
    r->edx = 0;
    wr16(r, r->esi + 0x48, 0xff9c);
    call(r, 0x4ac910, 0);
    set_low16(&r->ecx, rd16(r, 0x4f85f4));
    set_low16(&r->edi, rd16(r, 0x4f85fc));
    set_low16(&r->ebx, rd16(r, 0x4f85f0));
    set_low16(&r->edx, rd16(r, 0x4f85f8));
    set_low16(&r->eax, rd16(r, 0x4f85f0));
    r->ecx = r->ecx + r->edi;
    r->ebx = r->ebx + r->edx;
    wr16(r, r->esi + 0xa8, (r->eax & 0xffff));
    r->ebx = r->ebx - 1;
    set_low16(&r->edx, rd16(r, 0x4f85f4));
    wr16(r, r->esi + 0xaa, (r->ebx & 0xffff));
    r->ecx = r->ecx - 1;
    wr16(r, r->esi + 0xac, (r->edx & 0xffff));
    wr16(r, r->esi + 0xae, (r->ecx & 0xffff));
    r->ecx = rd32(r, 0x4f85fc);
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->edx & 0xffff);
    push(r, r->ecx);
    r->edx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->ecx = rd32(r, 0x4f85f8);
    r->eax = r->esi;
    wr8(r, r->esi + 0x8e, 0x3);
    call(r, 0x4ae110, 1);
    r->eax = 0x54671c;
    wr32(r, r->esi + 0x124, 0x1);
    r->edx = r->esi;
    wr16(r, r->esi + 0x148, 0x1);
    call(r, 0x4b5e70, 0);
    r->eax = 0x15c;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_4676de;
    }
    r->ebx = 0x1b;
    wr32(r, r->ebp - 0x34, r->eax);
    r->esi = 0;
    wr32(r, r->ebp - 0x40, r->ebx);
    call(r, 0x4abd70, 0);
    wr32(r, r->ebp - 0x40, r->esi);
at_4676de:
    r->esi = r->eax;
    push(r, 0x0);
    r->eax = rd32(r, 0x4f85f8);
    r->edi = rd32(r, 0x4f85f0);
    r->edx = rd32(r, 0x4f85fc);
    r->ecx = rd32(r, 0x4f85f4);
    push(r, 0x448ca0);
    r->eax = r->eax >> 0x1;
    r->edx = r->edx >> 0x1;
    push(r, 0x0);
    r->eax = r->eax + r->edi;
    r->edx = r->edx + r->ecx;
    push(r, 0x0);
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->edx & 0xffff);
    r->ecx = 0;
    push(r, 0x0);
    r->edx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = r->esi;
    call(r, 0x4adf20, 5);
    r->edx = 0x2;
    r->eax = r->esi;
    wr32(r, r->esi, 0x14);
    call(r, 0x4ac7b0, 0);
    r->eax = r->esi;
    r->edx = 0;
    wr8(r, r->esi + 0x44, 0x10);
    call(r, 0x4ac910, 0);
    wr32(r, r->esi + 0x150, 0x1);
    set_low16(&r->edx, rd16(r, 0x4f85f4));
    wr8(r, r->esi + 0x8e, 0x3);
    set_low16(&r->ebx, rd16(r, 0x4f85fc));
    wr32(r, r->esi + 0x138, 0x0);
    set_low16(&r->eax, rd16(r, 0x4f85f0));
    wr32(r, r->esi + 0x124, 0x1);
    set_low16(&r->ecx, rd16(r, 0x4f85f8));
    wr16(r, r->esi + 0x148, 0x1);
    r->edx = r->edx + r->ebx;
    r->eax = r->eax + r->ecx;
    set_low16(&r->ecx, rd16(r, 0x4f85f0));
    r->eax = r->eax - 1;
    wr16(r, r->esi + 0xa8, (r->ecx & 0xffff));
    r->edx = r->edx - 1;
    wr16(r, r->esi + 0xaa, (r->eax & 0xffff));
    set_low16(&r->ebx, rd16(r, 0x4f85f4));
    wr16(r, r->esi + 0xae, (r->edx & 0xffff));
    r->eax = 0x54671c;
    r->edx = r->esi;
    wr16(r, r->esi + 0xac, (r->ebx & 0xffff));
    call(r, 0x4b5e70, 0);
    r->eax = 0x15c;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_4677e2;
    }
    r->ebx = 0x1d;
    wr32(r, r->ebp - 0x34, r->eax);
    r->esi = 0;
    wr32(r, r->ebp - 0x40, r->ebx);
    call(r, 0x4abd70, 0);
    wr32(r, r->ebp - 0x40, r->esi);
at_4677e2:
    r->esi = r->eax;
    push(r, 0x0);
    r->eax = rd32(r, 0x4f85f8);
    r->edi = rd32(r, 0x4f85f0);
    r->edx = rd32(r, 0x4f85fc);
    r->ecx = rd32(r, 0x4f85f4);
    push(r, 0x449180);
    r->eax = r->eax >> 0x1;
    r->edx = r->edx >> 0x1;
    push(r, 0x0);
    r->eax = r->eax + r->edi;
    r->edx = r->edx + r->ecx;
    push(r, 0x0);
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->edx & 0xffff);
    r->ecx = 0;
    push(r, 0x0);
    r->edx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = r->esi;
    call(r, 0x4adf20, 5);
    r->edx = 0x2;
    r->eax = r->esi;
    call(r, 0x4ac7b0, 0);
    r->eax = r->esi;
    r->edx = 0;
    call(r, 0x4ac910, 0);
    wr8(r, r->esi + 0x8e, 0x3);
    wr8(r, r->esi + 0x93, 0x1);
    set_low16(&r->ebx, rd16(r, 0x4f85f4));
    wr8(r, r->esi + 0x95, 0x0);
    set_low16(&r->edi, rd16(r, 0x4f85fc));
    wr8(r, r->esi + 0x4e, 0x46);
    set_low16(&r->ecx, rd16(r, 0x4f85f0));
    wr32(r, r->esi + 0x138, 0x0);
    set_low16(&r->edx, rd16(r, 0x4f85f8));
    wr32(r, r->esi + 0x124, 0x1);
    set_low16(&r->eax, rd16(r, 0x4f85f0));
    wr16(r, r->esi + 0x148, 0x1);
    r->ebx = r->ebx + r->edi;
    r->ecx = r->ecx + r->edx;
    wr16(r, r->esi + 0xa8, (r->eax & 0xffff));
    r->eax = 0x54671c;
    r->ecx = r->ecx - 1;
    set_low16(&r->edx, rd16(r, 0x4f85f4));
    wr16(r, r->esi + 0xaa, (r->ecx & 0xffff));
    r->ebx = r->ebx - 1;
    wr16(r, r->esi + 0xac, (r->edx & 0xffff));
    r->edx = r->esi;
    wr16(r, r->esi + 0xae, (r->ebx & 0xffff));
    call(r, 0x4b5e70, 0);
    r->eax = 0x15c;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_4678e4;
    }
    r->ebx = 0x1f;
    wr32(r, r->ebp - 0x34, r->eax);
    r->esi = 0;
    wr32(r, r->ebp - 0x40, r->ebx);
    call(r, 0x4abd70, 0);
    wr32(r, r->ebp - 0x40, r->esi);
at_4678e4:
    r->esi = r->eax;
    push(r, 0x0);
    push(r, 0x44a610);
    r->ebx = rd32(r, 0x4f85f2);
    r->edx = rd32(r, 0x4f85ee);
    push(r, 0x0);
    r->eax = r->esi;
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    push(r, 0x0);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    call(r, 0x4adf20, 5);
    r->edx = 0x64;
    r->eax = r->esi;
    call(r, 0x4ac7d0, 0);
    r->eax = r->esi;
    r->edx = 0;
    call(r, 0x4ac910, 0);
    wr8(r, r->esi + 0x93, 0x1);
    r->edx = 0x544a18;
    wr8(r, r->esi + 0x95, 0x5);
    r->eax = r->esi;
    wr8(r, r->esi + 0x4e, 0x32);
    call(r, 0x4ac8d0, 0);
    r->edx = rd32(r, 0x4fbf24);
    r->eax = r->esi;
    call(r, 0x4ac710, 0);
    r->eax = r->esi;
    call(r, 0x4ac8a0, 0);
    wr32(r, r->esi + 0x138, 0x0);
    r->eax = rd32(r, 0x4f85f0);
    wr32(r, r->esi + 0x124, 0x0);
    wr32(r, r->esi + 0x58, r->eax);
    r->eax = rd32(r, 0x4f85f4);
    r->edx = r->esi;
    wr32(r, r->esi + 0x64, r->eax);
    r->eax = 0x54671c;
    wr16(r, r->esi + 0x148, 0x1);
    call(r, 0x4b5e70, 0);
    if (rd32(r, 0x532a8c) != 0x0)
    {
        goto at_468f7b;
    }
at_46799b:
    r->eax = 0x15c;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_4679be;
    }
    r->esi = 0x21;
    wr32(r, r->ebp - 0x34, r->eax);
    r->edi = 0;
    wr32(r, r->ebp - 0x40, r->esi);
    call(r, 0x4abd70, 0);
    wr32(r, r->ebp - 0x40, r->edi);
at_4679be:
    r->esi = r->eax;
    push(r, 0x0);
    push(r, 0x0);
    r->eax = rd32(r, 0x4f8630);
    push(r, 0x0);
    r->edx = rd32(r, 0x4f8634);
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->edx & 0xffff);
    push(r, 0x0);
    r->edx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = r->esi;
    call(r, 0x4adf20, 5);
    r->edx = 0x2;
    r->eax = r->esi;
    call(r, 0x4ac7b0, 0);
    r->eax = r->esi;
    r->edx = 0;
    call(r, 0x4ac910, 0);
    r->edx = 0x544a18;
    r->eax = r->esi;
    call(r, 0x4ac8d0, 0);
    r->edx = rd32(r, 0x4fbee8);
    r->eax = r->esi;
    r->ecx = 0;
    call(r, 0x4ac710, 0);
    r->eax = r->esi;
    r->ebx = 0;
    call(r, 0x4ac8a0, 0);
    r->edx = 0;
    wr8(r, r->esi + 0x52, 0x0);
    push(r, 0x0);
    wr8(r, r->esi + 0x94, 0x0);
    r->eax = r->esi;
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
        goto at_467a76;
    }
    r->edx = 0x23;
    wr32(r, r->ebp - 0x34, r->eax);
    r->ecx = 0;
    wr32(r, r->ebp - 0x40, r->edx);
    call(r, 0x4abd70, 0);
    wr32(r, r->ebp - 0x40, r->ecx);
at_467a76:
    r->esi = r->eax;
    push(r, 0x0);
    push(r, 0x0);
    r->eax = rd32(r, 0x4f8640);
    push(r, 0x0);
    r->edx = rd32(r, 0x4f8644);
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->edx & 0xffff);
    push(r, 0x0);
    r->edx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = r->esi;
    call(r, 0x4adf20, 5);
    r->edx = 0x2;
    r->eax = r->esi;
    call(r, 0x4ac7b0, 0);
    r->eax = r->esi;
    r->edx = 0;
    call(r, 0x4ac910, 0);
    r->edx = 0x544a18;
    r->eax = r->esi;
    call(r, 0x4ac8d0, 0);
    r->edx = rd32(r, 0x4fbef8);
    r->eax = r->esi;
    r->ecx = 0;
    call(r, 0x4ac710, 0);
    r->eax = r->esi;
    r->ebx = 0;
    call(r, 0x4ac8a0, 0);
    r->edx = 0;
    wr8(r, r->esi + 0x52, 0x0);
    push(r, 0x0);
    wr8(r, r->esi + 0x94, 0x0);
    r->eax = r->esi;
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
        goto at_467b2e;
    }
    r->ebx = 0x25;
    wr32(r, r->ebp - 0x34, r->eax);
    r->esi = 0;
    wr32(r, r->ebp - 0x40, r->ebx);
    call(r, 0x4abd70, 0);
    wr32(r, r->ebp - 0x40, r->esi);
at_467b2e:
    r->esi = r->eax;
    push(r, 0x0);
    push(r, 0x0);
    r->eax = rd32(r, 0x4f8638);
    push(r, 0x0);
    r->edx = rd32(r, 0x4f863c);
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->edx & 0xffff);
    push(r, 0x0);
    r->edx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = r->esi;
    call(r, 0x4adf20, 5);
    r->edx = 0x2;
    r->eax = r->esi;
    call(r, 0x4ac7b0, 0);
    r->edx = 0xa;
    r->eax = r->esi;
    call(r, 0x4ac470, 0);
    r->eax = r->esi;
    r->edx = 0;
    call(r, 0x4ac910, 0);
    r->edx = 0x544a18;
    r->eax = r->esi;
    r->edi = 0;
    call(r, 0x4ac8d0, 0);
    r->edx = rd32(r, 0x4fbef0);
    r->eax = r->esi;
    r->ecx = 0;
    call(r, 0x4ac710, 0);
    r->eax = r->esi;
    r->ebx = 0;
    call(r, 0x4ac8a0, 0);
    r->edx = 0;
    wr8(r, r->esi + 0x52, 0x0);
    push(r, 0x0);
    wr8(r, r->esi + 0x94, 0x0);
    r->eax = r->esi;
    wr32(r, r->esi + 0x124, 0x1);
    call(r, 0x4ae110, 1);
    r->eax = 0x54671c;
    r->edx = r->esi;
    wr32(r, r->esi + 0x13c, 0x0);
    call(r, 0x4b5e70, 0);
    wr32(r, r->ebp - 0x40, r->edi);
at_467bd4:
    r->eax = 0x15c;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_467bf7;
    }
    r->edx = 0x2d;
    wr32(r, r->ebp - 0x34, r->eax);
    r->ecx = 0;
    wr32(r, r->ebp - 0x40, r->edx);
    call(r, 0x4abd70, 0);
    wr32(r, r->ebp - 0x40, r->ecx);
at_467bf7:
    r->esi = r->eax;
    push(r, 0x0);
    push(r, 0x4492f0);
    r->eax = rd32(r, 0x4f8608);
    push(r, 0x0);
    r->edx = rd32(r, 0x4f860c);
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->edx & 0xffff);
    push(r, 0x0);
    r->edx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = r->esi;
    call(r, 0x4adf20, 5);
    r->edx = 0x2;
    r->eax = r->esi;
    call(r, 0x4ac7b0, 0);
    r->eax = r->esi;
    r->edx = 0;
    call(r, 0x4ac910, 0);
    push(r, 0x0);
    set_low16(&r->ecx, rd16(r, 0x4f860c));
    set_low16(&r->ebx, rd16(r, 0x4f8614));
    wr8(r, r->esi + 0x8e, 0x3);
    set_low16(&r->edx, rd16(r, 0x4f8608));
    wr16(r, r->esi + 0x48, 0x0);
    set_low16(&r->edi, rd16(r, 0x4f8610));
    wr16(r, r->esi + 0x4a, 0x0);
    set_low16(&r->eax, rd16(r, 0x4f8608));
    wr16(r, r->esi + 0x4c, 0x1);
    r->ecx = r->ecx + r->ebx;
    r->edx = r->edx + r->edi;
    wr16(r, r->esi + 0xa8, (r->eax & 0xffff));
    r->edx = r->edx - 1;
    set_low16(&r->ebx, rd16(r, 0x4f860c));
    wr16(r, r->esi + 0xaa, (r->edx & 0xffff));
    r->ecx = r->ecx - 1;
    wr16(r, r->esi + 0xac, (r->ebx & 0xffff));
    r->eax = r->esi;
    wr16(r, r->esi + 0xae, (r->ecx & 0xffff));
    r->ecx = 0;
    r->ebx = 0;
    r->edx = 0;
    wr32(r, r->esi + 0x124, 0x1);
    call(r, 0x4ae110, 1);
    r->eax = 0x54671c;
    wr32(r, r->esi + 0x13c, 0x0);
    r->edx = r->esi;
    wr32(r, r->esi + 0x7c, 0xffffffffu);
    call(r, 0x4b5e70, 0);
    if (rd32(r, 0x532a8c) != 0x0)
    {
        goto at_46918c;
    }
at_467cdc:
    r->eax = 0x15c;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_467cff;
    }
    r->esi = 0x2f;
    wr32(r, r->ebp - 0x34, r->eax);
    r->edi = 0;
    wr32(r, r->ebp - 0x40, r->esi);
    call(r, 0x4abd70, 0);
    wr32(r, r->ebp - 0x40, r->edi);
at_467cff:
    r->esi = r->eax;
    push(r, 0x0);
    push(r, 0x0);
    r->eax = rd32(r, 0x4f8648);
    push(r, 0x0);
    r->edx = rd32(r, 0x4f864c);
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->edx & 0xffff);
    push(r, 0x0);
    r->edx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = r->esi;
    call(r, 0x4adf20, 5);
    r->edx = 0x2;
    r->eax = r->esi;
    call(r, 0x4ac7b0, 0);
    r->eax = r->esi;
    r->edx = 0;
    call(r, 0x4ac910, 0);
    r->edx = 0x544a18;
    r->eax = r->esi;
    call(r, 0x4ac8d0, 0);
    r->edx = rd32(r, 0x4fbf00);
    r->eax = r->esi;
    r->ecx = 0;
    call(r, 0x4ac710, 0);
    r->eax = r->esi;
    r->ebx = 0;
    call(r, 0x4ac8a0, 0);
    r->edx = 0;
    wr8(r, r->esi + 0x52, 0x0);
    push(r, 0x0);
    wr8(r, r->esi + 0x94, 0x0);
    r->eax = r->esi;
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
        goto at_467db7;
    }
    r->edx = 0x31;
    wr32(r, r->ebp - 0x34, r->eax);
    r->ecx = 0;
    wr32(r, r->ebp - 0x40, r->edx);
    call(r, 0x4abd70, 0);
    wr32(r, r->ebp - 0x40, r->ecx);
at_467db7:
    r->esi = r->eax;
    push(r, 0x0);
    push(r, 0x0);
    r->eax = rd32(r, 0x4f8658);
    push(r, 0x0);
    r->edx = rd32(r, 0x4f865c);
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->edx & 0xffff);
    push(r, 0x0);
    r->edx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = r->esi;
    call(r, 0x4adf20, 5);
    r->edx = 0x2;
    r->eax = r->esi;
    call(r, 0x4ac7b0, 0);
    r->eax = r->esi;
    r->edx = 0;
    call(r, 0x4ac910, 0);
    r->edx = 0x544a18;
    r->eax = r->esi;
    call(r, 0x4ac8d0, 0);
    r->edx = rd32(r, 0x4fbf10);
    r->eax = r->esi;
    r->ecx = 0;
    call(r, 0x4ac710, 0);
    r->eax = r->esi;
    r->ebx = 0;
    call(r, 0x4ac8a0, 0);
    r->edx = 0;
    wr8(r, r->esi + 0x52, 0x0);
    push(r, 0x0);
    wr8(r, r->esi + 0x94, 0x0);
    r->eax = r->esi;
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
        goto at_467e6f;
    }
    r->ebx = 0x33;
    wr32(r, r->ebp - 0x34, r->eax);
    r->esi = 0;
    wr32(r, r->ebp - 0x40, r->ebx);
    call(r, 0x4abd70, 0);
    wr32(r, r->ebp - 0x40, r->esi);
at_467e6f:
    r->esi = r->eax;
    push(r, 0x0);
    push(r, 0x0);
    r->eax = rd32(r, 0x4f8650);
    push(r, 0x0);
    r->edx = rd32(r, 0x4f8654);
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->edx & 0xffff);
    push(r, 0x0);
    r->edx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = r->esi;
    call(r, 0x4adf20, 5);
    r->edx = 0x2;
    r->eax = r->esi;
    call(r, 0x4ac7b0, 0);
    r->edx = 0xa;
    r->eax = r->esi;
    call(r, 0x4ac470, 0);
    r->eax = r->esi;
    r->edx = 0;
    call(r, 0x4ac910, 0);
    r->edx = 0x544a18;
    r->eax = r->esi;
    r->edi = 0;
    call(r, 0x4ac8d0, 0);
    r->edx = rd32(r, 0x4fbf08);
    r->eax = r->esi;
    r->ecx = 0;
    call(r, 0x4ac710, 0);
    r->eax = r->esi;
    r->ebx = 0;
    call(r, 0x4ac8a0, 0);
    r->edx = 0;
    wr8(r, r->esi + 0x52, 0x0);
    push(r, 0x0);
    wr8(r, r->esi + 0x94, 0x0);
    r->eax = r->esi;
    wr32(r, r->esi + 0x124, 0x1);
    call(r, 0x4ae110, 1);
    r->eax = 0x54671c;
    r->edx = r->esi;
    wr32(r, r->esi + 0x13c, 0x0);
    call(r, 0x4b5e70, 0);
    wr32(r, r->ebp - 0x40, r->edi);
at_467f15:
    r->eax = 0x180;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_467f38;
    }
    r->edx = 0x3b;
    wr32(r, r->ebp - 0x34, r->eax);
    r->ecx = 0;
    wr32(r, r->ebp - 0x40, r->edx);
    call(r, 0x4b6350, 0);
    wr32(r, r->ebp - 0x40, r->ecx);
at_467f38:
    r->esi = r->eax;
    push(r, 0x0);
    push(r, 0x44a6d0);
    push(r, 0x0);
    push(r, 0x0);
    r->eax = r->esi;
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = 0;
    r->edx = 0;
    call(r, 0x4adf20, 5);
    set_low16(&r->eax, rd16(r, 0x4f860c));
    set_low16(&r->eax, (r->eax & 0xffff) + rd16(r, 0x4f8614));
    r->eax = r->eax - 1;
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    push(r, r->eax);
    r->eax = rd32(r, 0x4f860a);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    set_low16(&r->ebx, rd16(r, 0x4f8610));
    push(r, r->eax);
    set_low16(&r->eax, rd16(r, 0x4f8608));
    r->ecx = rd32(r, 0x4f8606);
    r->eax = r->eax + r->ebx;
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    r->eax = r->eax - 1;
    r->edx = 0x50e52a;
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    r->ebx = rd32(r, 0x540015);
    push(r, r->eax);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x18);
    r->eax = r->esi;
    call(r, 0x4b65d0, 3);
    set_low16(&r->eax, rd16(r, 0x4f860c));
    set_low16(&r->eax, (r->eax & 0xffff) + rd16(r, 0x4f8614));
    r->eax = r->eax - 1;
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    set_low16(&r->edx, rd16(r, 0x4f8610));
    push(r, r->eax);
    set_low16(&r->eax, rd16(r, 0x4f8608));
    r->ecx = rd32(r, 0x4f860a);
    r->eax = r->eax + r->edx;
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    r->eax = r->eax - 1;
    r->edx = rd32(r, 0x4f8606);
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = r->esi;
    call(r, 0x4b6690, 1);
    r->edx = 0x8;
    r->eax = r->esi;
    call(r, 0x4b6530, 0);
    r->edx = 0xffffffb0u;
    r->eax = r->esi;
    call(r, 0x4b6540, 0);
    r->eax = r->esi;
    r->edx = 0xffffffb0u;
    call(r, 0x4b65b0, 0);
    r->eax = r->esi;
    call(r, 0x4b6550, 0);
    r->edx = 0x2;
    r->eax = r->esi;
    call(r, 0x4ac7b0, 0);
    wr8(r, r->esi + 0x44, 0x0);
    r->edi = r->esi;
    wr8(r, r->esi + 0x93, 0x1);
    r->eax = rd32(r, 0x4f7bb0);
    wr8(r, r->esi + 0x4e, 0x32);
    r->ebx = rd32(r, 0x532a80);
    wr32(r, r->esi + 0x14c, r->eax);
    r->eax = 0x1;
    wr16(r, r->esi + 0x172, 0x1);
    if (r->ebx != r->eax)
    {
        goto at_469372;
    }
at_468048:
    wr8(r, r->edi + 0x52, 0x1);
    wr8(r, r->edi + 0x94, 0x0);
    wr8(r, r->edi + 0x95, 0x0);
at_46805a:
    r->eax = r->edi;
    r->edx = 0;
    call(r, 0x4ac910, 0);
    r->eax = 0x54671c;
    r->edx = r->edi;
    call(r, 0x4b5e70, 0);
    r->eax = 0x16c;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_468092;
    }
    r->edi = 0x3d;
    wr32(r, r->ebp - 0x34, r->eax);
    r->edx = 0;
    wr32(r, r->ebp - 0x40, r->edi);
    call(r, 0x429670, 0);
    wr32(r, r->ebp - 0x40, r->edx);
at_468092:
    r->esi = r->eax;
    push(r, 0x0);
    push(r, 0x44a570);
    r->ebx = rd32(r, 0x4f8662);
    r->edx = rd32(r, 0x4f865e);
    push(r, 0x0);
    r->eax = r->esi;
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    push(r, 0x0);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    call(r, 0x4adf20, 5);
    r->eax = rd32(r, 0x4f8668);
    r->edx = rd32(r, 0x4f866c);
    r->ecx = rd32(r, 0x4f867c);
    r->ebx = rd32(r, 0x4f8662);
    push(r, r->ecx);
    wr32(r, r->esi + 0x164, r->eax);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    wr32(r, r->esi + 0x168, r->edx);
    r->ecx = rd32(r, 0x4f8678);
    r->edx = rd32(r, 0x4f865e);
    r->eax = r->esi;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    wr32(r, r->esi + 0x124, 0x1);
    call(r, 0x4ae110, 1);
    r->eax = 0x54671c;
    r->edx = r->esi;
    call(r, 0x4b5e70, 0);
    r->eax = 0x16c;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_468132;
    }
    r->ebx = 0x3f;
    wr32(r, r->ebp - 0x34, r->eax);
    r->esi = 0;
    wr32(r, r->ebp - 0x40, r->ebx);
    call(r, 0x429670, 0);
    wr32(r, r->ebp - 0x40, r->esi);
at_468132:
    r->esi = r->eax;
    push(r, 0x0);
    push(r, 0x44a5c0);
    r->ebx = rd32(r, 0x4f8672);
    r->edx = rd32(r, 0x4f866e);
    push(r, 0x0);
    r->eax = r->esi;
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    push(r, 0x0);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    call(r, 0x4adf20, 5);
    r->edx = rd32(r, 0x4f8668);
    r->eax = rd32(r, 0x4f866c);
    r->edi = rd32(r, 0x4f867c);
    r->ecx = rd32(r, 0x4f8678);
    r->ebx = rd32(r, 0x4f8672);
    wr32(r, r->esi + 0x160, 0x0);
    push(r, r->edi);
    wr32(r, r->esi + 0x164, r->edx);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    wr32(r, r->esi + 0x168, r->eax);
    r->edx = rd32(r, 0x4f866e);
    r->eax = r->esi;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    wr32(r, r->esi + 0x124, 0x1);
    call(r, 0x4ae110, 1);
    r->eax = 0x54671c;
    r->edx = r->esi;
    call(r, 0x4b5e70, 0);
    r->eax = 0x180;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_4681dc;
    }
    r->edx = 0x41;
    wr32(r, r->ebp - 0x34, r->eax);
    r->ecx = 0;
    wr32(r, r->ebp - 0x40, r->edx);
    call(r, 0x4b6350, 0);
    wr32(r, r->ebp - 0x40, r->ecx);
at_4681dc:
    r->esi = r->eax;
    push(r, 0x0);
    push(r, 0x44aec0);
    push(r, 0x0);
    push(r, 0x0);
    r->eax = r->esi;
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = 0;
    r->edx = 0;
    call(r, 0x4adf20, 5);
    r->eax = rd32(r, 0x4f867e);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    push(r, r->eax);
    r->edx = 0x50e52d;
    r->ecx = rd32(r, 0x4f8696);
    push(r, r->eax);
    r->eax = rd32(r, 0x4f869a);
    r->ebx = rd32(r, 0x4f9bfd);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    push(r, r->eax);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x18);
    r->eax = r->esi;
    call(r, 0x4b65d0, 3);
    r->edx = 0x2;
    r->eax = r->esi;
    call(r, 0x4ac7b0, 0);
    r->edx = 0x64;
    r->eax = r->esi;
    call(r, 0x4ac860, 0);
    r->eax = rd32(r, 0x4f86e4);
    r->ecx = rd32(r, 0x4f86e0);
    wr8(r, r->esi + 0x44, 0x8);
    r->ebx = rd32(r, 0x4f86da);
    wr8(r, r->esi + 0x4e, 0x32);
    r->edx = rd32(r, 0x4f86d6);
    wr32(r, r->esi + 0x7c, 0x0);
    r->eax = r->eax >> 0x1;
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    push(r, r->eax);
    r->eax = r->esi;
    wr32(r, r->esi + 0x124, 0x1);
    call(r, 0x4ae110, 1);
    wr8(r, r->esi + 0x93, 0x1);
    r->eax = 0x54671c;
    wr8(r, r->esi + 0x4e, 0x5a);
    r->edx = r->esi;
    wr8(r, r->esi + 0x95, 0x1);
    call(r, 0x4b5e70, 0);
    r->eax = 0x180;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_4682c2;
    }
    r->ebx = 0x43;
    wr32(r, r->ebp - 0x34, r->eax);
    r->esi = 0;
    wr32(r, r->ebp - 0x40, r->ebx);
    call(r, 0x4b6350, 0);
    wr32(r, r->ebp - 0x40, r->esi);
at_4682c2:
    r->esi = r->eax;
    push(r, 0x0);
    push(r, 0x44b050);
    push(r, 0x0);
    push(r, 0x0);
    r->eax = r->esi;
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = 0;
    r->edx = 0;
    call(r, 0x4adf20, 5);
    r->eax = rd32(r, 0x4f8682);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    push(r, r->eax);
    r->edx = 0x50e52e;
    r->ecx = rd32(r, 0x4f8696);
    push(r, r->eax);
    r->eax = rd32(r, 0x4f869a);
    r->ebx = rd32(r, 0x4f9bfd);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    push(r, r->eax);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x18);
    r->eax = r->esi;
    call(r, 0x4b65d0, 3);
    r->edx = 0x2;
    r->eax = r->esi;
    call(r, 0x4ac7b0, 0);
    r->eax = rd32(r, 0x4f86e4);
    r->ecx = rd32(r, 0x4f86e0);
    r->edi = rd32(r, 0x4f86dc);
    r->edx = rd32(r, 0x4f86d6);
    wr8(r, r->esi + 0x44, 0x8);
    r->eax = r->eax >> 0x1;
    wr8(r, r->esi + 0x4e, 0x32);
    push(r, r->eax);
    r->eax = r->eax + r->edi;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = r->esi;
    wr32(r, r->esi + 0x124, 0x1);
    call(r, 0x4ae110, 1);
    wr8(r, r->esi + 0x93, 0x1);
    r->eax = 0x54671c;
    wr8(r, r->esi + 0x4e, 0x5a);
    r->edx = r->esi;
    wr8(r, r->esi + 0x95, 0x1);
    call(r, 0x4b5e70, 0);
    r->eax = 0x180;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_468397;
    }
    r->edx = 0x45;
    wr32(r, r->ebp - 0x34, r->eax);
    r->ecx = 0;
    wr32(r, r->ebp - 0x40, r->edx);
    call(r, 0x4b6350, 0);
    wr32(r, r->ebp - 0x40, r->ecx);
at_468397:
    r->esi = r->eax;
    push(r, 0x0);
    push(r, 0x44b170);
    push(r, 0x0);
    push(r, 0x0);
    r->eax = r->esi;
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = 0;
    r->edx = 0;
    call(r, 0x4adf20, 5);
    r->eax = rd32(r, 0x4f868e);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    push(r, r->eax);
    r->edx = 0x50e52f;
    r->ecx = rd32(r, 0x4f8696);
    push(r, r->eax);
    r->eax = rd32(r, 0x4f869a);
    r->ebx = rd32(r, 0x4f9bfd);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    push(r, r->eax);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x18);
    r->eax = r->esi;
    call(r, 0x4b65d0, 3);
    r->edx = 0x2;
    r->eax = r->esi;
    call(r, 0x4ac7b0, 0);
    r->edx = 0x44c;
    r->eax = r->esi;
    call(r, 0x4ac860, 0);
    r->eax = rd32(r, 0x4f86f4);
    r->ecx = rd32(r, 0x4f86f0);
    wr8(r, r->esi + 0x44, 0x8);
    r->ebx = rd32(r, 0x4f86ea);
    wr8(r, r->esi + 0x4e, 0x32);
    r->edx = rd32(r, 0x4f86e6);
    wr32(r, r->esi + 0x7c, 0x0);
    r->eax = r->eax >> 0x1;
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    push(r, r->eax);
    r->eax = r->esi;
    wr32(r, r->esi + 0x124, 0x1);
    call(r, 0x4ae110, 1);
    wr8(r, r->esi + 0x93, 0x1);
    r->eax = 0x54671c;
    wr8(r, r->esi + 0x4e, 0x5a);
    r->edx = r->esi;
    wr8(r, r->esi + 0x95, 0x1);
    call(r, 0x4b5e70, 0);
    r->eax = 0x180;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_46847d;
    }
    r->ebx = 0x47;
    wr32(r, r->ebp - 0x34, r->eax);
    r->esi = 0;
    wr32(r, r->ebp - 0x40, r->ebx);
    call(r, 0x4b6350, 0);
    wr32(r, r->ebp - 0x40, r->esi);
at_46847d:
    r->esi = r->eax;
    push(r, 0x0);
    push(r, 0x44b340);
    push(r, 0x0);
    push(r, 0x0);
    r->eax = r->esi;
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = 0;
    r->edx = 0;
    call(r, 0x4adf20, 5);
    r->eax = rd32(r, 0x4f8692);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    push(r, r->eax);
    r->edx = 0x50e530;
    r->ecx = rd32(r, 0x4f8696);
    push(r, r->eax);
    r->eax = rd32(r, 0x4f869a);
    r->ebx = rd32(r, 0x4f9bfd);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    push(r, r->eax);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x18);
    r->eax = r->esi;
    call(r, 0x4b65d0, 3);
    r->edx = 0x2;
    r->eax = r->esi;
    call(r, 0x4ac7b0, 0);
    r->eax = rd32(r, 0x4f86f4);
    r->ecx = rd32(r, 0x4f86f0);
    r->edi = rd32(r, 0x4f86ec);
    r->edx = rd32(r, 0x4f86e6);
    wr8(r, r->esi + 0x44, 0x8);
    r->eax = r->eax >> 0x1;
    wr8(r, r->esi + 0x4e, 0x32);
    push(r, r->eax);
    r->eax = r->eax + r->edi;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = r->esi;
    wr32(r, r->esi + 0x124, 0x1);
    call(r, 0x4ae110, 1);
    wr8(r, r->esi + 0x93, 0x1);
    r->eax = 0x54671c;
    wr8(r, r->esi + 0x4e, 0x5a);
    r->edx = r->esi;
    wr8(r, r->esi + 0x95, 0x1);
    call(r, 0x4b5e70, 0);
    r->eax = 0x180;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_468552;
    }
    r->edx = 0x49;
    wr32(r, r->ebp - 0x34, r->eax);
    r->ecx = 0;
    wr32(r, r->ebp - 0x40, r->edx);
    call(r, 0x4b6350, 0);
    wr32(r, r->ebp - 0x40, r->ecx);
at_468552:
    r->esi = r->eax;
    push(r, 0x0);
    push(r, 0x44b4a0);
    push(r, 0x0);
    push(r, 0x0);
    r->eax = r->esi;
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = 0;
    r->edx = 0;
    call(r, 0x4adf20, 5);
    r->eax = rd32(r, 0x4f8686);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    push(r, r->eax);
    r->edx = 0x50e531;
    r->ecx = rd32(r, 0x4f8696);
    push(r, r->eax);
    r->eax = rd32(r, 0x4f869a);
    r->ebx = rd32(r, 0x4f9bfd);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    push(r, r->eax);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x18);
    r->eax = r->esi;
    call(r, 0x4b65d0, 3);
    r->edx = 0x2;
    r->eax = r->esi;
    call(r, 0x4ac7b0, 0);
    r->eax = rd32(r, 0x4f8704);
    r->ecx = rd32(r, 0x4f8700);
    r->ebx = rd32(r, 0x4f86fa);
    wr8(r, r->esi + 0x44, 0x8);
    r->edx = rd32(r, 0x4f86f6);
    wr8(r, r->esi + 0x4e, 0x32);
    r->eax = r->eax >> 0x1;
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    push(r, r->eax);
    r->eax = r->esi;
    wr32(r, r->esi + 0x124, 0x1);
    call(r, 0x4ae110, 1);
    wr8(r, r->esi + 0x93, 0x1);
    r->eax = 0x54671c;
    wr8(r, r->esi + 0x4e, 0x5a);
    r->edx = r->esi;
    wr8(r, r->esi + 0x95, 0x1);
    call(r, 0x4b5e70, 0);
    r->eax = 0x180;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_468625;
    }
    r->ebx = 0x4b;
    wr32(r, r->ebp - 0x34, r->eax);
    r->esi = 0;
    wr32(r, r->ebp - 0x40, r->ebx);
    call(r, 0x4b6350, 0);
    wr32(r, r->ebp - 0x40, r->esi);
at_468625:
    r->esi = r->eax;
    push(r, 0x0);
    push(r, 0x44b5d0);
    push(r, 0x0);
    push(r, 0x0);
    r->eax = r->esi;
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = 0;
    r->edx = 0;
    call(r, 0x4adf20, 5);
    r->eax = rd32(r, 0x4f868a);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    push(r, r->eax);
    r->edx = 0x50e532;
    r->ecx = rd32(r, 0x4f8696);
    push(r, r->eax);
    r->eax = rd32(r, 0x4f869a);
    r->ebx = rd32(r, 0x4f9bfd);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    push(r, r->eax);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x18);
    r->eax = r->esi;
    call(r, 0x4b65d0, 3);
    r->edx = 0x2;
    r->eax = r->esi;
    call(r, 0x4ac7b0, 0);
    r->eax = rd32(r, 0x4f8704);
    r->ecx = rd32(r, 0x4f8700);
    r->edi = rd32(r, 0x4f86fc);
    r->edx = rd32(r, 0x4f86f6);
    wr8(r, r->esi + 0x44, 0x8);
    r->eax = r->eax >> 0x1;
    wr8(r, r->esi + 0x4e, 0x32);
    push(r, r->eax);
    r->eax = r->eax + r->edi;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = r->esi;
    wr32(r, r->esi + 0x124, 0x1);
    call(r, 0x4ae110, 1);
    wr8(r, r->esi + 0x93, 0x1);
    r->eax = 0x54671c;
    wr8(r, r->esi + 0x4e, 0x5a);
    r->edx = r->esi;
    wr8(r, r->esi + 0x95, 0x1);
    call(r, 0x4b5e70, 0);
    r->eax = 0x180;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_4686fa;
    }
    r->edx = 0x4d;
    wr32(r, r->ebp - 0x34, r->eax);
    r->ecx = 0;
    wr32(r, r->ebp - 0x40, r->edx);
    call(r, 0x4b6350, 0);
    wr32(r, r->ebp - 0x40, r->ecx);
at_4686fa:
    r->esi = r->eax;
    push(r, 0x0);
    push(r, 0x44b6f0);
    push(r, 0x0);
    push(r, 0x0);
    r->eax = r->esi;
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = 0;
    r->edx = 0;
    call(r, 0x4adf20, 5);
    set_low16(&r->eax, rd16(r, 0x4f85a4));
    set_low16(&r->eax, (r->eax & 0xffff) + rd16(r, 0x4f85a8));
    r->eax = r->eax - 1;
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    push(r, r->eax);
    r->eax = rd32(r, 0x4f85a2);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    set_low16(&r->ecx, rd16(r, 0x4f85f8));
    push(r, r->eax);
    set_low16(&r->eax, rd16(r, 0x4f85e8));
    r->edx = 0x50e533;
    r->eax = r->eax + r->ecx;
    r->ebx = rd32(r, 0x540016);
    r->eax = r->eax - 1;
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x18);
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    r->ecx = rd32(r, 0x4f85e6);
    push(r, r->eax);
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    r->eax = r->esi;
    call(r, 0x4b65d0, 3);
    r->edx = 0x2;
    r->eax = r->esi;
    call(r, 0x4ac7b0, 0);
    r->ebx = rd32(r, 0x4f85a8);
    r->ecx = rd32(r, 0x4f85f8);
    r->edx = rd32(r, 0x4f85e6);
    r->eax = r->esi;
    wr8(r, r->esi + 0x44, 0x8);
    push(r, r->ebx);
    r->ebx = rd32(r, 0x4f85a2);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    wr32(r, r->esi + 0x124, 0x1);
    call(r, 0x4ae110, 1);
    wr8(r, r->esi + 0x93, 0x1);
    r->eax = 0x54671c;
    wr8(r, r->esi + 0x4e, 0x5a);
    r->edx = r->esi;
    wr8(r, r->esi + 0x95, 0x1);
    call(r, 0x4b5e70, 0);
    r->eax = 0x180;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_4687e0;
    }
    r->esi = 0x4f;
    wr32(r, r->ebp - 0x34, r->eax);
    r->edi = 0;
    wr32(r, r->ebp - 0x40, r->esi);
    call(r, 0x4b6350, 0);
    wr32(r, r->ebp - 0x40, r->edi);
at_4687e0:
    r->esi = r->eax;
    push(r, 0x0);
    push(r, 0x44b810);
    push(r, 0x0);
    push(r, 0x0);
    r->eax = r->esi;
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = 0;
    r->edx = 0;
    call(r, 0x4adf20, 5);
    set_low16(&r->eax, rd16(r, 0x4f85a4));
    set_low16(&r->eax, (r->eax & 0xffff) + rd16(r, 0x4f85a8));
    r->eax = r->eax - 1;
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    push(r, r->eax);
    r->eax = rd32(r, 0x4f85a2);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    set_low16(&r->edx, rd16(r, 0x4f85f8));
    push(r, r->eax);
    set_low16(&r->eax, rd16(r, 0x4f85f0));
    r->ecx = rd32(r, 0x4f85ee);
    r->eax = r->eax + r->edx;
    r->ebx = rd32(r, 0x540016);
    r->eax = r->eax - 1;
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x18);
    push(r, r->eax);
    r->edx = 0x50e534;
    r->eax = r->esi;
    call(r, 0x4b65d0, 3);
    r->edx = 0x2;
    r->eax = r->esi;
    call(r, 0x4ac7b0, 0);
    r->eax = rd32(r, 0x4f85a8);
    r->ecx = rd32(r, 0x4f85f8);
    r->ebx = rd32(r, 0x4f85a2);
    r->edx = rd32(r, 0x4f85ee);
    wr8(r, r->esi + 0x44, 0x8);
    push(r, r->eax);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = r->esi;
    wr32(r, r->esi + 0x124, 0x1);
    call(r, 0x4ae110, 1);
    wr8(r, r->esi + 0x93, 0x1);
    r->eax = 0x54671c;
    wr8(r, r->esi + 0x4e, 0x5a);
    r->edx = r->esi;
    wr8(r, r->esi + 0x95, 0x1);
    call(r, 0x4b5e70, 0);
    r->eax = 0x180;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_4688c5;
    }
    r->edx = 0x51;
    wr32(r, r->ebp - 0x34, r->eax);
    r->ecx = 0;
    wr32(r, r->ebp - 0x40, r->edx);
    call(r, 0x4b6350, 0);
    wr32(r, r->ebp - 0x40, r->ecx);
at_4688c5:
    r->esi = r->eax;
    push(r, 0x0);
    push(r, 0x44b980);
    push(r, 0x0);
    push(r, 0x0);
    r->eax = r->esi;
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = 0;
    r->edx = 0;
    call(r, 0x4adf20, 5);
    set_low16(&r->eax, rd16(r, 0x4f85a4));
    set_low16(&r->eax, (r->eax & 0xffff) + rd16(r, 0x4f85a8));
    r->eax = r->eax - 1;
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    push(r, r->eax);
    r->eax = rd32(r, 0x4f85a2);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    set_low16(&r->ecx, rd16(r, 0x4f8610));
    push(r, r->eax);
    set_low16(&r->eax, rd16(r, 0x4f8608));
    r->edx = 0x50e535;
    r->eax = r->eax + r->ecx;
    r->ebx = rd32(r, 0x540016);
    r->eax = r->eax - 1;
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x18);
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    r->ecx = rd32(r, 0x4f8606);
    push(r, r->eax);
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    r->eax = r->esi;
    call(r, 0x4b65d0, 3);
    r->edx = 0x2;
    r->eax = r->esi;
    call(r, 0x4ac7b0, 0);
    r->ebx = rd32(r, 0x4f85a8);
    r->ecx = rd32(r, 0x4f8610);
    r->edx = rd32(r, 0x4f8606);
    r->eax = r->esi;
    wr8(r, r->esi + 0x44, 0x8);
    push(r, r->ebx);
    r->ebx = rd32(r, 0x4f85a2);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    wr32(r, r->esi + 0x124, 0x1);
    call(r, 0x4ae110, 1);
    wr8(r, r->esi + 0x93, 0x1);
    r->eax = 0x54671c;
    wr8(r, r->esi + 0x4e, 0x5a);
    r->edx = r->esi;
    wr8(r, r->esi + 0x95, 0x1);
    call(r, 0x4b5e70, 0);
    r->esi = rd32(r, 0x532a8c);
    if (r->esi != 0)
    {
        goto at_4693d2;
    }
at_468996:
    r->eax = 0x160;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_4689b9;
    }
    r->edx = 0x53;
    wr32(r, r->ebp - 0x34, r->eax);
    r->ecx = 0;
    wr32(r, r->ebp - 0x40, r->edx);
    call(r, 0x4b5400, 0);
    wr32(r, r->ebp - 0x40, r->ecx);
at_4689b9:
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
    push(r, 0x0);
    r->ebx = rd32(r, 0x4f86c6);
    r->edx = rd32(r, 0x4f86c2);
    r->eax = r->esi;
    r->ecx = 0;
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    call(r, 0x4b54d0, 1);
    r->edx = 0x2;
    r->eax = r->esi;
    wr16(r, r->esi + 0x48, 0xf);
    call(r, 0x4ac7b0, 0);
    r->ebx = 0;
    wr8(r, r->esi + 0x94, 0x0);
    r->edx = 0xff000000u;
    wr8(r, r->esi + 0x95, 0x1);
    r->eax = r->esi;
    wr8(r, r->esi + 0x110, 0x1);
    call(r, 0x4ac4e0, 0);
    r->edx = 0x44bac0;
    r->eax = r->esi;
    call(r, 0x4ac8f0, 0);
    r->eax = rd32(r, 0x4f86d0);
    r->eax = r->eax + 0x4;
    push(r, r->eax);
    set_low16(&r->eax, rd16(r, 0x4f86c8));
    r->eax = r->eax - 0x2;
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    set_low16(&r->eax, rd16(r, 0x4f86c4));
    r->ecx = rd32(r, 0x4f86cc);
    r->eax = r->eax - 0x2;
    r->ecx = r->ecx + 0x4;
    r->edx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = r->esi;
    wr32(r, r->esi + 0x124, 0x1);
    call(r, 0x4ae110, 1);
    r->eax = 0x54671c;
    r->edx = r->esi;
    wr32(r, r->esi + 0x7c, 0xffffffffu);
    call(r, 0x4b5e70, 0);
    r->eax = 0x160;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_468aa1;
    }
    r->ebx = 0x55;
    wr32(r, r->ebp - 0x34, r->eax);
    r->esi = 0;
    wr32(r, r->ebp - 0x40, r->ebx);
    call(r, 0x4b5400, 0);
    wr32(r, r->ebp - 0x40, r->esi);
at_468aa1:
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
    push(r, 0x0);
    r->ebx = rd32(r, 0x4f86b6);
    r->edx = rd32(r, 0x4f86b2);
    r->eax = r->esi;
    r->ecx = 0;
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    call(r, 0x4b54d0, 1);
    r->edx = 0x2;
    r->eax = r->esi;
    wr16(r, r->esi + 0x48, 0xf);
    call(r, 0x4ac7b0, 0);
    r->ebx = 0;
    wr8(r, r->esi + 0x94, 0x0);
    r->edx = 0xff000000u;
    wr8(r, r->esi + 0x95, 0x1);
    r->eax = r->esi;
    wr8(r, r->esi + 0x110, 0x1);
    call(r, 0x4ac4e0, 0);
    r->edx = 0x44bb30;
    r->eax = r->esi;
    call(r, 0x4ac8f0, 0);
    r->eax = rd32(r, 0x4f86c0);
    r->eax = r->eax + 0x4;
    push(r, r->eax);
    set_low16(&r->eax, rd16(r, 0x4f86b8));
    r->eax = r->eax - 0x2;
    r->edi = 0;
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    set_low16(&r->eax, rd16(r, 0x4f86b4));
    r->ecx = rd32(r, 0x4f86bc);
    r->eax = r->eax - 0x2;
    r->ecx = r->ecx + 0x4;
    r->edx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = r->esi;
    wr32(r, r->esi + 0x124, 0x1);
    call(r, 0x4ae110, 1);
    r->eax = 0x54671c;
    r->edx = r->esi;
    wr32(r, r->esi + 0x7c, 0xffffffffu);
    call(r, 0x4b5e70, 0);
    wr32(r, r->ebp - 0x40, r->edi);
at_468b6b:
    r->eax = rd32(r, 0x532a84);
    if (r->eax == 0x1)
    {
        goto at_4693e0;
    }
    r->eax = rd32(r, r->ebp - 0x4c);
    r->port->env.chain = r->eax;
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_468b8c:
    r->eax = 0;
    set_low16(&r->eax, rd16(r, r->ebp - 0x2c));
    call(r, 0x476650, 0);
    if (r->eax == 0x1 && !r->port->env.failed)
    {
        goto at_466e10;
    }
    r->eax = 0;
    set_low16(&r->eax, rd16(r, r->ebp - 0x20));
    call(r, 0x476650, 0);
    if (r->eax == 0x1 && !r->port->env.failed)
    {
        goto at_466e10;
    }
    r->eax = 0;
    set_low16(&r->eax, (r->edi & 0xffff));
    call(r, 0x476650, 0);
    if (r->eax == 0x1 && !r->port->env.failed)
    {
        goto at_466e10;
    }
    r->edi = 0x1;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_466e12;
at_468bd1:
    if (rd32(r, 0x532a7c) != 0x1)
    {
        goto at_468c8f;
    }
    if (rd32(r, 0x532a80) != 0x0)
    {
        goto at_468c8f;
    }
    r->eax = 0;
    set_low16(&r->eax, rd16(r, 0x532b74));
    wr32(r, r->ebp - 0x1c, r->eax);
    r->eax = 0;
    set_low16(&r->eax, rd16(r, 0x532b76));
    wr32(r, r->ebp - 0x2c, r->eax);
    r->eax = 0;
    set_low16(&r->eax, rd16(r, 0x532b78));
    wr32(r, r->ebp - 0x20, r->eax);
    r->eax = 0;
    set_low16(&r->eax, rd16(r, 0x532b6c));
    wr32(r, r->ebp - 0x28, r->eax);
    r->eax = 0;
    set_low16(&r->eax, rd16(r, 0x532b6e));
    wr32(r, r->ebp - 0x30, r->eax);
    r->eax = 0;
    set_low16(&r->eax, rd16(r, 0x532b70));
    wr32(r, r->ebp - 0x18, r->eax);
    r->eax = 0;
    r->edx = 0;
    set_low16(&r->eax, rd16(r, r->ebp - 0x28));
    set_low16(&r->edx, rd16(r, 0x532b72));
    call(r, 0x476650, 0);
    if (r->eax != 0x1)
    {
        goto at_468c52;
    }
at_468c46:
    r->eax = 0;
    wr32(r, r->ebp - 0x24, r->eax);
    r->edi = 0;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_466e17;
at_468c52:
    r->eax = 0;
    set_low16(&r->eax, rd16(r, r->ebp - 0x30));
    call(r, 0x476650, 0);
    if (r->eax == 0x1 && !r->port->env.failed)
    {
        goto at_468c46;
    }
    r->eax = 0;
    set_low16(&r->eax, rd16(r, r->ebp - 0x18));
    call(r, 0x476650, 0);
    if (r->eax == 0x1 && !r->port->env.failed)
    {
        goto at_468c46;
    }
    r->eax = 0;
    set_low16(&r->eax, (r->edx & 0xffff));
    call(r, 0x476650, 0);
    if (r->eax == 0x1 && !r->port->env.failed)
    {
        goto at_468c46;
    }
    wr32(r, r->ebp - 0x24, 0x1);
    r->edi = 0;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_466e17;
at_468c8f:
    r->eax = 0;
    set_low16(&r->eax, rd16(r, 0x532b6c));
    wr32(r, r->ebp - 0x1c, r->eax);
    r->eax = 0;
    set_low16(&r->eax, rd16(r, 0x532b6e));
    wr32(r, r->ebp - 0x2c, r->eax);
    r->eax = 0;
    set_low16(&r->eax, rd16(r, 0x532b70));
    wr32(r, r->ebp - 0x20, r->eax);
    r->eax = 0;
    set_low16(&r->eax, rd16(r, 0x532b74));
    wr32(r, r->ebp - 0x28, r->eax);
    r->eax = 0;
    set_low16(&r->eax, rd16(r, 0x532b76));
    wr32(r, r->ebp - 0x30, r->eax);
    r->eax = 0;
    r->edi = 0;
    set_low16(&r->eax, rd16(r, 0x532b78));
    r->edx = 0;
    wr32(r, r->ebp - 0x18, r->eax);
    r->eax = 0;
    set_low16(&r->edi, rd16(r, 0x532b72));
    set_low16(&r->eax, rd16(r, r->ebp - 0x1c));
    set_low16(&r->edx, rd16(r, 0x532b7a));
    call(r, 0x476650, 0);
    if (r->eax != 0x1)
    {
        goto at_468d0f;
    }
at_468cf3:
    r->edi = 0;
at_468cf5:
    r->eax = 0;
    set_low16(&r->eax, rd16(r, r->ebp - 0x28));
    call(r, 0x476650, 0);
    if (r->eax != 0x1)
    {
        goto at_468d45;
    }
at_468d05:
    r->esi = 0;
    wr32(r, r->ebp - 0x24, r->esi);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_466e17;
at_468d0f:
    r->eax = 0;
    set_low16(&r->eax, rd16(r, r->ebp - 0x2c));
    call(r, 0x476650, 0);
    if (r->eax == 0x1 && !r->port->env.failed)
    {
        goto at_468cf3;
    }
    r->eax = 0;
    set_low16(&r->eax, rd16(r, r->ebp - 0x20));
    call(r, 0x476650, 0);
    if (r->eax == 0x1 && !r->port->env.failed)
    {
        goto at_468cf3;
    }
    r->eax = 0;
    set_low16(&r->eax, (r->edi & 0xffff));
    call(r, 0x476650, 0);
    if (r->eax == 0x1 && !r->port->env.failed)
    {
        goto at_468cf3;
    }
    r->edi = 0x1;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_468cf5;
at_468d45:
    r->eax = 0;
    set_low16(&r->eax, rd16(r, r->ebp - 0x30));
    call(r, 0x476650, 0);
    if (r->eax == 0x1 && !r->port->env.failed)
    {
        goto at_468d05;
    }
    r->eax = 0;
    set_low16(&r->eax, rd16(r, r->ebp - 0x18));
    call(r, 0x476650, 0);
    if (r->eax == 0x1 && !r->port->env.failed)
    {
        goto at_468d05;
    }
    r->eax = 0;
    set_low16(&r->eax, (r->edx & 0xffff));
    call(r, 0x476650, 0);
    if (r->eax == 0x1 && !r->port->env.failed)
    {
        goto at_468d05;
    }
    wr32(r, r->ebp - 0x24, 0x1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_466e17;
at_468d80:
    r->eax = 0x15c;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_468da3;
    }
    r->edx = 0x13;
    wr32(r, r->ebp - 0x34, r->eax);
    r->ecx = 0;
    wr32(r, r->ebp - 0x40, r->edx);
    call(r, 0x4abd70, 0);
    wr32(r, r->ebp - 0x40, r->ecx);
at_468da3:
    r->esi = r->eax;
    push(r, 0x0);
    push(r, 0x449500);
    r->eax = rd32(r, 0x4f8618);
    push(r, 0x0);
    r->edx = rd32(r, 0x4f861c);
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->edx & 0xffff);
    push(r, 0x0);
    r->edx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = r->esi;
    call(r, 0x4adf20, 5);
    r->edx = 0x2;
    r->eax = r->esi;
    call(r, 0x4ac7b0, 0);
    r->ecx = 0;
    r->eax = r->esi;
    r->edx = 0;
    r->ebx = 0;
    call(r, 0x4ac910, 0);
    r->eax = rd32(r, r->ebp - 0x1c);
    push(r, 0x0);
    wr32(r, r->esi + 0x124, 0x1);
    r->edx = 0;
    wr32(r, r->esi + 0x64, r->eax);
    r->eax = r->esi;
    wr32(r, r->esi + 0x70, r->edi);
    call(r, 0x4ae110, 1);
    r->eax = 0x54671c;
    r->edx = r->esi;
    wr32(r, r->esi + 0x13c, 0x0);
    call(r, 0x4b5e70, 0);
    r->eax = 0x15c;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_468e3c;
    }
    r->ebx = 0x15;
    wr32(r, r->ebp - 0x34, r->eax);
    r->esi = 0;
    wr32(r, r->ebp - 0x40, r->ebx);
    call(r, 0x4abd70, 0);
    wr32(r, r->ebp - 0x40, r->esi);
at_468e3c:
    r->esi = r->eax;
    push(r, 0x0);
    push(r, 0x449660);
    r->eax = rd32(r, 0x4f8628);
    push(r, 0x0);
    r->edx = rd32(r, 0x4f862c);
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->edx & 0xffff);
    push(r, 0x0);
    r->edx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = r->esi;
    call(r, 0x4adf20, 5);
    r->edx = 0x2;
    r->eax = r->esi;
    call(r, 0x4ac7b0, 0);
    r->ecx = 0;
    r->eax = r->esi;
    r->edx = 0;
    r->ebx = 0;
    call(r, 0x4ac910, 0);
    r->eax = rd32(r, r->ebp - 0x2c);
    push(r, 0x0);
    wr32(r, r->esi + 0x124, 0x1);
    r->edx = 0;
    wr32(r, r->esi + 0x64, r->eax);
    r->eax = r->esi;
    wr32(r, r->esi + 0x70, r->edi);
    call(r, 0x4ae110, 1);
    r->eax = 0x54671c;
    r->edx = r->esi;
    wr32(r, r->esi + 0x13c, 0x0);
    call(r, 0x4b5e70, 0);
    r->eax = 0x15c;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_468ed5;
    }
    r->edx = 0x17;
    wr32(r, r->ebp - 0x34, r->eax);
    r->ecx = 0;
    wr32(r, r->ebp - 0x40, r->edx);
    call(r, 0x4abd70, 0);
    wr32(r, r->ebp - 0x40, r->ecx);
at_468ed5:
    r->edx = rd32(r, 0x4f8624);
    r->ebx = rd32(r, 0x532b40);
    r->esi = r->eax;
    r->eax = rd32(r, 0x4f8620);
    if (r->ebx != 0x1)
    {
        goto at_468f71;
    }
    r->ecx = 0x449870;
at_468ef6:
    push(r, 0x0);
    push(r, r->ecx);
    push(r, 0x0);
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->edx & 0xffff);
    push(r, 0x0);
    r->edx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    push(r, 0x0);
    r->eax = r->esi;
    r->ecx = 0;
    call(r, 0x4adf20, 5);
    r->edx = 0x2;
    r->eax = r->esi;
    call(r, 0x4ac7b0, 0);
    r->edx = 0xa;
    r->eax = r->esi;
    r->ecx = 0;
    call(r, 0x4ac470, 0);
    r->eax = r->esi;
    r->edx = 0;
    r->ebx = 0;
    call(r, 0x4ac910, 0);
    r->eax = rd32(r, r->ebp - 0x20);
    push(r, 0x0);
    wr32(r, r->esi + 0x124, 0x1);
    r->edx = 0;
    wr32(r, r->esi + 0x64, r->eax);
    r->eax = r->esi;
    wr32(r, r->esi + 0x70, r->edi);
    call(r, 0x4ae110, 1);
    r->eax = 0x54671c;
    r->edx = r->esi;
    wr32(r, r->esi + 0x13c, 0x0);
    r->esi = 0;
    call(r, 0x4b5e70, 0);
    wr32(r, r->ebp - 0x40, r->esi);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4675a3;
at_468f71:
    r->ecx = 0x4497c0;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_468ef6;
at_468f7b:
    if (rd32(r, 0x532a80) == 0x1 && !r->port->env.failed)
    {
        goto at_46799b;
    }
    r->eax = 0x15c;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_468fab;
    }
    r->edx = 0x27;
    wr32(r, r->ebp - 0x34, r->eax);
    r->ecx = 0;
    wr32(r, r->ebp - 0x40, r->edx);
    call(r, 0x4abd70, 0);
    wr32(r, r->ebp - 0x40, r->ecx);
at_468fab:
    r->esi = r->eax;
    push(r, 0x0);
    push(r, 0x449aa0);
    r->eax = rd32(r, 0x4f8630);
    push(r, 0x0);
    r->edx = rd32(r, 0x4f8634);
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->edx & 0xffff);
    push(r, 0x0);
    r->edx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = r->esi;
    call(r, 0x4adf20, 5);
    r->edx = 0x2;
    r->eax = r->esi;
    call(r, 0x4ac7b0, 0);
    r->ecx = 0;
    r->eax = r->esi;
    r->edx = 0;
    r->ebx = 0;
    call(r, 0x4ac910, 0);
    r->eax = rd32(r, r->ebp - 0x24);
    push(r, 0x0);
    wr32(r, r->esi + 0x70, r->eax);
    r->eax = rd32(r, r->ebp - 0x28);
    r->edx = 0;
    wr32(r, r->esi + 0x64, r->eax);
    r->eax = r->esi;
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
        goto at_469047;
    }
    r->ebx = 0x29;
    wr32(r, r->ebp - 0x34, r->eax);
    r->esi = 0;
    wr32(r, r->ebp - 0x40, r->ebx);
    call(r, 0x4abd70, 0);
    wr32(r, r->ebp - 0x40, r->esi);
at_469047:
    r->esi = r->eax;
    push(r, 0x0);
    push(r, 0x449c00);
    r->eax = rd32(r, 0x4f8640);
    push(r, 0x0);
    r->edx = rd32(r, 0x4f8644);
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->edx & 0xffff);
    push(r, 0x0);
    r->edx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = r->esi;
    call(r, 0x4adf20, 5);
    r->edx = 0x2;
    r->eax = r->esi;
    call(r, 0x4ac7b0, 0);
    r->ecx = 0;
    r->eax = r->esi;
    r->edx = 0;
    r->ebx = 0;
    call(r, 0x4ac910, 0);
    r->eax = rd32(r, r->ebp - 0x24);
    push(r, 0x0);
    wr32(r, r->esi + 0x70, r->eax);
    r->eax = rd32(r, r->ebp - 0x30);
    r->edx = 0;
    wr32(r, r->esi + 0x64, r->eax);
    r->eax = r->esi;
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
        goto at_4690e3;
    }
    r->edi = 0x2b;
    wr32(r, r->ebp - 0x34, r->eax);
    r->edx = 0;
    wr32(r, r->ebp - 0x40, r->edi);
    call(r, 0x4abd70, 0);
    wr32(r, r->ebp - 0x40, r->edx);
at_4690e3:
    r->edx = rd32(r, 0x4f863c);
    r->ecx = rd32(r, 0x532b40);
    r->esi = r->eax;
    r->eax = rd32(r, 0x4f8638);
    if (r->ecx != 0x1)
    {
        goto at_469182;
    }
    r->ecx = 0x449e10;
at_469104:
    push(r, 0x0);
    push(r, r->ecx);
    push(r, 0x0);
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->edx & 0xffff);
    push(r, 0x0);
    r->edx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    push(r, 0x0);
    r->eax = r->esi;
    r->ecx = 0;
    call(r, 0x4adf20, 5);
    r->edx = 0x2;
    r->eax = r->esi;
    call(r, 0x4ac7b0, 0);
    r->edx = 0xa;
    r->eax = r->esi;
    r->ecx = 0;
    call(r, 0x4ac470, 0);
    r->eax = r->esi;
    r->edx = 0;
    r->ebx = 0;
    call(r, 0x4ac910, 0);
    r->eax = rd32(r, r->ebp - 0x24);
    push(r, 0x0);
    wr32(r, r->esi + 0x70, r->eax);
    r->eax = rd32(r, r->ebp - 0x18);
    r->edx = 0;
    wr32(r, r->esi + 0x64, r->eax);
    r->eax = r->esi;
    wr32(r, r->esi + 0x124, 0x1);
    call(r, 0x4ae110, 1);
    r->eax = 0x54671c;
    r->edx = r->esi;
    wr32(r, r->esi + 0x13c, 0x0);
    r->ebx = 0;
    call(r, 0x4b5e70, 0);
    wr32(r, r->ebp - 0x40, r->ebx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_467bd4;
at_469182:
    r->ecx = 0x449d60;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_469104;
at_46918c:
    if (rd32(r, 0x532a7c) == 0x1 && !r->port->env.failed)
    {
        goto at_467cdc;
    }
    r->eax = 0x15c;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_4691bc;
    }
    r->edi = 0x35;
    wr32(r, r->ebp - 0x34, r->eax);
    r->edx = 0;
    wr32(r, r->ebp - 0x40, r->edi);
    call(r, 0x4abd70, 0);
    wr32(r, r->ebp - 0x40, r->edx);
at_4691bc:
    r->esi = r->eax;
    push(r, 0x0);
    push(r, 0x44a040);
    r->eax = rd32(r, 0x4f8648);
    push(r, 0x0);
    r->edx = rd32(r, 0x4f864c);
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->edx & 0xffff);
    push(r, 0x0);
    r->edx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = r->esi;
    call(r, 0x4adf20, 5);
    r->edx = 0x2;
    r->eax = r->esi;
    call(r, 0x4ac7b0, 0);
    r->ecx = 0;
    r->eax = r->esi;
    r->edx = 0;
    r->ebx = 0;
    call(r, 0x4ac910, 0);
    push(r, 0x0);
    r->eax = r->esi;
    r->edx = 0;
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
        goto at_46924c;
    }
    r->ecx = 0x37;
    wr32(r, r->ebp - 0x34, r->eax);
    r->ebx = 0;
    wr32(r, r->ebp - 0x40, r->ecx);
    call(r, 0x4abd70, 0);
    wr32(r, r->ebp - 0x40, r->ebx);
at_46924c:
    r->esi = r->eax;
    push(r, 0x0);
    push(r, 0x44a170);
    r->eax = rd32(r, 0x4f8658);
    push(r, 0x0);
    r->edx = rd32(r, 0x4f865c);
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->edx & 0xffff);
    push(r, 0x0);
    r->edx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = r->esi;
    call(r, 0x4adf20, 5);
    r->edx = 0x2;
    r->eax = r->esi;
    call(r, 0x4ac7b0, 0);
    r->ecx = 0;
    r->eax = r->esi;
    r->edx = 0;
    r->ebx = 0;
    call(r, 0x4ac910, 0);
    push(r, 0x0);
    r->eax = r->esi;
    r->edx = 0;
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
        goto at_4692dc;
    }
    r->esi = 0x39;
    wr32(r, r->ebp - 0x34, r->eax);
    r->edi = 0;
    wr32(r, r->ebp - 0x40, r->esi);
    call(r, 0x4abd70, 0);
    wr32(r, r->ebp - 0x40, r->edi);
at_4692dc:
    r->edx = rd32(r, 0x4f8654);
    r->ecx = rd32(r, 0x532b40);
    r->esi = r->eax;
    r->eax = rd32(r, 0x4f8650);
    if (r->ecx != 0x1)
    {
        goto at_46936b;
    }
    r->ecx = 0x44a340;
at_4692f9:
    push(r, 0x0);
    push(r, r->ecx);
    push(r, 0x0);
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->edx & 0xffff);
    push(r, 0x0);
    r->edx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    push(r, 0x0);
    r->eax = r->esi;
    r->ecx = 0;
    call(r, 0x4adf20, 5);
    r->edx = 0x2;
    r->eax = r->esi;
    call(r, 0x4ac7b0, 0);
    r->edx = 0xa;
    r->eax = r->esi;
    r->ecx = 0;
    call(r, 0x4ac470, 0);
    r->eax = r->esi;
    r->edx = 0;
    r->ebx = 0;
    call(r, 0x4ac910, 0);
    push(r, 0x0);
    r->eax = r->esi;
    r->edx = 0;
    wr32(r, r->esi + 0x124, 0x1);
    call(r, 0x4ae110, 1);
    r->eax = 0x54671c;
    r->edx = r->esi;
    wr32(r, r->esi + 0x13c, 0x0);
    r->ebx = 0;
    call(r, 0x4b5e70, 0);
    wr32(r, r->ebp - 0x40, r->ebx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_467f15;
at_46936b:
    r->ecx = 0x44a2a0;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4692f9;
at_469372:
    if (r->eax != rd32(r, 0x532a7c))
    {
        goto at_46938e;
    }
    r->edx = rd32(r, 0x532a6c);
    if (r->eax != rd32(r, r->edx * 4 + 0x5344f0))
    {
        goto at_4693b3;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_468048;
at_46938e:
    r->edx = rd32(r, 0x532a68);
    if (r->eax != rd32(r, r->edx * 4 + 0x5344a4))
    {
        goto at_46939f;
    }
    r->eax = 0;
at_46939f:
    r->edx = rd32(r, 0x532a6c);
    if (rd32(r, r->edx * 4 + 0x5344f0) == 0x1 && !r->port->env.failed)
    {
        goto at_468048;
    }
at_4693b3:
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_468048;
    }
    wr8(r, r->edi + 0x52, 0xd);
    wr8(r, r->edi + 0x94, 0x0);
    wr8(r, r->edi + 0x95, 0x1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_46805a;
at_4693d2:
    if (r->esi == 0x1 && !r->port->env.failed)
    {
        goto at_468996;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_468b6b;
at_4693e0:
    push(r, r->eax);
    push(r, 0x0);
    r->eax = rd32(r, 0x540015);
    push(r, 0x8);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x18);
    push(r, r->eax);
    set_low16(&r->eax, rd16(r, 0x4f8738));
    r->eax = r->eax + 0xc;
    r->ecx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    set_low16(&r->eax, rd16(r, 0x4f8734));
    r->eax = r->eax + 0x4;
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    set_low16(&r->eax, rd16(r, 0x4f8730));
    r->eax = r->eax - 0x6;
    r->edx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = rd32(r, 0x4f8734);
    r->esi = 0x280;
    r->eax = r->eax + 0x4;
    r->esi = r->esi - r->eax;
    r->eax = r->esi;
    push(r, 0x416970);
    r->eax = r->eax >> 0x1;
    push(r, 0x50e536);
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    call(r, 0x4602a0, 6);
    r->esi = r->eax;
    r->eax = rd32(r, r->eax + 0x160);
    r->edx = 0;
    wr8(r, r->eax + 0x52, 0x0);
    r->eax = r->esi;
    call(r, 0x4ac910, 0);
    r->edx = 0x445d80;
    r->eax = r->esi;
    call(r, 0x4ac8f0, 0);
    r->eax = 0x54671c;
    r->edx = r->esi;
    call(r, 0x4b5e70, 0);
    r->eax = rd32(r, r->ebp - 0x4c);
    r->port->env.chain = r->eax;
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
}

uint32_t vertrix_port_board_select_screen_build_466d60(PORT_SIGNATURE)
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
    port_set32(&port, r.ebp, -0x4u, entry->ebx);
    port_set32(&port, r.ebp, -0x8u, entry->ecx);
    port_set32(&port, r.ebp, -0xcu, entry->edx);
    port_set32(&port, r.ebp, -0x10u, entry->esi);
    port_set32(&port, r.ebp, -0x14u, entry->edi);
    run(&r);
    return port_return(&port, r.eax, r.edx);
}
