#include "port_rtlxmmoduleloads.h"

/* Allocates a 0x158-byte module record with vertrix_port_clear_allocate at 0x4b828c and returns
 * error 8 if that fails. */

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

static void set_high8(uint32_t *reg, uint32_t value)
{
    *reg = (*reg & 0xffff00ffu) | ((value & 0xff) << 8);
}

static void set_low16(uint32_t *reg, uint32_t value)
{
    *reg = (*reg & 0xffff0000u) | (value & 0xffff);
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

/* repe cmpsb: esi and edi walked while their bytes match (at most ecx). */
static void repe_cmpsb(Regs *r)
{
    while (r->ecx != 0 && !r->port->env.failed)
    {
        uint32_t a = rd8(r, r->esi);
        uint32_t b = rd8(r, r->edi);
        r->ecx--;
        r->esi++;
        r->edi++;
        flags(r, F_SUB, a, b, 8);
        if (a != b)
        {
            break;
        }
    }
}

/* Original 0x4b826f: Allocates a 0x158-byte module record with vertrix_port_clear_allocate at
 * 0x4b828c and returns error 8 if that fails. It reads the FastTracker 2 XM header into globals at
 * 0x5bd880.. with vertrix_port_stream_read_exact, then skips the rest of the header (header size
 * minus 0x114). It checks the 'Extended Module: ' signature (0x511143) and version 0x104. It also
 * checks the header counts: song length and patterns at most 0x100, instruments at most 0x80 and
 * channels at most 0x20. If any check fails, it frees the record (vertrix_port_module_free_40ef90)
 * and returns error 0xb. Otherwise it copies the module name and header fields into the record,
 * reads the patterns and instruments, and finishes with vertrix_port_sample_load and
 * vertrix_port_driver_write. Evidence: calls 0x4ec160, 0x48a930, 0x48aa90, 0x40ef90, 0x4eb860,
 * 0x4e7c90, 0x40ac50, 0x4b8fbc, 0x40acd0; reads 0x5bd8bc, 0x5bd8ba, 0x5bd8c0, 0x5bd8c6, 0x5bd8c8,
 * 0x5bd8c4, 0x5bd8ca, 0x5bd8c2, 0x5bd8cc, 0x5bd8ce, 0x5bd9d0, 0x5bd9d4, 0x5bd9d5, 0x5bd9d7,
 * 0x5bd9fb, 0x5bd9e0 and more; writes 0x5bd9e0, 0x5bdac1, 0x5bdac2. Register-for-register from the
 * listing (0x4b827c..0x4b8fbb); labels are the original addresses. */
static void run(Regs *r)
{
    wr32(r, r->ebp - 0x38, r->eax);
    wr32(r, r->ebp - 0x34, r->edx);
    r->edx = 0x158;
    r->eax = 0x1;
    call(r, 0x4ec160, 0);
    wr32(r, r->ebp - 0x2c, r->eax);
    if (rd32(r, r->ebp - 0x2c) != 0x0)
    {
        goto at_4b82a6;
    }
    wr32(r, r->ebp - 0x30, 0x8);
    goto at_4b8fb0;
at_4b82a6:
    r->ecx = 0x11;
    r->ebx = 0x1;
    r->edx = 0x5bd880;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    r->ecx = 0x14;
    r->ebx = 0x1;
    r->edx = 0x5bd891;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    r->ecx = 0x1;
    r->ebx = 0x1;
    r->edx = 0x5bd8a5;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    r->ecx = 0x14;
    r->ebx = 0x1;
    r->edx = 0x5bd8a6;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    r->ecx = 0x2;
    r->ebx = 0x1;
    r->edx = 0x5bd8ba;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    r->ecx = 0x4;
    r->ebx = 0x1;
    r->edx = 0x5bd8bc;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    r->ecx = 0x2;
    r->ebx = 0x1;
    r->edx = 0x5bd8c0;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    r->ecx = 0x2;
    r->ebx = 0x1;
    r->edx = 0x5bd8c2;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    r->ecx = 0x2;
    r->ebx = 0x1;
    r->edx = 0x5bd8c4;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    r->ecx = 0x2;
    r->ebx = 0x1;
    r->edx = 0x5bd8c6;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    r->ecx = 0x2;
    r->ebx = 0x1;
    r->edx = 0x5bd8c8;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    r->ecx = 0x2;
    r->ebx = 0x1;
    r->edx = 0x5bd8ca;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    r->ecx = 0x2;
    r->ebx = 0x1;
    r->edx = 0x5bd8cc;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    r->ecx = 0x2;
    r->ebx = 0x1;
    r->edx = 0x5bd8ce;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    r->ecx = 0x100;
    r->ebx = 0x1;
    r->edx = 0x5bd8d0;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    r->edx = rd32(r, 0x5bd8bc);
    r->edx = r->edx - 0x114;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48aa90, 0);
    r->ecx = 0x11;
    r->edi = 0x511143;
    r->esi = 0x5bd880;
    r->eax = 0;
    repe_cmpsb(r);
    if (cond(r, CC_E))
    {
        goto at_4b842d;
    }
    r->eax = r->eax - r->eax - carry(r);
    flags(r, F_LOGIC, r->eax, 0, 32);
    r->eax = r->eax - 0xffffffffu - carry(r);
at_4b842d:
    if (r->eax != 0)
    {
        goto at_4b843c;
    }
    if ((uint16_t)rd16(r, 0x5bd8ba) == (uint16_t)0x104)
    {
        goto at_4b843e;
    }
at_4b843c:
    goto at_4b844d;
at_4b843e:
    r->eax = 0;
    set_low16(&r->eax, rd16(r, 0x5bd8c0));
    if ((int32_t)r->eax <= (int32_t)0x100)
    {
        goto at_4b844f;
    }
at_4b844d:
    goto at_4b845e;
at_4b844f:
    r->eax = 0;
    set_low16(&r->eax, rd16(r, 0x5bd8c6));
    if ((int32_t)r->eax <= (int32_t)0x100)
    {
        goto at_4b8460;
    }
at_4b845e:
    goto at_4b846f;
at_4b8460:
    r->eax = 0;
    set_low16(&r->eax, rd16(r, 0x5bd8c8));
    if ((int32_t)r->eax <= (int32_t)0x80)
    {
        goto at_4b8471;
    }
at_4b846f:
    goto at_4b847e;
at_4b8471:
    r->eax = 0;
    set_low16(&r->eax, rd16(r, 0x5bd8c4));
    if ((int32_t)r->eax <= (int32_t)0x20)
    {
        goto at_4b8492;
    }
at_4b847e:
    r->eax = rd32(r, r->ebp - 0x2c);
    call(r, 0x40ef90, 0);
    wr32(r, r->ebp - 0x30, 0xb);
    goto at_4b8fb0;
at_4b8492:
    r->ebx = 0x14;
    r->edx = 0x5bd891;
    r->eax = rd32(r, r->ebp - 0x2c);
    call(r, 0x4eb860, 0);
    if ((uint8_t)(rd8(r, 0x5bd8ca) & 0x1) == 0)
    {
        goto at_4b84b4;
    }
    r->eax = rd32(r, r->ebp - 0x2c);
    wr8(r, r->eax + 0x20, rd8(r, r->eax + 0x20) | 0x1);
at_4b84b4:
    set_low16(&r->edx, rd16(r, 0x5bd8c0));
    r->eax = rd32(r, r->ebp - 0x2c);
    wr16(r, r->eax + 0x22, (r->edx & 0xffff));
    set_low16(&r->edx, rd16(r, 0x5bd8c2));
    r->eax = rd32(r, r->ebp - 0x2c);
    wr16(r, r->eax + 0x24, (r->edx & 0xffff));
    set_low16(&r->edx, rd16(r, 0x5bd8c4));
    r->eax = rd32(r, r->ebp - 0x2c);
    wr16(r, r->eax + 0x26, (r->edx & 0xffff));
    set_low16(&r->edx, rd16(r, 0x5bd8c6));
    r->eax = rd32(r, r->ebp - 0x2c);
    wr16(r, r->eax + 0x28, (r->edx & 0xffff));
    set_low16(&r->edx, rd16(r, 0x5bd8c8));
    r->eax = rd32(r, r->ebp - 0x2c);
    wr16(r, r->eax + 0x2a, (r->edx & 0xffff));
    set_low16(&r->edx, rd16(r, 0x5bd8cc));
    r->eax = rd32(r, r->ebp - 0x2c);
    wr16(r, r->eax + 0x2c, (r->edx & 0xffff));
    set_low16(&r->edx, rd16(r, 0x5bd8ce));
    r->eax = rd32(r, r->ebp - 0x2c);
    wr16(r, r->eax + 0x2e, (r->edx & 0xffff));
    wr32(r, r->ebp - 0x1c, 0x0);
    goto at_4b8522;
at_4b851f:
    wr32(r, r->ebp - 0x1c, rd32(r, r->ebp - 0x1c) + 1);
at_4b8522:
    r->eax = rd32(r, r->ebp - 0x2c);
    set_low16(&r->eax, rd16(r, r->eax + 0x22));
    r->eax = r->eax & 0xffff;
    if (r->eax <= rd32(r, r->ebp - 0x1c))
    {
        goto at_4b8547;
    }
    r->edx = rd32(r, r->ebp - 0x2c);
    r->edx = r->edx + rd32(r, r->ebp - 0x1c);
    r->eax = rd32(r, r->ebp - 0x1c);
    set_low8(&r->eax, rd8(r, r->eax + 0x5bd8d0));
    wr8(r, r->edx + 0x30, (r->eax & 0xff));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b851f;
at_4b8547:
    wr32(r, r->ebp - 0x1c, 0x0);
    goto at_4b8553;
at_4b8550:
    wr32(r, r->ebp - 0x1c, rd32(r, r->ebp - 0x1c) + 1);
at_4b8553:
    r->eax = rd32(r, r->ebp - 0x2c);
    set_low16(&r->eax, rd16(r, r->eax + 0x26));
    r->eax = r->eax & 0xffff;
    if (r->eax <= rd32(r, r->ebp - 0x1c))
    {
        goto at_4b8573;
    }
    r->eax = rd32(r, r->ebp - 0x2c);
    r->eax = r->eax + rd32(r, r->ebp - 0x1c);
    wr8(r, r->eax + 0x130, 0x7f);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b8550;
at_4b8573:
    r->edx = 0xc;
    r->eax = rd32(r, r->ebp - 0x2c);
    set_low16(&r->eax, rd16(r, r->eax + 0x28));
    r->eax = r->eax & 0xffff;
    call(r, 0x4ec160, 0);
    r->edx = r->eax;
    r->eax = rd32(r, r->ebp - 0x2c);
    wr32(r, r->eax + 0x150, r->edx);
    r->eax = rd32(r, r->ebp - 0x2c);
    if (rd32(r, r->eax + 0x150) != 0x0)
    {
        goto at_4b85b4;
    }
    r->eax = rd32(r, r->ebp - 0x2c);
    call(r, 0x40ef90, 0);
    wr32(r, r->ebp - 0x30, 0x8);
    goto at_4b8fb0;
at_4b85b4:
    r->eax = rd32(r, r->ebp - 0x2c);
    set_low16(&r->eax, rd16(r, r->eax + 0x2a));
    r->eax = r->eax & 0xffff;
    if ((int32_t)r->eax <= 0)
    {
        goto at_4b8607;
    }
    r->edx = 0xfc;
    r->eax = rd32(r, r->ebp - 0x2c);
    set_low16(&r->eax, rd16(r, r->eax + 0x2a));
    r->eax = r->eax & 0xffff;
    call(r, 0x4ec160, 0);
    r->edx = r->eax;
    r->eax = rd32(r, r->ebp - 0x2c);
    wr32(r, r->eax + 0x154, r->edx);
    r->eax = rd32(r, r->ebp - 0x2c);
    if (rd32(r, r->eax + 0x154) != 0x0)
    {
        goto at_4b8605;
    }
    r->eax = rd32(r, r->ebp - 0x2c);
    call(r, 0x40ef90, 0);
    wr32(r, r->ebp - 0x30, 0x8);
    goto at_4b8fb0;
at_4b8605:
    goto at_4b8614;
at_4b8607:
    r->eax = rd32(r, r->ebp - 0x2c);
    wr32(r, r->eax + 0x154, 0x0);
at_4b8614:
    r->eax = rd32(r, r->ebp - 0x2c);
    r->eax = rd32(r, r->eax + 0x150);
    wr32(r, r->ebp - 0x28, r->eax);
    wr32(r, r->ebp - 0x1c, 0x0);
    goto at_4b8630;
at_4b8629:
    wr32(r, r->ebp - 0x1c, rd32(r, r->ebp - 0x1c) + 1);
    wr32(r, r->ebp - 0x28, rd32(r, r->ebp - 0x28) + 0xc);
at_4b8630:
    r->eax = rd32(r, r->ebp - 0x2c);
    set_low16(&r->eax, rd16(r, r->eax + 0x28));
    r->eax = r->eax & 0xffff;
    if (r->eax <= rd32(r, r->ebp - 0x1c))
    {
        goto at_4b8768;
    }
    r->ecx = 0x4;
    r->ebx = 0x1;
    r->edx = 0x5bd9d0;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    r->ecx = 0x1;
    r->ebx = 0x1;
    r->edx = 0x5bd9d4;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    r->ecx = 0x2;
    r->ebx = 0x1;
    r->edx = 0x5bd9d5;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    r->ecx = 0x2;
    r->ebx = 0x1;
    r->edx = 0x5bd9d7;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    r->edx = rd32(r, 0x5bd9d0);
    r->edx = r->edx - 0x9;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48aa90, 0);
    if ((uint8_t)rd8(r, 0x5bd9d4) == (uint8_t)0x0)
    {
        goto at_4b86cf;
    }
    r->eax = rd32(r, r->ebp - 0x2c);
    call(r, 0x40ef90, 0);
    wr32(r, r->ebp - 0x30, 0xb);
    goto at_4b8fb0;
