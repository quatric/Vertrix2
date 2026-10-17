#include "port_rtlaifallbacks.h"

/* The AI fallback search over columns and rotations, used when no figure move is found (see
 * ai_player.c vertrix_ai_fallback). */

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

static void set_high8(uint32_t *reg, uint32_t value)
{
    *reg = (*reg & 0xffff00ffu) | ((value & 0xff) << 8);
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

/* Original 0x426240: The AI fallback search over columns and rotations, used when no figure move is
 * found (see ai_player.c vertrix_ai_fallback). Evidence: calls 0x4eb5c0, 0x4261b0, 0x4826c0.
 * Register-for-register from the listing (0x42624b..0x4269dd); labels are the original addresses.
 */
static void run(Regs *r)
{
    wr32(r, r->ebp - 0x2c, r->eax);
    wr32(r, r->ebp - 0x20, r->edx);
    wr32(r, r->ebp - 0x28, r->ebx);
    wr32(r, r->ebp - 0x24, r->ecx);
    r->ebx = 0x5;
    r->eax = r->ebp - 0x44;
    r->esi = rd32(r, r->ebp - 0x2c);
    r->edx = 0;
    r->ecx = 0x41;
    call_keep(r, 0x4eb5c0);
    r->ebx = 0x5;
    r->eax = r->ebp - 0x54;
    r->edx = 0;
    r->edi = r->ebp - 0x98;
    call_keep(r, 0x4eb5c0);
    r->ebx = 0x5;
    r->eax = r->ebp - 0x4c;
    r->edx = 0;
    r->esi = r->esi + 0x184;
    call_keep(r, 0x4eb5c0);
    push(r, r->edi);
    r->eax = r->ecx;
    r->ecx = r->ecx >> 0x2;
    rep_movs(r, 4);
    set_low8(&r->ecx, (r->eax & 0xff));
    set_low8(&r->ecx, (r->ecx & 0xff) & 0x3);
    rep_movs(r, 1);
    r->edi = pop(r);
    r->edx = rd32(r, r->ebp + 0x18);
    r->ecx = rd32(r, r->ebp + 0x14);
    r->ebx = r->ebp - 0x3c;
    r->eax = rd32(r, r->ebp - 0x2c);
    r->edi = 0;
    push(r, r->edx);
    r->edx = r->ebp - 0x98;
    r->esi = 0;
    call(r, 0x4261b0, 1);
    r->ecx = 0;
    set_low8(&r->ebx, 0xff);
at_4262c8:
    set_high8(&r->eax, 0xd);
    set_low8(&r->edx, rd8(r, r->ecx + r->ebp - 0x3c));
    wr8(r, r->ecx + r->ebp - 0x44, ((r->eax >> 8) & 0xff));
    if ((uint8_t)((r->edx & 0xff)) == 0)
    {
        goto at_426325;
    }
    r->eax = r->esi;
    set_high8(&r->ebx, rd8(r, r->esi + r->ebp - 0x98));
    r->edx = 0;
    if ((uint8_t)((r->ebx & 0xff)) != (uint8_t)(((r->ebx >> 8) & 0xff)))
    {
        goto at_4262ff;
    }
at_4262e5:
    set_high8(&r->ebx, rd8(r, r->ecx + r->ebp - 0x44));
    r->eax = r->eax + 1;
    set_high8(&r->ebx, ((r->ebx >> 8) & 0xff) + (r->ebx & 0xff));
    r->edx = r->edx + 1;
    wr8(r, r->ecx + r->ebp - 0x44, ((r->ebx >> 8) & 0xff));
    if ((int32_t)r->edx >= (int32_t)0xd)
    {
        goto at_4262ff;
    }
    if ((uint8_t)((r->ebx & 0xff)) == (uint8_t)rd8(r, r->eax + r->ebp - 0x98) &&
        !r->port->env.failed)
    {
        goto at_4262e5;
    }
at_4262ff:
    r->eax = 0;
    r->edx = 0xd;
    set_low8(&r->eax, rd8(r, r->ecx + r->ebp - 0x44));
    r->edx = r->edx - r->eax;
    r->eax = r->edx;
    if (r->ecx != 0x2)
    {
        goto at_4267c0;
    }
    if ((int32_t)r->edx > (int32_t)0x3)
    {
        goto at_4267c0;
    }
    wr8(r, r->ecx + r->ebp - 0x44, 0xd);
at_426325:
    r->ecx = r->ecx + 1;
    r->esi = r->esi + 0xd;
    if ((int32_t)r->ecx < (int32_t)0x5 && !r->port->env.failed)
    {
        goto at_4262c8;
    }
    if (r->edi != 0)
    {
        goto at_4267d1;
    }
    r->eax = rd32(r, r->ebp + 0xc);
    wr32(r, r->eax, 0x2);
at_42633f:
    r->ebx = rd32(r, r->ebp + 0x1c);
    r->eax = 0xffffffffu;
    if (r->ebx <= 0x1)
    {
        goto at_42636d;
    }
    r->edx = rd32(r, r->ebp - 0x20);
    r->esi = rd32(r, r->ebp - 0x28);
    if (r->edx == r->esi)
    {
        goto at_4268ab;
    }
    r->edi = rd32(r, r->ebp - 0x24);
    if (r->esi == r->edi)
    {
        goto at_4268bb;
    }
    if (r->edi == r->edx)
    {
        goto at_4268ce;
    }
at_42636d:
    if (r->eax != 0xffffffffu)
    {
        goto at_4267a9;
    }
    if (rd32(r, r->ebp + 0x1c) <= 0x2)
    {
        goto at_4267a9;
    }
    r->edx = rd32(r, r->ebp + 0xc);
    r->edx = rd32(r, r->edx);
    r->ecx = 0;
    r->ebx = 0xc;
    set_low8(&r->ecx, rd8(r, r->edx + r->ebp - 0x44));
    r->ebx = r->ebx - r->ecx;
    r->esi = r->edx;
    r->ecx = r->ebx;
    if ((int32_t)r->ebx <= (int32_t)0x2)
    {
        goto at_4267a9;
    }
    if (r->edx != 0)
    {
        goto at_4268e1;
    }
    set_low8(&r->ebx, 0xfe);
    wr8(r, r->ebp - 0x1c, (r->ebx & 0xff));
    wr8(r, r->ebp - 0x10, (r->ebx & 0xff));
    set_low8(&r->edx, (r->ebx & 0xff));
    wr8(r, r->ebp - 0xc, (r->ebx & 0xff));
    wr8(r, r->ebp - 0x18, (r->ebx & 0xff));
at_4263b7:
    if (r->esi != 0x4)
    {
        goto at_426955;
    }
    set_low8(&r->ecx, 0xfe);
    set_high8(&r->ebx, (r->ecx & 0xff));
    set_high8(&r->edx, (r->ecx & 0xff));
    wr8(r, r->ebp - 0x14, (r->ecx & 0xff));
    set_low8(&r->ebx, (r->ecx & 0xff));
at_4263cb:
    r->esi = rd32(r, r->ebp - 0xf);
    r->esi = (uint32_t)((int32_t)r->esi >> 0x18);
    if ((int32_t)r->esi <= (int32_t)0xffffffffu)
    {
        goto at_4263fe;
    }
    if ((uint8_t)((r->ebx & 0xff)) != (uint8_t)0xff)
    {
        goto at_4263fe;
    }
    r->esi = rd32(r, r->ebp - 0xf);
    r->edi = rd32(r, r->ebp - 0x20);
    r->esi = (uint32_t)((int32_t)r->esi >> 0x18);
    if (r->esi == r->edi)
    {
        goto at_4268ab;
    }
    if (r->esi == rd32(r, r->ebp - 0x28))
    {
        goto at_4268bb;
    }
    if (r->esi == rd32(r, r->ebp - 0x24))
    {
        goto at_4268ce;
    }
at_4263fe:
    if (r->eax != 0xffffffffu)
    {
        goto at_426506;
    }
    r->esi = (uint32_t)(int32_t)(int8_t)(r->ebx & 0xff);
    if ((int32_t)r->esi <= (int32_t)r->eax)
    {
        goto at_426434;
    }
    if ((uint8_t)rd8(r, r->ebp - 0xc) != (uint8_t)0xff)
    {
        goto at_426434;
    }
    r->edi = rd32(r, r->ebp - 0x20);
    r->esi = (uint32_t)(int32_t)(int8_t)(r->ebx & 0xff);
    if (r->esi == r->edi)
    {
        goto at_4268ab;
    }
    if (r->esi == rd32(r, r->ebp - 0x28))
    {
        goto at_4268bb;
    }
    if (r->esi == rd32(r, r->ebp - 0x24))
    {
        goto at_4268ce;
    }
at_426434:
    if (r->eax != 0xffffffffu)
    {
        goto at_426506;
    }
    r->esi = (uint32_t)(int32_t)(int8_t)(r->edx & 0xff);
    if ((int32_t)r->esi <= (int32_t)r->eax)
    {
        goto at_426469;
    }
    if ((uint8_t)(((r->edx >> 8) & 0xff)) != (uint8_t)0xff)
    {
        goto at_426469;
    }
    r->edi = rd32(r, r->ebp - 0x20);
    r->esi = (uint32_t)(int32_t)(int8_t)(r->edx & 0xff);
    if (r->esi == r->edi)
    {
        goto at_4268ce;
    }
    if (r->esi == rd32(r, r->ebp - 0x28))
    {
        goto at_4268ab;
    }
    if (r->esi == rd32(r, r->ebp - 0x24))
    {
        goto at_4268bb;
    }
at_426469:
    if (r->eax != 0xffffffffu)
    {
        goto at_426506;
    }
    r->esi = (uint32_t)(int32_t)(int8_t)((r->edx >> 8) & 0xff);
    if ((int32_t)r->esi <= (int32_t)r->eax)
    {
        goto at_42649e;
    }
    if ((uint8_t)((r->edx & 0xff)) != (uint8_t)0xff)
    {
        goto at_42649e;
    }
    r->edi = rd32(r, r->ebp - 0x20);
    r->esi = (uint32_t)(int32_t)(int8_t)((r->edx >> 8) & 0xff);
    if (r->esi == r->edi)
    {
        goto at_4268ce;
    }
    if (r->esi == rd32(r, r->ebp - 0x28))
    {
        goto at_4268ab;
    }
    if (r->esi == rd32(r, r->ebp - 0x24))
    {
        goto at_4268bb;
    }
at_42649e:
    if (r->eax != 0xffffffffu)
    {
        goto at_426506;
    }
    r->esi = rd32(r, r->ebp - 0x13);
    r->esi = (uint32_t)((int32_t)r->esi >> 0x18);
    if ((int32_t)r->esi <= (int32_t)r->eax)
    {
        goto at_4264d5;
    }
    if ((uint8_t)(((r->ebx >> 8) & 0xff)) != (uint8_t)0xff)
    {
        goto at_4264d5;
    }
    r->esi = rd32(r, r->ebp - 0x13);
    r->edi = rd32(r, r->ebp - 0x20);
    r->esi = (uint32_t)((int32_t)r->esi >> 0x18);
    if (r->esi == r->edi)
    {
        goto at_4268bb;
    }
    if (r->esi == rd32(r, r->ebp - 0x28))
    {
        goto at_4268ce;
    }
    if (r->esi == rd32(r, r->ebp - 0x24))
    {
        goto at_4268ab;
    }
at_4264d5:
    if (r->eax != 0xffffffffu)
    {
        goto at_426506;
    }
    r->esi = (uint32_t)(int32_t)(int8_t)((r->edx >> 8) & 0xff);
    if ((int32_t)r->esi <= (int32_t)r->eax)
    {
        goto at_426506;
    }
    if ((uint8_t)((r->edx & 0xff)) != (uint8_t)0xff)
    {
        goto at_426506;
    }
    r->edi = rd32(r, r->ebp - 0x20);
    r->esi = (uint32_t)(int32_t)(int8_t)((r->ebx >> 8) & 0xff);
    if (r->esi == r->edi)
    {
        goto at_4268bb;
    }
    if (r->esi == rd32(r, r->ebp - 0x28))
    {
        goto at_4268ce;
    }
    if (r->esi == rd32(r, r->ebp - 0x24))
    {
        goto at_4268ab;
    }
at_426506:
    if (r->eax != 0xffffffffu)
    {
        goto at_426654;
    }
    if (rd32(r, r->ebp + 0x1c) != 0x4)
    {
        goto at_426654;
    }
    r->esi = rd32(r, r->ebp - 0x1b);
    r->esi = (uint32_t)((int32_t)r->esi >> 0x18);
    if ((int32_t)r->esi <= (int32_t)r->eax)
    {
        goto at_42654b;
    }
    if ((uint8_t)(((r->edx >> 8) & 0xff)) != (uint8_t)0xff)
    {
        goto at_42654b;
    }
    r->esi = rd32(r, r->ebp - 0x1b);
    r->edi = rd32(r, r->ebp - 0x20);
    r->esi = (uint32_t)((int32_t)r->esi >> 0x18);
    if (r->esi == r->edi)
    {
        goto at_4268ab;
    }
    if (r->esi == rd32(r, r->ebp - 0x28))
    {
        goto at_4268bb;
    }
    if (r->esi == rd32(r, r->ebp - 0x24))
    {
        goto at_4268ce;
    }
at_42654b:
    if (r->eax != 0xffffffffu)
    {
        goto at_426654;
    }
    r->esi = (uint32_t)(int32_t)(int8_t)((r->edx >> 8) & 0xff);
    if ((int32_t)r->esi <= (int32_t)r->eax)
    {
        goto at_426581;
    }
    if ((uint8_t)rd8(r, r->ebp - 0x18) != (uint8_t)0xff)
    {
        goto at_426581;
    }
    r->edi = rd32(r, r->ebp - 0x20);
    r->esi = (uint32_t)(int32_t)(int8_t)((r->edx >> 8) & 0xff);
    if (r->esi == r->edi)
    {
        goto at_4268ab;
    }
    if (r->esi == rd32(r, r->ebp - 0x28))
    {
        goto at_4268bb;
    }
    if (r->esi == rd32(r, r->ebp - 0x24))
    {
        goto at_4268ce;
    }
at_426581:
    if (r->eax != 0xffffffffu)
    {
        goto at_426654;
    }
    r->esi = rd32(r, r->ebp - 0xf);
    r->esi = (uint32_t)((int32_t)r->esi >> 0x18);
    if ((int32_t)r->esi <= (int32_t)r->eax)
    {
        goto at_4265bc;
    }
    if ((uint8_t)(((r->ebx >> 8) & 0xff)) != (uint8_t)0xff)
    {
        goto at_4265bc;
    }
    r->esi = rd32(r, r->ebp - 0xf);
    r->edi = rd32(r, r->ebp - 0x20);
    r->esi = (uint32_t)((int32_t)r->esi >> 0x18);
    if (r->esi == r->edi)
    {
        goto at_4268ce;
    }
    if (r->esi == rd32(r, r->ebp - 0x28))
    {
        goto at_4268ab;
    }
    if (r->esi == rd32(r, r->ebp - 0x24))
    {
        goto at_4268bb;
    }
at_4265bc:
    if (r->eax != 0xffffffffu)
    {
        goto at_426654;
    }
    r->esi = (uint32_t)(int32_t)(int8_t)((r->ebx >> 8) & 0xff);
    if ((int32_t)r->esi <= (int32_t)r->eax)
    {
        goto at_4265f2;
    }
    if ((uint8_t)rd8(r, r->ebp - 0xc) != (uint8_t)0xff)
    {
        goto at_4265f2;
    }
    r->edi = rd32(r, r->ebp - 0x20);
    r->esi = (uint32_t)(int32_t)(int8_t)((r->ebx >> 8) & 0xff);
    if (r->esi == r->edi)
    {
        goto at_4268ce;
    }
    if (r->esi == rd32(r, r->ebp - 0x28))
    {
        goto at_4268ab;
    }
    if (r->esi == rd32(r, r->ebp - 0x24))
    {
        goto at_4268bb;
    }
at_4265f2:
    if (r->eax != 0xffffffffu)
    {
        goto at_426654;
    }
    r->esi = (uint32_t)(int32_t)(int8_t)(r->edx & 0xff);
    if ((int32_t)r->esi <= (int32_t)r->eax)
    {
        goto at_426623;
    }
    if ((uint8_t)((r->ecx & 0xff)) != (uint8_t)0xff)
    {
        goto at_426623;
    }
    r->edi = rd32(r, r->ebp - 0x20);
    r->esi = (uint32_t)(int32_t)(int8_t)(r->edx & 0xff);
    if (r->esi == r->edi)
    {
        goto at_4268bb;
    }
    if (r->esi == rd32(r, r->ebp - 0x28))
    {
        goto at_4268ce;
    }
    if (r->esi == rd32(r, r->ebp - 0x24))
    {
        goto at_4268ab;
    }
at_426623:
    if (r->eax != 0xffffffffu)
    {
        goto at_426654;
    }
    r->esi = (uint32_t)(int32_t)(int8_t)(r->ecx & 0xff);
    if ((int32_t)r->esi <= (int32_t)r->eax)
    {
        goto at_426654;
    }
    if ((uint8_t)((r->edx & 0xff)) != (uint8_t)0xff)
    {
        goto at_426654;
    }
    r->esi = rd32(r, r->ebp - 0x20);
    r->ecx = (uint32_t)(int32_t)(int8_t)(r->ecx & 0xff);
    if (r->ecx == r->esi)
    {
        goto at_4268bb;
    }
    if (r->ecx == rd32(r, r->ebp - 0x28))
    {
        goto at_4268ce;
    }
    if (r->ecx == rd32(r, r->ebp - 0x24))
    {
        goto at_4268ab;
    }
at_426654:
    if (r->eax != 0xffffffffu)
    {
        goto at_4267a9;
    }
    if (rd32(r, r->ebp + 0x1c) != 0x4)
    {
        goto at_4267a9;
    }
    r->ecx = rd32(r, r->ebp - 0x17);
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x18);
    if ((int32_t)r->ecx <= (int32_t)r->eax)
    {
        goto at_426699;
    }
    if ((uint8_t)((r->edx & 0xff)) != (uint8_t)0xff)
    {
        goto at_426699;
    }
    r->ecx = rd32(r, r->ebp - 0x17);
    r->esi = rd32(r, r->ebp - 0x20);
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x18);
    if (r->ecx == r->esi)
    {
        goto at_4268ab;
    }
    if (r->ecx == rd32(r, r->ebp - 0x28))
    {
        goto at_4268bb;
    }
    if (r->ecx == rd32(r, r->ebp - 0x24))
    {
        goto at_4268ce;
    }
