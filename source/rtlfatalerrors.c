#include "rtlfatalerrors.h"

#include "rtldebuggerreports.h"

enum
{
    MESSAGE = 0xc,
    INNER = 8,
    INNER_STATE = 0xc,
    FLAGS = 4,

    TERMINATE = 0x4e6c37,
    /* "return from "terminate" function!" */
    RETURNED_TEXT = 0x5127fb
};

/* Original 0x4e0c0c (eax = message text, edx = the exception record): the runtime's fatal error.
 * The message goes into the record (+0xc), its inner record (+8), when there is one, is set to
 * state 3, and bit 0 of the record's flags (+4) is set. Then the thread's terminate handler runs
 * (0x4e6c37, handed the inner record in eax and the caller's other registers), and should it
 * return, the runtime error 1 "return from "terminate" function!" (a tail jump into 0x4dee73, whose
 * code runs here). */
uint32_t vertrix_port_rtl_fatal_terminate_4e0c0c(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t record = entry->edx;
    port_set32(&port, record, MESSAGE, entry->eax);
    const uint32_t inner = port_u32(&port, record, INNER);
    if (inner != 0)
    {
        port_set8(&port, inner, INNER_STATE, 3);
    }
    port_set8(&port, record, FLAGS, port_u8(&port, record, FLAGS) | 1);
    port_call(&port, TERMINATE, inner, record, entry->ebx, entry->ecx);
    const uint32_t result = vertrix_rtl_error_report(&port, RETURNED_TEXT, 1);
    return port_return(&port, result, vertrix_lift_edx);
}
