#include "rtlhandlerthunks.h"

/* The runtime's C++ frame handler (0x4ec1ec jumps to 0x4e6e19), called with the exception record
 * and the frame on the stack. Unwinding calls the frame's cleanup (0x4cd9f0); a C++ exception
 * (0x25671234) is matched against the try blocks registered for the frame, setting the context's
 * action: 4 for a catch found here, 3 for the frame the search ends at, or what 0x4e8fa7 decides.
 */

enum
{
    BELOW = 4,
    ARGUMENTS = 4,
    ARGUMENT_RECORD = 4,
    ARGUMENT_FRAME = 8,

    RECORD_FLAGS = 4,
    RECORD_CONTEXT = 0x18,
    UNWINDING = 2,
    EXIT_UNWIND = 4,
    FRAME_STATE = 8,
    CPP_EXCEPTION = 0x25671234,
    CODE_MASK = 0x3fffffff,

    CONTEXT_STACK = 8,
    CONTEXT_ACTION = 0x24,
    CONTEXT_CATCHING = 0x2c,
    CONTEXT_LAST_FRAME = 0x30,
    CONTEXT_BLOCKS = 0x34,
    BLOCK_FRAME = 0,
    BLOCK_NEXT = 8,
    BLOCK_KIND = 0xc,
    BLOCK_CATCHING = 0x14,
    ACTION_LAST_FRAME = 3,
    ACTION_CATCH = 4,

    FRAME_CLEANUP = 0x4cd9f0,
    MATCH_CATCH = 0x4e8fa7,
    STACK_TOP = 0x507c9c, /* a procedure variable */
    STACK_BASE = 0x5c5c54
};

/* Original 0x4e6e19. Its callers read edx: the record, its low byte replaced by each block kind
 * looked at, or the catching block's +0x14, or what the last callee left. */
uint32_t vertrix_port_rtl_exception_handler_thunk_4ec1ec(PORT_SIGNATURE)
{
    uint8_t stack[BELOW + 8 + 4 * ARGUMENTS];
    Port port;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, ARGUMENTS);
    const uint32_t record = port_u32(&port, entry->esp, ARGUMENT_RECORD);
    const uint32_t frame = port_u32(&port, entry->esp, ARGUMENT_FRAME);
    uint32_t edx = record;
    if (frame == 0)
    {
        /* No frame: the context's stack pointer from the stack top. */
        const uint32_t top =
            port_call(&port, port_u32(&port, STACK_TOP, 0), entry->eax, record, 0, entry->ecx);
        edx = vertrix_lift_edx;
        const uint32_t context = port_u32(&port, record, RECORD_CONTEXT);
        port_set32(&port, port_u32(&port, context, CONTEXT_STACK), 0,
                   port_u32(&port, STACK_BASE, 0) + top);
        return port_return(&port, 0, edx);
    }
    const uint32_t flags = port_u8(&port, record, RECORD_FLAGS);
    if ((flags & UNWINDING) ||
        ((flags & EXIT_UNWIND) && port_u32(&port, port_u32(&port, frame, FRAME_STATE), 0) == 4))
    {
        port_call(&port, FRAME_CLEANUP, 0, frame, frame, entry->ecx);
        return port_return(&port, 1, vertrix_lift_edx);
    }
    if ((flags & EXIT_UNWIND) || (port_u32(&port, record, 0) & CODE_MASK) != CPP_EXCEPTION)
    {
        return port_return(&port, 1, edx);
    }
    const uint32_t context = port_u32(&port, record, RECORD_CONTEXT);
    if (frame == port_u32(&port, context, CONTEXT_CATCHING))
    {
        port_set32(&port, context, CONTEXT_CATCHING, 0);
    }
    /* The blocks of this frame: a catch (kind 2 or 7) becomes the catching block. */
    uint32_t block = port_u32(&port, context, CONTEXT_BLOCKS);
    while (block != 0 && frame == port_u32(&port, block, BLOCK_FRAME) && !port.env.failed)
    {
        if (port_u32(&port, context, CONTEXT_CATCHING) == 0)
        {
            const uint32_t kind = port_u8(&port, block, BLOCK_KIND);
            edx = (edx & 0xffffff00u) | kind;
            if (kind != 2 && kind != 7)
            {
                break;
            }
            edx = port_u32(&port, block, BLOCK_CATCHING);
            port_set32(&port, context, CONTEXT_CATCHING, edx);
        }
        block = port_u32(&port, block, BLOCK_NEXT);
    }
    if (block != 0 && frame == port_u32(&port, block, BLOCK_FRAME))
    {
        port_set8(&port, context, CONTEXT_ACTION, ACTION_CATCH);
        return port_return(&port, 0, edx);
    }
    if (port_u32(&port, context, CONTEXT_CATCHING) == 0)
    {
        const uint32_t action =
            port_call(&port, MATCH_CATCH, context, frame, frame, context) & 0xff;
        edx = vertrix_lift_edx;
        if (action != 0)
        {
            port_set8(&port, context, CONTEXT_ACTION, action);
            return port_return(&port, 0, edx);
        }
    }
    if (frame != port_u32(&port, context, CONTEXT_LAST_FRAME))
    {
        return port_return(&port, 1, edx);
    }
    port_set8(&port, context, CONTEXT_ACTION, ACTION_LAST_FRAME);
    return port_return(&port, 0, edx);
}
