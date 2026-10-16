#include "port_rtluiscreenactors.h"

/* 0x46b810 (4544 B; reached from the register forwarder 0x46b800 and recursively from itself at
 * 0x46c5de) first makes 73 calls to ui_companion_spawn 0x471100. */

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
} Regs;

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

/* Original 0x46b810: 0x46b810 (4544 B; reached from the register forwarder 0x46b800 and recursively
 * from itself at 0x46c5de) first makes 73 calls to ui_companion_spawn 0x471100. Each call takes an
 * id in ecx, an x/y pair from the 16.16 table at 0x4f888a.. (sar 0x10) and a picture handle from
 * 0x4fbf28..0x4fbfdc. It then builds further actors and adds them to the list at 0x54671c, and each
 * one is later removed with list_delete 0x4b5e70. These actors are labeled boxes (0x4b6350 +
 * actor_initialize 0x4adf20 + actor_set_text 0x4b65d0), a 0x43d3f0-constructed actor, and two menu
 * items (0x4b5580 + key_actor_label 0x4b5700 + actor_storage_style 0x4123d0). Along the way it also
 * calls table_pair_value 0x4178d0, object_flag 0x4126f0 and 0x46c500 (four times). Evidence: calls
 * 0x471100, 0x4178d0, 0x4126f0, 0x4ca000, 0x4b6350, 0x4adf20, 0x4b65d0, 0x4123d0, 0x4b5e70; reads
 * 0x5466c4, 0x4f888a, 0x4f888e, 0x4fbf28, 0x4f8896, 0x4f8892, 0x4f889e, 0x4f889a, 0x4fbf2c,
 * 0x4f88a6, 0x4f88a2, 0x4fbfdc, 0x4f893a, 0x4f8936, 0x4f894a, 0x4f8946 and more.
 * Register-for-register from the listing (0x46b81a..0x46c4ec); labels are the original addresses.
 */
