#include "port_rtljpegprogressivestarts.h"

/* At 0x4c23f0 the routine checks the scan's Ss/Se/Ah/Al values (+0x190..+0x19c) and raises error
 * 0x10 through [esi] if they form an invalid progression (0x4c241c-0x4c2490, 0x4c261c-0x4c2648). */

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

static uint32_t rd32(Regs *r, uint32_t address)
{
    return port_u32(r->port, address, 0);
}

static void wr32(Regs *r, uint32_t address, uint32_t value)
{
    port_set32(r->port, address, 0, value);
}

static void set_low8(uint32_t *reg, uint32_t value)
{
    *reg = (*reg & 0xffffff00u) | (value & 0xff);
}

static uint32_t flag_mask(const Regs *r)
{
    return r->fw == 8 ? 0xffu : r->fw == 16 ? 0xffffu : 0xffffffffu;
}

static uint32_t result(const Regs *r)
{
    uint32_t mask = flag_mask(r);
    if (r->fk == F_SUB)
    {
        return (r->fa - r->fb) & mask;
    }
    if (r->fk == F_ADD)
    {
        return (r->fa + r->fb) & mask;
    }
    return r->fa & mask;
}

static uint32_t carry(const Regs *r)
{
    uint32_t mask = flag_mask(r);
    if (r->fk == F_SUB)
    {
        return (r->fa & mask) < (r->fb & mask);
    }
    if (r->fk == F_ADD)
    {
        return result(r) < (r->fa & mask);
    }
    if (r->fk == F_INC || r->fk == F_DEC)
    {
        return r->fc;
    }
    return 0;
}

/* The flags of an instruction recorded (width 8, 16 or 32). */
static void flags(Regs *r, unsigned kind, uint32_t a, uint32_t b, unsigned width)
{
    if (kind == F_INC || kind == F_DEC)
    {
        r->fc = carry(r);
    }
    r->fk = kind;
    r->fa = a;
    r->fb = b;
    r->fw = width;
}

static uint32_t overflow(const Regs *r)
{
    uint32_t top = 1u << (r->fw - 1);
    uint32_t value = result(r);
    if (r->fk == F_SUB)
    {
        return (((r->fa ^ r->fb) & (r->fa ^ value)) & top) != 0;
    }
    if (r->fk == F_ADD)
    {
        return ((~(r->fa ^ r->fb) & (r->fa ^ value)) & top) != 0;
    }
    if (r->fk == F_INC)
    {
        return value == top;
    }
    if (r->fk == F_DEC)
    {
        return value == top - 1;
    }
    return 0;
}

/* A condition of the recorded flags. */
static uint32_t cond(const Regs *r, unsigned code)
{
    uint32_t zero = result(r) == 0;
    uint32_t sign = (result(r) >> (r->fw - 1)) & 1;
    uint32_t less = sign != overflow(r);
    switch (code)
    {
        case CC_E:
            return zero;
        case CC_NE:
            return !zero;
        case CC_B:
            return carry(r);
        case CC_AE:
            return !carry(r);
        case CC_BE:
            return carry(r) || zero;
        case CC_A:
            return !carry(r) && !zero;
        case CC_L:
            return less;
        case CC_GE:
            return !less;
        case CC_LE:
            return less || zero;
        case CC_G:
            return !less && !zero;
        case CC_S:
            return sign;
        default:
            return !sign;
    }
}

/* An indirect call (an import or a method): every value pushed passed and popped, as stdcall. */
static void call_all(Regs *r, uint32_t target)
{
    call_with_stack(r, target, r->pushed, 0);
}

