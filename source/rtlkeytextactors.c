#include "rtlkeytextactors.h"

enum
{
    ACTOR_METHODS = 0x158,
    KEY_TEXT_METHODS = 0x5180f4,
    /* Three key actors, the dwords before them and the dwords after them. */
    FIRST_KEY = 0x17c,
    SECOND_KEY = 0x184,
    THIRD_KEY = 0x180,
    KEY_ACTOR_BYTES = 0x160,

    TEXT_ACTOR_CONSTRUCT = 0x4b3100,
    KEY_ACTOR_CONSTRUCT = 0x4b5400,
    GET_MEM = 0x4ca000,
    ACTOR_PLACE = 0x4adf20,
    ACTOR_SET_BOX = 0x4b54d0
};

/* A key actor (0x4b5400) when the allocation succeeds, placed at 0, 0, 0 with nothing attached
 * (0x4adf20) and given an empty box (0x4b54d0), stored at `field`. A failed allocation stores and
 * places a null actor, as the original does. */
static void add_key(Port *port, uint32_t object, uint32_t field)
{
    uint32_t key = port_call(port, GET_MEM, KEY_ACTOR_BYTES, 0, 0, 0);
    if (key != 0)
    {
        key = port_call(port, KEY_ACTOR_CONSTRUCT, key, 0, 0, 0);
    }
    port_set32(port, object, field, key);
    const uint32_t nothing[5] = {0};
    port_call_stack(port, ACTOR_PLACE, key, 0, 0, 0, nothing, 5);
    port_call_stack(port, ACTOR_SET_BOX, port_u32(port, object, field), 0, 0, 0, nothing, 1);
}

/* Original 0x4b4cf0 (eax = object): construct a text actor (0x4b3100) whose methods are 0x5180f4,
 * with +0x170..+0x178 cleared, three key actors at +0x17c, +0x184 and +0x180 (in that order) and
 * +0x188..+0x194 cleared. Returns the object; edx is kept (the original saves it). The original's
 * C++ exception frame (unwinding a partly built object) is left out: the lifted runtime does not
 * hand fs:[0] to callees. */
uint32_t vertrix_port_key_text_actor_construct_4b4cf0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t object = port_call(&port, TEXT_ACTOR_CONSTRUCT, entry->eax, 0, 0, 0);
    port_set32(&port, object, ACTOR_METHODS, KEY_TEXT_METHODS);
    for (uint32_t field = 0x170; field <= 0x178; field += 4)
    {
        port_set32(&port, object, field, 0);
    }
    add_key(&port, object, FIRST_KEY);
    add_key(&port, object, SECOND_KEY);
    add_key(&port, object, THIRD_KEY);
    for (uint32_t field = 0x188; field <= 0x194; field += 4)
    {
        port_set32(&port, object, field, 0);
    }
    return port_return(&port, object, entry->edx);
}
