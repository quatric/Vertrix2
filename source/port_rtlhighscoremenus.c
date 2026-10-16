#include "port_rtlhighscoremenus.h"

/* At 0x4651b0, places a 0x11b x 0xb4 label box (0x460a40) centred on the screen size read from
 * [0x558c7c] and adds the 'HIGHS' title (0x50e4a7) through 0x460c50. */

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

/* The last count values pushed dropped (the caller's add esp). */
static void drop(Regs *r, unsigned count)
{
    r->pushed = count < r->pushed ? r->pushed - count : 0;
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

/* A cdecl call: every value pushed passed, left for the caller to drop. */
static void call_cdecl(Regs *r, uint32_t target)
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

/* Original 0x4651b0: At 0x4651b0, places a 0x11b x 0xb4 label box (0x460a40) centred on the screen
 * size read from [0x558c7c] and adds the 'HIGHS' title (0x50e4a7) through 0x460c50. It then loops
 * over 5 rows (counter byte at ebp-0x18, cmp at 0x465353). For each row it formats the entry from
 * table_last_change_417840 with rtl_print, gets score text from score_text_417790, and creates
 * items with 0x460df0 and 0x4601c0 ('ABC' at 0x50e4b0). It ends by placing further label boxes,
 * adding a 'RETURN' item (0x50e4b4) through 0x460b60, and calling actor_set_update 0x4ac8f0,
 * list_delete 0x4b5e70 and actor_reset 0x4abd70. Evidence: calls 0x4ca070, 0x460a40, 0x460c50,
 * 0x417840, 0x4cdfb0, 0x460df0, 0x4ca310, 0x417790, 0x4601c0, 0x460b60, 0x4ca000, 0x4ac8f0,
 * 0x4b5e70, 0x4ca210, 0x4abd70; reads 0x558c7c, 0x4f9bf5, 0x4f9bf9, 0x4f7b92; writes 0x532a48.
 * Register-for-register from the listing (0x4651be..0x4657df); labels are the original addresses.
 */
static void run(Regs *r)
{
    wr32(r, r->ebp - 0x98, r->eax);
    r->eax = r->ebp - 0xac;
    r->edx = 0x4ec1ec;
    r->ecx = 0x515aa4;
    r->esi = 0x1;
    r->edi = 0x4d;
    push(r, r->port->env.chain);
    wr32(r, r->eax, pop(r));
    r->port->env.chain = r->eax;
    r->ebx = 0;
    r->eax = r->ebp - 0x90;
    wr32(r, r->ebp - 0xa8, r->edx);
    wr32(r, r->ebp - 0xa4, r->ecx);
    wr32(r, r->ebp - 0xa0, r->ebx);
    call(r, 0x4ca070, 0);
    wr16(r, r->ebp - 0x2c, (r->edi & 0xffff));
    wr16(r, r->ebp - 0x3c, (r->edi & 0xffff));
    r->edx = 0x1a;
    r->ebx = 0x7f;
    r->ecx = 0x11b;
    push(r, 0x1);
    r->eax = rd32(r, 0x558c7c);
    wr32(r, r->ebp - 0xa0, r->esi);
    wr16(r, r->ebp - 0x34, (r->edx & 0xffff));
    r->edx = rd32(r, r->eax + 0x4);
    r->esi = 0xb4;
    r->edx = r->edx - 0x11b;
    wr16(r, r->ebp - 0x4c, (r->ebx & 0xffff));
    r->edx = r->edx >> 0x1;
    wr16(r, r->ebp - 0x44, (r->ecx & 0xffff));
    wr16(r, r->ebp - 0x1c, (r->edx & 0xffff));
    set_low16(&r->edx, rd16(r, r->eax + 0x8));
    wr16(r, r->ebp - 0x40, (r->esi & 0xffff));
    r->edx = r->edx - 0xdc;
    r->edi = rd32(r, r->ebp - 0x1e);
    wr16(r, r->ebp - 0x20, (r->edx & 0xffff));
    r->edx = rd32(r, r->ebp - 0x1c);
    r->edi = (uint32_t)((int32_t)r->edi >> 0x10);
    wr16(r, r->ebp - 0x24, (r->edx & 0xffff));
    set_low16(&r->edx, rd16(r, r->eax + 0x8));
    r->esi = rd32(r, r->ebp - 0x22);
    r->edx = r->edx - 0xc1;
    set_low16(&r->eax, rd16(r, r->eax + 0x8));
    wr32(r, r->ebp - 0x50, r->edx);
    r->eax = r->eax - 0x42;
    r->edx = rd32(r, r->ebp - 0x1c);
    wr16(r, r->ebp - 0x30, (r->eax & 0xffff));
    r->eax = r->edx;
    r->esi = (uint32_t)((int32_t)r->esi >> 0x10);
    r->eax = r->eax + 0x4e;
    push(r, r->esi);
    wr16(r, r->ebp - 0x48, (r->eax & 0xffff));
    r->eax = rd32(r, r->ebp - 0x30);
    push(r, r->edi);
    wr16(r, r->ebp - 0x5c, (r->eax & 0xffff));
    r->eax = r->edx;
    r->ebx = r->edi;
    r->eax = r->eax + 0xce;
    push(r, 0xb4);
    wr16(r, r->ebp - 0x64, (r->eax & 0xffff));
    r->eax = rd32(r, r->ebp - 0x30);
    push(r, 0x11b);
    wr16(r, r->ebp - 0x68, (r->eax & 0xffff));
    r->eax = rd32(r, r->ebp - 0x20);
    wr16(r, r->ebp - 0x38, (r->edx & 0xffff));
    r->eax = r->eax + 0x9;
    r->edx = 0x11;
    r->ecx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = 0x11b;
    call(r, 0x460a40, 5);
    push(r, 0x1);
    r->eax = rd32(r, 0x4f9bf5);
    push(r, 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x18);
    push(r, r->eax);
    push(r, 0x1);
    push(r, 0x1);
    push(r, 0x0);
    push(r, r->esi);
    push(r, r->edi);
    r->ebx = 0x1a;
    push(r, 0xb4);
    r->edx = 0x11b;
    r->ecx = r->edi;
    push(r, 0x11b);
    r->eax = 0x50e4a7;
    r->edi = 0;
    push(r, r->esi);
    wr32(r, r->ebp - 0x6c, r->edi);
    r->edi = r->ebp - 0xc0;
    call(r, 0x460c50, 11);
    r->eax = rd32(r, r->ebp - 0x50);
    r->ebx = 0x19;
    wr16(r, r->ebp - 0x60, (r->eax & 0xffff));
    set_high8(&r->eax, 0);
    r->esi = 0x4fd54c;
    wr8(r, r->ebp - 0x18, ((r->eax >> 8) & 0xff));
    r->eax = rd32(r, r->ebp - 0x1c);
    wr32(r, r->ebp - 0x28, r->ebx);
    r->eax = r->eax + 0x25;
    movs(r, 4);
    movs(r, 4);
    movs(r, 4);
    movs(r, 4);
    movs(r, 4);
    wr16(r, r->ebp - 0x58, (r->eax & 0xffff));
at_46534b:
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ebp - 0x18));
    wr32(r, r->ebp - 0x7c, r->eax);
    if ((int32_t)r->eax >= (int32_t)0x5)
    {
        goto at_465694;
    }
    r->eax = 0;
    r->esi = 0xd;
    set_low8(&r->eax, rd8(r, r->ebp - 0x18));
    wr32(r, r->ebp - 0x78, r->esi);
    call(r, 0x417840, 0);
    r->eax = r->eax & 0xff;
    push(r, r->eax);
    push(r, 0x50e4ad);
    r->eax = r->ebp - 0x90;
    push(r, r->eax);
    r->edi = rd32(r, r->ebp - 0x6c);
    call_cdecl(r, 0x4cdfb0);
    r->eax = rd32(r, r->ebp - 0x22);
    drop(r, 3);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    push(r, r->edi);
    wr32(r, r->ebp - 0x94, r->eax);
    push(r, r->eax);
    r->eax = rd32(r, r->ebp - 0x1e);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    push(r, r->eax);
    push(r, 0xb4);
    push(r, 0x11b);
    push(r, 0x1);
    push(r, 0x0);
    push(r, 0x45c8e0);
    r->ebx = 0x26;
    r->edi = rd32(r, r->ebp - 0x62);
    push(r, 0x10);
    r->edi = (uint32_t)((int32_t)r->edi >> 0x10);
    push(r, 0xa);
    r->ecx = rd32(r, r->ebp - 0x90);
    r->edx = r->edi;
    push(r, 0x0);
    wr32(r, r->ebp - 0x70, r->eax);
    r->eax = rd32(r, r->ebp - 0x26);
    push(r, r->ecx);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->ecx = 0x1a;
    call(r, 0x460df0, 12);
    r->edx = rd32(r, r->eax + 0x160);
    set_low8(&r->ebx, rd8(r, r->ebp - 0x78));
    wr8(r, r->edx + 0x52, (r->ebx & 0xff));
    r->edx = rd32(r, r->eax + 0x160);
    wr8(r, r->edx + 0x95, 0x4);
    r->edx = rd32(r, r->eax + 0x160);
    r->esi = rd32(r, r->ebp - 0x58);
    wr8(r, r->edx + 0x93, 0x1);
    r->edx = rd32(r, r->ebp - 0x7c);
    r->ecx = 0x4c;
    r->edx = r->edx << 0x2;
    r->eax = rd32(r, r->eax + 0x160);
    wr32(r, r->ebp - 0x88, r->edx);
    set_low16(&r->edx, rd16(r, r->edx + r->ebp - 0xc0));
    r->ebx = rd32(r, r->ebp - 0x7c);
    wr16(r, r->eax + 0x4c, (r->edx & 0xffff));
    r->eax = rd32(r, r->ebp - 0x98);
    wr16(r, r->ebp - 0x54, (r->ecx & 0xffff));
    if (r->eax == r->ebx)
    {
        goto at_4655a1;
    }
    r->edx = 0x5332a8;
    r->ecx = rd32(r, r->ebp - 0x88);
    r->eax = r->ebp - 0x90;
    r->edx = r->edx + r->ecx;
    r->ebx = rd32(r, r->ebp - 0x6c);
    call(r, 0x4ca310, 0);
    push(r, r->ebx);
    r->eax = rd32(r, r->ebp - 0x94);
    push(r, r->eax);
    r->edx = rd32(r, r->ebp - 0x70);
    push(r, r->edx);
    push(r, 0xb4);
    push(r, 0x11b);
    push(r, 0x1);
    push(r, 0x0);
    push(r, 0x45c8e0);
    push(r, 0x10);
    r->ecx = rd32(r, r->ebp - 0x90);
    push(r, 0xa);
    r->ebx = 0x4c;
    r->eax = rd32(r, r->ebp - 0x5a);
    push(r, 0x0);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    push(r, r->ecx);
    r->edx = r->edi;
    r->ecx = 0x1a;
    call(r, 0x460df0, 12);
    r->edx = rd32(r, r->eax + 0x160);
    set_low8(&r->ebx, rd8(r, r->ebp - 0x78));
    wr8(r, r->edx + 0x52, (r->ebx & 0xff));
    r->edx = rd32(r, r->eax + 0x160);
    wr8(r, r->edx + 0x95, 0x4);
    r->edx = rd32(r, r->eax + 0x160);
    wr8(r, r->edx + 0x93, 0x1);
    r->edx = rd32(r, r->eax + 0x160);
    r->eax = rd32(r, r->ebp - 0x88);
    set_low16(&r->eax, rd16(r, r->eax + r->ebp - 0xc0));
    wr16(r, r->edx + 0x4c, (r->eax & 0xffff));
