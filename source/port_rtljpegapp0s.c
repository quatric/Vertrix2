#include "port_rtljpegapp0s.h"

/* libjpeg examine_app0: recognises a JFIF APP0 header and stores its version, density unit and
 * densities. */

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

/* Original 0x4bef10: libjpeg examine_app0: recognises a JFIF APP0 header and stores its version,
 * density unit and densities. Evidence: no calls. Register-for-register from the listing
 * (0x4bef10..0x4bf18b); labels are the original addresses. */
static void run(Regs *r)
{
    push_mem(r, r->esi);
    push_mem(r, r->edi);
    r->esi = r->eax;
    r->edi = r->edx;
    r->ecx = r->ecx + r->ebx;
    if (r->ebx < 0xe)
    {
        goto at_4bf09f;
    }
    if ((uint8_t)rd8(r, r->edx) != (uint8_t)0x4a)
    {
        goto at_4bf09f;
    }
    set_low8(&r->edx, rd8(r, r->edx + 0x1));
    if ((uint8_t)((r->edx & 0xff)) != (uint8_t)0x46)
    {
        goto at_4bf09f;
    }
    if ((uint8_t)rd8(r, r->edi + 0x2) != (uint8_t)0x49)
    {
        goto at_4bf09f;
    }
    if ((uint8_t)((r->edx & 0xff)) != (uint8_t)rd8(r, r->edi + 0x3))
    {
        goto at_4bf09f;
    }
    set_high8(&r->eax, rd8(r, r->edi + 0x4));
    if ((uint8_t)(((r->eax >> 8) & 0xff)) != 0)
    {
        goto at_4bf09f;
    }
    wr32(r, r->esi + 0x118, 0x1);
    set_low8(&r->eax, rd8(r, r->edi + 0x5));
    wr8(r, r->esi + 0x11c, (r->eax & 0xff));
    set_low8(&r->eax, rd8(r, r->edi + 0x6));
    wr8(r, r->esi + 0x11d, (r->eax & 0xff));
    set_low8(&r->eax, rd8(r, r->edi + 0x7));
    wr8(r, r->esi + 0x11e, (r->eax & 0xff));
    set_low8(&r->eax, rd8(r, r->edi + 0x8));
    r->ebx = r->eax;
    r->ebx = r->ebx << 0x8;
    set_low8(&r->eax, rd8(r, r->edi + 0x9));
    r->ebx = r->ebx + r->eax;
    wr16(r, r->esi + 0x120, (r->ebx & 0xffff));
    set_low8(&r->eax, rd8(r, r->edi + 0xa));
    r->ebx = r->eax;
    r->ebx = r->ebx << 0x8;
    set_low8(&r->eax, rd8(r, r->edi + 0xb));
    r->ebx = r->ebx + r->eax;
    set_high8(&r->eax, rd8(r, r->esi + 0x11c));
    wr16(r, r->esi + 0x122, (r->ebx & 0xffff));
    if ((uint8_t)(((r->eax >> 8) & 0xff)) == (uint8_t)0x1)
    {
        goto at_4befdb;
    }
    r->eax = rd32(r, r->esi);
    wr32(r, r->eax + 0x14, 0x77);
    r->eax = 0;
    r->ebx = rd32(r, r->esi);
    set_low8(&r->eax, rd8(r, r->esi + 0x11c));
    wr32(r, r->ebx + 0x18, r->eax);
    r->eax = 0;
    r->ebx = rd32(r, r->esi);
    set_low8(&r->eax, rd8(r, r->esi + 0x11d));
    wr32(r, r->ebx + 0x1c, r->eax);
    r->ebx = rd32(r, r->esi);
    r->edx = 0xffffffffu;
    r->eax = r->esi;
    call_mem(r, rd32(r, r->ebx + 0x4), 2);
at_4befdb:
    r->ebx = 0;
    r->eax = rd32(r, r->esi);
    set_low8(&r->ebx, rd8(r, r->esi + 0x11c));
    wr32(r, r->eax + 0x18, r->ebx);
    r->ebx = 0;
    set_low8(&r->ebx, rd8(r, r->esi + 0x11d));
    wr32(r, r->eax + 0x1c, r->ebx);
    r->ebx = 0;
    set_low16(&r->ebx, rd16(r, r->esi + 0x120));
    wr32(r, r->eax + 0x20, r->ebx);
    r->ebx = 0;
    set_low16(&r->ebx, rd16(r, r->esi + 0x122));
    wr32(r, r->eax + 0x24, r->ebx);
    r->ebx = 0;
    set_low8(&r->ebx, rd8(r, r->esi + 0x11e));
    wr32(r, r->eax + 0x28, r->ebx);
    r->eax = rd32(r, r->esi);
    wr32(r, r->eax + 0x14, 0x57);
    r->ebx = rd32(r, r->esi);
    r->edx = 0x1;
    r->eax = r->esi;
    call_mem(r, rd32(r, r->ebx + 0x4), 0);
    r->ebx = 0;
    r->eax = 0;
    set_low8(&r->ebx, rd8(r, r->edi + 0xc));
    set_low8(&r->eax, rd8(r, r->edi + 0xd));
    r->eax = r->eax | r->ebx;
    if (r->eax == 0)
    {
        goto at_4bf062;
    }
    r->eax = rd32(r, r->esi);
    wr32(r, r->eax + 0x14, 0x5a);
    r->ebx = 0;
    r->eax = rd32(r, r->esi);
    set_low8(&r->ebx, rd8(r, r->edi + 0xc));
    wr32(r, r->eax + 0x18, r->ebx);
    r->eax = 0;
    r->ebx = rd32(r, r->esi);
    set_low8(&r->eax, rd8(r, r->edi + 0xd));
    wr32(r, r->ebx + 0x1c, r->eax);
    r->ebx = rd32(r, r->esi);
    r->edx = 0x1;
    r->eax = r->esi;
    call_mem(r, rd32(r, r->ebx + 0x4), 0);
at_4bf062:
    r->ebx = 0;
    r->eax = 0;
    set_low8(&r->ebx, rd8(r, r->edi + 0xc));
    set_low8(&r->eax, rd8(r, r->edi + 0xd));
    r->ebx = r->ebx * r->eax;
    r->eax = r->ebx * 4;
    r->ecx = r->ecx - 0xe;
    r->eax = r->eax - r->ebx;
    if (r->ecx != r->eax)
    {
        goto at_4bf082;
    }
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_4bf082:
    r->eax = rd32(r, r->esi);
    wr32(r, r->eax + 0x14, 0x58);
    r->eax = rd32(r, r->esi);
    wr32(r, r->eax + 0x18, r->ecx);
    r->ecx = rd32(r, r->esi);
    r->edx = 0x1;
    r->eax = r->esi;
    call_mem(r, rd32(r, r->ecx + 0x4), 0);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_4bf09f:
    if (r->ebx < 0x6)
    {
        goto at_4bf16f;
    }
    if ((uint8_t)rd8(r, r->edi) != (uint8_t)0x4a)
    {
        goto at_4bf16f;
    }
    if ((uint8_t)rd8(r, r->edi + 0x1) != (uint8_t)0x46)
    {
        goto at_4bf16f;
    }
    set_low8(&r->ebx, rd8(r, r->edi + 0x2));
    if ((uint8_t)((r->ebx & 0xff)) != (uint8_t)0x58)
    {
        goto at_4bf16f;
    }
    if ((uint8_t)((r->ebx & 0xff)) != (uint8_t)rd8(r, r->edi + 0x3))
    {
        goto at_4bf16f;
    }
    if ((uint8_t)rd8(r, r->edi + 0x4) != (uint8_t)0x0)
    {
        goto at_4bf16f;
    }
    set_low8(&r->eax, rd8(r, r->edi + 0x5));
    flags(r, F_SUB, (r->eax & 0xff), 0x11, 8);
    if (cond(r, CC_AE))
    {
        goto at_4bf167;
    }
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x10)
    {
        goto at_4bf140;
    }
    r->eax = rd32(r, r->esi);
    wr32(r, r->eax + 0x14, 0x6c);
    r->eax = rd32(r, r->esi);
    wr32(r, r->eax + 0x18, r->ecx);
    r->ecx = rd32(r, r->esi);
    r->edx = 0x1;
    r->eax = r->esi;
    call_mem(r, rd32(r, r->ecx + 0x4), 0);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_4bf106:
    r->eax = rd32(r, r->esi);
    wr32(r, r->eax + 0x14, 0x6d);
    r->eax = rd32(r, r->esi);
    wr32(r, r->eax + 0x18, r->ecx);
    r->ecx = rd32(r, r->esi);
    r->edx = 0x1;
    r->eax = r->esi;
    call_mem(r, rd32(r, r->ecx + 0x4), 0);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_4bf123:
    r->eax = rd32(r, r->esi);
    wr32(r, r->eax + 0x14, 0x6e);
    r->eax = rd32(r, r->esi);
    wr32(r, r->eax + 0x18, r->ecx);
    r->ecx = rd32(r, r->esi);
    r->edx = 0x1;
    r->eax = r->esi;
    call_mem(r, rd32(r, r->ecx + 0x4), 0);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_4bf140:
    r->eax = rd32(r, r->esi);
    wr32(r, r->eax + 0x14, 0x59);
    r->eax = 0;
    r->ebx = rd32(r, r->esi);
    set_low8(&r->eax, rd8(r, r->edi + 0x5));
    wr32(r, r->ebx + 0x18, r->eax);
    r->eax = rd32(r, r->esi);
    wr32(r, r->eax + 0x1c, r->ecx);
    r->ecx = rd32(r, r->esi);
    r->edx = 0x1;
    r->eax = r->esi;
    call_mem(r, rd32(r, r->ecx + 0x4), 0);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_4bf167:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4bf106;
    }
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x13 && !r->port->env.failed)
    {
        goto at_4bf123;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bf140;
at_4bf16f:
    r->eax = rd32(r, r->esi);
    wr32(r, r->eax + 0x14, 0x4d);
    r->eax = rd32(r, r->esi);
    wr32(r, r->eax + 0x18, r->ecx);
    r->ecx = rd32(r, r->esi);
    r->edx = 0x1;
    r->eax = r->esi;
    call_mem(r, rd32(r, r->ecx + 0x4), 0);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
}

uint32_t vertrix_port_jpeg_examine_app0_4bef10(PORT_SIGNATURE)
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
