#include "port_rtlfixedtexts.h"

/* Formats a 16.16 fixed-point value (edx) as decimal text at eax: a minus sign, the integer part,
 * then [ebx+8] fraction digits (4 when -1), rounding the last digit up with carry. */

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

/* Original 0x4df978: Formats a 16.16 fixed-point value (edx) as decimal text at eax: a minus sign,
 * the integer part, then [ebx+8] fraction digits (4 when -1), rounding the last digit up with
 * carry. Evidence: calls 0x4e636c. Register-for-register from the listing (0x4df978..0x4dfa6f);
 * labels are the original addresses. */
static void run(Regs *r)
{
    push_mem(r, r->ecx);
    push_mem(r, r->esi);
    push_mem(r, r->edi);
    push_mem(r, r->ebp);
    r->esp = r->esp - 0x4;
    r->ecx = r->eax;
    r->esi = r->ebx;
    wr32(r, r->esp, r->edx);
    if ((int32_t)r->edx >= 0)
    {
        goto at_4df995;
    }
    r->edx = 0u - r->edx;
    r->ecx = r->eax + 0x1;
    wr8(r, r->eax, 0x2d);
    wr32(r, r->esp, r->edx);
at_4df995:
    if (rd32(r, r->esi + 0x8) != 0xffffffffu)
    {
        goto at_4df9a2;
    }
    wr32(r, r->esi + 0x8, 0x4);
at_4df9a2:
    r->ebx = 0xa;
    r->eax = 0;
    r->edx = r->ecx;
    set_low16(&r->eax, rd16(r, r->esp + 0x2));
    call_mem_keep(r, 0x4e636c, 8);
    set_high8(&r->eax, rd8(r, r->ecx));
    r->ebx = r->ecx;
    if ((uint8_t)(((r->eax >> 8) & 0xff)) == 0)
    {
        goto at_4df9c5;
    }
at_4df9bd:
    set_low8(&r->edx, rd8(r, r->ecx + 0x1));
    r->ecx = r->ecx + 1;
    if ((uint8_t)((r->edx & 0xff)) != 0 && !r->port->env.failed)
    {
        goto at_4df9bd;
    }
at_4df9c5:
    if (rd32(r, r->esi + 0x8) == 0x0)
    {
        goto at_4df9fd;
    }
    wr8(r, r->ecx, 0x2e);
    r->eax = 0;
    r->ebp = rd32(r, r->esi + 0x8);
    r->ecx = r->ecx + 1;
    if ((int32_t)r->ebp <= 0)
    {
        goto at_4df9fa;
    }
at_4df9d8:
    r->edx = 0;
    wr16(r, r->esp + 0x2, (r->edx & 0xffff));
    r->edi = rd32(r, r->esp);
    r->edx = r->edi * 0xa;
    wr32(r, r->esp, r->edx);
    set_low8(&r->edx, rd8(r, r->esp + 0x2));
    set_low8(&r->edx, (r->edx & 0xff) + 0x30);
    wr8(r, r->ecx, (r->edx & 0xff));
    r->eax = r->eax + 1;
    r->ebp = rd32(r, r->esi + 0x8);
    r->ecx = r->ecx + 1;
    if ((int32_t)r->eax < (int32_t)r->ebp && !r->port->env.failed)
    {
        goto at_4df9d8;
    }
at_4df9fa:
    wr8(r, r->ecx, 0x0);
at_4df9fd:
    if ((uint8_t)(rd8(r, r->esp + 0x1) & 0x80) == 0)
    {
        goto at_4df96e;
    }
at_4dfa08:
    if (r->ecx != r->ebx)
    {
        goto at_4dfa4d;
    }
    r->ecx = r->ebx + 0x1;
    wr8(r, r->ebx, 0x31);
    if ((uint8_t)rd8(r, r->ecx) != (uint8_t)0x30)
    {
        goto at_4dfa1f;
    }
at_4dfa17:
    set_low8(&r->eax, rd8(r, r->ecx + 0x1));
    r->ecx = r->ecx + 1;
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x30 && !r->port->env.failed)
    {
        goto at_4dfa17;
    }
at_4dfa1f:
    set_high8(&r->eax, rd8(r, r->ecx));
    if ((uint8_t)(((r->eax >> 8) & 0xff)) != (uint8_t)0x2e)
    {
        goto at_4dfa3e;
    }
    wr8(r, r->ecx, 0x30);
    r->ecx = r->ecx + 1;
    wr8(r, r->ecx, ((r->eax >> 8) & 0xff));
    set_low8(&r->edx, rd8(r, r->ecx + 0x1));
    r->ecx = r->ecx + 1;
    if ((uint8_t)((r->edx & 0xff)) != (uint8_t)0x30)
    {
        goto at_4dfa3e;
    }
at_4dfa35:
    set_high8(&r->edx, rd8(r, r->ecx + 0x1));
    r->ecx = r->ecx + 1;
    if ((uint8_t)(((r->edx >> 8) & 0xff)) == (uint8_t)0x30 && !r->port->env.failed)
    {
        goto at_4dfa35;
    }
at_4dfa3e:
    wr8(r, r->ecx, 0x30);
    r->ecx = r->ecx + 1;
    wr8(r, r->ecx, 0x0);
    r->esp = r->esp + 0x4;
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    return;
at_4dfa4d:
    set_low8(&r->edx, rd8(r, r->ecx - 0x1));
    r->ecx = r->ecx - 1;
    if ((uint8_t)((r->edx & 0xff)) != (uint8_t)0x2e)
    {
        goto at_4dfa57;
    }
    r->ecx = r->ecx - 1;
at_4dfa57:
    set_high8(&r->edx, rd8(r, r->ecx));
    if ((uint8_t)(((r->edx >> 8) & 0xff)) == (uint8_t)0x39)
    {
        goto at_4dfa6c;
    }
    set_low8(&r->ebx, ((r->edx >> 8) & 0xff));
    set_low8(&r->ebx, (r->ebx & 0xff) + 1);
    wr8(r, r->ecx, (r->ebx & 0xff));
    r->esp = r->esp + 0x4;
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    return;
at_4dfa6c:
    wr8(r, r->ecx, 0x30);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4dfa08;
at_4df96e:
    r->esp = r->esp + 0x4;
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    return;
}

uint32_t vertrix_port_rtl_format_fixed_point_4df978(PORT_SIGNATURE)
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
