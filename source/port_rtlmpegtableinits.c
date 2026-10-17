#include "port_rtlmpegtableinits.h"

/* Builds the MP3 decoder's floating-point tables when the reader is reset (powers through 0x4c9921
 * and conversions between integer, double and single). */

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

static void wr32(Regs *r, uint32_t address, uint32_t value)
{
    port_set32(r->port, address, 0, value);
}

static void set_high8(uint32_t *reg, uint32_t value)
{
    *reg = (*reg & 0xffff00ffu) | ((value & 0xff) << 8);
}

/* idiv and div of edx:eax as the original's (a zero divisor or an overflowing quotient leaves
 * both registers). */
static void idiv32(Regs *r, uint32_t value)
{
    LiftFlags flags;
    memset(&flags, 0, sizeof flags);
    lift_idiv1(32, value, &r->eax, &r->edx, &flags);
}

/* The emulated stack of a routine without a frame pointer: pushes and pops move esp. */
static void push_mem(Regs *r, uint32_t value)
{
    r->esp -= 4;
    wr32(r, r->esp, value);
}

static uint32_t pop_mem(Regs *r)
{
    uint32_t value = rd32(r, r->esp);
    r->esp += 4;
    return value;
}

/* A call taking count stack arguments from esp up; the callee pops them unless kept (cdecl). */
static void call_mem_with(Regs *r, uint32_t target, unsigned count, int keep)
{
    uint32_t args[32] = {0};
    unsigned i;
    for (i = 0; i < count && i < 32; i++)
    {
        args[i] = rd32(r, r->esp + 4 * i);
    }
    vertrix_lift_in_esi = r->esi;
    vertrix_lift_in_edi = r->edi;
    vertrix_lift_in_ebp = r->ebp;
    r->eax =
        lift_call_arguments(&r->port->env, target, r->eax, r->edx, r->ebx, r->ecx, args, count);
    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    r->edx = vertrix_lift_edx;
    if (!keep)
    {
        r->esp += 4 * count;
    }
}

static void call_mem_keep(Regs *r, uint32_t target, unsigned count)
{
    call_mem_with(r, target, count, 1);
}

/* Original 0x406170: Builds the MP3 decoder's floating-point tables when the reader is reset
 * (powers through 0x4c9921 and conversions between integer, double and single). Evidence: calls
 * 0x4d6768, 0x4db507, 0x4c9921, 0x4eb606, 0x4db350, 0x4c9b10, 0x4eb652, 0x4c9daf, 0x4c9dd6,
 * 0x4eb5b4, 0x4c9e00; writes 0x524284, 0x524280. Register-for-register from the listing
 * (0x406170..0x40700c); labels are the original addresses. */