at_4654dd:
    r->eax = rd32(r, r->ebp - 0x54);
    r->edi = rd8(r, r->ebp - 0x18);
    r->eax = r->eax - 1;
    r->edx = r->ebp - 0x90;
    r->esi = r->esi + r->eax;
    r->eax = rd32(r, r->edi * 4 + 0x533294);
    r->ebx = rd32(r, r->ebp - 0x6c);
    call(r, 0x417790, 0);
    r->eax = rd32(r, r->ebp - 0x22);
    push(r, r->ebx);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    push(r, r->eax);
    r->eax = rd32(r, r->ebp - 0x1e);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    push(r, r->eax);
    push(r, 0xb4);
    push(r, 0x11b);
    push(r, 0x1);
    push(r, 0x0);
    push(r, 0x45c8e0);
    push(r, 0x10);
    r->ecx = 0x1a;
    r->edx = rd32(r, r->ebp - 0x62);
    push(r, 0xa);
    r->ebx = 0xab;
    r->eax = rd32(r, r->ebp - 0x90);
    push(r, 0x0);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    push(r, r->eax);
    r->eax = (uint32_t)(int32_t)(int16_t)(r->esi & 0xffff);
    call(r, 0x460df0, 12);
    r->edx = rd32(r, r->eax + 0x160);
    set_low8(&r->ebx, rd8(r, r->ebp - 0x78));
    wr8(r, r->edx + 0x52, (r->ebx & 0xff));
    r->edx = rd32(r, r->eax + 0x160);
    wr8(r, r->edx + 0x95, 0x4);
    r->edx = rd32(r, r->eax + 0x160);
    r->esi = rd32(r, r->ebp - 0x60);
    wr8(r, r->edx + 0x93, 0x1);
    set_high8(&r->ecx, rd8(r, r->ebp - 0x18));
    r->eax = rd32(r, r->eax + 0x160);
    set_low16(&r->edx, rd16(r, r->ebp + r->edi * 4 - 0xc0));
    set_high8(&r->ecx, ((r->ecx >> 8) & 0xff) + 1);
    wr16(r, r->eax + 0x4c, (r->edx & 0xffff));
    r->eax = rd32(r, r->ebp - 0x28);
    r->edx = rd32(r, r->ebp - 0x6c);
    r->esi = r->esi + r->eax;
    r->eax = 0x1;
    wr8(r, r->ebp - 0x18, ((r->ecx >> 8) & 0xff));
    r->eax = r->eax - r->edx;
    wr16(r, r->ebp - 0x60, (r->esi & 0xffff));
    wr32(r, r->ebp - 0x6c, r->eax);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_46534b;
