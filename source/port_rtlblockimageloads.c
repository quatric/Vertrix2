#include "port_rtlblockimageloads.h"

/* Routine 0x41df30 switches on the per-index mode word dword [0x4f8554 + idx*4]. */

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

/* Original 0x41df30: Routine 0x41df30 switches on the per-index mode word dword [0x4f8554 + idx*4].
 * For modes 0, 1 and 2 it first calls table_build_pair_45e440. It then loads block images from
 * '.\IMAGE\BLOCS\' (0x4fc6b0) by joining names from tables 0x533360/0x5333b0, calling
 * object_named_423ea0 and freeing the holder. Mode 0 loads one pair, then calls seven_steps_45f0a0
 * and seven_calls_415330. Mode 1 picks one index with random_below(0x12). It walks a 7-byte pattern
 * from 0x4f9e78, assigning a name into 0x53ba88 where the byte is 6, and calls
 * resource_kind_finish_45f0c0 and table_pair_select_415350. Mode 2 shuffles the other 17 indices,
 * then loads 7 slots with resource_indexed_finish_45f140 and table_pair_select_4153e0. Modes 1 and
 * 2 end with table_identity_cells_45f1e0. Every path ends with resource_rows_build_45e590. Callers
 * include screen_title_music_41f080 and screen_title_room_41f500. Evidence: calls 0x45e590,
 * 0x45e440, 0x45f540, 0x423ea0, 0x45f0a0, 0x478d80, 0x415330, 0x4826c0, 0x4ca310, 0x45f0c0,
 * 0x415350, 0x45f1e0, 0x45f140, 0x4153e0. Register-for-register from the listing
 * (0x41df3e..0x41e274); labels are the original addresses. */
