#include "port_rtlgamescreensetups.h"

/* Sets the view rect (0x41ab90), loads scenes 0 and 1 (0x41e280) indexed by 0x532a70, and makes
 * overlay sprites. */

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

/* The last value pushed taken back. */
static uint32_t pop(Regs *r)
{
    return r->pushed != 0 ? r->stack[--r->pushed] : 0;
}

/* An indirect call (an import or a method): every value pushed passed and popped, as stdcall. */
static void call_all(Regs *r, uint32_t target)
{
    call_with_stack(r, target, r->pushed, 0);
}

/* Original 0x424360: Sets the view rect (0x41ab90), loads scenes 0 and 1 (0x41e280) indexed by
 * 0x532a70, and makes overlay sprites. It then builds three record tables (0x4120a0/0x4122f0) from
 * '.\FILTRE\' (0x4fcff8) paths taken from the name tables 0x533310 and 0x534750 and passes them to
 * lifted_game_screen (0x46c9d0). After that it resets key records, calls game_keys_setup
 * (0x425ae0), adds layers and the HUD, and installs handlers 0x423fb0 and 0x424760 through
 * state_set_bc and state_set_c0. When 0x532a84 is 1 it waits on handles at 0x5bb4a8 and may release
 * tables and switch to state 0x41e780, 0x41c6d0 or 0x41b5e0 instead. Evidence: calls 0x4ca070,
 * 0x41ab90, 0x482540, 0x41e280, 0x45f770, 0x472d00, 0x4b7cd0, 0x4ca310, 0x45f540, 0x4ca000,
 * 0x4120a0, 0x4122f0, 0x46b800, 0x471a70, 0x4719f0, 0x4719e0, 0x46c9d0, 0x476090, 0x425ae0,
 * 0x46f000, 0x4ac1c0, 0x41aa20, 0x41ab00, 0x41aaa0 and 10 more; reads 0x532a84, 0x532a70, 0x532b40,
 * 0x532928, 0x544070, 0x4f1cf8, 0x5bb494, 0x4f1c7c, 0x5bb47c, 0x5bb488, 0x532a80; writes 0x532a40,
 * 0x532a44, 0x532a3c, 0x532928, 0x532a20, 0x532a24. Register-for-register from the listing
 * (0x42436e..0x424757); labels are the original addresses. */
static void run(Regs *r)
{
    r->esi = r->eax;
    r->eax = r->ebp - 0x38;
    r->edx = 0x4ec1ec;
    r->ecx = 0x5143bc;
    r->edi = 0x1;
    push(r, r->port->env.chain);
    wr32(r, r->eax, pop(r));
    r->port->env.chain = r->eax;
    r->ebx = 0;
    r->eax = r->ebp - 0x24;
    wr32(r, r->ebp - 0x34, r->edx);
    wr32(r, r->ebp - 0x30, r->ecx);
    wr32(r, r->ebp - 0x2c, r->ebx);
    call(r, 0x4ca070, 0);
    r->eax = r->ebp - 0x20;
    wr32(r, r->ebp - 0x2c, r->edi);
    call(r, 0x4ca070, 0);
    wr32(r, r->ebp - 0x2c, 0x2);
    r->eax = r->ebp - 0x1c;
    r->edx = 0x3;
    call(r, 0x4ca070, 0);
    r->eax = r->esi;
    wr32(r, r->ebp - 0x2c, r->edx);
    call(r, 0x41ab90, 0);
    if (rd32(r, 0x532a84) == 0x0)
    {
        goto at_424631;
    }
    r->eax = 0x598d30;
    call(r, 0x482540, 0);
at_4243e4:
    r->ebx = rd32(r, 0x532a84);
    if (r->ebx == 0x1)
    {
        goto at_424640;
    }
at_4243f3:
    r->eax = 0x1;
    r->ebx = 0;
    r->edx = rd32(r, 0x532a70);
    wr32(r, 0x532a40, r->ebx);
    wr32(r, 0x532a44, r->eax);
    r->eax = 0;
    wr32(r, 0x532a3c, r->ebx);
    call(r, 0x41e280, 0);
    r->eax = 0x1;
    r->edx = rd32(r, 0x532a70);
    call(r, 0x41e280, 0);
    call(r, 0x45f770, 0);
    if (rd32(r, 0x532b40) != 0x1)
    {
        goto at_42443d;
    }
    r->eax = 0;
    call(r, 0x472d00, 0);
at_42443d:
    call(r, 0x4b7cd0, 0);
    r->edx = rd32(r, 0x532a70);
    r->edx = r->edx << 0x2;
    r->eax = r->ebp - 0x24;
    r->edx = r->edx + 0x533310;
    call(r, 0x4ca310, 0);
    r->ebx = rd32(r, r->ebp - 0x24);
    r->edx = 0x4fcff8;
    r->eax = r->ebp - 0x13c;
    call(r, 0x45f540, 0);
    r->eax = 0x7b8;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_424497;
    }
    r->ecx = 0x4;
    r->edx = 0x7a;
    r->ebx = 0x3;
    wr32(r, r->ebp - 0x18, r->eax);
    wr32(r, r->ebp - 0x2c, r->ecx);
    call(r, 0x4120a0, 0);
    wr32(r, r->ebp - 0x2c, r->ebx);
