#include "table_loops.h"

enum
{
    ROW_STRIDE = 0x1c,
    ROW_LIMIT = 0xc4,
    ROW_BASE = 0x544ac0,
    ROW_OUTPUT = 0x546554,
    ROW_INDEX_TABLE = 0x546538,
    ROW_INDEX = 9,
    ROW_FRAMES = 8,
    COLUMN_OUTPUT = 0x544a50,
    COLUMN_SOURCE = 0x544a34,
    COLUMN_FRAMES = 0x13,
    GRID_TABLE = 0x544bf4,
    GRID_FINISH_ARGUMENT = 0x5b9c60
};

uint32_t vertrix_resource_rows_build(const VertrixCalls *calls, uint32_t ebx)
{
    uint32_t index = vertrix_call(calls, 0x4877f0, ROW_INDEX_TABLE, ROW_INDEX, ebx, ROW_BASE, 0);
    uint32_t row = ROW_BASE;
    uint32_t output = ROW_OUTPUT;
    uint32_t ecx = ROW_BASE;
    uint32_t result = 0;
    do
    {
        vertrix_call(calls, 0x487640, output, ROW_FRAMES, ebx, ecx, 0);
        for (ecx = 0; ecx < ROW_FRAMES;)
        {
            uint32_t frame = vertrix_call(calls, 0x4877f0, row, ecx, ebx, ecx, 0);
            uint32_t image = vertrix_call(calls, 0x4831b0, frame, index, 0, ecx, 0);
            ebx = image;
            result = vertrix_call(calls, 0x487850, output, ecx, ebx, ecx + 1, 0);
            ++ecx;
        }
        output += ROW_STRIDE;
        row += ROW_STRIDE;
        ebx = output;
    } while (row != ROW_BASE + ROW_LIMIT);
    return result;
}

uint32_t vertrix_resource_column_build(const VertrixCalls *calls)
{
    uint32_t result = vertrix_call(calls, 0x487640, COLUMN_OUTPUT, COLUMN_FRAMES, 0, 0, 0);
    uint32_t index = vertrix_call(calls, 0x4877f0, ROW_INDEX_TABLE, ROW_INDEX, 0, 0, 0);
    for (uint32_t i = 0; i < COLUMN_FRAMES; ++i)
    {
        uint32_t frame = vertrix_call(calls, 0x4877f0, COLUMN_SOURCE, i, 1, i, 0);
        uint32_t image = vertrix_call(calls, 0x4831b0, frame, index, 1, i, 0);
        vertrix_call(calls, 0x487850, COLUMN_OUTPUT, i, image, i, 0);
        result = vertrix_call(calls, 0x418270, 2, i, image, i + 1, 0);
    }
    return result;
}

uint32_t vertrix_resource_grid_finish(const VertrixCalls *calls, const VertrixTableDims *dims,
                                      uint32_t argument)
{
    uint32_t result = argument;
    if (dims->count == 0)
    {
        return argument;
    }
    if (dims->columns == 0)
    {
        return 0;
    }
    for (uint32_t i = 0; i < dims->count; ++i)
    {
        uint32_t row = i / dims->columns;
        uint32_t column = i - dims->columns * row;
        uint32_t ebx = (dims->cell_width + 1) * column + 1;
        uint32_t ecx = (dims->cell_height + 1) * row + 1;
        uint32_t entry = vertrix_call(calls, 0x4877f0, GRID_TABLE, i, ebx, ecx, 0);
        vertrix_call(calls, 0x482e10, entry, argument, ebx, ecx, 0);
        result = vertrix_call(calls, 0x483ed0, entry, GRID_FINISH_ARGUMENT, ebx, ecx, 0);
    }
    return result;
}

uint32_t vertrix_resource_single_finish(const VertrixCalls *calls, uint32_t selector,
                                        uint32_t argument)
{
    uint32_t entry = vertrix_call(calls, 0x4877f0, 0x544a6c, selector, 0, 0, 0);
    vertrix_call(calls, 0x482e10, entry, argument, 0, 0, 0);
    return vertrix_call(calls, 0x483ed0, entry, GRID_FINISH_ARGUMENT, 0, 0, 0);
}