static void run(Regs *r)
{
    wr32(r, r->ebp - 0x24, r->eax);
    r->esi = r->edx;
    r->ebx = rd32(r, 0x5466c4);
    push(r, r->eax);
    r->ecx = 0;
    r->eax = rd32(r, 0x4f888a);
    push(r, r->edx);
    r->edx = rd32(r, 0x4f888e);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = rd32(r, r->ebp - 0x24);
    r->ebx = rd32(r, 0x4fbf28);
    r->edx = rd32(r, 0x4f8896);
    r->eax = rd32(r, 0x4f8892);
    push(r, r->ecx);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    push(r, r->esi);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->ecx = 0x1;
    call(r, 0x471100, 2);
    r->ebx = rd32(r, r->ebp - 0x24);
    r->ecx = 0x2;
    r->edx = rd32(r, 0x4f889e);
    r->eax = rd32(r, 0x4f889a);
    push(r, r->ebx);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    push(r, r->esi);
    r->ebx = rd32(r, 0x4fbf2c);
    r->edi = rd32(r, r->ebp - 0x24);
    call(r, 0x471100, 2);
    r->ecx = 0x3;
    r->ebx = rd32(r, 0x4fbf2c);
    push(r, r->edi);
    r->edx = rd32(r, 0x4f88a6);
    r->eax = rd32(r, 0x4f88a2);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = 0x6a;
    r->ebx = rd32(r, 0x4fbfdc);
    push(r, r->edi);
    r->edx = rd32(r, 0x4f893a);
    r->eax = rd32(r, 0x4f8936);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = 0x6b;
    r->ebx = rd32(r, 0x4fbfdc);
    push(r, r->edi);
    r->edx = rd32(r, 0x4f894a);
    r->eax = rd32(r, 0x4f8946);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = 0x6c;
    r->ebx = rd32(r, 0x4fbfd8);
    push(r, r->edi);
    r->edx = rd32(r, 0x4f8932);
    r->eax = rd32(r, 0x4f892e);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = 0x6d;
    r->ebx = rd32(r, 0x4fbfd8);
    push(r, r->edi);
    r->edx = rd32(r, 0x4f8942);
    r->eax = rd32(r, 0x4f893e);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = 0x4;
    r->ebx = rd32(r, 0x4fbf30);
    push(r, r->edi);
    r->edx = rd32(r, 0x4f88ba);
    r->eax = rd32(r, 0x4f88b6);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = 0x5;
    r->ebx = rd32(r, 0x4fbf38);
    push(r, r->edi);
    r->edx = rd32(r, 0x4f88ca);
    r->eax = rd32(r, 0x4f88c6);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = 0x6;
    r->ebx = rd32(r, 0x4fbf34);
    push(r, r->edi);
    r->edx = rd32(r, 0x4f88b2);
    r->eax = rd32(r, 0x4f88ae);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = 0x7;
    r->ebx = rd32(r, 0x4fbf3c);
    push(r, r->edi);
    r->edx = rd32(r, 0x4f88c2);
    r->eax = rd32(r, 0x4f88be);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = 0x58;
    r->ebx = rd32(r, 0x4fbf38);
    push(r, r->edi);
    r->edx = rd32(r, 0x4f88da);
    r->eax = rd32(r, 0x4f88d6);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = 0x59;
    r->ebx = rd32(r, 0x4fbf30);
    push(r, r->edi);
    r->edx = rd32(r, 0x4f88ea);
    r->eax = rd32(r, 0x4f88e6);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = 0x5a;
    r->ebx = rd32(r, 0x4fbf3c);
    push(r, r->edi);
    r->edx = rd32(r, 0x4f88d2);
    r->eax = rd32(r, 0x4f88ce);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = 0x5b;
    r->ebx = rd32(r, 0x4fbf34);
    push(r, r->edi);
    r->edx = rd32(r, 0x4f88e2);
    r->eax = rd32(r, 0x4f88de);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = 0x62;
    r->ebx = rd32(r, 0x4fbfd0);
    push(r, r->edi);
    r->edx = rd32(r, 0x4f88fa);
    r->eax = rd32(r, 0x4f88f6);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = 0x63;
    r->ebx = rd32(r, 0x4fbfd0);
    push(r, r->edi);
    r->edx = rd32(r, 0x4f892a);
    r->eax = rd32(r, 0x4f8926);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = 0x64;
    r->ebx = rd32(r, 0x4fbfc8);
    push(r, r->edi);
    r->edx = rd32(r, 0x4f88f2);
    r->eax = rd32(r, 0x4f88ee);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = 0x65;
    r->ebx = rd32(r, 0x4fbfc8);
    push(r, r->edi);
    r->edx = rd32(r, 0x4f8922);
    r->eax = rd32(r, 0x4f891e);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = 0x66;
    r->ebx = rd32(r, 0x4fbfd4);
    push(r, r->edi);
    r->edx = rd32(r, 0x4f890a);
    r->eax = rd32(r, 0x4f8906);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = 0x67;
    r->ebx = rd32(r, 0x4fbfd4);
    push(r, r->edi);
    r->edx = rd32(r, 0x4f891a);
    r->eax = rd32(r, 0x4f8916);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = 0x68;
    r->ebx = rd32(r, 0x4fbfcc);
    push(r, r->edi);
    r->edx = rd32(r, 0x4f8902);
    r->eax = rd32(r, 0x4f88fe);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = 0x69;
    r->ebx = rd32(r, 0x4fbfcc);
    push(r, r->edi);
    r->edx = rd32(r, 0x4f8912);
    r->eax = rd32(r, 0x4f890e);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = 0x8;
    r->ebx = rd32(r, 0x4fbf44);
    push(r, r->edi);
    r->edx = rd32(r, 0x4f8952);
    r->eax = rd32(r, 0x4f894e);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = 0x9;
    r->ebx = rd32(r, 0x4fbf44);
    push(r, r->edi);
    r->edx = rd32(r, 0x4f895a);
    r->eax = rd32(r, 0x4f8956);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = 0xa;
    r->ebx = rd32(r, 0x4fbf40);
    push(r, r->edi);
    r->edx = rd32(r, 0x4f8962);
    r->eax = rd32(r, 0x4f895e);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = 0xb;
    r->ebx = rd32(r, 0x4fbf40);
    push(r, r->edi);
    r->edx = rd32(r, 0x4f896a);
    r->eax = rd32(r, 0x4f8966);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = 0x10;
    r->ebx = rd32(r, 0x4fbf5c);
    push(r, r->edi);
    r->edx = rd32(r, 0x4f89b2);
    r->eax = rd32(r, 0x4f89ae);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = 0x11;
    r->ebx = rd32(r, 0x4fbf5c);
    push(r, r->edi);
    r->edx = rd32(r, 0x4f89ba);
    r->eax = rd32(r, 0x4f89b6);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = 0x12;
    r->ebx = rd32(r, 0x4fbf58);
    push(r, r->edi);
    r->edx = rd32(r, 0x4f89ca);
    r->eax = rd32(r, 0x4f89c6);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = 0x13;
    r->ebx = rd32(r, 0x4fbf58);
    push(r, r->edi);
    r->edx = rd32(r, 0x4f89d2);
    r->eax = rd32(r, 0x4f89ce);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = 0x14;
    r->ebx = rd32(r, 0x4fbf50);
    push(r, r->edi);
    r->edx = rd32(r, 0x4f89ea);
    r->eax = rd32(r, 0x4f89e6);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = 0x15;
    r->ebx = rd32(r, 0x4fbf54);
    push(r, r->edi);
    r->edx = rd32(r, 0x4f89f2);
    r->eax = rd32(r, 0x4f89ee);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = 0x16;
    r->ebx = rd32(r, 0x4fbf48);
    push(r, r->edi);
    r->edx = rd32(r, 0x4f89da);
    r->eax = rd32(r, 0x4f89d6);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = 0x17;
    r->ebx = rd32(r, 0x4fbf4c);
    push(r, r->edi);
    r->edx = rd32(r, 0x4f89e2);
    r->eax = rd32(r, 0x4f89de);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = 0x18;
    r->ebx = rd32(r, 0x4fbf60);
    push(r, r->edi);
    r->edx = rd32(r, 0x4f8a1a);
    r->eax = rd32(r, 0x4f8a16);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = 0x19;
    r->ebx = rd32(r, 0x4fbf60);
    push(r, r->edi);
    r->edx = rd32(r, 0x4f8a22);
    r->eax = rd32(r, 0x4f8a1e);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = 0x1a;
    r->ebx = rd32(r, 0x4fbf60);
    push(r, r->edi);
    r->edx = rd32(r, 0x4f8a2a);
    r->eax = rd32(r, 0x4f8a26);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = 0x1b;
    r->ebx = rd32(r, 0x4fbf60);
    push(r, r->edi);
    r->edx = rd32(r, 0x4f8a32);
    r->eax = rd32(r, 0x4f8a2e);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = 0x1c;
    r->ebx = rd32(r, 0x4fbf6c);
    push(r, r->edi);
    r->edx = rd32(r, 0x4f8aa2);
    r->eax = rd32(r, 0x4f8a9e);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = 0x1d;
    r->ebx = rd32(r, 0x4fbf6c);
    push(r, r->edi);
    r->edx = rd32(r, 0x4f8aaa);
    r->eax = rd32(r, 0x4f8aa6);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = 0x1e;
    r->ebx = rd32(r, 0x4fbf70);
    push(r, r->edi);
    r->edx = rd32(r, 0x4f8ab2);
    r->eax = rd32(r, 0x4f8aae);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = 0x1f;
    r->ebx = rd32(r, 0x4fbf70);
    push(r, r->edi);
    r->edx = rd32(r, 0x4f8aba);
    r->eax = rd32(r, 0x4f8ab6);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    r->eax = 0;
    wr32(r, r->ebp - 0x2c, r->eax);
    wr32(r, r->ebp - 0x1c, r->eax);
at_46be31:
    r->edi = 0;
    r->eax = r->edi;
    r->eax = 0u - r->eax;
    r->eax = r->eax + 0x3;
    wr32(r, r->ebp - 0x14, r->eax);
at_46be3f:
    r->ebx = 0x1;
    if (r->esi == (0xffffffffu))
    {
        goto at_46c441;
    }
at_46be4d:
    if (r->ebx != 0x1)
    {
        goto at_46becc;
    }
    r->eax = rd32(r, r->ebp - 0x1c);
    set_low16(&r->eax, (r->eax & 0xffff) * rd16(r, 0x4f8acc));
    r->ecx = rd32(r, r->ebp - 0x24);
    push(r, r->ecx);
    set_low16(&r->eax, (r->eax & 0xffff) + rd16(r, 0x4f8ac4));
    r->edx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    set_low16(&r->eax, rd16(r, 0x4f8ac8));
    r->eax = r->eax * r->edi;
    r->ebx = rd32(r, 0x4fbf64);
    set_low16(&r->ecx, rd16(r, 0x4f8ac0));
    push(r, r->esi);
    r->eax = r->eax + r->ecx;
    r->ecx = 0x2a;
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    call(r, 0x471100, 2);
    r->eax = rd32(r, r->ebp - 0x1c);
    set_low16(&r->eax, (r->eax & 0xffff) * rd16(r, 0x4f8acc));
    set_low16(&r->eax, (r->eax & 0xffff) + rd16(r, 0x4f8ac4));
    r->edx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    set_low16(&r->eax, rd16(r, 0x4f8ac8));
    r->eax = r->eax * r->edi;
    r->ebx = rd32(r, r->ebp - 0x24);
    push(r, r->ebx);
    r->ebx = rd32(r, 0x4fbf68);
    set_low16(&r->ecx, rd16(r, 0x4f8ac0));
    push(r, r->esi);
    r->eax = r->eax + r->ecx;
    r->ecx = 0x2c;
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    call(r, 0x471100, 2);
at_46becc:
    r->ebx = 0x1;
    if (r->esi != (0xffffffffu))
    {
        goto at_46c45f;
    }
    r->edx = 0;
    r->eax = 0;
    set_low8(&r->edx, rd8(r, r->ebp - 0x2c));
    set_low8(&r->eax, rd8(r, 0x532a6c));
    call(r, 0x4178d0, 0);
    if (r->eax != r->esi)
    {
        goto at_46c45f;
    }
at_46bef3:
    r->ecx = rd32(r, r->ebp - 0x2c);
    r->eax = rd32(r, r->ebp - 0x14);
    r->edi = r->edi + 1;
    r->ecx = r->ecx + 1;
    r->eax = r->eax - 1;
    wr32(r, r->ebp - 0x2c, r->ecx);
    wr32(r, r->ebp - 0x14, r->eax);
    if (r->edi < 0x4 && !r->port->env.failed)
    {
        goto at_46be3f;
    }
    r->ebx = rd32(r, r->ebp - 0x1c);
    r->ebx = r->ebx + 1;
    wr32(r, r->ebp - 0x1c, r->ebx);
    if (r->ebx < 0x7 && !r->port->env.failed)
    {
        goto at_46be31;
    }
    r->edx = 0x20;
    r->eax = rd32(r, r->ebp - 0x24);
    call(r, 0x4126f0, 0);
    if (r->eax != 0x1)
    {
        goto at_46bfdf;
    }
    r->eax = 0x180;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_46bf44;
    }
    call(r, 0x4b6350, 0);