static void run(Regs *r)
{
    push_mem(r, r->ebx);
    push_mem(r, r->ecx);
    push_mem(r, r->edx);
    push_mem(r, r->esi);
    push_mem(r, r->edi);
    push_mem(r, r->ebp);
    r->esp = r->esp - 0xec;
    wr32(r, r->esp, r->eax);
    r->esi = 0xfffffc00u;
    r->edi = 0xffffffd2u;
    r->ebp = 0x40000000;
at_40618e:
    r->eax = r->edi;
    call_mem_keep(r, 0x4d6768, 8);
    r->ebx = 0;
    r->ecx = 0xbfd00000u;
    call_mem_keep(r, 0x4db507, 8);
    r->ebx = r->eax;
    r->ecx = r->edx;
    r->eax = 0;
    r->edx = r->ebp;
    call_mem_keep(r, 0x4c9921, 8);
    call_mem_keep(r, 0x4eb606, 8);
    wr32(r, r->esi + 0x523698, r->eax);
    r->esi = r->esi + 0x4;
    r->edi = r->edi + 1;
    if (r->esi != 0x1e8 && !r->port->env.failed)
    {
        goto at_40618e;
    }
    r->esi = 0;
    r->edi = 0;
    r->ebp = 0x55555554;
at_4061ce:
    r->eax = r->esi;
    call_mem_keep(r, 0x4d6768, 8);
    r->ebx = r->ebp;
    r->ecx = 0x3ff55555;
    call_mem_keep(r, 0x4c9921, 8);
    call_mem_keep(r, 0x4eb606, 8);
    wr32(r, r->edi + 0x524288, r->eax);
    r->edi = r->edi + 0x4;
    r->esi = r->esi + 1;
    if ((int32_t)r->esi < (int32_t)0x200f && !r->port->env.failed)
    {
        goto at_4061ce;
    }
    r->edx = 0;
    wr32(r, r->esp + 0x20, r->edx);
    r->esi = 0;
at_406200:
    r->eax = rd32(r, r->esi + 0x4f5e28);
    r->edx = rd32(r, r->esi + 0x4f5e2c);
    r->ebx = r->eax;
    r->ecx = r->edx;
    call_mem_keep(r, 0x4db507, 8);
    r->ebx = 0;
    r->ecx = 0x3ff00000;
    call_mem_keep(r, 0x4db350, 8);
    call_mem_keep(r, 0x4c9b10, 8);
    r->ebp = r->eax;
    r->edi = r->edx;
    r->eax = 0;
    r->edx = 0x3ff00000;
    r->ebx = r->ebp;
    r->ecx = r->edi;
    call_mem_keep(r, 0x4eb652, 8);
    call_mem_keep(r, 0x4eb606, 8);
    r->edx = rd32(r, r->esp + 0x20);
    wr32(r, r->edx + 0x5238a0, r->eax);
    r->eax = rd32(r, r->esi + 0x4f5e28);
    r->edx = rd32(r, r->esi + 0x4f5e2c);
    r->ebx = r->ebp;
    r->ecx = r->edi;
    call_mem_keep(r, 0x4eb652, 8);
    call_mem_keep(r, 0x4eb606, 8);
    r->edx = rd32(r, r->esp + 0x20);
    wr32(r, r->edx + 0x523880, r->eax);
    r->ecx = r->edx + 0x4;
    wr32(r, r->esp + 0x20, r->ecx);
    r->esi = r->esi + 0x8;
    if (r->ecx != 0x20 && !r->port->env.failed)
    {
        goto at_406200;
    }
    wr32(r, r->esp + 0x24, 0x37);
    r->ebp = 0x25;
    r->esi = 0;
    wr32(r, r->esp + 0x28, 0x13);
    r->edi = 0x1;
at_406298:
    r->eax = r->edi;
    call_mem_keep(r, 0x4d6768, 8);
    r->ebx = 0x4ae74487;
    r->ecx = 0x3fa65718;
    call_mem_keep(r, 0x4db507, 8);
    call_mem_keep(r, 0x4c9daf, 8);
    r->ebx = 0;
    r->ecx = 0x3fe00000;
    call_mem_keep(r, 0x4db507, 8);
    wr32(r, r->esp + 0xe8, r->eax);
    wr32(r, r->esp + 0x4, r->edx);
    r->eax = rd32(r, r->esp + 0x28);
    call_mem_keep(r, 0x4d6768, 8);
    r->ebx = 0x54442d18;
    r->ecx = 0x400921fb;
    call_mem_keep(r, 0x4db507, 8);
    r->ebx = 0;
    r->ecx = 0x40520000;
    call_mem_keep(r, 0x4eb652, 8);
    call_mem_keep(r, 0x4c9dd6, 8);
    r->ebx = r->eax;
    r->ecx = r->edx;
    r->eax = rd32(r, r->esp + 0xe8);
    r->edx = rd32(r, r->esp + 0x4);
    call_mem_keep(r, 0x4eb652, 8);
    call_mem_keep(r, 0x4eb606, 8);
    wr32(r, r->esi + 0x523b90, r->eax);
    wr32(r, r->esi + 0x523b00, r->eax);
    r->eax = r->ebp;
    call_mem_keep(r, 0x4d6768, 8);
    r->ebx = 0x4ae74487;
    r->ecx = 0x3fa65718;
    call_mem_keep(r, 0x4db507, 8);
    call_mem_keep(r, 0x4c9daf, 8);
    r->ebx = 0;
    r->ecx = 0x3fe00000;
    call_mem_keep(r, 0x4db507, 8);
    wr32(r, r->esp + 0xe8, r->eax);
    wr32(r, r->esp + 0x4, r->edx);
    r->eax = rd32(r, r->esp + 0x24);
    call_mem_keep(r, 0x4d6768, 8);
    r->ebx = 0x54442d18;
    r->ecx = 0x400921fb;
    call_mem_keep(r, 0x4db507, 8);
    r->ebx = 0;
    r->ecx = 0x40520000;
    call_mem_keep(r, 0x4eb652, 8);
    call_mem_keep(r, 0x4c9dd6, 8);
    r->ebx = r->eax;
    r->ecx = r->edx;
    r->eax = rd32(r, r->esp + 0xe8);
    r->edx = rd32(r, r->esp + 0x4);
    call_mem_keep(r, 0x4eb652, 8);
    call_mem_keep(r, 0x4eb606, 8);
    wr32(r, r->esi + 0x523cf8, r->eax);
    wr32(r, r->esi + 0x523b48, r->eax);
    wr32(r, r->esp + 0x24, rd32(r, r->esp + 0x24) + 0x2);
    r->ebp = r->ebp + 0x2;
    r->esi = r->esi + 0x4;
    wr32(r, r->esp + 0x28, rd32(r, r->esp + 0x28) + 0x2);
    r->edi = r->edi + 0x2;
    if (r->edi != 0x25 && !r->port->env.failed)
    {
        goto at_406298;
    }
    r->edi = 0x1;
    wr32(r, r->esp + 0x2c, 0x1f);
    wr32(r, r->esp + 0x30, 0xd);
    r->ebp = 0x43;
    wr32(r, r->esp + 0x34, 0x2b);
    r->esi = 0;
    wr32(r, r->esp + 0x38, 0x37);
at_4063e0:
    r->eax = rd32(r, r->esp + 0x38);
    call_mem_keep(r, 0x4d6768, 8);
    r->ebx = 0x54442d18;
    r->ecx = 0x400921fb;
    call_mem_keep(r, 0x4db507, 8);
    r->ebx = 0;
    r->ecx = 0x40520000;
    call_mem_keep(r, 0x4eb652, 8);
    call_mem_keep(r, 0x4c9dd6, 8);
    r->ebx = r->eax;
    r->ecx = r->edx;
    r->eax = 0;
    r->edx = 0x3fe00000;
    call_mem_keep(r, 0x4eb652, 8);
    call_mem_keep(r, 0x4eb606, 8);
    wr32(r, r->esi + 0x523bd8, r->eax);
    r->eax = rd32(r, r->esp + 0x34);
    call_mem_keep(r, 0x4d6768, 8);
    r->ebx = 0x54442d18;
    r->ecx = 0x400921fb;
    call_mem_keep(r, 0x4db507, 8);
    r->ebx = 0;
    r->ecx = 0x40520000;
    call_mem_keep(r, 0x4eb652, 8);
    call_mem_keep(r, 0x4c9dd6, 8);
    r->ebx = r->eax;
    r->ecx = r->edx;
    r->eax = 0;
    r->edx = 0x3fe00000;
    call_mem_keep(r, 0x4eb652, 8);
    call_mem_keep(r, 0x4eb606, 8);
    wr32(r, r->esi + 0x523ce0, r->eax);
    r->eax = r->ebp;
    call_mem_keep(r, 0x4d6768, 8);
    r->ebx = 0x54442d18;
    r->ecx = 0x400921fb;
    call_mem_keep(r, 0x4db507, 8);
    r->ebx = 0;
    r->ecx = 0x40520000;
    call_mem_keep(r, 0x4eb652, 8);
    call_mem_keep(r, 0x4c9dd6, 8);
    wr32(r, r->esp + 0xe8, r->eax);
    wr32(r, r->esp + 0x4, r->edx);
    r->eax = rd32(r, r->esp + 0x30);
    call_mem_keep(r, 0x4d6768, 8);
    r->ebx = 0x382d7365;
    r->ecx = 0x3fc0c152;
    call_mem_keep(r, 0x4db507, 8);
    call_mem_keep(r, 0x4c9daf, 8);
    r->ebx = 0;
    r->ecx = 0x3fe00000;
    call_mem_keep(r, 0x4db507, 8);
    r->ebx = rd32(r, r->esp + 0xe8);
    r->ecx = rd32(r, r->esp + 0x4);
    call_mem_keep(r, 0x4eb652, 8);
    call_mem_keep(r, 0x4eb606, 8);
    wr32(r, r->esi + 0x523bf0, r->eax);
    r->edx = 0;
    wr32(r, r->esi + 0x523cb0, r->edx);
    wr32(r, r->esi + 0x523c08, r->edx);
    r->eax = rd32(r, r->esp + 0x2c);
    call_mem_keep(r, 0x4d6768, 8);
    r->ebx = 0x54442d18;
    r->ecx = 0x400921fb;
    call_mem_keep(r, 0x4db507, 8);
    r->ebx = 0;
    r->ecx = 0x40520000;
    call_mem_keep(r, 0x4eb652, 8);
    call_mem_keep(r, 0x4c9dd6, 8);
    wr32(r, r->esp + 0x4, r->eax);
    wr32(r, r->esp + 0xe8, r->edx);
    r->eax = r->edi;
    call_mem_keep(r, 0x4d6768, 8);
    r->ebx = 0x382d7365;
    r->ecx = 0x3fc0c152;
    call_mem_keep(r, 0x4db507, 8);
    call_mem_keep(r, 0x4c9daf, 8);
    r->ebx = 0;
    r->ecx = 0x3fe00000;
    call_mem_keep(r, 0x4db507, 8);
    r->ebx = rd32(r, r->esp + 0x4);
    r->ecx = rd32(r, r->esp + 0xe8);
    call_mem_keep(r, 0x4eb652, 8);
    call_mem_keep(r, 0x4eb606, 8);
    wr32(r, r->esi + 0x523cc8, r->eax);
    r->edi = r->edi + 0x2;
    wr32(r, r->esp + 0x2c, rd32(r, r->esp + 0x2c) + 0x2);
    wr32(r, r->esp + 0x30, rd32(r, r->esp + 0x30) + 0x2);
    r->ebp = r->ebp + 0x2;
    wr32(r, r->esp + 0x34, rd32(r, r->esp + 0x34) + 0x2);
    r->esi = r->esi + 0x4;
    wr32(r, r->esp + 0x38, rd32(r, r->esp + 0x38) + 0x2);
    if (r->edi != 0xd && !r->port->env.failed)
    {
        goto at_4063e0;
    }
    r->esi = 0;
    r->edi = 0;
at_40658c:
    r->eax = r->esi;
    call_mem_keep(r, 0x4d6768, 8);
    r->ebx = 0x4ae74489;
    r->ecx = 0x3fc65718;
    call_mem_keep(r, 0x4db507, 8);
    call_mem_keep(r, 0x4c9dd6, 8);
    call_mem_keep(r, 0x4eb606, 8);
    wr32(r, r->edi + 0x52c2c4, r->eax);
    r->edi = r->edi + 0x4;
    r->esi = r->esi + 1;
    if ((int32_t)r->esi < (int32_t)0x9 && !r->port->env.failed)
    {
        goto at_40658c;
    }
    r->edi = 0;
    r->esi = 0x1;
    r->ebp = 0x3fe00000;
at_4065c7:
    r->eax = r->esi;
    call_mem_keep(r, 0x4d6768, 8);
    r->ebx = 0x54442d18;
    r->ecx = 0x400921fb;
    call_mem_keep(r, 0x4db507, 8);
    r->ebx = 0;
    r->ecx = 0x40420000;
    call_mem_keep(r, 0x4eb652, 8);
    call_mem_keep(r, 0x4c9dd6, 8);
    r->ebx = r->eax;
    r->ecx = r->edx;
    r->eax = 0;
    r->edx = r->ebp;
    call_mem_keep(r, 0x4eb652, 8);
    call_mem_keep(r, 0x4eb606, 8);
    wr32(r, r->edi + 0x52c2e8, r->eax);
    r->edi = r->edi + 0x4;
    r->esi = r->esi + 0x2;
    if (r->esi != 0x13 && !r->port->env.failed)
    {
        goto at_4065c7;
    }
    r->edi = 0;
    r->esi = 0x1;
    r->ebp = 0x3fe00000;
at_40661d:
    r->eax = r->esi;
    call_mem_keep(r, 0x4d6768, 8);
    r->ebx = 0x54442d18;
    r->ecx = 0x400921fb;
    call_mem_keep(r, 0x4db507, 8);
    r->ebx = 0;
    r->ecx = 0x40280000;
    call_mem_keep(r, 0x4eb652, 8);
    call_mem_keep(r, 0x4c9dd6, 8);
    r->ebx = r->eax;
    r->ecx = r->edx;
    r->eax = 0;
    r->edx = r->ebp;
    call_mem_keep(r, 0x4eb652, 8);
    call_mem_keep(r, 0x4eb606, 8);
    wr32(r, r->edi + 0x524274, r->eax);
    r->edi = r->edi + 0x4;
    r->esi = r->esi + 0x2;
    if (r->esi != 0x7 && !r->port->env.failed)
    {
        goto at_40661d;
    }
    r->eax = 0x382d7366;
    r->edx = 0x3fe0c152;
    call_mem_keep(r, 0x4c9dd6, 8);
    call_mem_keep(r, 0x4eb606, 8);
    wr32(r, 0x524284, r->eax);
    r->eax = 0x382d7367;
    r->edx = 0x3ff0c152;
    call_mem_keep(r, 0x4c9dd6, 8);
    call_mem_keep(r, 0x4eb606, 8);
    wr32(r, 0x524280, r->eax);
    r->ecx = 0;
    wr32(r, r->esp + 0xd8, r->ecx);
    wr32(r, r->esp + 0x40, 0x18);
    wr32(r, r->esp + 0x44, 0xe);
    wr32(r, r->esp + 0x48, r->ecx);
    wr32(r, r->esp + 0x4c, 0x1);
at_4066be:
    r->esi = rd32(r, r->esp + 0xd8);
    r->esi = r->esi + r->esi;
    r->eax = rd32(r, r->esp + 0x4c);
    call_mem_keep(r, 0x4d6768, 8);
    r->ebx = 0x382d7365;
    r->ecx = 0x3fc0c152;
    call_mem_keep(r, 0x4db507, 8);
    call_mem_keep(r, 0x4c9daf, 8);
    r->ebx = 0;
    r->ecx = 0x3fe00000;
    call_mem_keep(r, 0x4db507, 8);
    r->ebp = r->eax;
    r->edi = r->edx;
    r->esi = r->esi + 0x7;
    r->eax = r->esi;
    call_mem_keep(r, 0x4d6768, 8);
    r->ebx = 0x54442d18;
    r->ecx = 0x400921fb;
    call_mem_keep(r, 0x4db507, 8);
    r->ebx = 0;
    r->ecx = 0x40380000;
    call_mem_keep(r, 0x4eb652, 8);
    call_mem_keep(r, 0x4c9dd6, 8);
    r->ebx = r->eax;
    r->ecx = r->edx;
    r->eax = r->ebp;
    r->edx = r->edi;
    call_mem_keep(r, 0x4eb652, 8);
    call_mem_keep(r, 0x4eb606, 8);
    r->edx = rd32(r, r->esp + 0x48);
    wr32(r, r->edx + 0x523c20, r->eax);
    r->edi = rd32(r, r->esp + 0xd8);
    r->edi = r->edi << 0x2;
    r->edi = r->edi - rd32(r, r->esp + 0xd8);
    r->edi = r->edi << 0x3;
    r->ebp = rd32(r, r->esp + 0x44);
    r->eax = r->esi * 0x0;
    r->esi = r->esi + r->eax;
    r->eax = rd32(r, r->esp + 0x40);
    wr32(r, r->esp + 0x3c, r->eax);
at_40675f:
    r->eax = r->esi;
    call_mem_keep(r, 0x4d6768, 8);
    r->ebx = 0x382d7365;
    r->ecx = 0x3fc0c152;
    call_mem_keep(r, 0x4db507, 8);
    call_mem_keep(r, 0x4c9dd6, 8);
    call_mem_keep(r, 0x4eb606, 8);
    wr32(r, r->edi + 0x523d40, r->eax);
    r->edi = r->edi + 0x4;
    r->esi = r->esi + r->ebp;
    if (r->edi != rd32(r, r->esp + 0x3c) && !r->port->env.failed)
    {
        goto at_40675f;
    }
    wr32(r, r->esp + 0x40, rd32(r, r->esp + 0x40) + 0x18);
    wr32(r, r->esp + 0x44, rd32(r, r->esp + 0x44) + 0x4);
    wr32(r, r->esp + 0x48, rd32(r, r->esp + 0x48) + 0x4);
    wr32(r, r->esp + 0x4c, rd32(r, r->esp + 0x4c) + 0x2);
    r->ebp = rd32(r, r->esp + 0xd8);
    r->ebp = r->ebp + 1;
    wr32(r, r->esp + 0xd8, r->ebp);
    if ((int32_t)r->ebp < (int32_t)0xc && !r->port->env.failed)
    {
        goto at_4066be;
    }
    r->esi = 0;
    r->edi = 0;
    r->ebp = 0x1;
at_4067c5:
    r->edx = 0;
    r->ebx = r->esi;
    r->eax = r->edi;
    if ((int32_t)rd32(r, r->esi + 0x4f5e68) <= (int32_t)0x0)
    {
        goto at_4067ee;
    }
at_4067d4:
    r->ecx = rd32(r, r->eax + 0x523b00);
    wr32(r, r->eax + 0x5238c0, r->ecx);
    r->eax = r->eax + 0x8;
    r->edx = r->edx + 0x2;
    if ((int32_t)r->edx < (int32_t)rd32(r, r->ebx + 0x4f5e68) && !r->port->env.failed)
    {
        goto at_4067d4;
    }
at_4067ee:
    r->ecx = r->ebp;
    r->ebx = r->esi;
    r->edx = r->edi + 0x4;
    if ((int32_t)r->ebp >= (int32_t)rd32(r, r->esi + 0x4f5e68))
    {
        goto at_40681c;
    }
at_4067fd:
    r->eax = rd32(r, r->edx + 0x523b00);
    call_mem_keep(r, 0x4eb5b4, 8);
    wr32(r, r->edx + 0x5238c0, r->eax);
    r->edx = r->edx + 0x8;
    r->ecx = r->ecx + 0x2;
    if ((int32_t)r->ecx < (int32_t)rd32(r, r->ebx + 0x4f5e68) && !r->port->env.failed)
    {
        goto at_4067fd;
    }
at_40681c:
    r->esi = r->esi + 0x4;
    r->edi = r->edi + 0x90;
    if (r->esi != 0x10 && !r->port->env.failed)
    {
        goto at_4067c5;
    }
    r->edx = 0;
    wr32(r, r->esp + 0xd4, r->edx);
    wr32(r, r->esp + 0x54, r->edx);
at_406837:
    r->eax = rd32(r, r->esp + 0xd4);
    call_mem_keep(r, 0x4d6768, 8);
    r->ebx = 0x54442d18;
    r->ecx = 0x400921fb;
    call_mem_keep(r, 0x4db507, 8);
    r->ebx = 0;
    r->ecx = 0x40280000;
    call_mem_keep(r, 0x4eb652, 8);
    call_mem_keep(r, 0x4c9e00, 8);
    r->ebp = r->eax;
    wr32(r, r->esp + 0x8, r->edx);
    r->ebx = 0;
    r->ecx = 0x3ff00000;
    call_mem_keep(r, 0x4db350, 8);
    r->esi = r->eax;
    r->edi = r->edx;
    r->eax = r->ebp;
    r->edx = rd32(r, r->esp + 0x8);
    r->ebx = r->esi;
    r->ecx = r->edi;
    call_mem_keep(r, 0x4eb652, 8);
    call_mem_keep(r, 0x4eb606, 8);
    r->edx = rd32(r, r->esp + 0x54);
    wr32(r, r->edx + 0x523218, r->eax);
    r->eax = 0;
    r->edx = 0x3ff00000;
    r->ebx = r->esi;
    r->ecx = r->edi;
    call_mem_keep(r, 0x4eb652, 8);
    call_mem_keep(r, 0x4eb606, 8);
    r->edx = rd32(r, r->esp + 0x54);
    wr32(r, r->edx + 0x523198, r->eax);
    r->eax = r->ebp;
    r->edx = rd32(r, r->esp + 0x8);
    r->ebx = 0x667f3bcc;
    r->ecx = 0x3ff6a09e;
    call_mem_keep(r, 0x4db507, 8);
    r->ebx = r->esi;
    r->ecx = r->edi;
    call_mem_keep(r, 0x4eb652, 8);
    call_mem_keep(r, 0x4eb606, 8);
    r->edx = rd32(r, r->esp + 0x54);
    wr32(r, r->edx + 0x523258, r->eax);
    r->eax = 0x667f3bcc;
    r->edx = 0x3ff6a09e;
    r->ebx = r->esi;
    r->ecx = r->edi;
    call_mem_keep(r, 0x4eb652, 8);
    call_mem_keep(r, 0x4eb606, 8);
    r->edx = rd32(r, r->esp + 0x54);
    wr32(r, r->edx + 0x5231d8, r->eax);
    r->ebx = 0;
    wr32(r, r->esp + 0xdc, r->ebx);
    wr32(r, r->esp + 0x50, r->edx);
at_406912:
    r->eax = rd32(r, r->esp + 0xdc);
    call_mem_keep(r, 0x4d6768, 8);
    r->ebx = 0;
    r->ecx = 0x3ff00000;
    call_mem_keep(r, 0x4db350, 8);
    r->ebx = 0;
    r->ecx = 0xbfd00000u;
    call_mem_keep(r, 0x4db507, 8);
    r->ebx = r->eax;
    r->ecx = r->edx;
    r->eax = 0;
    r->edx = 0x40000000;
    call_mem_keep(r, 0x4c9921, 8);
    wr32(r, r->esp + 0xc, r->eax);
    wr32(r, r->esp + 0x10, r->edx);
    r->ebp = 0;
    r->esi = 0x3ff00000;
    wr32(r, r->esp + 0x14, r->ebp);
    r->edi = r->esi;
    if ((int32_t)rd32(r, r->esp + 0xd4) <= (int32_t)0x0)
    {
        goto at_4069a9;
    }
    if ((uint8_t)(rd8(r, r->esp + 0xd4) & 0x1) == 0)
    {
        goto at_406fdd;
    }
    r->eax = rd32(r, r->esp + 0xd4);
    call_mem_keep(r, 0x4d6768, 8);
    r->ebx = 0;
    r->ecx = r->esi;
    call_mem_keep(r, 0x4db350, 8);
    r->ebx = 0;
    r->ecx = 0x3fe00000;
    call_mem_keep(r, 0x4db507, 8);
    r->ebx = r->eax;
    r->ecx = r->edx;
    r->eax = rd32(r, r->esp + 0xc);
    r->edx = rd32(r, r->esp + 0x10);
    call_mem_keep(r, 0x4c9921, 8);
    r->ebp = r->eax;
    r->esi = r->edx;
at_4069a9:
    r->eax = r->ebp;
    r->edx = r->esi;
    call_mem_keep(r, 0x4eb606, 8);
    r->edx = rd32(r, r->esp + 0x50);
    wr32(r, r->edx + 0x523118, r->eax);
    r->eax = rd32(r, r->esp + 0x14);
    r->edx = r->edi;
    call_mem_keep(r, 0x4eb606, 8);
    r->edx = rd32(r, r->esp + 0x50);
    wr32(r, r->edx + 0x523018, r->eax);
    r->eax = r->ebp;
    r->edx = r->esi;
    r->ebx = 0x667f3bcc;
    r->ecx = 0x3ff6a09e;
    call_mem_keep(r, 0x4db507, 8);
    call_mem_keep(r, 0x4eb606, 8);
    r->edx = rd32(r, r->esp + 0x50);
    wr32(r, r->edx + 0x523098, r->eax);
    r->eax = rd32(r, r->esp + 0x14);
    r->edx = r->edi;
    r->ebx = 0x667f3bcc;
    r->ecx = 0x3ff6a09e;
    call_mem_keep(r, 0x4db507, 8);
    call_mem_keep(r, 0x4eb606, 8);
    r->edx = rd32(r, r->esp + 0x50);
    wr32(r, r->edx + 0x522f98, r->eax);
    r->edx = r->edx + 0x40;
    wr32(r, r->esp + 0x50, r->edx);
    r->ecx = rd32(r, r->esp + 0xdc);
    r->ecx = r->ecx + 1;
    wr32(r, r->esp + 0xdc, r->ecx);
    if ((int32_t)r->ecx < (int32_t)0x2 && !r->port->env.failed)
    {
        goto at_406912;
    }
    wr32(r, r->esp + 0x54, rd32(r, r->esp + 0x54) + 0x4);
    r->edi = rd32(r, r->esp + 0xd4);
    r->edi = r->edi + 1;
    wr32(r, r->esp + 0xd4, r->edi);
    if ((int32_t)r->edi < (int32_t)0x10 && !r->port->env.failed)
    {
        goto at_406837;
    }
    r->ebp = 0x521210;
    wr32(r, r->esp + 0x58, 0x4f5918);
    wr32(r, r->esp + 0x5c, 0x51fc20);
    wr32(r, r->esp + 0x60, 0x522770);
    r->ebx = 0;
    wr32(r, r->esp + 0x64, r->ebx);
at_406a76:
    r->eax = rd32(r, r->esp + 0x58);
    wr32(r, r->esp + 0x18, r->eax);
    r->eax = rd32(r, r->esp + 0x64);
    wr32(r, r->eax + 0x524208, r->ebp);
    r->eax = r->ebp;
    r->ecx = rd32(r, r->esp + 0x58);
    r->ecx = r->ecx + 0x2e;
    r->edi = 0;
    r->edx = 0;
at_406a95:
    r->ebx = (uint32_t)(int32_t)(int16_t)rd16(r, r->ecx);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x1);
    wr32(r, r->eax, r->ebx);
    r->eax = r->eax + 0x4;
    wr32(r, r->eax, r->edi);
    r->eax = r->eax + 0x4;
    wr32(r, r->eax, 0x3);
    r->eax = r->eax + 0x4;
    wr32(r, r->eax, r->edx);
    r->ebx = (uint32_t)(int32_t)(int16_t)rd16(r, r->ecx);
    r->eax = r->eax + 0x4;
    r->edx = r->edx + 1;
    r->ecx = r->ecx + 0x2;
    r->edi = r->edi + r->ebx;
    if ((int32_t)r->edx < (int32_t)0x8 && !r->port->env.failed)
    {
        goto at_406a95;
    }
    r->edx = rd32(r, r->esp + 0x18);
    r->edx = r->edx + 0x7c;
    wr32(r, r->esp + 0xe4, r->edx);
    r->ebx = 0x3;
