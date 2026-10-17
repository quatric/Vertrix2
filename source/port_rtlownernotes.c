#include "port_rtlownernotes.h"

/* Calls the object's method +0xd0, then hands it with its +0x58 and +0x4c fields to the thread
 * record's handler. */

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

/* Original 0x4d7140: Calls the object's method +0xd0, then hands it with its +0x58 and +0x4c fields
 * to the thread record's handler. Evidence: calls 0x4ce760, 0x4d70e0, 0x4cf850, 0x4cf8e0, 0x4cce60,
 * 0x4ce740, 0x4cbe80, 0x4d2910, 0x4d28c0, 0x4d25f0, 0x4ccc60, 0x4d71d0, 0x4ccdd0; reads 0x4f19c4,
 * 0x4f1b68, 0x4f1c48, 0x4f1c60. Register-for-register from the listing (0x4d7140..0x4d73ab); labels
 * are the original addresses. */
static void run(Regs *r)
{
    push_mem(r, r->ecx);
    push_mem(r, r->esi);
    push_mem(r, r->edi);
    r->esi = r->eax;
    r->edi = rd32(r, r->eax);
    call_mem(r, rd32(r, r->edi + 0xd0), 3);
    call_mem_keep(r, 0x4ce760, 8);
    r->eax = rd32(r, r->eax + 0x8);
    if (r->eax == 0)
    {
        goto at_4d7197;
    }
    if (rd32(r, r->esi + 0x58) == 0x0)
    {
        goto at_4d7197;
    }
    if (rd32(r, r->esi + 0x4c) == 0x0)
    {
        goto at_4d7174;
    }
    r->edx = r->esi;
    r->edi = rd32(r, r->eax);
    r->ecx = rd32(r, r->esi + 0x58);
    r->ebx = rd32(r, r->esi + 0x4c);
    call_mem(r, rd32(r, r->edi + 0x18), 0);
    goto at_4d7181;
at_4d7174:
    r->edx = r->esi;
    r->edi = rd32(r, r->eax);
    r->ecx = rd32(r, r->esi + 0x58);
    r->ebx = rd32(r, r->esi + 0x40);
    call_mem(r, rd32(r, r->edi + 0x14), 0);
at_4d7181:
    if (r->eax != 0)
    {
        goto at_4d7197;
    }
    r->edx = 0xffffffffu;
    r->eax = r->esi;
    call_mem_keep(r, 0x4d70e0, 8);
    r->eax = 0;
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    return;
at_4d7197:
    r->eax = r->esi;
    call_mem_keep(r, 0x4cf850, 8);
    r->ebx = r->eax;
    if (r->eax == 0)
    {
        goto at_4d71c9;
    }
    if ((uint8_t)(rd8(r, r->esi + 0x25) & 0x1) == 0)
    {
        goto at_4d71c9;
    }
    push_mem(r, 0x0);
    push_mem(r, 0x0);
    push_mem(r, rd32(r, r->esi + 0x1c));
    call_mem(r, rd32(r, 0x4f19c4), 3);
    push_mem(r, r->eax);
    call_mem(r, 0x4cf8e0, 1);
    if (r->eax == 0)
    {
        goto at_4d71c9;
    }
    call_mem_keep(r, 0x4cce60, 8);
    r->ebx = 0;
at_4d71c9:
    r->eax = r->ebx;
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    return;
    wr8(r, r->ebx + 0x56, rd8(r, r->ebx + 0x56) + (r->edx & 0xff));
    r->esp = r->esp - 0x10;
    call_mem_keep(r, 0x4ce740, 8);
    r->eax = rd32(r, r->eax + 0x4);
    if (r->eax == 0)
    {
        goto at_4d722d;
    }
    call_mem_keep(r, 0x4cbe80, 8);
    if (r->eax == 0)
    {
        goto at_4d7214;
    }
    call_mem_keep(r, 0x4cbe80, 8);
    r->edx = rd32(r, r->eax);
    call_mem(r, rd32(r, r->edx + 0x78), 0);
    if (r->eax == 0)
    {
        goto at_4d7214;
    }
    r->edx = r->esp;
    r->esi = rd32(r, r->eax);
    r->ecx = 0;
    push_mem(r, r->edx);
    r->ebx = 0;
    r->edx = 0xe146;
    call_mem(r, rd32(r, r->esi + 0x14), 1);
    if (r->eax == 0)
    {
        goto at_4d7214;
    }
    r->eax = 0x1;
    goto at_4d722d;
at_4d7214:
    call_mem_keep(r, 0x4ce740, 8);
    r->edx = r->esp;
    r->eax = rd32(r, r->eax + 0x4);
    r->ecx = 0;
    push_mem(r, r->edx);
    r->esi = rd32(r, r->eax);
    r->ebx = 0;
    r->edx = 0xe146;
    call_mem(r, rd32(r, r->esi + 0x14), 1);
at_4d722d:
    r->esp = r->esp + 0x10;
    r->esi = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    set_low8(&r->ebx, (r->ebx & 0xff) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->ebx + 0x51, rd8(r, r->ebx + 0x51) + (r->edx & 0xff));
    push_mem(r, r->edx);
    r->ecx = r->eax;
    if (rd32(r, r->eax + 0x4c) == 0x0)
    {
        goto at_4d7265;
    }
    r->edx = rd32(r, r->eax + 0x4c);
    call_mem_keep(r, 0x4d2910, 8);
    goto at_4d726d;
at_4d7265:
    r->edx = rd32(r, r->eax + 0x40);
    call_mem_keep(r, 0x4d28c0, 8);
at_4d726d:
    if (r->eax != 0)
    {
        goto at_4d7283;
    }
    r->edx = 0xffffffffu;
    r->eax = r->ecx;
    call_mem_keep(r, 0x4d70e0, 8);
    r->eax = 0;
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_4d7283:
    r->eax = r->ecx;
    r->edx = 0;
    call_mem_keep(r, 0x4d25f0, 8);
    if (r->eax != 0)
    {
        goto at_4d72a2;
    }
    r->edx = 0xffffffffu;
    r->eax = r->ecx;
    call_mem_keep(r, 0x4d70e0, 8);
    r->eax = 0;
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_4d72a2:
    r->edx = 0xe146;
    r->eax = r->ecx;
    call_mem_keep(r, 0x4ccc60, 8);
    r->ebx = r->eax;
    if (r->eax == 0)
    {
        goto at_4d72cd;
    }
    call_mem_keep(r, 0x4d71d0, 8);
    if (r->eax == 0)
    {
        goto at_4d72c4;
    }
    r->edx = 0x5;
    goto at_4d72c6;
at_4d72c4:
    r->edx = 0;
at_4d72c6:
    r->eax = r->ebx;
    call_mem_keep(r, 0x4ccdd0, 8);
at_4d72cd:
    r->eax = 0x1;
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    push_mem(r, r->ecx);
    push_mem(r, r->edx);
    r->ecx = r->eax;
    r->edx = 0x1;
    call_mem_keep(r, 0x4d25f0, 8);
    if (r->eax == 0)
    {
        goto at_4d72fe;
    }
    r->edx = 0x1;
    r->eax = r->ecx;
    call_mem_keep(r, 0x4d70e0, 8);
at_4d72fe:
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    return;
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->edx - 0x46, rd8(r, r->edx - 0x46) + (r->edx & 0xff));
    set_low8(&r->eax, (r->eax & 0xff) + rd8(r, r->eax));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    call_mem_keep(r, 0x4d70e0, 8);
    r->edx = pop_mem(r);
    return;
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->ebx + 0x51, rd8(r, r->ebx + 0x51) + (r->edx & 0xff));
    push_mem(r, r->edx);
    push_mem(r, r->esi);
    push_mem(r, r->edi);
    r->esi = r->eax;
    r->ebx = rd32(r, r->eax + 0x48);
    r->eax = rd32(r, r->eax + 0x44);
    if (rd32(r, r->esi + 0x40) == 0x0)
    {
        goto at_4d7351;
    }
    call_mem_keep(r, 0x4ce740, 8);
    push_mem(r, 0x5);
    push_mem(r, rd32(r, r->esi + 0x40));
    r->edi = rd32(r, r->eax + 0xc);
    push_mem(r, r->edi);
    call_mem(r, rd32(r, 0x4f1b68), 3);
    push_mem(r, r->eax);
    push_mem(r, r->edi);
    call_mem(r, rd32(r, 0x4f1c48), 2);
