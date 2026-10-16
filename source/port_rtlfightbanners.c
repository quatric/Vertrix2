#include "port_rtlfightbanners.h"

/* Sets up a 48-slot string array and first fills every slot with the text at 0x50e60d. */

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

/* Original 0x46ea30: Sets up a 48-slot string array and first fills every slot with the text at
 * 0x50e60d. It then fills (table[0x53fd38]+8) lines: the leading lines get uppercased text chosen
 * by random_below(3) (0x4826c0) from the table at 0x53d998. The last three used lines get 'PREPARE'
 * (0x50e60e), the string at 0x50e616 and 'FIGHT' (0x50e619). For each line it centres the text on a
 * 640-pixel screen using text_measure (0x440610), with lines 50 pixels apart. For each character it
 * allocates an actor with get_memory(0x15c), actor_reset and actor_initialize. It sets the
 * font_glyph (0x43f420) through actor_set_b4 and actor_lookup_image and places letters 0x23 apart.
 * Lines before the last three also get set_update(0x457e40), and every actor gets
 * set_next(0x458410) and set_time_scale. Finally it passes each actor to the list routine at
 * 0x4b5e70 with the list 0x54671c. Evidence: calls 0x4ca070, 0x4ccf3b, 0x4826c0, 0x4ca370,
 * 0x4ca310, 0x4ca710, 0x440610, 0x4ca000, 0x4abd70, 0x4adf20, 0x43f420, 0x4ac950, 0x4ac8a0,
 * 0x4ac8f0, 0x4ac910, 0x4ac7d0, 0x4b5e70, 0x4cda10; reads 0x4f9c0a. Register-for-register from the
 * listing (0x46ea3e..0x46ed97); labels are the original addresses. */
