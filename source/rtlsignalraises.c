#include "rtlsignalraises.h"

enum
{
    /* The signals: 1 (abort), 2 (interrupt, through the handler 0x4e8bd4 sends to), and up to 12.
     */
    SIGNAL_ABORT = 1,
    SIGNAL_INTERRUPT = 2,
    SIGNAL_LAST = 12,
    INTERRUPT_CODE = 0x8c,

    /* The handler values that are no routine: default, ignore and error. */
    HANDLER_DEFAULT = 1,
    HANDLER_IGNORE = 2,
    HANDLER_ERROR = 3,
    RESET_TO = 2,

    FAILED = 0xffffffffu,

    HANDLER_OF = 0x4e8a58,
    SET_HANDLER = 0x4e8a10,
    INTERRUPT = 0x4e8bd4,
    ABORT_MESSAGE = 0x4ea2a8,
    DEFAULTS_KEPT = 0x4e8b24,
    RESTORE_CONSOLE = 0x4e8b8c
};

/* Original 0x4e8cc8 (eax = the signal): the runtime's raise. A signal outside 1..12 returns -1.
 * The interrupt (2) goes to 0x4e8bd4 with 0x8c. Any other runs its handler (0x4e8a58), first
 * reset to 2 (0x4e8a10), unless the handler is 1, 2 or 3; an abort (1) whose handler is 2 first
 * reports (0x4ea2a8). Then, when 0x4e8b24 finds the defaults changed, 0x4e8b8c runs. Returns 0;
 * edx is kept. */
uint32_t vertrix_port_rtl_raise_4e8cc8(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t signal = entry->eax;
    const uint32_t handler = port_call(&port, HANDLER_OF, signal, entry->edx, signal, entry->ecx);
    uint32_t edx = signal - 1;
    if (edx > SIGNAL_LAST - 1)
    {
        return port_return(&port, FAILED, entry->edx);
    }
    if (signal == SIGNAL_INTERRUPT)
    {
        port_call(&port, INTERRUPT, INTERRUPT_CODE, edx, signal, handler);
        return port_return(&port, 0, entry->edx);
    }
    uint32_t eax = handler;
    if (signal == SIGNAL_ABORT && handler == HANDLER_IGNORE)
    {
        eax = port_call(&port, ABORT_MESSAGE, handler, edx, signal, handler);
        edx = vertrix_lift_edx;
    }
    if (handler != HANDLER_DEFAULT && handler != HANDLER_IGNORE && handler != HANDLER_ERROR)
    {
        port_call(&port, SET_HANDLER, signal, RESET_TO, signal, handler);
        eax = port_call(&port, handler, signal, vertrix_lift_edx, signal, handler);
        edx = vertrix_lift_edx;
    }
    if (port_call(&port, DEFAULTS_KEPT, eax, edx, signal, handler) == 0)
    {
        port_call(&port, RESTORE_CONSOLE, 0, vertrix_lift_edx, signal, handler);
    }
    return port_return(&port, 0, entry->edx);
}
