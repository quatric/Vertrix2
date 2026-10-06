#include "table_queries.h"

void vertrix_table_byte_pair(const uint8_t *first, const uint8_t *second, uint8_t row,
                             uint8_t column, uint8_t *first_out, uint8_t *second_out)
{
    uint32_t index = (uint32_t)row * VERTRIX_PAIR_ROW_SIZE + column;
    *first_out = first[index];
    *second_out = second[index];
}

uint32_t vertrix_table_grid_value(const uint32_t *grid, uint32_t row, uint32_t column)
{
    return grid[row * VERTRIX_GRID_ROW_SIZE + column];
}

uint32_t vertrix_table_row_used(const uint8_t *flags, uint32_t row)
{
    uint32_t first = row * VERTRIX_FLAG_ROW_SIZE;
    for (uint32_t i = 0; i < VERTRIX_FLAG_ROW_SIZE; ++i)
    {
        if (flags[first + i] != 0)
        {
            return 1;
        }
    }
    return 0;
}

uint32_t vertrix_table_bonus(uint32_t base, uint32_t value, uint32_t limit,
                             const uint32_t *multipliers, uint32_t level)
{
    uint32_t steps = value < limit ? limit - value : 0;
    uint32_t total = steps * multipliers[level] + base;
    total += total >> 1;
    return total > VERTRIX_BONUS_CAP ? VERTRIX_BONUS_CAP : total;
}

uint32_t vertrix_table_column_count(const uint32_t *grid, const uint32_t *counts, uint32_t column,
                                    uint32_t value)
{
    uint32_t matches = 0;
    for (uint32_t row = 0; row < counts[column]; ++row)
    {
        if (grid[row * VERTRIX_SLOT_COLUMNS + column] == value)
        {
            ++matches;
        }
    }
    return matches;
}

uint32_t vertrix_table_column_nth(const uint32_t *grid, const uint32_t *counts, uint32_t column,
                                  uint32_t value, uint32_t n)
{
    uint32_t matches = 0;
    for (uint32_t row = 0; row < counts[column]; ++row)
    {
        if (grid[row * VERTRIX_SLOT_COLUMNS + column] != value)
        {
            continue;
        }
        if (matches == n)
        {
            return row;
        }
        ++matches;
    }
    return 0;
}

uint8_t vertrix_table_last_change(const uint32_t *table, uint32_t n)
{
    uint8_t last = 0;
    for (uint32_t i = 0; i <= n; ++i)
    {
        if (i > 0 && table[i + 1] != table[i])
        {
            last = (uint8_t)i;
        }
    }
    return (uint8_t)(last + 1);
}

uint32_t vertrix_table_level_for(const uint16_t *steps, uint32_t value)
{
    if (value == 0)
    {
        return 0;
    }
    for (uint32_t i = 0; i < VERTRIX_LEVEL_STEPS; ++i)
    {
        if (value >= steps[i])
        {
            return i + 1;
        }
    }
    return 0;
}

uint32_t vertrix_table_all_filled(const uint32_t *slots)
{
    for (uint32_t i = 0; i < VERTRIX_FILLED_SLOTS; ++i)
    {
        if (slots[i] == 0)
        {
            return 0;
        }
    }
    return 1;
}

int32_t vertrix_table_find_matching(const uint32_t *items, uint32_t count, uint32_t key,
                                    VertrixCompare compare, void *context)
{
    int32_t found = VERTRIX_NO_MATCH;
    for (uint32_t i = 0; i < count; ++i)
    {
        if (compare(items[i], key, context) == 0)
        {
            found = (int32_t)i;
        }
    }
    return found;
}

int32_t vertrix_table_find_equal(const uint32_t *items, uint32_t count, uint32_t key)
{
    int32_t found = VERTRIX_NO_MATCH;
    for (uint32_t i = 0; i < count; ++i)
    {
        if (items[i] == key)
        {
            found = (int32_t)i;
        }
    }
    return found;
}

