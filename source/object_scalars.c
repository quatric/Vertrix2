#include "object_scalars.h"
#include "object_access.h"

enum
{
    FLAG_TABLE = 0x5cc,
    PERIOD = 0xc0,
    COUNTER = 0xbc,
    PIECE_OFFSET_X = 0x16c,
    PIECE_OFFSET_Y = 0x16d,
    WORD_Y = 0x16,
    WORD_LIMIT = 0xae,
    PLAYER_E0 = 0x4e0,
    PLAYER_E8 = 0x4e8,
    PLAYER_CD = 0x4cd,
    PLAYER_CC = 0x4cc,
    PLAYER_C4 = 0x4c4,
    PLAYER_STATE_BYTE = 0x4dc,
    PLAYER_STATE_DWORD = 0x470,
    PLAYER_STATE_BYTE_VALUE = 2,
    PLAYER_STATE_DWORD_VALUE = 3,
    PLAYER_PARTNER = 0x3b0
};

int vertrix_object_toggle_flag(void *storage, size_t size, uint32_t index)
{
    size_t offset = FLAG_TABLE + (size_t)index * 4;
    uint32_t value;
    return vertrix_actor_storage_read(storage, size, offset, 4, &value) &&
           vertrix_actor_storage_write(storage, size, offset, 4, value != 1);
}

int vertrix_object_flag(const void *storage, size_t size, uint32_t index, uint32_t *value)
{
    return vertrix_actor_storage_read(storage, size, FLAG_TABLE + (size_t)index * 4, 4, value);
}

int vertrix_object_set_period(void *storage, size_t size, uint32_t value)
{
    return vertrix_actor_storage_write(storage, size, PERIOD, 4, value);
}

int vertrix_object_set_counter(void *storage, size_t size, uint32_t value)
{
    return vertrix_actor_storage_write(storage, size, COUNTER, 4, value);
}

int vertrix_object_counter_to_period(void *storage, size_t size)
{
    uint32_t period;
    return vertrix_actor_storage_read(storage, size, PERIOD, 4, &period) &&
           vertrix_actor_storage_write(storage, size, COUNTER, 4, period);
}

int vertrix_object_clear_counter(void *storage, size_t size)
{
    return vertrix_actor_storage_write(storage, size, COUNTER, 4, 0);
}

int vertrix_piece_clear_offset_x(void *storage, size_t size)
{
    return vertrix_actor_storage_write(storage, size, PIECE_OFFSET_X, 1, 0);
}

int vertrix_piece_clear_offset_y(void *storage, size_t size)
{
    return vertrix_actor_storage_write(storage, size, PIECE_OFFSET_Y, 1, 0);
}

int vertrix_object_y_above_limit(const void *storage, size_t size, uint32_t *above)
{
    uint32_t y, limit;
    if (!vertrix_actor_storage_read(storage, size, WORD_Y, 2, &y) ||
        !vertrix_actor_storage_read(storage, size, WORD_LIMIT, 2, &limit))
    {
        return 0;
    }
    *above = (int16_t)y > (int16_t)limit;
    return 1;
}

int vertrix_player_set_e0(void *storage, size_t size, uint32_t value)
{
    return vertrix_actor_storage_write(storage, size, PLAYER_E0, 4, value);
}

int vertrix_player_e0(const void *storage, size_t size, uint32_t *value)
{
    return vertrix_actor_storage_read(storage, size, PLAYER_E0, 4, value);
}

int vertrix_player_has_e8(const void *storage, size_t size, uint32_t *flag)
{
    uint32_t value;
    if (!vertrix_actor_storage_read(storage, size, PLAYER_E8, 4, &value))
    {
        return 0;
    }
    *flag = value != 0;
    return 1;
}

int vertrix_player_set_cd(void *storage, size_t size, uint8_t value)
{
    return vertrix_actor_storage_write(storage, size, PLAYER_CD, 1, value);
}

int vertrix_player_set_cc(void *storage, size_t size, uint8_t value)
{
    return vertrix_actor_storage_write(storage, size, PLAYER_CC, 1, value);
}

int vertrix_player_c4_is_one(const void *storage, size_t size, uint32_t *flag)
{
    uint32_t value;
    if (!vertrix_actor_storage_read(storage, size, PLAYER_C4, 1, &value))
    {
        return 0;
    }
    *flag = value == 1;
    return 1;
}

int vertrix_player_enter_state(void *storage, size_t size)
{
    uint32_t probe;
    if (!vertrix_actor_storage_read(storage, size, PLAYER_STATE_BYTE, 1, &probe) ||
        !vertrix_actor_storage_read(storage, size, PLAYER_STATE_DWORD, 4, &probe))
    {
        return 0;
    }
    return vertrix_actor_storage_write(storage, size, PLAYER_STATE_BYTE, 1,
                                       PLAYER_STATE_BYTE_VALUE) &&
           vertrix_actor_storage_write(storage, size, PLAYER_STATE_DWORD, 4,
                                       PLAYER_STATE_DWORD_VALUE);
}

int vertrix_player_partner_not_cc_one(const void *storage, size_t size,
                                      VertrixObjectStorage resolve, void *context, uint32_t *flag)
{
    uint32_t partner, value;
    if (!vertrix_actor_storage_read(storage, size, PLAYER_PARTNER, 4, &partner) ||
        !vertrix_object_read(partner, resolve, context, PLAYER_CC, 1, &value))
    {
        return 0;
    }
    *flag = value != 1;
    return 1;
}

int vertrix_global_set_cell(uint32_t *cells, uint32_t count, uint32_t index)
{
    if (!cells || index >= count)
    {
        return 0;
    }
    cells[index] = 1;
    return 1;
}