at_4b86cf:
    set_high8(&r->edx, 0);
    set_low8(&r->edx, rd8(r, 0x5bd9d4));
    r->eax = rd32(r, r->ebp - 0x28);
    wr16(r, r->eax, (r->edx & 0xffff));
    r->eax = rd32(r, r->ebp - 0x2c);
    set_low16(&r->edx, rd16(r, r->eax + 0x26));
    r->eax = rd32(r, r->ebp - 0x28);
    wr16(r, r->eax + 0x2, (r->edx & 0xffff));
    set_low16(&r->edx, rd16(r, 0x5bd9d5));
    r->eax = rd32(r, r->ebp - 0x28);
    wr16(r, r->eax + 0x4, (r->edx & 0xffff));
    set_low16(&r->edx, rd16(r, 0x5bd9d7));
    r->eax = rd32(r, r->ebp - 0x28);
    wr16(r, r->eax + 0x6, (r->edx & 0xffff));
    r->eax = rd32(r, r->ebp - 0x28);
    if ((uint16_t)rd16(r, r->eax + 0x6) == (uint16_t)0x0)
    {
        goto at_4b8763;
    }
    r->eax = rd32(r, r->ebp - 0x28);
    set_low16(&r->eax, rd16(r, r->eax + 0x6));
    r->eax = r->eax & 0xffff;
    call(r, 0x4e7c90, 0);
    r->edx = r->eax;
    r->eax = rd32(r, r->ebp - 0x28);
    wr32(r, r->eax + 0x8, r->edx);
    r->eax = rd32(r, r->ebp - 0x28);
    if (rd32(r, r->eax + 0x8) != 0x0)
    {
        goto at_4b8747;
    }
    r->eax = rd32(r, r->ebp - 0x2c);
    call(r, 0x40ef90, 0);
    wr32(r, r->ebp - 0x30, 0x8);
    goto at_4b8fb0;
