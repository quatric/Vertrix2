#include "port_rtlddrawerrors.h"

/* Copies a message prefix to 0x5b9a48 and appends the name of a DirectDraw result code (0x8876xxxx
 * and the generic COM codes). */

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

static void wr8(Regs *r, uint32_t address, uint32_t value)
{
    port_set8(r->port, address, 0, value);
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

/* repne scasb: edi walked to just past the first byte equal to al (or ecx bytes). */
static void repne_scasb(Regs *r)
{
    while (r->ecx != 0 && !r->port->env.failed)
    {
        uint32_t byte = rd8(r, r->edi);
        r->ecx--;
        r->edi++;
        flags(r, F_SUB, r->eax & 0xff, byte, 8);
        if ((r->eax & 0xff) == byte)
        {
            break;
        }
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

/* Original 0x485700: Copies a message prefix to 0x5b9a48 and appends the name of a DirectDraw
 * result code (0x8876xxxx and the generic COM codes). Evidence: no calls. Register-for-register
 * from the listing (0x485700..0x486cfe); labels are the original addresses. */
static void run(Regs *r)
{
    push_mem(r, r->esi);
    push_mem(r, r->edi);
    r->esi = r->ebx;
    r->edi = 0x5b9a48;
    push_mem(r, r->edi);
at_48570a:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_485722;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_48570a;
    }
at_485722:
    r->edi = pop_mem(r);
    r->esi = r->ecx;
    flags(r, F_SUB, r->ecx, 0x8876019au, 32);
    if (cond(r, CC_AE))
    {
        goto at_48666c;
    }
    flags(r, F_SUB, r->ecx, 0x887600d7u, 32);
    if (cond(r, CC_AE))
    {
        goto at_486a3e;
    }
    flags(r, F_SUB, r->ecx, 0x8876005fu, 32);
    if (cond(r, CC_AE))
    {
        goto at_486bbf;
    }
    flags(r, F_SUB, r->ecx, 0x88760005u, 32);
    if (cond(r, CC_AE))
    {
        goto at_486c82;
    }
    flags(r, F_SUB, r->ecx, 0x800401f0u, 32);
    if (cond(r, CC_AE))
    {
        goto at_486cd8;
    }
    flags(r, F_SUB, r->ecx, 0x80004001u, 32);
    if (cond(r, CC_B))
    {
        goto at_48577b;
    }
    if (cond(r, CC_BE))
    {
        goto at_48651c;
    }
    if (r->ecx == 0x80004005u)
    {
        goto at_4859f4;
    }
at_48577b:
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_48577e:
    r->esi = 0x50fe91;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_48578c:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_4857a4;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_48578c;
    }
at_4857a4:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_4857a8:
    r->esi = 0x50feaa;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_4857b6:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_4857ce;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_4857b6;
    }
at_4857ce:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_4857d2:
    r->esi = 0x50fec0;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_4857e0:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_4857f8;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_4857e0;
    }
at_4857f8:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_4857fc:
    r->esi = 0x50feda;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_48580a:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_485822;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_48580a;
    }
at_485822:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_485826:
    r->esi = 0x50fef4;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_485834:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_48584c;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_485834;
    }
at_48584c:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_485850:
    r->esi = 0x50ff1b;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_48585e:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_485876;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_48585e;
    }
at_485876:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_48587a:
    r->esi = 0x50ff31;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_485888:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_4858a0;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_485888;
    }
at_4858a0:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_4858a4:
    r->esi = 0x50ff44;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_4858b2:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_4858ca;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_4858b2;
    }
at_4858ca:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_4858ce:
    r->esi = 0x50ff59;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_4858dc:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_4858f4;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_4858dc;
    }
at_4858f4:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_4858f8:
    r->esi = 0x50ff72;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_485906:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_48591e;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_485906;
    }
at_48591e:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_485922:
    r->esi = 0x50ff87;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_485930:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_485948;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_485930;
    }
at_485948:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_48594c:
    r->esi = 0x50ff9f;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_48595a:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_485972;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_48595a;
    }
at_485972:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_485976:
    r->esi = 0x50ffb6;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_485984:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_48599c;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_485984;
    }
