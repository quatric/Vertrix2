#include "rtlsubclassprocs.h"

enum
{
    /* The frame under the return slot: ebx, then 0x84 bytes of locals (from the low end S): the
     * jump buffer (S), the message record for the application (S+0x34: window, message, wparam,
     * lparam), the window's control record (S+0x60), the exception's object (S+0x78), the control
     * state (S+0x7c) and the result (S+0x80). */
    BELOW = 0x88,
    ARGUMENTS = 4,
    LOCALS = 0x88,
    MESSAGE_RECORD = 0x34,
    CONTROL_RECORD = 0x60,
    OLD_PROCEDURE = 0x74,
    EXCEPTION_OBJECT = 0x78,
    CONTROL_STATE = 0x7c,
    RESULT = 0x80,

    /* The stdcall arguments above the return slot. */
    ARGUMENT_WINDOW = 4,
    ARGUMENT_MESSAGE = 8,
    ARGUMENT_WPARAM = 0xc,
    ARGUMENT_LPARAM = 0x10,

    WM_ACTIVATE = 6,
    WM_SETCURSOR = 0x20,
    WM_NCDESTROY = 0x82,
    WM_INITDIALOG = 0x110,
    GWL_WNDPROC = 0xfffffffcu,
    PROPERTY = 0x502778,
    LONGJMP_RETURN = 1,
    APPLICATION_HANDLE_EXCEPTION = 0x70,

    GET_PROP = 0x4f19cc,
    REMOVE_PROP = 0x4f1a7c,
    SET_WINDOW_LONG = 0x4f1ad0,
    CALL_WINDOW_PROC = 0x4f18f0,
    SET_JUMP = 0x4d9f06,
    CONTROL_OF = 0x4cf8e0,
    CONTROL_SAVE = 0x4cf4a0,
    CONTROL_RESTORE = 0x4cf4d0,
    ACTIVATE = 0x4cf560,
    SET_CURSOR = 0x4cf5d0,
    APPLICATION = 0x4cbe80,
    RELEASE = 0x4d9350,
    EXCEPTION_DONE = 0x4da6b6
};

/* A call handing the callee this routine's own esi, edi and ebp (0x4cf8e0 and the control calls
 * read ebp; the jump buffer saves them all). */
static uint32_t call(Port *port, const LiftEntry *entry, uint32_t target, uint32_t eax,
                     uint32_t edx, uint32_t ebx, const uint32_t *stack, unsigned count)
{
    return port_forward_stack(port, entry, target, eax, edx, ebx, entry->ecx, entry->esi, stack,
                              count);
}

/* The original window procedure with this message (CallWindowProcA). */
static uint32_t call_original(Port *port, const LiftEntry *entry, uint32_t locals, uint32_t ebx)
{
    const uint32_t args[5] = {
        port_u32(port, locals, OLD_PROCEDURE), port_u32(port, entry->esp, ARGUMENT_WINDOW),
        port_u32(port, entry->esp, ARGUMENT_MESSAGE), port_u32(port, entry->esp, ARGUMENT_WPARAM),
        port_u32(port, entry->esp, ARGUMENT_LPARAM)};
    return call(port, entry, CALL_WINDOW_PROC, args[0], vertrix_lift_edx, ebx, args, 5);
}

/* Original 0x4cfa20 (stdcall: window, message, wparam, lparam): the procedure of a subclassed
 * dialog window, whose original procedure is its property 0x502778 (GetPropA), under a jump
 * buffer (0x4d9f06). WM_INITDIALOG runs the original between saving and restoring the window's
 * control (0x4cf8e0, 0x4cf4a0, 0x4cf4d0). WM_ACTIVATE tells 0x4cf560 with the controls of the
 * window and the lparam; WM_SETCURSOR asks 0x4cf5d0 with the window's control and the lparam's two
 * halves, and passes on only when it answers 0; WM_NCDESTROY puts the original back
 * (SetWindowLongA) and removes the property. Every other message, and those three, then go to the
 * original. Returns the original's result. When the buffer's jump comes back (1) the message goes
 * to the application's exception handler (method +0x70 of 0x4cbe80) and the exception is released
 * (0x4d9350, 0x4da6b6). The exception frame at fs:[0] is left out (docs/NATIVE-PORTS.md). */
