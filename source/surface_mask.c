#include "surface_mask.h"

enum
{
    MASK_OFFSET = 0x478eb0,
    MASK_ALPHA_SHIFT = 24,
    MASK_BIT = 1,
    MASK_COUNT = 0xffff
};

static uint32_t sign_extend16(uint32_t value)
{
    return (uint32_t)(int32_t)(int16_t)(value & MASK_COUNT);
}

void vertrix_surface_mask32(const VertrixCalls *calls, uint32_t surface, uint32_t mask_width,
                            uint32_t source_token, uint32_t skip, uint32_t x, uint32_t y,
                            uint32_t width, uint32_t height, const uint32_t *source, uint8_t *mask)
{
    uint32_t rows = height & MASK_COUNT;
    uint32_t columns = width & MASK_COUNT;
    vertrix_call(calls, MASK_OFFSET, surface, sign_extend16(x), sign_extend16(y), source_token, 0);
    for (; rows != 0; rows--)
    {
        for (uint32_t column = 0; column < columns; column++)
        {
            if ((source[column] >> MASK_ALPHA_SHIFT) != 0)
            {
                mask[column] |= MASK_BIT;
            }
        }
        source += columns + skip;
        mask += (int32_t)(mask_width - sign_extend16(width)) + columns;
    }
}
