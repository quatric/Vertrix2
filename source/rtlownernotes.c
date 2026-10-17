#include "rtlownernotes.h"

/* MFC-style notification routing: the window's method +0xd0 runs first, then the thread record's
 * handler gets the notification; if that does not take it, the parent window does. */

enum
{
    METHOD_PREPARE = 0xd0,
    THREAD_STATE = 0x4ce760,
    STATE_HANDLER = 8,
    HANDLER_WITH_ID = 0x18,
    HANDLER_WITHOUT_ID = 0x14,
    WINDOW_HWND = 0x1c,
    WINDOW_STYLE_HIGH = 0x25,
    WINDOW_PARAMETER = 0x40,
    WINDOW_ID = 0x4c,
    WINDOW_CODE = 0x58,
    WINDOW_DEFAULT = 0x4d70e0,
    WINDOW_OWNER = 0x4cf850,
    GET_PARENT = 0x4f19c4, /* import slot */
    FROM_HANDLE = 0x4cf8e0,
    OWNER_NOTIFY = 0x4cce60
};

/* Original 0x4d7140. Its callers read edx, the edx the last callee left. */
uint32_t vertrix_port_rtl_object_notify_owner_4d7140(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t window = entry->eax;
    const uint32_t table = port_u32(&port, window, 0);
    /* Every callee here runs with esi the window; edi is the table last called through. */
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t edi = table;
    uint32_t result = port_call_with(&port, port_u32(&port, table, METHOD_PREPARE), window, edx,
                                     ebx, ecx, window, edi, entry->ebp);
    edx = vertrix_lift_edx;
    const uint32_t state =
        port_call_with(&port, THREAD_STATE, result, edx, ebx, ecx, window, edi, entry->ebp);
    edx = vertrix_lift_edx;
    const uint32_t handler = port_u32(&port, state, STATE_HANDLER);
    const uint32_t code = port_u32(&port, window, WINDOW_CODE);
    if (handler != 0 && code != 0)
    {
        const uint32_t id = port_u32(&port, window, WINDOW_ID);
        edi = port_u32(&port, handler, 0);
        edx = window;
        ecx = code;
        ebx = id != 0 ? id : port_u32(&port, window, WINDOW_PARAMETER);
        const uint32_t method = id != 0 ? HANDLER_WITH_ID : HANDLER_WITHOUT_ID;
        result = port_call_with(&port, port_u32(&port, edi, method), handler, edx, ebx, ecx, window,
                                edi, entry->ebp);
        edx = vertrix_lift_edx;
        if (result == 0)
        {
            port_call_with(&port, WINDOW_DEFAULT, window, 0xffffffffu, ebx, ecx, window, edi,
                           entry->ebp);
            return port_return(&port, 0, vertrix_lift_edx);
        }
    }
    uint32_t owner =
        port_call_with(&port, WINDOW_OWNER, window, edx, ebx, ecx, window, edi, entry->ebp);
    edx = vertrix_lift_edx;
    if (owner != 0 && (port_u8(&port, window, WINDOW_STYLE_HIGH) & 1))
    {
        const uint32_t parent_arguments[3] = {port_u32(&port, window, WINDOW_HWND), 0, 0};
        vertrix_lift_in_esi = window;
        vertrix_lift_in_edi = edi;
        vertrix_lift_in_ebp = entry->ebp;
        const uint32_t hwnd = port_call_stack(&port, port_u32(&port, GET_PARENT, 0), owner, edx,
                                              owner, ecx, parent_arguments, 3);
        edx = vertrix_lift_edx;
        const uint32_t parent =
            port_call_stack(&port, FROM_HANDLE, hwnd, edx, owner, ecx, &hwnd, 1);
        vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
        edx = vertrix_lift_edx;
        if (parent != 0)
        {
            port_call_with(&port, OWNER_NOTIFY, parent, edx, owner, ecx, window, edi, entry->ebp);
            edx = vertrix_lift_edx;
            owner = 0;
        }
    }
    return port_return(&port, owner, edx);
}