at_406ad3:
    r->esi = rd32(r, r->esp + 0xe4);
    r->esi = (uint32_t)(int32_t)(int16_t)rd16(r, r->esi);
    r->esi = (uint32_t)((int32_t)r->esi >> 0x1);
    r->edx = 0;
    wr32(r, r->esp + 0xe4, rd32(r, r->esp + 0xe4) + 0x2);
    r->ecx = r->edi;
at_406aeb:
    wr32(r, r->eax, r->esi);
    r->eax = r->eax + 0x4;
    wr32(r, r->eax, r->ecx);
    r->eax = r->eax + 0x4;
    wr32(r, r->eax, r->edx);
    r->eax = r->eax + 0x4;
    wr32(r, r->eax, r->ebx);
    r->eax = r->eax + 0x4;
    r->ecx = r->ecx + 1;
    r->edx = r->edx + 1;
    if ((int32_t)r->edx < (int32_t)0x3 && !r->port->env.failed)
    {
        goto at_406aeb;
    }
    r->esi = r->esi * 0x6;
    r->edi = r->edi + r->esi;
    r->ebx = r->ebx + 1;
    if ((int32_t)r->ebx < (int32_t)0xd && !r->port->env.failed)
    {
        goto at_406ad3;
    }
    r->edx = rd32(r, r->esp + 0x64);
    wr32(r, r->edx + 0x523e60, r->eax);
    r->eax = rd32(r, r->esp + 0x5c);
    wr32(r, r->edx + 0x52420c, r->eax);
    r->edx = rd32(r, r->esp + 0x18);
    r->edx = r->edx + 0x76;
    wr32(r, r->esp + 0xe0, r->edx);
    r->edi = 0;
    r->ebx = 0;