static void run(Regs *r)
{
    r->edi = r->eax;
    r->eax = r->ebp - 0x68;
    r->edx = 0x4ec1ec;
    r->ecx = 0x5161a4;
    r->esi = 0x513e60;
    push(r, r->port->env.chain);
    wr32(r, r->eax, pop(r));
    r->port->env.chain = r->eax;
    r->ebx = 0;
    r->eax = r->ebp - 0x3c;
    wr32(r, r->ebp - 0x64, r->edx);
    wr32(r, r->ebp - 0x60, r->ecx);
    wr32(r, r->ebp - 0x5c, r->ebx);
    call(r, 0x4ca070, 0);
    r->eax = r->ebp - 0x128;
    r->edx = 0x30;
    r->ecx = 0x4;
    wr32(r, r->ebp - 0x4c, r->ebx);
    wr32(r, r->ebp - 0x54, r->eax);
    r->eax = 0x2;
    r->ebx = r->esi;
    wr32(r, r->ebp - 0x5c, r->eax);
    r->eax = r->ebp - 0x128;
    wr32(r, r->ebp - 0x50, r->esi);
    call(r, 0x4ccf3b, 0);
    r->edx = 0x3;
    r->eax = 0x598d30;
    wr32(r, r->ebp - 0x5c, r->ecx);
    call(r, 0x4826c0, 0);
    r->ebx = 0;
    r->edx = r->edi;
    set_low16(&r->ebx, (r->eax & 0xffff));
    r->eax = r->edx * 4;
    r->eax = r->eax - r->edx;
    r->edx = r->ebx * 4;
    r->eax = rd32(r, r->edx + r->eax * 4 + 0x53fd38);
    r->esi = r->ebp - 0x128;
    r->eax = r->eax + 0x8;
    r->ecx = r->esi + 0xc0;
    wr32(r, r->ebp - 0x48, r->eax);
at_46eae4:
    r->edx = 0x50e60d;
    r->eax = r->esi;
    r->esi = r->esi + 0x4;
    call(r, 0x4ca370, 0);
    if (r->esi != r->ecx && !r->port->env.failed)
    {
        goto at_46eae4;
    }
    r->eax = r->ebx * 4;
    r->ecx = rd32(r, r->ebp - 0x48);
    r->eax = r->eax + r->ebx;
    r->esi = r->ebp - 0x128;
    r->eax = r->eax << 0x2;
    r->edi = r->edi << 0x2;
    r->eax = r->eax - r->ebx;
    r->ecx = r->ecx - 0x8;
    r->eax = r->eax << 0x2;
    r->ecx = r->ecx << 0x2;
    r->edi = r->edi + r->eax;
    r->ecx = r->ecx + r->esi;
    r->edi = r->edi + 0x53d998;
    if (r->esi >= r->ecx)
    {
        goto at_46eb50;
    }
at_46eb28:
    r->edx = r->edi;
    r->eax = r->esi;
    call(r, 0x4ca310, 0);
    r->eax = r->esi;
    call(r, 0x4ca710, 0);
    r->esi = r->esi + 0x4;
    r->edi = r->edi + 0xe4;
    if (r->esi < r->ecx && !r->port->env.failed)
    {
        goto at_46eb28;
    }
at_46eb50:
    r->ecx = rd32(r, r->ebp - 0x48);
    r->edx = r->ebp - 0x128;
    r->ecx = r->ecx << 0x2;
    r->ebx = 0x1a4;
    r->eax = r->ecx - 0xc;
    r->edi = rd32(r, r->ebp - 0x48);
    r->eax = r->eax + r->edx;
    r->edx = 0x50e60e;
    r->esi = 0;
    call(r, 0x4ca370, 0);
    r->edx = r->ebp - 0x128;
    r->eax = r->ecx - 0x8;
    wr32(r, r->ebp - 0x30, r->ebx);
    r->eax = r->eax + r->edx;
    r->edx = 0x50e616;
    r->ecx = r->ecx - 0x4;
    call(r, 0x4ca370, 0);
    r->eax = r->ebp - 0x128;
    r->edx = 0x50e619;
    r->eax = r->eax + r->ecx;
    wr32(r, r->ebp - 0x2c, r->esi);
    call(r, 0x4ca370, 0);
    if (r->edi == 0)
    {
        goto at_46ed80;
    }
    r->eax = r->edi - 0x3;
    wr32(r, r->ebp - 0x40, r->eax);
    r->eax = r->ebp - 0x128;
    wr32(r, r->ebp - 0x24, r->eax);
    r->eax = r->edi;
    r->eax = 0u - r->eax;
    r->eax = r->eax + 0x3;
    wr32(r, r->ebp - 0x44, r->eax);
at_46ebc6:
    r->edx = rd32(r, r->ebp - 0x24);
    r->eax = r->ebp - 0x3c;
    r->ecx = r->ebp - 0x38;
    r->ebx = 0x10;
    call(r, 0x4ca310, 0);
    r->esi = rd32(r, r->ebp - 0x3c);
    r->eax = r->ebp - 0x34;
    r->edx = rd32(r, r->ebp - 0x3c);
    push(r, r->eax);
    r->eax = rd32(r, 0x4f9c0a);
    r->esi = r->esi - 0xc;
    r->eax = (uint32_t)((int32_t)r->eax >> 0x18);
    r->esi = rd32(r, r->esi + 0x4);
    call(r, 0x440610, 1);
    r->eax = 0x280;
    r->eax = r->eax - rd32(r, r->ebp - 0x38);
    r->eax = r->eax + 1;
    r->eax = r->eax >> 0x1;
    r->eax = r->eax + 0x11;
    wr32(r, r->ebp - 0x28, r->eax);
    r->eax = 0;
    wr32(r, r->ebp - 0x1c, r->esi);
    wr32(r, r->ebp - 0x18, r->eax);
    if (r->esi == 0)
    {
        goto at_46ed55;
    }
    r->eax = rd32(r, r->ebp - 0x44);
    wr32(r, r->ebp - 0x20, r->eax);
at_46ec1d:
    r->eax = 0x15c;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_46ec30;
    }
    call(r, 0x4abd70, 0);
