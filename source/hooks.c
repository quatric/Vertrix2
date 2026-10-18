#include "hooks.h"

/* The runtime's window object teardowns, activation and focus steps, the window procedure hook,
 * the string assignment from a C string and the exception forwarders. */

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

static void guard_record(Port *port, uint32_t record, uint32_t guard, uint32_t step)
{
    port_set32(port, record, 0, port->env.chain);
    port_set32(port, record, 4, 0x4ec1ec);
    port_set32(port, record, 8, guard);
    port_set32(port, record, 0xc, step);
}

/* The array kill of the teardowns: the elements (0x4ccb9f with `kill`) freed (0x4ca040). */
static void array_kill(Port *port, const LiftEntry *entry, uint32_t frame, uint32_t object,
                       uint32_t kill, uint32_t ebx, uint32_t ecx)
{
    uint32_t result;
    port_set32(port, frame, 0x20, 1);
    port_set32(port, frame, 0, object);
    result =
        port_call_with(port, 0x4ccb9f, object, kill, ebx, ecx, entry->esi, entry->edi, entry->ebp);
    port_set32(port, frame, 0x20, 0);
    port_call_with(port, 0x4ca040, result, vertrix_lift_edx, ebx, ecx, entry->esi, entry->edi,
                   entry->ebp);
}

/* Original 0x4cbfe0: the handle object's teardown by the flags dl: with bit 4 the array kill
 * (0x518ef0); otherwise the methods 0x518e24, its handle +0x28 closed (slot 0x4f1b2c), the base
 * teardown 0x4cb4f0 and with bit 2 the free 0x4ca050. */
uint32_t vertrix_port_handle_object_teardown_4cbfe0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x3c
    };
    Port port;
    uint32_t frame = entry->esp - 0x3c;
    uint32_t object = entry->eax;
    uint32_t flags = entry->edx;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, frame, 0x30, flags);
    if ((port_u8(&port, frame, 0x30) & 4) != 0)
    {
        array_kill(&port, entry, frame, object, 0x518ef0, object, entry->ecx);
        return port_return(&port, object, vertrix_lift_edx);
    }
    port_set32(&port, object, 0, 0x518e24);
    port_set32(&port, frame, 0x24, object);
    port_set8(&port, frame, 0x28, flags);
    guard_record(&port, frame + 0x14, 0x518d98, 3);
    if (port_u32(&port, object, 0x28) != 0)
    {
        uint32_t handle[1];
        handle[0] = port_u32(&port, object, 0x28);
        call_frame(&port, 0x4f1b2c, frame + 0x14, flags, object, entry->ecx, entry->esi, entry->edi,
                   entry->ebp, handle, 1);
    }
    port_set32(&port, frame, 0x20, 0);
    result = port_call_with(&port, 0x4cb4f0, object, 1, object, entry->ecx, entry->esi, entry->edi,
                            entry->ebp);
    if ((port_u8(&port, frame, 0x30) & 2) != 0)
    {
        port_call_with(&port, 0x4ca050, result, vertrix_lift_edx, result, entry->ecx, entry->esi,
                       entry->edi, entry->ebp);
    }
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x4d3f70: the window object's teardown by the flags dl: with bit 4 the array kill
 * (0x5199f0); otherwise the methods 0x5198f4, its close (0x4d4060), the text +0xac released
 * (0x4ca210), the parts (0x4d83f0 and the base 0x4d01a0 on the object back from them) and with bit
 * 2 the free 0x4ca050. */
