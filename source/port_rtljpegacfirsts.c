#include "port_rtljpegacfirsts.h"

/* libjpeg decode_mcu_AC_first: the first progressive AC pass for one block, with the end-of-band
 * run. */

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

static void call(Regs *r, uint32_t target, unsigned count)
{
    call_with_stack(r, target, count, 0);
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

static uint32_t rd32(Regs *r, uint32_t address)
{
    return port_u32(r->port, address, 0);
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

/* Original 0x4c29c0: libjpeg decode_mcu_AC_first: the first progressive AC pass for one block, with
 * the end-of-band run. Evidence: calls 0x4c26f0, 0x4bbf30, 0x4bc050. Register-for-register from the
 * listing (0x4c29ca..0x4c2c41); labels are the original addresses. */
static void run(Regs *r)
{
    wr32(r, r->ebp - 0x30, r->eax);
    r->ecx = r->edx;
    r->eax = rd32(r, r->eax + 0x1bc);
    wr32(r, r->ebp - 0x34, r->eax);
    r->eax = rd32(r, r->ebp - 0x30);
    r->eax = rd32(r, r->eax + 0x194);
    wr32(r, r->ebp - 0x24, r->eax);
    r->eax = rd32(r, r->ebp - 0x30);
    r->eax = rd32(r, r->eax + 0x19c);
    wr32(r, r->ebp - 0x2c, r->eax);
    r->eax = rd32(r, r->ebp - 0x30);
    if (rd32(r, r->eax + 0x114) == 0x0)
    {
        goto at_4c2a12;
    }
    r->eax = rd32(r, r->ebp - 0x34);
    r->ebx = rd32(r, r->eax + 0x28);
    if (r->ebx != 0)
    {
        goto at_4c2a12;
    }
    r->eax = rd32(r, r->ebp - 0x30);
    call_keep(r, 0x4c26f0);
    if (r->eax == 0)
    {
        goto at_4c2a3f;
    }
at_4c2a12:
    r->eax = rd32(r, r->ebp - 0x34);
    if (rd32(r, r->eax + 0x8) != 0x0)
    {
        goto at_4c2a34;
    }
    r->eax = rd32(r, r->eax + 0x14);
    wr32(r, r->ebp - 0x38, r->eax);
    if (r->eax == 0)
    {
        goto at_4c2a4a;
    }
    r->edx = r->eax - 0x1;
    wr32(r, r->ebp - 0x38, r->edx);
at_4c2a2b:
    r->edx = rd32(r, r->ebp - 0x34);
    r->eax = rd32(r, r->ebp - 0x38);
    wr32(r, r->edx + 0x14, r->eax);
at_4c2a34:
    r->eax = rd32(r, r->ebp - 0x34);
    r->ebx = 0x1;
    wr32(r, r->eax + 0x28, rd32(r, r->eax + 0x28) - r->ebx);
at_4c2a3f:
    r->eax = r->ebx;
    r->edi = rd32(r, r->ebp - 0x10);
    r->esi = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4c2a4a:
    r->eax = rd32(r, r->ebp - 0x30);
    wr32(r, r->ebp - 0x40, r->eax);
    r->eax = rd32(r, r->eax + 0x18);
    r->eax = rd32(r, r->eax);
    wr32(r, r->ebp - 0x50, r->eax);
    r->eax = rd32(r, r->ebp - 0x30);
    r->eax = rd32(r, r->eax + 0x18);
    r->edx = rd32(r, r->ebp - 0x34);
    r->ebx = rd32(r, r->ebp - 0x34);
    r->eax = rd32(r, r->eax + 0x4);
    r->edi = rd32(r, r->ebp - 0x34);
    wr32(r, r->ebp - 0x4c, r->eax);
    r->esi = rd32(r, r->ebp - 0x30);
    r->edx = rd32(r, r->edx + 0xc);
    r->ebx = rd32(r, r->ebx + 0x10);
    r->eax = rd32(r, r->ecx);
    r->esi = rd32(r, r->esi + 0x190);
    wr32(r, r->ebp - 0x28, r->eax);
    r->eax = rd32(r, r->ebp - 0x24);
    r->edi = rd32(r, r->edi + 0x3c);
    if ((int32_t)r->esi > (int32_t)r->eax)
    {
        goto at_4c2b65;
    }
at_4c2a8f:
    if ((int32_t)r->ebx < (int32_t)0x8)
    {
        goto at_4c2b8a;
    }
at_4c2a98:
    r->ecx = r->ebx - 0x8;
    r->eax = r->edx;
    r->eax = (uint32_t)((int32_t)r->eax >> (r->ecx & 0xff));
    r->ecx = r->eax;
    r->ecx = r->ecx & 0xff;
    r->eax = r->ecx;
    r->eax = rd32(r, r->edi + r->eax * 4 + 0x90);
    if (r->eax == 0)
    {
        goto at_4c2bdb;
    }
    r->ebx = r->ebx - r->eax;
    r->eax = r->ecx;
    set_low8(&r->eax, rd8(r, r->edi + r->eax + 0x490));
    r->eax = r->eax & 0xff;
    wr32(r, r->ebp - 0x18, r->eax);
at_4c2acb:
    r->eax = rd32(r, r->ebp - 0x18);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x4);
    wr32(r, r->ebp - 0x1c, r->eax);
    r->eax = rd32(r, r->ebp - 0x18);
    r->eax = r->eax & 0xf;
    flags(r, F_LOGIC, r->eax, 0, 32);
    wr32(r, r->ebp - 0x18, r->eax);
    if (cond(r, CC_E))
    {
        goto at_4c2be4;
    }
    r->eax = rd32(r, r->ebp - 0x1c);
    r->ecx = rd32(r, r->ebp - 0x18);
    r->esi = r->esi + r->eax;
    if ((int32_t)r->ebx >= (int32_t)r->ecx)
    {
        goto at_4c2b05;
    }
    r->eax = r->ebp - 0x50;
    call_keep(r, 0x4bbf30);
    if (r->eax == 0)
    {
        goto at_4c2bce;
    }
    r->edx = rd32(r, r->ebp - 0x48);
    r->ebx = rd32(r, r->ebp - 0x44);
at_4c2b05:
    r->ebx = r->ebx - rd32(r, r->ebp - 0x18);
    set_low8(&r->ecx, (r->ebx & 0xff));
    r->eax = r->edx;
    r->eax = (uint32_t)((int32_t)r->eax >> (r->ecx & 0xff));
    set_low8(&r->ecx, rd8(r, r->ebp - 0x18));
    wr32(r, r->ebp - 0x3c, r->eax);
    r->eax = 0x1;
    r->eax = r->eax << (r->ecx & 0xff);
    r->ecx = rd32(r, r->ebp - 0x3c);
    r->eax = r->eax - 1;
    r->ecx = r->ecx & r->eax;
    r->eax = rd32(r, r->ebp - 0x18);
    r->eax = r->eax << 0x2;
    if ((int32_t)r->ecx >= (int32_t)rd32(r, r->eax + 0x4ffd3c))
    {
        goto at_4c2b35;
    }
    r->ecx = r->ecx + rd32(r, r->eax + 0x4ffd7c);
at_4c2b35:
    r->eax = r->ecx;
    wr32(r, r->ebp - 0x18, r->eax);
    set_low8(&r->ecx, rd8(r, r->ebp - 0x2c));
    r->eax = rd32(r, r->ebp - 0x18);
    r->eax = r->eax << (r->ecx & 0xff);
    wr32(r, r->ebp - 0x14, r->eax);
    r->eax = rd32(r, r->esi * 4 + 0x5000d0);
    r->ecx = rd32(r, r->ebp - 0x28);
    r->eax = r->eax + r->eax;
    r->eax = r->eax + r->ecx;
    r->ecx = rd32(r, r->ebp - 0x14);
    wr16(r, r->eax, (r->ecx & 0xffff));
at_4c2b59:
    r->ecx = rd32(r, r->ebp - 0x24);
    r->esi = r->esi + 1;
    if ((int32_t)r->esi <= (int32_t)r->ecx && !r->port->env.failed)
    {
        goto at_4c2a8f;
    }
at_4c2b65:
    r->ecx = rd32(r, r->ebp - 0x30);
    r->ecx = rd32(r, r->ecx + 0x18);
    r->eax = rd32(r, r->ebp - 0x50);
    wr32(r, r->ecx, r->eax);
    r->ecx = rd32(r, r->ebp - 0x30);
    r->ecx = rd32(r, r->ecx + 0x18);
    r->eax = rd32(r, r->ebp - 0x4c);
    wr32(r, r->ecx + 0x4, r->eax);
    r->eax = rd32(r, r->ebp - 0x34);
    wr32(r, r->eax + 0xc, r->edx);
    wr32(r, r->eax + 0x10, r->ebx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c2a2b;
at_4c2b8a:
    r->eax = r->ebp - 0x50;
    r->ecx = 0;
    call_keep(r, 0x4bbf30);
    if (r->eax == 0)
    {
        goto at_4c2bce;
    }
    r->ebx = rd32(r, r->ebp - 0x44);
    r->edx = rd32(r, r->ebp - 0x48);
    if ((int32_t)r->ebx >= (int32_t)0x8 && !r->port->env.failed)
    {
        goto at_4c2a98;
    }
    wr32(r, r->ebp - 0x20, 0x1);
at_4c2bae:
    r->ecx = rd32(r, r->ebp - 0x20);
    push(r, r->ecx);
    r->eax = r->ebp - 0x50;
    r->ecx = r->edi;
    call(r, 0x4bc050, 1);
    wr32(r, r->ebp - 0x18, r->eax);
    if ((int32_t)r->eax < 0)
    {
        goto at_4c2bce;
    }
    r->edx = rd32(r, r->ebp - 0x48);
    r->ebx = rd32(r, r->ebp - 0x44);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c2acb;
at_4c2bce:
    r->ebx = 0;
    r->eax = r->ebx;
    r->edi = rd32(r, r->ebp - 0x10);
    r->esi = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4c2bdb:
    wr32(r, r->ebp - 0x20, 0x9);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c2bae;
at_4c2be4:
    r->eax = rd32(r, r->ebp - 0x1c);
    if (r->eax != 0xf)
    {
        goto at_4c2bf3;
    }
    r->esi = r->esi + r->eax;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c2b59;
at_4c2bf3:
    set_low8(&r->ecx, rd8(r, r->ebp - 0x1c));
    r->eax = 0x1;
    r->eax = r->eax << (r->ecx & 0xff);
    r->ecx = rd32(r, r->ebp - 0x1c);
    wr32(r, r->ebp - 0x38, r->eax);
    if (r->ecx == 0)
    {
        goto at_4c2c3e;
    }
    if ((int32_t)r->ebx >= (int32_t)r->ecx)
    {
        goto at_4c2c1d;
    }
    r->eax = r->ebp - 0x50;
    call_keep(r, 0x4bbf30);
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_4c2bce;
    }
    r->edx = rd32(r, r->ebp - 0x48);
    r->ebx = rd32(r, r->ebp - 0x44);
at_4c2c1d:
    r->ebx = r->ebx - rd32(r, r->ebp - 0x1c);
    r->esi = r->edx;
    set_low8(&r->ecx, (r->ebx & 0xff));
    r->eax = 0x1;
    r->esi = (uint32_t)((int32_t)r->esi >> (r->ecx & 0xff));
    set_low8(&r->ecx, rd8(r, r->ebp - 0x1c));
    r->eax = r->eax << (r->ecx & 0xff);
    r->eax = r->eax - 1;
    r->ecx = rd32(r, r->ebp - 0x38);
    r->esi = r->esi & r->eax;
    r->ecx = r->ecx + r->esi;
    wr32(r, r->ebp - 0x1c, r->esi);
    wr32(r, r->ebp - 0x38, r->ecx);
at_4c2c3e:
    wr32(r, r->ebp - 0x38, rd32(r, r->ebp - 0x38) - 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c2b65;
}

uint32_t vertrix_port_jpeg_decode_ac_first_4c29c0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x54
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