at_46bf44:
    r->edi = r->eax;
    push(r, 0x0);
    push(r, 0x0);
    push(r, 0x0);
    push(r, 0x0);
    r->eax = r->edi;
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = 0;
    r->edx = 0;
    call(r, 0x4adf20, 5);
    set_low16(&r->eax, rd16(r, 0x4f8cc4));
    set_low16(&r->eax, (r->eax & 0xffff) + rd16(r, 0x4f8ccc));
    r->eax = r->eax - 1;
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    push(r, r->eax);
    r->eax = rd32(r, 0x4f8cc2);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    set_low16(&r->ebx, rd16(r, 0x4f8cc8));
    push(r, r->eax);
    set_low16(&r->eax, rd16(r, 0x4f8cc0));
    r->eax = r->eax + r->ebx;
    r->eax = r->eax - 1;
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    r->ecx = rd32(r, 0x4f8cbe);
    push(r, r->eax);
    r->eax = rd32(r, 0x532a68);
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    r->eax = r->eax << 0x2;
    r->ebx = rd32(r, 0x4f9c07);
    r->eax = r->eax + 0x5345d4;
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x18);
    r->edx = rd32(r, r->eax);
    r->eax = r->edi;
    call(r, 0x4b65d0, 3);
    r->edx = 0x20;
    r->eax = rd32(r, r->ebp - 0x24);
    r->ebx = r->edi;
    wr32(r, r->ebp - 0x38, r->edi);
    call(r, 0x4123d0, 0);
    wr8(r, r->edi + 0x44, 0x10);
    if (r->esi != 0x20)
    {
        goto at_46bfd2;
    }
    wr8(r, r->edi + 0x110, 0x1);