at_406b37:
    r->esi = rd32(r, r->esp + 0xe0);
    r->esi = (uint32_t)(int32_t)(int16_t)rd16(r, r->esi);
    r->esi = (uint32_t)((int32_t)r->esi >> 0x1);
    r->edx = 0;
    wr32(r, r->esp + 0xe0, rd32(r, r->esp + 0xe0) + 0x2);
    r->ecx = r->edi;
at_406b4f:
    wr32(r, r->eax, r->esi);
    r->eax = r->eax + 0x4;
    wr32(r, r->eax, r->ecx);
    r->eax = r->eax + 0x4;
    wr32(r, r->eax, r->edx);
    r->eax = r->eax + 0x4;
    wr32(r, r->eax, r->ebx);
    r->eax = r->eax + 0x4;
    r->ecx = r->ecx + 1;
    r->edx = r->edx + 1;
    if ((int32_t)r->edx < (int32_t)0x3 && !r->port->env.failed)
    {
        goto at_406b4f;
    }
    r->esi = r->esi * 0x6;
    r->edi = r->edi + r->esi;
    r->ebx = r->ebx + 1;
    if ((int32_t)r->ebx < (int32_t)0xd && !r->port->env.failed)
    {
        goto at_406b37;
    }
    r->edx = rd32(r, r->esp + 0x64);
    wr32(r, r->edx + 0x523e64, r->eax);
    r->eax = rd32(r, r->esp + 0x60);
    wr32(r, r->edx + 0x524210, r->eax);
    r->ecx = rd32(r, r->esp + 0x18);
    r->ecx = r->ecx + 0x2e;
    r->edx = 0;
