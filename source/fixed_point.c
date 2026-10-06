#include "fixed_point.h"

enum
{
    FIXED_SHIFT = 16,
    HALF_TURN = 0xb4,
    FULL_TURN = 0x168
};

int32_t vertrix_fixed_multiply(int32_t a, int32_t b)
{
    int64_t product = (int64_t)a * (int64_t)b;
    return (int32_t)(uint32_t)((uint64_t)product >> FIXED_SHIFT);
}

int32_t vertrix_fixed_divide(int32_t a, int32_t b, int *valid)
{
    int64_t dividend = (int64_t)a * (1 << FIXED_SHIFT);
    *valid = 0;
    if (b == 0)
    {
        return 0;
    }
    int64_t quotient = dividend / b;
    if (quotient > INT32_MAX || quotient < INT32_MIN)
    {
        return 0;
    }
    *valid = 1;
    return (int32_t)quotient;
}

uint32_t vertrix_integer_root(uint32_t value, int *valid)
{
    uint32_t guess = 1;
    uint32_t next;
    uint32_t difference;
    *valid = 1;
    do
    {
        if (guess == 0)
        {
            *valid = 0;
            return 0;
        }
        next = (value / guess + guess) >> 1;
        difference = next - guess;
        if ((int32_t)difference < 0)
        {
            difference = 0u - difference;
        }
        guess = next;
    } while ((int32_t)difference > 1);
    return guess;
}

uint32_t vertrix_point_distance(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, int *valid)
{
    int32_t dx = (int16_t)x2 - (int16_t)x1;
    int32_t dy = (int16_t)y2 - (int16_t)y1;
    uint32_t squared = (uint32_t)dx * (uint32_t)dx + (uint32_t)dy * (uint32_t)dy;
    return vertrix_integer_root(squared, valid);
}

uint32_t vertrix_angle_from_ratio(const uint16_t table[VERTRIX_RATIO_TABLE_SIZE], int32_t ratio)
{
    if (ratio >= 0)
    {
        if (ratio >= VERTRIX_RATIO_TABLE_SIZE)
        {
            return 0;
        }
        return table[ratio];
    }
    int32_t magnitude = (int32_t)(0u - (uint32_t)ratio);
    if (magnitude >= VERTRIX_RATIO_TABLE_SIZE)
    {
        return HALF_TURN;
    }
    return HALF_TURN - table[magnitude & 0xffff];
}

uint16_t vertrix_point_heading(const uint16_t table[VERTRIX_RATIO_TABLE_SIZE], uint16_t x1,
                               uint16_t y1, uint16_t x2, uint16_t y2, int *valid)
{
    uint16_t dx = (uint16_t)((uint32_t)x2 - x1);
    uint16_t dy = (uint16_t)((uint32_t)y2 - y1);
    *valid = 1;
    if (dx == 0 && dy == 0)
    {
        return 0;
    }
    int32_t horizontal = (int16_t)dx;
    int32_t vertical = (int16_t)dy;
    uint32_t squared =
        (uint32_t)horizontal * (uint32_t)horizontal + (uint32_t)vertical * (uint32_t)vertical;
    uint32_t distance = vertrix_integer_root(squared, valid);
    if (!*valid)
    {
        return 0;
    }
    int32_t scaled_distance = (int32_t)(distance << FIXED_SHIFT);
    int32_t numerator = horizontal;
    if (horizontal < 0)
    {
        numerator = -horizontal;
    }
    int32_t ratio =
        vertrix_fixed_divide((int32_t)((uint32_t)numerator << FIXED_SHIFT), scaled_distance, valid);
    if (!*valid)
    {
        return 0;
    }
    if (horizontal < 0)
    {
        ratio = (int32_t)(0u - (uint32_t)ratio);
    }
    uint16_t angle = (uint16_t)vertrix_angle_from_ratio(table, ratio);
    if (vertical > 0)
    {
        angle = (uint16_t)(FULL_TURN - angle);
    }
    return angle;
}