at_46bfd2:
    r->edx = rd32(r, r->ebp - 0x38);
    r->eax = 0x54671c;
    call(r, 0x4b5e70, 0);
at_46bfdf:
    r->edx = 0x21;
    r->eax = rd32(r, r->ebp - 0x24);
    call(r, 0x4126f0, 0);
    if (r->eax != 0x1)
    {
        goto at_46c0a3;
    }
    r->eax = 0x180;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_46c008;
    }
    call(r, 0x4b6350, 0);
at_46c008:
    r->edi = r->eax;
    push(r, 0x0);
    push(r, 0x0);
    push(r, 0x0);
    push(r, 0x0);
    r->eax = r->edi;
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = 0;
    r->edx = 0;
    call(r, 0x4adf20, 5);
    set_low16(&r->eax, rd16(r, 0x4f8cd4));
    set_low16(&r->eax, (r->eax & 0xffff) + rd16(r, 0x4f8cdc));
    r->eax = r->eax - 1;
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    push(r, r->eax);
    r->eax = rd32(r, 0x4f8cd2);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    set_low16(&r->edx, rd16(r, 0x4f8cd8));
    push(r, r->eax);
    set_low16(&r->eax, rd16(r, 0x4f8cd0));
    r->eax = r->eax + r->edx;
    r->eax = r->eax - 1;
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    r->ebx = rd32(r, 0x4f9c07);
    push(r, r->eax);
    r->eax = rd32(r, 0x532a6c);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x18);
    r->eax = r->eax << 0x2;
    r->ecx = rd32(r, 0x4f8cce);
    r->eax = r->eax + 0x5345d4;
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    r->edx = rd32(r, r->eax);
    r->eax = r->edi;
    call(r, 0x4b65d0, 3);
    r->edx = 0x21;
    r->eax = rd32(r, r->ebp - 0x24);
    r->ebx = r->edi;
    wr32(r, r->ebp - 0x34, r->edi);
    call(r, 0x4123d0, 0);
    wr8(r, r->edi + 0x44, 0x10);
    if (r->esi != 0x21)
    {
        goto at_46c096;
    }
    wr8(r, r->edi + 0x110, 0x1);