at_406b92:
    r->ebx = (uint32_t)(int32_t)(int16_t)rd16(r, r->ecx);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x1);
    wr32(r, r->eax, r->ebx);
    r->ecx = r->ecx + 0x2;
    r->eax = r->eax + 0x4;
    wr32(r, r->eax, r->edx);
    r->eax = r->eax + 0x4;
    r->edx = r->edx + 1;
    if ((int32_t)r->edx < (int32_t)0x16 && !r->port->env.failed)
    {
        goto at_406b92;
    }
    r->edx = rd32(r, r->esp + 0x64);
    wr32(r, r->edx + 0x523e68, r->eax);
    r->ebp = r->ebp + 0x260;
    wr32(r, r->esp + 0x58, rd32(r, r->esp + 0x58) + 0x90);
    wr32(r, r->esp + 0x5c, rd32(r, r->esp + 0x5c) + 0x270);
    wr32(r, r->esp + 0x60, rd32(r, r->esp + 0x60) + 0xb0);
    r->eax = r->edx + 0xc;
    wr32(r, r->esp + 0x64, r->eax);
    if (r->eax != 0x6c && !r->port->env.failed)
    {
        goto at_406a76;
    }
    r->edi = 0;
    wr32(r, r->esp + 0x68, 0x2e);
    wr32(r, r->esp + 0x6c, r->edi);
    r->ebp = 0x1c;
    wr32(r, r->esp + 0x70, r->edi);