at_4b8747:
    r->eax = rd32(r, r->ebp - 0x28);
    r->ecx = 0;
    set_low16(&r->ecx, rd16(r, r->eax + 0x6));
    r->ebx = 0x1;
    r->eax = rd32(r, r->ebp - 0x28);
    r->edx = rd32(r, r->eax + 0x8);
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
at_4b8763:
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b8629;
at_4b8768:
    r->eax = rd32(r, r->ebp - 0x2c);
    r->eax = rd32(r, r->eax + 0x154);
    wr32(r, r->ebp - 0x24, r->eax);
    wr32(r, r->ebp - 0x1c, 0x0);
    goto at_4b8787;
at_4b877d:
    wr32(r, r->ebp - 0x1c, rd32(r, r->ebp - 0x1c) + 1);
    wr32(r, r->ebp - 0x24, rd32(r, r->ebp - 0x24) + 0xfc);
at_4b8787:
    r->eax = rd32(r, r->ebp - 0x2c);
    set_low16(&r->eax, rd16(r, r->eax + 0x2a));
    r->eax = r->eax & 0xffff;
    if (r->eax <= rd32(r, r->ebp - 0x1c))
    {
        goto at_4b8fa1;
    }
    r->ecx = 0x4;
    r->ebx = 0x1;
    r->edx = 0x5bd9e0;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    r->ecx = 0x16;
    r->ebx = 0x1;
    r->edx = 0x5bd9e4;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    r->ecx = 0x1;
    r->ebx = 0x1;
    r->edx = 0x5bd9fa;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    r->ecx = 0x2;
    r->ebx = 0x1;
    r->edx = 0x5bd9fb;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    if ((uint16_t)rd16(r, 0x5bd9fb) == (uint16_t)0x0)
    {
        goto at_4b8a14;
    }
    r->ecx = 0x4;
    r->ebx = 0x1;
    r->edx = 0x5bd9fd;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    r->ecx = 0x60;
    r->ebx = 0x1;
    r->edx = 0x5bda01;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    wr32(r, r->ebp - 0x18, 0x0);
    goto at_4b8840;
