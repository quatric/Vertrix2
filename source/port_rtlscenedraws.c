#include "port_rtlscenedraws.h"

/* At 0x42f910 the routine draws the actors in the scene object, passing edx through to each draw
 * call. */

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

/* An indirect call (an import or a method): every value pushed passed and popped, as stdcall. */
static void call_all(Regs *r, uint32_t target)
{
    call_with_stack(r, target, r->pushed, 0);
}

/* Original 0x42f910: At 0x42f910 the routine draws the actors in the scene object, passing edx
 * through to each draw call. When the flag at +0xb8c is set, it finds the range of byte +0x44
 * across the two 65-entry actor arrays at +0x220 and +0x87c, with the minimum starting at 0x10. It
 * then calls each matching actor's draw slot [[actor+0x158]+8] for each value from the lowest to
 * the highest. When the flag is clear, it calls vertrix_port_actor_array_draw (0x4b2380) on both
 * arrays. Next it calls array_draw on +0x988 (5), +0x9e8 (13), +0xa2c (13) and +0x324 (0x104). It
 * then draws the actors at +0xa60, +0xb70 and +0xb78 when they are not null, calls array_draw on
 * +0xbdc (0x41), calls vertrix_port_layer_list_call (0x4b6070) on +0xcec, and draws the actor at
 * +0xce0 last. Evidence: calls 0x4b2380, 0x4b6070. Register-for-register from the listing
 * (0x42f91a..0x42fb55); labels are the original addresses. */
