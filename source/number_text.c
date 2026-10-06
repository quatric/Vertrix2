#include "number_text.h"
#include <string.h>

int vertrix_number_text(uint32_t value, uint32_t mode, uint32_t width, uint32_t show_zero,
                        char *output, size_t capacity)
{
    if (!output)
    {
        return 0;
    }
    char digits[10];
    size_t count = 0;
    uint32_t remaining = value;
    do
    {
        digits[count++] = (char)('0' + remaining % 10);
        remaining /= 10;
    } while (remaining);
    size_t length = mode == 1 && width > count ? width : count;
    if (!value && !show_zero)
    {
        length = 0;
    }
    if (length >= capacity)
    {
        return 0;
    }
    if (length)
    {
        size_t padding = length - count;
        memset(output, '0', padding);
        for (size_t index = 0; index < count; ++index)
        {
            output[padding + index] = digits[count - index - 1];
        }
    }
    output[length] = '\0';
    return 1;
}
