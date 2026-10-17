#include "port_rtlformatspecs.h"

/* Parses one format specification (flags, width, precision through 0x4d6710) and formats its
 * argument into the result string. */

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

static void call_mem(Regs *r, uint32_t target, unsigned count)
{
    call_mem_with(r, target, count, 0);
}

static void call_mem_keep(Regs *r, uint32_t target, unsigned count)
{
    call_mem_with(r, target, count, 1);
}

/* Original 0x4cdbe0: Parses one format specification (flags, width, precision through 0x4d6710) and
 * formats its argument into the result string. Evidence: calls 0x4e1054, 0x4e105a, 0x4d6710,
 * 0x4e1060, 0x4d8580, 0x4ca670, 0x4cd0a4, 0x4ca6c0; reads 0x4f1d24. Register-for-register from the
 * listing (0x4cdbe0..0x4cdfa9); labels are the original addresses. */
static void run(Regs *r)
{
    push_mem(r, r->ecx);
    push_mem(r, r->esi);
    push_mem(r, r->edi);
    push_mem(r, r->ebp);
    r->esp = r->esp - 0x10;
    wr32(r, r->esp + 0x4, r->eax);
    wr32(r, r->esp + 0xc, r->edx);
    r->esi = r->ebx;
    r->eax = rd32(r, r->ebx);
    r->edi = 0;
    wr32(r, r->esp, r->eax);
    r->ebx = r->edx;
    if ((uint8_t)rd8(r, r->edx) != (uint8_t)0x0)
    {
        goto at_4cdc16;
    }
    goto at_4cdf71;
at_4cdc04:
    r->eax = r->ebx;
    call_mem_keep(r, 0x4e1054, 8);
    r->ebx = r->eax;
    if ((uint8_t)rd8(r, r->eax) == (uint8_t)0x0)
    {
        goto at_4cdf71;
    }
at_4cdc16:
    if ((uint8_t)rd8(r, r->ebx) != (uint8_t)0x25)
    {
        goto at_4cdc29;
    }
    r->eax = r->ebx;
    call_mem_keep(r, 0x4e1054, 8);
    r->ebx = r->eax;
    if ((uint8_t)rd8(r, r->eax) != (uint8_t)0x25)
    {
        goto at_4cdc34;
    }
at_4cdc29:
    r->eax = r->ebx;
    call_mem_keep(r, 0x4e105a, 8);
    r->edi = r->edi + r->eax;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4cdc04;
at_4cdc34:
    r->edx = 0;
    r->ebp = 0;
    if ((uint8_t)rd8(r, r->eax) != (uint8_t)0x0)
    {
        goto at_4cdc4d;
    }
    goto at_4cdc7a;
at_4cdc3f:
    r->eax = r->ebx;
    call_mem_keep(r, 0x4e1054, 8);
    r->ebx = r->eax;
    if ((uint8_t)rd8(r, r->eax) == (uint8_t)0x0)
    {
        goto at_4cdc7a;
    }
at_4cdc4d:
    if ((uint8_t)rd8(r, r->ebx) != (uint8_t)0x23)
    {
        goto at_4cdc57;
    }
    r->edi = r->edi + 0x2;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4cdc3f;
at_4cdc57:
    if ((uint8_t)rd8(r, r->ebx) != (uint8_t)0x2a)
    {
        goto at_4cdc66;
    }
    wr32(r, r->esi, rd32(r, r->esi) + 0x4);
    r->eax = rd32(r, r->esi);
    r->ebp = rd32(r, r->eax - 0x4);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4cdc3f;
at_4cdc66:
    if ((uint8_t)rd8(r, r->ebx) == (uint8_t)0x2d && !r->port->env.failed)
    {
        goto at_4cdc3f;
    }
    if ((uint8_t)rd8(r, r->ebx) == (uint8_t)0x2b && !r->port->env.failed)
    {
        goto at_4cdc3f;
    }
    if ((uint8_t)rd8(r, r->ebx) == (uint8_t)0x30 && !r->port->env.failed)
    {
        goto at_4cdc3f;
    }
    if ((uint8_t)rd8(r, r->ebx) == (uint8_t)0x20 && !r->port->env.failed)
    {
        goto at_4cdc3f;
    }
at_4cdc7a:
    if (r->ebp != 0)
    {
        goto at_4cdca8;
    }
    r->eax = r->ebx;
    call_mem_keep(r, 0x4d6710, 8);
    r->ebp = r->eax;
    if ((uint8_t)rd8(r, r->ebx) != (uint8_t)0x0)
    {
        goto at_4cdc9c;
    }
    goto at_4cdca8;
at_4cdc8e:
    r->eax = r->ebx;
    call_mem_keep(r, 0x4e1054, 8);
    r->ebx = r->eax;
    if ((uint8_t)rd8(r, r->eax) == (uint8_t)0x0)
    {
        goto at_4cdca8;
    }
at_4cdc9c:
    r->eax = (uint32_t)(int32_t)(int8_t)rd8(r, r->ebx);
    call_mem_keep(r, 0x4e1060, 8);
    if (r->eax != 0 && !r->port->env.failed)
    {
        goto at_4cdc8e;
    }
at_4cdca8:
    wr32(r, r->esp + 0x8, 0x0);
    if ((uint8_t)rd8(r, r->ebx) != (uint8_t)0x2e)
    {
        goto at_4cdd0a;
    }
    r->eax = r->ebx;
    call_mem_keep(r, 0x4e1054, 8);
    r->ecx = r->eax;
    r->ebx = r->eax;
    if ((uint8_t)rd8(r, r->eax) != (uint8_t)0x2a)
    {
        goto at_4cdce0;
    }
    wr32(r, r->esi, rd32(r, r->esi) + 0x4);
    r->eax = rd32(r, r->esi);
    r->eax = rd32(r, r->eax - 0x4);
    wr32(r, r->esp + 0x8, r->eax);
    r->eax = r->ecx;
    call_mem_keep(r, 0x4e1054, 8);
    r->ebx = r->eax;
    goto at_4cdd0a;
at_4cdce0:
    call_mem_keep(r, 0x4d6710, 8);
    wr32(r, r->esp + 0x8, r->eax);
    if ((uint8_t)rd8(r, r->ecx) != (uint8_t)0x0)
    {
        goto at_4cdcfe;
    }
    goto at_4cdd0a;
at_4cdcf0:
    r->eax = r->ebx;
    call_mem_keep(r, 0x4e1054, 8);
    r->ebx = r->eax;
    if ((uint8_t)rd8(r, r->eax) == (uint8_t)0x0)
    {
        goto at_4cdd0a;
    }
at_4cdcfe:
    r->eax = (uint32_t)(int32_t)(int8_t)rd8(r, r->ebx);
    call_mem_keep(r, 0x4e1060, 8);
    if (r->eax != 0 && !r->port->env.failed)
    {
        goto at_4cdcf0;
    }
at_4cdd0a:
    set_low8(&r->eax, rd8(r, r->ebx));
    r->ecx = 0;
    flags(r, F_SUB, (r->eax & 0xff), 0x4e, 8);
    if (cond(r, CC_B))
    {
        goto at_4cdd5b;
    }
    if (cond(r, CC_BE))
    {
        goto at_4cdd4d;
    }
    flags(r, F_SUB, (r->eax & 0xff), 0x68, 8);
    if (cond(r, CC_B))
    {
        goto at_4cdd69;
    }
    if (cond(r, CC_BE))
    {
        goto at_4cdd27;
    }
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x6c)
    {
        goto at_4cdd3a;
    }
    goto at_4cdd69;
