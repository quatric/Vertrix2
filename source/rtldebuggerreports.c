#include "rtldebuggerreports.h"

enum
{
    /* The data selector the original hands over (mov edx, ds): the oracle's flat data segment. */
    DATA_SELECTOR = 0x10,

    DEBUGGER_NOTICE = 0x4e6220,
    ERROR_EXIT = 0x4eb4d4,
    ERROR_MESSAGE = 0x4e6250
};

/* Both start the same way: the debugger notice (0x4e6220) gets the text and the data selector, and
 * answers 1 when a debugger is attached (0x509764) and 0 otherwise. */
static uint32_t notify(Port *port, uint32_t text)
{
    return port_call(port, DEBUGGER_NOTICE, text, DATA_SELECTOR, 0, 0);
}

/* Original 0x4dee73 (eax = message text, edx = error number): with a debugger attached, the error
 * exit 0x4eb4d4 with the number (eax and ecx) and the edx the notice leaves; otherwise the message
 * 0x4e6250 with the text and the number (edx and ecx). Returns that callee's eax and edx. */
uint32_t vertrix_rtl_error_report(Port *port, uint32_t text, uint32_t number)
{
    if (notify(port, text) != 0)
    {
        return port_call(port, ERROR_EXIT, number, vertrix_lift_edx, 0, number);
    }
    return port_call(port, ERROR_MESSAGE, text, number, 0, number);
}

uint32_t vertrix_port_rtl_error_report_4dee73(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t result = vertrix_rtl_error_report(&port, entry->eax, entry->edx);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x4e628c (eax = message text, edx = error number): with a debugger attached, returns the
 * notice's 1 and edx; otherwise the message 0x4e6250 with the text and the number (edx and ecx),
 * and its eax and edx. */
uint32_t vertrix_port_rtl_error_message_4e628c(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t text = entry->eax;
    const uint32_t number = entry->edx;
    uint32_t result = notify(&port, text);
    if (result == 0)
    {
        result = port_call(&port, ERROR_MESSAGE, text, number, 0, number);
    }
    return port_return(&port, result, vertrix_lift_edx);
}