at_48599c:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_4859a0:
    r->esi = 0x50ffd5;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_4859ae:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_4859c6;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_4859ae;
    }
at_4859c6:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_4859ca:
    r->esi = 0x50ffe5;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_4859d8:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_4859f0;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_4859d8;
    }
at_4859f0:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_4859f4:
    r->esi = 0x510003;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_485a02:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_485a1a;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_485a02;
    }
at_485a1a:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_485a1e:
    r->esi = 0x510011;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_485a2c:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_485a44;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_485a2c;
    }
at_485a44:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_485a48:
    r->esi = 0x510023;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_485a56:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_485a6e;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_485a56;
    }
at_485a6e:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_485a72:
    r->esi = 0x51004d;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_485a80:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_485a98;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_485a80;
    }
at_485a98:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_485a9c:
    r->esi = 0x510065;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_485aaa:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_485ac2;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_485aaa;
    }
at_485ac2:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_485ac6:
    r->esi = 0x51007f;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_485ad4:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_485aec;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_485ad4;
    }
at_485aec:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_485af0:
    r->esi = 0x510091;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_485afe:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_485b16;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_485afe;
    }
at_485b16:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_485b1a:
    r->esi = 0x5100a7;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_485b28:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_485b40;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_485b28;
    }
at_485b40:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_485b44:
    r->esi = 0x5100c3;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_485b52:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_485b6a;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_485b52;
    }
at_485b6a:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_485b6e:
    r->esi = 0x5100d5;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_485b7c:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_485b94;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_485b7c;
    }
at_485b94:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_485b98:
    r->esi = 0x5100e9;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_485ba6:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_485bbe;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_485ba6;
    }
at_485bbe:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_485bc2:
    r->esi = 0x5100fd;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_485bd0:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_485be8;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_485bd0;
    }
at_485be8:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_485bec:
    r->esi = 0x51012c;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_485bfa:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_485c12;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_485bfa;
    }
at_485c12:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_485c16:
    r->esi = 0x51013e;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_485c24:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_485c3c;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_485c24;
    }
at_485c3c:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_485c40:
    r->esi = 0x510157;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_485c4e:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_485c66;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_485c4e;
    }
at_485c66:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_485c6a:
    r->esi = 0x51016c;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_485c78:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_485c90;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_485c78;
    }
at_485c90:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_485c94:
    r->esi = 0x510177;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_485ca2:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_485cba;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_485ca2;
    }
at_485cba:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_485cbe:
    r->esi = 0x510187;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_485ccc:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_485ce4;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_485ccc;
    }
at_485ce4:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_485ce8:
    r->esi = 0x510195;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_485cf6:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_485d0e;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_485cf6;
    }
at_485d0e:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_485d12:
    r->esi = 0x5101a6;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_485d20:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_485d38;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_485d20;
    }
at_485d38:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_485d3c:
    r->esi = 0x5101be;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_485d4a:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_485d62;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_485d4a;
    }
at_485d62:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_485d66:
    r->esi = 0x5101d2;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_485d74:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_485d8c;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_485d74;
    }
at_485d8c:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_485d90:
    r->esi = 0x5101e3;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_485d9e:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_485db6;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_485d9e;
    }
at_485db6:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_485dba:
    r->esi = 0x5101f6;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_485dc8:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_485de0;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_485dc8;
    }
at_485de0:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_485de4:
    r->esi = 0x510243;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_485df2:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_485e0a;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_485df2;
    }
at_485e0a:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_485e0e:
    r->esi = 0x51025d;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_485e1c:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_485e34;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_485e1c;
    }
at_485e34:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_485e38:
    r->esi = 0x51026f;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_485e46:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_485e5e;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_485e46;
    }
at_485e5e:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_485e62:
    r->esi = 0x510285;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_485e70:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_485e88;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_485e70;
    }
at_485e88:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_485e8c:
    r->esi = 0x510294;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_485e9a:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_485eb2;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_485e9a;
    }
at_485eb2:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_485eb6:
    r->esi = 0x5102a0;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_485ec4:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_485edc;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_485ec4;
    }
