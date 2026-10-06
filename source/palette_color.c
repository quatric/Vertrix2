#include "palette_color.h"
#include <string.h>

int vertrix_palette_lookup_entry(const uint8_t *maps, size_t size, uint16_t row,
                                 const uint8_t channels[3], uint32_t *output)
{
    if (!maps || !channels || !output || row > 200 || size < (size_t)(row + 1) * 101u)
    {
        return 0;
    }
    uint32_t entry = row;
    for (uint32_t channel = 0; channel < 3; ++channel)
    {
        uint32_t nearest = 0, minimum = 256;
        for (uint32_t index = 0; index <= 100; ++index)
        {
            int32_t difference = (int32_t)channels[channel] - maps[row * 101u + index];
            uint32_t distance = (uint32_t)(difference < 0 ? -difference : difference);
            if (distance < minimum)
            {
                minimum = distance;
                nearest = index;
            }
        }
        entry |= nearest << (24 - channel * 8);
    }
    *output = entry;
    return 1;
}

int vertrix_palette_channels(uint8_t *output, size_t size)
{
    if (!output || size < 201u * 101u)
    {
        return 0;
    }
    memset(output, 255, 201u * 101u);
    for (uint16_t row = 0; row <= 100; ++row)
    {
        for (uint16_t column = 0; column <= 100; ++column)
        {
            uint16_t color[3];
            vertrix_palette_color(0, column, row, color);
            output[row * 101u + column] = (uint8_t)color[1];
        }
    }
    for (uint32_t d = 0; d <= 100; ++d)
    {
        uint8_t value = output[100u * 101u + d];
        for (uint32_t i = 0; i < 101u - d; ++i)
        {
            output[(100u + i) * 101u + d + i] = value;
        }
    }
    return 1;
}

/* Original software subtraction rounds its aligned mantissa before
 * normalization, which differs from IEEE subtraction near cancellation. */
static float subtract_positive(float a, float b)
{
    uint32_t x, y;
    memcpy(&x, &a, 4);
    memcpy(&y, &b, 4);
    if (!y)
    {
        return a;
    }
    uint32_t exponent = (x >> 23) & 255u;
    uint32_t difference = exponent - ((y >> 23) & 255u);
    uint32_t left = ((x & 0x7fffffu) | 0x800000u) << 8;
    uint32_t right = ((y & 0x7fffffu) | 0x800000u) << 8;
    right = difference >= 32 ? 0 : right >> difference;
    uint32_t mantissa = left - right;
    if (!mantissa)
    {
        return 0.0f;
    }
    mantissa = (mantissa + 128u) & 0xffffff00u;
    while (!(mantissa & 0x80000000u))
    {
        mantissa <<= 1;
        --exponent;
    }
    x = (exponent << 23) | ((mantissa & 0x7fffffffu) >> 8);
    memcpy(&a, &x, 4);
    return a;
}

int vertrix_palette_color(uint16_t hue, uint16_t saturation, uint16_t value, uint16_t output[3])
{
    if (!output || hue > 360 || saturation > 100 || value > 100)
    {
        return 0;
    }
    float s = (float)((double)saturation * 0.01);
    float v = (float)((double)value * 0.01);
    float r = v, g = v, b = v;
    if (s != 0.0f)
    {
        float h = (float)((double)(hue == 360 ? 0 : hue) * 0.016666666666666666);
        uint16_t sector = (uint16_t)h;
        float f = subtract_positive(h, (float)sector);
        float p = v * subtract_positive(1.0f, s);
        float q = v * subtract_positive(1.0f, s * f);
        float t = v * subtract_positive(1.0f, s * subtract_positive(1.0f, f));
        switch (sector)
        {
            case 0:
                r = v;
                g = t;
                b = p;
                break;
            case 1:
                r = q;
                g = v;
                b = p;
                break;
            case 2:
                r = p;
                g = v;
                b = t;
                break;
            case 3:
                r = p;
                g = q;
                b = v;
                break;
            case 4:
                r = t;
                g = p;
                b = v;
                break;
            case 5:
                r = v;
                g = p;
                b = q;
                break;
        }
    }
    float channels[3] = {r, g, b};
    for (uint32_t i = 0; i < 3; ++i)
    {
        float scaled = (float)((double)channels[i] * 255.0);
        uint16_t integral = (uint16_t)scaled;
        output[i] = integral + (subtract_positive(scaled, (float)integral) >= 0.5f);
    }
    return 1;
}

int vertrix_palette_rgb(uint16_t red, uint16_t green, uint16_t blue, uint16_t output[3],
                        uint32_t *chromatic)
{
    if (!output || !chromatic || red > 255 || green > 255 || blue > 255)
    {
        return 0;
    }
    float r = (float)((double)red * (1.0 / 255.0));
    float g = (float)((double)green * (1.0 / 255.0));
    float b = (float)((double)blue * (1.0 / 255.0));
    float maximum = r > g ? r : g;
    maximum = maximum > b ? maximum : b;
    float minimum = r < g ? r : g;
    minimum = minimum < b ? minimum : b;
    float delta = subtract_positive(maximum, minimum);
    float saturation = maximum == 0.0f ? 0.0f : delta / maximum;
    float hue = 0.0f;
    if (saturation != 0.0f)
    {
        float a, z;
        double offset;
        if (r == maximum)
        {
            a = g;
            z = b;
            offset = 0.0;
        }
        else if (g == maximum)
        {
            a = b;
            z = r;
            offset = 120.0;
        }
        else
        {
            a = r;
            z = g;
            offset = 240.0;
        }
        float difference = a >= z ? subtract_positive(a, z) : -subtract_positive(z, a);
        hue = (float)((double)difference * 60.0 / (double)delta + offset);
        if (hue < 0.0f)
        {
            hue += 360.0f;
        }
    }
    output[0] = (uint16_t)hue;
    float channels[2] = {(float)((double)saturation * 100.0), (float)((double)maximum * 100.0)};
    for (uint32_t i = 0; i < 2; ++i)
    {
        uint16_t integral = (uint16_t)channels[i];
        output[i + 1] = integral + (subtract_positive(channels[i], (float)integral) >= 0.5f);
    }
    *chromatic = saturation != 0.0f;
    return 1;
}
