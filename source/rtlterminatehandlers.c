#include "rtlterminatehandlers.h"

enum
{
    THREAD_DATA = 0x507c9c, /* a procedure variable: the thread data's offset */
    STACK_BASE = 0x5c5c54,
    TERMINATE_HANDLER = 0x14,
    EXCEPTION_TEXT = 0xc,

    /* exit()'s state: the message-box flag, the exit hooks and the two buffers it frees. */
    QUIET_EXIT = 0x5c7b90,
    EXIT_HOOK = 0x507ce4,
    MESSAGE_HOOK = 0x507cd8,
    BUFFER_FIRST = 0x5c7b94,
    BUFFER_SECOND = 0x5c7b98,

    ERROR_REPORT = 0x4dee73,
    CURRENT_EXCEPTION = 0x4e0f8b,
    ERROR_BANNER = 0x4e6b2c,
    ERROR_TEXT = 0x4e6bac,
    FREE = 0x4ea190,
    EXIT_PROCESS = 0x4f1b4c, /* an import slot */
    /* "return from "terminate" function!" */
    RETURNED_TEXT = 0x512eac
};

/* The runtime error 1 with `text`; the caller's edx comes back. */
static uint32_t report(Port *port, const LiftEntry *entry, uint32_t text, uint32_t edx)
{
    const uint32_t result = port_call(port, ERROR_REPORT, text, 1, entry->ebx, entry->ecx);
    return port_return(port, result, edx);
}

/* exit(1) from 0x4e078c: with the message flag clear (0x5c7b90), the banner (0x4e6b2c), the error
 * text 0xf (0x4e6bac) and the message hook (0x507cd8); with it set, the exit hook (0x507ce4) when
 * there is one. Then ExitProcess(1), which under the verifier returns, so the original runs on into
 * 0x4e07d0, the release of the two buffers (0x5c7b94, 0x5c7b98, each freed by 0x4ea190 and
 * cleared), and returns from there. */
static uint32_t exit_one(Port *port, const LiftEntry *entry, uint32_t edx)
{
    const uint32_t ecx = entry->ecx;
    uint32_t eax = 1;
    if (port_u32(port, QUIET_EXIT, 0) == 0)
    {
        port_call(port, ERROR_BANNER, 1, edx, 1, ecx);
        eax = port_call(port, ERROR_TEXT, 0, 0xf, 1, ecx);
        eax = port_call(port, port_u32(port, MESSAGE_HOOK, 0), eax, vertrix_lift_edx, 1, ecx);
        edx = vertrix_lift_edx;
    }
    else if (port_u32(port, EXIT_HOOK, 0) != 0)
    {
        eax = port_call(port, port_u32(port, EXIT_HOOK, 0), 0, 0xff, 1, ecx);
        edx = vertrix_lift_edx;
    }
    const uint32_t code = 1;
    eax = port_call_stack(port, EXIT_PROCESS, eax, edx, 1, ecx, &code, 1);
    const uint32_t kept_edx = vertrix_lift_edx;
    uint32_t ebx = 1;
    const uint32_t first = port_u32(port, BUFFER_FIRST, 0);
    if (first != 0)
    {
        ebx = 0;
        eax = port_call(port, FREE, first, first, ebx, ecx);
        port_set32(port, BUFFER_FIRST, 0, ebx);
    }
    const uint32_t second = port_u32(port, BUFFER_SECOND, 0);
    if (second != 0)
    {
        eax = port_call(port, FREE, second, vertrix_lift_edx, ebx, second);
        port_set32(port, BUFFER_SECOND, 0, 0);
    }
    return port_return(port, eax, kept_edx);
}

/* Original 0x4e6c37: terminate(). The thread data (the offset 0x507c9c's procedure returns, from
 * 0x5c5c54) holds the terminate handler (+0x14); when there is one it runs with the caller's
 * registers, and should it return, the runtime error 1 "return from "terminate" function!"
 * (0x4dee73). Without one, the current exception (0x4e0f8b) is reported by its text (+0xc) as
 * runtime error 1; without a text, exit(1) (a jump into 0x4e078c). */
uint32_t vertrix_port_rtl_terminate_4e6c37(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t offset = port_call(&port, port_u32(&port, THREAD_DATA, 0), entry->eax,
                                      entry->edx, entry->ebx, entry->ecx);
    const uint32_t handler =
        port_u32(&port, offset + port_u32(&port, STACK_BASE, 0), TERMINATE_HANDLER);
    if (handler != 0)
    {
        port_call(&port, handler, handler, vertrix_lift_edx, entry->ebx, entry->ecx);
        return report(&port, entry, RETURNED_TEXT, vertrix_lift_edx);
    }
    const uint32_t exception =
        port_call(&port, CURRENT_EXCEPTION, 0, vertrix_lift_edx, entry->ebx, entry->ecx);
    const uint32_t edx = vertrix_lift_edx;
    const uint32_t text = port_u32(&port, exception, EXCEPTION_TEXT);
    if (text != 0)
    {
        return report(&port, entry, text, edx);
    }
    return exit_one(&port, entry, edx);
}
