#include "rtlguardedcalls.h"

enum
{
    /* The frame below the return slot, and the locals the callees reach by address (offsets from
     * the original's ebp, entry->esp - 4). */
    BELOW = 0x78,
    CHAIN_RECORD = 0x2c,
    JUMP_BUFFER = 0x74,
    ERROR_TEXT = 0x24,
    CAUGHT = 0x18,
    RESULT = 0x1c,

    /* The values the original leaves in ebx, ecx and edi for the jump capture. */
    HANDLER_TABLE = 0x517210,
    HANDLER_CODE = 0x4ec1ec,
    STATE = 2,
    CAUGHT_JUMP = 1,

    METHOD = 0x38,
    EXCEPTION_DETAIL = 0x8,
    ERROR_KIND = 4,

    CHAIN_PUSH = 0x4d93f0,
    JUMP_CAPTURE = 0x4d9f06,
    ERROR_TEXT_BUILD = 0x488d80,
    STRING_RELEASE = 0x4ca210,
    CHAIN_STEP = 0x4da6b6,
    CHAIN_POP = 0x4d9430
};

/* Original 0x489a10 (eax = an object): calls the object's method +0x38 under a try frame and
 * returns its result. The thread chain record is pushed (0x4d93f0) and the jump captured
 * (0x4d9f06); when the capture reports a caught exception (1), an exception whose +8 is set has its
 * error text built (0x488d80, kind 4) and released at once without being shown, the result is 0,
 * and the handler steps the chain (0x4da6b6). An exception whose +8 is clear leaves the result
 * as the caller's stack held it, as the original does. Either way the record is popped (0x4d9430).
 *
 * The method's object is the edx the jump capture hands back, which is the object the original
 * passed it. Only caller: vertrix_port_resource_load_48a710 (0x48a797). The exception frame at
 * fs:[0] is left out (docs/NATIVE-PORTS.md). Returns the caller's edx. */
uint32_t vertrix_port_guarded_method38_call_489a10(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[BELOW + 8];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t frame = entry->esp - 4;
    port_set32(&port, frame, 0, entry->ebp);

    port_call_with(&port, CHAIN_PUSH, frame - CHAIN_RECORD, entry->eax, HANDLER_TABLE, HANDLER_CODE,
                   0, STATE, frame);
    const uint32_t chain_edx = vertrix_lift_edx;
    const uint32_t jumped = port_call_with(&port, JUMP_CAPTURE, frame - JUMP_BUFFER, chain_edx,
                                           HANDLER_TABLE, HANDLER_CODE, 0, STATE, frame);
    const uint32_t object = vertrix_lift_edx;
    if (jumped == CAUGHT_JUMP)
    {
        const uint32_t caught = port_u32(&port, frame - CAUGHT, 0);
        uint32_t step_eax = caught;
        uint32_t step_ecx = HANDLER_CODE;
        if (port_u32(&port, caught, EXCEPTION_DETAIL) != 0)
        {
            port_call(&port, ERROR_TEXT_BUILD, frame - ERROR_TEXT, caught, 0, ERROR_KIND);
            step_eax = port_call(&port, STRING_RELEASE, frame - ERROR_TEXT, 0, 0, 0);
            step_ecx = ERROR_KIND;
            port_set32(&port, frame - RESULT, 0, 0);
        }
        port_call(&port, CHAIN_STEP, step_eax, 0, 0, step_ecx);
    }
    else
    {
        const uint32_t vtable = port_u32(&port, object, 0);
        const uint32_t method = port_u32(&port, vtable, METHOD);
        const uint32_t result =
            port_call_with(&port, method, object, object, HANDLER_TABLE, vtable, 0, STATE, frame);
        port_set32(&port, frame - RESULT, 0, result);
    }
    port_call_with(&port, CHAIN_POP, 0, 0, 0, 0, 0, STATE, frame);
    return port_return(&port, port_u32(&port, frame - RESULT, 0), entry->edx);
}
