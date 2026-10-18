#include "rtltooltiptexts.h"

enum
{
    /* The frame: three saved registers, then (from ebp = entry esp - 0xc) the result pointer, the
     * hint string (-8), the exception record and the window text (-0x11c). */
    BELOW = 0x128,
    FRAME = 0xc,
    HINT = 8,
    TEXT = 0x11c,
    TEXT_SIZE = 0x100,

    /* The tooltip notification: its window, its id, its code, the text (+0x10, 80 characters) and
     * the flags of the ANSI (+0x64) and wide (+0xb4) forms; flag bit 0: the id is a window. */
    NOTIFY_WINDOW = 0,
    NOTIFY_ID = 4,
    NOTIFY_CODE = 8,
    NOTIFY_TEXT = 0x10,
    NOTIFY_FLAGS_ANSI = 0x64,
    NOTIFY_FLAGS_WIDE = 0xb4,
    ID_IS_WINDOW = 1,
    TEXT_LENGTH = 0x50,
    TTN_GETDISPINFOA = 0xfffffdf8u,
    TTN_GETDISPINFOW = 0xfffffdeeu,

    /* The hint's first part, up to the separator 0xa. */
    HINT_PART = 1,
    HINT_SEPARATOR = 0xa,
    /* SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER. */
    POSITION_FLAGS = 0x13,

    HANDLED = 0x4cba60,
    STRING_INIT = 0x4ca070,
    STRING_RELEASE = 0x4ca210,
    WINDOW_TEXT = 0x4db950,
    TEXT_PART = 0x4db980,
    TO_WIDE = 0x4ca770,
    GET_DLG_CTRL_ID = 0x4f1980,
    COPY_ANSI = 0x4f1d20,
    SET_WINDOW_POS = 0x4f1ad8
};

/* Original 0x4d5ab0 (eax = the control, ebx = a tooltip's TTN_GETDISPINFO notification, ecx = the
 * result): unless 0x4cba60 handles it (returning 0), fills the tooltip's text: the control id
 * (GetDlgCtrlID when the id is a window), its window text (0x4db950) cut at the separator 0xa
 * (0x4db980) into a string, copied as 80 ANSI (lstrcpynA) or wide (0x4ca770) characters, the result
 * cleared and the tooltip placed without moving (SetWindowPos with 0x13). Returns 1; edx is the
 * string release's. The exception frame at fs:[0] is left out (docs/NATIVE-PORTS.md). */
uint32_t vertrix_port_rtl_tooltip_text_4d5ab0(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[BELOW + 8];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t control = entry->eax;
    const uint32_t notify = entry->ebx;
    const uint32_t frame = entry->esp - FRAME;
    const uint32_t hint = frame - HINT;
    const uint32_t text = frame - TEXT;
    uint32_t args[7];
    if (port_call_with(&port, HANDLED, control, entry->edx, notify, entry->ecx, notify, control,
                       frame) != 0)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    port_call(&port, STRING_INIT, hint, vertrix_lift_edx, notify, entry->ecx);
    const uint32_t code = port_u32(&port, notify, NOTIFY_CODE);
    uint32_t id = port_u32(&port, notify, NOTIFY_ID);
    if ((code == TTN_GETDISPINFOA &&
         (port_u8(&port, notify, NOTIFY_FLAGS_ANSI) & ID_IS_WINDOW) != 0) ||
        (code == TTN_GETDISPINFOW &&
         (port_u8(&port, notify, NOTIFY_FLAGS_WIDE) & ID_IS_WINDOW) != 0))
    {
        args[0] = id;
        id = port_call_stack(&port, GET_DLG_CTRL_ID, id, vertrix_lift_edx, notify, entry->ecx, args,
                             1) &
             0xffff;
    }
    if (id != 0)
    {
        args[0] = id;
        args[1] = text;
        args[2] = TEXT_SIZE;
        port_call_stack(&port, WINDOW_TEXT, id, text, notify, entry->ecx, args, 3);
        args[0] = hint;
        args[1] = text;
        args[2] = HINT_PART;
        args[3] = HINT_SEPARATOR;
        port_call_stack(&port, TEXT_PART, hint, vertrix_lift_edx, notify, entry->ecx, args, 4);
    }
    if (port_u32(&port, notify, NOTIFY_CODE) == TTN_GETDISPINFOA)
    {
        args[0] = notify + NOTIFY_TEXT;
        args[1] = port_u32(&port, hint, 0);
        args[2] = TEXT_LENGTH;
        port_call_stack(&port, COPY_ANSI, hint, vertrix_lift_edx, notify + NOTIFY_TEXT, entry->ecx,
                        args, 3);
    }
    else
    {
        port_call(&port, TO_WIDE, notify + NOTIFY_TEXT, port_u32(&port, hint, 0), TEXT_LENGTH,
                  entry->ecx);
    }
    port_set32(&port, entry->ecx, 0, 0);
    args[0] = port_u32(&port, notify, NOTIFY_WINDOW);
    args[1] = 0;
    args[2] = 0;
    args[3] = 0;
    args[4] = 0;
    args[5] = 0;
    args[6] = POSITION_FLAGS;
    port_call_stack(&port, SET_WINDOW_POS, entry->ecx, vertrix_lift_edx, notify, entry->ecx, args,
                    7);
    port_call(&port, STRING_RELEASE, hint, 0, notify, entry->ecx);
    return port_return(&port, 1, vertrix_lift_edx);
}
