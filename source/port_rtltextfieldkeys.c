#include "port_rtltextfieldkeys.h"

/* Loops reading keys from the key set at 0x54d640 (call 0x476530) and dispatches on the scan code.
 */

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

static void wr32(Regs *r, uint32_t address, uint32_t value)
{
    port_set32(r->port, address, 0, value);
}

static void set_low8(uint32_t *reg, uint32_t value)
{
    *reg = (*reg & 0xffffff00u) | (value & 0xff);
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

/* Original 0x444e00: Loops reading keys from the key set at 0x54d640 (call 0x476530) and dispatches
 * on the scan code. Esc (1) and Enter (0x1c/0x56) both call object_reset_center(0x5588f8),
 * object_set_mode and actor_set_update(0x444c80), set byte +0x52 to 9 and call key_set_select. Esc
 * then calls parent_append_4b4c90. Enter calls parent_append_4b4cd0 only when the field's text
 * matches the string at 0x50e16a, then calls the optional callback at +0x184. Codes
 * 0x5f/0x60/0x5c/0x61/0xe/0x65 call the cursor-step, length-reset, remove (0xe Backspace) and
 * remove-after routines. A character key is first checked against the parent glyph set (spaces skip
 * this check), then limited to '0'..'9' when [obj]==0x1f5, then inserted with
 * object_text_insert_4b4790 (0x445070). Called from actor_swing_state 0x445090 and 0x445130.
 * Evidence: calls 0x476530, 0x4ca280, 0x477ed0, 0x4b4510, 0x4ac8f0, 0x4ccfe0, 0x4b4cd0, 0x4766b0,
 * 0x4ca210, 0x4b4c90, 0x4b4600, 0x4b4af0, 0x4b4610, 0x4b4620, 0x4b4630, 0x4b4950, 0x4cda90,
 * 0x4cda10, 0x4b4cb0, 0x4b4790; reads 0x532b3c. Register-for-register from the listing
 * (0x444e0b..0x445085); labels are the original addresses. */
static void run(Regs *r)
{
    r->ecx = r->eax;
    r->eax = r->ebp - 0x38;
    r->edx = 0x4ec1ec;
    r->ebx = 0x515160;
    push(r, r->port->env.chain);
    wr32(r, r->eax, pop(r));
    r->port->env.chain = r->eax;
    r->esi = 0;
    wr32(r, r->ebp - 0x34, r->edx);
    wr32(r, r->ebp - 0x30, r->ebx);
    wr32(r, r->ebp - 0x2c, r->esi);
    r->esi = 0x1;
    r->edi = 0;
at_444e3b:
    r->edx = r->ebp - 0x1c;
    r->eax = 0x54d640;
    call(r, 0x476530, 0);
    r->ebx = r->eax;
    if ((uint16_t)((r->eax & 0xffff)) != 0)
    {
        goto at_444e6b;
    }
    if (r->edi != rd32(r, r->ebp - 0x1c))
    {
        goto at_444fe3;
    }
    r->eax = rd32(r, r->ebp - 0x38);
    r->port->env.chain = r->eax;
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_444e6b:
    r->edx = rd32(r, r->ecx + 0x160);
    r->eax = r->ebp - 0x24;
    r->edx = rd32(r, r->edx + 0x15c);
    call(r, 0x4ca280, 0);
    wr32(r, r->ebp - 0x2c, r->esi);
    if ((uint16_t)((r->ebx & 0xffff)) == (uint16_t)0x1)
    {
        goto at_444f1e;
    }
    if ((uint16_t)((r->ebx & 0xffff)) == (uint16_t)0x1c)
    {
        goto at_444e9c;
    }
    if ((uint16_t)((r->ebx & 0xffff)) != (uint16_t)0x56)
    {
        goto at_444f71;
    }
at_444e9c:
    r->eax = 0x5588f8;
    call(r, 0x477ed0, 0);
    r->edx = 0;
    r->eax = r->ecx;
    call(r, 0x4b4510, 0);
    r->edx = 0x444c80;
    r->eax = r->ecx;
    call(r, 0x4ac8f0, 0);
    wr8(r, r->ecx + 0x52, 0x9);
    r->edx = 0x50e16a;
    r->eax = rd32(r, r->ebp - 0x24);
    call(r, 0x4ccfe0, 0);
    if (r->eax != 0)
    {
        goto at_444ed7;
    }
    r->eax = r->ecx;
    call(r, 0x4b4cd0, 0);
at_444ed7:
    r->ebx = rd32(r, r->ecx + 0x184);
    r->edx = r->ecx;
    if (r->ebx == 0)
    {
        goto at_444ef5;
    }
    r->eax = rd32(r, r->ecx + 0x160);
    r->eax = rd32(r, r->eax + 0x15c);
    call_all(r, rd32(r, r->edx + 0x184));
at_444ef5:
    r->eax = 0x54d640;
    r->edx = 0;
    call(r, 0x4766b0, 0);
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
at_444f1e:
    r->eax = 0x5588f8;
    call(r, 0x477ed0, 0);
    r->edx = 0;
    r->eax = r->ecx;
    call(r, 0x4b4510, 0);
    r->edx = 0x444c80;
    r->eax = r->ecx;
    call(r, 0x4ac8f0, 0);
    r->eax = r->ecx;
    wr8(r, r->ecx + 0x52, 0x9);
    call(r, 0x4b4c90, 0);
    r->edx = 0;
    r->eax = 0x54d640;
    call(r, 0x4766b0, 0);
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
at_444f71:
    if ((uint16_t)((r->ebx & 0xffff)) != (uint16_t)0x5f)
    {
        goto at_444f93;
    }
at_444f77:
    r->eax = r->ecx;
    call(r, 0x4b4600, 0);
at_444f7e:
    r->eax = r->ebp - 0x24;
    r->edx = r->edi;
    wr32(r, r->ebp - 0x2c, r->edi);
    call(r, 0x4ca210, 0);
    wr32(r, r->ebp - 0x2c, r->edi);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_444e3b;
at_444f93:
    if ((uint16_t)((r->ebx & 0xffff)) == (uint16_t)0x60)
    {
        goto at_444fba;
    }
    if ((uint16_t)((r->ebx & 0xffff)) == (uint16_t)0x5c)
    {
        goto at_444fc3;
    }
    if ((uint16_t)((r->ebx & 0xffff)) == (uint16_t)0x61)
    {
        goto at_444fcc;
    }
    if ((uint16_t)((r->ebx & 0xffff)) == (uint16_t)0xe)
    {
        goto at_444fd5;
    }
    if ((uint16_t)((r->ebx & 0xffff)) != (uint16_t)0x65 && !r->port->env.failed)
    {
        goto at_444f7e;
    }
    r->eax = r->ecx;
    call(r, 0x4b4af0, 0);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_444f7e;
at_444fba:
    r->eax = r->ecx;
    call(r, 0x4b4610, 0);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_444f7e;
at_444fc3:
    r->eax = r->ecx;
    call(r, 0x4b4620, 0);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_444f7e;
at_444fcc:
    r->eax = r->ecx;
    call(r, 0x4b4630, 0);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_444f7e;
at_444fd5:
    r->eax = r->ecx;
    call(r, 0x4b4950, 0);
    if (r->eax != 0x1 && !r->port->env.failed)
    {
        goto at_444f7e;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_444f77;
at_444fe3:
    r->eax = rd32(r, r->ecx + 0x160);
    r->edx = rd32(r, r->eax + 0x15c);
    r->eax = r->ebp - 0x18;
    call(r, 0x4ca280, 0);
    r->edx = 0x3;
    r->ebx = r->esi;
    wr32(r, r->ebp - 0x2c, r->edx);
    r->edx = 0;
    r->eax = r->ebp - 0x20;
    set_low8(&r->edx, rd8(r, r->ebp - 0x1c));
    call(r, 0x4cda90, 0);
    r->ebx = 0x4;
    r->eax = rd32(r, 0x532b3c);
    wr32(r, r->ebp - 0x2c, r->ebx);
    r->ebx = r->esi;
    if (r->edi != r->eax)
    {
        goto at_445031;
    }
    if (rd32(r, r->ebp - 0x1c) != 0x40)
    {
        goto at_445031;
    }
at_445027:
    call(r, 0x4cda10, 0);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_444e3b;
at_445031:
    if (r->ebx != 0x1)
    {
        goto at_44504c;
    }
    if (rd32(r, r->ebp - 0x1c) == 0x20)
    {
        goto at_44504c;
    }
    r->edx = 0;
    r->eax = r->ecx;
    set_low8(&r->edx, rd8(r, r->ebp - 0x1c));
    call(r, 0x4b4cb0, 0);
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_445027;
    }
at_44504c:
    if (r->ebx != 0x1)
    {
        goto at_445066;
    }
    if (rd32(r, r->ecx) != 0x1f5)
    {
        goto at_445066;
    }
    r->eax = rd32(r, r->ebp - 0x1c);
    if (r->eax < 0x30 && !r->port->env.failed)
    {
        goto at_445027;
    }
    if (r->eax > 0x39 && !r->port->env.failed)
    {
        goto at_445027;
    }
at_445066:
    if (r->ebx != 0x1 && !r->port->env.failed)
    {
        goto at_445027;
    }
    r->edx = rd32(r, r->ebp - 0x20);
    r->eax = r->ecx;
    call(r, 0x4b4790, 0);
    if (r->eax != r->ebx && !r->port->env.failed)
    {
        goto at_445027;
    }
    r->eax = r->ecx;
    call(r, 0x4b4610, 0);
    call(r, 0x4cda10, 0);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_444e3b;
}

uint32_t vertrix_port_text_field_key_handler_444e00(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x3c
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
