#include "rtlsigncompares.h"

/* Original 0x4d8082 (eax, edx): the signed comparison of eax with edx as -1, 0 or 1, by the
 * runtime's carry trick, which also leaves edx changed (callers read it): unchanged when equal,
 * doubled when the signs differ, and otherwise the doubled complement of edx xor the halved
 * difference (the borrow shifted into its top bit). Callers branch on the flags it leaves: those of
 * the final decrement (sign and parity set for -1), or of the subtraction when equal (zero and
 * parity set); carry and overflow are clear either way. */
uint32_t vertrix_port_rtl_sign_compare_4d8082(PORT_SIGNATURE)
{
    Port port;
    port_open_frame(&port, calls, services, globals, entry, 0);
    const uint32_t a = entry->eax;
    uint32_t edx = entry->edx;
    LiftFlags flags = vertrix_lift_fl;
    flags.cf = 0;
    flags.of = 0;
    if (((a ^ edx) & 0x80000000u) == 0)
    {
        const uint32_t difference = a - edx;
        if (difference == 0)
        {
            flags.zf = 1;
            flags.sf = 0;
            flags.pf = 1;
            vertrix_lift_fl = flags;
            return port_return(&port, 0, edx);
        }
        const uint32_t borrow = a < edx ? 0x80000000u : 0;
        edx = ~(edx ^ (borrow | (difference >> 1)));
    }
    const int negative = (edx & 0x80000000u) == 0;
    flags.zf = 0;
    flags.sf = negative;
    flags.pf = negative;
    vertrix_lift_fl = flags;
    return port_return(&port, negative ? 0xffffffffu : 1, edx << 1);
}
