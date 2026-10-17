#include "port_rtleffectreleases.h"

enum
{
    /* The object's two arrays of effect slots. */
    EFFECTS = 0x15c,
    EFFECT_COUNT = 500,
    BURSTS = 0x92c,
    BURST_COUNT = 8,
    /* Destroy every slot in use and clear it (object_slots.h). */
    RELEASE_SLOTS = 0x4b22c0
};

/* Original 0x43d800 (eax = object): release its 500 effect slots at +0x15c and its 8 at +0x92c
 * (0x4b22c0 each). No caller reads a result. */
uint32_t vertrix_port_effects_release_all_43d800(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t object = entry->eax;
    port_call(&port, RELEASE_SLOTS, object + EFFECTS, EFFECT_COUNT, 0, 0);
    port_call(&port, RELEASE_SLOTS, object + BURSTS, BURST_COUNT, 0, 0);
    return port_return(&port, 0, 0);
}
