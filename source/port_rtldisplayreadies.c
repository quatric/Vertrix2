#include "port_rtldisplayreadies.h"

/* Returns 1 when the display object has both its first field and its +0x10 field set; otherwise it
 * continues at 0x47ed00. */

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

static uint32_t rd32(Regs *r, uint32_t address)
{
    return port_u32(r->port, address, 0);
}

/* Original 0x47f410: Returns 1 when the display object has both its first field and its +0x10 field
 * set; otherwise it continues at 0x47ed00. Evidence: no calls. Register-for-register from the
 * listing (0x47f410..0x47f428); labels are the original addresses. */
static void run(Regs *r)
{
    if (rd32(r, r->eax) == 0x0)
    {
        goto at_47ed00;
    }
    if (rd32(r, r->eax + 0x10) == 0x0)
    {
        goto at_47ed00;
    }
    r->eax = 0x1;
    return;
at_47ed00:
    r->eax = 0;
    return;
}

uint32_t vertrix_port_display_ready_47f410(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x10
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