at_4655a1:
    set_low8(&r->edx, rd8(r, r->ebp - 0x18));
    if ((uint8_t)((r->edx & 0xff)) != 0)
    {
        goto at_46564c;
    }
    wr32(r, r->ebp - 0x74, 0x417880);
at_4655b3:
    r->edi = rd32(r, r->ebp - 0x6c);
    r->eax = rd32(r, r->ebp - 0x22);
    push(r, r->edi);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    push(r, r->eax);
    r->eax = rd32(r, r->ebp - 0x1e);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    push(r, r->eax);
    push(r, 0xb4);
    push(r, 0x11b);
    push(r, 0x45cc40);
    push(r, 0x50e4b0);
    push(r, 0x3);
    push(r, 0x1);
    push(r, 0x1);
    push(r, 0x0);
    r->ebx = rd32(r, r->ebp - 0x56);
    r->edx = rd32(r, r->ebp - 0x62);
    push(r, 0x10);
    r->ecx = 0x1a;
    r->eax = rd32(r, r->ebp - 0x74);
    push(r, 0xa);
    r->edi = rd8(r, r->ebp - 0x18);
    push(r, r->eax);
    r->eax = 0x5332a8;
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    r->eax = rd32(r, r->eax + r->edi * 4);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    push(r, r->eax);
    r->eax = (uint32_t)(int32_t)(int16_t)(r->esi & 0xffff);
    call(r, 0x4601c0, 15);
    r->edx = rd32(r, r->eax + 0x160);
    set_low8(&r->ebx, rd8(r, r->ebp - 0x78));
    wr8(r, r->edx + 0x52, (r->ebx & 0xff));
    r->edx = rd32(r, r->eax + 0x160);
    wr8(r, r->edx + 0x95, 0x4);
    r->edx = rd32(r, r->eax + 0x160);
    wr8(r, r->edx + 0x93, 0x1);
    r->eax = rd32(r, r->eax + 0x160);
    set_low16(&r->edx, rd16(r, r->ebp + r->edi * 4 - 0xc0));
    wr16(r, r->eax + 0x4c, (r->edx & 0xffff));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4654dd;