at_424497:
    r->edx = r->ebp - 0x13c;
    wr32(r, 0x532928, r->eax);
    call(r, 0x4122f0, 0);
    r->eax = rd32(r, 0x532928);
    call(r, 0x46b800, 0);
    call(r, 0x471a70, 0);
    r->eax = rd32(r, 0x544070);
    r->eax = rd32(r, r->eax + 0x268);
    call(r, 0x4719f0, 0);
    call(r, 0x4719e0, 0);
    r->eax = 0x7b8;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_4244f5;
    }
    r->edi = 0x6;
    r->edx = 0x1;
    wr32(r, r->ebp - 0x18, r->eax);
    wr32(r, r->ebp - 0x2c, r->edi);
    call(r, 0x4120a0, 0);
    wr32(r, r->ebp - 0x2c, 0x3);
at_4244f5:
    r->edi = r->eax;
    r->eax = 0x7b8;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_424522;
    }
    r->ecx = 0x8;
    r->edx = 0x1;
    r->ebx = 0x3;
    wr32(r, r->ebp - 0x18, r->eax);
    wr32(r, r->ebp - 0x2c, r->ecx);
    call(r, 0x4120a0, 0);
    wr32(r, r->ebp - 0x2c, r->ebx);
at_424522:
    r->ecx = r->eax;
    r->edx = rd32(r, 0x532a70);
    r->edx = r->edx << 0x2;
    r->eax = r->ebp - 0x20;
    r->edx = r->edx + 0x534750;
    call(r, 0x4ca310, 0);
    r->ebx = rd32(r, r->ebp - 0x20);
    r->edx = 0x4fcff8;
    r->eax = r->ebp - 0x13c;
    call(r, 0x45f540, 0);
    r->edx = r->ebp - 0x13c;
    r->eax = r->edi;
    call(r, 0x4122f0, 0);
    r->edx = rd32(r, 0x532a70);
    r->edx = r->edx << 0x2;
    r->eax = r->ebp - 0x1c;
    r->edx = r->edx + 0x534750;
    call(r, 0x4ca310, 0);
    r->ebx = rd32(r, r->ebp - 0x1c);
    r->edx = 0x4fcff8;
    r->eax = r->ebp - 0x13c;
    call(r, 0x45f540, 0);
    r->edx = r->ebp - 0x13c;
    r->eax = r->ecx;
    call(r, 0x4122f0, 0);
    r->ebx = r->ecx;
    r->eax = rd32(r, 0x532928);
    r->edx = r->edi;
    call(r, 0x46c9d0, 0);
    r->eax = 0x54d640;
    call(r, 0x476090, 0);
    r->eax = r->esi;
    call(r, 0x425ae0, 0);
    r->edi = rd32(r, 0x532928);
    if (r->edi == 0)
    {
        goto at_4245ca;
    }
    r->ecx = rd32(r, r->edi + 0x7b4);
    r->edx = 0x2;
    r->eax = r->edi;
    call_all(r, rd32(r, r->ecx));