at_485edc:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_485ee0:
    r->esi = 0x5102ad;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_485eee:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_485f06;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_485eee;
    }
at_485f06:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_485f0a:
    r->esi = 0x5102be;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_485f18:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_485f30;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_485f18;
    }
at_485f30:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_485f34:
    r->esi = 0x5102cf;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_485f42:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_485f5a;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_485f42;
    }
at_485f5a:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_485f5e:
    r->esi = 0x5102e3;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_485f6c:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_485f84;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_485f6c;
    }
at_485f84:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_485f88:
    r->esi = 0x5102f5;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_485f96:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_485fae;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_485f96;
    }
at_485fae:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_485fb2:
    r->esi = 0x51031f;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_485fc0:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_485fd8;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_485fc0;
    }
at_485fd8:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_485fdc:
    r->esi = 0x510332;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_485fea:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_486002;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_485fea;
    }
at_486002:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_486006:
    r->esi = 0x510345;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_486014:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_48602c;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_486014;
    }
at_48602c:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_486030:
    r->esi = 0x510357;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_48603e:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_486056;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_48603e;
    }
at_486056:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_48605a:
    r->esi = 0x51036a;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_486068:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_486080;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_486068;
    }
at_486080:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_486084:
    r->esi = 0x510382;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_486092:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_4860aa;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_486092;
    }
at_4860aa:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_4860ae:
    r->esi = 0x510395;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_4860bc:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_4860d4;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_4860bc;
    }
at_4860d4:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_4860d8:
    r->esi = 0x5103ae;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_4860e6:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_4860fe;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_4860e6;
    }
at_4860fe:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_486102:
    r->esi = 0x5103c0;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_486110:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_486128;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_486110;
    }
at_486128:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_48612c:
    r->esi = 0x5103d3;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_48613a:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_486152;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_48613a;
    }
at_486152:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_486156:
    r->esi = 0x5103e2;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_486164:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_48617c;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_486164;
    }
at_48617c:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_486180:
    r->esi = 0x5103f7;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_48618e:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_4861a6;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_48618e;
    }
at_4861a6:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_4861aa:
    r->esi = 0x510407;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_4861b8:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_4861d0;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_4861b8;
    }
at_4861d0:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_4861d4:
    r->esi = 0x51042f;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_4861e2:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_4861fa;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_4861e2;
    }
at_4861fa:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_4861fe:
    r->esi = 0x51043f;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_48620c:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_486224;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_48620c;
    }
at_486224:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_486228:
    r->esi = 0x510451;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_486236:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_48624e;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_486236;
    }
at_48624e:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_486252:
    r->esi = 0x510464;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_486260:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_486278;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_486260;
    }
at_486278:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_48627c:
    r->esi = 0x510474;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_48628a:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_4862a2;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_48628a;
    }
at_4862a2:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_4862a6:
    r->esi = 0x510486;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_4862b4:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_4862cc;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_4862b4;
    }
at_4862cc:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_4862d0:
    r->esi = 0x51049d;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_4862de:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_4862f6;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_4862de;
    }
at_4862f6:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_4862fa:
    r->esi = 0x5104b3;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_486308:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_486320;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_486308;
    }
at_486320:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_486324:
    r->esi = 0x5104d6;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_486332:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_48634a;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_486332;
    }
at_48634a:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_48634e:
    r->esi = 0x5104ee;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_48635c:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_486374;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_48635c;
    }
at_486374:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_486378:
    r->esi = 0x510500;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_486386:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_48639e;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_486386;
    }
at_48639e:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_4863a2:
    r->esi = 0x510537;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_4863b0:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_4863c8;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_4863b0;
    }
at_4863c8:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_4863cc:
    r->esi = 0x510554;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_4863da:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_4863f2;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_4863da;
    }
at_4863f2:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_4863f6:
    r->esi = 0x510572;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_486404:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_48641c;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_486404;
    }
at_48641c:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_486420:
    r->esi = 0x510584;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_48642e:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_486446;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_48642e;
    }
at_486446:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_48644a:
    r->esi = 0x51059c;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_486458:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_486470;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_486458;
    }
