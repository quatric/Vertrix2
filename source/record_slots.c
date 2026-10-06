#include "record_slots.h"
#include "actor_storage.h"

enum
{
    BYTE_WIDTH = 1,
    WORD_WIDTH = 2,
    DWORD_WIDTH = 4,
    RECORD_STATE_BYTE = 0,
    RECORD_STATE_ONE = 1,
    RECORD_STATE_TWO = 2,
    RECORD_STATE_WORD = 4,
    RECORD_STATE_SIX = 6,
    RECORD_STATE_SEVEN = 7,
    RECORD_STATE_EIGHT = 8,
    RECORD_STATE_LAST = 0xa,
    RECORD_ONE = 1,
    RECORD_TWO = 2,
    RECORD_STEP = 0xd,
    RECORD_LIMIT = 0x32,
    WORD_SHIFT = 16,
    BYTE_SHIFT = 24
};

/* Forward dword copy, as the original's string move; overlapping ranges see earlier writes. */
static int copy_record(uint8_t *storage, size_t size, size_t source, size_t destination)
{
    uint32_t value;
    size_t last = VERTRIX_RECORD_SIZE - DWORD_WIDTH;
    if (!vertrix_actor_storage_read(storage, size, source + last, DWORD_WIDTH, &value) ||
        !vertrix_actor_storage_read(storage, size, destination + last, DWORD_WIDTH, &value))
    {
        return 0;
    }
    for (size_t offset = 0; offset < VERTRIX_RECORD_SIZE; offset += DWORD_WIDTH)
    {
        vertrix_actor_storage_read(storage, size, source + offset, DWORD_WIDTH, &value);
        vertrix_actor_storage_write(storage, size, destination + offset, DWORD_WIDTH, value);
    }
    return 1;
}

int vertrix_record_load_current(uint8_t *storage, size_t size, uint32_t index)
{
    size_t offset = (uint32_t)(index * VERTRIX_RECORD_SIZE);
    return copy_record(storage, size, offset, VERTRIX_RECORD_CURRENT);
}

int vertrix_record_store_current(uint8_t *storage, size_t size, uint32_t index)
{
    size_t offset = (uint32_t)(index * VERTRIX_RECORD_SIZE);
    return copy_record(storage, size, VERTRIX_RECORD_CURRENT, offset);
}

static void init_record(uint8_t *storage, size_t size, size_t base)
{
    vertrix_actor_storage_write(storage, size, base + RECORD_STATE_BYTE, BYTE_WIDTH, 0);
    vertrix_actor_storage_write(storage, size, base + RECORD_STATE_SEVEN, BYTE_WIDTH, RECORD_TWO);
    vertrix_actor_storage_write(storage, size, base + RECORD_STATE_ONE, BYTE_WIDTH, RECORD_ONE);
    vertrix_actor_storage_write(storage, size, base + RECORD_STATE_WORD, WORD_WIDTH, 0);
    vertrix_actor_storage_write(storage, size, base + RECORD_STATE_SIX, BYTE_WIDTH, RECORD_STEP);
    vertrix_actor_storage_write(storage, size, base + RECORD_STATE_TWO, BYTE_WIDTH, RECORD_LIMIT);
    vertrix_actor_storage_write(storage, size, base + RECORD_STATE_LAST, WORD_WIDTH, 0);
    vertrix_actor_storage_write(storage, size, base + RECORD_STATE_EIGHT, BYTE_WIDTH, 0);
}

int vertrix_record_table_init(uint8_t *storage, size_t size, uint32_t owner)
{
    if (storage == 0 || size < VERTRIX_RECORD_STORAGE_SIZE)
    {
        return 0;
    }
    vertrix_actor_storage_write(storage, size, VERTRIX_RECORD_CLASS_OFFSET, DWORD_WIDTH,
                                VERTRIX_RECORD_CLASS);
    vertrix_actor_storage_write(storage, size, VERTRIX_RECORD_COUNT_OFFSET, DWORD_WIDTH, 1);
    vertrix_actor_storage_write(storage, size, VERTRIX_RECORD_OWNER_OFFSET, DWORD_WIDTH, owner);
    for (uint32_t slot = 0; slot < VERTRIX_RECORD_SLOTS; ++slot)
    {
        init_record(storage, size, slot * VERTRIX_RECORD_SIZE);
        vertrix_actor_storage_write(storage, size, VERTRIX_RECORD_FLAGS_OFFSET + 4 * slot,
                                    DWORD_WIDTH, 1);
    }
    init_record(storage, size, VERTRIX_RECORD_CURRENT);
    return 1;
}

static int read_field(const uint8_t *storage, size_t size, size_t offset, unsigned width,
                      uint32_t *raw)
{
    return vertrix_actor_storage_read(storage, size, offset, width, raw);
}