at_46c096:
    r->edx = rd32(r, r->ebp - 0x34);
    r->eax = 0x54671c;
    call(r, 0x4b5e70, 0);
at_46c0a3:
    r->eax = rd32(r, r->ebp - 0x24);
    r->ecx = 0x2e;
    r->ebx = rd32(r, 0x4fbf84);
    r->edx = rd32(r, 0x4f8b5a);
    push(r, r->eax);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = rd32(r, 0x4f8b56);
    push(r, r->esi);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    r->edx = rd32(r, r->ebp - 0x24);
    r->ecx = 0x2f;
    r->ebx = rd32(r, 0x4fbf88);
    r->eax = rd32(r, 0x4f8b5e);
    push(r, r->edx);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->edx = rd32(r, 0x4f8b62);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = rd32(r, r->ebp - 0x24);
    r->ebx = rd32(r, 0x4fbf8c);
    r->edx = rd32(r, 0x4f8b6a);
    r->eax = rd32(r, 0x4f8b66);
    push(r, r->ecx);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    push(r, r->esi);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->ecx = 0x30;
    call(r, 0x471100, 2);
    r->ebx = rd32(r, r->ebp - 0x24);
    r->ecx = 0x31;
    r->edx = rd32(r, 0x4f8b72);
    r->eax = rd32(r, 0x4f8b6e);
    push(r, r->ebx);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    push(r, r->esi);
    r->ebx = rd32(r, 0x4fbf8c);
    r->edi = rd32(r, r->ebp - 0x24);
    call(r, 0x471100, 2);
    r->ecx = 0x5e;
    r->ebx = rd32(r, 0x4fbf90);
    push(r, r->edi);
    r->edx = rd32(r, 0x4f8b6a);
    r->eax = rd32(r, 0x4f8b66);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = 0x5f;
    r->ebx = rd32(r, 0x4fbf90);
    push(r, r->edi);
    r->edx = rd32(r, 0x4f8b72);
    r->eax = rd32(r, 0x4f8b6e);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = 0x32;
    r->ebx = rd32(r, 0x4fbf94);
    push(r, r->edi);
    r->edx = rd32(r, 0x4f8b7a);
    r->eax = rd32(r, 0x4f8b76);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = 0x33;
    r->ebx = rd32(r, 0x4fbf98);
    push(r, r->edi);
    r->edx = rd32(r, 0x4f8b82);
    r->eax = rd32(r, 0x4f8b7e);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = 0x5c;
    r->ebx = rd32(r, 0x4fbf9c);
    push(r, r->edi);
    r->edx = rd32(r, 0x4f8b7a);
    r->eax = rd32(r, 0x4f8b76);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = 0x5d;
    r->ebx = rd32(r, 0x4fbf9c);
    push(r, r->edi);
    r->edx = rd32(r, 0x4f8b82);
    r->eax = rd32(r, 0x4f8b7e);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    r->eax = 0x34;
    r->edi = 0;
    wr32(r, r->ebp - 0x18, r->eax);
