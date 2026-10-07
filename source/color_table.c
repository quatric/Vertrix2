#include "color_table.h"

enum
{
    MASK_RED = 0xff0000,
    MASK_GREEN = 0xff00,
    MASK_BLUE = 0xff,
    MASK_ALPHA = 0xff000000
};

void vertrix_color_table_build(const VertrixCalls *calls, uint32_t frame, uint32_t argument,
                               const uint32_t colors[7][3], uint32_t out[7][3])
{
    uint32_t object = frame - VERTRIX_COLOR_OBJECT;
    uint32_t ebx = 0;
    uint32_t ecx = 0;
    vertrix_call(calls, 0x481b20, object, VERTRIX_COLOR_FRAME_HANDLER, 0, VERTRIX_COLOR_FRAME_TYPE,
                 0);
    if (vertrix_call(calls, 0x481bc0, object, MASK_RED, MASK_GREEN, MASK_BLUE, MASK_ALPHA) == 0)
    {
        vertrix_call(calls, 0x481b30, object, 0, MASK_GREEN, MASK_BLUE, 0);
        return;
    }
    for (uint32_t row = 0; row < VERTRIX_COLOR_ROWS; ++row)
    {
        for (uint32_t column = 0; column < VERTRIX_COLOR_COLUMNS; ++column)
        {
            ebx = colors[row][column];
            ecx = column + 1;
            out[row][column] = vertrix_call(calls, 0x481e10, object, argument, ebx, ecx, 0);
        }
        ecx = VERTRIX_COLOR_COLUMNS;
    }
    vertrix_call(calls, 0x481b30, object, 0, ebx, ecx, 0);
}

uint32_t vertrix_color_table_build_full(const VertrixCalls *calls, uint32_t frame,
                                        uint32_t argument, uint32_t previous_exception,
                                        VertrixMemoryRead read, VertrixMemoryWrite write,
                                        void *context)
{
    if (!calls || !calls->call || !read || !write)
    {
        return 0;
    }
    uint32_t object = frame - VERTRIX_COLOR_OBJECT;
    uint32_t ebx = MASK_GREEN, ecx = MASK_BLUE;
    vertrix_call(calls, 0x481b20, object, VERTRIX_COLOR_FRAME_HANDLER, 0, VERTRIX_COLOR_FRAME_TYPE,
                 0);
    if (vertrix_call(calls, 0x481bc0, object, MASK_RED, MASK_GREEN, MASK_BLUE, MASK_ALPHA))
    {
        for (uint32_t row = 0; row < VERTRIX_COLOR_ROWS; ++row)
        {
            for (uint32_t column = 0; column < VERTRIX_COLOR_COLUMNS; ++column)
            {
                uint32_t offset = 4 * (row * VERTRIX_COLOR_COLUMNS + column);
                if (!read(0x4fb9f0 + offset, 4, &ebx, context))
                {
                    return 0;
                }
                ecx = column + 1;
                uint32_t entry = vertrix_call(calls, 0x481e10, object, argument, ebx, ecx, 0);
                if (!write(0x5440f8 + offset, 4, entry, context))
                {
                    return 0;
                }
            }
        }
    }
    vertrix_call(calls, 0x481b30, object, 0, ebx, ecx, 0);
    return previous_exception;
}