at_4b883d:
    wr32(r, r->ebp - 0x18, rd32(r, r->ebp - 0x18) + 1);
at_4b8840:
    if (rd32(r, r->ebp - 0x18) >= 0xc)
    {
        goto at_4b8867;
    }
    r->ecx = 0x4;
    r->ebx = 0x1;
    r->eax = rd32(r, r->ebp - 0x18);
    r->eax = r->eax << 0x2;
    r->edx = 0x5bda61;
    r->edx = r->edx + r->eax;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b883d;
at_4b8867:
    wr32(r, r->ebp - 0x18, 0x0);
    goto at_4b8873;
at_4b8870:
    wr32(r, r->ebp - 0x18, rd32(r, r->ebp - 0x18) + 1);
at_4b8873:
    if (rd32(r, r->ebp - 0x18) >= 0xc)
    {
        goto at_4b889a;
    }
    r->ecx = 0x4;
    r->ebx = 0x1;
    r->eax = rd32(r, r->ebp - 0x18);
    r->eax = r->eax << 0x2;
    r->edx = 0x5bda91;
    r->edx = r->edx + r->eax;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b8870;
at_4b889a:
    r->ecx = 0x1;
    r->ebx = 0x1;
    r->edx = 0x5bdac1;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    r->ecx = 0x1;
    r->ebx = 0x1;
    r->edx = 0x5bdac2;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    r->ecx = 0x1;
    r->ebx = 0x1;
    r->edx = 0x5bdac3;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    r->ecx = 0x1;
    r->ebx = 0x1;
    r->edx = 0x5bdac4;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    r->ecx = 0x1;
    r->ebx = 0x1;
    r->edx = 0x5bdac5;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    r->ecx = 0x1;
    r->ebx = 0x1;
    r->edx = 0x5bdac6;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    r->ecx = 0x1;
    r->ebx = 0x1;
    r->edx = 0x5bdac7;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    r->ecx = 0x1;
    r->ebx = 0x1;
    r->edx = 0x5bdac8;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    r->ecx = 0x1;
    r->ebx = 0x1;
    r->edx = 0x5bdac9;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    r->ecx = 0x1;
    r->ebx = 0x1;
    r->edx = 0x5bdaca;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    r->ecx = 0x1;
    r->ebx = 0x1;
    r->edx = 0x5bdacb;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    r->ecx = 0x1;
    r->ebx = 0x1;
    r->edx = 0x5bdacc;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    r->ecx = 0x1;
    r->ebx = 0x1;
    r->edx = 0x5bdacd;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    r->ecx = 0x1;
    r->ebx = 0x1;
    r->edx = 0x5bdace;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    r->ecx = 0x2;
    r->ebx = 0x1;
    r->edx = 0x5bdacf;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    r->ecx = 0x2;
    r->ebx = 0x1;
    r->edx = 0x5bdad1;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    wr32(r, 0x5bd9e0, rd32(r, 0x5bd9e0) - 0xd6);