at_4cdd27:
    r->eax = r->ebx;
    r->ecx = 0x10000;
    call_mem_keep(r, 0x4e1054, 8);
    r->ebx = r->eax;
    goto at_4cdd69;
at_4cdd3a:
    r->eax = r->ebx;
    r->ecx = 0x20000;
    call_mem_keep(r, 0x4e1054, 8);
    r->ebx = r->eax;
    goto at_4cdd69;
at_4cdd4d:
    r->eax = r->ebx;
    call_mem_keep(r, 0x4e1054, 8);
    r->ebx = r->eax;
    goto at_4cdd69;
at_4cdd5b:
    flags(r, F_SUB, (r->eax & 0xff), 0x46, 8);
    if (cond(r, CC_B))
    {
        goto at_4cdd69;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4cdd4d;
    }
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x4c && !r->port->env.failed)
    {
        goto at_4cdd4d;
    }
at_4cdd69:
    r->eax = (uint32_t)(int32_t)(int8_t)rd8(r, r->ebx);
    r->eax = r->eax | r->ecx;
    flags(r, F_SUB, r->eax, 0x10053, 32);
    if (cond(r, CC_B))
    {
        goto at_4cde4a;
    }
    if (cond(r, CC_BE))
    {
        goto at_4cddf0;
    }
    flags(r, F_SUB, r->eax, 0x20043, 32);
    if (cond(r, CC_B))
    {
        goto at_4cde34;
    }
    if (cond(r, CC_BE))
    {
        goto at_4cdda5;
    }
    flags(r, F_SUB, r->eax, 0x20063, 32);
    if (cond(r, CC_B))
    {
        goto at_4cde2b;
    }
    if (cond(r, CC_BE))
    {
        goto at_4cdda5;
    }
    if (r->eax == 0x20073)
    {
        goto at_4cde10;
    }
    goto at_4cde81;
