#include "port_rtlsurfaceflips.h"

/* Flips a loaded bitmap's rows top to bottom. */

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

/* Original 0x479b50: Flips a loaded bitmap's rows top to bottom. Evidence: no calls.
 * Register-for-register from the listing (0x479b50..0x479d64); labels are the original addresses.
 */
static void run(Regs *r)
{
    push_mem(r, r->ebx);
    push_mem(r, r->ecx);
    push_mem(r, r->edx);
    push_mem(r, r->esi);
    push_mem(r, r->edi);
    push_mem(r, r->ebp);
    r->esp = r->esp - 0x18;
    set_low16(&r->edx, rd16(r, r->eax + 0x8));
    wr16(r, r->esp + 0x14, (r->edx & 0xffff));
    set_low8(&r->edx, rd8(r, r->eax + 0xc));
    set_low16(&r->ebx, rd16(r, r->eax + 0x4));
    if ((uint8_t)((r->edx & 0xff)) == (uint8_t)0x1)
    {
        goto at_479bef;
    }
    if ((uint8_t)((r->edx & 0xff)) != (uint8_t)0x2)
    {
        goto at_479c76;
    }
    r->edx = rd32(r, r->esp + 0x12);
    r->ecx = (uint32_t)(int32_t)(int16_t)(r->ebx & 0xffff);
    r->eax = rd32(r, r->eax);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    wr32(r, r->esp + 0x10, r->eax);
    r->eax = r->edx - 0x1;
    r->eax = r->eax * r->ecx;
    r->ecx = rd32(r, r->esp + 0x10);
    r->eax = r->eax + r->eax;
    r->ecx = r->ecx + r->eax;
    r->eax = r->edx;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    r->eax = r->eax - r->edx;
    r->eax = (uint32_t)((int32_t)r->eax >> 0x1);
    wr32(r, r->esp + 0x4, r->ecx);
    wr16(r, r->esp + 0x14, (r->eax & 0xffff));
    if ((uint16_t)((r->eax & 0xffff)) == 0)
    {
        goto at_479be5;
    }
at_479bb0:
    r->eax = 0;
at_479bb2:
    r->edx = 0;
    r->ecx = (uint32_t)(int32_t)(int16_t)(r->ebx & 0xffff);
    set_low16(&r->edx, (r->eax & 0xffff));
    if ((int32_t)r->edx < (int32_t)r->ecx)
    {
        goto at_479c56;
    }
    r->edx = rd32(r, r->esp + 0x4);
    r->ecx = r->ecx + r->ecx;
    r->eax = rd32(r, r->esp + 0x10);
    r->edx = r->edx - r->ecx;
    r->eax = r->eax + r->ecx;
    wr32(r, r->esp + 0x4, r->edx);
    r->edx = rd32(r, r->esp + 0x14);
    wr32(r, r->esp + 0x10, r->eax);
    set_low16(&r->edx, (r->edx & 0xffff) - 1);
    flags(r, F_DEC, (r->edx & 0xffff), 0, 16);
    wr16(r, r->esp + 0x14, (r->edx & 0xffff));
    if (cond(r, CC_NE) && !r->port->env.failed)
    {
        goto at_479bb0;
    }
at_479be5:
    r->esp = r->esp + 0x18;
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_479bef:
    r->edx = rd32(r, r->esp + 0x12);
    r->ecx = (uint32_t)(int32_t)(int16_t)(r->ebx & 0xffff);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->edi = rd32(r, r->eax);
    r->eax = r->edx - 0x1;
    r->eax = r->eax * r->ecx;
    r->ecx = r->edi + r->eax;
    r->eax = r->edx;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    r->eax = r->eax - r->edx;
    r->eax = (uint32_t)((int32_t)r->eax >> 0x1);
    wr32(r, r->esp + 0x8, r->ecx);
    wr16(r, r->esp + 0x14, (r->eax & 0xffff));
    flags(r, F_LOGIC, (r->eax & 0xffff), 0, 16);
at_479c19:
    if (cond(r, CC_E) && !r->port->env.failed)
    {
        goto at_479be5;
    }
    r->ebp = rd32(r, r->esp + 0x8);
    r->edx = 0;
at_479c21:
    r->eax = 0;
    r->ecx = (uint32_t)(int32_t)(int16_t)(r->ebx & 0xffff);
    set_low16(&r->eax, (r->edx & 0xffff));
    if ((int32_t)r->eax < (int32_t)r->ecx)
    {
        goto at_479c46;
    }
    r->ebp = rd32(r, r->esp + 0x8);
    r->esi = rd32(r, r->esp + 0x14);
    r->ebp = r->ebp - r->ecx;
    r->edi = r->edi + r->ecx;
    wr32(r, r->esp + 0x8, r->ebp);
    set_low16(&r->esi, (r->esi & 0xffff) - 1);
    flags(r, F_DEC, (r->esi & 0xffff), 0, 16);
    wr16(r, r->esp + 0x14, (r->esi & 0xffff));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_479c19;
at_479c46:
    r->esi = r->edi + r->eax;
    r->eax = r->eax + r->ebp;
    set_high8(&r->ecx, rd8(r, r->esi));
    set_low8(&r->ecx, rd8(r, r->eax));
    wr8(r, r->esi, (r->ecx & 0xff));
    r->edx = r->edx + 1;
    wr8(r, r->eax, ((r->ecx >> 8) & 0xff));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_479c21;
at_479c56:
    r->ecx = rd32(r, r->esp + 0x10);
    r->edx = r->edx + r->edx;
    r->esi = rd32(r, r->esp + 0x4);
    r->ecx = r->ecx + r->edx;
    r->edx = r->edx + r->esi;
    set_low16(&r->esi, rd16(r, r->edx));
    set_low16(&r->edi, rd16(r, r->ecx));
    wr16(r, r->ecx, (r->esi & 0xffff));
    r->eax = r->eax + 1;
    wr16(r, r->edx, (r->edi & 0xffff));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_479bb2;
at_479c76:
    if ((uint8_t)((r->edx & 0xff)) != (uint8_t)0x3)
    {
        goto at_479ce9;
    }
    r->ebx = r->ebx * 0x3;
    r->edx = rd32(r, r->esp + 0x12);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->edi = rd32(r, r->eax);
    r->eax = r->edx - 0x1;
    r->ecx = (uint32_t)(int32_t)(int16_t)(r->ebx & 0xffff);
    r->eax = r->eax * r->ecx;
    r->ecx = r->edi + r->eax;
    r->eax = r->edx;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    r->eax = r->eax - r->edx;
    r->eax = (uint32_t)((int32_t)r->eax >> 0x1);
    wr32(r, r->esp + 0xc, r->ecx);
    wr16(r, r->esp + 0x14, (r->eax & 0xffff));
    flags(r, F_LOGIC, (r->eax & 0xffff), 0, 16);
at_479ca8:
    if (cond(r, CC_E) && !r->port->env.failed)
    {
        goto at_479be5;
    }
    r->ebp = rd32(r, r->esp + 0xc);
    r->edx = 0;
at_479cb4:
    r->eax = 0;
    r->ecx = (uint32_t)(int32_t)(int16_t)(r->ebx & 0xffff);
    set_low16(&r->eax, (r->edx & 0xffff));
    if ((int32_t)r->eax < (int32_t)r->ecx)
    {
        goto at_479cd9;
    }
    r->ebp = rd32(r, r->esp + 0xc);
    r->esi = rd32(r, r->esp + 0x14);
    r->ebp = r->ebp - r->ecx;
    r->edi = r->edi + r->ecx;
    wr32(r, r->esp + 0xc, r->ebp);
    set_low16(&r->esi, (r->esi & 0xffff) - 1);
    flags(r, F_DEC, (r->esi & 0xffff), 0, 16);
    wr16(r, r->esp + 0x14, (r->esi & 0xffff));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_479ca8;
at_479cd9:
    r->esi = r->edi + r->eax;
    r->eax = r->eax + r->ebp;
    set_low8(&r->ecx, rd8(r, r->esi));
    set_high8(&r->ecx, rd8(r, r->eax));
    wr8(r, r->esi, ((r->ecx >> 8) & 0xff));
    r->edx = r->edx + 1;
    wr8(r, r->eax, (r->ecx & 0xff));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_479cb4;
at_479ce9:
    if ((uint8_t)((r->edx & 0xff)) != (uint8_t)0x4 && !r->port->env.failed)
    {
        goto at_479be5;
    }
    r->edx = rd32(r, r->esp + 0x12);
    r->ebp = rd32(r, r->eax);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)(int32_t)(int16_t)(r->ebx & 0xffff);
    r->ecx = r->edx - 0x1;
    r->eax = r->eax * r->ecx;
    r->eax = r->eax << 0x2;
    r->ecx = r->eax + r->ebp;
    r->eax = r->edx;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    r->eax = r->eax - r->edx;
    r->eax = (uint32_t)((int32_t)r->eax >> 0x1);
    wr32(r, r->esp, r->ecx);
    wr16(r, r->esp + 0x14, (r->eax & 0xffff));
    flags(r, F_LOGIC, (r->eax & 0xffff), 0, 16);
