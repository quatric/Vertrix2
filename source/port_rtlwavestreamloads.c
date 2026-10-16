#include "port_rtlwavestreamloads.h"

/* The routine 0x4b7e80 returns 2 when the output pointer is null, otherwise sets *out to 0. */

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

/* Original 0x4b7e80: The routine 0x4b7e80 returns 2 when the output pointer is null, otherwise sets
 * *out to 0. It allocates a 0x18-byte record with clear_allocate (0x4ec160) and returns 8 if that
 * fails. It reads a 'RIFF'/'WAVE' header with stream_read_exact (0x48a930) and walks the chunks. It
 * reads the 'fmt ' fields into 0x5bd868..0x5bd876 and skips other chunks with stream_skip
 * (0x48aa90). On the 'data' chunk it requires format tag 1 and sets flags from the bit depth and
 * channel count. It then calls sample_load (0x40ac50) and reads the samples, flipping the sign of
 * 8-bit data with xor 0x80. It hands the samples to driver_write (0x40acd0), stores the record to
 * *out and adds the size to 0x598dac. It returns 0 on success. On a bad header or a missing 'data'
 * chunk it frees the record through 0x4b8170 and returns 0xb. If sample_load fails it frees the
 * record the same way and returns sample_load's result. The only caller is sample_file_read
 * (0x4b7e69). Evidence: calls 0x4ec160, 0x48a930, 0x4eb5c0, 0x48aa90, 0x4b8170, 0x40ac50, 0x40acd0;
 * reads 0x5bd854, 0x5bd850, 0x5bd858, 0x5bd864, 0x5bd860, 0x5bd868, 0x5bd86c, 0x5bd876, 0x5bd86a,
 * 0x598dac; writes 0x5bd854, 0x5bd864, 0x598dac. Register-for-register from the listing
 * (0x4b7e8a..0x4b8161); labels are the original addresses. */