at_406bf9:
    r->ebx = r->edi * 0x90;
    r->ecx = rd32(r, r->esp + 0x6c);
    r->esi = rd32(r, r->esp + 0x68);
at_406c07:
    r->edx = rd32(r, r->ebx + 0x4f5916);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->edx = r->edx + 0x7;
    r->eax = r->edx;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    wr32(r, r->esp + 0xe8, 0x12);
    idiv32(r, rd32(r, r->esp + 0xe8));
    r->eax = r->eax + 1;
    wr32(r, r->ecx + 0x523ecc, r->eax);
    r->edx = rd32(r, r->esp);
    if ((int32_t)r->eax <= (int32_t)r->edx)
    {
        goto at_406c3e;
    }
    wr32(r, r->ecx + 0x523ecc, r->edx);
at_406c3e:
    r->ecx = r->ecx + 0x4;
    r->ebx = r->ebx + 0x2;
    if (r->ebx != r->esi && !r->port->env.failed)
    {
        goto at_406c07;
    }
    r->ebx = r->edi * 0x90;
    r->ecx = rd32(r, r->esp + 0x70);
    r->esi = r->ebp;
at_406c54:
    r->edx = rd32(r, r->ebx + 0x4f5970);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->edx = r->edx - 1;
    r->eax = r->edx;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    wr32(r, r->esp + 0xe8, 0x12);
    idiv32(r, rd32(r, r->esp + 0xe8));
    r->eax = r->eax + 1;
    wr32(r, r->ecx + 0x522da0, r->eax);
    r->edx = rd32(r, r->esp);
    if ((int32_t)r->eax <= (int32_t)r->edx)
    {
        goto at_406c89;
    }
    wr32(r, r->ecx + 0x522da0, r->edx);
