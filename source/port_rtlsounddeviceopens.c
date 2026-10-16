#include "port_rtlsounddeviceopens.h"

/* At 0x40b6e0 the routine zeroes the 0x79c-byte sound state at 0x52f170 and returns 2 if its config
 * argument is null. */

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

/* The last value pushed taken back. */
static uint32_t pop(Regs *r)
{
    return r->pushed != 0 ? r->stack[--r->pushed] : 0;
}

/* An indirect call (an import or a method): every value pushed passed and popped, as stdcall. */
static void call_all(Regs *r, uint32_t target)
{
    call_with_stack(r, target, r->pushed, 0);
}

/* Original 0x40b6e0: At 0x40b6e0 the routine zeroes the 0x79c-byte sound state at 0x52f170 and
 * returns 2 if its config argument is null. It creates the device with 0x40b620 and returns 5 if
 * that fails. It calls vtable +0x18 (import 0x4f1994 result, 2) and +0x10 (0x60-byte caps),
 * clearing the config's arg+5 and arg+4 bits when caps flags 2 and 8 are absent. It creates a
 * buffer through +0xc (0x14-byte desc, flags 1) into 0x52f174 and calls +0x38 with a format block
 * starting at 44100 Hz (arg+6), halving the rate on failure while it is above 11025 Hz. On success
 * it calls +0x30(0,0,1), stores import 0x4f1bf8 at 0x52f900, zeroes 0x52f904 and calls
 * lifted_curve_table_build (0x40ba00). It fills 256 dwords at 0x52f300 with (-256000 + 2000*i) >> 7
 * and returns 0. A later failure releases the device via 0x40b660 and returns 5. Evidence: calls
 * 0x4eb5c0, 0x40b620, 0x40b660, 0x40ba00; reads 0x52f170, 0x4f1994, 0x52f174, 0x4f1bf8; writes
 * 0x52f900, 0x52f904. Register-for-register from the listing (0x40b6ee..0x40b973); labels are the
 * original addresses. */