at_486470:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_486474:
    r->esi = 0x5105ae;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_486482:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_48649a;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_486482;
    }
at_48649a:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_48649e:
    r->esi = 0x5105c7;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_4864ac:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_4864c4;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_4864ac;
    }
at_4864c4:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_4864c8:
    r->esi = 0x5105da;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_4864d6:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_4864ee;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_4864d6;
    }
at_4864ee:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_4864f2:
    r->esi = 0x5105eb;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_486500:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_486518;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_486500;
    }
at_486518:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_48651c:
    r->esi = 0x5105fd;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_48652a:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_486542;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_48652a;
    }
at_486542:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_486546:
    r->esi = 0x51060f;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_486554:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_48656c;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_486554;
    }
at_48656c:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_486570:
    r->esi = 0x510627;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_48657e:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_486596;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_48657e;
    }
at_486596:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_48659a:
    r->esi = 0x51063d;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_4865a8:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_4865c0;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_4865a8;
    }
at_4865c0:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_4865c4:
    r->esi = 0x510653;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_4865d2:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_4865ea;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_4865d2;
    }
at_4865ea:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_4865ee:
    r->esi = 0x510671;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_4865fc:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_486614;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_4865fc;
    }
at_486614:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_486618:
    r->esi = 0x510687;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_486626:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_48663e;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_486626;
    }
at_48663e:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_486642:
    r->esi = 0x510697;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_486650:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_486668;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_486650;
    }
at_486668:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_48666c:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4863a2;
    }
    flags(r, F_SUB, r->ecx, 0x8876023bu, 32);
    if (cond(r, CC_AE))
    {
        goto at_4866bf;
    }
    flags(r, F_SUB, r->ecx, 0x88760219u, 32);
    if (cond(r, CC_AE))
    {
        goto at_4868c4;
    }
    flags(r, F_SUB, r->ecx, 0x887601ccu, 32);
    if (cond(r, CC_AE))
    {
        goto at_4869c1;
    }
    flags(r, F_SUB, r->ecx, 0x887601b3u, 32);
    if (cond(r, CC_AE))
    {
        goto at_486a17;
    }
    flags(r, F_SUB, r->ecx, 0x887601a4u, 32);
    if (cond(r, CC_B) && !r->port->env.failed)
    {
        goto at_48577b;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4863cc;
    }
    if (r->ecx == 0x887601aeu && !r->port->env.failed)
    {
        goto at_4863f6;
    }
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_4866bf:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_485a48;
    }
    flags(r, F_SUB, r->ecx, 0x88760248u, 32);
    if (cond(r, CC_AE))
    {
        goto at_48671b;
    }
    flags(r, F_SUB, r->ecx, 0x88760241u, 32);
    if (cond(r, CC_AE))
    {
        goto at_486802;
    }
    flags(r, F_SUB, r->ecx, 0x8876023eu, 32);
    if (cond(r, CC_AE))
    {
        goto at_486888;
    }
    if (r->ecx <= 0x8876023cu && !r->port->env.failed)
    {
        goto at_485f88;
    }
    r->esi = 0x51030d;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_4866ff:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_486717;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_4866ff;
    }
at_486717:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_48671b:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_486180;
    }
    flags(r, F_SUB, r->ecx, 0x8876024eu, 32);
    if (cond(r, CC_AE))
    {
        goto at_48676b;
    }
    flags(r, F_SUB, r->ecx, 0x8876024bu, 32);
    if (cond(r, CC_AE))
    {
        goto at_4867c6;
    }
    if (r->ecx <= 0x88760249u && !r->port->env.failed)
    {
        goto at_485826;
    }
    r->esi = 0x510212;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_48674f:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_486767;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_48674f;
    }