uint32_t vertrix_port_object_destroy_f_4d3f70(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x38
    };
    Port port;
    uint32_t frame = entry->esp - 0x38;
    uint32_t object = entry->eax;
    uint32_t flags = entry->edx;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    if ((flags & 4) != 0)
    {
        array_kill(&port, entry, frame, object, 0x5199f0, flags, object);
        return port_return(&port, object, vertrix_lift_edx);
    }
    port_set32(&port, object, 0, 0x5198f4);
    port_set32(&port, frame, 0x24, object);
    port_set8(&port, frame, 0x28, flags);
    guard_record(&port, frame + 0x14, 0x5197fc, 5);
    port_call_with(&port, 0x4d4060, object, 0, flags, object, entry->esi, entry->edi, entry->ebp);
    port_set32(&port, frame, 0x20, 4);
    result = port_call_with(&port, 0x4ca210, object + 0xac, vertrix_lift_edx, flags, object,
                            entry->esi, entry->edi, entry->ebp);
    port_set32(&port, frame, 0x20, 3);
    result = port_call_with(&port, 0x4d83f0, result - 0x40, 0, flags, object, entry->esi,
                            entry->edi, entry->ebp);
    port_set32(&port, frame, 0x20, 0);
    result = port_call_with(&port, 0x4d01a0, result - 0x6c, 1, flags, object, entry->esi,
                            entry->edi, entry->ebp);
    if ((flags & 2) != 0)
    {
        port_call_with(&port, 0x4ca050, result, vertrix_lift_edx, flags, result, entry->esi,
                       entry->edi, entry->ebp);
    }
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x4d4630: the window's activation by dx: a modal window (+0x24 bit 4) being activated
 * leaves the modal state (0x4cce30 with 0, slot 0x4f1aa8 with 0); otherwise, unless the parent
 * (slot 0x4f19c8 of +0x1c) handles it (0x4cf8e0), a deactivated window without a menu (+0xa0)
 * marks itself (+0x24 bit 0x80) and calls its method +0x8c, an activated marked one clears the
 * mark, calls +0x90 and, being the focus (slot 0x4f195c), sends itself 6 (slot 0x4f1a94); an
 * activated window with bit 0x20 sends 0x86 1; then the state 0x10 or 0x20 (0x4d4700). */
uint32_t vertrix_port_window_activate_4d4630(PORT_SIGNATURE)
{
    Port port;
    uint32_t window = entry->eax;
    uint32_t active = entry->edx;
    uint32_t ecx = entry->ecx;
    uint32_t eax;
    uint32_t edx;
    uint32_t args[4];
    port_open(&port, calls, services, globals, entry);
    if (active != 0 && (port_u8(&port, window, 0x24) & 4) != 0)
    {
        uint32_t zero[1] = {0};
        eax =
            port_call_with(&port, 0x4cce30, window, 0, window, ecx, active, entry->edi, entry->ebp);
        eax = call_frame(&port, 0x4f1aa8, eax, vertrix_lift_edx, window, ecx, active, entry->edi,
                         entry->ebp, zero, 1);
        return port_return(&port, eax, vertrix_lift_edx);
    }
    args[0] = port_u32(&port, window, 0x1c);
    eax = call_frame(&port, 0x4f19c8, window, active, window, ecx, active, entry->edi, entry->ebp,
                     args, 1);
    args[0] = eax;
    eax = call_frame(&port, 0x4cf8e0, eax, vertrix_lift_edx, window, ecx, active, entry->edi,
                     entry->ebp, args, 1);
    edx = vertrix_lift_edx;
    if (eax != 0)
    {
        return port_return(&port, eax, edx);
    }
    if (active == 0 && port_u32(&port, window, 0xa0) == 0)
    {
        uint32_t methods = port_u32(&port, window, 0);
        port_set8(&port, window, 0x24, port_u8(&port, window, 0x24) | 0x80);
        eax = port_call_with(&port, port_u32(&port, methods, 0x8c), window, methods, window, ecx,
                             active, entry->edi, entry->ebp);
        edx = vertrix_lift_edx;
    }
    else if (active != 0 && (port_u8(&port, window, 0x24) & 0x80) != 0)
    {
        uint32_t methods = port_u32(&port, window, 0);
        port_set8(&port, window, 0x24, port_u8(&port, window, 0x24) & 0x7f);
        eax = port_call_with(&port, port_u32(&port, methods, 0x90), window, methods, window, ecx,
                             active, entry->edi, entry->ebp);
        eax = call_frame(&port, 0x4f195c, eax, vertrix_lift_edx, window, ecx, active, entry->edi,
                         entry->ebp, args, 0);
        edx = vertrix_lift_edx;
        if (eax == port_u32(&port, window, 0x1c))
        {
            args[0] = eax;
            args[1] = 6;
            args[2] = 1;
            args[3] = 0;
            eax = call_frame(&port, 0x4f1a94, eax, edx, window, ecx, active, entry->edi, entry->ebp,
                             args, 4);
            edx = vertrix_lift_edx;
        }
    }
    if (active != 0 && (port_u8(&port, window, 0x24) & 0x20) != 0)
    {
        args[0] = port_u32(&port, window, 0x1c);
        args[1] = 0x86;
        args[2] = 1;
        args[3] = 0;
        call_frame(&port, 0x4f1a94, eax, edx, window, ecx, active, entry->edi, entry->ebp, args, 4);
    }
    eax = port_call_with(&port, 0x4d4700, window, active != 0 ? 0x10 : 0x20, window, ecx, active,
                         entry->edi, entry->ebp);
    return port_return(&port, eax, vertrix_lift_edx);
}

