#include "surface_bounds.h"

enum
{
    MAX_DIMENSION = 0x7fff
};

static int16_t word(int32_t value)
{
    return (int16_t)(uint16_t)value;
}

static int pixel_is_set(const VertrixSurface *surface, uint32_t x, uint32_t y, int *set)
{
    uint8_t size = surface->bytes_per_pixel;
    uint32_t value = 0;
    if (size == 1 || size == 2 || size == 4)
    {
        if (!vertrix_surface_read(surface, x, y, &value))
        {
            return 0;
        }
    }
    *set = value != 0;
    return 1;
}

int vertrix_surface_bounds(const VertrixSurface *surface, VertrixSurfaceBounds *bounds,
                           uint32_t *differs)
{
    if (!surface || !bounds || !differs || !surface->data || surface->width > MAX_DIMENSION ||
        surface->height > MAX_DIMENSION)
    {
        return 0;
    }
    int32_t last_x = (int32_t)surface->width - 1;
    int32_t last_y = (int32_t)surface->height - 1;
    int16_t min_x = word(last_x);
    int16_t min_y = word(last_y);
    int16_t max_x = 0;
    int16_t max_y = 0;
    for (int32_t x = 0; x <= last_x; ++x)
    {
        for (int32_t y = 0; y <= last_y; ++y)
        {
            int set;
            if (!pixel_is_set(surface, (uint32_t)x, (uint32_t)y, &set))
            {
                return 0;
            }
            if (!set)
            {
                continue;
            }
            if (x < min_x)
            {
                min_x = word(x);
            }
            if (x > max_x)
            {
                max_x = word(x);
            }
            if (y < min_y)
            {
                min_y = word(y);
            }
            if (y > max_y)
            {
                max_y = word(y);
            }
        }
    }
    VertrixSurfaceBounds result;
    if (min_x == last_x)
    {
        result = (VertrixSurfaceBounds){0, 0, last_x + 1, last_y + 1};
    }
    else
    {
        result = (VertrixSurfaceBounds){min_x, min_y, max_x - min_x + 1, max_y - min_y + 1};
    }
    *bounds = result;
    *differs = !(result.x == 0 && result.y == 0 && result.width == (int32_t)surface->width &&
                 result.height == (int32_t)surface->height);
    return 1;
}