at_426699:
    if (r->eax != 0xffffffffu)
    {
        goto at_4267a9;
    }
    r->ecx = (uint32_t)(int32_t)(int8_t)(r->edx & 0xff);
    if ((int32_t)r->ecx <= (int32_t)r->eax)
    {
        goto at_4266cf;
    }
    if ((uint8_t)rd8(r, r->ebp - 0x14) != (uint8_t)0xff)
    {
        goto at_4266cf;
    }
    r->edi = rd32(r, r->ebp - 0x20);
    r->ecx = (uint32_t)(int32_t)(int8_t)(r->edx & 0xff);
    if (r->ecx == r->edi)
    {
        goto at_4268ab;
    }
    if (r->ecx == rd32(r, r->ebp - 0x28))
    {
        goto at_4268bb;
    }
    if (r->ecx == rd32(r, r->ebp - 0x24))
    {
        goto at_4268ce;
    }
at_4266cf:
    if (r->eax != 0xffffffffu)
    {
        goto at_4267a9;
    }
    r->ecx = (uint32_t)(int32_t)(int8_t)(r->ebx & 0xff);
    if ((int32_t)r->ecx <= (int32_t)r->eax)
    {
        goto at_426705;
    }
    if ((uint8_t)rd8(r, r->ebp - 0x10) != (uint8_t)0xff)
    {
        goto at_426705;
    }
    r->esi = rd32(r, r->ebp - 0x20);
    r->ecx = (uint32_t)(int32_t)(int8_t)(r->ebx & 0xff);
    if (r->ecx == r->esi)
    {
        goto at_4268ce;
    }
    if (r->ecx == rd32(r, r->ebp - 0x28))
    {
        goto at_4268ab;
    }
    if (r->ecx == rd32(r, r->ebp - 0x24))
    {
        goto at_4268bb;
    }