at_486767:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_48676b:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_48659a;
    }
    flags(r, F_SUB, r->ecx, 0x8876026cu, 32);
    if (cond(r, CC_AE))
    {
        goto at_486794;
    }
    if (r->ecx <= 0x8876024fu && !r->port->env.failed)
    {
        goto at_485ee0;
    }
    if (r->ecx == 0x88760250u && !r->port->env.failed)
    {
        goto at_485c16;
    }
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_486794:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_48594c;
    }
    flags(r, F_SUB, r->ecx, 0x88760294u, 32);
    if (cond(r, CC_AE))
    {
        goto at_4867b1;
    }
    if (r->ecx == 0x88760280u && !r->port->env.failed)
    {
        goto at_48587a;
    }
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_4867b1:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4858a4;
    }
    if (r->ecx == 0x887602a8u && !r->port->env.failed)
    {
        goto at_4861aa;
    }
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_4867c6:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_486618;
    }
    if (r->ecx <= 0x8876024cu && !r->port->env.failed)
    {
        goto at_485a72;
    }
    r->esi = 0x51041b;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_4867e6:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_4867fe;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_4867e6;
    }
at_4867fe:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_486802:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_486324;
    }
    flags(r, F_SUB, r->ecx, 0x88760244u, 32);
    if (cond(r, CC_AE))
    {
        goto at_486846;
    }
    if (r->ecx <= 0x88760242u && !r->port->env.failed)
    {
        goto at_485f34;
    }
    r->esi = 0x510116;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_48682a:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_486842;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_48682a;
    }
at_486842:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_486846:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4860ae;
    }
    flags(r, F_SUB, r->ecx, 0x88760246u, 32);
    if (cond(r, CC_B) && !r->port->env.failed)
    {
        goto at_4859ca;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_486102;
    }
    r->esi = 0x50ff07;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_48686c:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_486884;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_48686c;
    }
at_486884:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_486888:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4857a8;
    }
    if (r->ecx <= 0x8876023fu && !r->port->env.failed)
    {
        goto at_485cbe;
    }
    r->esi = 0x51021d;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_4868a8:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_4868c0;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_4868a8;
    }
at_4868c0:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_4868c4:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4865c4;
    }
    flags(r, F_SUB, r->ecx, 0x88760234u, 32);
    if (cond(r, CC_AE))
    {
        goto at_4868ff;
    }
    flags(r, F_SUB, r->ecx, 0x88760231u, 32);
    if (cond(r, CC_AE))
    {
        goto at_486985;
    }
    flags(r, F_SUB, r->ecx, 0x8876021cu, 32);
    if (cond(r, CC_B) && !r->port->env.failed)
    {
        goto at_48577b;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4865ee;
    }
    if (r->ecx == 0x88760230u && !r->port->env.failed)
    {
        goto at_486642;
    }
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_4868ff:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_486378;
    }
    flags(r, F_SUB, r->ecx, 0x88760237u, 32);
    if (cond(r, CC_AE))
    {
        goto at_486943;
    }
    if (r->ecx <= 0x88760235u && !r->port->env.failed)
    {
        goto at_485e0e;
    }
    r->esi = 0x510522;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_486927:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_48693f;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_486927;
    }
at_48693f:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_486943:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4858ce;
    }
    flags(r, F_SUB, r->ecx, 0x88760239u, 32);
    if (cond(r, CC_B) && !r->port->env.failed)
    {
        goto at_485d12;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_485eb6;
    }
    r->esi = 0x510038;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_486969:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_486981;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_486969;
    }
at_486981:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_486985:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_485b1a;
    }
    if (r->ecx <= 0x88760232u && !r->port->env.failed)
    {
        goto at_485976;
    }
    r->esi = 0x51022e;
    push_mem(r, r->edi);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, 0x0);
    repne_scasb(r);
    r->edi = r->edi - 1;
at_4869a5:
    set_low8(&r->eax, rd8(r, r->esi));
    wr8(r, r->edi, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x0)
    {
        goto at_4869bd;
    }
    set_low8(&r->eax, rd8(r, r->esi + 0x1));
    r->esi = r->esi + 0x2;
    wr8(r, r->edi + 0x1, (r->eax & 0xff));
    r->edi = r->edi + 0x2;
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_4869a5;
    }