uint32_t vertrix_resource_cell_rows(const VertrixCalls *calls, const VertrixCellRow rows[3],
                                    uint32_t argument, uint32_t ebx, uint32_t ecx)
{
    static const uint32_t tables[3] = {0x544ba0, 0x544bbc, 0x544bd8};
    static const uint32_t counts[3] = {12, 12, 7};
    uint32_t result = 0;
    for (int run = 0; run < 3; ++run)
    {
        for (uint32_t i = 0; i < counts[run]; ++i)
        {
            uint32_t entry = vertrix_call(calls, 0x4877f0, tables[run], i, ebx, ecx, 0);
            ecx = rows[run].top;
            ebx = (rows[run].spacing + 1) * i + rows[run].left;
            vertrix_call(calls, 0x482e10, entry, argument, ebx, ecx, 0);
            result = vertrix_call(calls, 0x483ed0, entry, GRID_FINISH_ARGUMENT, ebx, ecx, 0);
        }
    }
    return result;
}

uint32_t vertrix_resource_paired_finish(const VertrixCalls *calls, const uint32_t first[13],
                                        const uint32_t second[13], uint32_t argument)
{
    uint32_t result = 0;
    for (uint32_t i = 0; i < 13; ++i)
    {
        uint32_t entry = vertrix_call(calls, 0x4877f0, 0x544b84, i, 4 * i, 4 * i, 0);
        vertrix_call(calls, 0x482e10, entry, argument, first[i], second[i], 0);
        result =
            vertrix_call(calls, 0x483ed0, entry, GRID_FINISH_ARGUMENT, first[i], 4 * (i + 1), 0);
    }
    return result;
}

uint32_t vertrix_resource_indexed_finish(const VertrixCalls *calls, const uint8_t first[7],
                                         const uint8_t second[7], uint32_t line, uint32_t column,
                                         uint32_t argument)
{
    uint32_t cell = ROW_BASE + ROW_STRIDE * first[column];
    uint32_t offset = 24 * second[line];
    uint32_t result = 0;
    for (uint32_t i = 0; i < 8; ++i)
    {
        uint32_t entry = vertrix_call(calls, 0x4877f0, cell, i, 24 * i, offset, 0);
        vertrix_call(calls, 0x482e10, entry, argument, 24 * i, offset, 0);
        result =
            vertrix_call(calls, 0x483ed0, entry, GRID_FINISH_ARGUMENT, 24 * i, 24 * (i + 1), 0);
    }
    return result;
}

uint32_t vertrix_resource_stride_finish(const VertrixCalls *calls, uint32_t argument)
{
    uint32_t result = 0;
    for (uint32_t i = 0; i < 8; ++i)
    {
        uint32_t ebx = 1 + 31 * i;
        uint32_t entry = vertrix_call(calls, 0x4877f0, 0x544d28, i, ebx, 1, 0);
        vertrix_call(calls, 0x482e10, entry, argument, ebx, 1, 0);
        result = vertrix_call(calls, 0x483ed0, entry, GRID_FINISH_ARGUMENT, ebx, ebx + 31, 0);
    }
    return result;
}

uint32_t vertrix_resource_flagged_finish(const VertrixCalls *calls, uint32_t argument,
                                         uint32_t flag, uint32_t count)
{
    uint32_t result = argument;
    for (uint32_t i = 0; i < count; ++i)
    {
        uint32_t cell = 1 + 49 * i;
        uint32_t entry =
            vertrix_call(calls, 0x4877f0, flag == 0 ? 0x544d44 : 0x544d60, i, 1, cell, 0);
        vertrix_call(calls, 0x482e10, entry, argument, 1, cell, 0);
        if (flag == 1)
        {
            vertrix_call(calls, 0x483ce0, entry, argument, 1, cell, 0);
        }
        result = vertrix_call(calls, 0x483ed0, entry, GRID_FINISH_ARGUMENT, count, cell, 0);
    }
    return result;
}

void vertrix_table_identity_cells(uint8_t cells[7])
{
    uint32_t i;
    for (i = 0; i < 7; ++i)
    {
        cells[i] = (uint8_t)i;
    }
}
