#include "port_rtlkeysmenus.h"

/* The routine at 0x4627a0 builds the key-configuration menu. */

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

/* Original 0x4627a0: The routine at 0x4627a0 builds the key-configuration menu. It places a 'KEYS'
 * title (0x50e3b6) and 'PLAYER1'/'PLAYER2' column headers (0x50e3bb, 0x50e3c3). Under each header
 * it adds LEFT, RIGHT, PERMUTE and DOWN rows (0x50e3cb-0x50e3de and 0x50e3e3-0x50e3f6), then a
 * PAUSE row (0x50e3fb) and a 'DELAY' item (0x50e401). It uses label_box_place, menu_item_pair and
 * menu_item_make, and positions the items from the screen size at [0x558c7c]+4/+8. Three labels
 * come from vertrix_port_key_name_416c10, and three strings come from table lookups of 0x532b64,
 * 0x532b80 and 0x532b84. The only caller is vertrix_native_game_frame at 0x41bf7a. Evidence: calls
 * 0x4ca070, 0x415ed0, 0x4ca370, 0x460a40, 0x460c50, 0x460ad0, 0x4ca280, 0x416c10, 0x460df0,
 * 0x4ca210, 0x460fa0, 0x460b60, 0x4ca000, 0x4ac8f0, 0x4b5e70, 0x4cda10, 0x4abd70; reads 0x532b64,
 * 0x532b80, 0x532b84, 0x558c7c, 0x4f9bf5, 0x4f9bfa, 0x4f9bf9, 0x4f7b9a; writes 0x532b68, 0x532a48.
 * Register-for-register from the listing (0x4627ae..0x4633ad); labels are the original addresses.
 */
