#include "score_table.h"

enum
{
    NAME_STRIDE = 4,
    LAST_SHIFTED = 3
};

static uint32_t pack_ebx(uint32_t high, int8_t upper, int8_t lower)
{
    return (high & 0xffff0000u) | (uint32_t)(uint8_t)upper << 8 | (uint8_t)lower;
}

uint32_t vertrix_high_score_insert(const VertrixCalls *calls, uint32_t scores[5], uint32_t score,
                                   uint32_t ebx_high)
{
    int8_t rank = 0;
    int8_t shift;
    uint32_t result;
    while (rank < VERTRIX_SCORE_ENTRIES && score <= scores[rank])
    {
        ++rank;
    }
    if (rank >= VERTRIX_SCORE_ENTRIES)
    {
        return VERTRIX_SCORE_NOT_RANKED;
    }
    shift = LAST_SHIFTED;
    while (rank <= shift)
    {
        uint32_t slot = VERTRIX_SCORE_NAMES + NAME_STRIDE * (uint32_t)shift;
        vertrix_call(calls, 0x4ca310, slot + NAME_STRIDE, slot, pack_ebx(ebx_high, shift, rank),
                     NAME_STRIDE * (uint32_t)shift, 0);
        scores[shift + 1] = scores[shift];
        --shift;
    }
    result = vertrix_call(calls, 0x4ca370, VERTRIX_SCORE_NAMES + NAME_STRIDE * (uint32_t)rank,
                          VERTRIX_SCORE_DEFAULT_NAME, pack_ebx(ebx_high, shift, rank),
                          NAME_STRIDE * (uint32_t)rank, 0);
    scores[rank] = score;
    return (result & 0xffffff00u) | (uint8_t)rank;
}

uint32_t vertrix_quad_average(const VertrixCalls *calls, uint8_t a, uint8_t index,
                              uint32_t sum_address, uint32_t *sum, uint32_t *average)
{
    uint32_t values[4];
    uint32_t found = 0;
    uint32_t total = 0;
    uint32_t base = 4 * (uint32_t)index;
    for (uint32_t i = 0; i < 4; ++i)
    {
        values[i] = vertrix_call(calls, 0x417970, a, (base + i) & 0xff, i == 3 ? 0 : sum_address,
                                 base + i, 0);
    }
    for (uint32_t i = 0; i < 4; ++i)
    {
        if (values[i] != UINT32_MAX)
        {
            ++found;
            total += values[i];
        }
    }
    *sum = total;
    if (found == 0)
    {
        *average = 0;
        return total;
    }
    *average = 12 * total / found;
    return *average;
}