/* Original 0x4d4d10: the window's focus step: after 0x4d5930, a cursor +0x44 other than the
 * window's (slot 0x4f19b0 of +0x1c) is set (slot 0x4f1ab4); the application's main window
 * (0x4ce740's +4's +0x1c) is raised (slot 0x4f1b1c with 0, 2, 0); then 0x4cf850. */
uint32_t vertrix_port_window_focus_step_4d4d10(PORT_SIGNATURE)
{
    Port port;
    uint32_t window = entry->eax;
    uint32_t eax;
    uint32_t args[4];
    port_open(&port, calls, services, globals, entry);
    eax = port_forward(&port, entry, 0x4d5930, window, entry->edx, window, entry->ecx);
    if (port_u32(&port, window, 0x44) != 0)
    {
        args[0] = port_u32(&port, window, 0x1c);
        eax = call_frame(&port, 0x4f19b0, eax, vertrix_lift_edx, window, entry->ecx, entry->esi,
                         entry->edi, entry->ebp, args, 1);
        if (eax != port_u32(&port, window, 0x44))
        {
            args[0] = port_u32(&port, window, 0x1c);
            args[1] = port_u32(&port, window, 0x44);
            eax = call_frame(&port, 0x4f1ab4, eax, vertrix_lift_edx, window, entry->ecx, entry->esi,
                             entry->edi, entry->ebp, args, 2);
        }
    }
    eax = port_forward(&port, entry, 0x4ce740, eax, vertrix_lift_edx, window, entry->ecx);
    eax = port_u32(&port, eax, 4);
    if (window == port_u32(&port, eax, 0x1c))
    {
        args[0] = port_u32(&port, window, 0x1c);
        args[1] = 0;
        args[2] = 2;
        args[3] = 0;
        call_frame(&port, 0x4f1b1c, eax, vertrix_lift_edx, window, entry->ecx, entry->esi,
                   entry->edi, entry->ebp, args, 4);
    }
    eax = port_forward(&port, entry, 0x4cf850, window, vertrix_lift_edx, window, entry->ecx);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4d04f0: the application's idle step (0x4ce220): its main window +0xd0's handle
 * +0x1c is told 0x401 (slot 0x4f1a94); with the stack word set and an active control +0x108, a
 * key up (slot 0x4f1998 of 1 not negative) runs its method +0xe0 with -1. ret 4. */
uint32_t vertrix_port_application_idle_step_4d04f0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 4
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4];
    uint32_t application;
    uint32_t window;
    uint32_t control;
    uint32_t eax;
    uint32_t edx;
    uint32_t args[4];
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 1);
    application = port_call_with(&port, 0x4ce220, entry->eax, entry->edx, entry->ebx, entry->ecx,
                                 entry->esi, entry->edi, entry->ebp);
    edx = vertrix_lift_edx;
    eax = port_u32(&port, application, 0xd0);
    if (eax != 0)
    {
        window = eax;
        eax = port_u32(&port, window, 0x1c);
        if (eax != 0)
        {
            args[0] = eax;
            args[1] = 0x401;
            args[2] = 0;
            args[3] = 0;
            eax = call_frame(&port, 0x4f1a94, eax, edx, application, entry->ecx, entry->esi,
                             entry->edi, entry->ebp, args, 4);
            edx = vertrix_lift_edx;
        }
    }
    control = port_u32(&port, application, 0x108);
    if (port_u32(&port, entry->esp, 4) != 0 && control != 0)
    {
        args[0] = 1;
        eax = call_frame(&port, 0x4f1998, eax, edx, control, entry->ecx, entry->esi, entry->edi,
                         entry->ebp, args, 1);
        edx = vertrix_lift_edx;
        eax = (uint32_t)(int32_t)(int16_t)eax;
        if ((int32_t)eax >= 0)
        {
            uint32_t methods = port_u32(&port, control, 0);
            eax = port_call_with(&port, port_u32(&port, methods, 0xe0), control, 0xffffffffu,
                                 control, methods, entry->esi, entry->edi, entry->ebp);
            edx = vertrix_lift_edx;
        }
    }
    return port_return(&port, eax, edx);
}

/* The window procedure call (slot 0x4f18ec) on the application's old procedure +0x30 with the
 * three stack words. */