at_4245ca:
    call(r, 0x46f000, 0);
    call(r, 0x4ac1c0, 0);
    r->eax = r->esi;
    call(r, 0x41aa20, 0);
    call(r, 0x471a70, 0);
    r->eax = r->esi;
    call(r, 0x41ab00, 0);
    r->eax = r->esi;
    call(r, 0x41aaa0, 0);
    r->eax = 0;
    r->edx = 0x423fb0;
    wr32(r, 0x532a20, r->eax);
    wr32(r, 0x532a24, r->eax);
    r->eax = r->esi;
    wr8(r, r->esi + 0xc8, 0x0);
    call(r, 0x418840, 0);
    r->edx = 0x424760;
    r->eax = r->esi;
    call(r, 0x418820, 0);
    call(r, 0x4cda10, 0);
    r->eax = rd32(r, r->ebp - 0x38);
    r->port->env.chain = r->eax;
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_424631:
    r->eax = 0x598d30;
    call(r, 0x482550, 0);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4243e4;
at_424640:
    r->eax = 0x5bb254;
    call(r, 0x48c260, 0);
    if (r->eax != r->ebx && !r->port->env.failed)
    {
        goto at_4243f3;
    }
    push(r, 0xffffffffu);
    push(r, 0x0);
    push(r, 0x5bb4a8);
    push(r, 0x3);
    call_all(r, rd32(r, 0x4f1cf8));
    if (r->eax == 0)
    {
        goto at_4246cf;
    }
    if (r->eax == r->ebx)
    {
        goto at_4246e2;
    }
    if (r->eax != 0x2 && !r->port->env.failed)
    {
        goto at_4243f3;
    }
    r->edi = rd32(r, 0x5bb494);
    push(r, r->edi);
    call_all(r, rd32(r, 0x4f1c7c));
    r->eax = 0x5588f8;
    r->edx = 0x41e780;
    call(r, 0x477ed0, 0);
    call(r, 0x45ea80, 0);
    r->eax = r->esi;
    call(r, 0x418840, 0);
    r->eax = r->ebp - 0x1c;
    r->edx = 0;
    call(r, 0x4ca210, 0);
    r->eax = r->ebp - 0x20;
    r->edx = 0;
    call(r, 0x4ca210, 0);
    r->eax = r->ebp - 0x24;
    r->edx = 0;
    call(r, 0x4ca210, 0);
    r->eax = rd32(r, r->ebp - 0x38);
    r->port->env.chain = r->eax;
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4246cf:
    r->ecx = rd32(r, 0x5bb47c);
    push(r, r->ecx);
    call_all(r, rd32(r, 0x4f1c7c));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4243f3;
at_4246e2:
    r->eax = rd32(r, 0x5bb488);
    push(r, r->eax);
    call_all(r, rd32(r, 0x4f1c7c));
    r->eax = 0x5588f8;
    call(r, 0x477ed0, 0);
    if (r->ebx != rd32(r, 0x532a80))
    {
        goto at_424743;
    }
    call(r, 0x45ea80, 0);
    r->edx = 0x41c6d0;
at_42470b:
    r->eax = r->esi;
    call(r, 0x418840, 0);
    r->eax = r->ebp - 0x1c;
    r->edx = 0;
    call(r, 0x4ca210, 0);
    r->eax = r->ebp - 0x20;
    r->edx = 0;
    call(r, 0x4ca210, 0);
    r->eax = r->ebp - 0x24;
    r->edx = 0;
    call(r, 0x4ca210, 0);
    r->eax = rd32(r, r->ebp - 0x38);
    r->port->env.chain = r->eax;
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_424743:
    call(r, 0x45ea80, 0);
    call(r, 0x45e8f0, 0);
    call(r, 0x45e910, 0);
    r->edx = 0x41b5e0;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_42470b;
}

uint32_t vertrix_port_game_screen_setup_424360(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x140
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
