#include "native_ports.h"

enum
{
    BYTE_WIDTH = 1,
    DWORD_WIDTH = 4,
    KIND_EMPTY = 0xff,
    SLOT_KIND = 0x15c
};

uint32_t vertrix_port_kind_snapshot(VertrixNativeMemory *memory, uint32_t slots, uint32_t kinds,
                                    uint32_t count)
{
    uint32_t end;
    if (count == 0)
    {
        return slots;
    }
    end = slots + (count << 2);
    do
    {
        uint32_t object;
        vertrix_native_put(memory, kinds, 0, BYTE_WIDTH, KIND_EMPTY);
        object = vertrix_native_get(memory, slots, 0, DWORD_WIDTH);
        if (object != 0)
        {
            vertrix_native_put(memory, kinds, 0, BYTE_WIDTH,
                               vertrix_native_get(memory, object, SLOT_KIND, BYTE_WIDTH));
        }
        slots += 4;
        kinds++;
    } while (slots < end && memory->ok);
    return slots;
}