at_406c89:
    r->ecx = r->ecx + 0x4;
    r->ebx = r->ebx + 0x2;
    if (r->ebx != r->esi && !r->port->env.failed)
    {
        goto at_406c54;
    }
    wr32(r, r->esp + 0x68, rd32(r, r->esp + 0x68) + 0x90);
    wr32(r, r->esp + 0x6c, rd32(r, r->esp + 0x6c) + 0x5c);
    r->ebp = r->ebp + 0x90;
    wr32(r, r->esp + 0x70, rd32(r, r->esp + 0x70) + 0x38);
    r->edi = r->edi + 1;
    if ((int32_t)r->edi < (int32_t)0x9 && !r->port->env.failed)
    {
        goto at_406bf9;
    }
    r->edi = 0;
    wr32(r, r->esp + 0xd0, r->edi);
    r->ebp = 0;
    wr32(r, r->esp + 0x80, r->edi);
at_406cc7:
    wr32(r, r->esp + 0x7c, r->ebp);
    r->edi = r->ebp;
    r->eax = rd32(r, r->esp + 0x80);
    r->eax = r->eax << 0x2;
    wr32(r, r->esp + 0x74, r->eax);
    r->eax = r->eax + 0x18;
    wr32(r, r->esp + 0x78, r->eax);
at_406ce2:
    r->ebx = rd32(r, r->esp + 0xd0);
    r->ebx = r->ebx | r->edi;
    r->eax = rd32(r, r->esp + 0x74);
    r->eax = r->eax + rd32(r, r->esp + 0x7c);
    r->edx = 0;
    r->esi = rd32(r, r->esp + 0x7c);
    r->esi = r->esi + rd32(r, r->esp + 0x78);
at_406cfd:
    r->ecx = r->ebx;
    r->ecx = r->ecx | r->edx;
    set_high8(&r->ecx, ((r->ecx >> 8) & 0xff) | 0x30);
    wr32(r, r->eax + 0x51f820, r->ecx);
    r->eax = r->eax + 0x4;
    r->edx = r->edx + 0x40;
    if (r->eax != r->esi && !r->port->env.failed)
    {
        goto at_406cfd;
    }
    wr32(r, r->esp + 0x7c, rd32(r, r->esp + 0x7c) + 0x18);
    r->edi = r->edi + 0x8;
    if (r->edi != 0x30 && !r->port->env.failed)
    {
        goto at_406ce2;
    }
    wr32(r, r->esp + 0x80, rd32(r, r->esp + 0x80) + 0x24);
    r->edi = rd32(r, r->esp + 0xd0);
    r->edi = r->edi + 1;
    wr32(r, r->esp + 0xd0, r->edi);
    if ((int32_t)r->edi < (int32_t)0x5 && !r->port->env.failed)
    {
        goto at_406cc7;
    }
    r->edx = 0;
    wr32(r, r->esp + 0xcc, r->edx);
    wr32(r, r->esp + 0x90, r->edx);
    r->ebp = 0;
at_406d4f:
    r->edi = r->ebp;
    wr32(r, r->esp + 0x8c, r->ebp);
    r->eax = rd32(r, r->esp + 0x90);
    r->eax = r->eax << 0x2;
    wr32(r, r->esp + 0x84, r->eax);
    r->eax = r->eax + 0x10;
    wr32(r, r->esp + 0x88, r->eax);
at_406d73:
    r->esi = rd32(r, r->esp + 0xcc);
    r->esi = r->esi | rd32(r, r->esp + 0x8c);
    r->eax = rd32(r, r->esp + 0x84);
    r->eax = r->eax + r->edi;
    r->edx = 0;
    r->ebx = rd32(r, r->esp + 0x88);
    r->ebx = r->ebx + r->edi;
at_406d95:
    r->ecx = r->esi;
    r->ecx = r->ecx | r->edx;
    set_high8(&r->ecx, ((r->ecx >> 8) & 0xff) | 0x40);
    wr32(r, r->eax + 0x51faf0, r->ecx);
    r->eax = r->eax + 0x4;
    r->edx = r->edx + 0x40;
    if (r->eax != r->ebx && !r->port->env.failed)
    {
        goto at_406d95;
    }
    r->edi = r->edi + 0x10;
    r->esi = rd32(r, r->esp + 0x8c);
    r->esi = r->esi + 0x8;
    wr32(r, r->esp + 0x8c, r->esi);
    if (r->esi != 0x20 && !r->port->env.failed)
    {
        goto at_406d73;
    }
    wr32(r, r->esp + 0x90, rd32(r, r->esp + 0x90) + 0x10);
    r->ecx = rd32(r, r->esp + 0xcc);
    r->ecx = r->ecx + 1;
    wr32(r, r->esp + 0xcc, r->ecx);
    if ((int32_t)r->ecx < (int32_t)0x4 && !r->port->env.failed)
    {
        goto at_406d4f;
    }
    r->esi = 0;
    r->ebp = 0xc;
    wr32(r, r->esp + 0x94, r->esi);
at_406df3:
    r->eax = rd32(r, r->esp + 0x94);
    r->edx = 0;
    r->edi = r->ebp;
at_406dfe:
    r->ecx = r->esi;
    r->ecx = r->ecx | r->edx;
    r->ebx = r->ecx;
    set_high8(&r->ebx, ((r->ebx >> 8) & 0xff) | 0x50);
    wr32(r, r->eax + 0x51fbf0, r->ebx);
    set_high8(&r->ecx, ((r->ecx >> 8) & 0xff) | 0xa0);
    wr32(r, r->eax + 0x51f7f0, r->ecx);
    r->eax = r->eax + 0x4;
    r->edx = r->edx + 0x8;
    if (r->eax != r->edi && !r->port->env.failed)
    {
        goto at_406dfe;
    }
    r->ebp = r->ebp + 0xc;
    wr32(r, r->esp + 0x94, rd32(r, r->esp + 0x94) + 0xc);
    r->esi = r->esi + 1;
    if ((int32_t)r->esi < (int32_t)0x4 && !r->port->env.failed)
    {
        goto at_406df3;
    }
    r->edx = 0;
    wr32(r, r->esp + 0xc8, r->edx);
    wr32(r, r->esp + 0xac, r->edx);