static uint32_t window_call(Port *port, uint32_t application, uint32_t eax, uint32_t ecx,
                            uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t arguments)
{
    uint32_t message[4];
    message[0] = port_u32(port, application, 0x30);
    message[1] = port_u32(port, arguments, 4);
    message[2] = port_u32(port, arguments, 8);
    message[3] = port_u32(port, arguments, 0xc);
    return call_frame(port, 0x4f18ec, eax, vertrix_lift_edx, application, ecx, esi, edi, ebp,
                      message, 4);
}

/* Original 0x4cfe40: the application window's procedure hook (0x4ce220): messages other than 3
 * pass on (slot 0x4f18ec); on 3 with a window record (the third word) not yet seen, the record's
 * kind 0x8002 is kept (+0x28) and, unless the hook is set up (0x5c79c8), 0x4cfd20 runs, otherwise
 * +0x24 the second word and the hook 4 (slot 0x4f1ae0 on 0x4cff20 for this thread, slot 0x4f1ba0)
 * into +0x2c, 1 when that fails; after passing on, a shut application (0x4ce740 +0x14) releases
 * the procedure (slot 0x4f1b08). ret 0xc. */
uint32_t vertrix_port_window_procedure_hook_4cfe40(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 8
    };
    Port port;
    uint8_t stack[BELOW + 8 + 0xc];
    uint32_t application;
    uint32_t record;
    uint32_t eax;
    uint32_t result;
    uint32_t args[4];
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 3);
    application = port_call_with(&port, 0x4ce220, entry->eax, entry->edx, entry->ebx, entry->ecx,
                                 entry->esi, entry->edi, entry->ebp);
    eax = application;
    if (port_u32(&port, entry->esp, 4) != 3)
    {
        return port_return(&port,
                           window_call(&port, application, eax, entry->ecx, entry->esi, entry->edi,
                                       entry->ebp, entry->esp),
                           vertrix_lift_edx);
    }
    record = port_u32(&port, port_u32(&port, entry->esp, 0xc), 0);
    if (port_u32(&port, application, 0x14) == 0)
    {
        if ((port_u8(&port, record, 0x23) & 0x40) != 0)
        {
            goto pass;
        }
        eax = port_call_with(&port, 0x4ce740, eax, vertrix_lift_edx, application, entry->ecx,
                             record, entry->edi, entry->ebp);
        if (port_u8(&port, eax, 0x14) != 0)
        {
            goto pass;
        }
    }
    eax = port_u32(&port, record, 0x28) == 0x8002;
    port_set32(&port, application, 0x28, eax);
    if (port_u32(&port, 0, 0x5c79c8) == 0)
    {
        args[0] = port_u32(&port, entry->esp, 8);
        eax = call_frame(&port, 0x4cfd20, eax, vertrix_lift_edx, application, entry->ecx, record,
                         entry->edi, entry->ebp, args, 1);
        goto pass;
    }
    eax = port_u32(&port, entry->esp, 8);
    port_set32(&port, application, 0x24, eax);
    eax = call_frame(&port, 0x4f1ba0, eax, vertrix_lift_edx, application, entry->ecx, record,
                     entry->edi, entry->ebp, args, 0);
    args[0] = 4;
    args[1] = 0x4cff20;
    args[2] = 0;
    args[3] = eax;
    eax = call_frame(&port, 0x4f1ae0, eax, vertrix_lift_edx, application, entry->ecx, record,
                     entry->edi, entry->ebp, args, 4);
    port_set32(&port, application, 0x2c, eax);
    if (eax == 0)
    {
        return port_return(&port, 1, vertrix_lift_edx);
    }
pass:
    result = window_call(&port, application, eax, entry->ecx, record, entry->edi, entry->ebp,
                         entry->esp);
    eax = port_call_with(&port, 0x4ce740, result, vertrix_lift_edx, application, entry->ecx, result,
                         entry->edi, entry->ebp);
    if (port_u8(&port, eax, 0x14) != 0)
    {
        args[0] = port_u32(&port, application, 0x30);
        call_frame(&port, 0x4f1b08, eax, vertrix_lift_edx, application, entry->ecx, result,
                   entry->edi, entry->ebp, args, 1);
        port_set32(&port, application, 0x30, 0);
    }
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x4d9930: the runtime's paired forward: with a first stack word its record
 * (0x4d9ae0) and both words go to 0x4d9a10, otherwise 0. ret 8. */