at_426705:
    if (r->eax != 0xffffffffu)
    {
        goto at_4267a9;
    }
    r->ecx = rd32(r, r->ebp - 0x13);
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x18);
    if ((int32_t)r->ecx <= (int32_t)r->eax)
    {
        goto at_426740;
    }
    if ((uint8_t)((r->ebx & 0xff)) != (uint8_t)0xff)
    {
        goto at_426740;
    }
    r->ecx = rd32(r, r->ebp - 0x13);
    r->edi = rd32(r, r->ebp - 0x20);
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x18);
    if (r->ecx == r->edi)
    {
        goto at_4268ce;
    }
    if (r->ecx == rd32(r, r->ebp - 0x28))
    {
        goto at_4268ab;
    }
    if (r->ecx == rd32(r, r->ebp - 0x24))
    {
        goto at_4268bb;
    }
at_426740:
    if (r->eax != 0xffffffffu)
    {
        goto at_4267a9;
    }
    r->ecx = (uint32_t)(int32_t)(int8_t)((r->edx >> 8) & 0xff);
    if ((int32_t)r->ecx <= (int32_t)r->eax)
    {
        goto at_426772;
    }
    if ((uint8_t)rd8(r, r->ebp - 0x1c) != (uint8_t)0xff)
    {
        goto at_426772;
    }
    r->edi = rd32(r, r->ebp - 0x20);
    r->ecx = (uint32_t)(int32_t)(int8_t)((r->edx >> 8) & 0xff);
    if (r->ecx == r->edi)
    {
        goto at_4268bb;
    }
    if (r->ecx == rd32(r, r->ebp - 0x28))
    {
        goto at_4268ce;
    }
    if (r->ecx == rd32(r, r->ebp - 0x24))
    {
        goto at_4268ab;
    }