at_46ec30:
    r->esi = r->eax;
    push(r, 0x0);
    push(r, 0x4578f0);
    push(r, 0x0);
    push(r, 0x0);
    r->eax = r->esi;
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = 0;
    r->edx = 0;
    call(r, 0x4adf20, 5);
    r->eax = rd32(r, r->ebp - 0x3c);
    r->eax = r->eax + rd32(r, r->ebp - 0x18);
    set_low8(&r->eax, rd8(r, r->eax));
    r->edx = 0;
    set_low8(&r->edx, (r->eax & 0xff));
    r->eax = rd32(r, 0x4f9c0a);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x18);
    call(r, 0x43f420, 0);
    r->edx = r->eax;
    r->eax = r->esi;
    call(r, 0x4ac950, 0);
    r->eax = r->esi;
    call(r, 0x4ac8a0, 0);
    r->eax = rd32(r, r->ebp - 0x28);
    wr16(r, r->esi + 0xc, 0x0);
    wr16(r, r->esi + 0x8, (r->eax & 0xffff));
    r->eax = rd32(r, r->ebp - 0x30);
    wr16(r, r->esi + 0xa, (r->eax & 0xffff));
    r->eax = rd32(r, r->ebp - 0x28);
    wr16(r, r->esi + 0xe, (r->eax & 0xffff));
    r->eax = rd32(r, r->ebp - 0x30);
    r->edi = r->esi;
    wr16(r, r->esi + 0x16, (r->eax & 0xffff));
    r->eax = rd32(r, r->ebp - 0x28);
    r->ecx = rd32(r, r->ebp - 0x40);
    wr16(r, r->esi + 0x10, (r->eax & 0xffff));
    r->eax = rd32(r, r->ebp - 0x2c);
    wr16(r, r->esi + 0x18, 0xffd8);
    if (r->eax < r->ecx)
    {
        goto at_46ed06;
    }
    r->edx = 0x457e40;
    r->eax = r->esi;
    call(r, 0x4ac8f0, 0);
    r->eax = rd32(r, r->ebp - 0x34);
    r->eax = r->eax + r->eax * 2;
    r->edx = 0x1e0;
    r->eax = r->eax + 0x28;
    r->edx = r->edx - r->eax;
    r->eax = r->edx;
    r->edx = rd32(r, r->ebp - 0x34);
    r->ebx = rd32(r, r->ebp - 0x20);
    r->edx = r->edx + 0x14;
    r->edx = r->edx * r->ebx;
    r->eax = r->eax >> 0x1;
    r->eax = r->eax + r->edx;
    r->edx = rd32(r, r->ebp - 0x34);
    wr8(r, r->esi + 0x52, 0x9);
    wr8(r, r->esi + 0x94, 0x1);
    wr8(r, r->esi + 0x95, 0x4);
    wr8(r, r->esi + 0x93, 0x1);
    r->edx = r->edx >> 0x1;
    wr8(r, r->esi + 0x4e, 0x32);
    r->eax = r->eax + r->edx;
    wr16(r, r->esi + 0x18, (r->eax & 0xffff));
at_46ed06:
    r->edx = 0x458410;
    r->eax = r->edi;
    r->ecx = rd32(r, r->ebp - 0x18);
    call(r, 0x4ac910, 0);
    wr16(r, r->edi + 0x12, 0x1);
    r->edx = 0x14;
    wr16(r, r->edi + 0x1a, 0x1);
    r->eax = r->edi;
    wr8(r, r->edi + 0x44, 0x0);
    call(r, 0x4ac7d0, 0);
    r->eax = 0x54671c;
    r->edx = r->edi;
    r->ebx = rd32(r, r->ebp - 0x1c);
    call(r, 0x4b5e70, 0);
    r->edx = rd32(r, r->ebp - 0x28);
    r->ecx = r->ecx + 1;
    r->edx = r->edx + 0x23;
    wr32(r, r->ebp - 0x18, r->ecx);
    wr32(r, r->ebp - 0x28, r->edx);
    if (r->ecx < r->ebx && !r->port->env.failed)
    {
        goto at_46ec1d;
    }
at_46ed55:
    r->eax = rd32(r, r->ebp - 0x30);
    r->edx = rd32(r, r->ebp - 0x24);
    r->ecx = rd32(r, r->ebp - 0x44);
    r->ebx = rd32(r, r->ebp - 0x2c);
    r->esi = rd32(r, r->ebp - 0x48);
    r->eax = r->eax + 0x32;
    r->edx = r->edx + 0x4;
    r->ecx = r->ecx + 1;
    r->ebx = r->ebx + 1;
    wr32(r, r->ebp - 0x30, r->eax);
    wr32(r, r->ebp - 0x24, r->edx);
    wr32(r, r->ebp - 0x44, r->ecx);
    wr32(r, r->ebp - 0x2c, r->ebx);
    if (r->ebx < r->esi && !r->port->env.failed)
    {
        goto at_46ebc6;
    }
at_46ed80:
    call(r, 0x4cda10, 0);
    r->eax = rd32(r, r->ebp - 0x68);
    r->port->env.chain = r->eax;
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
}

uint32_t vertrix_port_spawn_prepare_fight_letters_46ea30(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x12c
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