at_4b8a14:
    r->edx = rd32(r, 0x5bd9e0);
    r->edx = r->edx - 0x1d;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48aa90, 0);
    r->eax = 0;
    set_low8(&r->eax, rd8(r, 0x5bdac1));
    if ((int32_t)r->eax <= (int32_t)0xc)
    {
        goto at_4b8a38;
    }
    wr8(r, 0x5bdac1, 0xc);
at_4b8a38:
    r->eax = 0;
    set_low8(&r->eax, rd8(r, 0x5bdac2));
    if ((int32_t)r->eax <= (int32_t)0xc)
    {
        goto at_4b8a4b;
    }
    wr8(r, 0x5bdac2, 0xc);
at_4b8a4b:
    r->eax = 0;
    set_low16(&r->eax, rd16(r, 0x5bd9fb));
    if ((int32_t)r->eax > (int32_t)0x10)
    {
        goto at_4b8a64;
    }
    r->eax = 0;
    set_low8(&r->eax, rd8(r, 0x5bdac1));
    if ((int32_t)r->eax <= (int32_t)0xc)
    {
        goto at_4b8a66;
    }
at_4b8a64:
    goto at_4b8a72;
at_4b8a66:
    r->eax = 0;
    set_low8(&r->eax, rd8(r, 0x5bdac2));
    if ((int32_t)r->eax <= (int32_t)0xc)
    {
        goto at_4b8a86;
    }
at_4b8a72:
    r->eax = rd32(r, r->ebp - 0x2c);
    call(r, 0x40ef90, 0);
    wr32(r, r->ebp - 0x30, 0xb);
    goto at_4b8fb0;
at_4b8a86:
    r->ebx = 0x16;
    r->edx = 0x5bd9e4;
    r->eax = rd32(r, r->ebp - 0x24);
    call(r, 0x4eb860, 0);
    wr32(r, r->ebp - 0x18, 0x0);
    goto at_4b8aa4;
at_4b8aa1:
    wr32(r, r->ebp - 0x18, rd32(r, r->ebp - 0x18) + 1);
at_4b8aa4:
    if (rd32(r, r->ebp - 0x18) >= 0x60)
    {
        goto at_4b8adf;
    }
    r->edx = rd32(r, r->ebp - 0x24);
    r->edx = r->edx + rd32(r, r->ebp - 0x18);
    r->eax = rd32(r, r->ebp - 0x18);
    set_low8(&r->eax, rd8(r, r->eax + 0x5bda01));
    wr8(r, r->edx + 0x20, (r->eax & 0xff));
    r->eax = rd32(r, r->ebp - 0x24);
    r->eax = r->eax + rd32(r, r->ebp - 0x18);
    r->edx = 0;
    set_low8(&r->edx, rd8(r, r->eax + 0x20));
    r->eax = 0;
    set_low16(&r->eax, rd16(r, 0x5bd9fb));
    if ((int32_t)r->edx < (int32_t)r->eax)
    {
        goto at_4b8add;
    }
    r->eax = rd32(r, r->ebp - 0x24);
    r->eax = r->eax + rd32(r, r->ebp - 0x18);
    wr8(r, r->eax + 0x20, 0x0);
at_4b8add:
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b8aa1;
at_4b8adf:
    set_low16(&r->edx, rd16(r, 0x5bd9fb));
    r->eax = rd32(r, r->ebp - 0x24);
    wr16(r, r->eax + 0x80, (r->edx & 0xffff));
    set_low8(&r->edx, rd8(r, 0x5bdacb));
    r->eax = rd32(r, r->ebp - 0x24);
    wr8(r, r->eax + 0x82, (r->edx & 0xff));
    set_low8(&r->edx, rd8(r, 0x5bdacc));
    r->eax = rd32(r, r->ebp - 0x24);
    wr8(r, r->eax + 0x83, (r->edx & 0xff));
    set_low8(&r->edx, rd8(r, 0x5bdacd));
    r->eax = rd32(r, r->ebp - 0x24);
    wr8(r, r->eax + 0x84, (r->edx & 0xff));
    set_low8(&r->edx, rd8(r, 0x5bdace));
    r->eax = rd32(r, r->ebp - 0x24);
    wr8(r, r->eax + 0x85, (r->edx & 0xff));
    set_low16(&r->edx, rd16(r, 0x5bdacf));
    r->eax = rd32(r, r->ebp - 0x24);
    wr16(r, r->eax + 0x86, (r->edx & 0xffff));
    set_low8(&r->edx, rd8(r, 0x5bdac1));
    r->eax = rd32(r, r->ebp - 0x24);
    wr8(r, r->eax + 0xb8, (r->edx & 0xff));
    set_low8(&r->edx, rd8(r, 0x5bdac3));
    r->eax = rd32(r, r->ebp - 0x24);
    wr8(r, r->eax + 0xb9, (r->edx & 0xff));
    set_low8(&r->edx, rd8(r, 0x5bdac4));
    r->eax = rd32(r, r->ebp - 0x24);
    wr8(r, r->eax + 0xba, (r->edx & 0xff));
    set_low8(&r->edx, rd8(r, 0x5bdac5));
    r->eax = rd32(r, r->ebp - 0x24);
    wr8(r, r->eax + 0xbb, (r->edx & 0xff));
    if ((uint8_t)(rd8(r, 0x5bdac9) & 0x1) == 0)
    {
        goto at_4b8b8c;
    }
    r->eax = rd32(r, r->ebp - 0x24);
    wr8(r, r->eax + 0xbc, rd8(r, r->eax + 0xbc) | 0x1);
