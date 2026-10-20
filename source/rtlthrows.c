#include "rtlthrows.h"

enum
{
    /* The frame: ebp sits 0x82 under the saved ecx, esi and ebp, the locals around it; 0x10 more
     * are taken when the stack check asks for them. */
    BELOW = 0xb8,
    FRAME = 0xc + 0x82,

    /* The throw's state (0x4e38ff fills it at THROW): what to do next (+0xa), its flags (+0xb),
     * the exception record's code, flags, argument count and arguments (+0x1e, +0x22, +0x2e,
     * +0x32) and the frame to unwind to (+0x2a). */
    THROW = -0x1a,
    HANDLER_RECORD = -0x16,
    CATCH = -0xe,
    CATCH_OFFSET = -2,
    TARGET = 6,
    ACTION = 0xa,
    OPTIONS = 0xb,
    RAISED = 0x16,
    EXCEPTION = 0x1e,
    EXCEPTION_FLAGS = 0x22,
    UNWIND_TO = 0x2a,
    ARGUMENT_COUNT = 0x2e,
    ARGUMENTS = 0x32,
    MESSAGE_SCOPE = 0x3a,
    /* The frame's exception registration: the next record, the handler, its table and state. */
    RECORD = 0x4e,
    RECORD_HANDLER = 0x52,
    RECORD_TABLE = 0x56,
    RECORD_STATE = 0x5a,
    TERMINATE_SCOPE = 0x62,
    CURRENT = 0x72,
    CAUGHT = 0x7e,

    ACTION_RETHROWN = 1,
    ACTION_CAUGHT = 2,
    ACTION_UNHANDLED = 3,
    ACTION_RETHROW = 4,
    OPTION_TRACED = 2,
    OPTION_KEEP = 4,
    /* The exception object's state (+0xc), kept at +0xd while traced, its frame and offset. */
    OBJECT_STATE = 0xc,
    OBJECT_KEPT = 0xd,
    OBJECT_OFFSET = 0x18,
    OBJECT_FRAME = 0x20,
    CURRENT_STATE = 0xc,
    CURRENT_OBJECT = 8,
    CURRENT_PENDING = 0x1a,
    STACK_NEEDED = 0x10,

    FRAME_HANDLER = 0x4ec1ec,
    FRAME_TABLE = 0x51a910,
    CURRENT_EXCEPTION = 0x4e0f8b,
    PREPARE = 0x4e38ff,
    STACK_LEFT = 0x4e08a0,
    STACK_PROBE = 0x4e08f0,
    ERROR_REPORT = 0x4dee73,
    TERMINATE = 0x4e0bf8,
    SCOPE_OPEN = 0x4e36d2,
    SCOPE_CLOSE = 0x4e36e4,
    FATAL = 0x4e0c0c,
    COPY_OBJECT = 0x4cd9f0,
    RETHROW = 0x4da26a,
    FIND_CATCH = 0x4e0c56,
    CATCH_ENTER = 0x4d9fca,
    TERMINATE_OPEN = 0x4e3698,
    TERMINATE_CLOSE = 0x4e36c4,
    UNWIND = 0x4f06b6,
    RAISE_EXCEPTION = 0x4f1c70, /* an import slot */

    /* The runtime's messages for a throw nothing catches. */
    UNCAUGHT_TEXT = 0x512672,
    DURING_TEXT = 0x5125b0,
    FIRST_TEXT = 0x5125f2,
    SECOND_TEXT = 0x51261b,
    THIRD_TEXT = 0x512643,
    UNHANDLED_TEXT = 0x51269d
};

/* Original 0x4da3ba (eax = the object thrown; esi, edi and the frame go to the rethrow 0x4da26a):
 * a C++ throw. A frame is registered on the exception chain (handler 0x4ec1ec, table 0x51a910);
 * the thread's current exception (0x4e0f8b) is cleared and the throw prepared (0x4e38ff), with
 * 0x10 bytes of stack more when it is short (0x4e08a0, 0x4e08f0). The exception is raised
 * (RaiseException) when the preparation asks for it, else it is unhandled. Then by the action
 * (+0xa) it is caught (the object found, 0x4e0c56, copied, 0x4cd9f0, the stack unwound,
 * RtlUnwind), rethrown (0x4da26a, 0x4d9fca) or unhandled (the fatal messages, 0x4e0c0c, and
 * terminate, 0x4e0bf8), and the chain is put back. Returns the chain's former head, edx the last
 * call's. */
