#include "port_rtlmp3memorydecodes.h"

/* Decodes a whole MP3 stream into memory: allocates a 400,000-byte buffer, resets the reader,
 * decodes frames 0x2000 bytes at a time (0x405f70) and appends each frame's output, then wraps the
 * result in a new 0x18-byte record. */

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

static void set_low16(uint32_t *reg, uint32_t value)
{
    *reg = (*reg & 0xffff0000u) | (value & 0xffff);
}

/* The last value pushed taken back. */
static uint32_t pop(Regs *r)
{
    return r->pushed != 0 ? r->stack[--r->pushed] : 0;
}

/* movs and rep movs of size bytes from esi to edi, forwards. */
static void movs(Regs *r, unsigned size)
{
    if (size == 1)
    {
        wr8(r, r->edi, rd8(r, r->esi));
    }
    else if (size == 2)
    {
        wr16(r, r->edi, rd16(r, r->esi));
    }
    else
    {
        wr32(r, r->edi, rd32(r, r->esi));
    }
    r->esi += size;
    r->edi += size;
}

static void rep_movs(Regs *r, unsigned size)
{
    for (; r->ecx != 0 && !r->port->env.failed; r->ecx--)
    {
        movs(r, size);
    }
}

/* Original 0x48b2f0: Decodes a whole MP3 stream into memory: allocates a 400,000-byte buffer,
 * resets the reader, decodes frames 0x2000 bytes at a time (0x405f70) and appends each frame's
 * output, then wraps the result in a new 0x18-byte record. Evidence: calls 0x4ec160, 0x405d60,
 * 0x48aa70, 0x48aa80, 0x405f70, 0x404580, 0x40ac50, 0x4ea190, 0x40acd0; reads 0x598dac; writes
 * 0x598dac. Register-for-register from the listing (0x48b2fd..0x48b49d); labels are the original
 * addresses. */
static void run(Regs *r)
{
    r->ecx = r->eax;
    wr32(r, r->ebp - 0x20, r->edx);
    r->edx = 0;
    r->eax = 0x1;
    wr32(r, r->ebp - 0x18, r->edx);
    r->edx = 0x61a80;
    call_keep(r, 0x4ec160);
    wr32(r, r->ebp - 0x1c, r->eax);
    wr32(r, r->ebp - 0x14, r->eax);
    r->eax = r->ebp - 0x6798;
    call_keep(r, 0x405d60);
    r->eax = r->ebp - 0x24;
    push(r, r->eax);
    push(r, 0x2000);
    r->eax = r->ecx;
    call_keep(r, 0x48aa70);
    r->ebx = r->eax;
    r->eax = r->ecx;
    call_keep(r, 0x48aa80);
    r->ecx = r->ebp - 0x2028;
    r->edx = r->eax;
    r->eax = r->ebp - 0x6798;
    call(r, 0x405f70, 2);
    r->ebx = r->eax;
    r->ecx = r->eax;
    r->eax = r->ebp - 0x6784;
    call_keep(r, 0x404580);
    if (r->ebx != 0)
    {
        goto at_48b3c0;
    }
at_48b366:
    r->ecx = rd32(r, r->ebp - 0x24);
    r->esi = r->ebp - 0x2028;
    r->edi = rd32(r, r->ebp - 0x14);
    r->ebx = rd32(r, r->ebp - 0x18);
    push(r, r->edi);
    r->eax = r->ecx;
    r->ecx = r->ecx >> 0x2;
    rep_movs(r, 4);
    set_low8(&r->ecx, (r->eax & 0xff));
    set_low8(&r->ecx, (r->ecx & 0xff) & 0x3);
    rep_movs(r, 1);
    r->edi = pop(r);
    r->eax = rd32(r, r->ebp - 0x24);
    r->edx = 0;
    r->ecx = r->edi + r->eax;
    r->ebx = r->ebx + r->eax;
    r->eax = r->ebp - 0x24;
    wr32(r, r->ebp - 0x14, r->ecx);
    push(r, r->eax);
    wr32(r, r->ebp - 0x18, r->ebx);
    r->ecx = r->ebp - 0x2028;
    push(r, 0x2000);
    r->ebx = 0;
    r->eax = r->ebp - 0x6798;
    call(r, 0x405f70, 2);
    r->ecx = r->eax;
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_48b366;
    }