at_4b8b8c:
    if ((uint8_t)(rd8(r, 0x5bdac9) & 0x2) == 0)
    {
        goto at_4b8b9f;
    }
    r->eax = rd32(r, r->ebp - 0x24);
    wr8(r, r->eax + 0xbc, rd8(r, r->eax + 0xbc) | 0x2);
at_4b8b9f:
    if ((uint8_t)(rd8(r, 0x5bdac9) & 0x4) == 0)
    {
        goto at_4b8bb2;
    }
    r->eax = rd32(r, r->ebp - 0x24);
    wr8(r, r->eax + 0xbc, rd8(r, r->eax + 0xbc) | 0x4);
at_4b8bb2:
    wr32(r, r->ebp - 0x18, 0x0);
    goto at_4b8bbe;
at_4b8bbb:
    wr32(r, r->ebp - 0x18, rd32(r, r->ebp - 0x18) + 1);
at_4b8bbe:
    r->eax = rd32(r, r->ebp - 0x24);
    set_low8(&r->eax, rd8(r, r->eax + 0xb8));
    r->eax = r->eax & 0xff;
    if (r->eax <= rd32(r, r->ebp - 0x18))
    {
        goto at_4b8c16;
    }
    r->edx = rd32(r, r->ebp - 0x18);
    r->edx = r->edx << 0x2;
    r->eax = rd32(r, r->ebp - 0x18);
    r->eax = r->eax << 0x2;
    r->eax = r->eax + rd32(r, r->ebp - 0x24);
    set_low16(&r->edx, rd16(r, r->edx + 0x5bda61));
    wr16(r, r->eax + 0x88, (r->edx & 0xffff));
    r->eax = rd32(r, r->ebp - 0x18);
    r->eax = r->eax << 0x2;
    r->eax = rd32(r, r->eax + 0x5bda61);
    r->eax = r->eax >> 0x10;
    r->eax = r->eax & 0xffff;
    r->edx = r->eax;
    r->eax = rd32(r, r->ebp - 0x18);
    r->eax = r->eax << 0x2;
    r->eax = r->eax + rd32(r, r->ebp - 0x24);
    wr16(r, r->eax + 0x8a, (r->edx & 0xffff));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b8bbb;
at_4b8c16:
    set_low8(&r->edx, rd8(r, 0x5bdac2));
    r->eax = rd32(r, r->ebp - 0x24);
    wr8(r, r->eax + 0xf0, (r->edx & 0xff));
    set_low8(&r->edx, rd8(r, 0x5bdac6));
    r->eax = rd32(r, r->ebp - 0x24);
    wr8(r, r->eax + 0xf1, (r->edx & 0xff));
    set_low8(&r->edx, rd8(r, 0x5bdac7));
    r->eax = rd32(r, r->ebp - 0x24);
    wr8(r, r->eax + 0xf2, (r->edx & 0xff));
    set_low8(&r->edx, rd8(r, 0x5bdac8));
    r->eax = rd32(r, r->ebp - 0x24);
    wr8(r, r->eax + 0xf3, (r->edx & 0xff));
    if ((uint8_t)(rd8(r, 0x5bdaca) & 0x1) == 0)
    {
        goto at_4b8c65;
    }
    r->eax = rd32(r, r->ebp - 0x24);
    wr8(r, r->eax + 0xf4, rd8(r, r->eax + 0xf4) | 0x1);
at_4b8c65:
    if ((uint8_t)(rd8(r, 0x5bdaca) & 0x2) == 0)
    {
        goto at_4b8c78;
    }
    r->eax = rd32(r, r->ebp - 0x24);
    wr8(r, r->eax + 0xf4, rd8(r, r->eax + 0xf4) | 0x2);
at_4b8c78:
    if ((uint8_t)(rd8(r, 0x5bdaca) & 0x4) == 0)
    {
        goto at_4b8c8b;
    }
    r->eax = rd32(r, r->ebp - 0x24);
    wr8(r, r->eax + 0xf4, rd8(r, r->eax + 0xf4) | 0x4);
at_4b8c8b:
    wr32(r, r->ebp - 0x18, 0x0);
    goto at_4b8c97;