at_426772:
    if (r->eax != 0xffffffffu)
    {
        goto at_4267a9;
    }
    r->ecx = rd32(r, r->ebp - 0x1f);
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x18);
    if ((int32_t)r->ecx <= (int32_t)r->eax)
    {
        goto at_4267a9;
    }
    if ((uint8_t)(((r->edx >> 8) & 0xff)) != (uint8_t)0xff)
    {
        goto at_4267a9;
    }
    r->edx = rd32(r, r->ebp - 0x1f);
    r->edi = rd32(r, r->ebp - 0x20);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x18);
    if (r->edx == r->edi)
    {
        goto at_4268bb;
    }
    if (r->edx == rd32(r, r->ebp - 0x28))
    {
        goto at_4268ce;
    }
    if (r->edx == rd32(r, r->ebp - 0x24))
    {
        goto at_4268ab;
    }
at_4267a9:
    if (r->eax == 0xffffffffu)
    {
        goto at_4269be;
    }
    r->edx = rd32(r, r->ebp + 0x8);
    wr32(r, r->edx, r->eax);
    r->edi = rd32(r, r->ebp - 0x8);
    r->esi = rd32(r, r->ebp - 0x4);
    return;
at_4267c0:
    if ((uint8_t)rd8(r, r->ecx + r->ebp - 0x44) == (uint8_t)0xd && !r->port->env.failed)
    {
        goto at_426325;
    }
    r->edi = r->edi + 1;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_426325;
