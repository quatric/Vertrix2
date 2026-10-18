#include "rtlruntimeobjectdestroys.h"

enum
{
    /* The object made with the table 0x518a94 (0x4cbf10 is its base): its owned objects (+0x78,
     * +0xa4: method +4 destroys; +0xa0: its second table +0x1c, method +0x14 destroys), its two
     * modules (+0x8c, +0x90) and its two atoms (+0xa8, +0xaa). */
    OBJECT_TABLE = 0,
    OBJECT_FIRST = 0x78,
    OBJECT_SECOND = 0xa0,
    OBJECT_THIRD = 0xa4,
    OBJECT_MODULE_ONE = 0x8c,
    OBJECT_MODULE_TWO = 0x90,
    OBJECT_ATOM_ONE = 0xa8,
    OBJECT_ATOM_TWO = 0xaa,
    TABLE_VALUE = 0x518a94,
    SECOND_TABLE = 0x1c,
    METHOD_DESTROY = 4,
    SECOND_DESTROY = 0x14,
    DESTROY_MODE = 2,

    /* The thread data's flag (+0x14) that keeps the two shared objects. */
    DATA_KEEP = 0x14,
    SHARED_ONE = 0x5c5c08,
    SHARED_TWO = 0x5c5c04,

    /* The delete flags: bit 1 frees the memory, bit 2 deletes an array. */
    FLAG_FREE = 2,
    FLAG_ARRAY = 4,
    ARRAY_DESTRUCTOR = 0x518bc0,

    ARRAY_DELETE = 0x4ccb9f,
    ARRAY_FREE = 0x4ca040,
    THREAD_DATA = 0x4ce740,
    MODULE_RELEASE = 0x4dc4b0,
    GLOBAL_DELETE_ATOM = 0x4f1c10,
    BASE_DESTROY = 0x4cbfe0,
    FREE = 0x4ca050
};

/* Destroys an owned object through its table's `method` (eax = it, edx = 2, ebx = the object
 * destroyed, ecx = the table); returns eax. */
static uint32_t destroy(Port *port, uint32_t owned, uint32_t table, uint32_t method, uint32_t ebx)
{
    return port_call(port, port_u32(port, table, method), owned, DESTROY_MODE, ebx, table);
}

/* Original 0x4cae30 (eax = the object, edx = the delete flags): the destructor of the object with
 * the table 0x518a94. An array delete (flag 4) goes to 0x4ccb9f with the destructor 0x518bc0, then
 * 0x4ca040. Otherwise the table is set back, the owned objects +0x78 and +0xa0 destroyed, and,
 * unless the thread data (0x4ce740) keeps them, the shared objects 0x5c5c08 and 0x5c5c04 destroyed
 * and cleared; then the modules +0x8c and +0x90 released (0x4dc4b0), the atoms +0xa8 and +0xaa
 * deleted (GlobalDeleteAtom), the owned object +0xa4 destroyed and the base destructor 0x4cbfe0 run
 * with 1, the memory freed (0x4ca050) when flag 2 asks. Returns the base destructor's eax (the
 * array path: the object). The exception frame at fs:[0] is left out (docs/NATIVE-PORTS.md). */
uint32_t vertrix_port_rtl_runtime_object_destroy_4cae30(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t object = entry->eax;
    const uint32_t flags = entry->edx;
    uint32_t eax;
    if ((flags & FLAG_ARRAY) != 0)
    {
        eax = port_call(&port, ARRAY_DELETE, object, ARRAY_DESTRUCTOR, object, entry->ecx);
        port_call(&port, ARRAY_FREE, eax, vertrix_lift_edx, object, entry->ecx);
        return port_return(&port, object, vertrix_lift_edx);
    }
    port_set32(&port, object, OBJECT_TABLE, TABLE_VALUE);
    eax = object;
    uint32_t owned = port_u32(&port, object, OBJECT_FIRST);
    if (owned != 0)
    {
        eax = destroy(&port, owned, port_u32(&port, owned, 0), METHOD_DESTROY, object);
    }
    owned = port_u32(&port, object, OBJECT_SECOND);
    if (owned != 0)
    {
        eax = destroy(&port, owned, port_u32(&port, owned, SECOND_TABLE), SECOND_DESTROY, object);
    }
    eax = port_call(&port, THREAD_DATA, eax, vertrix_lift_edx, object, entry->ecx);
    if (port_u8(&port, eax, DATA_KEEP) == 0)
    {
        static const uint32_t shared[2] = {SHARED_ONE, SHARED_TWO};
        for (unsigned index = 0; index < 2; index++)
        {
            owned = port_u32(&port, shared[index], 0);
            if (owned != 0)
            {
                eax = destroy(&port, owned, port_u32(&port, owned, 0), METHOD_DESTROY, object);
                port_set32(&port, shared[index], 0, 0);
            }
        }
    }
    static const uint32_t modules[2] = {OBJECT_MODULE_ONE, OBJECT_MODULE_TWO};
    for (unsigned index = 0; index < 2; index++)
    {
        const uint32_t module = port_u32(&port, object, modules[index]);
        if (module != 0)
        {
            const uint32_t args[1] = {module};
            eax = port_call_stack(&port, MODULE_RELEASE, eax, vertrix_lift_edx, object, entry->ecx,
                                  args, 1);
        }
    }
    static const uint32_t atoms[2] = {OBJECT_ATOM_ONE, OBJECT_ATOM_TWO};
    for (unsigned index = 0; index < 2; index++)
    {
        const uint32_t atom = port_u16(&port, object, atoms[index]);
        if (atom != 0)
        {
            const uint32_t args[1] = {atom};
            port_call_stack(&port, GLOBAL_DELETE_ATOM, atom, vertrix_lift_edx, object, entry->ecx,
                            args, 1);
        }
    }
    owned = port_u32(&port, object, OBJECT_THIRD);
    if (owned != 0)
    {
        destroy(&port, owned, port_u32(&port, owned, 0), METHOD_DESTROY, object);
    }
    const uint32_t result = port_call(&port, BASE_DESTROY, object, 1, object, entry->ecx);
    if ((flags & FLAG_FREE) != 0)
    {
        port_call(&port, FREE, result, vertrix_lift_edx, result, entry->ecx);
    }
    return port_return(&port, result, vertrix_lift_edx);
}