int vertrix_table_pair_select(const uint32_t *table, uint32_t column, uint32_t mode,
                              uint32_t *first, uint32_t *second)
{
    uint32_t row;
    if (mode < VERTRIX_PAIR_MODE_LAST)
    {
        row = mode * 2;
    }
    else if (mode == VERTRIX_PAIR_MODE_LAST + 1)
    {
        row = 10;
    }
    else if (mode == VERTRIX_PAIR_MODE_LAST)
    {
        row = 12;
    }
    else
    {
        return 0;
    }
    *first = table[row * VERTRIX_PAIR_TABLE_ROW + column];
    *second = table[(row + 1) * VERTRIX_PAIR_TABLE_ROW + column];
    return 1;
}

uint32_t vertrix_table_pair_link(const uint8_t *first, const uint8_t *second, const uint8_t *links,
                                 uint8_t row, uint8_t column)
{
    uint32_t index = (uint32_t)row * VERTRIX_PAIR_ROW_SIZE + column;
    uint8_t a = first[index];
    uint8_t b = second[index];
    if (a == 0 || b == 0)
    {
        return 0xffffffffu;
    }
    return links[(uint32_t)a * VERTRIX_LINK_ROW_SIZE + b];
}

uint32_t vertrix_table_groups_used(const uint8_t *flags, uint32_t row)
{
    uint32_t used = 0;
    for (uint32_t group = 0; group < VERTRIX_GROUPS; ++group)
    {
        uint32_t first = row * VERTRIX_GROUP_ROW_SIZE + group * VERTRIX_GROUP_SIZE;
        uint32_t any = 0;
        for (uint32_t i = 0; i < VERTRIX_GROUP_SIZE; ++i)
        {
            if (flags[first + i] != 0)
            {
                any = 1;
            }
        }
        used += any;
    }
    return used;
}

uint32_t vertrix_table_random_empty(const uint32_t *slots, VertrixDraw draw, void *context)
{
    uint32_t empty[VERTRIX_OPEN_SLOTS];
    uint32_t count = 0;
    for (uint32_t i = 0; i < VERTRIX_OPEN_SLOTS; ++i)
    {
        if (slots[i] == 0)
        {
            empty[count] = i;
            count += 1;
        }
    }
    if (count == 0)
    {
        return 0;
    }
    uint32_t pick = draw(count, context) & 0xffff;
    return pick < count ? empty[pick] : 0;
}

static int row_is_open(uint32_t value)
{
    return value == 0 || value == 3 || value == 4 || value == 5;
}

uint32_t vertrix_table_column_open(const uint32_t *grid, const uint32_t *counts, uint32_t column)
{
    uint32_t open = 0;
    for (uint32_t row = 0; row < counts[column]; ++row)
    {
        if (row_is_open(grid[row * VERTRIX_SLOT_COLUMNS + column]))
        {
            ++open;
        }
    }
    return open;
}

uint32_t vertrix_table_column_open_nth(const uint32_t *grid, const uint32_t *counts,
                                       uint32_t column, uint32_t n)
{
    uint32_t seen = 0;
    for (uint32_t row = 0; row < counts[column]; ++row)
    {
        if (!row_is_open(grid[row * VERTRIX_SLOT_COLUMNS + column]))
        {
            continue;
        }
        if (seen == n)
        {
            return row;
        }
        ++seen;
    }
    return 0;
}

uint32_t vertrix_table_value_matching(const uint32_t *items, const uint32_t *values, uint32_t count,
                                      uint32_t key, VertrixCompare compare, void *context)
{
    int32_t index = vertrix_table_find_matching(items, count, key, compare, context);
    return index < 0 ? 0 : values[index];
}

uint32_t vertrix_table_value_equal(const uint32_t *items, const uint32_t *values, uint32_t count,
                                   uint32_t key)
{
    int32_t index = vertrix_table_find_equal(items, count, key);
    return index < 0 ? 0 : values[index];
}