static void run(Regs *r)
{
    r->eax = r->ebp - 0x12c;
    r->edx = 0x4ec1ec;
    r->ecx = 0x51597c;
    r->esi = 0x1;
    r->edi = 0x2;
    push(r, r->port->env.chain);
    wr32(r, r->eax, pop(r));
    r->port->env.chain = r->eax;
    r->ebx = 0;
    r->eax = r->ebp - 0x10c;
    wr32(r, r->ebp - 0x128, r->edx);
    wr32(r, r->ebp - 0x124, r->ecx);
    wr32(r, r->ebp - 0x120, r->ebx);
    call(r, 0x4ca070, 0);
    r->eax = r->ebp - 0x108;
    r->ecx = 0x5;
    wr32(r, r->ebp - 0x120, r->esi);
    call(r, 0x4ca070, 0);
    r->eax = r->ebp - 0x104;
    wr32(r, r->ebp - 0x120, r->edi);
    call(r, 0x4ca070, 0);
    r->eax = 0x3;
    r->ebx = 0x4f8134;
    wr32(r, r->ebp - 0x120, r->eax);
    r->eax = rd32(r, 0x532b64);
    r->edx = 0x532b20;
    wr32(r, 0x532b68, r->eax);
    call(r, 0x415ed0, 0);
    r->ecx = 0x6;
    r->edx = r->eax;
    r->eax = r->ebp - 0x10c;
    r->ebx = 0x4f8148;
    call(r, 0x4ca370, 0);
    r->edx = 0x532b08;
    r->eax = rd32(r, 0x532b80);
    call(r, 0x415ed0, 0);
    r->ecx = 0x6;
    r->edx = r->eax;
    r->eax = r->ebp - 0x108;
    r->ebx = 0x4f8148;
    call(r, 0x4ca370, 0);
    r->edx = 0x532b08;
    r->eax = rd32(r, 0x532b84);
    wr32(r, r->ebp - 0xec, r->esi);
    call(r, 0x415ed0, 0);
    r->ebx = 0x1a;
    r->edx = r->eax;
    r->eax = r->ebp - 0x104;
    r->ecx = 0;
    call(r, 0x4ca370, 0);
    wr32(r, r->ebp - 0xe0, r->ecx);
    wr16(r, r->ebp - 0x70, (r->ebx & 0xffff));
    wr16(r, r->ebp - 0xb8, (r->ebx & 0xffff));
    wr16(r, r->ebp - 0xac, (r->ebx & 0xffff));
    r->edx = 0xffffffffu;
    r->eax = 0x7f;
    wr32(r, r->ebp - 0x18, r->edx);
    wr16(r, r->ebp - 0x28, (r->eax & 0xffff));
    r->edx = 0xa9;
    r->eax = rd32(r, 0x558c7c);
    wr32(r, r->ebp - 0x84, r->edx);
    wr32(r, r->ebp - 0x8c, r->edx);
    wr16(r, r->ebp - 0x88, (r->edx & 0xffff));
    wr16(r, r->ebp - 0x30, (r->edx & 0xffff));
    wr16(r, r->ebp - 0x98, (r->edx & 0xffff));
    wr16(r, r->ebp - 0xc8, (r->edx & 0xffff));
    wr16(r, r->ebp - 0x78, (r->edx & 0xffff));
    wr16(r, r->ebp - 0x6c, (r->edx & 0xffff));
    r->edx = rd32(r, r->eax + 0x4);
    wr16(r, r->ebp - 0x9c, (r->ebx & 0xffff));
    r->edx = r->edx - 0x1f9;
    set_low16(&r->eax, rd16(r, r->eax + 0x8));
    r->edx = r->edx >> 0x1;
    r->eax = r->eax - 0x10d;
    wr16(r, r->ebp - 0x34, (r->edx & 0xffff));
    wr16(r, r->ebp - 0x38, (r->eax & 0xffff));
    r->edx = r->edx + 0xa8;
    wr16(r, r->ebp - 0x50, (r->edx & 0xffff));
    r->edx = rd32(r, r->ebp - 0x34);
    r->edx = r->edx + 0x150;
    wr16(r, r->ebp - 0x54, (r->edx & 0xffff));
    r->edx = rd32(r, r->ebp - 0x34);
    wr16(r, r->ebp - 0x40, (r->edx & 0xffff));
    r->edx = rd32(r, r->ebp - 0x38);
    r->edx = r->edx + r->ebx;
    wr16(r, r->ebp - 0x58, (r->edx & 0xffff));
    r->edx = rd32(r, r->ebp - 0x50);
    wr16(r, r->ebp - 0x3c, (r->edx & 0xffff));
    r->edx = rd32(r, r->ebp - 0x54);
    wr16(r, r->ebp - 0x44, (r->edx & 0xffff));
    r->edx = rd32(r, r->ebp - 0x34);
    wr16(r, r->ebp - 0x74, (r->edx & 0xffff));
    r->edx = rd32(r, r->ebp - 0x38);
    r->edx = r->edx + 0x97;
    wr16(r, r->ebp - 0x4c, (r->edx & 0xffff));
    r->edx = rd32(r, r->ebp - 0x50);
    wr16(r, r->ebp - 0xb4, (r->edx & 0xffff));
    r->edx = rd32(r, r->ebp - 0x4c);
    wr16(r, r->ebp - 0x20, (r->edx & 0xffff));
    r->edx = rd32(r, r->ebp - 0x54);
    wr16(r, r->ebp - 0x1c, (r->edx & 0xffff));
    r->edx = rd32(r, r->ebp - 0x4c);
    wr16(r, r->ebp - 0xa0, (r->edx & 0xffff));
    r->edx = rd32(r, r->ebp - 0x34);
    wr16(r, r->ebp - 0x60, (r->edx & 0xffff));
    r->edx = rd32(r, r->ebp - 0x4c);
    r->edx = r->edx + 0x19;
    wr16(r, r->ebp - 0x48, (r->edx & 0xffff));
    r->edx = rd32(r, r->ebp - 0x50);
    wr16(r, r->ebp - 0xc4, (r->edx & 0xffff));
    r->edx = rd32(r, r->ebp - 0x48);
    wr16(r, r->ebp - 0x94, (r->edx & 0xffff));
    r->edx = rd32(r, r->ebp - 0x54);
    wr16(r, r->ebp - 0x90, (r->edx & 0xffff));
    r->edx = rd32(r, r->ebp - 0x48);
    wr16(r, r->ebp - 0xa4, (r->edx & 0xffff));
    r->edx = rd32(r, r->ebp - 0x34);
    wr16(r, r->ebp - 0x80, (r->edx & 0xffff));
    r->edx = rd32(r, r->ebp - 0x48);
    r->edx = r->edx + 0x1b;
    wr16(r, r->ebp - 0x5c, (r->edx & 0xffff));
    r->edx = rd32(r, r->ebp - 0x34);
    r->edx = r->edx + 0xbd;
    wr16(r, r->ebp - 0x68, (r->edx & 0xffff));
    r->edx = rd32(r, r->ebp - 0x5c);
    wr16(r, r->ebp - 0xa8, (r->edx & 0xffff));
    r->edx = rd32(r, r->ebp - 0x34);
    r->ecx = 0xbc;
    r->edx = r->edx + 0x13d;
    r->eax = r->eax + 1;
    wr16(r, r->ebp - 0xc0, (r->edx & 0xffff));
    r->edx = rd32(r, r->ebp - 0x5c);
    push(r, r->esi);
    wr16(r, r->ebp - 0xbc, (r->edx & 0xffff));
    r->edx = rd32(r, r->ebp - 0x3a);
    r->esi = rd32(r, r->ebp - 0x36);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    wr16(r, r->ebp - 0xb0, (r->ecx & 0xffff));
    push(r, r->edx);
    r->esi = (uint32_t)((int32_t)r->esi >> 0x10);
    wr16(r, r->ebp - 0x64, (r->ecx & 0xffff));
    push(r, r->esi);
    r->edi = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = 0xa9;
    push(r, 0xe5);
    r->ecx = r->edi;
    r->ebx = r->esi;
    push(r, 0x1f9);
    wr32(r, r->ebp - 0xe4, r->edx);
    r->edx = 0x1a;
    call(r, 0x460a40, 5);
    push(r, 0x1);
    r->eax = rd32(r, 0x4f9bf5);
    push(r, 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x18);
    push(r, r->eax);
    push(r, 0x1);
    push(r, 0x1);
    push(r, 0x0);
    r->eax = rd32(r, r->ebp - 0xe4);
    push(r, r->eax);
    push(r, r->esi);
    push(r, 0xe5);
    push(r, 0x1f9);
    r->ebx = 0x1a;
    r->edx = 0xa9;
    push(r, r->edi);
    r->ecx = r->esi;
    r->eax = 0x50e3b6;
    call(r, 0x460c50, 11);
    push(r, 0x1);
    r->edx = rd32(r, r->ebp - 0xe4);
    push(r, r->edx);
    r->eax = rd32(r, r->ebp - 0x52);
    r->ecx = r->edi;
    push(r, r->esi);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    push(r, 0xe5);
    r->edx = 0x1a;
    wr32(r, r->ebp - 0xf0, r->eax);
    push(r, 0x1f9);
    r->ebx = r->eax;
    r->eax = 0xa9;
    call(r, 0x460ad0, 5);
    push(r, 0x1);
    r->ecx = rd32(r, r->ebp - 0xe4);
    push(r, r->ecx);
    r->eax = rd32(r, r->ebp - 0x56);
    r->edx = 0x1a;
    push(r, r->esi);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    push(r, 0xe5);
    wr32(r, r->ebp - 0xf4, r->eax);
    r->ecx = r->edi;
    push(r, 0x1f9);
    r->ebx = r->eax;
    r->eax = 0xa9;
    call(r, 0x460ad0, 5);
    push(r, 0x1);
    r->eax = rd32(r, 0x4f9bf5);
    push(r, 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x18);
    push(r, r->eax);
    push(r, 0x1);
    push(r, 0x1);
    push(r, 0xa);
    r->ebx = rd32(r, r->ebp - 0xe4);
    push(r, r->ebx);
    push(r, r->esi);
    push(r, 0xe5);
    push(r, 0x1f9);
    r->ecx = rd32(r, r->ebp - 0xf0);
    r->edx = 0xa9;
    push(r, r->edi);
    r->eax = 0x50e3bb;
    r->ebx = 0x1a;
    call(r, 0x460c50, 11);
    push(r, 0x1);
    r->eax = rd32(r, 0x4f9bf5);
    push(r, 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x18);
    push(r, r->eax);
    push(r, 0x1);
    push(r, 0x1);
    push(r, 0xa);
    r->eax = rd32(r, r->ebp - 0xe4);
    push(r, r->eax);
    push(r, r->esi);
    push(r, 0xe5);
    push(r, 0x1f9);
    r->ecx = rd32(r, r->ebp - 0xf4);
    r->ebx = 0x1a;
    push(r, r->edi);
    r->edx = 0xa9;
    r->eax = 0x50e3c3;
    call(r, 0x460c50, 11);
    push(r, 0x1);
    r->edx = rd32(r, r->ebp - 0xe4);
    push(r, r->edx);
    push(r, r->esi);
    r->ecx = rd32(r, r->ebp - 0x5a);
    push(r, 0xe5);
    r->eax = 0xa9;
    r->ebx = r->esi;
    push(r, 0x1f9);
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    r->edx = 0x7e;
    call(r, 0x460ad0, 5);
    r->eax = r->ebp - 0x174;
    r->ecx = 0x513e60;
    r->ebx = 0x4;
    r->edi = r->ebp - 0x174;
    r->edx = 0x50e3cb;
    r->esi = 0;
    wr32(r, r->ebp - 0x114, r->ecx);
    wr32(r, r->ebp - 0x110, r->esi);
    r->ecx = 0x9;
    r->esi = 0x54680c;
    wr32(r, r->ebp - 0x118, r->eax);
    wr32(r, r->ebp - 0x120, r->ebx);
    rep_movs(r, 4);
    call(r, 0x4ca280, 0);
    r->edi = 0x1;
    r->edx = 0x50e3d0;
    r->eax = r->ebp - 0x170;
    wr32(r, r->ebp - 0x110, r->edi);
    call(r, 0x4ca280, 0);
    r->eax = 0x2;
    r->edx = 0x50e3d6;
    wr32(r, r->ebp - 0x110, r->eax);
    r->eax = r->ebp - 0x16c;
    r->esi = 0x6;
    call(r, 0x4ca280, 0);
    r->edx = 0x3;
    r->eax = r->ebp - 0x168;
    wr32(r, r->ebp - 0x110, r->edx);
    r->edx = 0x50e3de;
    r->edi = 0x7;
    call(r, 0x4ca280, 0);
    r->edx = 0x50e3e3;
    r->eax = r->ebp - 0x164;
    wr32(r, r->ebp - 0x110, r->ebx);
    call(r, 0x4ca280, 0);
    r->ebx = 0x5;
    r->edx = 0x50e3e8;
    r->eax = r->ebp - 0x160;
    wr32(r, r->ebp - 0x110, r->ebx);
    call(r, 0x4ca280, 0);
    r->edx = 0x50e3ee;
    r->eax = r->ebp - 0x15c;
    wr32(r, r->ebp - 0x110, r->esi);
    call(r, 0x4ca280, 0);
    r->ebx = 0;
    r->edx = 0x50e3f6;
    r->eax = r->ebp - 0x158;
    wr32(r, r->ebp - 0x110, r->edi);
    call(r, 0x4ca280, 0);
    wr32(r, r->ebp - 0xd4, r->ebx);
    r->eax = 0x8;
    r->edx = 0x50e3fb;
    wr32(r, r->ebp - 0x110, r->eax);
    r->eax = r->ebp - 0x154;
    r->edi = r->ebp - 0x198;
    call(r, 0x4ca280, 0);
    r->edx = 0x9;
    r->eax = rd32(r, r->ebp - 0x58);
    wr32(r, r->ebp - 0x120, r->esi);
    r->esi = 0x4fd504;
    r->ecx = r->edx;
    wr16(r, r->ebp - 0x7c, (r->eax & 0xffff));
    wr16(r, r->ebp - 0x24, (r->eax & 0xffff));
    wr16(r, r->ebp - 0x2c, (r->eax & 0xffff));
    rep_movs(r, 4);
    r->eax = r->ebp - 0x174;
    r->edi = r->ebp - 0x150;
    r->esi = 0x4fd528;
    r->ecx = r->edx;
    wr32(r, r->ebp - 0x110, r->edx);
    wr32(r, r->ebp - 0xcc, r->eax);
    rep_movs(r, 4);
at_462d0f:
    push(r, 0x1);
    r->eax = rd32(r, 0x4f9bf5);
    push(r, 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x18);
    push(r, r->eax);
    push(r, 0x1);
    push(r, 0x0);
    r->edi = rd32(r, r->ebp - 0x3a);
    push(r, 0xa);
    r->edi = (uint32_t)((int32_t)r->edi >> 0x10);
    r->eax = rd32(r, r->ebp - 0x36);
    push(r, r->edi);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    push(r, r->eax);
    push(r, 0xe5);
    wr32(r, r->ebp - 0xd0, r->eax);
    r->eax = rd32(r, r->ebp - 0x7e);
    push(r, 0x1f9);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    push(r, r->eax);
    r->eax = rd32(r, r->ebp - 0x42);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->ebx = 0x1a;
    wr32(r, r->ebp - 0xdc, r->eax);
    r->eax = rd32(r, r->ebp - 0xcc);
    r->edx = 0xa9;
    r->ecx = rd32(r, r->ebp - 0xdc);
    r->eax = rd32(r, r->eax);
    call(r, 0x460c50, 11);
    push(r, 0x0);
    push(r, r->edi);
    r->eax = rd32(r, r->ebp - 0xd0);
    push(r, r->eax);
    push(r, 0xe5);
    push(r, 0x1f9);
    push(r, 0x1);
    push(r, 0x0);
    r->esi = rd32(r, r->ebp - 0xd4);
    r->eax = rd32(r, 0x4f9bfa);
    push(r, 0x448810);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x18);
    push(r, 0x10);
    r->esi = r->esi << 0x2;
    push(r, r->eax);
    r->edx = rd32(r, r->esi + r->ebp - 0x198);
    push(r, r->edx);
    r->edx = rd32(r, r->esi + r->ebp - 0x150);
    set_low16(&r->edx, rd16(r, r->edx));
    r->eax = r->ebp - 0xfc;
    r->edx = r->edx & 0xffff;
    r->ecx = 0x7;
    call(r, 0x416c10, 0);
    wr32(r, r->ebp - 0x120, r->ecx);
    r->eax = rd32(r, r->eax);
    r->edx = rd32(r, r->ebp - 0x26);
    r->ecx = 0x1a;
    push(r, r->eax);
    r->eax = rd32(r, r->ebp - 0x3e);
    r->ebx = 0xa9;
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    wr32(r, r->ebp - 0xd8, r->eax);
    call(r, 0x460df0, 12);
    r->ebx = 0x6;
    r->eax = r->ebp - 0xfc;
    r->edx = 0;
    wr32(r, r->ebp - 0x120, r->ebx);
    call(r, 0x4ca210, 0);
    push(r, 0x0);
    push(r, r->edi);
    r->edx = rd32(r, r->ebp - 0xd0);
    push(r, r->edx);
    push(r, 0xe5);
    push(r, 0x1f9);
    push(r, 0x1);
    push(r, 0x0);
    push(r, 0x448810);
    r->eax = rd32(r, 0x4f9bfa);
    wr32(r, r->ebp - 0x120, r->ebx);
    push(r, 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x18);
    r->edx = rd32(r, r->esi + r->ebp - 0x140);
    push(r, r->eax);
    r->ecx = rd32(r, r->esi + r->ebp - 0x188);
    set_low16(&r->edx, rd16(r, r->edx));
    push(r, r->ecx);
    r->eax = r->ebp - 0xf8;
    r->ebx = 0x9;
    r->edx = r->edx & 0xffff;
    r->ecx = 0x1a;
    call(r, 0x416c10, 0);
    wr32(r, r->ebp - 0x120, r->ebx);
    r->edx = rd32(r, r->ebp - 0x2e);
    r->eax = rd32(r, r->eax);
    r->ebx = 0xa9;
    push(r, r->eax);
    r->eax = rd32(r, r->ebp - 0x46);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->esi = 0x6;
    call(r, 0x460df0, 12);
    r->eax = r->ebp - 0xf8;
    r->ebx = rd32(r, r->ebp - 0x2c);
    r->ecx = rd32(r, r->ebp - 0xd4);
    r->edx = 0;
    wr32(r, r->ebp - 0x120, r->esi);
    call(r, 0x4ca210, 0);
    r->eax = rd32(r, r->ebp - 0x7c);
    r->edx = rd32(r, r->ebp - 0x24);
    r->ebx = r->ebx + 0x19;
    wr32(r, r->ebp - 0x120, r->esi);
    r->ecx = r->ecx + 1;
    r->eax = r->eax + 0x19;
    r->edx = r->edx + 0x19;
    wr16(r, r->ebp - 0x2c, (r->ebx & 0xffff));
    wr16(r, r->ebp - 0x24, (r->edx & 0xffff));
    r->edx = rd32(r, r->ebp - 0xcc);
    wr32(r, r->ebp - 0xd4, r->ecx);
    r->edx = r->edx + 0x4;
    wr16(r, r->ebp - 0x7c, (r->eax & 0xffff));
    wr32(r, r->ebp - 0xcc, r->edx);
    if ((int32_t)r->ecx < (int32_t)0x4 && !r->port->env.failed)
    {
        goto at_462d0f;
    }
    push(r, 0x1);
    r->eax = rd32(r, 0x4f9bf5);
    push(r, 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x18);
    push(r, r->eax);
    r->esi = rd32(r, r->ebp - 0xec);
    push(r, r->esi);
    push(r, 0x0);
    push(r, 0xa);
    push(r, r->edi);
    r->eax = rd32(r, r->ebp - 0xd0);
    push(r, r->eax);
    push(r, 0xe5);
    r->eax = rd32(r, r->ebp - 0x7e);
    push(r, 0x1f9);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->ecx = rd32(r, r->ebp - 0xdc);
    push(r, r->eax);
    r->eax = r->ebp - 0x174;
    r->ebx = 0x1a;
    r->edx = 0xa9;
    r->eax = rd32(r, r->eax + 0x20);
    call(r, 0x460c50, 11);
    r->edx = rd32(r, r->ebp - 0xe0);
    push(r, r->edx);
    push(r, r->edi);
    r->ecx = rd32(r, r->ebp - 0xd0);
    push(r, r->ecx);
    push(r, 0xe5);
    push(r, 0x1f9);
    push(r, 0x1);
    push(r, 0x0);
    push(r, 0x448810);
    r->eax = rd32(r, 0x4f9bfa);
    push(r, 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x18);
    r->edx = rd32(r, r->ebp - 0x130);
    push(r, r->eax);
    r->ebx = rd32(r, r->ebp - 0x178);
    set_low16(&r->edx, rd16(r, r->edx));
    push(r, r->ebx);
    r->eax = r->ebp - 0x100;
    r->edx = r->edx & 0xffff;
    r->esi = 0xb;
    call(r, 0x416c10, 0);
    wr32(r, r->ebp - 0x120, r->esi);
    r->eax = rd32(r, r->eax);
    r->ecx = rd32(r, r->ebp - 0x18);
    r->esi = rd32(r, r->ebp - 0x8c);
    push(r, r->eax);
    r->eax = rd32(r, r->ebp - 0x84);
    r->edx = rd32(r, r->ebp - 0x26);
    r->eax = r->eax + r->ecx;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = r->eax + r->esi;
    r->ecx = 0x1a;
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = rd32(r, r->ebp - 0xd8);
    r->esi = rd32(r, r->ebp - 0x76);
    call(r, 0x460df0, 12);
    r->esi = (uint32_t)((int32_t)r->esi >> 0x10);
    r->eax = 0x6;
    r->ecx = rd32(r, r->ebp - 0xec);
    r->edx = 0;
    wr32(r, r->ebp - 0x120, r->eax);
    r->eax = r->ebp - 0x100;
    r->ebx = rd32(r, r->ebp - 0xd0);
    call(r, 0x4ca210, 0);
    r->edx = 0x6;
    push(r, r->ecx);
    r->eax = rd32(r, r->ebp - 0x4e);
    wr32(r, r->ebp - 0x120, r->edx);
    push(r, r->edi);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    push(r, r->ebx);
    r->edx = rd32(r, r->ebp - 0x72);
    wr32(r, r->ebp - 0xf0, r->eax);
    push(r, 0xe5);
    r->eax = rd32(r, r->ebp - 0x8a);
    r->ecx = rd32(r, r->ebp - 0xf0);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    push(r, 0x1f9);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->ebx = r->esi;
    wr32(r, r->ebp - 0xf4, r->eax);
    call(r, 0x460ad0, 5);
    push(r, 0x1);
    r->eax = rd32(r, 0x4f9bf5);
    push(r, 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x18);
    push(r, r->eax);
    r->eax = rd32(r, r->ebp - 0xec);
    push(r, r->eax);
    push(r, 0x0);
    push(r, 0xa);
    push(r, r->edi);
    r->edx = rd32(r, r->ebp - 0xd0);
    push(r, r->edx);
    push(r, 0xe5);
    r->ecx = rd32(r, r->ebp - 0xf0);
    push(r, 0x1f9);
    r->ebx = 0x1a;
    r->eax = 0x50e401;
    push(r, r->ecx);
    r->edx = rd32(r, r->ebp - 0xf4);
    r->ecx = r->esi;
    call(r, 0x460c50, 11);
    r->ebx = rd32(r, r->ebp - 0xe0);
    push(r, r->ebx);
    push(r, r->edi);
    r->esi = rd32(r, r->ebp - 0xd0);
    push(r, r->esi);
    push(r, 0xe5);
    push(r, 0x1f9);
    push(r, 0x1);
    push(r, 0x0);
    r->eax = rd32(r, 0x4f9bfa);
    push(r, 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x18);
    push(r, r->eax);
    push(r, 0x447f40);
    push(r, 0x0);
    push(r, 0x416bd0);
    push(r, 0x2);
    push(r, 0x0);
    push(r, 0x6);
    push(r, 0x532b08);
    r->eax = rd32(r, r->ebp - 0x108);
    r->ebx = rd32(r, r->ebp - 0x32);
    r->edx = rd32(r, r->ebp - 0x22);
    r->ecx = 0x1a;
    push(r, r->eax);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    r->eax = rd32(r, r->ebp - 0xb6);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x460fa0, 17);
    r->edx = rd32(r, r->ebp - 0xe0);
    push(r, r->edx);
    push(r, r->edi);
    push(r, r->esi);
    push(r, 0xe5);
    push(r, 0x1f9);
    push(r, 0x1);
    push(r, 0x0);
    r->eax = rd32(r, 0x4f9bfa);
    push(r, 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x18);
    push(r, r->eax);
    push(r, 0x447f40);
    push(r, 0x0);
    push(r, 0x416bf0);
    push(r, 0x2);
    push(r, 0x0);
    push(r, 0x6);
    push(r, 0x532b08);
    r->ebx = rd32(r, r->ebp - 0x104);
    r->edx = rd32(r, r->ebp - 0xa2);
    r->eax = rd32(r, r->ebp - 0x1e);
    r->ecx = 0x1a;
    push(r, r->ebx);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->ebx = rd32(r, r->ebp - 0x9a);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    r->esi = rd32(r, r->ebp - 0xec);
    call(r, 0x460fa0, 17);
    r->eax = rd32(r, r->ebp - 0xd0);
    push(r, r->esi);
    r->edx = rd32(r, r->ebp - 0xba);
    r->esi = rd32(r, r->ebp - 0xca);
    push(r, r->edi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    push(r, r->eax);
    r->eax = rd32(r, r->ebp - 0x4a);
    r->esi = (uint32_t)((int32_t)r->esi >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    push(r, 0xe5);
    wr32(r, r->ebp - 0xf4, r->eax);
    r->eax = rd32(r, r->ebp - 0x62);
    push(r, 0x1f9);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->ecx = rd32(r, r->ebp - 0xf4);
    wr32(r, r->ebp - 0xf0, r->eax);
    r->ebx = r->eax;
    r->eax = r->esi;
    call(r, 0x460ad0, 5);
    push(r, 0x1);
    r->eax = rd32(r, 0x4f9bf5);
    push(r, 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x18);
    push(r, r->eax);
    r->edx = rd32(r, r->ebp - 0xec);
    push(r, r->edx);
    push(r, 0x0);
    push(r, 0xa);
    push(r, r->edi);
    r->ecx = rd32(r, r->ebp - 0xd0);
    push(r, r->ecx);
    push(r, 0xe5);
    r->ebx = rd32(r, r->ebp - 0xf4);
    r->eax = 0x50e407;
    push(r, 0x1f9);
    r->edx = r->esi;
    r->ecx = rd32(r, r->ebp - 0xf0);
    push(r, r->ebx);
    r->ebx = 0x1a;
    r->esi = rd32(r, r->ebp - 0xe0);
    call(r, 0x460c50, 11);
    push(r, r->esi);
    push(r, r->edi);
    r->eax = rd32(r, r->ebp - 0xd0);
    push(r, r->eax);
    push(r, 0xe5);
    push(r, 0x1f9);
    push(r, 0x1);
    push(r, 0x0);
    r->eax = rd32(r, 0x4f9bfa);
    push(r, 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x18);
    push(r, r->eax);
    push(r, 0x448260);
    push(r, 0x448680);
    push(r, 0x416bb0);
    push(r, 0x2);
    push(r, 0x0);
    push(r, 0x5);
    push(r, 0x532b20);
    r->edx = rd32(r, r->ebp - 0x10c);
    r->ebx = rd32(r, r->ebp - 0x7a);
    r->eax = rd32(r, r->ebp - 0xc6);
    r->ecx = 0x1a;
    push(r, r->edx);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    r->edx = rd32(r, r->ebp - 0x96);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    call(r, 0x460fa0, 17);
    r->ebx = rd32(r, r->ebp - 0xd0);
    r->ecx = rd32(r, r->ebp - 0xa6);
    push(r, r->esi);
    r->edx = rd32(r, r->ebp - 0xae);
    r->eax = rd32(r, r->ebp - 0x6e);
    push(r, r->edi);
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    push(r, r->ebx);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    push(r, 0xe5);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->ebx = rd32(r, r->ebp - 0x92);
    push(r, 0x1f9);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    call(r, 0x460ad0, 5);
    push(r, r->esi);
    r->eax = rd32(r, r->ebp - 0xd0);
    r->ecx = rd32(r, r->ebp - 0x5e);
    push(r, r->edi);
    r->ebx = rd32(r, r->ebp - 0x82);
    r->edx = 0x11;
    push(r, r->eax);
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    push(r, 0xe5);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    r->eax = rd32(r, r->ebp - 0xb2);
    push(r, 0x1f9);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x460a40, 5);
    push(r, 0x1);
    push(r, 0x0);
    r->eax = rd32(r, 0x4f9bf9);
    push(r, 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x18);
    push(r, r->eax);
    push(r, r->esi);
    push(r, r->edi);
    r->ecx = rd32(r, r->ebp - 0xd0);
    push(r, r->ecx);
    push(r, 0xe5);
    r->eax = rd32(r, r->ebp - 0xaa);
    push(r, 0x1f9);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    push(r, r->eax);
    r->eax = rd32(r, r->ebp - 0x6a);
    r->ebx = 0x1;
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->edx = rd32(r, 0x4f7b9a);
    push(r, r->eax);
    r->eax = rd32(r, r->ebp - 0x9e);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->ecx = rd32(r, r->ebp - 0x2a);
    push(r, r->eax);
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    r->eax = 0x50e410;
    call(r, 0x460b60, 12);
    r->ecx = rd32(r, r->ebp - 0xbe);
    push(r, r->esi);
    r->ebx = rd32(r, r->ebp - 0xc2);
    r->eax = rd32(r, r->ebp - 0x66);
    push(r, r->edi);
    r->esi = rd32(r, r->ebp - 0xd0);
    r->edx = 0x11;
    push(r, r->esi);
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    push(r, 0xe5);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    push(r, 0x1f9);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x460a40, 5);
    r->eax = 0x15c;
    call(r, 0x4ca000, 0);
    if (r->eax != 0)
    {
        goto at_46338c;
    }
at_46334f:
    r->esi = r->eax;
    r->edx = 0x45c6e0;
    r->eax = r->esi;
    call(r, 0x4ac8f0, 0);
    r->eax = 0x54671c;
    r->edx = r->esi;
    r->ecx = 0;
    call(r, 0x4b5e70, 0);
    wr32(r, 0x532a48, r->ecx);
    call(r, 0x4cda10, 0);
    r->eax = rd32(r, r->ebp - 0x12c);
    r->port->env.chain = r->eax;
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_46338c:
    r->edi = 0xd;
    r->edx = 0x6;
    wr32(r, r->ebp - 0xe8, r->eax);
    wr32(r, r->ebp - 0x120, r->edi);
    call(r, 0x4abd70, 0);
    wr32(r, r->ebp - 0x120, r->edx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_46334f;
}

uint32_t vertrix_port_keys_menu_screen_4627a0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x19c
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
