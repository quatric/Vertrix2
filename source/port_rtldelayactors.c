#include "port_rtldelayactors.h"

enum
{
    /* The text table's row on show and each row's total text length (text_table.h). */
    MESSAGE_ROW = 0x532a64,
    MESSAGE_LENGTHS = 0x53bdac,
    /* Milliseconds to read a message: a base and a step per character. */
    READ_BASE = 5000,
    READ_PER_CHARACTER = 180,

    ACTOR_BYTES = 0x15c,
    ACTOR_COUNTDOWN = 0,
    COUNTDOWN = 0xc8,
    UPDATE = 0x457770,
    OBJECTS = 0x54671c,

    GET_MEM = 0x4ca000,
    ACTOR_RESET = 0x4abd70,
    ACTOR_PLACE = 0x4adf20,
    ACTOR_SET_UPDATE = 0x4ac8f0,
    ACTOR_SET_DELAY = 0x4ac7d0,
    LIST_APPEND = 0x4b5e70
};

/* Original 0x471340: create the actor that waits while a message is read: a 0x15c-byte actor
 * (0x4ca000) reset to its initial fields (0x4abd70, which returns it) when the allocation succeeds,
 * placed at 0, 0, 0 with nothing attached (0x4adf20), updated by 0x457770 with the delay 5000 +
 * 180 per character of the message on show (0x4ac7d0), its countdown +0 at 0xc8, and appended
 * to the object list 0x54671c. A failed allocation goes on with a null actor, as the original
 * does. No caller reads a result. */
uint32_t vertrix_port_delay_actor_spawn_471340(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t row = port_u32(&port, MESSAGE_ROW, 0);
    const uint32_t length = port_u32(&port, MESSAGE_LENGTHS + row * 4, 0);
    const uint32_t delay = READ_BASE + READ_PER_CHARACTER * length;

    uint32_t actor = port_call(&port, GET_MEM, ACTOR_BYTES, 0, 0, 0);
    if (actor != 0)
    {
        actor = port_call(&port, ACTOR_RESET, actor, 0, 0, 0);
    }
    const uint32_t nothing[5] = {0};
    port_call_stack(&port, ACTOR_PLACE, actor, 0, 0, 0, nothing, 5);
    port_call(&port, ACTOR_SET_UPDATE, actor, UPDATE, 0, 0);
    port_call(&port, ACTOR_SET_DELAY, actor, delay, 0, 0);
    port_set32(&port, actor, ACTOR_COUNTDOWN, COUNTDOWN);
    port_call(&port, LIST_APPEND, OBJECTS, actor, 0, 0);
    return port_return(&port, 0, 0);
}
