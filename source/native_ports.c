#include "native_ports.h"

enum
{
    BYTE_WIDTH = 1,
    DWORD_WIDTH = 4,
    KIND_EMPTY = 0xff,
    SLOT_KIND = 0x15c,
    BIT_POINTER = 0x51f014,
    BIT_INDEX = 0x51f018,
    SHIFT_MASK = 0x1f,
    BYTE_MASK = 0xff
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

uint32_t vertrix_port_bit_read(VertrixNativeMemory *memory)
{
    uint32_t pointer = vertrix_native_get(memory, BIT_POINTER, 0, DWORD_WIDTH);
    uint32_t value = vertrix_native_get(memory, pointer, 0, BYTE_WIDTH);
    uint32_t shift = vertrix_native_get(memory, BIT_INDEX, 0, BYTE_WIDTH) & SHIFT_MASK;
    uint32_t index = vertrix_native_get(memory, BIT_INDEX, 0, DWORD_WIDTH) + 1;
    value = shift >= 8 ? 0 : (value << shift) & BYTE_MASK;
    vertrix_native_put(memory, BIT_INDEX, 0, DWORD_WIDTH, index);
    pointer += (uint32_t)((int32_t)index >> 3);
    vertrix_native_put(memory, BIT_POINTER, 0, DWORD_WIDTH, pointer);
    vertrix_native_put(memory, BIT_INDEX, 0, DWORD_WIDTH, index & 7);
    return value >> 7;
}