at_4b8c94:
    wr32(r, r->ebp - 0x18, rd32(r, r->ebp - 0x18) + 1);
at_4b8c97:
    r->eax = rd32(r, r->ebp - 0x24);
    set_low8(&r->eax, rd8(r, r->eax + 0xf0));
    r->eax = r->eax & 0xff;
    if (r->eax <= rd32(r, r->ebp - 0x18))
    {
        goto at_4b8cef;
    }
    r->edx = rd32(r, r->ebp - 0x18);
    r->edx = r->edx << 0x2;
    r->eax = rd32(r, r->ebp - 0x18);
    r->eax = r->eax << 0x2;
    r->eax = r->eax + rd32(r, r->ebp - 0x24);
    set_low16(&r->edx, rd16(r, r->edx + 0x5bda91));
    wr16(r, r->eax + 0xc0, (r->edx & 0xffff));
    r->eax = rd32(r, r->ebp - 0x18);
    r->eax = r->eax << 0x2;
    r->eax = rd32(r, r->eax + 0x5bda91);
    r->eax = r->eax >> 0x10;
    r->eax = r->eax & 0xffff;
    r->edx = r->eax;
    r->eax = rd32(r, r->ebp - 0x18);
    r->eax = r->eax << 0x2;
    r->eax = r->eax + rd32(r, r->ebp - 0x24);
    wr16(r, r->eax + 0xc2, (r->edx & 0xffff));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b8c94;
at_4b8cef:
    r->eax = rd32(r, r->ebp - 0x24);
    if ((uint16_t)rd16(r, r->eax + 0x80) == (uint16_t)0x0)
    {
        goto at_4b8d40;
    }
    r->edx = 0x3c;
    r->eax = rd32(r, r->ebp - 0x24);
    set_low16(&r->eax, rd16(r, r->eax + 0x80));
    r->eax = r->eax & 0xffff;
    call(r, 0x4ec160, 0);
    r->edx = r->eax;
    r->eax = rd32(r, r->ebp - 0x24);
    wr32(r, r->eax + 0xf8, r->edx);
    r->eax = rd32(r, r->ebp - 0x24);
    if (rd32(r, r->eax + 0xf8) != 0x0)
    {
        goto at_4b8d40;
    }
    r->eax = rd32(r, r->ebp - 0x2c);
    call(r, 0x40ef90, 0);
    wr32(r, r->ebp - 0x30, 0x8);
    goto at_4b8fb0;
at_4b8d40:
    r->eax = rd32(r, r->ebp - 0x24);
    r->eax = rd32(r, r->eax + 0xf8);
    wr32(r, r->ebp - 0x20, r->eax);
    wr32(r, r->ebp - 0x18, 0x0);
    goto at_4b8d5c;
at_4b8d55:
    wr32(r, r->ebp - 0x18, rd32(r, r->ebp - 0x18) + 1);
    wr32(r, r->ebp - 0x20, rd32(r, r->ebp - 0x20) + 0x3c);
at_4b8d5c:
    r->eax = 0;
    set_low16(&r->eax, rd16(r, 0x5bd9fb));
    if (r->eax <= rd32(r, r->ebp - 0x18))
    {
        goto at_4b8f0d;
    }
    r->ecx = 0x4;
    r->ebx = 0x1;
    r->edx = 0x5bdad8;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    r->ecx = 0x4;
    r->ebx = 0x1;
    r->edx = 0x5bdadc;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    r->ecx = 0x4;
    r->ebx = 0x1;
    r->edx = 0x5bdae0;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    r->ecx = 0x1;
    r->ebx = 0x1;
    r->edx = 0x5bdae4;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    r->ecx = 0x1;
    r->ebx = 0x1;
    r->edx = 0x5bdae5;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    r->ecx = 0x1;
    r->ebx = 0x1;
    r->edx = 0x5bdae6;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    r->ecx = 0x1;
    r->ebx = 0x1;
    r->edx = 0x5bdae7;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    r->ecx = 0x1;
    r->ebx = 0x1;
    r->edx = 0x5bdae8;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    r->ecx = 0x1;
    r->ebx = 0x1;
    r->edx = 0x5bdae9;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    r->ecx = 0x16;
    r->ebx = 0x1;
    r->edx = 0x5bdaea;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    r->edx = rd32(r, 0x5bd9fd);
    r->edx = r->edx - 0x28;
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48aa90, 0);
    r->ebx = 0x16;
    r->edx = 0x5bdaea;
    r->eax = rd32(r, r->ebp - 0x20);
    call(r, 0x4eb860, 0);
    r->edx = rd32(r, 0x5bdad8);
    r->eax = rd32(r, r->ebp - 0x20);
    wr32(r, r->eax + 0x2c, r->edx);
    r->edx = rd32(r, 0x5bdadc);
    r->eax = rd32(r, r->ebp - 0x20);
    wr32(r, r->eax + 0x30, r->edx);
    r->eax = rd32(r, 0x5bdadc);
    r->eax = r->eax + rd32(r, 0x5bdae0);
    r->edx = rd32(r, r->ebp - 0x20);
    wr32(r, r->edx + 0x34, r->eax);
    r->eax = rd32(r, r->ebp - 0x20);
    wr16(r, r->eax + 0x38, 0x20ab);
    set_low8(&r->edx, rd8(r, 0x5bdae4));
    r->eax = rd32(r, r->ebp - 0x20);
    wr8(r, r->eax + 0x20, (r->edx & 0xff));
    set_low8(&r->edx, rd8(r, 0x5bdae7));
    r->eax = rd32(r, r->ebp - 0x20);
    wr8(r, r->eax + 0x21, (r->edx & 0xff));
    set_low8(&r->edx, rd8(r, 0x5bdae8));
    r->eax = rd32(r, r->ebp - 0x20);
    wr8(r, r->eax + 0x22, (r->edx & 0xff));
    set_low8(&r->edx, rd8(r, 0x5bdae5));
    r->eax = rd32(r, r->ebp - 0x20);
    wr8(r, r->eax + 0x23, (r->edx & 0xff));
    if ((uint8_t)(rd8(r, 0x5bdae6) & 0x10) == 0)
    {
        goto at_4b8ee8;
    }
    r->eax = rd32(r, r->ebp - 0x20);
    wr8(r, r->eax + 0x3a, rd8(r, r->eax + 0x3a) | 0x1);