int vertrix_record_field(const uint8_t *storage, size_t size, uint32_t index, uint32_t field,
                         int32_t *value)
{
    size_t base = (uint32_t)(index * VERTRIX_RECORD_SIZE);
    uint32_t raw;
    switch (field)
    {
        case VERTRIX_RECORD_FIELD_0:
        case VERTRIX_RECORD_FIELD_1:
            if (!read_field(storage, size, base + field, BYTE_WIDTH, &raw))
            {
                return 0;
            }
            *value = (int8_t)raw;
            return 1;
        case VERTRIX_RECORD_FIELD_2:
            if (!read_field(storage, size, base + RECORD_STATE_TWO, BYTE_WIDTH, &raw))
            {
                return 0;
            }
            *value = (int32_t)raw;
            return 1;
        case VERTRIX_RECORD_FIELD_4:
            if (!read_field(storage, size, base + RECORD_STATE_TWO, DWORD_WIDTH, &raw))
            {
                return 0;
            }
            *value = (int32_t)raw >> WORD_SHIFT;
            return 1;
        case VERTRIX_RECORD_FIELD_6:
            if (!read_field(storage, size, base + RECORD_STATE_SIX, BYTE_WIDTH, &raw))
            {
                return 0;
            }
            *value = (int32_t)raw;
            return 1;
        case VERTRIX_RECORD_FIELD_7:
        case VERTRIX_RECORD_FIELD_8:
            if (!read_field(storage, size, base + (field == VERTRIX_RECORD_FIELD_7 ? 4 : 5),
                            DWORD_WIDTH, &raw))
            {
                return 0;
            }
            *value = (int32_t)raw >> BYTE_SHIFT;
            return 1;
        case VERTRIX_RECORD_FIELD_A:
            if (!read_field(storage, size, base + RECORD_STATE_LAST, WORD_WIDTH, &raw))
            {
                return 0;
            }
            *value = (int32_t)raw;
            return 1;
        default:
            *value = 0;
            return 1;
    }
}

typedef struct
{
    uint8_t offset;
    uint8_t width;
    uint8_t is_signed;
    uint8_t wraps;
    int32_t up_below;
    int32_t down_above;
    int32_t wrap_down;
} StepRule;

static const StepRule STEP_RULES[] = {
    {RECORD_STATE_BYTE, BYTE_WIDTH, 1, 0, 1, 0, 0},
    {RECORD_STATE_ONE, BYTE_WIDTH, 1, 0, 10, 0, 0},
    {RECORD_STATE_TWO, BYTE_WIDTH, 0, 0, 0x64, 0, 0},
    {RECORD_STATE_WORD, WORD_WIDTH, 1, 0, 200, -200, 0},
    {RECORD_STATE_SIX, BYTE_WIDTH, 0, 0, 0xd, 0, 0},
    {RECORD_STATE_SEVEN, BYTE_WIDTH, 1, 0, 2, 0, 0},
    {RECORD_STATE_EIGHT, BYTE_WIDTH, 1, 0, 1, 0, 0},
    {RECORD_STATE_LAST, WORD_WIDTH, 0, 1, 0xfe, 0, 0xfe},
};

static int32_t extend(uint32_t raw, const StepRule *rule)
{
    if (!rule->is_signed)
    {
        return (int32_t)raw;
    }
    return rule->width == BYTE_WIDTH ? (int8_t)raw : (int16_t)raw;
}

int vertrix_record_step(uint8_t *storage, size_t size, uint32_t index, uint32_t field, int increase)
{
    if (field >= sizeof STEP_RULES / sizeof STEP_RULES[0])
    {
        return 1;
    }
    const StepRule *rule = &STEP_RULES[field];
    size_t base = (uint32_t)(index * VERTRIX_RECORD_SIZE);
    uint32_t raw;
    uint32_t probe;
    if (field == VERTRIX_RECORD_FIELD_4 &&
        !vertrix_actor_storage_read(storage, size, base + RECORD_STATE_TWO, DWORD_WIDTH, &probe))
    {
        return 0;
    }
    if (!vertrix_actor_storage_read(storage, size, base + rule->offset, rule->width, &raw))
    {
        return 0;
    }
    int32_t value = extend(raw, rule);
    int32_t next;
    if (increase)
    {
        next = value < rule->up_below ? value + 1 : rule->wraps ? 0 : value;
    }
    else
    {
        next = value > rule->down_above ? value - 1 : rule->wraps ? rule->wrap_down : value;
    }
    if (next != value)
    {
        vertrix_actor_storage_write(storage, size, base + rule->offset, rule->width,
                                    (uint32_t)next);
    }
    return 1;
}