at_46c21a:
    r->edx = rd32(r, r->ebp - 0x24);
    r->ecx = rd32(r, r->ebp - 0x18);
    r->ebx = rd32(r, 0x4fbfa4);
    r->eax = rd32(r, r->edi + 0x4f8b86);
    push(r, r->edx);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->edx = rd32(r, r->edi + 0x4f8bb6);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = rd32(r, r->ebp - 0x24);
    r->ebx = rd32(r, 0x4fbfa4);
    r->edx = rd32(r, r->edi + 0x4f8c16);
    r->eax = rd32(r, r->edi + 0x4f8be6);
    push(r, r->ecx);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    push(r, r->esi);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->ecx = rd32(r, r->ebp - 0x18);
    call(r, 0x471100, 2);
    r->ebx = rd32(r, r->ebp - 0x18);
    r->ebx = r->ebx + 1;
    r->edi = r->edi + 0x4;
    wr32(r, r->ebp - 0x18, r->ebx);
    if (r->edi != 0x30 && !r->port->env.failed)
    {
        goto at_46c21a;
    }
    r->edi = rd32(r, r->ebp - 0x24);
    r->ecx = 0x60;
    r->ebx = rd32(r, 0x4fbfa0);
    r->edx = rd32(r, 0x4f8b7a);
    r->eax = rd32(r, 0x4f8b76);
    push(r, r->edi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    push(r, r->esi);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = 0x61;
    r->ebx = rd32(r, 0x4fbfa0);
    push(r, r->edi);
    r->edx = rd32(r, 0x4f8b82);
    r->eax = rd32(r, 0x4f8b7e);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    r->edi = 0;
    r->edx = 0x4f;
    r->ecx = 0x4e;
    wr32(r, r->ebp - 0x3c, r->edx);
    wr32(r, r->ebp - 0x28, r->ecx);
at_46c2ce:
    r->ebx = rd32(r, r->ebp - 0x24);
    r->ecx = rd32(r, r->ebp - 0x28);
    r->edx = rd32(r, r->edi + 0x4f8c66);
    r->eax = rd32(r, r->edi + 0x4f8c5e);
    push(r, r->ebx);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    push(r, r->esi);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->ebx = rd32(r, 0x4fbfb0);
    call(r, 0x471100, 2);
    r->eax = rd32(r, r->ebp - 0x24);
    r->ecx = rd32(r, r->ebp - 0x3c);
    r->ebx = rd32(r, 0x4fbfb4);
    r->edx = rd32(r, r->edi + 0x4f8c76);
    push(r, r->eax);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = rd32(r, r->edi + 0x4f8c6e);
    push(r, r->esi);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->edi = r->edi + 0x4;
    call(r, 0x471100, 2);
    r->edx = rd32(r, r->ebp - 0x3c);
    r->ecx = rd32(r, r->ebp - 0x28);
    r->edx = r->edx + 0x2;
    r->ecx = r->ecx + 0x2;
    wr32(r, r->ebp - 0x3c, r->edx);
    wr32(r, r->ebp - 0x28, r->ecx);
    if (r->ecx != 0x52 && !r->port->env.failed)
    {
        goto at_46c2ce;
    }
    r->edi = 0x53;
    wr32(r, r->ebp - 0x20, r->ecx);
    wr32(r, r->ebp - 0x30, r->edi);
    r->edi = 0;
at_46c33f:
    r->edx = rd32(r, r->ebp - 0x24);
    r->ecx = rd32(r, r->ebp - 0x20);
    r->ebx = rd32(r, 0x4fbfb8);
    r->eax = rd32(r, r->edi + 0x4f8c7e);
    push(r, r->edx);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->edx = rd32(r, r->edi + 0x4f8c86);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = rd32(r, r->ebp - 0x24);
    r->ebx = rd32(r, 0x4fbfb8);
    r->edx = rd32(r, r->edi + 0x4f8c96);
    r->eax = rd32(r, r->edi + 0x4f8c8e);
    push(r, r->ecx);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    push(r, r->esi);
    r->ecx = rd32(r, r->ebp - 0x30);
    r->edi = r->edi + 0x4;
    call(r, 0x471100, 2);
    r->ebx = rd32(r, r->ebp - 0x30);
    r->eax = rd32(r, r->ebp - 0x20);
    r->ebx = r->ebx + 0x2;
    r->eax = r->eax + 0x2;
    wr32(r, r->ebp - 0x30, r->ebx);
    wr32(r, r->ebp - 0x20, r->eax);
    if (r->eax != 0x56 && !r->port->env.failed)
    {
        goto at_46c33f;
    }
    r->ecx = rd32(r, r->ebp - 0x24);
    r->ebx = rd32(r, 0x4fbfbc);
    r->edx = rd32(r, 0x4f8ca2);
    r->eax = rd32(r, 0x4f8c9e);
    push(r, r->ecx);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    push(r, r->esi);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->ecx = 0x56;
    call(r, 0x471100, 2);
    r->ebx = rd32(r, r->ebp - 0x24);
    r->ecx = 0x57;
    r->edx = rd32(r, 0x4f8caa);
    r->eax = rd32(r, 0x4f8ca6);
    push(r, r->ebx);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    push(r, r->esi);
    r->ebx = rd32(r, 0x4fbfc0);
    r->edi = rd32(r, r->ebp - 0x24);
    call(r, 0x471100, 2);
    r->ecx = 0x22;
    r->ebx = rd32(r, 0x4fbfc4);
    push(r, r->edi);
    r->edx = rd32(r, 0x4f8cb2);
    r->eax = rd32(r, 0x4f8cae);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    r->ecx = 0x23;
    r->ebx = rd32(r, 0x4fbfc4);
    push(r, r->edi);
    r->edx = rd32(r, 0x4f8cba);
    r->eax = rd32(r, 0x4f8cb6);
    push(r, r->esi);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    call(r, 0x471100, 2);
    return;
at_46c441:
    r->edx = 0;
    r->eax = 0;
    set_low8(&r->edx, rd8(r, r->ebp - 0x2c));
    set_low8(&r->eax, rd8(r, 0x532a68));
    call(r, 0x4178d0, 0);
    if (r->eax != r->esi && !r->port->env.failed)
    {
        goto at_46be4d;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_46becc;
at_46c45f:
    if (r->ebx != 0x1 && !r->port->env.failed)
    {
        goto at_46bef3;
    }
    r->eax = rd32(r, r->ebp - 0x24);
    set_low16(&r->edx, rd16(r, 0x4f8adc));
    push(r, r->eax);
    r->eax = rd32(r, r->ebp - 0x1c);
    r->eax = r->eax * r->edx;
    set_low16(&r->eax, (r->eax & 0xffff) + rd16(r, 0x4f8ad4));
    set_low16(&r->ecx, rd16(r, 0x4f8ad8));
    r->edx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = rd32(r, r->ebp - 0x14);
    r->eax = r->eax * r->ecx;
    r->ebx = rd32(r, 0x4fbf64);
    set_low16(&r->ecx, rd16(r, 0x4f8ad0));
    push(r, r->esi);
    r->eax = r->eax + r->ecx;
    r->ecx = 0x2b;
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    call(r, 0x471100, 2);
    r->edx = rd32(r, r->ebp - 0x24);
    r->eax = rd32(r, r->ebp - 0x1c);
    push(r, r->edx);
    set_low16(&r->eax, (r->eax & 0xffff) * rd16(r, 0x4f8adc));
    set_low16(&r->eax, (r->eax & 0xffff) + rd16(r, 0x4f8ad4));
    set_low16(&r->ecx, rd16(r, 0x4f8ad8));
    r->edx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = rd32(r, r->ebp - 0x14);
    r->eax = r->eax * r->ecx;
    r->ebx = rd32(r, 0x4fbf68);
    set_low16(&r->ecx, rd16(r, 0x4f8ad0));
    push(r, r->esi);
    r->eax = r->eax + r->ecx;
    r->ecx = 0x2d;
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    call(r, 0x471100, 2);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_46bef3;
}

uint32_t vertrix_port_ui_screen_actors_build_46b810(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x40
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