at_4267d1:
    set_low8(&r->edx, rd8(r, r->ebp - 0x44));
    r->eax = 0;
    if ((uint8_t)((r->edx & 0xff)) != (uint8_t)0xd)
    {
        goto at_4267e8;
    }
at_4267db:
    r->eax = r->eax + 1;
    if ((int32_t)r->eax >= (int32_t)0x5)
    {
        goto at_4267e8;
    }
    if ((uint8_t)rd8(r, r->eax + r->ebp - 0x44) == (uint8_t)0xd && !r->port->env.failed)
    {
        goto at_4267db;
    }
at_4267e8:
    if (r->eax != 0x5)
    {
        goto at_426855;
    }
    r->ecx = 0x2;
    r->edi = 0xc;
    wr32(r, r->ebp - 0x30, r->ecx);
at_4267fe:
    r->ebx = 0xffffffffu;
    r->ecx = 0x4;
    r->esi = 0;
at_42680a:
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->esi + r->ebp - 0x44));
    if (r->eax != r->edi)
    {
        goto at_426816;
    }
    r->ebx = r->esi;
at_426816:
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ecx + r->ebp - 0x44));
    if (r->eax != r->edi)
    {
        goto at_426827;
    }
    if (r->ebx != 0xffffffffu)
    {
        goto at_42687c;
    }