uint32_t vertrix_port_rtl_forward_pair_4d9930(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[8 + 8];
    uint32_t first;
    uint32_t result;
    uint32_t args[3];
    port_open_arguments(&port, stack, calls, services, globals, entry, 0, 2);
    first = port_u32(&port, entry->esp, 4);
    if (first == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    args[0] = first;
    args[1] = first;
    args[2] = port_u32(&port, entry->esp, 8);
    result = call_frame(&port, 0x4d9ae0, first, entry->edx, entry->ebx, entry->ecx, entry->esi,
                        entry->edi, entry->ebp, args, 3);
    args[0] = result;
    args[1] = first;
    args[2] = port_u32(&port, entry->esp, 8);
    result = call_frame(&port, 0x4d9a10, result, vertrix_lift_edx, entry->ebx, entry->ecx,
                        entry->esi, entry->edi, entry->ebp, args, 3);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x4d9a10: the runtime error raise: an error object (20 bytes, 0x4ca000; 0x4d9280) with
 * the methods 0x517494, the two stack words (+8, +0xc) and the text of the third (0x4ca070,
 * 0x4ca370 at +0x10) is thrown (0x4da71b with the type 0x51a7b0); none thrown as 0. The guard
 * record's chain. ret 0xc. */
uint32_t vertrix_port_rtl_error_raise_4d9a10(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x2c
    };
    Port port;
    uint8_t stack[BELOW + 8 + 0xc];
    uint32_t frame = entry->esp - 0x2c;
    uint32_t error;
    uint32_t ecx = entry->ecx;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 3);
    guard_record(&port, frame, 0x51a6e0, 0);
    error = port_call_with(&port, 0x4ca000, 0x14, entry->edx, 0x51a7b0, ecx, entry->esi, entry->edi,
                           entry->ebp);
    if (error != 0)
    {
        uint32_t text;
        port_set32(&port, frame, 0xc, 1);
        port_set8(&port, frame, 0x10, port_u8(&port, frame, 0x10) | 1);
        port_set8(&port, frame, 0x18, 0);
        port_set32(&port, frame, 0x24, error);
        port_set32(&port, frame, 0x14, error);
        text = port_call_with(&port, 0x4d9280, error, vertrix_lift_edx, 0x51a7b0, ecx, entry->esi,
                              entry->edi, entry->ebp);
        port_set32(&port, frame, 0xc, 3);
        text = port_call_with(&port, 0x4ca070, text + 0x10, vertrix_lift_edx, 0x51a7b0, ecx,
                              entry->esi, entry->edi, entry->ebp);
        error = text - 0x10;
        ecx = error;
        port_set32(&port, frame, 0xc, 4);
        port_set32(&port, error, 8, port_u32(&port, entry->esp, 4));
        port_set32(&port, error, 0xc, port_u32(&port, entry->esp, 8));
        port_set32(&port, error, 0, 0x517494);
        port_call_with(&port, 0x4ca370, error + 0x10, port_u32(&port, entry->esp, 0xc), 0x51a7b0,
                       ecx, entry->esi, entry->edi, entry->ebp);
        port_set32(&port, frame, 0xc, 1);
        port_set8(&port, frame, 0x10, port_u8(&port, frame, 0x10) & 0xfe);
        port_set32(&port, frame, 0xc, 2);
    }
    port_set32(&port, frame, 0x20, error);
    port_call_with(&port, 0x4da71b, frame + 0x20, 0x51a7b0, 0x51a7b0, ecx, entry->esi, entry->edi,
                   entry->ebp);
    return port_return(&port, port_u32(&port, frame, 0), vertrix_lift_edx);
}

/* Original 0x4ca4a0: the string's assignment from a C string (the third stack word, its length by
 * slot 0x4f1d24, 0 for none) over the text of the second (0x4ca3f0), after 0x4ca070 on the first;
 * the first back. ret 0xc. */
uint32_t vertrix_port_string_assign_text_4ca4a0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint8_t stack[BELOW + 8 + 0xc];
    uint32_t ebp = entry->esp - 0xc;
    uint32_t string;
    uint32_t text;
    uint32_t length = 0;
    uint32_t eax;
    uint32_t source;
    uint32_t pushed[1];
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 3);
    string = port_u32(&port, entry->esp, 4);
    guard_record(&port, ebp - 0x14, 0x518884, 0);
    eax = port_call_with(&port, 0x4ca070, string, port_u32(&port, entry->esp, 0xc), entry->ebx,
                         entry->ecx, string, entry->edi, ebp);
    text = vertrix_lift_edx;
    pushed[0] = text;
    if (text != 0)
    {
        length = call_frame(&port, 0x4f1d24, eax, text, entry->ebx, entry->ecx, string, entry->edi,
                            ebp, pushed, 1);
    }
    source = port_u32(&port, port_u32(&port, entry->esp, 8), 0);
    call_frame(&port, 0x4ca3f0, string, port_u32(&port, source - 0xc, 4), source, length, string,
               entry->edi, ebp, pushed, 1);
    return port_return(&port, string, vertrix_lift_edx);
}