at_46564c:
    if ((uint8_t)((r->edx & 0xff)) != (uint8_t)0x1)
    {
        goto at_46565d;
    }
    wr32(r, r->ebp - 0x74, 0x417890);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4655b3;
at_46565d:
    if ((uint8_t)((r->edx & 0xff)) != (uint8_t)0x2)
    {
        goto at_46566e;
    }
    wr32(r, r->ebp - 0x74, 0x4178a0);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4655b3;
at_46566e:
    if ((uint8_t)((r->edx & 0xff)) != (uint8_t)0x3)
    {
        goto at_46567f;
    }
    wr32(r, r->ebp - 0x74, 0x4178b0);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4655b3;
at_46567f:
    if ((uint8_t)((r->edx & 0xff)) != (uint8_t)0x4 && !r->port->env.failed)
    {
        goto at_4655b3;
    }
    wr32(r, r->ebp - 0x74, 0x4178c0);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4655b3;
at_465694:
    r->edx = rd32(r, r->ebp - 0x6c);
    r->eax = rd32(r, r->ebp - 0x22);
    r->edi = rd32(r, r->ebp - 0x1e);
    r->esi = rd32(r, r->ebp - 0x46);
    r->ecx = rd32(r, r->ebp - 0x32);
    r->ebx = rd32(r, r->ebp - 0x3a);
    push(r, r->edx);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->edi = (uint32_t)((int32_t)r->edi >> 0x10);
    r->esi = (uint32_t)((int32_t)r->esi >> 0x10);
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    push(r, r->eax);
    wr32(r, r->ebp - 0x8c, r->eax);
    r->eax = rd32(r, r->ebp - 0x42);
    push(r, r->edi);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->edx = 0x11;
    push(r, r->eax);
    wr32(r, r->ebp - 0x84, r->eax);
    r->eax = rd32(r, r->ebp - 0x2e);
    push(r, r->esi);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x460a40, 5);
    push(r, 0x1);
    push(r, 0x0);
    r->eax = rd32(r, 0x4f9bf9);
    push(r, 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x18);
    push(r, r->eax);
    r->eax = rd32(r, r->ebp - 0x6c);
    push(r, r->eax);
    r->edx = rd32(r, r->ebp - 0x8c);
    push(r, r->edx);
    push(r, r->edi);
    r->ecx = rd32(r, r->ebp - 0x84);
    push(r, r->ecx);
    r->eax = rd32(r, r->ebp - 0x5e);
    push(r, r->esi);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    push(r, r->eax);
    r->eax = rd32(r, r->ebp - 0x4a);
    r->ebx = 0x1;
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->edx = rd32(r, 0x4f7b92);
    push(r, r->eax);
    r->eax = rd32(r, r->ebp - 0x36);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->ecx = rd32(r, r->ebp - 0x4e);
    push(r, r->eax);
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    r->eax = 0x50e4b4;
    call(r, 0x460b60, 12);
    r->ebx = rd32(r, r->ebp - 0x6c);
    r->eax = rd32(r, r->ebp - 0x8c);
    push(r, r->ebx);
    r->edx = rd32(r, r->ebp - 0x84);
    r->ecx = rd32(r, r->ebp - 0x6a);
    push(r, r->eax);
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    push(r, r->edi);
    r->ebx = rd32(r, r->ebp - 0x66);
    r->eax = rd32(r, r->ebp - 0x3e);
    push(r, r->edx);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    push(r, r->esi);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->edx = 0x11;
    call(r, 0x460a40, 5);
    r->eax = 0x15c;
    call(r, 0x4ca000, 0);
    if (r->eax != 0)
    {
        goto at_4657c1;
    }
at_465770:
    r->ebx = r->eax;
    r->edx = 0x45c6e0;
    r->eax = r->ebx;
    call(r, 0x4ac8f0, 0);
    r->eax = 0x54671c;
    r->edx = r->ebx;
    r->ecx = 0;
    call(r, 0x4b5e70, 0);
    r->eax = r->ebp - 0x90;
    wr32(r, 0x532a48, r->ecx);
    r->edx = 0;
    wr32(r, r->ebp - 0xa0, r->ecx);
    call(r, 0x4ca210, 0);
    r->eax = rd32(r, r->ebp - 0xac);
    wr32(r, r->ebp - 0xa0, r->ecx);
    r->port->env.chain = r->eax;
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4657c1:
    r->ecx = 0x2;
    r->ebx = 0x1;
    wr32(r, r->ebp - 0x80, r->eax);
    wr32(r, r->ebp - 0xa0, r->ecx);
    call(r, 0x4abd70, 0);
    wr32(r, r->ebp - 0xa0, r->ebx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_465770;
}

uint32_t vertrix_port_high_scores_menu_build_4651b0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0xc4
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
