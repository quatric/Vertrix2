#include "native_ports.h"

enum
{
    BYTE_WIDTH = 1,
    WORD_WIDTH = 2,
    DWORD_WIDTH = 4,
    KIND_EMPTY = 0xff,
    SLOT_KIND = 0x15c,
    BIT_POINTER = 0x51f014,
    BIT_INDEX = 0x51f018,
    SHIFT_MASK = 0x1f,
    BYTE_MASK = 0xff,
    COLUMNS = 5,
    ROWS = 13,
    CELL_EMPTY = 0xff,
    CELL_STONE = 5,
    CELL_BOMB = 6
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

static int inside(int x, int y)
{
    return x >= 0 && x < COLUMNS && y >= 0 && y < ROWS;
}

uint32_t vertrix_port_line_pass(VertrixNativeMemory *memory, uint32_t board, uint32_t mask,
                                uint32_t threshold, uint32_t reward)
{
    static const int DX[6] = {1, 0, 1, 1, -1, -1};
    static const int DY[6] = {0, 1, 1, 1, 1, 1};
    uint8_t scan[COLUMNS * ROWS];
    uint32_t found = 0;
    int limit = (int)(threshold & BYTE_MASK);
    for (int i = 0; i < COLUMNS * ROWS; i++)
    {
        scan[i] = (uint8_t)vertrix_native_get(memory, board, (size_t)i, BYTE_WIDTH);
    }
    for (int pass = 0; pass < 6 && memory->ok; pass++)
    {
        int starts = (pass == 0 || pass == 2 || pass == 4) ? ROWS : COLUMNS;
        for (int start = 0; start < starts; start++)
        {
            int x = pass == 0 || pass == 2 ? 0 : pass == 4 ? COLUMNS - 1 : start;
            int y = pass == 0 || pass == 2 || pass == 4 ? start : 0;
            int n = 0;
            int color = CELL_EMPTY;
            for (; inside(x, y); x += DX[pass], y += DY[pass])
            {
                int cell = scan[x * ROWS + y];
                int used = 0;
                if (cell == CELL_EMPTY || cell == CELL_STONE || cell == CELL_BOMB)
                {
                    color = cell;
                    n = 0;
                    continue;
                }
                if (cell != color)
                {
                    color = cell;
                    n = 1;
                    continue;
                }
                n++;
                if (n <= limit)
                {
                    continue;
                }
                for (int i = 0; i < n; i++)
                {
                    size_t at = (size_t)((x - i * DX[pass]) * ROWS + y - i * DY[pass]) * 4;
                    used += vertrix_native_get(memory, mask, at, DWORD_WIDTH) == 1;
                }
                for (int i = 0; i < n; i++)
                {
                    size_t at = (size_t)((x - i * DX[pass]) * ROWS + y - i * DY[pass]) * 4;
                    vertrix_native_put(memory, mask, at, DWORD_WIDTH, 1);
                }
                if (!used)
                {
                    vertrix_native_put(memory, reward, 0, WORD_WIDTH,
                                       vertrix_native_get(memory, reward, 0, WORD_WIDTH) + 1);
                    found = 1;
                }
            }
        }
    }
    return found;
}
