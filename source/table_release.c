#include "table_release.h"

enum
{
    INDEXED_STRIDE = 28,
    SINGLE_FIRST = 0x544a34,
    SINGLE_SECOND = 0x544a50,
    SINGLE_THIRD = 0x5464e4,
    RUN_A_FIRST = 0x546458,
    RUN_A_COUNT = 5,
    RUN_B_FIRST = 0x544d7c,
    RUN_B_COUNT = 19,
    FLAG_TABLE = 0x544d60,
    NULL_TABLE = 0x544d44,
    VISIT_TABLE = 0x544a88,
    VISIT_ARGUMENT = 0x50,
    PAIR_FIRST = 0x544ac0,
    PAIR_SECOND = 0x546554,
    PAIR_COUNT = 7,
    ROWS_FIRST = 0x544f90,
    ROW_SIZE = 0x118,
    ROW_COUNT = 19,
    ROW_OBJECTS = 10,
    PAIR_BUILD_COUNT = 8,
    PAIR_BUILD_SIZE = 0x18,
    FLAG_BUILD_SIZE_A = 0x78,
    FLAG_BUILD_SIZE_B = 0x30,
    BUILD_FLAG = 1,
    BUILD_MODE = 4
};

uint32_t vertrix_table_release_one(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services, uint32_t address,
                                   uint32_t edx)
{
    return vertrix_array_list_release(calls, services, address, edx);
}

uint32_t vertrix_table_release_by_flag(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services, uint32_t eax,
                                       uint32_t edx)
{
    return vertrix_array_list_release(calls, services, eax == 0 ? NULL_TABLE : FLAG_TABLE, edx);
}

uint32_t vertrix_table_visit_all(const VertrixCalls *calls, const VertrixFactoryServices *services)
{
    return vertrix_array_list_each(calls, services, VISIT_TABLE, VISIT_ARGUMENT);
}

uint32_t vertrix_table_release_run(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services, uint32_t first,
                                   uint32_t count)
{
    uint32_t result = 0;
    for (uint32_t i = 0; i < count; ++i)
    {
        uint32_t object = first + VERTRIX_LIST_STRIDE * i;
        result = vertrix_array_list_release(calls, services, object, object + VERTRIX_LIST_STRIDE);
    }
    return result;
}

uint32_t vertrix_table_release_rows(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services)
{
    uint32_t result = 0;
    for (uint32_t row = 0; row < ROW_COUNT; ++row)
    {
        result =
            vertrix_table_release_run(calls, services, ROWS_FIRST + ROW_SIZE * row, ROW_OBJECTS);
    }
    return result;
}

uint32_t vertrix_table_release_pair(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services)
{
    vertrix_table_release_run(calls, services, PAIR_FIRST, PAIR_COUNT);
    return vertrix_table_release_run(calls, services, PAIR_SECOND, PAIR_COUNT);
}

uint32_t vertrix_table_fill_slot(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 uint32_t table, uint32_t index, uint32_t source, uint32_t field4,
                                 uint32_t field8, uint32_t pair_ebx, uint32_t pair_ecx,
                                 uint32_t flag)
{
    uint32_t arguments[VERTRIX_SLOT_MAKE_ARGUMENTS] = {pair_ebx, pair_ecx, 0, 0,    field4,
                                                       field8,   0,        0, flag, 4};
    uint32_t slot;
    if (vertrix_array_list_make(calls, services, table, index, field4, field8, arguments) == 0)
    {
        return 0;
    }
    slot = vertrix_call(calls, 0x4877f0, table, index, pair_ebx, pair_ecx, 0);
    vertrix_call(calls, 0x482e10, slot, source, 0, 0, 0);
    return vertrix_call(calls, 0x483ed0, slot, 0x5b9c60, 0, 0, 0);
}

uint32_t vertrix_table_fill_indexed(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services, uint32_t base,
                                    uint32_t row, uint32_t index, uint32_t record, uint32_t field4,
                                    uint32_t field8, uint32_t ecx, uint32_t argument)
{
    return vertrix_table_fill_slot(calls, services, base + INDEXED_STRIDE * row, index, record,
                                   field4, field8, ecx, argument, 1);
}

static const uint32_t RELEASE_FIRST[] = {
    0x5466a4, 0x546618, 0x546634, 0x546688, 0x54666c, 0x546650, 0x546538, 0x54651c,
    0x546500, 0x5449c4, 0x5449e0, 0x5449fc, 0x544a18, 0x544bf4, 0x544d0c, 0x544c64,
    0x544cf0, 0x544cd4, 0x544c9c, 0x544cb8, 0x544c80, 0x544c2c, 0x544c48, 0x544c10};
static const uint32_t RELEASE_SECOND[] = {0x544a6c, 0x544a88, 0x544aa4, 0x544d28,
                                          0x544b84, 0x544ba0, 0x544bbc, 0x544bd8};

uint32_t vertrix_table_release_everything(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services, uint32_t edx)
{
    for (size_t i = 0; i < sizeof RELEASE_FIRST / sizeof RELEASE_FIRST[0]; i++)
    {
        vertrix_array_list_release(calls, services, RELEASE_FIRST[i], edx);
    }
    vertrix_table_release_one(calls, services, SINGLE_FIRST, edx);
    vertrix_table_release_one(calls, services, SINGLE_SECOND, edx);
    for (size_t i = 0; i < sizeof RELEASE_SECOND / sizeof RELEASE_SECOND[0]; i++)
    {
        vertrix_array_list_release(calls, services, RELEASE_SECOND[i], edx);
    }
    vertrix_table_release_run(calls, services, RUN_B_FIRST, RUN_B_COUNT);
    vertrix_table_release_one(calls, services, SINGLE_THIRD, edx);
    return vertrix_table_release_run(calls, services, RUN_A_FIRST, RUN_A_COUNT);
}

uint32_t vertrix_table_build_pair(const VertrixCalls *calls, const VertrixFactoryServices *services)
{
    uint32_t arguments[VERTRIX_SLOT_MAKE_ARGUMENTS] = {
        0, 0, 0, 0, PAIR_BUILD_SIZE, PAIR_BUILD_SIZE, 0, 0, BUILD_FLAG, BUILD_MODE};
    uint32_t result = 0;
    for (uint32_t address = PAIR_FIRST; address != PAIR_FIRST + PAIR_COUNT * INDEXED_STRIDE;
         address += INDEXED_STRIDE)
    {
        result = vertrix_array_list_build(calls, services, address, PAIR_BUILD_COUNT,
                                          PAIR_BUILD_SIZE, PAIR_BUILD_SIZE, arguments);
    }
    return result;
}

uint32_t vertrix_table_build_by_flag(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services, uint32_t eax,
                                     uint32_t edx)
{
    uint32_t arguments[VERTRIX_SLOT_MAKE_ARGUMENTS] = {
        0, 0, 0, 0, FLAG_BUILD_SIZE_A, FLAG_BUILD_SIZE_B, 0, 0, BUILD_FLAG, BUILD_MODE};
    return vertrix_array_list_build(calls, services, eax == 0 ? NULL_TABLE : FLAG_TABLE, edx,
                                    FLAG_BUILD_SIZE_A, FLAG_BUILD_SIZE_B, arguments);
}