at_4d7351:
    if (r->eax == 0)
    {
        goto at_4d735f;
    }
    push_mem(r, r->eax);
    call_mem(r, rd32(r, 0x4f1c60), 1);
    r->ebx = r->eax;
at_4d735f:
    r->eax = 0x1;
    if (r->ebx == 0)
    {
        goto at_4d73a6;
    }
    r->eax = rd16(r, r->ebx + 0x2);
    r->edi = rd32(r, r->ebx);
    if (r->eax != 0xffff)
    {
        goto at_4d7382;
    }
    r->edi = rd32(r, r->ebx + 0xc);
    set_low16(&r->esi, rd16(r, r->ebx + 0x12));
    set_low16(&r->eax, rd16(r, r->ebx + 0x14));
    goto at_4d738a;
at_4d7382:
    set_low16(&r->esi, rd16(r, r->ebx + 0xa));
    set_low16(&r->eax, rd16(r, r->ebx + 0xc));
at_4d738a:
    if ((uint16_t)((r->edi & 0xffff) & 0x1801) != 0)
    {
        goto at_4d73a4;
    }
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->esi & 0xffff);
    if (r->ebx != 0)
    {
        goto at_4d73a4;
    }
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    if (r->eax != 0)
    {
        goto at_4d73a4;
    }
    r->eax = 0x1;
    goto at_4d73a6;
at_4d73a4:
    r->eax = 0;
at_4d73a6:
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
}

uint32_t vertrix_port_rtl_object_notify_owner_4d7140(PORT_SIGNATURE)
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
