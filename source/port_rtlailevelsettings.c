#include "port_rtlailevelsettings.h"

/* Sets a computer player's values from its level byte (dl): +0x15c from table 0x4f8cec, +0x160 from
 * that value's range (2 above 3, other values for 7 and 12), +0x164 from table 0x4f8d38, and +0x180
 * to -1. */

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

static uint32_t rd32(Regs *r, uint32_t address)
{
    return port_u32(r->port, address, 0);
}

static void wr32(Regs *r, uint32_t address, uint32_t value)
{
    port_set32(r->port, address, 0, value);
}

static void set_low8(uint32_t *reg, uint32_t value)
{
    *reg = (*reg & 0xffffff00u) | (value & 0xff);
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

/* Original 0x425ef0: Sets a computer player's values from its level byte (dl): +0x15c from table
 * 0x4f8cec, +0x160 from that value's range (2 above 3, other values for 7 and 12), +0x164 from
 * table 0x4f8d38, and +0x180 to -1. Evidence: no calls. Register-for-register from the listing
 * (0x425ef0..0x425f39); labels are the original addresses. */
static void run(Regs *r)
{
    push_mem(r, r->ebx);
    set_low8(&r->ebx, (r->edx & 0xff));
    r->edx = 0;
    set_low8(&r->edx, (r->ebx & 0xff));
    r->edx = rd32(r, r->edx * 4 + 0x4f8cec);
    wr32(r, r->eax + 0x15c, r->edx);
    if (r->edx == 0xc)
    {
        goto at_425f41;
    }
    if (r->edx > 0x7)
    {
        goto at_425f48;
    }
    if (r->edx <= 0x3)
    {
        goto at_425f4f;
    }
    r->edx = 0x2;
at_425f18:
    wr32(r, r->eax + 0x160, r->edx);
    r->edx = 0;
    set_low8(&r->edx, (r->ebx & 0xff));
    r->edx = rd32(r, r->edx * 4 + 0x4f8d38);
    wr32(r, r->eax + 0x180, 0xffffffffu);
    wr32(r, r->eax + 0x164, r->edx);
    r->ebx = pop_mem(r);
    return;
at_425f41:
    r->edx = 0x4;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_425f18;
at_425f48:
    r->edx = 0x3;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_425f18;
at_425f4f:
    r->edx = 0x1;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_425f18;
}

uint32_t vertrix_port_ai_level_settings_init_425ef0(PORT_SIGNATURE)
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