static void run(Regs *r)
{
    wr32(r, r->ebp - 0x28, r->eax);
    r->edi = r->ebp - 0x34;
    r->esi = 0x4f9e78;
    movs(r, 4);
    movs(r, 2);
    movs(r, 1);
    r->esi = r->eax * 4;
    r->edx = rd32(r, r->esi + 0x4f8554);
    if (r->edx == 0)
    {
        goto at_41df7f;
    }
    if (r->edx == 0x1)
    {
        goto at_41dfee;
    }
    if (r->edx == 0x2)
    {
        goto at_41e0b1;
    }
    call(r, 0x45e590, 0);
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_41df7f:
    call(r, 0x45e440, 0);
    r->ebx = 0x533360;
    r->edx = 0x4fc6b0;
    r->eax = r->ebp - 0x278;
    r->ebx = rd32(r, r->esi + r->ebx);
    call(r, 0x45f540, 0);
    r->ebx = 0x5333b0;
    r->edx = 0x4fc6b0;
    r->eax = r->ebp - 0x37c;
    r->ebx = rd32(r, r->esi + r->ebx);
    call(r, 0x45f540, 0);
    r->edx = r->ebp - 0x37c;
    r->eax = r->ebp - 0x278;
    call(r, 0x423ea0, 0);
    r->edx = r->eax;
    if (r->eax == 0)
    {
        goto at_41dfd7;
    }
    call(r, 0x45f0a0, 0);
    r->eax = r->edx;
    call(r, 0x478d80, 0);
at_41dfd7:
    r->eax = rd32(r, r->ebp - 0x28);
    call(r, 0x415330, 0);
    call(r, 0x45e590, 0);
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_41dfee:
    call(r, 0x45e440, 0);
    r->eax = 0x53ba88;
    r->eax = r->eax + r->esi;
    r->ecx = 0;
    wr32(r, r->ebp - 0x24, r->eax);
at_41dfff:
    r->edx = 0x12;
    r->eax = 0x598d30;
    call(r, 0x4826c0, 0);
    r->esi = 0;
    set_low8(&r->ebx, rd8(r, r->ecx + r->ebp - 0x34));
    set_low16(&r->esi, (r->eax & 0xffff));
    if ((uint8_t)((r->ebx & 0xff)) != (uint8_t)0x6)
    {
        goto at_41e031;
    }
    r->edx = r->esi * 4;
    r->eax = rd32(r, r->ebp - 0x24);
    r->edx = r->edx + 0x53ba88;
    call(r, 0x4ca310, 0);
at_41e031:
    r->ebx = 0x533360;
    r->edx = 0x4fc6b0;
    r->eax = r->ebp - 0x278;
    r->ebx = rd32(r, r->ebx + r->esi * 4);
    call(r, 0x45f540, 0);
    r->ebx = 0x5333b0;
    r->edx = 0x4fc6b0;
    r->eax = r->ebp - 0x37c;
    r->ebx = rd32(r, r->ebx + r->esi * 4);
    call(r, 0x45f540, 0);
    r->edx = r->ebp - 0x37c;
    r->eax = r->ebp - 0x278;
    call(r, 0x423ea0, 0);
    r->ebx = r->eax;
    if (r->eax == 0)
    {
        goto at_41e086;
    }
    r->edx = r->ecx;
    call(r, 0x45f0c0, 0);
    r->eax = r->ebx;
    call(r, 0x478d80, 0);
at_41e086:
    r->edx = 0;
    r->eax = r->esi;
    set_low8(&r->edx, rd8(r, r->ecx + r->ebp - 0x34));
    r->ecx = r->ecx + 1;
    call(r, 0x415350, 0);
    if (r->ecx < 0x7 && !r->port->env.failed)
    {
        goto at_41dfff;
    }
    call(r, 0x45f1e0, 0);
    call(r, 0x45e590, 0);
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_41e0b1:
    call(r, 0x45e440, 0);
    r->edx = 0x12;
    r->eax = 0x598d30;
    call(r, 0x4826c0, 0);
    r->edi = 0x6;
    r->eax = r->eax & 0xffff;
    r->edx = 0x5;
    wr32(r, r->ebp - 0x2c, r->eax);
    r->ebx = 0;
    r->esi = rd32(r, r->ebp - 0x2c);
    r->eax = 0;
at_41e0de:
    if (r->eax == r->esi)
    {
        goto at_41e100;
    }
    r->ebx = r->ebx + 1;
    r->ebx = r->ebx + 1;
    wr32(r, r->ebp + r->ebx * 4 - 0x17c, r->eax);
    wr32(r, r->ebp + r->ebx * 4 - 0xdc, r->edi);
    wr32(r, r->ebp + r->ebx * 4 - 0x178, r->eax);
    wr32(r, r->ebp + r->ebx * 4 - 0xd8, r->edx);
at_41e100:
    r->eax = r->eax + 1;
    if (r->eax < 0x12 && !r->port->env.failed)
    {
        goto at_41e0de;
    }
    r->edi = 0;
    if (r->ebx == 0)
    {
        goto at_41e170;
    }
    r->ecx = 0;
at_41e10e:
    r->edx = 0;
    r->eax = 0x598d30;
    set_low16(&r->edx, (r->ebx & 0xffff));
    call(r, 0x4826c0, 0);
    r->eax = r->eax & 0xffff;
    r->ecx = r->ecx + 0x4;
    r->edx = rd32(r, r->ebp + r->eax * 4 - 0x174);
    r->esi = rd32(r, r->ecx + r->ebp - 0x178);
    wr32(r, r->ecx + r->ebp - 0x178, r->edx);
    r->edx = rd32(r, r->ebp + r->eax * 4 - 0xd4);
    wr32(r, r->ebp + r->eax * 4 - 0x174, r->esi);
    r->esi = rd32(r, r->ecx + r->ebp - 0xd8);
    wr32(r, r->ecx + r->ebp - 0xd8, r->edx);
    r->edi = r->edi + 1;
    wr32(r, r->ebp + r->eax * 4 - 0xd4, r->esi);
    if (r->edi < r->ebx && !r->port->env.failed)
    {
        goto at_41e10e;
    }
at_41e170:
    r->eax = rd32(r, r->ebp - 0x28);
    r->edx = 0x53ba88;
    r->eax = r->eax << 0x2;
    r->ecx = 0;
    r->edx = r->edx + r->eax;
    wr32(r, r->ebp - 0x1c, r->ecx);
    wr32(r, r->ebp - 0x20, r->edx);
at_41e185:
    set_high8(&r->eax, rd8(r, r->ecx + r->ebp - 0x34));
    if ((uint8_t)(((r->eax >> 8) & 0xff)) != (uint8_t)0x5)
    {
        goto at_41e23f;
    }
    r->edx = 0x5;
    r->edi = rd32(r, r->ebp - 0x2c);
    wr32(r, r->ebp - 0x18, r->edx);
at_41e19d:
    if ((uint8_t)rd8(r, r->ecx + r->ebp - 0x34) != (uint8_t)0x6)
    {
        goto at_41e1b9;
    }
    r->edx = r->edi * 4;
    r->eax = rd32(r, r->ebp - 0x20);
    r->edx = r->edx + 0x53ba88;
    call(r, 0x4ca310, 0);
at_41e1b9:
    r->ebx = 0x533360;
    r->edx = 0x4fc6b0;
    r->eax = r->ebp - 0x278;
    r->ebx = rd32(r, r->ebx + r->edi * 4);
    call(r, 0x45f540, 0);
    r->ebx = 0x5333b0;
    r->edx = 0x4fc6b0;
    r->eax = r->ebp - 0x37c;
    r->ebx = rd32(r, r->ebx + r->edi * 4);
    call(r, 0x45f540, 0);
    r->edx = r->ebp - 0x37c;
    r->eax = r->ebp - 0x278;
    call(r, 0x423ea0, 0);
    r->esi = r->eax;
    if (r->eax == 0)
    {
        goto at_41e211;
    }
    r->edx = rd32(r, r->ebp - 0x18);
    r->ebx = r->ecx;
    call(r, 0x45f140, 0);
    r->eax = r->esi;
    call(r, 0x478d80, 0);
at_41e211:
    r->edx = rd32(r, r->ebp - 0x18);
    r->ebx = 0;
    r->eax = r->edi;
    set_low8(&r->ebx, rd8(r, r->ecx + r->ebp - 0x34));
    r->ecx = r->ecx + 1;
    call(r, 0x4153e0, 0);
    if (r->ecx < 0x7 && !r->port->env.failed)
    {
        goto at_41e185;
    }
    call(r, 0x45f1e0, 0);
    call(r, 0x45e590, 0);
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_41e23f:
    if ((uint8_t)(((r->eax >> 8) & 0xff)) != (uint8_t)0x6)
    {
        goto at_41e254;
    }
    r->eax = 0x6;
    r->edi = rd32(r, r->ebp - 0x2c);
    wr32(r, r->ebp - 0x18, r->eax);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_41e19d;
at_41e254:
    r->eax = rd32(r, r->ebp - 0x1c);
    r->esi = rd32(r, r->ebp - 0x1c);
    r->edi = rd32(r, r->ebp - 0x1c);
    r->esi = r->esi + 0x4;
    r->eax = rd32(r, r->eax + r->ebp - 0xd4);
    r->edi = rd32(r, r->edi + r->ebp - 0x174);
    wr32(r, r->ebp - 0x18, r->eax);
    wr32(r, r->ebp - 0x1c, r->esi);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_41e19d;
}

uint32_t vertrix_port_block_images_load_for_mode_41df30(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x380
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
