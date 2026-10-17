#include "port_rtlpatterntables.h"

/* Reads the pattern tables from the game data into newly allocated memory. */

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

/* Original 0x441f20: Reads the pattern tables from the game data into newly allocated memory.
 * Evidence: calls 0x478f10, 0x4ec160; reads 0x5440f6, 0x5440f7; writes 0x5440f6, 0x5440f7.
 * Register-for-register from the listing (0x441f2b..0x4420fd); labels are the original addresses.
 */
static void run(Regs *r)
{
    r->edi = r->eax;
    r->ecx = 0x1;
    r->edx = 0;
    set_high8(&r->eax, 0);
    r->ebx = 0;
    wr32(r, r->ebp - 0x44, r->edx);
    wr32(r, r->ebp - 0x34, r->ecx);
    wr8(r, r->ebp - 0x1c, ((r->eax >> 8) & 0xff));
    wr32(r, r->ebp - 0x24, r->ebx);
    r->ebx = 0xb;
    r->edx = 0;
    r->eax = rd32(r, r->edi + 0x4);
    wr32(r, r->ebp - 0x28, r->edx);
    set_low8(&r->edx, 0);
    wr32(r, r->ebp - 0x38, r->eax);
    wr8(r, 0x5440f6, (r->edx & 0xff));
    set_high8(&r->edx, 0x4);
    wr32(r, r->ebp - 0x3c, r->ebx);
    wr8(r, 0x5440f7, ((r->edx >> 8) & 0xff));
at_441f67:
    r->eax = 0;
    set_low16(&r->eax, rd16(r, r->ebp - 0x24));
    if ((int32_t)r->eax < (int32_t)0x6)
    {
        goto at_441ff4;
    }
    r->esi = 0;
at_441f78:
    r->eax = 0;
    set_low16(&r->eax, (r->esi & 0xffff));
    if ((int32_t)r->eax >= (int32_t)0x100)
    {
        goto at_441eea;
    }
    r->eax = 0;
at_441f8a:
    r->ecx = 0;
    r->edx = 0;
    set_low16(&r->ecx, (r->esi & 0xffff));
    set_low8(&r->edx, rd8(r, r->eax + 0x4fba48));
    if (r->edx == r->ecx)
    {
        goto at_441fa1;
    }
    r->eax = r->eax + 1;
    if (r->eax < 0x73 && !r->port->env.failed)
    {
        goto at_441f8a;
    }
at_441fa1:
    if (r->eax == 0x73)
    {
        goto at_4420f8;
    }
at_441faa:
    r->edx = 0;
    r->ecx = rd32(r, r->eax * 4 + 0x54414c);
    set_low16(&r->edx, (r->esi & 0xffff));
    set_low8(&r->eax, rd8(r, r->eax + 0x544318));
    r->esi = r->esi + 1;
    wr32(r, r->edx * 4 + 0x54438c, r->ecx);
    wr8(r, r->edx + 0x544790, (r->eax & 0xff));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_441f78;
at_441fcc:
    r->edx = rd32(r, r->ebp - 0x3c);
    r->ecx = rd32(r, r->ebp - 0x34);
    set_low8(&r->ebx, 0);
    r->eax = 0;
    wr8(r, r->ebp - 0x1c, (r->ebx & 0xff));
    r->ecx = r->ecx + 0xb;
    wr32(r, r->ebp - 0x44, r->eax);
    wr32(r, r->ebp - 0x34, r->ecx);
    r->ecx = rd32(r, r->ebp - 0x24);
    r->edx = r->edx + 0xb;
    r->ecx = r->ecx + 1;
    wr32(r, r->ebp - 0x3c, r->edx);
    wr32(r, r->ebp - 0x24, r->ecx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_441f67;
at_441ff4:
    r->eax = rd32(r, r->ebp - 0x3c);
    wr32(r, r->ebp - 0x40, r->eax);
at_441ffa:
    r->eax = rd32(r, r->ebp - 0x44);
    if (r->eax >= rd32(r, r->ebp - 0x38) && !r->port->env.failed)
    {
        goto at_441fcc;
    }
    r->ecx = rd32(r, r->ebp - 0x34);
    r->esi = 0;
at_442007:
    r->edx = rd32(r, r->ebp - 0x44);
    r->ebx = r->ecx;
    r->eax = r->edi;
    call_keep(r, 0x478f10);
    if (r->eax != 0)
    {
        goto at_442020;
    }
    r->ebx = rd32(r, r->ebp - 0x40);
    r->ecx = r->ecx + 1;
    r->esi = r->esi + 1;
    if (r->ecx < r->ebx && !r->port->env.failed)
    {
        goto at_442007;
    }
at_442020:
    if (r->esi != 0xa)
    {
        goto at_4420da;
    }
    if ((uint8_t)rd8(r, r->ebp - 0x1c) == (uint8_t)0x1)
    {
        goto at_442034;
    }
at_44202f:
    wr32(r, r->ebp - 0x44, rd32(r, r->ebp - 0x44) + 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_441ffa;
at_442034:
    set_low8(&r->eax, rd8(r, r->ebp - 0x44));
    set_low8(&r->eax, (r->eax & 0xff) - rd8(r, r->ebp - 0x20));
    set_low8(&r->edx, rd8(r, 0x5440f6));
    wr8(r, r->ebp - 0x18, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) <= (uint8_t)((r->edx & 0xff)))
    {
        goto at_44204c;
    }
    wr8(r, 0x5440f6, (r->eax & 0xff));
at_44204c:
    set_low8(&r->eax, rd8(r, r->ebp - 0x18));
    if ((uint8_t)((r->eax & 0xff)) < (uint8_t)rd8(r, 0x5440f7))
    {
        goto at_4420b1;
    }
at_442057:
    r->ecx = 0;
    set_low16(&r->ecx, rd16(r, r->ebp - 0x28));
    set_low8(&r->eax, rd8(r, r->ebp - 0x18));
    wr8(r, r->ecx + 0x544318, (r->eax & 0xff));
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ebp - 0x18));
    r->eax = r->eax * 0xa;
    r->edx = 0x1;
    call_keep(r, 0x4ec160);
    r->esi = r->eax;
    wr32(r, r->ecx * 4 + 0x54414c, r->eax);
    r->eax = rd32(r, r->ebp - 0x34);
    wr32(r, r->ebp - 0x2c, r->eax);