at_4cdda5:
    r->edx = 0x2;
    wr32(r, r->esi, rd32(r, r->esi) + 0x4);
    goto at_4cde89;
at_4cddb2:
    wr32(r, r->esi, rd32(r, r->esi) + 0x4);
    r->eax = rd32(r, r->esi);
    push_mem(r, rd32(r, r->eax - 0x4));
    call_mem(r, rd32(r, 0x4f1d24), 1);
    if ((int32_t)r->eax >= (int32_t)0x1)
    {
        goto at_4cddcb;
    }
    r->eax = 0x1;
at_4cddcb:
    r->edx = r->eax;
    goto at_4cde81;
at_4cddd2:
    wr32(r, r->esi, rd32(r, r->esi) + 0x4);
    r->eax = rd32(r, r->esi);
    r->eax = rd32(r, r->eax - 0x4);
    call_mem_keep(r, 0x4d8580, 8);
    if ((int32_t)r->eax >= (int32_t)0x1)
    {
        goto at_4cdde9;
    }
    r->eax = 0x1;
at_4cdde9:
    r->edx = r->eax;
    goto at_4cde81;
at_4cddf0:
    wr32(r, r->esi, rd32(r, r->esi) + 0x4);
    r->eax = rd32(r, r->esi);
    push_mem(r, rd32(r, r->eax - 0x4));
    call_mem(r, rd32(r, 0x4f1d24), 1);
    if ((int32_t)r->eax >= (int32_t)0x1)
    {
        goto at_4cde09;
    }
    r->eax = 0x1;
at_4cde09:
    r->edx = r->eax;
    goto at_4cde81;
at_4cde10:
    wr32(r, r->esi, rd32(r, r->esi) + 0x4);
    r->eax = rd32(r, r->esi);
    r->eax = rd32(r, r->eax - 0x4);
    call_mem_keep(r, 0x4d8580, 8);
    if ((int32_t)r->eax >= (int32_t)0x1)
    {
        goto at_4cde27;
    }
    r->eax = 0x1;
at_4cde27:
    r->edx = r->eax;
    goto at_4cde81;
at_4cde2b:
    if (r->eax == 0x20053 && !r->port->env.failed)
    {
        goto at_4cde10;
    }
    goto at_4cde81;
at_4cde34:
    flags(r, F_SUB, r->eax, 0x10063, 32);
    if (cond(r, CC_B))
    {
        goto at_4cde81;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4cdda5;
    }
    if (r->eax == 0x10073 && !r->port->env.failed)
    {
        goto at_4cddf0;
    }
    goto at_4cde81;
at_4cde4a:
    flags(r, F_SUB, r->eax, 0x63, 32);
    if (cond(r, CC_B))
    {
        goto at_4cde6d;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4cdda5;
    }
    flags(r, F_SUB, r->eax, 0x73, 32);
    if (cond(r, CC_B))
    {
        goto at_4cde81;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4cddb2;
    }
    if (r->eax == 0x10043 && !r->port->env.failed)
    {
        goto at_4cdda5;
    }
    goto at_4cde81;
at_4cde6d:
    flags(r, F_SUB, r->eax, 0x43, 32);
    if (cond(r, CC_B))
    {
        goto at_4cde81;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4cdda5;
    }
    if (r->eax == 0x53 && !r->port->env.failed)
    {
        goto at_4cddd2;
    }
at_4cde81:
    if (r->edx == 0)
    {
        goto at_4cdf03;
    }
at_4cde89:
    if ((int32_t)r->edx <= (int32_t)r->ebp)
    {
        goto at_4cde8f;
    }
    r->ebp = r->edx;
at_4cde8f:
    r->edx = r->ebp;
    if (rd32(r, r->esp + 0x8) == 0x0)
    {
        goto at_4cdf6a;
    }
    if ((int32_t)r->ebp < (int32_t)rd32(r, r->esp + 0x8))
    {
        goto at_4cdf6a;
    }
    r->edx = rd32(r, r->esp + 0x8);
    r->edi = r->edi + r->edx;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4cdc04;
