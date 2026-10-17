#include "port_rtlhandlerrecords.h"

/* Runtime initialisation: sets 0x5c7564 and 0x5c7568 to 0x80000000, clears 0x5c756c and 0x5c7570,
 * and builds records with the handlers 0x4d6490, 0x4d64a0 and 0x4d64b0 (calls application_link). */

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

static void wr16(Regs *r, uint32_t address, uint32_t value)
{
    port_set16(r->port, address, 0, value);
}

static void wr32(Regs *r, uint32_t address, uint32_t value)
{
    port_set32(r->port, address, 0, value);
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

static void call_mem_keep(Regs *r, uint32_t target, unsigned count)
{
    call_mem_with(r, target, count, 1);
}

/* Original 0x4d3140: Runtime initialisation: sets 0x5c7564 and 0x5c7568 to 0x80000000, clears
 * 0x5c756c and 0x5c7570, and builds records with the handlers 0x4d6490, 0x4d64a0 and 0x4d64b0
 * (calls application_link). Evidence: calls 0x4d30f0; reads 0x5c7574, 0x5c7578, 0x5c757c, 0x5c7580,
 * 0x5c7584, 0x5c7588, 0x5c758c, 0x5c7590, 0x5c7594, 0x5c7598, 0x5c759c, 0x5c75a0, 0x5c75a4,
 * 0x5c75a8, 0x5c75ac, 0x5c75b0 and more; writes 0x5c7564, 0x5c7568, 0x5c756c, 0x5c7570, 0x50316c,
 * 0x503170, 0x503174, 0x50318c, 0x503190, 0x503194, 0x5031ac, 0x5031b0, 0x5031b4, 0x5031ec,
 * 0x5031f0, 0x5031cc and more. Register-for-register from the listing (0x4d3140..0x4d3e15); labels
 * are the original addresses. */
static void run(Regs *r)
{
    push_mem(r, r->edx);
    push_mem(r, r->esi);
    push_mem(r, r->edi);
    r->esp = r->esp - 0x30c;
    wr32(r, 0x5c7564, 0x80000000u);
    wr32(r, 0x5c7568, 0x80000000u);
    wr32(r, 0x5c756c, 0x0);
    wr32(r, 0x5c7570, 0x0);
    wr32(r, r->esp, 0x4d6490);
    wr32(r, r->esp + 0x4, 0x0);
    wr32(r, r->esp + 0x8, 0x0);
    r->edi = r->esp + 0xc;
    r->esi = r->esp;
    wr32(r, r->esp + 0x18, 0x4d64a0);
    wr32(r, r->esp + 0x1c, 0x0);
    movs(r, 4);
    movs(r, 4);
    movs(r, 4);
    wr32(r, r->esp + 0x20, 0x0);
    r->eax = rd32(r, r->esp + 0xc);
    wr32(r, r->esp + 0x30, 0x4d64b0);
    wr32(r, 0x50316c, r->eax);
    r->eax = rd32(r, r->esp + 0x10);
    r->edi = r->esp + 0x24;
    wr32(r, 0x503170, r->eax);
    r->eax = rd32(r, r->esp + 0x14);
    r->esi = r->esp + 0x18;
    wr32(r, 0x503174, r->eax);
    wr32(r, r->esp + 0x34, 0x0);
    movs(r, 4);
    movs(r, 4);
    movs(r, 4);
    wr32(r, r->esp + 0x38, 0x0);
    r->eax = rd32(r, r->esp + 0x24);
    wr32(r, r->esp + 0x48, 0x4d64c0);
    wr32(r, 0x50318c, r->eax);
    r->eax = rd32(r, r->esp + 0x28);
    r->edi = r->esp + 0x3c;
    wr32(r, 0x503190, r->eax);
    r->eax = rd32(r, r->esp + 0x2c);
    r->esi = r->esp + 0x30;
    wr32(r, 0x503194, r->eax);
    wr32(r, r->esp + 0x4c, 0x0);
    movs(r, 4);
    movs(r, 4);
    movs(r, 4);
    wr32(r, r->esp + 0x50, 0x0);
    r->eax = rd32(r, r->esp + 0x3c);
    wr32(r, r->esp + 0x60, 0x4d64e0);
    wr32(r, 0x5031ac, r->eax);
    r->eax = rd32(r, r->esp + 0x40);
    r->edi = r->esp + 0x54;
    wr32(r, 0x5031b0, r->eax);
    r->eax = rd32(r, r->esp + 0x44);
    r->esi = r->esp + 0x48;
    wr32(r, 0x5031b4, r->eax);
    wr32(r, r->esp + 0x64, 0x0);
    movs(r, 4);
    movs(r, 4);
    movs(r, 4);
    wr32(r, r->esp + 0x68, 0x0);
    r->eax = rd32(r, r->esp + 0x54);
    wr32(r, 0x5031ec, 0x4d64d0);
    wr32(r, 0x5031f0, 0x0);
    r->edi = r->esp + 0x6c;
    wr32(r, 0x5031cc, r->eax);
    r->eax = rd32(r, r->esp + 0x58);
    r->esi = r->esp + 0x60;
    wr32(r, 0x5031d0, r->eax);
    r->eax = rd32(r, r->esp + 0x5c);
    wr32(r, 0x5031f4, 0x0);
    wr32(r, 0x5031d4, r->eax);
    movs(r, 4);
    movs(r, 4);
    movs(r, 4);
    r->eax = rd32(r, r->esp + 0x6c);
    wr32(r, 0x50320c, r->eax);
    r->eax = rd32(r, r->esp + 0x70);
    wr32(r, 0x503210, r->eax);
    r->eax = rd32(r, r->esp + 0x74);
    wr32(r, 0x503214, r->eax);
    wr32(r, r->esp + 0x78, 0x4d64f0);
    wr32(r, r->esp + 0x7c, 0x0);
    r->edi = r->esp + 0x84;
    r->esi = r->esp + 0x78;
    wr32(r, r->esp + 0x80, 0x0);
    wr32(r, r->esp + 0x90, 0x4d6500);
    movs(r, 4);
    movs(r, 4);
    movs(r, 4);
    wr32(r, r->esp + 0x94, 0x0);
    r->eax = rd32(r, r->esp + 0x84);
    wr32(r, r->esp + 0x98, 0x0);
    wr32(r, 0x50322c, r->eax);
    r->eax = rd32(r, r->esp + 0x88);
    r->edi = r->esp + 0x9c;
    wr32(r, 0x503230, r->eax);
    r->eax = rd32(r, r->esp + 0x8c);
    r->esi = r->esp + 0x90;
    wr32(r, 0x503234, r->eax);
    wr32(r, r->esp + 0xa8, 0x4d6510);
    movs(r, 4);
    movs(r, 4);
    movs(r, 4);
    wr32(r, r->esp + 0xac, 0x0);
    r->eax = rd32(r, r->esp + 0x9c);
    wr32(r, r->esp + 0xb0, 0x0);
    wr32(r, 0x50324c, r->eax);
    r->eax = rd32(r, r->esp + 0xa0);
    r->edi = r->esp + 0xb4;
    wr32(r, 0x503250, r->eax);
    r->eax = rd32(r, r->esp + 0xa4);
    r->esi = r->esp + 0xa8;
    wr32(r, 0x503254, r->eax);
    wr32(r, r->esp + 0xc0, 0x4d6520);
    movs(r, 4);
    movs(r, 4);
    movs(r, 4);
    wr32(r, r->esp + 0xc4, 0x0);
    r->eax = rd32(r, r->esp + 0xb4);
    r->edi = r->esp + 0xcc;
    wr32(r, 0x50326c, r->eax);
    r->eax = rd32(r, r->esp + 0xb8);
    r->esi = r->esp + 0xc0;
    wr32(r, 0x503270, r->eax);
    r->eax = rd32(r, r->esp + 0xbc);
    wr32(r, r->esp + 0xc8, 0x0);
    wr32(r, 0x503274, r->eax);
    movs(r, 4);
    movs(r, 4);
    movs(r, 4);
    r->eax = rd32(r, r->esp + 0xcc);
    wr32(r, 0x5032ac, 0x4d6530);
    wr32(r, 0x5032b0, 0x0);
    wr32(r, 0x5032b4, 0x0);
    wr32(r, 0x5032cc, 0x4d6540);
    wr32(r, 0x50328c, r->eax);
    r->eax = rd32(r, r->esp + 0xd0);
    wr32(r, 0x5032d0, 0x0);
    wr32(r, 0x503290, r->eax);
    r->eax = rd32(r, r->esp + 0xd4);
    wr32(r, 0x5032d4, 0x0);
    wr32(r, 0x503294, r->eax);
    wr32(r, r->esp + 0xd8, 0x4d6550);
    wr32(r, r->esp + 0xdc, 0x0);
    r->edi = r->esp + 0xe4;
    r->esi = r->esp + 0xd8;
    wr32(r, r->esp + 0xe0, 0x0);
    wr32(r, r->esp + 0xf0, 0x4d6560);
    movs(r, 4);
    movs(r, 4);
    movs(r, 4);
    wr32(r, r->esp + 0xf4, 0x0);
    r->eax = rd32(r, r->esp + 0xe4);
    wr32(r, r->esp + 0xf8, 0x0);
    wr32(r, 0x5032ec, r->eax);
    r->eax = rd32(r, r->esp + 0xe8);
    r->edi = r->esp + 0xfc;
    wr32(r, 0x5032f0, r->eax);
    r->eax = rd32(r, r->esp + 0xec);
    r->esi = r->esp + 0xf0;
    wr32(r, 0x5032f4, r->eax);
    wr32(r, r->esp + 0x108, 0x4d6570);
    movs(r, 4);
    movs(r, 4);
    movs(r, 4);
    wr32(r, r->esp + 0x10c, 0x0);
    r->eax = rd32(r, r->esp + 0xfc);
    wr32(r, r->esp + 0x110, 0x0);
    wr32(r, 0x50330c, r->eax);
    r->eax = rd32(r, r->esp + 0x100);
    r->edi = r->esp + 0x114;
    wr32(r, 0x503310, r->eax);
    r->eax = rd32(r, r->esp + 0x104);
    r->esi = r->esp + 0x108;
    wr32(r, 0x503314, r->eax);
    wr32(r, r->esp + 0x120, 0x4d6580);
    movs(r, 4);
    movs(r, 4);
    movs(r, 4);
    wr32(r, r->esp + 0x124, 0x0);
    r->eax = rd32(r, r->esp + 0x114);
    wr32(r, r->esp + 0x128, 0x0);
    wr32(r, 0x50332c, r->eax);
    r->eax = rd32(r, r->esp + 0x118);
    r->edi = r->esp + 0x12c;
    wr32(r, 0x503330, r->eax);
    r->eax = rd32(r, r->esp + 0x11c);
    r->esi = r->esp + 0x120;
    wr32(r, 0x503334, r->eax);
    wr32(r, r->esp + 0x138, 0x4d6590);
    movs(r, 4);
    movs(r, 4);
    movs(r, 4);
    wr32(r, r->esp + 0x13c, 0x0);
    r->eax = rd32(r, r->esp + 0x12c);
    wr32(r, r->esp + 0x140, 0x0);
    wr32(r, 0x50334c, r->eax);
    r->eax = rd32(r, r->esp + 0x130);
    r->edi = r->esp + 0x144;
    wr32(r, 0x503350, r->eax);
    r->eax = rd32(r, r->esp + 0x134);
    r->esi = r->esp + 0x138;
    wr32(r, 0x503354, r->eax);
    wr32(r, r->esp + 0x150, 0x4d65a0);
    movs(r, 4);
    movs(r, 4);
    movs(r, 4);
    wr32(r, r->esp + 0x154, 0x0);
    r->eax = rd32(r, r->esp + 0x144);
    r->edi = r->esp + 0x15c;
    wr32(r, 0x50336c, r->eax);
    r->eax = rd32(r, r->esp + 0x148);
    r->esi = r->esp + 0x150;
    wr32(r, 0x503370, r->eax);
    r->eax = rd32(r, r->esp + 0x14c);
    wr32(r, r->esp + 0x158, 0x0);
    wr32(r, 0x503374, r->eax);
    movs(r, 4);
    movs(r, 4);
    movs(r, 4);
    r->eax = rd32(r, r->esp + 0x15c);
    wr32(r, 0x50338c, r->eax);
    r->eax = rd32(r, r->esp + 0x160);
    wr32(r, 0x503390, r->eax);
    r->eax = rd32(r, r->esp + 0x164);
    wr32(r, 0x503394, r->eax);
    wr32(r, r->esp + 0x168, 0x4d65b0);
    wr32(r, r->esp + 0x16c, 0x0);
    r->edi = r->esp + 0x174;
    r->esi = r->esp + 0x168;
    wr32(r, r->esp + 0x170, 0x0);
    wr32(r, r->esp + 0x180, 0x4d65c0);
    movs(r, 4);
    movs(r, 4);
    movs(r, 4);
    wr32(r, r->esp + 0x184, 0x0);
    r->eax = rd32(r, r->esp + 0x174);
    wr32(r, r->esp + 0x188, 0x0);
    wr32(r, 0x5033ac, r->eax);
    r->eax = rd32(r, r->esp + 0x178);
    r->edi = r->esp + 0x18c;
    wr32(r, 0x5033b0, r->eax);
    r->eax = rd32(r, r->esp + 0x17c);
    r->esi = r->esp + 0x180;
    wr32(r, 0x5033b4, r->eax);
    wr32(r, r->esp + 0x198, 0x4d65d0);
    movs(r, 4);
    movs(r, 4);
    movs(r, 4);
    wr32(r, r->esp + 0x19c, 0x0);
    r->eax = rd32(r, r->esp + 0x18c);
    wr32(r, r->esp + 0x1a0, 0x0);
    wr32(r, 0x5033cc, r->eax);
    r->eax = rd32(r, r->esp + 0x190);
    r->edi = r->esp + 0x1a4;
    wr32(r, 0x5033d0, r->eax);
    r->eax = rd32(r, r->esp + 0x194);
    r->esi = r->esp + 0x198;
    wr32(r, 0x5033d4, r->eax);
    wr32(r, r->esp + 0x1b0, 0x4d65e0);
    movs(r, 4);
    movs(r, 4);
    movs(r, 4);
    wr32(r, r->esp + 0x1b4, 0x0);
    r->eax = rd32(r, r->esp + 0x1a4);
    wr32(r, r->esp + 0x1b8, 0x0);
    wr32(r, 0x5033ec, r->eax);
    r->eax = rd32(r, r->esp + 0x1a8);
    r->edi = r->esp + 0x1bc;
    wr32(r, 0x5033f0, r->eax);
    r->eax = rd32(r, r->esp + 0x1ac);
    r->esi = r->esp + 0x1b0;
    wr32(r, 0x5033f4, r->eax);
    wr32(r, r->esp + 0x1c8, 0x4d65f0);
    movs(r, 4);
    movs(r, 4);
    movs(r, 4);
    wr32(r, r->esp + 0x1cc, 0x0);
    r->eax = rd32(r, r->esp + 0x1bc);
    wr32(r, r->esp + 0x1d0, 0x0);
    wr32(r, 0x50340c, r->eax);
    r->eax = rd32(r, r->esp + 0x1c0);
    r->edi = r->esp + 0x1d4;
    wr32(r, 0x503410, r->eax);
    r->eax = rd32(r, r->esp + 0x1c4);
    r->esi = r->esp + 0x1c8;
    wr32(r, 0x503414, r->eax);
    wr32(r, r->esp + 0x1e0, 0x4d6600);
    movs(r, 4);
    movs(r, 4);
    movs(r, 4);
    wr32(r, r->esp + 0x1e4, 0x0);
    r->eax = rd32(r, r->esp + 0x1d4);
    r->edi = r->esp + 0x1ec;
    wr32(r, 0x50342c, r->eax);
    r->eax = rd32(r, r->esp + 0x1d8);
    r->esi = r->esp + 0x1e0;
    wr32(r, 0x503430, r->eax);
    r->eax = rd32(r, r->esp + 0x1dc);
    wr32(r, r->esp + 0x1e8, 0x0);
    wr32(r, 0x503434, r->eax);
    movs(r, 4);
    movs(r, 4);
    movs(r, 4);
    r->eax = rd32(r, r->esp + 0x1ec);
    wr32(r, 0x50344c, r->eax);
    r->eax = rd32(r, r->esp + 0x1f0);
    wr32(r, 0x503450, r->eax);
    r->eax = rd32(r, r->esp + 0x1f4);
    wr32(r, 0x503454, r->eax);
    wr32(r, r->esp + 0x1f8, 0x4d6610);
    wr32(r, r->esp + 0x1fc, 0x0);
    r->edi = r->esp + 0x204;
    r->esi = r->esp + 0x1f8;
    wr32(r, r->esp + 0x200, 0x0);
    wr32(r, r->esp + 0x210, 0x4d6620);
    movs(r, 4);
    movs(r, 4);
    movs(r, 4);
    wr32(r, r->esp + 0x214, 0x0);
    r->eax = rd32(r, r->esp + 0x204);
    wr32(r, r->esp + 0x218, 0x0);
    wr32(r, 0x50346c, r->eax);
    r->eax = rd32(r, r->esp + 0x208);
    r->edi = r->esp + 0x21c;
    wr32(r, 0x503470, r->eax);
    r->eax = rd32(r, r->esp + 0x20c);
    r->esi = r->esp + 0x210;
    wr32(r, 0x503474, r->eax);
    wr32(r, r->esp + 0x228, 0x4d6630);
    movs(r, 4);
    movs(r, 4);
    movs(r, 4);
    wr32(r, r->esp + 0x22c, 0x0);
    r->eax = rd32(r, r->esp + 0x21c);
    wr32(r, r->esp + 0x230, 0x0);
    wr32(r, 0x50348c, r->eax);
    r->eax = rd32(r, r->esp + 0x220);
    r->edi = r->esp + 0x234;
    wr32(r, 0x503490, r->eax);
    r->eax = rd32(r, r->esp + 0x224);
    r->esi = r->esp + 0x228;
    wr32(r, 0x503494, r->eax);
    wr32(r, r->esp + 0x240, 0x4d6640);
    movs(r, 4);
    movs(r, 4);
    movs(r, 4);
    wr32(r, r->esp + 0x244, 0x0);
    r->eax = rd32(r, r->esp + 0x234);
    wr32(r, r->esp + 0x248, 0x0);
    wr32(r, 0x5034ac, r->eax);
    r->eax = rd32(r, r->esp + 0x238);
    r->esi = r->esp + 0x240;
    wr32(r, 0x5034b0, r->eax);
    r->eax = rd32(r, r->esp + 0x23c);
    r->edi = 0x5c7574;
    wr32(r, 0x5034b4, r->eax);
    wr32(r, r->esp + 0x24c, 0x4d6650);
    movs(r, 4);
    movs(r, 4);
    movs(r, 4);
    wr32(r, r->esp + 0x250, 0x0);
    r->eax = rd32(r, 0x5c7574);
    wr32(r, r->esp + 0x254, 0x0);
    wr32(r, 0x5034cc, r->eax);
    r->eax = rd32(r, 0x5c7578);
    r->esi = r->esp + 0x24c;
    wr32(r, 0x5034d0, r->eax);
    r->eax = rd32(r, 0x5c757c);
    r->edi = 0x5c7580;
    wr32(r, 0x5034d4, r->eax);
    wr32(r, r->esp + 0x258, 0x4d6640);
    movs(r, 4);
    movs(r, 4);
    movs(r, 4);
    wr32(r, r->esp + 0x25c, 0x0);
    r->eax = rd32(r, 0x5c7580);
    r->esi = r->esp + 0x258;
    wr32(r, 0x5034ec, r->eax);
    r->eax = rd32(r, 0x5c7584);
    r->edi = 0x5c758c;
    wr32(r, 0x5034f0, r->eax);
    r->eax = rd32(r, 0x5c7588);
    wr32(r, r->esp + 0x260, 0x0);
    wr32(r, 0x5034f4, r->eax);
    movs(r, 4);
    movs(r, 4);
    movs(r, 4);
    r->eax = rd32(r, 0x5c758c);
    wr32(r, 0x50350c, r->eax);
    r->eax = rd32(r, 0x5c7590);
    wr32(r, 0x503510, r->eax);
    r->eax = rd32(r, 0x5c7594);
    wr32(r, 0x503514, r->eax);
    wr32(r, r->esp + 0x264, 0x4d6650);
    wr32(r, r->esp + 0x268, 0x0);
    r->esi = r->esp + 0x264;
    r->edi = 0x5c7598;
    wr32(r, r->esp + 0x26c, 0x0);
    wr32(r, r->esp + 0x270, 0x4d6660);
    movs(r, 4);
    movs(r, 4);
    movs(r, 4);
    wr32(r, r->esp + 0x274, 0x0);
    r->eax = rd32(r, 0x5c7598);
    wr32(r, r->esp + 0x278, 0x0);
    wr32(r, 0x50352c, r->eax);
    r->eax = rd32(r, 0x5c759c);
    r->esi = r->esp + 0x270;
    wr32(r, 0x503530, r->eax);
    r->eax = rd32(r, 0x5c75a0);
    r->edi = 0x5c75a4;
    wr32(r, 0x503534, r->eax);
    wr32(r, r->esp + 0x27c, 0x4d6660);
    movs(r, 4);
    movs(r, 4);
    movs(r, 4);
    wr32(r, r->esp + 0x280, 0x0);
    r->eax = rd32(r, 0x5c75a4);
    wr32(r, r->esp + 0x284, 0x0);
    wr32(r, 0x50354c, r->eax);
    r->eax = rd32(r, 0x5c75a8);
    r->esi = r->esp + 0x27c;
    wr32(r, 0x503550, r->eax);
    r->eax = rd32(r, 0x5c75ac);
    r->edi = 0x5c75b0;
    wr32(r, 0x503554, r->eax);
    wr32(r, r->esp + 0x288, 0x4d6660);
    movs(r, 4);
    movs(r, 4);
    movs(r, 4);
    wr32(r, r->esp + 0x28c, 0x0);
    r->eax = rd32(r, 0x5c75b0);
    wr32(r, r->esp + 0x290, 0x0);
    wr32(r, 0x50356c, r->eax);
    r->eax = rd32(r, 0x5c75b4);
    r->esi = r->esp + 0x288;
    wr32(r, 0x503570, r->eax);
    r->eax = rd32(r, 0x5c75b8);
    r->edi = 0x5c75bc;
    wr32(r, 0x503574, r->eax);
    wr32(r, r->esp + 0x294, 0x4d6660);
    movs(r, 4);
    movs(r, 4);
    movs(r, 4);
    wr32(r, r->esp + 0x298, 0x0);
    r->eax = rd32(r, 0x5c75bc);
    wr32(r, r->esp + 0x29c, 0x0);
    wr32(r, 0x50358c, r->eax);
    r->eax = rd32(r, 0x5c75c0);
    r->esi = r->esp + 0x294;
    wr32(r, 0x503590, r->eax);
    r->eax = rd32(r, 0x5c75c4);
    r->edi = 0x5c75c8;
    wr32(r, 0x503594, r->eax);
    wr32(r, r->esp + 0x2a0, 0x4d6670);
    movs(r, 4);
    movs(r, 4);
    movs(r, 4);
    wr32(r, r->esp + 0x2a4, 0x0);
    r->eax = rd32(r, 0x5c75c8);
    r->esi = r->esp + 0x2a0;
    wr32(r, 0x5035ac, r->eax);
    r->eax = rd32(r, 0x5c75cc);
    r->edi = 0x5c75d4;
    wr32(r, 0x5035b0, r->eax);
    r->eax = rd32(r, 0x5c75d0);
    wr32(r, r->esp + 0x2a8, 0x0);
    wr32(r, 0x5035b4, r->eax);
    movs(r, 4);
    movs(r, 4);
    movs(r, 4);
    r->eax = rd32(r, 0x5c75d4);
    wr32(r, 0x5035cc, r->eax);
    r->eax = rd32(r, 0x5c75d8);
    wr32(r, 0x5035d0, r->eax);
    r->eax = rd32(r, 0x5c75dc);
    wr32(r, 0x5035d4, r->eax);
    wr32(r, r->esp + 0x2ac, 0x4d6680);
    wr32(r, r->esp + 0x2b0, 0x0);
    r->esi = r->esp + 0x2ac;
    r->edi = 0x5c75e0;
    wr32(r, r->esp + 0x2b4, 0x0);
    wr32(r, r->esp + 0x2b8, 0x4d6680);
    movs(r, 4);
    movs(r, 4);
    movs(r, 4);
    wr32(r, r->esp + 0x2bc, 0x0);
    r->eax = rd32(r, 0x5c75e0);
    wr32(r, r->esp + 0x2c0, 0x0);
    wr32(r, 0x5035ec, r->eax);
    r->eax = rd32(r, 0x5c75e4);
    r->esi = r->esp + 0x2b8;
    wr32(r, 0x5035f0, r->eax);
    r->eax = rd32(r, 0x5c75e8);
    r->edi = 0x5c75ec;
    wr32(r, 0x5035f4, r->eax);
    wr32(r, r->esp + 0x2c4, 0x4d6690);
    movs(r, 4);
    movs(r, 4);
    movs(r, 4);
    wr32(r, r->esp + 0x2c8, 0x0);
    r->eax = rd32(r, 0x5c75ec);
    wr32(r, r->esp + 0x2cc, 0x0);
    wr32(r, 0x50360c, r->eax);
    r->eax = rd32(r, 0x5c75f0);
    r->edi = r->esp + 0x2d0;
    wr32(r, 0x503610, r->eax);
    r->eax = rd32(r, 0x5c75f4);
    r->esi = r->esp + 0x2c4;
    wr32(r, 0x503614, r->eax);
    wr32(r, r->esp + 0x2dc, 0x4d66a0);
    movs(r, 4);
    movs(r, 4);
    movs(r, 4);
    wr32(r, r->esp + 0x2e0, 0x0);
    r->eax = rd32(r, r->esp + 0x2d0);
    wr32(r, r->esp + 0x2e4, 0x0);
    wr32(r, 0x50362c, r->eax);
    r->eax = rd32(r, r->esp + 0x2d4);
    r->edi = r->esp + 0x2e8;
    wr32(r, 0x503630, r->eax);
    r->eax = rd32(r, r->esp + 0x2d8);
    r->esi = r->esp + 0x2dc;
    wr32(r, 0x503634, r->eax);
    wr32(r, r->esp + 0x2f4, 0x4d66b0);
    movs(r, 4);
    movs(r, 4);
    movs(r, 4);
    wr32(r, r->esp + 0x2f8, 0x0);
    r->eax = rd32(r, r->esp + 0x2e8);
    r->edi = r->esp + 0x300;
    wr32(r, 0x50364c, r->eax);
    r->eax = rd32(r, r->esp + 0x2ec);
    r->esi = r->esp + 0x2f4;
    wr32(r, 0x503650, r->eax);
    r->eax = rd32(r, r->esp + 0x2f0);
    wr32(r, r->esp + 0x2fc, 0x0);
    wr32(r, 0x503654, r->eax);
    movs(r, 4);
    movs(r, 4);
    movs(r, 4);
    r->eax = rd32(r, r->esp + 0x300);
    r->edx = 0x503698;
    wr32(r, 0x50366c, r->eax);
    r->eax = rd32(r, r->esp + 0x304);
    wr32(r, 0x50368c, 0x0);
    wr32(r, 0x503670, r->eax);
    r->eax = rd32(r, r->esp + 0x308);
    wr32(r, 0x503690, 0x0);
    wr32(r, 0x503674, r->eax);
    r->eax = 0x5c75f8;
    wr32(r, 0x503694, 0x0);
    call_mem_keep(r, 0x4d30f0, 8);
    r->edx = 0x5036b0;
    r->eax = 0x5c75f9;
    call_mem_keep(r, 0x4d30f0, 8);
    r->edx = 0x5036c8;
    r->eax = 0x5c75fa;
    call_mem_keep(r, 0x4d30f0, 8);
    r->esp = r->esp + 0x30c;
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->edx = pop_mem(r);
    return;
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    r->eax = 0x519864;
    return;
}

uint32_t vertrix_port_rtl_handler_records_init_4d3140(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x330
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
