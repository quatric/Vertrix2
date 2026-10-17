#include "port_rtljpeglargestinputs.h"

/* libjpeg largest_input_value: ((2j + 1) * 255 + maxj) / (2 * maxj). */

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

/* idiv and div of edx:eax as the original's (a zero divisor or an overflowing quotient leaves
 * both registers). */
static void idiv32(Regs *r, uint32_t value)
{
    LiftFlags flags;
    memset(&flags, 0, sizeof flags);
    lift_idiv1(32, value, &r->eax, &r->edx, &flags);
}

/* Original 0x4c5d60: libjpeg largest_input_value: ((2j + 1) * 255 + maxj) / (2 * maxj). Evidence:
 * no calls. Register-for-register from the listing (0x4c5d60..0x4c5d7f); labels are the original
 * addresses. */
static void run(Regs *r)
{
    r->ebx = r->ebx + r->ebx;
    r->edx = r->ebx + 0x1;
    r->eax = r->edx;
    r->eax = r->eax << 0x4;
    r->eax = r->eax + r->edx;
    r->edx = r->eax;
    r->eax = r->eax << 0x4;
    r->eax = r->eax - r->edx;
    r->edx = r->eax + r->ecx;
    r->eax = r->edx;
    r->ecx = r->ecx + r->ecx;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    idiv32(r, r->ecx);
    return;
}

uint32_t vertrix_port_jpeg_largest_input_value_4c5d60(PORT_SIGNATURE)
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
