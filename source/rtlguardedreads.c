#include "rtlguardedreads.h"

enum
{
    /* The frame under the return slot: ebp, four saved registers and 0x4c bytes of locals. From
     * ebp: a string object (-0x5c: its class, -0x54, -0x50), a second one (-0x4c), the exception
     * record (-0x48: link, handler, class, state at -0x3c, flags at -0x38), its cleanup fields
     * (-0x34, -0x30, -0x28, -0x24), the object's class (-0x1c), the edx argument (-0x14) and a
     * result object (-0x18). */
    BELOW = 0x60,
    FRAME = 0x5c,
    STRING = 0x5c,
    STRING_FIELD_ONE = 0x54,
    STRING_FIELD_TWO = 0x50,
    STRING_TWO = 0x4c,
    RECORD_HANDLER = 0x44,
    RECORD_CLASS = 0x40,
    RECORD_STATE = 0x3c,
    RECORD_FLAGS = 0x38,
    CLEANUP_OBJECT = 0x34,
    CLEANUP_DONE = 0x30,
    CLEANUP_STRING = 0x28,
    CLEANUP_FLAG = 0x24,
    OBJECT_CLASS = 0x1c,
    RESULT = 0x18,
    ARGUMENT = 0x14,

    HANDLER = 0x4ec1ec,
    HANDLER_CLASS = 0x517038,
    STRING_CLASS = 0x517494,
    STRING_CLASS_BASE = 0x517454,
    METHOD = 0x28,
    METHOD_FLAGS = 0x8000,

    STRING_CONSTRUCT = 0x4d9280,
    STRING_INITIALISE = 0x4ca070,
    STRING_ASSIGN = 0x4ca370,
    STRING_DESTROY = 0x4ca210,
    RESULT_MAKE = 0x488d80
};

/* Original 0x488c50 (eax = an object, edx = its argument): calls the object's method +0x28 (edx
 * the argument, ebx 0x8000, ecx a string object built in the frame by 0x4d9280, 0x4ca070 and
 * 0x4ca370). When it returns 0 a result is made from the string (0x488d80) and destroyed
 * (0x4ca210). The second string is destroyed (0x4ca210) and the frame's string left with its base
 * class. Returns 1 when the method returned nonzero, else 0. The exception frame at fs:[0] is left
 * out (docs/NATIVE-PORTS.md). */
uint32_t vertrix_port_rtl_guarded_read_488c50(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[BELOW + 8];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t ebp = entry->esp - 4;
    const uint32_t frame = ebp - FRAME;
    const uint32_t object = entry->eax;
    port_set32(&port, ebp - ARGUMENT, 0, entry->edx);
    port_set32(&port, ebp - RECORD_HANDLER, 0, HANDLER);
    port_set32(&port, ebp - RECORD_CLASS, 0, HANDLER_CLASS);
    port_set32(&port, ebp - RECORD_STATE, 0, 0);
    port_set8(&port, ebp - RECORD_FLAGS, 0, port_u8(&port, ebp - RECORD_FLAGS, 0) & 0xfe);
    port_set8(&port, ebp - CLEANUP_FLAG, 0, 0);
    port_set32(&port, ebp - CLEANUP_STRING, 0, frame);
    port_call_with(&port, STRING_CONSTRUCT, ebp - STRING, STRING_CLASS, 0, HANDLER_CLASS, object, 3,
                   ebp);
    port_set32(&port, ebp - RECORD_STATE, 0, 3);
    port_call_with(&port, STRING_INITIALISE, ebp - STRING_TWO, vertrix_lift_edx, 0, HANDLER_CLASS,
                   object, 3, ebp);
    port_set32(&port, ebp - STRING, 0, vertrix_lift_edx);
    port_set32(&port, ebp - STRING_FIELD_ONE, 0, 0);
    port_set32(&port, ebp - RECORD_STATE, 0, 4);
    port_set32(&port, ebp - STRING_FIELD_TWO, 0, 0xffffffffu);
    port_call_with(&port, STRING_ASSIGN, ebp - STRING_TWO, 0, 0xffffffffu, HANDLER_CLASS, object, 1,
                   ebp);
    port_set32(&port, ebp - RECORD_STATE, 0, 1);
    const uint32_t vtable = port_u32(&port, object, 0);
    port_set32(&port, ebp - OBJECT_CLASS, 0, vtable);
    const uint32_t read =
        port_call_with(&port, port_u32(&port, vtable, METHOD), object,
                       port_u32(&port, ebp - ARGUMENT, 0), METHOD_FLAGS, frame, vtable, 0, ebp);
    uint32_t result = 1;
    if (read == 0)
    {
        result = 0;
        port_call_with(&port, RESULT_MAKE, ebp - RESULT, frame, METHOD_FLAGS, frame, vtable, 0,
                       ebp);
        port_set32(&port, ebp - RECORD_STATE, 0, 1);
        port_call_with(&port, STRING_DESTROY, ebp - RESULT, 0, METHOD_FLAGS, frame, vtable, 0, ebp);
        port_set32(&port, ebp - RECORD_STATE, 0, 1);
    }
    port_set32(&port, ebp - STRING, 0, STRING_CLASS);
    port_set32(&port, ebp - CLEANUP_STRING, 0, frame);
    port_set8(&port, ebp - CLEANUP_FLAG, 0, 0);
    port_set32(&port, ebp - RECORD_STATE, 0, 8);
    port_call_with(&port, STRING_DESTROY, ebp - STRING_TWO, 0, 8, STRING_CLASS, STRING_CLASS_BASE,
                   result, ebp);
    port_set8(&port, ebp - CLEANUP_DONE, 0, 1);
    port_set32(&port, ebp - STRING, 0, STRING_CLASS_BASE);
    port_set32(&port, ebp - RECORD_STATE, 0, 0);
    port_set32(&port, ebp - CLEANUP_OBJECT, 0, frame);
    return port_return(&port, result, vertrix_lift_edx);
}