/* Original 0x4c23f0: At 0x4c23f0 the routine checks the scan's Ss/Se/Ah/Al values (+0x190..+0x19c)
 * and raises error 0x10 through [esi] if they form an invalid progression (0x4c241c-0x4c2490,
 * 0x4c261c-0x4c2648). For each component in the scan it updates coef_bits (+0xa0, component<<8) to
 * Al, issuing warning 0x73 through [err+4] on a mismatch (0x4c24f6-0x4c2515, 0x4c265e-0x4c267d). It
 * installs one of four decode methods (0x4c2780/0x4c29c0/0x4c2c50/0x4c2d60) depending on DC or AC
 * and first pass or refinement, builds the DC or AC derived Huffman tables through 0x4bbc00
 * (0x4c25be, 0x4c26d7), clears the bit-buffer and EOB state, and copies restart_interval (+0x114)
 * into the decoder (0x4c25e7-0x4c260f). This matches libjpeg's start_pass_phuff_decoder
 * (jdphuff.c). Evidence: calls 0x4bbc00. Register-for-register from the listing
 * (0x4c23fb..0x4c26eb); labels are the original addresses. */
static void run(Regs *r)
{
    r->esi = r->eax;
    r->eax = rd32(r, r->eax + 0x1bc);
    r->edx = rd32(r, r->esi + 0x190);
    r->ecx = 0;
    wr32(r, r->ebp - 0x2c, r->eax);
    flags(r, F_LOGIC, r->edx, 0, 32);
    set_low8(&r->eax, cond(r, CC_E));
    set_low8(&r->ecx, (r->eax & 0xff));
    wr32(r, r->ebp - 0x30, r->ecx);
    r->eax = 0;
    if (r->ecx == 0)
    {
        goto at_4c261c;
    }
    flags(r, F_SUB, rd32(r, r->esi + 0x194), 0x0, 32);
at_4c2429:
    if (cond(r, CC_E))
    {
        goto at_4c2430;
    }
    r->eax = 0x1;
at_4c2430:
    r->ebx = rd32(r, r->esi + 0x198);
    if (r->ebx == 0)
    {
        goto at_4c244a;
    }
    r->ecx = r->ebx - 0x1;
    if (r->ecx == rd32(r, r->esi + 0x19c))
    {
        goto at_4c244a;
    }
    r->eax = 0x1;
at_4c244a:
    if ((int32_t)rd32(r, r->esi + 0x19c) <= (int32_t)0xd)
    {
        goto at_4c2648;
    }
at_4c2457:
    r->eax = rd32(r, r->esi);
    wr32(r, r->eax + 0x14, 0x10);
    r->ecx = rd32(r, r->esi);
    r->eax = rd32(r, r->esi + 0x190);
    wr32(r, r->ecx + 0x18, r->eax);
    r->ecx = rd32(r, r->esi);
    r->eax = rd32(r, r->esi + 0x194);
    wr32(r, r->ecx + 0x1c, r->eax);
    r->eax = rd32(r, r->esi);
    r->ecx = rd32(r, r->esi + 0x198);
    wr32(r, r->eax + 0x20, r->ecx);
    r->ecx = rd32(r, r->esi);
    r->eax = rd32(r, r->esi + 0x19c);
    wr32(r, r->ecx + 0x24, r->eax);
    r->ecx = rd32(r, r->esi);
    r->eax = r->esi;
    call_all(r, rd32(r, r->ecx));
at_4c2492:
    r->ecx = 0;
    r->ebx = rd32(r, r->esi + 0x148);
    wr32(r, r->ebp - 0x1c, r->ecx);
    if ((int32_t)r->ebx <= 0)
    {
        goto at_4c254c;
    }
    wr32(r, r->ebp - 0x20, r->esi);
at_4c24a8:
    r->eax = rd32(r, r->ebp - 0x20);
    r->eax = rd32(r, r->eax + 0x14c);
    r->eax = rd32(r, r->eax + 0x4);
    r->edi = rd32(r, r->esi + 0xa0);
    wr32(r, r->ebp - 0x18, r->eax);
    r->eax = r->eax << 0x8;
    r->edx = rd32(r, r->ebp - 0x30);
    r->edi = r->edi + r->eax;
    if (r->edx == 0)
    {
        goto at_4c2655;
    }
at_4c24cd:
    r->ebx = rd32(r, r->esi + 0x190);
    if ((int32_t)r->ebx > (int32_t)rd32(r, r->esi + 0x194))
    {
        goto at_4c252e;
    }
    r->ecx = r->ebx * 4;
    r->ecx = r->ecx + r->edi;
at_4c24e4:
    r->eax = rd32(r, r->ecx);
    if ((int32_t)r->eax < 0)
    {
        goto at_4c2685;
    }
at_4c24ee:
    if (r->eax == rd32(r, r->esi + 0x198))
    {
        goto at_4c2518;
    }
    r->eax = rd32(r, r->esi);
    wr32(r, r->eax + 0x14, 0x73);
    r->eax = rd32(r, r->esi);
    r->edi = rd32(r, r->ebp - 0x18);
    wr32(r, r->eax + 0x18, r->edi);
    r->eax = rd32(r, r->esi);
    wr32(r, r->eax + 0x1c, r->ebx);
    r->edi = rd32(r, r->esi);
    r->edx = 0xffffffffu;
    r->eax = r->esi;
    call_all(r, rd32(r, r->edi + 0x4));
at_4c2518:
    r->eax = rd32(r, r->esi + 0x19c);
    wr32(r, r->ecx, r->eax);
    r->ebx = r->ebx + 1;
    r->edi = rd32(r, r->esi + 0x194);
    r->ecx = r->ecx + 0x4;
    if ((int32_t)r->ebx <= (int32_t)r->edi && !r->port->env.failed)
    {
        goto at_4c24e4;
    }
at_4c252e:
    r->edi = rd32(r, r->ebp - 0x20);
    r->eax = rd32(r, r->ebp - 0x1c);
    r->edx = rd32(r, r->esi + 0x148);
    r->edi = r->edi + 0x4;
    r->eax = r->eax + 1;
    wr32(r, r->ebp - 0x20, r->edi);
    wr32(r, r->ebp - 0x1c, r->eax);
    if ((int32_t)r->eax < (int32_t)r->edx && !r->port->env.failed)
    {
        goto at_4c24a8;
    }
at_4c254c:
    if (rd32(r, r->esi + 0x198) != 0x0)
    {
        goto at_4c269b;
    }
    if (rd32(r, r->ebp - 0x30) == 0x0)
    {
        goto at_4c268c;
    }
    r->eax = rd32(r, r->ebp - 0x2c);
    wr32(r, r->eax + 0x4, 0x4c2780);
at_4c256d:
    r->eax = rd32(r, r->esi + 0x148);
    r->edi = 0;
    if ((int32_t)r->eax <= 0)
    {
        goto at_4c25e7;
    }
    r->eax = rd32(r, r->ebp - 0x2c);
    r->eax = r->eax + 0x2c;
    wr32(r, r->ebp - 0x34, r->eax);
    r->eax = rd32(r, r->ebp - 0x2c);
    wr32(r, r->ebp - 0x24, r->esi);
    wr32(r, r->ebp - 0x28, r->eax);
at_4c258b:
    r->ebx = rd32(r, r->ebp - 0x24);
    r->eax = rd32(r, r->ebp - 0x30);
    r->ebx = rd32(r, r->ebx + 0x14c);
    if (r->eax == 0)
    {
        goto at_4c26bf;
    }
    if (rd32(r, r->esi + 0x198) != 0x0)
    {
        goto at_4c25c3;
    }
    r->ebx = rd32(r, r->ebx + 0x14);
    r->edx = rd32(r, r->ebp - 0x34);
    r->ecx = r->ebx * 4;
    r->eax = r->esi;
    r->ecx = r->ecx + r->edx;
    r->edx = 0x1;
    call(r, 0x4bbc00, 0);
at_4c25c3:
    r->eax = rd32(r, r->ebp - 0x28);
    r->edx = rd32(r, r->ebp - 0x24);
    r->edi = r->edi + 1;
    r->edx = r->edx + 0x4;
    r->ecx = r->eax + 0x4;
    wr32(r, r->eax + 0x18, 0x0);
    wr32(r, r->ebp - 0x24, r->edx);
    r->ebx = rd32(r, r->esi + 0x148);
    wr32(r, r->ebp - 0x28, r->ecx);
    if ((int32_t)r->edi < (int32_t)r->ebx && !r->port->env.failed)
    {
        goto at_4c258b;
    }
at_4c25e7:
    r->eax = rd32(r, r->ebp - 0x2c);
    wr32(r, r->eax + 0x10, 0x0);
    wr32(r, r->eax + 0xc, 0x0);
    wr32(r, r->eax + 0x8, 0x0);
    wr32(r, r->eax + 0x14, 0x0);
    r->ecx = rd32(r, r->ebp - 0x2c);
    r->eax = rd32(r, r->esi + 0x114);
    wr32(r, r->ecx + 0x28, r->eax);
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4c261c:
    r->ebx = rd32(r, r->esi + 0x194);
    if ((int32_t)r->edx <= (int32_t)r->ebx)
    {
        goto at_4c2637;
    }
at_4c2626:
    r->eax = 0x1;
    flags(r, F_SUB, rd32(r, r->esi + 0x148), 0x1, 32);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c2429;
at_4c2637:
    if ((int32_t)r->ebx >= (int32_t)0x40 && !r->port->env.failed)
    {
        goto at_4c2626;
    }
    flags(r, F_SUB, rd32(r, r->esi + 0x148), 0x1, 32);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c2429;
at_4c2648:
    if (r->eax != 0 && !r->port->env.failed)
    {
        goto at_4c2457;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c2492;
at_4c2655:
    if ((int32_t)rd32(r, r->edi) >= (int32_t)0x0 && !r->port->env.failed)
    {
        goto at_4c24cd;
    }
    r->eax = rd32(r, r->esi);
    wr32(r, r->eax + 0x14, 0x73);
    r->eax = rd32(r, r->esi);
    r->ecx = rd32(r, r->ebp - 0x18);
    wr32(r, r->eax + 0x18, r->ecx);
    r->eax = rd32(r, r->esi);
    wr32(r, r->eax + 0x1c, r->edx);
    r->ecx = rd32(r, r->esi);
    r->edx = 0xffffffffu;
    r->eax = r->esi;
    call_all(r, rd32(r, r->ecx + 0x4));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c24cd;
at_4c2685:
    r->eax = 0;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c24ee;
at_4c268c:
    r->eax = rd32(r, r->ebp - 0x2c);
    wr32(r, r->eax + 0x4, 0x4c29c0);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c256d;
at_4c269b:
    if (rd32(r, r->ebp - 0x30) == 0x0)
    {
        goto at_4c26b0;
    }
    r->eax = rd32(r, r->ebp - 0x2c);
    wr32(r, r->eax + 0x4, 0x4c2c50);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c256d;
at_4c26b0:
    r->eax = rd32(r, r->ebp - 0x2c);
    wr32(r, r->eax + 0x4, 0x4c2d60);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c256d;
at_4c26bf:
    r->ebx = rd32(r, r->ebx + 0x18);
    r->eax = r->ebx * 4;
    r->ecx = rd32(r, r->ebp - 0x34);
    wr32(r, r->ebp - 0x38, r->eax);
    r->edx = r->eax;
    r->ecx = r->ecx + r->eax;
    r->edx = r->edx ^ r->eax;
    r->eax = r->esi;
    call(r, 0x4bbc00, 0);
    r->eax = rd32(r, r->ebp - 0x2c);
    r->eax = r->eax + rd32(r, r->ebp - 0x38);
    r->ecx = rd32(r, r->ebp - 0x2c);
    r->eax = rd32(r, r->eax + 0x2c);
    wr32(r, r->ecx + 0x3c, r->eax);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c25c3;
}

uint32_t vertrix_port_jpeg_progressive_huff_start_pass_4c23f0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x3c
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
