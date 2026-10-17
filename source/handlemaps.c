#include "handlemaps.h"

/* MFC keeps, per thread, maps from Windows handles to the C++ objects wrapping them (CHandleMap).
 * When a thread ends, each map it has is deleted: its objects lose their handles and are deleted
 * with it. */

enum
{
    /* The thread's maps (eax 0: give the map without creating one; 0 when there is none). */
    DC_MAP = 0x4dd3e0,
    GDI_MAP = 0x4ddbe0,
    MENU_MAP = 0x4e11b0,
    WINDOW_MAP = 0x4cf880,

    /* The CHandleMap: its permanent map (a CMapPtrToPtr: +0xc its count), the offset of the
     * handles in an object and how many it has (a CDC has two). */
    PERMANENT = 0x1c,
    MAP_COUNT = 0xc,
    HANDLE_OFFSET = 0x3c,
    HANDLE_COUNT = 0x40,

    /* The map's first position before GetNextAssoc: none for an empty map, else -1. */
    BEFORE_START = 0xffffffffu,
    GET_NEXT_ASSOC = 0x4df220,
    REMOVE_ALL = 0x4def90,
    /* An object's method table and its deleting destructor (edx 2: free it too). */
    DESTRUCTOR = 4,
    DELETE_TOO = 2,

    /* The shared tail 0x4dee00 saves five registers and keeps three locals under them, whose
     * addresses GetNextAssoc is given. */
    BELOW = 0x20,
    POSITION = 0x20,
    KEY = 0x1c,
    VALUE = 0x18
};

/* The original's 0x4dee00, which every one of these jumps to with a map: walk the permanent map
 * (GetNextAssoc, 0x4df220), clear each object's handles and delete it (its virtual destructor,
 * flag 2), then empty the map (0x4def90). Returns what 0x4def90 returns. */
static uint32_t delete_map(Port *port, const LiftEntry *entry, uint32_t map)
{
    const uint32_t position = entry->esp - POSITION;
    const uint32_t key = entry->esp - KEY;
    const uint32_t value = entry->esp - VALUE;
    const uint32_t permanent = map + PERMANENT;
    const uint32_t start = port_u32(port, permanent, MAP_COUNT) == 0 ? 0 : BEFORE_START;
    port_set32(port, position, 0, start);
    while (port_u32(port, position, 0) != 0 && !port->env.failed)
    {
        port_call(port, GET_NEXT_ASSOC, permanent, position, key, value);
        const uint32_t object = port_u32(port, value, 0);
        const uint32_t handles = object + port_u32(port, map, HANDLE_OFFSET);
        port_set32(port, handles, 0, 0);
        if (port_u32(port, map, HANDLE_COUNT) == 2)
        {
            port_set32(port, handles, 4, 0);
        }
        if (port_u32(port, value, 0) != 0)
        {
            const uint32_t object_now = port_u32(port, value, 0);
            const uint32_t methods = port_u32(port, object_now, 0);
            /* A virtual call, compared in every register: ebx holds the method table as in the
             * original, and ecx the value's address (what the verifier's GetNextAssoc stub leaves;
             * the destructor reads only eax and edx). */
            port_call(port, port_u32(port, methods, DESTRUCTOR), object_now, DELETE_TOO, methods,
                      value);
        }
    }
    return port_call(port, REMOVE_ALL, permanent, 0, 0, 0);
}

/* Delete the calling thread's map from `fetch`, if it has one. Returns 0 without a map. */
static uint32_t delete_thread_map(PORT_SIGNATURE, uint32_t fetch)
{
    Port port;
    uint8_t stack[BELOW + 8];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t map = port_call(&port, fetch, 0, 0, 0, 0);
    if (map == 0)
    {
        return port_return(&port, 0, 0);
    }
    return port_return(&port, delete_map(&port, entry, map), 0);
}

/* Original 0x4dd430: delete the calling thread's CDC (device context) map. */
uint32_t vertrix_port_delete_thread_dc_map(PORT_SIGNATURE)
{
    return delete_thread_map(calls, services, globals, entry, DC_MAP);
}

/* Original 0x4ddc30: delete the calling thread's CGdiObject map. */
uint32_t vertrix_port_delete_thread_gdi_map(PORT_SIGNATURE)
{
    return delete_thread_map(calls, services, globals, entry, GDI_MAP);
}

/* Original 0x4e1200: delete the calling thread's CMenu map. */
uint32_t vertrix_port_delete_thread_menu_map(PORT_SIGNATURE)
{
    return delete_thread_map(calls, services, globals, entry, MENU_MAP);
}

/* Original 0x4cf8d0: delete the calling thread's CWnd (window) map. */
uint32_t vertrix_port_delete_thread_window_map(PORT_SIGNATURE)
{
    return delete_thread_map(calls, services, globals, entry, WINDOW_MAP);
}
