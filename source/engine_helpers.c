#include "engine_helpers.h"
#include "actor_storage.h"

enum
{
    RANDOM_SAMPLES = 0x0,
    RANDOM_MODE = 0x4,
    RANDOM_CURSOR = 0x8,
    RANDOM_POSITION = 0xc,
    RANDOM_SEED = 0x10,
    RANDOM_CLASS = 0x14,
    RANDOM_CLASS_TOKEN = 0x516c24,
    TABLE_SAMPLES = 0x0,
    TABLE_DEFAULT = 0x4,
    TABLE_END = 0x8,
    TABLE_CLASS = 0xc,
    TABLE_CLASS_TOKEN = 0x516dc4,
    RLE_MAX_RUN = 0x3f,
    RLE_LITERAL_LIMIT = 0xc0
};

int vertrix_random_object_construct(void *storage, size_t size)
{
    if (!vertrix_actor_storage_write(storage, size, RANDOM_CLASS, 4, RANDOM_CLASS_TOKEN) ||
        !vertrix_actor_storage_write(storage, size, RANDOM_SAMPLES, 4, 0))
    {
        return 0;
    }
    vertrix_actor_storage_write(storage, size, RANDOM_MODE, 1, 1);
    vertrix_actor_storage_write(storage, size, RANDOM_CURSOR, 4, 0);
    vertrix_actor_storage_write(storage, size, RANDOM_POSITION, 2, 0);
    vertrix_actor_storage_write(storage, size, RANDOM_SEED, 4, 0);
    return 1;
}

int vertrix_table_object_construct(void *storage, size_t size, uint32_t default_value)
{
    if (!vertrix_actor_storage_write(storage, size, TABLE_CLASS, 4, TABLE_CLASS_TOKEN))
    {
        return 0;
    }
    vertrix_actor_storage_write(storage, size, TABLE_SAMPLES, 4, 0);
    vertrix_actor_storage_write(storage, size, TABLE_END, 4, 0);
    vertrix_actor_storage_write(storage, size, TABLE_DEFAULT, 4, default_value);
    return 1;
}

int vertrix_random_inclusive(VertrixRandom *random, uint16_t minimum, uint16_t maximum,
                             uint32_t *value)
{
    uint16_t width = (uint16_t)((uint32_t)maximum - minimum + 1);
    if (width == 0)
    {
        return 0;
    }
    *value = (uint32_t)vertrix_random_modulo(random, width) + minimum;
    return 1;
}

uint32_t vertrix_rle_encoded_length(const uint8_t *data, uint32_t count)
{
    uint32_t length = 0;
    uint32_t index = 0;
    while (count != 0)
    {
        uint8_t value = data[index];
        uint32_t run = 1;
        for (;;)
        {
            /* The original peeks one byte past the run; past the input it cannot matter. */
            uint8_t next = count > 1 ? data[index + 1] : 0;
            index++;
            count--;
            if (value != next || run >= RLE_MAX_RUN || count == 0)
            {
                break;
            }
            run++;
        }
        if (run == 1 && value < RLE_LITERAL_LIMIT)
        {
            length += 1;
        }
        else
        {
            length += 2;
        }
    }
    return length;
}

int vertrix_cursor_clamp(VertrixCursor *cursor)
{
    int16_t x = cursor->x;
    int16_t y = cursor->y;
    if (x < 0)
    {
        x = 0;
    }
    else if (x >= cursor->width)
    {
        x = (int16_t)(cursor->width - 1);
    }
    if (y < 0)
    {
        y = 0;
    }
    else if (y >= cursor->height)
    {
        y = (int16_t)(cursor->height - 1);
    }
    cursor->index = (int32_t)y * cursor->width + x;
    cursor->y = y;
    cursor->x = x;
    return 1;
}
