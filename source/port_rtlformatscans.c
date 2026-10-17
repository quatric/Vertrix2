#include "port_rtlformatscans.h"

/* Scans a format string for the printf core, handling flags (+0x10) and literal text. */

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

static void set_high8(uint32_t *reg, uint32_t value)
{
    *reg = (*reg & 0xffff00ffu) | ((value & 0xff) << 8);
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

static void call_mem_keep(Regs *r, uint32_t target, unsigned count)
{
    call_mem_with(r, target, count, 1);
}

/* Original 0x4e4110: Scans a format string for the printf core, handling flags (+0x10) and literal
 * text. Evidence: calls 0x4e44c8, 0x4e4100, 0x4e4108, 0x4e43c4, 0x4e4bb0, 0x4e48d8, 0x4e45f0,
 * 0x4e47ec, 0x4e4508, 0x4e4748. Register-for-register from the listing (0x4e4110..0x4e43c2); labels
 * are the original addresses. */
static void run(Regs *r)
{
    push_mem(r, r->ecx);
    push_mem(r, r->esi);
    push_mem(r, r->edi);
    push_mem(r, r->ebp);
    r->esp = r->esp - 0x8;
    r->esi = r->eax;
    wr32(r, r->esp, r->edx);
    r->eax = rd32(r, r->ebx);
    wr32(r, r->esp + 0x4, r->eax);
    set_high8(&r->eax, rd8(r, r->esi + 0x10));
    r->ebp = 0;
    set_high8(&r->eax, ((r->eax >> 8) & 0xff) & 0xfd);
    r->edi = 0;
    wr8(r, r->esi + 0x10, ((r->eax >> 8) & 0xff));
at_4e412f:
    r->ebx = rd32(r, r->esp);
    r->edx = r->ebx + 0x1;
    wr32(r, r->esp, r->edx);
    set_low8(&r->ebx, rd8(r, r->ebx));
    r->ebx = r->ebx & 0xff;
    if (r->ebx == 0)
    {
        goto at_4e43a8;
    }
    set_low8(&r->eax, (r->ebx & 0xff));
    set_low8(&r->eax, (r->eax & 0xff) + 1);
    r->eax = r->eax & 0xff;
    if ((uint8_t)(rd8(r, r->eax + 0x507d58) & 0x2) == 0)
    {
        goto at_4e4166;
    }
    r->eax = r->esi;
    call_mem_keep(r, 0x4e44c8, 8);
    r->edi = r->edi + r->eax;
    goto at_4e4372;
at_4e4166:
    if (r->ebx == 0x25)
    {
        goto at_4e4190;
    }
    r->eax = r->esi;
    call_mem_keep(r, 0x4e4100, 8);
    if (r->eax == r->ebx)
    {
        goto at_4e4371;
    }
    if ((uint8_t)(rd8(r, r->esi + 0x10) & 0x2) != 0)
    {
        goto at_4e43a8;
    }
    r->edx = r->esi;
    call_mem_keep(r, 0x4e4108, 8);
    goto at_4e43a8;
at_4e4190:
    r->eax = rd32(r, r->esp);
    r->edx = r->esi;
    call_mem_keep(r, 0x4e43c4, 8);
    r->ebx = 0;
    wr32(r, r->esp, r->eax);
    set_low8(&r->ebx, rd8(r, r->eax));
    if (r->ebx == 0)
    {
        goto at_4e41a9;
    }
    r->eax = r->eax + 1;
    wr32(r, r->esp, r->eax);
at_4e41a9:
    flags(r, F_SUB, r->ebx, 0x64, 32);
    if (cond(r, CC_B))
    {
        goto at_4e421c;
    }
    if (cond(r, CC_BE))
    {
        goto at_4e4284;
    }
    flags(r, F_SUB, r->ebx, 0x6f, 32);
    if (cond(r, CC_B))
    {
        goto at_4e41f5;
    }
    if (cond(r, CC_BE))
    {
        goto at_4e42b5;
    }
    flags(r, F_SUB, r->ebx, 0x73, 32);
    if (cond(r, CC_B))
    {
        goto at_4e41e7;
    }
    if (cond(r, CC_BE))
    {
        goto at_4e4308;
    }
    flags(r, F_SUB, r->ebx, 0x75, 32);
    if (cond(r, CC_B))
    {
        goto at_4e4372;
    }
    if (cond(r, CC_BE))
    {
        goto at_4e42cc;
    }
    if (r->ebx == 0x78)
    {
        goto at_4e42e0;
    }
    goto at_4e4372;
at_4e41e7:
    if (r->ebx == 0x70)
    {
        goto at_4e42e0;
    }
    goto at_4e4372;
at_4e41f5:
    flags(r, F_SUB, r->ebx, 0x69, 32);
    if (cond(r, CC_B))
    {
        goto at_4e420e;
    }
    if (cond(r, CC_BE))
    {
        goto at_4e429e;
    }
    if (r->ebx == 0x6e)
    {
        goto at_4e4348;
    }
    goto at_4e4372;
at_4e420e:
    if (r->ebx <= 0x67)
    {
        goto at_4e42f7;
    }
    goto at_4e4372;
at_4e421c:
    flags(r, F_SUB, r->ebx, 0x47, 32);
    if (cond(r, CC_B))
    {
        goto at_4e425d;
    }
    if (cond(r, CC_BE))
    {
        goto at_4e42f7;
    }
    flags(r, F_SUB, r->ebx, 0x58, 32);
    if (cond(r, CC_B))
    {
        goto at_4e424f;
    }
    if (cond(r, CC_BE))
    {
        goto at_4e42e0;
    }
    flags(r, F_SUB, r->ebx, 0x5b, 32);
    if (cond(r, CC_B))
    {
        goto at_4e4372;
    }
    if (cond(r, CC_BE))
    {
        goto at_4e4315;
    }
    if (r->ebx == 0x63)
    {
        goto at_4e4328;
    }
    goto at_4e4372;
at_4e424f:
    if (r->ebx == 0x53)
    {
        goto at_4e4304;
    }
    goto at_4e4372;
at_4e425d:
    flags(r, F_SUB, r->ebx, 0x43, 32);
    if (cond(r, CC_B))
    {
        goto at_4e4276;
    }
    if (cond(r, CC_BE))
    {
        goto at_4e4324;
    }
    if (r->ebx == 0x45)
    {
        goto at_4e42f7;
    }
    goto at_4e4372;
at_4e4276:
    if (r->ebx == 0x25)
    {
        goto at_4e4357;
    }
    goto at_4e4372;
at_4e4284:
    r->ecx = 0x1;
    r->ebx = 0xa;
    r->edx = r->esp + 0x4;
    r->eax = r->esi;
    call_mem_keep(r, 0x4e4bb0, 8);
    goto at_4e4333;
at_4e429e:
    r->ecx = 0x1;
    r->edx = r->esp + 0x4;
    r->eax = r->esi;
    r->ebx = 0;
    call_mem_keep(r, 0x4e4bb0, 8);
    goto at_4e4333;
at_4e42b5:
    r->ecx = 0x1;
    r->ebx = 0x8;
    r->edx = r->esp + 0x4;
    r->eax = r->esi;
    call_mem_keep(r, 0x4e4bb0, 8);
    goto at_4e4333;
at_4e42cc:
    r->ebx = 0xa;
    r->edx = r->esp + 0x4;
    r->eax = r->esi;
    r->ecx = 0;
    call_mem_keep(r, 0x4e4bb0, 8);
    goto at_4e4333;
at_4e42e0:
    r->ecx = 0x1;
    r->ebx = 0x10;
    r->edx = r->esp + 0x4;
    r->eax = r->esi;
    call_mem_keep(r, 0x4e4bb0, 8);
    goto at_4e4333;
at_4e42f7:
    r->edx = r->esp + 0x4;
    r->eax = r->esi;
    call_mem_keep(r, 0x4e48d8, 8);
    goto at_4e4333;
at_4e4304:
    wr8(r, r->esi + 0x10, rd8(r, r->esi + 0x10) | 0x20);
at_4e4308:
    r->edx = r->esp + 0x4;
    r->eax = r->esi;
    call_mem_keep(r, 0x4e45f0, 8);
    goto at_4e4333;
at_4e4315:
    r->ebx = r->esp;
    r->edx = r->esp + 0x4;
    r->eax = r->esi;
    call_mem_keep(r, 0x4e47ec, 8);
    goto at_4e4333;
at_4e4324:
    wr8(r, r->esi + 0x10, rd8(r, r->esi + 0x10) | 0x20);
at_4e4328:
    r->edx = r->esp + 0x4;
    r->eax = r->esi;
    call_mem_keep(r, 0x4e4508, 8);
at_4e4333:
    r->ebx = r->eax;
    if ((int32_t)r->ebx <= 0)
    {
        goto at_4e43a8;
    }
    r->edi = r->edi + r->ebx;
    if ((uint8_t)(rd8(r, r->esi + 0x10) & 0x1) == 0)
    {
        goto at_4e4372;
    }
    r->ebp = r->ebp + 1;
    goto at_4e4372;
at_4e4348:
    r->edx = r->esp + 0x4;
    r->ebx = r->edi;
    r->eax = r->esi;
    call_mem_keep(r, 0x4e4748, 8);
    goto at_4e4372;
at_4e4357:
    r->eax = r->esi;
    call_mem_keep(r, 0x4e4100, 8);
    if (r->eax == r->ebx)
    {
        goto at_4e4371;
    }
    if ((uint8_t)(rd8(r, r->esi + 0x10) & 0x2) != 0)
    {
        goto at_4e43a8;
    }
    r->edx = r->esi;
    call_mem_keep(r, 0x4e4108, 8);
    goto at_4e43a8;
at_4e4371:
    r->edi = r->edi + 1;
at_4e4372:
    if ((uint8_t)(rd8(r, r->esi + 0x10) & 0x2) == 0 && !r->port->env.failed)
    {
        goto at_4e412f;
    }
    r->eax = rd32(r, r->esp);
    if ((uint8_t)rd8(r, r->eax) != (uint8_t)0x25)
    {
        goto at_4e43a8;
    }
    r->ebx = r->eax + 0x1;
    r->edx = r->esi;
    r->eax = r->ebx;
    wr32(r, r->esp, r->ebx);
    call_mem_keep(r, 0x4e43c4, 8);
    wr32(r, r->esp, r->eax);
    if ((uint8_t)rd8(r, r->eax) != (uint8_t)0x6e)
    {
        goto at_4e43a8;
    }
    r->edx = r->esp + 0x4;
    r->ebx = r->edi;
    r->eax = r->esi;
    call_mem_keep(r, 0x4e4748, 8);
at_4e43a8:
    if (r->ebp != 0)
    {
        goto at_4e43b9;
    }
    if ((uint8_t)(rd8(r, r->esi + 0x10) & 0x2) == 0)
    {
        goto at_4e43b9;
    }
    r->eax = 0xffffffffu;
    goto at_4e43bb;
at_4e43b9:
    r->eax = r->ebp;
at_4e43bb:
    r->esp = r->esp + 0x8;
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    return;
}

uint32_t vertrix_port_rtl_format_scan_4e4110(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x30
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
