#include "port_rtlmessagequeues.h"

/* Takes the next message off the network session's incoming queue. */

enum
{
    SESSION_QUEUE = 0x200,
    LOCK = 0x5328f0,
    /* The event set while messages wait, reset when the queue runs empty. */
    WAITING_EVENT = 0x5bb4a0,

    /* The parts of a message that are copied: its first 8 bytes and four dwords (DWORDS). */
    MESSAGE_HEADER_BYTES = 8,

    ENTER_CRITICAL_SECTION = 0x4f1b48,
    LEAVE_CRITICAL_SECTION = 0x4f1c40,
    RESET_EVENT = 0x4f1c7c,
    QUEUE_EMPTY = 0x48d5f0,
    QUEUE_FRONT = 0x48d620,
    QUEUE_REMOVE = 0x48d650
};

static const uint32_t DWORDS[] = {0x20, 0x2c, 0x14, 0x18};

static int queue_empty(Port *port, uint32_t queue)
{
    return port_call(port, QUEUE_EMPTY, queue, 0, 0, 0) == 1;
}

/* Original 0x48be70 (eax = the session, edx = where the message goes): under the lock 0x5328f0,
 * copies the front message out and removes it (0x48d650 with 0 and 1), and resets the waiting
 * event when nothing is left. */
uint32_t vertrix_port_message_queue_take_48be70(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t queue = entry->eax + SESSION_QUEUE;
    const uint32_t out = entry->edx;
    const uint32_t lock = LOCK;

    port_call_stack(&port, ENTER_CRITICAL_SECTION, 0, 0, 0, 0, &lock, 1);
    if (!queue_empty(&port, queue))
    {
        const uint32_t message = port_call(&port, QUEUE_FRONT, queue, 0, 0, 0);
        if (message != 0)
        {
            for (uint32_t offset = 0; offset < MESSAGE_HEADER_BYTES; offset++)
            {
                port_set8(&port, out, offset, port_u8(&port, message, offset));
            }
            for (unsigned index = 0; index < 4; index++)
            {
                port_set32(&port, out, DWORDS[index], port_u32(&port, message, DWORDS[index]));
            }
            port_call(&port, QUEUE_REMOVE, queue, 0, 1, 0);
        }
    }
    if (queue_empty(&port, queue))
    {
        const uint32_t event = port_u32(&port, WAITING_EVENT, 0);
        port_call_stack(&port, RESET_EVENT, 0, 0, 0, 0, &event, 1);
    }
    port_call_stack(&port, LEAVE_CRITICAL_SECTION, 0, 0, 0, 0, &lock, 1);
    return port_return(&port, 0, 0);
}