at_4869bd:
    r->edi = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_4869c1:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_486474;
    }
    flags(r, F_SUB, r->ecx, 0x887601eau, 32);
    if (cond(r, CC_AE))
    {
        goto at_4869f0;
    }
    flags(r, F_SUB, r->ecx, 0x887601d6u, 32);
    if (cond(r, CC_B) && !r->port->env.failed)
    {
        goto at_48577b;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_48649e;
    }
    if (r->ecx == 0x887601e0u && !r->port->env.failed)
    {
        goto at_4864c8;
    }
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_4869f0:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4864f2;
    }
    flags(r, F_SUB, r->ecx, 0x887601feu, 32);
    if (cond(r, CC_B) && !r->port->env.failed)
    {
        goto at_48577b;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_486546;
    }
    if (r->ecx == 0x88760208u && !r->port->env.failed)
    {
        goto at_486570;
    }
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_486a17:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_485850;
    }
    flags(r, F_SUB, r->ecx, 0x887601b8u, 32);
    if (cond(r, CC_B) && !r->port->env.failed)
    {
        goto at_48577b;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_486420;
    }
    if (r->ecx == 0x887601c2u && !r->port->env.failed)
    {
        goto at_48644a;
    }
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_486a3e:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_485d66;
    }
    flags(r, F_SUB, r->ecx, 0x8876013cu, 32);
    if (cond(r, CC_AE))
    {
        goto at_486a85;
    }
    flags(r, F_SUB, r->ecx, 0x887600fau, 32);
    if (cond(r, CC_AE))
    {
        goto at_486b42;
    }
    flags(r, F_SUB, r->ecx, 0x887600e1u, 32);
    if (cond(r, CC_AE))
    {
        goto at_486b98;
    }
    flags(r, F_SUB, r->ecx, 0x887600dcu, 32);
    if (cond(r, CC_B) && !r->port->env.failed)
    {
        goto at_48577b;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_485d90;
    }
    if (r->ecx == 0x887600deu && !r->port->env.failed)
    {
        goto at_485de4;
    }
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_486a85:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_486030;
    }
    flags(r, F_SUB, r->ecx, 0x8876015eu, 32);
    if (cond(r, CC_AE))
    {
        goto at_486aba;
    }
    flags(r, F_SUB, r->ecx, 0x8876014au, 32);
    if (cond(r, CC_AE))
    {
        goto at_486b1b;
    }
    if (r->ecx <= 0x8876013du && !r->port->env.failed)
    {
        goto at_48605a;
    }
    if (r->ecx == 0x88760140u && !r->port->env.failed)
    {
        goto at_486084;
    }
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_486aba:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_486228;
    }
    flags(r, F_SUB, r->ecx, 0x8876017eu, 32);
    if (cond(r, CC_AE))
    {
        goto at_486ae9;
    }
    flags(r, F_SUB, r->ecx, 0x88760168u, 32);
    if (cond(r, CC_B) && !r->port->env.failed)
    {
        goto at_48577b;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_486252;
    }
    if (r->ecx == 0x8876017cu && !r->port->env.failed)
    {
        goto at_4862a6;
    }
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_486ae9:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4862d0;
    }
    flags(r, F_SUB, r->ecx, 0x88760183u, 32);
    if (cond(r, CC_AE))
    {
        goto at_486b06;
    }
    if (r->ecx == 0x88760180u && !r->port->env.failed)
    {
        goto at_4862fa;
    }
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_486b06:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_48634e;
    }
    if (r->ecx == 0x88760190u && !r->port->env.failed)
    {
        goto at_4858f8;
    }
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_486b1b:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4860d8;
    }
    flags(r, F_SUB, r->ecx, 0x8876014fu, 32);
    if (cond(r, CC_B) && !r->port->env.failed)
    {
        goto at_48577b;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4861d4;
    }
    if (r->ecx == 0x88760154u && !r->port->env.failed)
    {
        goto at_4861fe;
    }
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_486b42:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_485f0a;
    }
    flags(r, F_SUB, r->ecx, 0x88760118u, 32);
    if (cond(r, CC_AE))
    {
        goto at_486b71;
    }
    flags(r, F_SUB, r->ecx, 0x887600ffu, 32);
    if (cond(r, CC_B) && !r->port->env.failed)
    {
        goto at_48577b;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_48612c;
    }
    if (r->ecx == 0x88760104u && !r->port->env.failed)
    {
        goto at_485f5e;
    }
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_486b71:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_485fb2;
    }
    flags(r, F_SUB, r->ecx, 0x88760122u, 32);
    if (cond(r, CC_B) && !r->port->env.failed)
    {
        goto at_48577b;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_485fdc;
    }
    if (r->ecx == 0x88760136u && !r->port->env.failed)
    {
        goto at_486006;
    }
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_486b98:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_485e38;
    }
    flags(r, F_SUB, r->ecx, 0x887600e6u, 32);
    if (cond(r, CC_B) && !r->port->env.failed)
    {
        goto at_48577b;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_485e62;
    }
    if (r->ecx == 0x887600f0u && !r->port->env.failed)
    {
        goto at_485e8c;
    }
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_486bbf:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_485a9c;
    }
    flags(r, F_SUB, r->ecx, 0x88760096u, 32);
    if (cond(r, CC_AE))
    {
        goto at_486bfa;
    }
    flags(r, F_SUB, r->ecx, 0x88760078u, 32);
    if (cond(r, CC_AE))
    {
        goto at_486c5b;
    }
    flags(r, F_SUB, r->ecx, 0x88760064u, 32);
    if (cond(r, CC_B) && !r->port->env.failed)
    {
        goto at_48577b;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_485ac6;
    }
    if (r->ecx == 0x8876006eu && !r->port->env.failed)
    {
        goto at_485af0;
    }
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_486bfa:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_485bec;
    }
    flags(r, F_SUB, r->ecx, 0x887600b4u, 32);
    if (cond(r, CC_AE))
    {
        goto at_486c29;
    }
    flags(r, F_SUB, r->ecx, 0x887600a0u, 32);
    if (cond(r, CC_B) && !r->port->env.failed)
    {
        goto at_48577b;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_485c40;
    }
    if (r->ecx == 0x887600aau && !r->port->env.failed)
    {
        goto at_485c6a;
    }
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_486c29:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_485c94;
    }
    flags(r, F_SUB, r->ecx, 0x887600d2u, 32);
    if (cond(r, CC_AE))
    {
        goto at_486c46;
    }
    if (r->ecx == 0x887600cdu && !r->port->env.failed)
    {
        goto at_485ce8;
    }
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_486c46:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_485d3c;
    }
    if (r->ecx == 0x887600d4u && !r->port->env.failed)
    {
        goto at_485dba;
    }
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_486c5b:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_485b44;
    }
    flags(r, F_SUB, r->ecx, 0x88760082u, 32);
    if (cond(r, CC_B) && !r->port->env.failed)
    {
        goto at_48577b;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_485b6e;
    }
    if (r->ecx == 0x88760091u && !r->port->env.failed)
    {
        goto at_485bc2;
    }
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_486c82:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_48577e;
    }
    flags(r, F_SUB, r->ecx, 0x88760028u, 32);
    if (cond(r, CC_AE))
    {
        goto at_486cb1;
    }
    flags(r, F_SUB, r->ecx, 0x8876000au, 32);
    if (cond(r, CC_B) && !r->port->env.failed)
    {
        goto at_48577b;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4857d2;
    }
    if (r->ecx == 0x88760014u && !r->port->env.failed)
    {
        goto at_4857fc;
    }
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_486cb1:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_485922;
    }
    flags(r, F_SUB, r->ecx, 0x88760037u, 32);
    if (cond(r, CC_B) && !r->port->env.failed)
    {
        goto at_48577b;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4859a0;
    }
    if (r->ecx == 0x8876005au && !r->port->env.failed)
    {
        goto at_485a1e;
    }
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_486cd8:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_486156;
    }
    flags(r, F_SUB, r->ecx, 0x8007000eu, 32);
    if (cond(r, CC_B) && !r->port->env.failed)
    {
        goto at_48577b;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_48627c;
    }
    if (r->ecx == 0x80070057u && !r->port->env.failed)
    {
        goto at_485b98;
    }
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
}

uint32_t vertrix_port_ddraw_error_text_485700(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
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
