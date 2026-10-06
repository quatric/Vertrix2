#include "text_table.h"

#include "actor_storage.h"

enum
{
    DWORD_WIDTH = 4,
    TABLE_BASE = 0x53bdfc,
    ROW_BYTES = 0x24,
    ROWS = 20,
    COLUMNS = 9,
    FIRST_SOURCE = 0x53c0cc,
    FIRST_SELECTOR_BYTES = 80,
    FIRST_ROW_STEP = 4,
    FIRST_COLUMN_STEP = 0xf0,
    SECOND_SOURCE = 0x53c93c,
    SECOND_SELECTOR_BYTES = 24,
    SECOND_COLUMN_STEP = 0x1c8,
    SECOND_FIRST_ROW = 1,
    SECOND_ROWS = 6,
    LEADING = 0x53bd08,
    COUNTS = 0x53bd5c,
    LENGTHS = 0x53bdac,
    ASSIGN = 0x4ca310,
    CHECK = 0x4ccfe0,
    LEADING_KEY = 0x50d383,
    COUNT_KEY = 0x50d384,
    HEADER_SIZE = 0xc,
    HEADER_LENGTH = 4
};

static int region_read(const VertrixFactoryServices *services, uint32_t address, uint32_t *value)
{
    void *storage;
    size_t size;
    return services->resolve(VERTRIX_TEXT_TABLE_REGION, &storage, &size, services->context) &&
           vertrix_actor_storage_read(storage, size, address - VERTRIX_TEXT_TABLE_REGION,
                                      DWORD_WIDTH, value);
}

static int region_write(const VertrixFactoryServices *services, uint32_t address, uint32_t value)
{
    void *storage;
    size_t size;
    return services->resolve(VERTRIX_TEXT_TABLE_REGION, &storage, &size, services->context) &&
           vertrix_actor_storage_write(storage, size, address - VERTRIX_TEXT_TABLE_REGION,
                                       DWORD_WIDTH, value);
}

static int string_length(const VertrixFactoryServices *services, uint32_t text, uint32_t *length)
{
    void *storage;
    size_t size;
    return services->resolve(text - HEADER_SIZE, &storage, &size, services->context) &&
           vertrix_actor_storage_read(storage, size, HEADER_LENGTH, DWORD_WIDTH, length);
}

static void assign_column(const VertrixCalls *calls, uint32_t destination, uint32_t source)
{
    vertrix_call(calls, ASSIGN, destination, source, source, destination, 0);
}

int vertrix_text_table_refresh(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               uint32_t first, uint32_t second)
{
    for (uint32_t row = 0; row < ROWS; row++)
    {
        for (uint32_t column = 0; column < COLUMNS; column++)
        {
            assign_column(calls, TABLE_BASE + row * ROW_BYTES + column * DWORD_WIDTH,
                          FIRST_SOURCE + first * FIRST_SELECTOR_BYTES + row * FIRST_ROW_STEP +
                              column * FIRST_COLUMN_STEP);
        }
    }
    for (uint32_t row = 0; row < SECOND_ROWS; row++)
    {
        for (uint32_t column = 0; column < COLUMNS; column++)
        {
            assign_column(calls,
                          TABLE_BASE + (row + SECOND_FIRST_ROW) * ROW_BYTES + column * DWORD_WIDTH,
                          SECOND_SOURCE + second * SECOND_SELECTOR_BYTES + row * FIRST_ROW_STEP +
                              column * SECOND_COLUMN_STEP);
        }
    }
    for (uint32_t row = 0; row < ROWS; row++)
    {
        uint32_t found = COLUMNS;
        for (int32_t column = COLUMNS - 1; column >= 0; column--)
        {
            uint32_t slot = TABLE_BASE + row * ROW_BYTES + (uint32_t)column * DWORD_WIDTH, text;
            if (!region_read(services, slot, &text))
            {
                return 0;
            }
            if (vertrix_call(calls, CHECK, text, LEADING_KEY, (uint32_t)column, slot, 0) != 0)
            {
                break;
            }
            found--;
        }
        if (!region_write(services, LEADING + (row + 1) * DWORD_WIDTH, found))
        {
            return 0;
        }
    }
    for (uint32_t row = 0; row < ROWS; row++)
    {
        uint32_t count = 0, total = 0;
        for (uint32_t column = 0; column < COLUMNS; column++)
        {
            uint32_t slot = TABLE_BASE + row * ROW_BYTES + column * DWORD_WIDTH, text, length;
            if (!region_read(services, slot, &text))
            {
                return 0;
            }
            if (vertrix_call(calls, CHECK, text, COUNT_KEY, slot, column, 0) == 0)
            {
                continue;
            }
            if (!region_read(services, slot, &text) || !string_length(services, text, &length))
            {
                return 0;
            }
            count++;
            total += length;
        }
        if (!region_write(services, COUNTS + row * DWORD_WIDTH, count) ||
            !region_write(services, LENGTHS + row * DWORD_WIDTH, total))
        {
            return 0;
        }
    }
    return 1;
}