static void run(Regs *r)
{
    r->esi = r->eax;
    r->ebx = 0x79c;
    r->edx = 0;
    r->eax = 0x52f170;
    call(r, 0x4eb5c0, 0);
    if (r->esi != 0)
    {
        goto at_40b714;
    }
    r->eax = 0x2;
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_40b714:
    r->ebx = 0;
    r->edx = 0x52f170;
    r->eax = 0;
    call(r, 0x40b620, 0);
    if (r->eax == 0)
    {
        goto at_40b735;
    }
    r->eax = 0x5;
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_40b735:
    r->eax = rd32(r, 0x52f170);
    r->ebx = rd32(r, r->eax);
    push(r, 0x2);
    call_all(r, rd32(r, 0x4f1994));
    push(r, r->eax);
    r->edx = rd32(r, 0x52f170);
    push(r, r->edx);
    call_all(r, rd32(r, r->ebx + 0x18));
    if (r->eax != 0)
    {
        goto at_40b876;
    }
    wr32(r, r->ebp - 0x9c, 0x60);
    r->eax = rd32(r, 0x52f170);
    r->edx = rd32(r, r->eax);
    r->ecx = r->ebp - 0x9c;
    push(r, r->ecx);
    push(r, r->eax);
    call_all(r, rd32(r, r->edx + 0x10));
    if (r->eax != 0)
    {
        goto at_40b876;
    }
    wr16(r, r->esi + 0x6, 0xac44);
    if ((uint8_t)(rd8(r, r->ebp - 0x98) & 0x2) != 0)
    {
        goto at_40b78f;
    }
    wr8(r, r->esi + 0x5, rd8(r, r->esi + 0x5) & 0xfe);
at_40b78f:
    if ((uint8_t)(rd8(r, r->ebp - 0x98) & 0x8) != 0)
    {
        goto at_40b79c;
    }
    wr8(r, r->esi + 0x4, rd8(r, r->esi + 0x4) & 0xfe);
at_40b79c:
    wr16(r, r->ebp - 0x28, 0x1);
    flags(r, F_LOGIC, rd8(r, r->esi + 0x5) & 0x1, 0, 8);
    set_low8(&r->eax, cond(r, CC_NE));
    r->eax = r->eax & 0xff;
    r->eax = r->eax + 1;
    wr16(r, r->ebp - 0x26, (r->eax & 0xffff));
    if ((uint8_t)(rd8(r, r->esi + 0x4) & 0x1) == 0)
    {
        goto at_40b88f;
    }
    r->eax = 0x10;
at_40b7c2:
    wr16(r, r->ebp - 0x1a, (r->eax & 0xffff));
    r->eax = 0;
    set_low16(&r->eax, rd16(r, r->esi + 0x6));
    wr32(r, r->ebp - 0x24, r->eax);
    r->eax = 0;
    set_low16(&r->eax, rd16(r, r->esi + 0x6));
    wr32(r, r->ebp - 0x20, r->eax);
    wr16(r, r->ebp - 0x1c, 0x1);
    r->ecx = 0;
    wr16(r, r->ebp - 0x18, (r->ecx & 0xffff));
    if ((uint8_t)(rd8(r, r->esi + 0x5) & 0x1) == 0)
    {
        goto at_40b7f6;
    }
    r->ebx = r->eax + r->eax;
    wr32(r, r->ebp - 0x20, r->ebx);
    wr16(r, r->ebp - 0x1c, 0x2);
at_40b7f6:
    if ((uint8_t)(rd8(r, r->esi + 0x4) & 0x1) == 0)
    {
        goto at_40b80d;
    }
    r->edi = rd32(r, r->ebp - 0x20);
    r->edi = r->edi + r->edi;
    wr32(r, r->ebp - 0x20, r->edi);
    r->eax = rd32(r, r->ebp - 0x1c);
    r->eax = r->eax + r->eax;
    wr16(r, r->ebp - 0x1c, (r->eax & 0xffff));
at_40b80d:
    r->ebx = 0x14;
    r->edx = 0;
    r->eax = r->ebp - 0x3c;
    call(r, 0x4eb5c0, 0);
    wr32(r, r->ebp - 0x3c, 0x14);
    wr32(r, r->ebp - 0x38, 0x1);
    r->ecx = 0;
    wr32(r, r->ebp - 0x34, r->ecx);
    wr32(r, r->ebp - 0x2c, r->ecx);
    r->eax = rd32(r, 0x52f170);
    r->edx = rd32(r, r->eax);
    push(r, r->ecx);
    push(r, 0x52f174);
    r->ecx = r->ebp - 0x3c;
    push(r, r->ecx);
    push(r, r->eax);
    call_all(r, rd32(r, r->edx + 0xc));
    if (r->eax != 0)
    {
        goto at_40b876;
    }
at_40b84b:
    r->eax = rd32(r, 0x52f174);
    r->ecx = rd32(r, r->eax);
    r->edx = r->ebp - 0x28;
    push(r, r->edx);
    push(r, r->eax);
    call_all(r, rd32(r, r->ecx + 0x38));
    if (r->eax == 0)
    {
        goto at_40b899;
    }
    if ((uint16_t)rd16(r, r->esi + 0x6) <= (uint16_t)0x2b11)
    {
        goto at_40b876;
    }
    wr32(r, r->ebp - 0x24, rd32(r, r->ebp - 0x24) >> 0x1);
    wr32(r, r->ebp - 0x20, rd32(r, r->ebp - 0x20) >> 0x1);
    wr16(r, r->ebp - 0x1c, rd16(r, r->ebp - 0x1c) >> 0x1);
    wr16(r, r->esi + 0x6, rd16(r, r->esi + 0x6) >> 0x1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_40b84b;
at_40b876:
    r->eax = rd32(r, 0x52f170);
    call(r, 0x40b660, 0);
    r->eax = 0x5;
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_40b88f:
    r->eax = 0x8;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_40b7c2;
at_40b899:
    r->eax = rd32(r, 0x52f174);
    r->edx = rd32(r, r->eax);
    push(r, 0x1);
    push(r, 0x0);
    push(r, 0x0);
    push(r, r->eax);
    call_all(r, rd32(r, r->edx + 0x30));
    call_all(r, rd32(r, 0x4f1bf8));
    wr32(r, 0x52f900, r->eax);
    r->esi = 0;
    wr32(r, 0x52f904, r->esi);
    r->edx = 0x60;
    r->eax = 0x1;
    call(r, 0x40ba00, 0);
    r->eax = 0;
    r->esi = 0xfffc1800u;
at_40b8d4:
    r->edx = r->esi;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x7);
    wr32(r, r->eax + 0x52f300, r->edx);
    r->eax = r->eax + 0x4;
    r->esi = r->esi + 0x7d0;
    if (r->eax != 0x400 && !r->port->env.failed)
    {
        goto at_40b8d4;
    }
    r->eax = 0;
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
    push(r, r->ebx);
    push(r, r->ecx);
    push(r, r->edx);
    push(r, r->esi);
    if (rd32(r, 0x52f170) == 0x0)
    {
        goto at_40b94a;
    }
    r->ecx = rd32(r, 0x52f174);
    if (r->ecx != 0)
    {
        goto at_40b962;
    }
at_40b917:
    r->ebx = 0;
at_40b919:
    r->esi = rd32(r, r->ebx + 0x52f178);
    if (r->esi == 0)
    {
        goto at_40b935;
    }
    r->edx = rd32(r, r->esi);
    push(r, r->esi);
    call_all(r, rd32(r, r->edx + 0x48));
    r->eax = rd32(r, r->ebx + 0x52f178);
    r->edx = rd32(r, r->eax);
    push(r, r->eax);
    call_all(r, rd32(r, r->edx + 0x8));
at_40b935:
    r->ebx = r->ebx + 0x4;
    if (r->ebx != 0x80 && !r->port->env.failed)
    {
        goto at_40b919;
    }
    r->eax = rd32(r, 0x52f170);
    call(r, 0x40b660, 0);
at_40b94a:
    r->ebx = 0x79c;
    r->edx = 0;
    r->eax = 0x52f170;
    call(r, 0x4eb5c0, 0);
    r->eax = 0;
    r->esi = pop(r);
    r->edx = pop(r);
    r->ecx = pop(r);
    r->ebx = pop(r);
    return;
at_40b962:
    r->edx = rd32(r, r->ecx);
    push(r, r->ecx);
    call_all(r, rd32(r, r->edx + 0x48));
    r->eax = rd32(r, 0x52f174);
    r->edx = rd32(r, r->eax);
    push(r, r->eax);
    call_all(r, rd32(r, r->edx + 0x8));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_40b917;
}

uint32_t vertrix_port_sound_device_open_40b6e0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0xa0
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
