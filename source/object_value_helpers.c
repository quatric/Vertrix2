#include "object_value_helpers.h"
#include "guest_bytes.h"

enum
{
    RAMP_COUNT_STORAGE = 0x28,
    RAMP_HALF = 0x80,
    RAMP_RANGE = 0x100,
    RAMP_LIMIT = 0xff,
    REMAINING_STORAGE = 0x1c,
    CLAMP_STORAGE = 0x4c,
    FORMAT_332 = 0,
    FORMAT_555 = 1,
    FORMAT_565 = 2
};

size_t vertrix_format_decimal(int32_t value, uint8_t width, char *dest)
{
    char digits[16];
    uint8_t count = 0;
    int negative = 0;
    if (value < 0)
    {
        negative = 1;
        value = (int32_t)(0u - (uint32_t)value);
        width = (uint8_t)(width - 1);
    }
    while (value != 0 && count < width)
    {
        int32_t quotient = value / 10;
        int32_t remainder = value - quotient * 10;
        digits[count++] = (char)(remainder + '0');
        value = quotient;
    }
    if (count == 0 && value == 0)
    {
        digits[count++] = '0';
    }
    if (negative)
    {
        digits[count++] = '-';
    }
    size_t length = 0;
    while (count > 0)
    {
        dest[length++] = digits[--count];
    }
    dest[length] = 0;
    return length;
}

int vertrix_object_fill_ramp(uint8_t *object, size_t size)
{
    if (!object || size < RAMP_COUNT_STORAGE)
    {
        return 0;
    }
    uint32_t count = vertrix_guest_get16(object, VERTRIX_RAMP_COUNT);
    uint32_t value = RAMP_HALF;
    uint32_t step = 0;
    if (size < VERTRIX_RAMP_FIRST + count)
    {
        return 0;
    }
    if (count == 0)
    {
        return 1;
    }
    if (count != 1)
    {
        step = RAMP_RANGE / (count - 1);
        value = 0;
    }
    for (uint32_t i = 0; i < count; ++i)
    {
        if (value > RAMP_LIMIT)
        {
            value = RAMP_LIMIT;
        }
        vertrix_guest_set8(object, VERTRIX_RAMP_FIRST + i, (uint8_t)value);
        value += step;
    }
    return 1;
}

int vertrix_object_remaining(uint8_t *object, size_t size)
{
    if (!object || size < REMAINING_STORAGE)
    {
        return 0;
    }
    uint32_t used = vertrix_guest_get32(object, 4) * vertrix_guest_get8(object, 0xc);
    uint32_t remaining = vertrix_guest_get32(object, 0x14) - used;
    vertrix_guest_set32(object, 0x18, remaining);
    vertrix_guest_set32(object, 0x10, remaining != 0);
    return remaining != 0;
}

static int32_t clamp_axis(int32_t value, int32_t minimum, int32_t maximum)
{
    if (value >= minimum)
    {
        if (value > maximum)
        {
            value = maximum;
        }
    }
    else
    {
        value = minimum;
    }
    return value;
}

int vertrix_object_clamp_position(uint8_t *object, size_t size, int32_t x, int32_t y)
{
    if (!object || size < CLAMP_STORAGE)
    {
        return 0;
    }
    int32_t min_x = vertrix_guest_get16(object, 0x3c);
    int32_t min_y = vertrix_guest_get16(object, 0x3e);
    int32_t max_x = vertrix_guest_get16(object, 0x40);
    int32_t max_y = vertrix_guest_get16(object, 0x42);
    x = clamp_axis(x, min_x, max_x);
    y = clamp_axis(y, min_y, max_y);
    vertrix_guest_set16(object, 0x48, (uint16_t)x);
    vertrix_guest_set16(object, 0x4a, (uint16_t)y);
    return 1;
}

uint32_t vertrix_pixel_pack(uint8_t format, uint32_t rgb, uint8_t *stored_format)
{
    uint32_t packed = rgb;
    if (format == FORMAT_332)
    {
        packed = ((rgb & 0xe00000) >> 10 | (rgb & 0xe000) >> 5 | (rgb & 0xc0)) >> 6;
    }
    else if (format == FORMAT_555)
    {
        packed = ((rgb & 0xf800) >> 3 | (rgb & 0xf80000) >> 6 | (rgb & 0xf8)) >> 3;
    }
    else if (format == FORMAT_565)
    {
        packed = ((rgb & 0xfc00) >> 2 | (rgb & 0xf80000) >> 5 | (rgb & 0xf8)) >> 3;
    }
    if (stored_format)
    {
        *stored_format = format;
    }
    return packed;
}