/* Original 0x4d4ee0: the window's enable state: after 0x4cf850, the window's top (itself when a
 * top window, 0x4d1930 otherwise) is enabled (+0x24 bit 0x20) when it is the given one (edx set:
 * the window), the given one's top, or that top's handle enabled (slot 0x4f1a94 0x36d 0x40); the
 * state 4 or 8 (0x4d4700); the frame (0x4d5350, made by method +0xc4 when absent) is told: method
 * +0xe8 with 1 when edx is set and ecx not, then +0xec with edx. */
uint32_t vertrix_port_window_enable_state_4d4ee0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x10
    };
    Port port;
    uint32_t frame = entry->esp - 0x10;
    uint32_t window = entry->eax;
    uint32_t ebx = entry->ecx;
    uint32_t ecx = entry->ecx;
    uint32_t ebp = entry->ebp;
    uint32_t top;
    uint32_t edx;
    uint32_t eax;
    uint32_t enabled;
    uint32_t flag[1];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, frame, 0, entry->edx);
    port_call_with(&port, 0x4cf850, window, entry->ebx, ebx, ecx, window, entry->edi, ebp);
    eax = port_call_with(&port, 0x4cccc0, window, vertrix_lift_edx, ebx, ecx, window, entry->edi,
                         ebp);
    if ((eax & 0x40000000u) != 0)
    {
        top = window;
    }
    else
    {
        top = port_call_with(&port, 0x4d1930, window, vertrix_lift_edx, ebx, ecx, window,
                             entry->edi, ebp);
    }
    edx = vertrix_lift_edx;
    if (port_u32(&port, frame, 0) != 0)
    {
        edx = window;
    }
    if (top == edx)
    {
        enabled = 1;
    }
    else
    {
        eax = port_call_with(&port, 0x4d1930, edx, edx, ebx, ecx, window, top, ebp);
        edx = vertrix_lift_edx;
        if (top != eax)
        {
            enabled = 0;
        }
        else if (edx == eax)
        {
            enabled = 1;
        }
        else
        {
            uint32_t args[4];
            args[0] = port_u32(&port, edx, 0x1c);
            args[1] = 0x36d;
            args[2] = 0x40;
            args[3] = 0;
            enabled =
                call_frame(&port, 0x4f1a94, eax, edx, ebx, ecx, window, top, ebp, args, 4) != 0;
        }
    }
    port_set8(&port, top, 0x24, port_u8(&port, top, 0x24) & 0xdf);
    if (enabled)
    {
        port_set8(&port, top, 0x24, port_u8(&port, top, 0x24) | 0x20);
    }
    port_call_with(&port, 0x4d4700, window, enabled ? 4 : 8, ebx, ecx, window, top, ebp);
    eax = port_call_with(&port, 0x4d5350, window, vertrix_lift_edx, ebx, ecx, window, top, ebp);
    top = eax;
    if (eax == 0)
    {
        uint32_t methods = port_u32(&port, window, 0);
        flag[0] = port_u32(&port, frame, 0);
        eax = call_frame(&port, port_u32(&port, methods, 0xc4), window, methods, ebx, ecx, window,
                         top, ebp, flag, 1);
        eax = port_call_with(&port, 0x4d5350, eax, vertrix_lift_edx, ebx, ecx, window, top, ebp);
        top = eax;
    }
    if (top != 0)
    {
        uint32_t methods;
        if (port_u32(&port, frame, 0) != 0 && ebx == 0)
        {
            ebp = port_u32(&port, top, 0);
            flag[0] = port_u32(&port, frame, 0);
            call_frame(&port, port_u32(&port, ebp, 0xe8), top, 1, top, top, window, top, ebp, flag,
                       1);
        }
        methods = port_u32(&port, top, 0);
        flag[0] = port_u32(&port, frame, 0);
        eax = call_frame(&port, port_u32(&port, methods, 0xec), top, flag[0], window, methods,
                         window, top, ebp, flag, 1);
    }
    return port_return(&port, eax, vertrix_lift_edx);
}