at_479d1e:
    if (cond(r, CC_E) && !r->port->env.failed)
    {
        goto at_479be5;
    }
    r->eax = 0;
at_479d26:
    r->edx = 0;
    r->ecx = (uint32_t)(int32_t)(int16_t)(r->ebx & 0xffff);
    set_low16(&r->edx, (r->eax & 0xffff));
    if ((int32_t)r->edx < (int32_t)r->ecx)
    {
        goto at_479d4c;
    }
    r->edx = rd32(r, r->esp);
    r->ecx = r->ecx << 0x2;
    r->edx = r->edx - r->ecx;
    wr32(r, r->esp, r->edx);
    r->edx = rd32(r, r->esp + 0x14);
    r->ebp = r->ebp + r->ecx;
    set_low16(&r->edx, (r->edx & 0xffff) - 1);
    flags(r, F_DEC, (r->edx & 0xffff), 0, 16);
    wr16(r, r->esp + 0x14, (r->edx & 0xffff));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_479d1e;
at_479d4c:
    r->ecx = r->edx * 4;
    r->esi = rd32(r, r->esp);
    r->edx = r->ecx + r->ebp;
    r->ecx = r->ecx + r->esi;
    r->esi = rd32(r, r->ecx);
    r->edi = rd32(r, r->edx);
    wr32(r, r->edx, r->esi);
    r->eax = r->eax + 1;
    wr32(r, r->ecx, r->edi);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_479d26;
}

uint32_t vertrix_port_surface_flip_vertical_479b50(PORT_SIGNATURE)
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