static void run(Regs *r)
{
    wr32(r, r->ebp - 0x24, r->eax);
    r->esi = r->edx;
    if (rd32(r, r->eax + 0xb8c) == 0x0)
    {
        goto at_42fb16;
    }
    set_low8(&r->ecx, 0x10);
    r->edi = 0;
    set_high8(&r->ebx, 0);
    wr32(r, r->ebp - 0x30, r->edi);
at_42f935:
    r->edi = rd32(r, r->ebp - 0x24);
    r->edi = r->edi + rd32(r, r->ebp - 0x30);
    r->eax = 0;
    wr32(r, r->ebp - 0x28, r->edi);
    wr32(r, r->ebp - 0x2c, r->edi);
at_42f943:
    r->edi = rd32(r, r->ebp - 0x2c);
    r->edi = r->edi + r->eax;
    r->edx = rd32(r, r->edi + 0x220);
    if (r->edx == 0)
    {
        goto at_42f961;
    }
    set_low8(&r->ebx, rd8(r, r->edx + 0x44));
    if ((uint8_t)((r->ebx & 0xff)) <= (uint8_t)(((r->ebx >> 8) & 0xff)))
    {
        goto at_42f95b;
    }
    set_high8(&r->ebx, (r->ebx & 0xff));
at_42f95b:
    if ((uint8_t)((r->ebx & 0xff)) >= (uint8_t)((r->ecx & 0xff)))
    {
        goto at_42f961;
    }
    set_low8(&r->ecx, (r->ebx & 0xff));
at_42f961:
    r->edi = rd32(r, r->ebp - 0x28);
    r->edi = r->edi + r->eax;
    r->edx = rd32(r, r->edi + 0x87c);
    if (r->edx == 0)
    {
        goto at_42f97f;
    }
    set_low8(&r->ebx, rd8(r, r->edx + 0x44));
    if ((uint8_t)((r->ebx & 0xff)) <= (uint8_t)(((r->ebx >> 8) & 0xff)))
    {
        goto at_42f979;
    }
    set_high8(&r->ebx, (r->ebx & 0xff));
at_42f979:
    if ((uint8_t)((r->ebx & 0xff)) >= (uint8_t)((r->ecx & 0xff)))
    {
        goto at_42f97f;
    }
    set_low8(&r->ecx, (r->ebx & 0xff));
at_42f97f:
    r->eax = r->eax + 0x4;
    if (r->eax != 0x34 && !r->port->env.failed)
    {
        goto at_42f943;
    }
    r->edi = rd32(r, r->ebp - 0x30);
    r->edi = r->edi + r->eax;
    wr32(r, r->ebp - 0x30, r->edi);
    if (r->edi != 0x104 && !r->port->env.failed)
    {
        goto at_42f935;
    }
    set_low8(&r->ebx, (r->ecx & 0xff));
    if ((uint8_t)((r->ecx & 0xff)) > (uint8_t)(((r->ebx >> 8) & 0xff)))
    {
        goto at_42fa3f;
    }
at_42f9a1:
    r->edx = 0;
    wr32(r, r->ebp - 0x20, r->edx);
at_42f9a6:
    r->eax = rd32(r, r->ebp - 0x24);
    r->eax = r->eax + rd32(r, r->ebp - 0x20);
    r->ecx = 0;
    wr32(r, r->ebp - 0x18, r->eax);
at_42f9b1:
    r->eax = rd32(r, r->ebp - 0x18);
    r->eax = r->eax + r->ecx;
    r->edx = rd32(r, r->eax + 0x220);
    if (r->edx == 0)
    {
        goto at_42f9d2;
    }
    r->eax = r->edx;
    if ((uint8_t)((r->ebx & 0xff)) != (uint8_t)rd8(r, r->edx + 0x44))
    {
        goto at_42f9d2;
    }
    r->edi = rd32(r, r->eax + 0x158);
    r->edx = r->esi;
    call_all(r, rd32(r, r->edi + 0x8));
at_42f9d2:
    r->ecx = r->ecx + 0x4;
    if (r->ecx != 0x34 && !r->port->env.failed)
    {
        goto at_42f9b1;
    }
    r->ecx = rd32(r, r->ebp - 0x20);
    r->ecx = r->ecx + 0x34;
    wr32(r, r->ebp - 0x20, r->ecx);
    if (r->ecx != 0x104 && !r->port->env.failed)
    {
        goto at_42f9a6;
    }
    r->eax = 0;
    wr32(r, r->ebp - 0x1c, r->eax);
at_42f9f0:
    r->eax = rd32(r, r->ebp - 0x24);
    r->eax = r->eax + rd32(r, r->ebp - 0x1c);
    r->ecx = 0;
    wr32(r, r->ebp - 0x14, r->eax);
at_42f9fb:
    r->eax = rd32(r, r->ebp - 0x14);
    r->eax = r->eax + r->ecx;
    r->edi = rd32(r, r->eax + 0x87c);
    if (r->edi == 0)
    {
        goto at_42fa1e;
    }
    set_high8(&r->edx, rd8(r, r->edi + 0x44));
    r->eax = r->edi;
    if ((uint8_t)((r->ebx & 0xff)) != (uint8_t)(((r->edx >> 8) & 0xff)))
    {
        goto at_42fa1e;
    }
    r->edi = rd32(r, r->edi + 0x158);
    r->edx = r->esi;
    call_all(r, rd32(r, r->edi + 0x8));
at_42fa1e:
    r->ecx = r->ecx + 0x4;
    if (r->ecx != 0x34 && !r->port->env.failed)
    {
        goto at_42f9fb;
    }
    r->eax = rd32(r, r->ebp - 0x1c);
    r->eax = r->eax + r->ecx;
    wr32(r, r->ebp - 0x1c, r->eax);
    if (r->eax != 0x104 && !r->port->env.failed)
    {
        goto at_42f9f0;
    }
    set_low8(&r->ebx, (r->ebx & 0xff) + 1);
    if ((uint8_t)((r->ebx & 0xff)) <= (uint8_t)(((r->ebx >> 8) & 0xff)) && !r->port->env.failed)
    {
        goto at_42f9a1;
    }
at_42fa3f:
    r->eax = rd32(r, r->ebp - 0x24);
    r->edx = 0x5;
    r->ebx = r->esi;
    r->eax = r->eax + 0x988;
    call(r, 0x4b2380, 0);
    r->eax = rd32(r, r->ebp - 0x24);
    r->edx = 0xd;
    r->ebx = r->esi;
    r->eax = r->eax + 0x9e8;
    call(r, 0x4b2380, 0);
    r->eax = rd32(r, r->ebp - 0x24);
    r->edx = 0xd;
    r->ebx = r->esi;
    r->eax = r->eax + 0xa2c;
    call(r, 0x4b2380, 0);
    r->eax = rd32(r, r->ebp - 0x24);
    r->edx = 0x104;
    r->ebx = r->esi;
    r->eax = r->eax + 0x324;
    call(r, 0x4b2380, 0);
    r->eax = rd32(r, r->ebp - 0x24);
    r->ecx = rd32(r, r->eax + 0xa60);
    if (r->ecx == 0)
    {
        goto at_42faa9;
    }
    r->eax = r->ecx;
    r->ecx = rd32(r, r->ecx + 0x158);
    r->edx = r->esi;
    call_all(r, rd32(r, r->ecx + 0x8));
at_42faa9:
    r->eax = rd32(r, r->ebp - 0x24);
    r->ebx = rd32(r, r->eax + 0xb70);
    if (r->ebx == 0)
    {
        goto at_42fac3;
    }
    r->ecx = rd32(r, r->ebx + 0x158);
    r->eax = r->ebx;
    r->edx = r->esi;
    call_all(r, rd32(r, r->ecx + 0x8));
at_42fac3:
    r->eax = rd32(r, r->ebp - 0x24);
    r->edi = rd32(r, r->eax + 0xb78);
    if (r->edi == 0)
    {
        goto at_42fadd;
    }
    r->ecx = rd32(r, r->edi + 0x158);
    r->eax = r->edi;
    r->edx = r->esi;
    call_all(r, rd32(r, r->ecx + 0x8));
at_42fadd:
    r->eax = rd32(r, r->ebp - 0x24);
    r->edx = 0x41;
    r->ebx = r->esi;
    r->eax = r->eax + 0xbdc;
    call(r, 0x4b2380, 0);
    r->eax = rd32(r, r->ebp - 0x24);
    r->edx = r->esi;
    r->eax = r->eax + 0xcec;
    call(r, 0x4b6070, 0);
    r->eax = rd32(r, r->ebp - 0x24);
    r->edx = rd32(r, r->eax + 0xce0);
    if (r->edx != 0)
    {
        goto at_42fb40;
    }
    r->edi = rd32(r, r->ebp - 0x10);
    r->esi = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_42fb16:
    r->edx = 0x41;
    r->eax = r->eax + 0x220;
    r->ebx = r->esi;
    call(r, 0x4b2380, 0);
    r->eax = rd32(r, r->ebp - 0x24);
    r->edx = 0x41;
    r->ebx = r->esi;
    r->eax = r->eax + 0x87c;
    call(r, 0x4b2380, 0);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_42fa3f;
at_42fb40:
    r->ecx = rd32(r, r->edx + 0x158);
    r->eax = r->edx;
    r->edx = r->esi;
    call_all(r, rd32(r, r->ecx + 0x8));
    r->edi = rd32(r, r->ebp - 0x10);
    r->esi = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
}

uint32_t vertrix_port_scene_draw_actors_layered_42f910(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x34
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
    port_set32(&port, r.ebp, -0xcu, entry->esi);
    port_set32(&port, r.ebp, -0x10u, entry->edi);
    run(&r);
    return port_return(&port, r.eax, r.edx);
}