at_4cdeb1:
    r->ebp = r->ebp + rd32(r, r->esp + 0x8);
    wr32(r, r->esi, rd32(r, r->esi) + 0x4);
    if ((int32_t)r->ebp >= (int32_t)0x20)
    {
        goto at_4cdec9;
    }
    r->edx = 0x20;
    r->edi = r->edi + r->edx;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4cdc04;
at_4cdec9:
    r->edx = r->ebp;
    r->edi = r->edi + r->edx;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4cdc04;
at_4cded2:
    r->edx = r->ebp;
    r->edi = r->edi + r->edx;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4cdc04;
at_4cdedb:
    r->edx = rd32(r, r->esp + 0x8);
    r->edx = r->edx + r->ebp;
    wr32(r, r->esi, rd32(r, r->esi) + 0x4);
    if ((int32_t)r->edx >= (int32_t)0x20)
    {
        goto at_4cdf6a;
    }
    r->edx = 0x20;
    r->edi = r->edi + r->edx;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4cdc04;
at_4cdef9:
    wr32(r, r->esi, rd32(r, r->esi) + 0x4);
    r->edi = r->edi + r->edx;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4cdc04;
at_4cdf03:
    set_low8(&r->eax, rd8(r, r->ebx));
    flags(r, F_SUB, (r->eax & 0xff), 0x67, 8);
    if (cond(r, CC_B))
    {
        goto at_4cdf37;
    }
    if (cond(r, CC_BE))
    {
        goto at_4cdf41;
    }
    flags(r, F_SUB, (r->eax & 0xff), 0x6f, 8);
    if (cond(r, CC_B))
    {
        goto at_4cdf26;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4cdeb1;
    }
    flags(r, F_SUB, (r->eax & 0xff), 0x75, 8);
    if (cond(r, CC_B))
    {
        goto at_4cdf1b;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4cdeb1;
    }
    flags(r, F_SUB, (r->eax & 0xff), 0x78, 8);
    goto at_4cdf64;
at_4cdf1b:
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x70 && !r->port->env.failed)
    {
        goto at_4cdedb;
    }
    r->edi = r->edi + r->edx;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4cdc04;
at_4cdf26:
    flags(r, F_SUB, (r->eax & 0xff), 0x69, 8);
    if (cond(r, CC_B))
    {
        goto at_4cdf6a;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4cdeb1;
    }
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x6e && !r->port->env.failed)
    {
        goto at_4cdef9;
    }
    r->edi = r->edi + r->edx;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4cdc04;
at_4cdf37:
    flags(r, F_SUB, (r->eax & 0xff), 0x64, 8);
    if (cond(r, CC_B))
    {
        goto at_4cdf5c;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4cdeb1;
    }
at_4cdf41:
    r->ebp = r->ebp + rd32(r, r->esp + 0x8);
    wr32(r, r->esi, rd32(r, r->esi) + 0x8);
    if ((int32_t)r->ebp >= (int32_t)0x80 && !r->port->env.failed)
    {
        goto at_4cded2;
    }
    r->edx = 0x80;
    r->edi = r->edi + r->edx;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4cdc04;
at_4cdf5c:
    flags(r, F_SUB, (r->eax & 0xff), 0x47, 8);
    if (cond(r, CC_B))
    {
        goto at_4cdf6a;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4cdf41;
    }
    flags(r, F_SUB, (r->eax & 0xff), 0x58, 8);
at_4cdf64:
    if (cond(r, CC_E) && !r->port->env.failed)
    {
        goto at_4cdeb1;
    }
at_4cdf6a:
    r->edi = r->edi + r->edx;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4cdc04;
at_4cdf71:
    r->eax = rd32(r, r->esp + 0x4);
    r->edx = r->edi;
    call_mem_keep(r, 0x4ca670, 8);
    r->eax = rd32(r, r->esp + 0x4);
    r->ebx = r->esp;
    r->edx = rd32(r, r->esp + 0xc);
    r->eax = rd32(r, r->eax);
    call_mem_keep(r, 0x4cd0a4, 8);
    r->edx = 0xffffffffu;
    r->eax = rd32(r, r->esp + 0x4);
    call_mem_keep(r, 0x4ca6c0, 8);
    wr32(r, r->esp, 0x0);
    r->esp = r->esp + 0x10;
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    return;
}

uint32_t vertrix_port_rtl_format_spec_4cdbe0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x40
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