int vertrix_global_cell(const uint32_t *cells, uint32_t count, uint32_t index, uint32_t *value)
{
    if (!cells || index >= count)
    {
        return 0;
    }
    *value = cells[index];
    return 1;
}

void vertrix_global_clear(uint32_t *cell)
{
    *cell = 0;
}

void vertrix_global_increment(uint32_t *cell)
{
    *cell += 1;
}

void vertrix_global_clear_tables(uint32_t first[19], uint32_t second[19])
{
    for (int i = 0; i < 19; ++i)
    {
        first[i] = 0;
        second[i] = 0;
    }
}

int vertrix_global_next_index(uint32_t *index)
{
    *index += 1;
    return *index != 7;
}

void vertrix_global_reset_pair(uint32_t mode, uint32_t *first, uint32_t *second)
{
    if (mode == 1)
    {
        *first = 0;
        *second = 0;
    }
}

int32_t vertrix_compare_unsigned(uint32_t left, uint32_t right)
{
    return left > right ? 1 : left < right ? -1 : 0;
}

uint32_t vertrix_table_used_count(const uint32_t table[7])
{
    uint32_t used = 0;
    for (int i = 0; i < 7; ++i)
    {
        used += table[i] != 0xffffffffu;
    }
    return used;
}

int vertrix_player_partner_free(const void *storage, size_t size, VertrixObjectStorage resolve,
                                void *context, uint32_t *flag)
{
    uint32_t partner, value;
    if (!vertrix_actor_storage_read(storage, size, PLAYER_PARTNER, 4, &partner) ||
        !vertrix_object_read(partner, resolve, context, PLAYER_CC, 1, &value))
    {
        return 0;
    }
    *flag = value != 1 && value != 4;
    return 1;
}

int vertrix_global_set_first_cell_full(uint32_t eax, VertrixMemoryRead read,
                                       VertrixMemoryWrite write, void *context, uint32_t *result)
{
    (void)read;
    if (!result)
    {
        return 0;
    }
    if (!write || !write(0x5344a4u + eax * 4u, 4, 1, context))
    {
        return 0;
    }
    *result = eax;
    return 1;
}

int vertrix_global_set_second_cell_full(uint32_t eax, VertrixMemoryRead read,
                                        VertrixMemoryWrite write, void *context, uint32_t *result)
{
    (void)read;
    if (!result)
    {
        return 0;
    }
    if (!write || !write(0x5344f0u + eax * 4u, 4, 1, context))
    {
        return 0;
    }
    *result = eax;
    return 1;
}

int vertrix_global_set_current_cell_full(uint32_t eax, VertrixMemoryRead read,
                                         VertrixMemoryWrite write, void *context, uint32_t *result)
{
    if (!result)
    {
        return 0;
    }
    if (!read || !write || !read(0x53bb10, 4, &eax, context) ||
        !write(0x53baf4u + eax * 4u, 4, 1, context))
    {
        return 0;
    }
    *result = eax;
    return 1;
}

int vertrix_global_read_current_cell_full(uint32_t eax, VertrixMemoryRead read,
                                          VertrixMemoryWrite write, void *context, uint32_t *result)
{
    (void)write;
    if (!result)
    {
        return 0;
    }
    if (!read || !read(0x53bb10, 4, &eax, context) || !read(0x53bad8u + eax * 4u, 4, &eax, context))
    {
        return 0;
    }
    *result = eax;
    return 1;
}

int vertrix_global_clear_full(uint32_t eax, VertrixMemoryRead read, VertrixMemoryWrite write,
                              void *context, uint32_t *result)
{
    (void)read;
    if (!result)
    {
        return 0;
    }
    if (!write || !write(0x54004c, 4, 0, context))
    {
        return 0;
    }
    *result = eax;
    return 1;
}

int vertrix_global_increment_full(uint32_t eax, VertrixMemoryRead read, VertrixMemoryWrite write,
                                  void *context, uint32_t *result)
{
    if (!result)
    {
        return 0;
    }
    uint32_t value;
    if (!read || !write || !read(0x5329f8, 4, &value, context) ||
        !write(0x5329f8, 4, value + 1u, context))
    {
        return 0;
    }
    *result = eax;
    return 1;
}

int vertrix_global_clear_tables_full(uint32_t eax, VertrixMemoryRead read, VertrixMemoryWrite write,
                                     void *context, uint32_t *result)
{
    (void)read;
    if (!result)
    {
        return 0;
    }
    if (!write)
    {
        return 0;
    }
    for (uint32_t offset = 0; offset < 76; offset += 4)
    {
        if (!write(0x5344a4 + offset, 4, 0, context) || !write(0x5344f0 + offset, 4, 0, context))
        {
            return 0;
        }
    }
    eax = 76;
    *result = eax;
    return 1;
}

int vertrix_global_next_index_full(uint32_t eax, VertrixMemoryRead read, VertrixMemoryWrite write,
                                   void *context, uint32_t *result)
{
    if (!result)
    {
        return 0;
    }
    uint32_t value;
    if (!read || !write || !read(0x53bb10, 4, &value, context) ||
        !write(0x53bb10, 4, value + 1u, context))
    {
        return 0;
    }
    eax = value + 1u != 7;
    *result = eax;
    return 1;
}

int vertrix_global_reset_pair_full(uint32_t eax, VertrixMemoryRead read, VertrixMemoryWrite write,
                                   void *context, uint32_t *result)
{
    if (!result)
    {
        return 0;
    }
    uint32_t value;
    if (!read || !read(0x532b40, 4, &value, context))
    {
        return 0;
    }
    if (value == 1)
    {
        if (!write || !write(0x532b48, 4, 0, context) || !write(0x532b44, 4, 0, context))
        {
            return 0;
        }
    }
    *result = eax;
    return 1;
}