at_442087:
    r->eax = rd32(r, r->ebp - 0x2c);
    r->ecx = 0;
    wr32(r, r->ebp - 0x30, r->eax);
at_44208f:
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ebp - 0x18));
    if (r->ecx >= r->eax)
    {
        goto at_4420b8;
    }
    r->edx = 0;
    r->ebx = rd32(r, r->ebp - 0x30);
    set_low16(&r->edx, rd16(r, r->ebp - 0x20));
    r->eax = r->edi;
    r->edx = r->edx + r->ecx;
    r->esi = r->esi + 1;
    call_keep(r, 0x478f10);
    r->ecx = r->ecx + 1;
    wr8(r, r->esi - 0x1, (r->eax & 0xff));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_44208f;
at_4420b1:
    wr8(r, 0x5440f7, (r->eax & 0xff));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_442057;
at_4420b8:
    r->eax = rd32(r, r->ebp - 0x2c);
    r->eax = r->eax + 1;
    r->edx = rd32(r, r->ebp - 0x40);
    wr32(r, r->ebp - 0x2c, r->eax);
    if (r->eax != r->edx && !r->port->env.failed)
    {
        goto at_442087;
    }
    r->esi = rd32(r, r->ebp - 0x28);
    set_low8(&r->ebx, 0);
    r->esi = r->esi + 1;
    wr8(r, r->ebp - 0x1c, (r->ebx & 0xff));
    wr32(r, r->ebp - 0x28, r->esi);
    wr32(r, r->ebp - 0x44, rd32(r, r->ebp - 0x44) + 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_441ffa;
at_4420da:
    if ((uint8_t)rd8(r, r->ebp - 0x1c) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_44202f;
    }
    set_low8(&r->ecx, 0x1);
    r->eax = rd32(r, r->ebp - 0x44);
    wr8(r, r->ebp - 0x1c, (r->ecx & 0xff));
    wr16(r, r->ebp - 0x20, (r->eax & 0xffff));
    wr32(r, r->ebp - 0x44, rd32(r, r->ebp - 0x44) + 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_441ffa;
at_4420f8:
    r->eax = 0x53;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_441faa;
at_441eea:
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
}

uint32_t vertrix_port_pattern_tables_441f20(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x48
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
