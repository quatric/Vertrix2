#include "port_rtlterminates.h"

/* A runtime file and handle routine (the lifter named it rtl_terminate_call): it calls 0x4cd0c0,
 * 0x4cd184, 0x4e08e0, the stream seek 0x4e0150 and the handle table setter 0x4e0228, and reads
 * GetLastError through 0x4e0884. */

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

static void call_mem_keep(Regs *r, uint32_t target, unsigned count)
{
    call_mem_with(r, target, count, 1);
}

/* Original 0x4cd0a4: A runtime file and handle routine (the lifter named it rtl_terminate_call): it
 * calls 0x4cd0c0, 0x4cd184, 0x4e08e0, the stream seek 0x4e0150 and the handle table setter
 * 0x4e0228, and reads GetLastError through 0x4e0884. Evidence: calls 0x4df320, 0x4e0150, 0x4e01d0,
 * 0x4e0228, 0x4eb5c0, 0x4cd184. Register-for-register from the listing (0x4cd0a4..0x4cd186); labels
 * are the original addresses. */
static void run(Regs *r)
{
    push_mem(r, r->ecx);
    push_mem(r, r->esi);
    r->esi = r->eax;
    r->ecx = 0x4cd090;
    call_mem_keep(r, 0x4df320, 8);
    wr8(r, r->esi + r->eax, 0x0);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    return;
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->ebx + 0x51, rd8(r, r->ebx + 0x51) + (r->edx & 0xff));
    push_mem(r, r->edx);
    push_mem(r, r->esi);
    push_mem(r, r->edi);
    r->esp = r->esp - 0x200;
    r->edi = r->eax;
    r->ebx = 0x1;
    r->edx = 0;
    call_mem_keep(r, 0x4e0150, 8);
    r->ecx = r->eax;
    if (r->eax == 0xffffffffu)
    {
        goto at_4cd177;
    }
    r->ebx = 0x2;
    r->eax = r->edi;
    r->edx = 0;
    call_mem_keep(r, 0x4e0150, 8);
    if (r->eax == 0xffffffffu)
    {
        goto at_4cd177;
    }
    if ((int32_t)r->ecx <= (int32_t)r->eax)
    {
        goto at_4cd14c;
    }
    r->ecx = r->ecx - r->eax;
    r->eax = r->edi;
    call_mem_keep(r, 0x4e01d0, 8);
    set_high8(&r->eax, ((r->eax >> 8) & 0xff) & 0x7f);
    r->edx = r->eax;
    r->eax = r->edi;
    call_mem_keep(r, 0x4e0228, 8);
    if ((int32_t)r->ecx <= 0)
    {
        goto at_4cd175;
    }
    r->ebx = 0x200;
    r->eax = r->esp;
    r->edx = 0;
    call_mem_keep(r, 0x4eb5c0, 8);
at_4cd126:
    if ((int32_t)r->ecx <= (int32_t)0x200)
    {
        goto at_4cd135;
    }
    r->esi = 0x200;
    goto at_4cd137;
at_4cd135:
    r->esi = r->ecx;
at_4cd137:
    r->edx = r->esp;
    r->ebx = r->esi;
    r->eax = r->edi;
    call_mem_keep(r, 0x4cd184, 8);
    if ((int32_t)r->eax < 0)
    {
        goto at_4cd177;
    }
    r->ecx = r->ecx - r->esi;
    if (r->ecx != 0 && !r->port->env.failed)
    {
        goto at_4cd126;
    }
    goto at_4cd175;
at_4cd14c:
    r->edx = r->ecx;
    r->eax = r->edi;
    r->ebx = 0;
    call_mem_keep(r, 0x4e0150, 8);
    r->ecx = r->eax;
    r->eax = r->edi;
    call_mem_keep(r, 0x4e01d0, 8);
    set_high8(&r->eax, ((r->eax >> 8) & 0xff) & 0x7f);
    r->edx = r->eax;
    r->eax = r->edi;
    call_mem_keep(r, 0x4e0228, 8);
    if (r->ecx != 0xffffffffu)
    {
        goto at_4cd175;
    }
    r->eax = r->ecx;
    goto at_4cd177;
at_4cd175:
    r->eax = 0;
at_4cd177:
    r->esp = r->esp + 0x200;
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
    push_mem(r, r->ecx);
    push_mem(r, r->esi);
    push_mem(r, r->edi);
}

uint32_t vertrix_port_rtl_terminate_call_4cd0a4(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x220
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