uint32_t vertrix_port_rtl_throw_4da3ba(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[BELOW + 8];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t thrown = entry->eax;
    const uint32_t frame = entry->esp - FRAME;
#define AT(offset) (frame + (uint32_t)(offset))
    uint32_t eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t action;

    port_set32(&port, AT(RECORD), 0, port.env.chain);
    port.env.chain = AT(RECORD);
    port_set32(&port, AT(RECORD_HANDLER), 0, FRAME_HANDLER);
    port_set32(&port, AT(RECORD_TABLE), 0, FRAME_TABLE);
    port_set32(&port, AT(RECORD_STATE), 0, 0);
    eax = port_call(&port, CURRENT_EXCEPTION, AT(RECORD), edx, ebx, ecx);
    edx = vertrix_lift_edx;
    port_set32(&port, AT(CURRENT), 0, eax);
    port_set32(&port, eax, CURRENT_STATE, 0);
    {
        const uint32_t arguments[2] = {thrown, AT(EXCEPTION)};
        ecx = AT(CURRENT);
        eax = port_call_stack(&port, PREPARE, AT(THROW), edx, ebx, ecx, arguments, 2);
        edx = vertrix_lift_edx;
    }
    eax = port_call(&port, STACK_LEFT, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    if (eax > STACK_NEEDED)
    {
        const uint32_t needed = STACK_NEEDED;
        port_call_stack(&port, STACK_PROBE, eax, edx, ebx, ecx, &needed, 1);
        edx = vertrix_lift_edx;
        eax = STACK_NEEDED;
    }
    port_set32(&port, AT(CAUGHT), 0, 0);
    if (port_u32(&port, AT(RAISED), 0) != 0)
    {
        goto raise;
    }
    port_set8(&port, AT(ACTION), 0, ACTION_UNHANDLED);

unhandled:
    if (port.env.failed)
    {
        goto done;
    }
    if ((port_u8(&port, AT(OPTIONS), 0) & OPTION_TRACED) == 0)
    {
        goto terminate_scope;
    }
    eax = port_call(&port, ERROR_REPORT, UNCAUGHT_TEXT, 1, ebx, ecx);
    edx = vertrix_lift_edx;

done:
    port_call(&port, TERMINATE, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    eax = port_u32(&port, AT(RECORD), 0);
    port.env.chain = eax;
    return port_return(&port, eax, edx);

rethrow_state:
    if (port_u32(&port, AT(CURRENT_PENDING), 0) == 0)
    {
        eax = port_call(&port, TERMINATE, eax, edx, ebx, ecx);
        edx = vertrix_lift_edx;
    }
    {
        const uint32_t pending = port_u32(&port, AT(CURRENT_PENDING), 0);
        const uint32_t state = port_u8(&port, pending, OBJECT_STATE);
        switch (state)
        {
            case 0:
                eax = state;
                goto during;
            case 3:
                eax = state;
                goto first;
            case 5:
                eax = state;
                goto second;
            case 6:
                eax = state;
                goto third;
            case 1:
            case 2:
            case 4:
                eax = state;
                goto terminate;
            default:
                eax = (pending & 0xffffff00u) | state;
                goto terminate;
        }
    }

during:
    if ((port_u8(&port, AT(OPTIONS), 0) & OPTION_TRACED) == 0)
    {
        eax = port_u32(&port, port_u32(&port, AT(CURRENT), 0), CURRENT_OBJECT);
    }
    else
    {
        eax = 0;
    }
    {
        const uint32_t argument = eax;
        ecx = 3;
        edx = AT(CURRENT);
        ebx = 0;
        port_call_stack(&port, SCOPE_OPEN, AT(MESSAGE_SCOPE), edx, ebx, ecx, &argument, 1);
    }
    edx = port_u32(&port, AT(CURRENT), 0);
    port_set32(&port, AT(RECORD_STATE), 0, 1);
    port_call(&port, FATAL, DURING_TEXT, edx, ebx, ecx);
    port_set32(&port, AT(RECORD_STATE), 0, 0);
    port_call(&port, SCOPE_CLOSE, AT(MESSAGE_SCOPE), 0, ebx, ecx);
    port_set32(&port, AT(RECORD_STATE), 0, 0);
first:
    eax = port_call(&port, ERROR_REPORT, FIRST_TEXT, 1, ebx, ecx);
second:
    eax = port_call(&port, ERROR_REPORT, SECOND_TEXT, 1, ebx, ecx);
third:
    eax = port_call(&port, ERROR_REPORT, THIRD_TEXT, 1, ebx, ecx);
    edx = vertrix_lift_edx;
terminate:
    eax = port_call(&port, TERMINATE, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
next:
    if (port_u32(&port, AT(CAUGHT), 0) == 0)
    {
        goto catch_found;
    }
copy:
    edx = port_u32(&port, AT(THROW), 0);
    eax = port_call(&port, COPY_OBJECT, port_u32(&port, AT(TARGET), 0), edx, ebx, ecx);
    edx = vertrix_lift_edx;
act:
    if (port.env.failed)
    {
        goto done;
    }
    action = port_u8(&port, AT(ACTION), 0);
    if (action == ACTION_CAUGHT)
    {
        eax = port_call(&port, CATCH_ENTER, AT(THROW), edx, ebx, ecx);
        edx = vertrix_lift_edx;
        goto rethrow;
    }
    if (action == ACTION_UNHANDLED)
    {
        goto unhandled;
    }
    if (action != ACTION_RETHROWN)
    {
        goto done;
    }
rethrow:
    eax = port_call_with(&port, RETHROW, AT(THROW), edx, ebx, ecx, thrown, entry->edi, frame);
    edx = vertrix_lift_edx;
    goto unhandled;

catch_found:
    port_set32(&port, AT(CAUGHT), 0, 1);
    if ((port_u8(&port, AT(OPTIONS), 0) & OPTION_TRACED) == 0)
    {
        ebx = AT(CURRENT);
        edx = port_u32(&port, AT(HANDLER_RECORD), 0);
        eax = port_call(&port, FIND_CATCH, thrown, edx, ebx, ecx);
        edx = eax;
        port_set32(&port, AT(CATCH), 0, eax);
        port_set32(&port, edx, OBJECT_OFFSET, port_u32(&port, AT(CATCH_OFFSET), 0));
        eax = port_u32(&port, AT(THROW), 0);
        port_set32(&port, edx, OBJECT_FRAME, eax);
    }
    else
    {
        eax = port_u32(&port, AT(CATCH), 0);
        const uint32_t state = port_u8(&port, eax, OBJECT_STATE);
        edx = (edx & 0xffffff00u) | state;
        port_set8(&port, eax, OBJECT_KEPT, state);
        if (port_u8(&port, AT(OPTIONS), 0) & OPTION_KEEP)
        {
            ebx = port_u32(&port, AT(CATCH), 0);
            eax = port_u32(&port, AT(CATCH_OFFSET), 0);
            port_set32(&port, ebx, OBJECT_OFFSET, eax);
            eax = port_u32(&port, AT(THROW), 0);
            port_set32(&port, ebx, OBJECT_FRAME, eax);
        }
    }
    if (port_u8(&port, AT(ACTION), 0) != ACTION_CAUGHT)
    {
        eax = port_u32(&port, AT(CATCH), 0);
        port_set8(&port, eax, OBJECT_STATE, 0);
        const uint32_t arguments[4] = {port_u32(&port, AT(THROW), 0),
                                       port_u32(&port, AT(UNWIND_TO), 0), AT(EXCEPTION), 0};
        eax = port_call_stack(&port, UNWIND, AT(EXCEPTION), edx, ebx, ecx, arguments, 4);
        edx = vertrix_lift_edx;
        goto copy;
    }
    if ((port_u8(&port, AT(OPTIONS), 0) & OPTION_TRACED) == 0)
    {
        goto act;
    }
    eax = port_u32(&port, AT(CATCH), 0);
    {
        const uint32_t kept = port_u8(&port, eax, OBJECT_KEPT);
        edx = (edx & 0xffffff00u) | kept;
        port_set8(&port, eax, OBJECT_STATE, kept);
    }
    goto act;

raise:
    {
        const uint32_t arguments[4] = {port_u32(&port, AT(EXCEPTION), 0),
                                       port_u32(&port, AT(EXCEPTION_FLAGS), 0),
                                       port_u32(&port, AT(ARGUMENT_COUNT), 0), AT(ARGUMENTS)};
        eax = port_call_stack(&port, port_u32(&port, RAISE_EXCEPTION, 0), AT(ARGUMENTS), edx, ebx,
                              ecx, arguments, 4);
        edx = vertrix_lift_edx;
    }
    action = port_u8(&port, AT(ACTION), 0);
    if (action == ACTION_RETHROWN || action == ACTION_CAUGHT)
    {
        goto next;
    }
    if (action == ACTION_RETHROW)
    {
        goto rethrow_state;
    }
    goto act;

terminate_scope:
    ecx = 3;
    ebx = 0;
    port_call(&port, TERMINATE_OPEN, AT(TERMINATE_SCOPE), AT(CURRENT), ebx, ecx);
    edx = port_u32(&port, AT(CURRENT), 0);
    port_set32(&port, AT(RECORD_STATE), 0, 3);
    eax = port_call(&port, FATAL, UNHANDLED_TEXT, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    port_set32(&port, AT(RECORD_STATE), 0, 0);
    eax = port_call(&port, TERMINATE_CLOSE, AT(TERMINATE_SCOPE), 0, ebx, ecx);
    edx = vertrix_lift_edx;
    port_set32(&port, AT(RECORD_STATE), 0, 0);
    goto done;
#undef AT
}