uint32_t vertrix_port_rtl_subclass_proc_4cfa20(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[BELOW + 8 + 4 * ARGUMENTS];
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, ARGUMENTS);
    port_set32(&port, entry->esp, -4u, entry->ebx);
    const uint32_t locals = entry->esp - LOCALS;
    const uint32_t window = port_u32(&port, entry->esp, ARGUMENT_WINDOW);
    const uint32_t message = port_u32(&port, entry->esp, ARGUMENT_MESSAGE);
    const uint32_t wparam = port_u32(&port, entry->esp, ARGUMENT_WPARAM);
    const uint32_t lparam = port_u32(&port, entry->esp, ARGUMENT_LPARAM);
    uint32_t args[5] = {window, PROPERTY};
    port_set32(&port, locals, OLD_PROCEDURE,
               call(&port, entry, GET_PROP, window, entry->edx, entry->ebx, args, 2));
    port_set32(&port, locals, RESULT, 0);
    if (call(&port, entry, SET_JUMP, locals, vertrix_lift_edx, entry->ebx, NULL, 0) ==
        LONGJMP_RETURN)
    {
        port_set32(&port, locals, MESSAGE_RECORD, window);
        port_set32(&port, locals, MESSAGE_RECORD + 4, message);
        port_set32(&port, locals, MESSAGE_RECORD + 8, wparam);
        port_set32(&port, locals, MESSAGE_RECORD + 0xc, lparam);
        const uint32_t application =
            call(&port, entry, APPLICATION, lparam, vertrix_lift_edx, entry->ebx, NULL, 0);
        const uint32_t table = port_u32(&port, application, 0);
        const uint32_t record = locals + MESSAGE_RECORD;
        port_set32(&port, locals, RESULT,
                   port_forward_stack(&port, entry,
                                      port_u32(&port, table, APPLICATION_HANDLE_EXCEPTION),
                                      application, port_u32(&port, locals, EXCEPTION_OBJECT),
                                      record, table, entry->esi, NULL, 0));
        const uint32_t released =
            port_forward_stack(&port, entry, RELEASE, port_u32(&port, locals, EXCEPTION_OBJECT),
                               vertrix_lift_edx, record, table, entry->esi, NULL, 0);
        port_forward_stack(&port, entry, EXCEPTION_DONE, released, vertrix_lift_edx, record, table,
                           entry->esi, NULL, 0);
        return port_return(&port, port_u32(&port, locals, RESULT), vertrix_lift_edx);
    }
    uint32_t pass = 1;
    if (message == WM_INITDIALOG)
    {
        args[0] = window;
        const uint32_t control =
            call(&port, entry, CONTROL_OF, window, vertrix_lift_edx, 1, args, 1);
        args[0] = control;
        args[1] = locals + CONTROL_RECORD;
        args[2] = locals + CONTROL_STATE;
        call(&port, entry, CONTROL_SAVE, args[1], vertrix_lift_edx, control, args, 3);
        port_set32(&port, locals, RESULT, call_original(&port, entry, locals, control));
        args[0] = control;
        args[1] = locals + CONTROL_RECORD;
        args[2] = port_u32(&port, locals, CONTROL_STATE);
        call(&port, entry, CONTROL_RESTORE, args[1], vertrix_lift_edx, control, args, 3);
        return port_return(&port, port_u32(&port, locals, RESULT), vertrix_lift_edx);
    }
    if (message == WM_ACTIVATE)
    {
        args[0] = lparam;
        const uint32_t other = call(&port, entry, CONTROL_OF, lparam, vertrix_lift_edx, 1, args, 1);
        args[0] = window;
        const uint32_t control =
            call(&port, entry, CONTROL_OF, window, vertrix_lift_edx, 1, args, 1);
        args[0] = control;
        args[1] = wparam;
        args[2] = other;
        call(&port, entry, ACTIVATE, control, vertrix_lift_edx, 1, args, 3);
    }
    else if (message == WM_SETCURSOR)
    {
        args[0] = window;
        const uint32_t control =
            call(&port, entry, CONTROL_OF, window, vertrix_lift_edx, 1, args, 1);
        args[0] = control;
        args[1] = (uint32_t)(int32_t)(int16_t)(lparam & 0xffff);
        args[2] = lparam >> 16;
        pass = call(&port, entry, SET_CURSOR, control, vertrix_lift_edx, 1, args, 3) == 0;
    }
    else if (message == WM_NCDESTROY)
    {
        args[0] = window;
        args[1] = GWL_WNDPROC;
        args[2] = port_u32(&port, locals, OLD_PROCEDURE);
        call(&port, entry, SET_WINDOW_LONG, window, vertrix_lift_edx, 1, args, 3);
        args[0] = window;
        args[1] = PROPERTY;
        call(&port, entry, REMOVE_PROP, window, vertrix_lift_edx, 1, args, 2);
    }
    if (pass)
    {
        port_set32(&port, locals, RESULT, call_original(&port, entry, locals, pass));
    }
    return port_return(&port, port_u32(&port, locals, RESULT), vertrix_lift_edx);
}