at_48b3c0:
    if (r->ecx == 0xffffffffu)
    {
        goto at_48b488;
    }
    r->edx = 0x18;
    r->eax = 0x1;
    call_keep(r, 0x4ec160);
    r->ecx = r->eax;
    wr32(r, r->ebp - 0x28, r->eax);
    if (r->eax == 0)
    {
        goto at_48b488;
    }
    wr16(r, r->eax + 0x16, 0x1);
    r->eax = rd32(r, r->ebp - 0x6760);
    set_low16(&r->eax, rd16(r, r->eax * 4 + 0x4f41ac));
    wr32(r, r->ecx + 0xc, 0x0);
    wr16(r, r->ecx + 0x14, (r->eax & 0xffff));
    r->eax = rd32(r, r->ebp - 0x18);
    wr32(r, r->ecx + 0x8, r->eax);
    r->eax = r->ecx;
    wr32(r, r->ecx + 0x10, 0x0);
    call_keep(r, 0x40ac50);
    if (r->eax == 0)
    {
        goto at_48b434;
    }
    r->eax = rd32(r, r->ebp - 0x1c);
    call_keep(r, 0x4ea190);
    r->eax = r->ecx;
    call_keep(r, 0x4ea190);
    r->eax = rd32(r, r->ebp - 0x20);
    wr32(r, r->eax, 0x0);
at_48b434:
    r->edi = rd32(r, r->ebp - 0x28);
    r->ecx = rd32(r, r->ebp - 0x18);
    r->esi = rd32(r, r->ebp - 0x1c);
    r->ebx = rd32(r, r->ebp - 0x18);
    r->edi = rd32(r, r->edi);
    r->edx = 0;
    push(r, r->edi);
    r->eax = r->ecx;
    r->ecx = r->ecx >> 0x2;
    rep_movs(r, 4);
    set_low8(&r->ecx, (r->eax & 0xff));
    set_low8(&r->ecx, (r->ecx & 0xff) & 0x3);
    rep_movs(r, 1);
    r->edi = pop(r);
    r->eax = rd32(r, r->ebp - 0x28);
    call_keep(r, 0x40acd0);
    r->eax = rd32(r, r->ebp - 0x20);
    r->ecx = rd32(r, r->ebp - 0x28);
    wr32(r, r->eax, r->ecx);
    r->eax = rd32(r, r->ebp - 0x1c);
    call_keep(r, 0x4ea190);
    r->esi = rd32(r, 0x598dac);
    r->eax = rd32(r, r->ecx + 0x8);
    r->esi = r->esi + r->eax;
    wr32(r, 0x598dac, r->esi);
    r->eax = 0;
    r->edi = rd32(r, r->ebp - 0x10);
    r->esi = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_48b488:
    r->eax = rd32(r, r->ebp - 0x1c);
    call_keep(r, 0x4ea190);
    r->eax = 0xb;
    r->edi = rd32(r, r->ebp - 0x10);
    r->esi = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
}

uint32_t vertrix_port_mp3_decode_to_memory_48b2f0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x679c
    };
    /* Static: 26 KB is too much for the Wii thread stack, and the routine is not reentered (its
     * callees decode one MP3 frame and never call back). */
    static uint8_t stack[BELOW + 8];
    Port port;
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
    port_set32(&port, r.ebp, -0xcu, entry->esi);
    port_set32(&port, r.ebp, -0x10u, entry->edi);
    run(&r);
    return port_return(&port, r.eax, r.edx);
}