at_406e41:
    r->ebx = 0;
    wr32(r, r->esp + 0xa4, r->ebx);
    wr32(r, r->esp + 0xa8, r->ebx);
    r->eax = rd32(r, r->esp + 0xac);
    r->eax = r->eax << 0x2;
    wr32(r, r->esp + 0x98, r->eax);
    r->eax = r->eax + 0x10;
    wr32(r, r->esp + 0x9c, r->eax);
at_406e6c:
    r->eax = rd32(r, r->esp + 0xc8);
    r->edi = rd32(r, r->esp + 0xa4);
    r->eax = r->eax | r->edi;
    wr32(r, r->esp + 0x1c, r->eax);
    r->edi = 0;
    r->ebp = 0;
    r->eax = rd32(r, r->esp + 0xa8);
    r->eax = r->eax << 0x2;
    r->edx = rd32(r, r->esp + 0x98);
    r->edx = r->edx + r->eax;
    wr32(r, r->esp + 0xc0, r->edx);
    r->edx = rd32(r, r->esp + 0x9c);
    r->edx = r->edx + r->eax;
    wr32(r, r->esp + 0xa0, r->edx);
at_406eae:
    r->ebx = rd32(r, r->esp + 0x1c);
    r->ebx = r->ebx | r->ebp;
    r->eax = rd32(r, r->esp + 0xc0);
    r->eax = r->eax + r->edi;
    r->edx = 0;
    r->esi = rd32(r, r->esp + 0xa0);
    r->esi = r->esi + r->edi;
at_406ec8:
    r->ecx = r->ebx;
    r->ecx = r->ecx | r->edx;
    wr32(r, r->eax + 0x51f020, r->ecx);
    r->eax = r->eax + 0x4;
    r->edx = r->edx + 0x200;
    if (r->eax != r->esi && !r->port->env.failed)
    {
        goto at_406ec8;
    }
    r->edi = r->edi + 0x10;
    r->ebp = r->ebp + 0x40;
    if (r->edi != 0x40 && !r->port->env.failed)
    {
        goto at_406eae;
    }
    r->ebp = rd32(r, r->esp + 0xa4);
    r->ebp = r->ebp + 0x8;
    wr32(r, r->esp + 0xa4, r->ebp);
    wr32(r, r->esp + 0xa8, rd32(r, r->esp + 0xa8) + 0x10);
    if (r->ebp != 0x28 && !r->port->env.failed)
    {
        goto at_406e6c;
    }
    wr32(r, r->esp + 0xac, rd32(r, r->esp + 0xac) + 0x50);
    r->ebx = rd32(r, r->esp + 0xc8);
    r->ebx = r->ebx + 1;
    wr32(r, r->esp + 0xc8, r->ebx);
    if ((int32_t)r->ebx < (int32_t)0x5 && !r->port->env.failed)
    {
        goto at_406e41;
    }
    r->edi = 0;
    wr32(r, r->esp + 0xc4, r->edi);
    r->ebp = 0;
    wr32(r, r->esp + 0xbc, r->edi);
at_406f3e:
    wr32(r, r->esp + 0xb8, r->ebp);
    r->edi = r->ebp;
    r->eax = rd32(r, r->esp + 0xbc);
    r->eax = r->eax << 0x2;
    wr32(r, r->esp + 0xb0, r->eax);
    r->eax = r->eax + 0x10;
    wr32(r, r->esp + 0xb4, r->eax);
at_406f62:
    r->ebx = rd32(r, r->esp + 0xc4);
    r->ebx = r->ebx | r->edi;
    r->eax = rd32(r, r->esp + 0xb0);
    r->eax = r->eax + rd32(r, r->esp + 0xb8);
    r->edx = 0;
    r->esi = rd32(r, r->esp + 0xb8);
    r->esi = r->esi + rd32(r, r->esp + 0xb4);
at_406f89:
    r->ecx = r->ebx;
    r->ecx = r->ecx | r->edx;
    set_high8(&r->ecx, ((r->ecx >> 8) & 0xff) | 0x10);
    wr32(r, r->eax + 0x51f660, r->ecx);
    r->eax = r->eax + 0x4;
    r->edx = r->edx + 0x40;
    if (r->eax != r->esi && !r->port->env.failed)
    {
        goto at_406f89;
    }
    wr32(r, r->esp + 0xb8, rd32(r, r->esp + 0xb8) + 0x10);
    r->edi = r->edi + 0x8;
    if (r->edi != 0x28 && !r->port->env.failed)
    {
        goto at_406f62;
    }
    wr32(r, r->esp + 0xbc, rd32(r, r->esp + 0xbc) + 0x14);
    r->edi = rd32(r, r->esp + 0xc4);
    r->edi = r->edi + 1;
    wr32(r, r->esp + 0xc4, r->edi);
    if ((int32_t)r->edi < (int32_t)0x5 && !r->port->env.failed)
    {
        goto at_406f3e;
    }
    r->esp = r->esp + 0xec;
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_406fdd:
    r->eax = rd32(r, r->esp + 0xd4);
    call_mem_keep(r, 0x4d6768, 8);
    r->ebx = 0;
    r->ecx = 0x3fe00000;
    call_mem_keep(r, 0x4db507, 8);
    r->ebx = r->eax;
    r->ecx = r->edx;
    r->eax = rd32(r, r->esp + 0xc);
    r->edx = rd32(r, r->esp + 0x10);
    call_mem_keep(r, 0x4c9921, 8);
    wr32(r, r->esp + 0x14, r->eax);
    r->edi = r->edx;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4069a9;
}

uint32_t vertrix_port_mpeg_tables_init_406170(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x120
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4 * 8];
    Regs r;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 8);
    memset(&r, 0, sizeof r);
    r.port = &port;
    r.eax = entry->eax;
    r.edx = entry->edx;
    r.ebx = entry->ebx;
    r.ecx = entry->ecx;
    r.esi = entry->esi;
    r.edi = entry->edi;
    r.ebp = entry->ebp;
    r.esp = entry->esp;
    run(&r);
    return port_return(&port, r.eax, r.edx);
}