static void run(Regs *r)
{
    r->esi = r->eax;
    wr32(r, r->ebp - 0x14, r->edx);
    if (r->edx != 0)
    {
        goto at_4b7ea1;
    }
    r->eax = 0x2;
    r->edi = rd32(r, r->ebp - 0x10);
    r->esi = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4b7ea1:
    r->eax = 0x1;
    wr32(r, r->edx, 0x0);
    r->edx = 0x18;
    call(r, 0x4ec160, 0);
    r->edi = r->eax;
    if (r->eax != 0)
    {
        goto at_4b7eca;
    }
    r->eax = 0x8;
    r->edi = rd32(r, r->ebp - 0x10);
    r->esi = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4b7eca:
    r->ecx = 0x4;
    r->ebx = 0x1;
    r->edx = 0x5bd850;
    r->eax = r->esi;
    call(r, 0x48a930, 0);
    r->ecx = 0x4;
    r->ebx = 0x1;
    r->edx = 0x5bd854;
    r->eax = r->esi;
    call(r, 0x48a930, 0);
    r->ecx = 0x4;
    r->ebx = 0x1;
    r->edx = 0x5bd858;
    r->eax = r->esi;
    call(r, 0x48a930, 0);
    r->eax = rd32(r, 0x5bd854);
    r->ecx = rd32(r, 0x5bd854);
    r->eax = r->eax & 0x1;
    r->ecx = r->ecx + r->eax;
    r->ebx = rd32(r, 0x5bd850);
    wr32(r, 0x5bd854, r->ecx);
    if (r->ebx != 0x46464952)
    {
        goto at_4b807e;
    }
    if (rd32(r, 0x5bd858) != 0x45564157)
    {
        goto at_4b807e;
    }
    r->ebx = 0x10;
    r->eax = 0x5bd868;
    r->edx = 0;
    call(r, 0x4eb5c0, 0);
    r->edx = rd32(r, 0x5bd854);
    r->edx = r->edx - 0x4;
    flags(r, F_SUB, r->edx + 0x4, 0x4, 32);
    wr32(r, 0x5bd854, r->edx);
    if (cond(r, CC_E))
    {
        goto at_4b8070;
    }
at_4b7f6a:
    r->ecx = 0x4;
    r->ebx = 0x1;
    r->edx = 0x5bd860;
    r->eax = r->esi;
    call(r, 0x48a930, 0);
    r->ecx = 0x4;
    r->ebx = 0x1;
    r->edx = 0x5bd864;
    r->eax = r->esi;
    call(r, 0x48a930, 0);
    r->eax = rd32(r, 0x5bd864);
    r->edx = rd32(r, 0x5bd864);
    r->eax = r->eax & 0x1;
    r->edx = r->edx + r->eax;
    r->ecx = rd32(r, 0x5bd854);
    wr32(r, 0x5bd864, r->edx);
    r->eax = r->edx + 0x8;
    r->ecx = r->ecx - r->eax;
    r->ebx = rd32(r, 0x5bd860);
    wr32(r, 0x5bd854, r->ecx);
    if (r->ebx != 0x20746d66)
    {
        goto at_4b8093;
    }
    r->ecx = 0x2;
    r->ebx = 0x1;
    r->edx = 0x5bd868;
    r->eax = r->esi;
    call(r, 0x48a930, 0);
    r->ecx = 0x2;
    r->ebx = 0x1;
    r->edx = 0x5bd86a;
    r->eax = r->esi;
    call(r, 0x48a930, 0);
    r->ecx = 0x4;
    r->ebx = 0x1;
    r->edx = 0x5bd86c;
    r->eax = r->esi;
    call(r, 0x48a930, 0);
    r->ecx = 0x4;
    r->ebx = 0x1;
    r->edx = 0x5bd870;
    r->eax = r->esi;
    call(r, 0x48a930, 0);
    r->ecx = 0x2;
    r->ebx = 0x1;
    r->edx = 0x5bd874;
    r->eax = r->esi;
    call(r, 0x48a930, 0);
    r->ecx = 0x2;
    r->ebx = 0x1;
    r->edx = 0x5bd876;
    r->eax = r->esi;
    call(r, 0x48a930, 0);
    r->edx = rd32(r, 0x5bd864);
    r->eax = r->esi;
    r->edx = r->edx - 0x10;
at_4b805e:
    call(r, 0x48aa90, 0);
    if (rd32(r, 0x5bd854) != 0x0 && !r->port->env.failed)
    {
        goto at_4b7f6a;
    }
at_4b8070:
    r->eax = 0xb;
    r->edi = rd32(r, r->ebp - 0x10);
    r->esi = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4b807e:
    r->eax = r->edi;
    call(r, 0x4b8170, 0);
    r->eax = 0xb;
    r->edi = rd32(r, r->ebp - 0x10);
    r->esi = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4b8093:
    if (r->ebx != 0x61746164)
    {
        goto at_4b815f;
    }
    if ((uint16_t)rd16(r, 0x5bd868) != (uint16_t)0x1 && !r->port->env.failed)
    {
        goto at_4b807e;
    }
    r->eax = rd32(r, 0x5bd864);
    wr32(r, r->edi + 0x8, r->eax);
    set_low16(&r->eax, rd16(r, 0x5bd86c));
    wr16(r, r->edi + 0x16, 0x0);
    wr16(r, r->edi + 0x14, (r->eax & 0xffff));
    if ((uint16_t)rd16(r, 0x5bd876) == (uint16_t)0x8)
    {
        goto at_4b80cf;
    }
    wr8(r, r->edi + 0x16, rd8(r, r->edi + 0x16) | 0x1);
at_4b80cf:
    if ((uint16_t)rd16(r, 0x5bd86a) == (uint16_t)0x1)
    {
        goto at_4b80dd;
    }
    wr8(r, r->edi + 0x17, rd8(r, r->edi + 0x17) | 0x1);
at_4b80dd:
    r->eax = r->edi;
    call(r, 0x40ac50, 0);
    r->edx = r->eax;
    if (r->eax != 0)
    {
        goto at_4b814d;
    }
    r->ebx = 0x1;
    r->eax = r->esi;
    r->ecx = rd32(r, r->edi + 0x8);
    r->edx = rd32(r, r->edi);
    call(r, 0x48a930, 0);
    if ((uint8_t)(rd8(r, r->edi + 0x16) & 0x1) != 0)
    {
        goto at_4b8120;
    }
    r->edx = rd32(r, r->edi + 0x8);
    r->eax = 0;
    if (r->edx == 0)
    {
        goto at_4b8120;
    }
at_4b810a:
    r->esi = rd32(r, r->edi);
    wr8(r, r->esi + r->eax, rd8(r, r->esi + r->eax) ^ 0x80);
    r->eax = r->eax + 1;
    if (r->eax < rd32(r, r->edi + 0x8) && !r->port->env.failed)
    {
        goto at_4b810a;
    }
at_4b8120:
    r->eax = r->edi;
    r->ebx = rd32(r, r->edi + 0x8);
    r->edx = 0;
    call(r, 0x40acd0, 0);
    r->eax = rd32(r, r->ebp - 0x14);
    wr32(r, r->eax, r->edi);
    r->ebx = rd32(r, 0x598dac);
    r->eax = rd32(r, r->edi + 0x8);
    r->ebx = r->ebx + r->eax;
    wr32(r, 0x598dac, r->ebx);
    r->eax = 0;
    r->edi = rd32(r, r->ebp - 0x10);
    r->esi = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4b814d:
    r->eax = r->edi;
    call(r, 0x4b8170, 0);
    r->eax = r->edx;
    r->edi = rd32(r, r->ebp - 0x10);
    r->esi = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4b815f:
    r->eax = r->esi;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b805e;
}

uint32_t vertrix_port_wave_stream_load_4b7e80(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x18
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
