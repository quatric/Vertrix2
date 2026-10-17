#include "port_rtlmessagequeues.h"

/* Enters the critical section 0x5328f0 and takes the next 4-byte message from the list at +0x200
 * into ebx. */

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

/* Original 0x48be70: Enters the critical section 0x5328f0 and takes the next 4-byte message from
 * the list at +0x200 into ebx. Evidence: calls 0x48d5f0, 0x48d620, 0x48d650, 0x48bdf0, 0x48bb80,
 * 0x482640, 0x47ed30; reads 0x4f1b48, 0x4f1c40, 0x5bb4a0, 0x4f1c7c, 0x5bb47c, 0x4f1ca0, 0x5bb484,
 * 0x5bb48c, 0x5bb494, 0x5bb490; writes 0x532a6c, 0x532a20, 0x532a68, 0x532a70.
 * Register-for-register from the listing (0x48be70..0x48c05c); labels are the original addresses.
 */
static void run(Regs *r)
{
    push_mem(r, r->ebx);
    push_mem(r, r->ecx);
    push_mem(r, r->esi);
    r->esi = r->eax;
    r->ebx = r->edx;
    push_mem(r, 0x5328f0);
    call_mem(r, rd32(r, 0x4f1b48), 4);
    r->ecx = r->esi + 0x200;
    r->eax = r->ecx;
    call_mem_keep(r, 0x48d5f0, 8);
    if (r->eax == 0x1)
    {
        goto at_48bef4;
    }
    r->eax = r->ecx;
    call_mem_keep(r, 0x48d620, 8);
    if (r->eax == 0)
    {
        goto at_48bef4;
    }
    set_low8(&r->edx, rd8(r, r->eax));
    wr8(r, r->ebx, (r->edx & 0xff));
    set_low8(&r->edx, rd8(r, r->eax + 0x1));
    wr8(r, r->ebx + 0x1, (r->edx & 0xff));
    set_low8(&r->edx, rd8(r, r->eax + 0x2));
    wr8(r, r->ebx + 0x2, (r->edx & 0xff));
    set_low8(&r->edx, rd8(r, r->eax + 0x3));
    wr8(r, r->ebx + 0x3, (r->edx & 0xff));
    set_low8(&r->edx, rd8(r, r->eax + 0x4));
    wr8(r, r->ebx + 0x4, (r->edx & 0xff));
    set_low8(&r->edx, rd8(r, r->eax + 0x5));
    wr8(r, r->ebx + 0x5, (r->edx & 0xff));
    set_low8(&r->edx, rd8(r, r->eax + 0x6));
    wr8(r, r->ebx + 0x6, (r->edx & 0xff));
    set_low8(&r->edx, rd8(r, r->eax + 0x7));
    wr8(r, r->ebx + 0x7, (r->edx & 0xff));
    r->edx = rd32(r, r->eax + 0x20);
    wr32(r, r->ebx + 0x20, r->edx);
    r->edx = rd32(r, r->eax + 0x2c);
    wr32(r, r->ebx + 0x2c, r->edx);
    r->edx = rd32(r, r->eax + 0x14);
    wr32(r, r->ebx + 0x14, r->edx);
    r->eax = rd32(r, r->eax + 0x18);
    r->edx = 0;
    wr32(r, r->ebx + 0x18, r->eax);
    r->ebx = 0x1;
    r->eax = r->ecx;
    call_mem_keep(r, 0x48d650, 8);
at_48bef4:
    r->eax = r->esi + 0x200;
    call_mem_keep(r, 0x48d5f0, 8);
    if (r->eax == 0x1)
    {
        goto at_48bf14;
    }
    push_mem(r, 0x5328f0);
    call_mem(r, rd32(r, 0x4f1c40), 1);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_48bf14:
    r->edx = rd32(r, 0x5bb4a0);
    push_mem(r, r->edx);
    call_mem(r, rd32(r, 0x4f1c7c), 1);
    push_mem(r, 0x5328f0);
    call_mem(r, rd32(r, 0x4f1c40), 1);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
    r->eax = 0x5bb254;
    r->edx = rd32(r, r->edx + 0x10);
    call_mem_keep(r, 0x48bdf0, 8);
    r->eax = 0;
    return;
    push_mem(r, r->ebx);
    push_mem(r, r->ecx);
    push_mem(r, r->esi);
    push_mem(r, r->edi);
    r->ecx = r->eax;
    r->eax = r->edx;
    if ((uint8_t)rd8(r, r->edx) == (uint8_t)0x2)
    {
        goto at_48bf96;
    }
    set_high8(&r->edx, rd8(r, r->eax));
    if ((uint8_t)(((r->edx >> 8) & 0xff)) == (uint8_t)0x3)
    {
        goto at_48bfa1;
    }
    if ((uint8_t)(((r->edx >> 8) & 0xff)) == (uint8_t)0x4)
    {
        goto at_48bfb0;
    }
    if ((uint8_t)(((r->edx >> 8) & 0xff)) == (uint8_t)0x5)
    {
        goto at_48bfcd;
    }
    if ((uint8_t)(((r->edx >> 8) & 0xff)) != (uint8_t)0x6)
    {
        goto at_48bff9;
    }
    r->ebx = rd32(r, r->ecx + 0x44);
    set_low8(&r->eax, rd8(r, r->eax + 0x1));
    if (r->ebx != 0x1)
    {
        goto at_48bfe5;
    }
    r->eax = r->eax & 0xff;
    wr32(r, 0x532a6c, r->eax);
at_48bf8c:
    r->eax = 0x1;
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_48bf96:
    r->edx = r->eax;
    r->eax = r->ecx;
    call_mem_keep(r, 0x48bb80, 8);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_48bf8c;
at_48bfa1:
    r->eax = rd32(r, 0x5bb47c);
    push_mem(r, r->eax);
    call_mem(r, rd32(r, 0x4f1ca0), 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_48bf8c;
at_48bfb0:
    r->edx = rd32(r, r->eax + 0x4);
    r->eax = 0x598d30;
    call_mem_keep(r, 0x482640, 8);
    r->edi = rd32(r, 0x5bb484);
    push_mem(r, r->edi);
    call_mem(r, rd32(r, 0x4f1ca0), 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_48bf8c;
at_48bfcd:
    r->esi = rd32(r, 0x5bb48c);
    r->eax = rd32(r, r->eax + 0x4);
    push_mem(r, r->esi);
    wr32(r, 0x532a20, r->eax);
    call_mem(r, rd32(r, 0x4f1ca0), 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_48bf8c;
at_48bfe5:
    r->eax = r->eax & 0xff;
    wr32(r, 0x532a68, r->eax);
    r->eax = 0x1;
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_48bff9:
    if ((uint8_t)(((r->edx >> 8) & 0xff)) == (uint8_t)0x7)
    {
        goto at_48c020;
    }
    if ((uint8_t)(((r->edx >> 8) & 0xff)) == (uint8_t)0x8)
    {
        goto at_48c037;
    }
    if ((uint8_t)(((r->edx >> 8) & 0xff)) != (uint8_t)0x9)
    {
        goto at_48c04f;
    }
    r->edx = rd32(r, 0x5bb494);
    push_mem(r, r->edx);
    call_mem(r, rd32(r, 0x4f1ca0), 1);
    r->eax = 0x1;
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_48c020:
    set_low8(&r->eax, rd8(r, r->eax + 0x1));
    r->eax = r->eax & 0xff;
    wr32(r, 0x532a70, r->eax);
    r->eax = 0x1;
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_48c037:
    r->ecx = rd32(r, 0x5bb490);
    push_mem(r, r->ecx);
    call_mem(r, rd32(r, 0x4f1ca0), 1);
    r->eax = 0x1;
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_48c04f:
    r->edx = r->eax;
    r->eax = r->ecx;
    call_mem_keep(r, 0x47ed30, 8);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
}

uint32_t vertrix_port_message_queue_take_48be70(PORT_SIGNATURE)
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