at_426825:
    r->ebx = r->ecx;
at_426827:
    r->ecx = r->ecx - 1;
    r->esi = r->esi + 1;
    if (r->ebx != 0xffffffffu)
    {
        goto at_426833;
    }
    if ((int32_t)r->esi < (int32_t)0x2 && !r->port->env.failed)
    {
        goto at_42680a;
    }
at_426833:
    if (r->ebx != 0xffffffffu)
    {
        goto at_426842;
    }
    r->ecx = rd32(r, r->ebp - 0x30);
    if (r->ecx != 0x2)
    {
        goto at_426842;
    }
    r->ebx = r->ecx;
at_426842:
    r->eax = rd32(r, r->ebp - 0x2c);
    wr32(r, r->eax + 0x180, r->ebx);
    r->eax = rd32(r, r->ebp + 0xc);
    wr32(r, r->eax, r->ebx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_42633f;
at_426855:
    wr32(r, r->ebp - 0x30, r->eax);
    r->eax = r->eax + 1;
    r->edi = rd8(r, r->eax + r->ebp - 0x45);
at_42685e:
    if ((int32_t)r->eax >= (int32_t)0x5 && !r->port->env.failed)
    {
        goto at_4267fe;
    }
    if ((uint8_t)rd8(r, r->eax + r->ebp - 0x3c) == (uint8_t)0x0)
    {
        goto at_426879;
    }
    r->edx = 0;
    set_low8(&r->edx, rd8(r, r->eax + r->ebp - 0x44));
    if ((int32_t)r->edx >= (int32_t)r->edi)
    {
        goto at_426879;
    }
    wr32(r, r->ebp - 0x30, r->eax);
    r->edi = r->edx;
at_426879:
    r->eax = r->eax + 1;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_42685e;
at_42687c:
    r->eax = rd32(r, r->ebp - 0x2c);
    r->edx = rd32(r, r->eax + 0x180);
    if (r->ecx != r->edx)
    {
        goto at_42688d;
    }
    r->ebx = r->edx;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_426827;
at_42688d:
    if (r->esi == r->edx && !r->port->env.failed)
    {
        goto at_426827;
    }
    r->edx = 0x2;
    r->eax = 0x598d48;
    call_keep(r, 0x4826c0);
    if ((uint16_t)((r->eax & 0xffff)) != (uint16_t)0x1 && !r->port->env.failed)
    {
        goto at_426827;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_426825;
at_4268ab:
    r->eax = 0;
    r->edx = rd32(r, r->ebp + 0x8);
    wr32(r, r->edx, r->eax);
    r->edi = rd32(r, r->ebp - 0x8);
    r->esi = rd32(r, r->ebp - 0x4);
    return;
at_4268bb:
    r->eax = 0x1;
    r->edx = rd32(r, r->ebp + 0x8);
    wr32(r, r->edx, r->eax);
    r->edi = rd32(r, r->ebp - 0x8);
    r->esi = rd32(r, r->ebp - 0x4);
    return;
at_4268ce:
    r->eax = 0x2;
    r->edx = rd32(r, r->ebp + 0x8);
    wr32(r, r->edx, r->eax);
    r->edi = rd32(r, r->ebp - 0x8);
    r->esi = rd32(r, r->ebp - 0x4);
    return;
at_4268e1:
    if ((int32_t)r->ebx <= (int32_t)0x3)
    {
        goto at_426946;
    }
    r->ebx = r->edx - 0x1;
    r->edx = r->ebx * 4;
    r->edx = r->edx - r->ebx;
    r->edx = r->edx << 0x2;
    r->edx = r->edx + r->ebx;
    r->edx = r->edx + r->ecx;
    set_low8(&r->edx, rd8(r, r->edx + r->ebp - 0x9b));
    wr8(r, r->ebp - 0x18, (r->edx & 0xff));
at_426903:
    r->ebx = r->esi - 0x1;
    r->edx = r->ebx * 4;
    r->edx = r->edx - r->ebx;
    r->edx = r->edx << 0x2;
    r->edx = r->edx + r->ebx;
    r->ebx = r->edx + r->ecx;
    set_low8(&r->edx, rd8(r, r->ebx + r->ebp - 0x9a));
    wr8(r, r->ebp - 0xc, (r->edx & 0xff));
    set_low8(&r->edx, rd8(r, r->ebx + r->ebp - 0x99));
    set_high8(&r->edx, rd8(r, r->ebx + r->ebp - 0x98));
    wr8(r, r->ebp - 0x10, ((r->edx >> 8) & 0xff));
    if ((int32_t)r->ecx >= (int32_t)0xc)
    {
        goto at_42694c;
    }
    set_high8(&r->edx, rd8(r, r->ebx + r->ebp - 0x97));
    wr8(r, r->ebp - 0x1c, ((r->edx >> 8) & 0xff));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4263b7;
at_426946:
    wr8(r, r->ebp - 0x18, 0xfe);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_426903;
at_42694c:
    wr8(r, r->ebp - 0x1c, 0xfe);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4263b7;
at_426955:
    if ((int32_t)r->ecx <= (int32_t)0x3)
    {
        goto at_4269b1;
    }
    r->ebx = r->esi + 0x1;
    wr32(r, r->ebp - 0x34, r->ebx);
    r->edi = rd32(r, r->ebp - 0x34);
    r->ebx = r->ebx << 0x2;
    r->ebx = r->ebx - r->edi;
    r->ebx = r->ebx << 0x2;
    r->ebx = r->ebx + r->edi;
    r->ebx = r->ebx + r->ecx;
    set_high8(&r->edx, rd8(r, r->ebx + r->ebp - 0x9b));
    wr8(r, r->ebp - 0x14, ((r->edx >> 8) & 0xff));
at_426979:
    r->esi = r->esi + 1;
    r->ebx = r->esi * 4;
    r->ebx = r->ebx - r->esi;
    r->ebx = r->ebx << 0x2;
    r->ebx = r->ebx + r->esi;
    r->esi = r->ebx + r->ecx;
    set_low8(&r->ebx, rd8(r, r->esi + r->ebp - 0x9a));
    set_high8(&r->edx, rd8(r, r->esi + r->ebp - 0x99));
    set_high8(&r->ebx, rd8(r, r->esi + r->ebp - 0x98));
    if ((int32_t)r->ecx <= (int32_t)0xc)
    {
        goto at_4269b7;
    }
    set_low8(&r->ecx, rd8(r, r->esi + r->ebp - 0x97));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4263cb;
at_4269b1:
    wr8(r, r->ebp - 0x14, 0xfe);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_426979;
at_4269b7:
    set_low8(&r->ecx, 0xfe);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4263cb;
at_4269be:
    r->edx = 0x3;
    r->eax = 0x598d48;
    call_keep(r, 0x4826c0);
    r->eax = r->eax & 0xffff;
    r->edx = rd32(r, r->ebp + 0x8);
    wr32(r, r->edx, r->eax);
    r->edi = rd32(r, r->ebp - 0x8);
    r->esi = rd32(r, r->ebp - 0x4);
    return;
}

uint32_t vertrix_port_ai_fallback_426240(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x9c
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4 * 6];
    Regs r;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 6);
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
    port_set32(&port, r.ebp, -0x4u, entry->esi);
    port_set32(&port, r.ebp, -0x8u, entry->edi);
    run(&r);
    return port_return(&port, r.eax, r.edx);
}