at_4b8ee8:
    if ((uint8_t)(rd8(r, 0x5bdae6) & 0x1) == 0)
    {
        goto at_4b8ef8;
    }
    r->eax = rd32(r, r->ebp - 0x20);
    wr8(r, r->eax + 0x3a, rd8(r, r->eax + 0x3a) | 0x10);
at_4b8ef8:
    if ((uint8_t)(rd8(r, 0x5bdae6) & 0x2) == 0)
    {
        goto at_4b8f08;
    }
    r->eax = rd32(r, r->ebp - 0x20);
    wr8(r, r->eax + 0x3a, rd8(r, r->eax + 0x3a) | 0x20);
at_4b8f08:
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b8d55;
at_4b8f0d:
    r->eax = rd32(r, r->ebp - 0x24);
    r->eax = rd32(r, r->eax + 0xf8);
    wr32(r, r->ebp - 0x20, r->eax);
    wr32(r, r->ebp - 0x18, 0x0);
    goto at_4b8f29;
at_4b8f22:
    wr32(r, r->ebp - 0x18, rd32(r, r->ebp - 0x18) + 1);
    wr32(r, r->ebp - 0x20, rd32(r, r->ebp - 0x20) + 0x3c);
at_4b8f29:
    r->eax = 0;
    set_low16(&r->eax, rd16(r, 0x5bd9fb));
    if (r->eax <= rd32(r, r->ebp - 0x18))
    {
        goto at_4b8f9c;
    }
    r->eax = rd32(r, r->ebp - 0x20);
    if (rd32(r, r->eax + 0x2c) == 0x0)
    {
        goto at_4b8f9a;
    }
    r->eax = rd32(r, r->ebp - 0x20);
    r->eax = r->eax + 0x24;
    call(r, 0x40ac50, 0);
    wr32(r, r->ebp - 0x14, r->eax);
    if (rd32(r, r->ebp - 0x14) == 0x0)
    {
        goto at_4b8f63;
    }
    r->eax = rd32(r, r->ebp - 0x2c);
    call(r, 0x40ef90, 0);
    r->eax = rd32(r, r->ebp - 0x14);
    wr32(r, r->ebp - 0x30, r->eax);
    goto at_4b8fb0;
at_4b8f63:
    r->eax = rd32(r, r->ebp - 0x20);
    r->ecx = rd32(r, r->eax + 0x2c);
    r->ebx = 0x1;
    r->eax = rd32(r, r->ebp - 0x20);
    r->edx = rd32(r, r->eax + 0x24);
    r->eax = rd32(r, r->ebp - 0x38);
    call(r, 0x48a930, 0);
    r->eax = rd32(r, r->ebp - 0x20);
    r->eax = r->eax + 0x24;
    call(r, 0x4b8fbc, 0);
    r->eax = rd32(r, r->ebp - 0x20);
    r->ebx = rd32(r, r->eax + 0x2c);
    r->edx = 0;
    r->eax = rd32(r, r->ebp - 0x20);
    r->eax = r->eax + 0x24;
    call(r, 0x40acd0, 0);
at_4b8f9a:
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b8f22;
at_4b8f9c:
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b877d;
at_4b8fa1:
    r->eax = rd32(r, r->ebp - 0x2c);
    r->edx = rd32(r, r->ebp - 0x34);
    wr32(r, r->edx, r->eax);
    wr32(r, r->ebp - 0x30, 0x0);
at_4b8fb0:
    r->eax = rd32(r, r->ebp - 0x30);
    r->edi = rd32(r, r->ebp - 0x10);
    r->esi = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
}

uint32_t vertrix_port_xm_module_load_4b826f(PORT_SIGNATURE)
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
    port_set32(&port, r.ebp, -0xcu, entry->esi);
    port_set32(&port, r.ebp, -0x10u, entry->edi);
    run(&r);
    return port_return(&port, r.eax, r.edx);
}
