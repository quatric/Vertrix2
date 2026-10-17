#include "port_rtljpegquantize3s.h"

/* libjpeg color_quantize3: maps three-component pixels to colormap indexes without dithering. */

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

/* Original 0x4c6460: libjpeg color_quantize3: maps three-component pixels to colormap indexes
 * without dithering. Evidence: no calls. Register-for-register from the listing
 * (0x4c6460..0x4c6506); labels are the original addresses. */
static void run(Regs *r)
{
    push_mem(r, r->esi);
    push_mem(r, r->edi);
    push_mem(r, r->ebp);
    r->esp = r->esp - 0x18;
    r->esi = r->eax;
    wr32(r, r->esp + 0x4, r->ecx);
    r->eax = rd32(r, r->eax + 0x1cc);
    r->eax = rd32(r, r->eax + 0x18);
    r->ecx = rd32(r, r->eax);
    r->edi = rd32(r, r->eax + 0x4);
    wr32(r, r->esp + 0x14, r->ecx);
    r->eax = rd32(r, r->eax + 0x8);
    r->ecx = 0;
    wr32(r, r->esp + 0x10, r->eax);
    wr32(r, r->esp + 0xc, r->ecx);
    r->eax = rd32(r, r->esi + 0x70);
    r->esi = rd32(r, r->esp + 0x4);
    wr32(r, r->esp + 0x8, r->eax);
    if ((int32_t)r->esi <= 0)
    {
        goto at_4c6500;
    }
    wr32(r, r->esp, r->ebx);
    r->ebp = r->edx;
at_4c649f:
    r->ecx = rd32(r, r->esp);
    r->ebx = rd32(r, r->esp + 0x8);
    r->eax = rd32(r, r->ebp);
    r->ecx = rd32(r, r->ecx);
    if (r->ebx == 0)
    {
        goto at_4c64e3;
    }
at_4c64af:
    r->edx = 0;
    r->esi = rd32(r, r->esp + 0x14);
    set_low8(&r->edx, rd8(r, r->eax));
    r->edx = r->edx + r->esi;
    r->eax = r->eax + 1;
    set_low8(&r->edx, rd8(r, r->edx));
    r->esi = rd8(r, r->eax);
    r->edx = r->edx & 0xff;
    r->esi = rd8(r, r->edi + r->esi);
    r->edx = r->edx + r->esi;
    r->esi = rd8(r, r->eax + 0x1);
    r->esi = r->esi + rd32(r, r->esp + 0x10);
    r->eax = r->eax + 1;
    r->ecx = r->ecx + 1;
    r->esi = rd8(r, r->esi);
    r->ebx = r->ebx - 1;
    r->edx = r->edx + r->esi;
    r->eax = r->eax + 1;
    wr8(r, r->ecx - 0x1, (r->edx & 0xff));
    if (r->ebx != 0 && !r->port->env.failed)
    {
        goto at_4c64af;
    }
at_4c64e3:
    r->eax = rd32(r, r->esp);
    r->edx = rd32(r, r->esp + 0xc);
    r->ecx = rd32(r, r->esp + 0x4);
    r->ebp = r->ebp + 0x4;
    r->eax = r->eax + 0x4;
    r->edx = r->edx + 1;
    wr32(r, r->esp, r->eax);
    wr32(r, r->esp + 0xc, r->edx);
    if ((int32_t)r->edx < (int32_t)r->ecx && !r->port->env.failed)
    {
        goto at_4c649f;
    }
at_4c6500:
    r->esp = r->esp + 0x18;
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
}

uint32_t vertrix_port_jpeg_color_quantize3_4c6460(PORT_SIGNATURE)
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
