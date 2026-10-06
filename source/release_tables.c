#include "release_tables.h"

void vertrix_release_table_a(const uint32_t entries[VERTRIX_RELEASE_TABLE_A_COUNT], uint32_t *state,
                             VertrixRelease release, void *context)
{
    for (int i = 0; i < VERTRIX_RELEASE_TABLE_A_COUNT; ++i)
    {
        if (entries[i] != 0)
        {
            release(entries[i], context);
        }
    }
    *state = 0;
}

void vertrix_release_table_b(const uint32_t entries[VERTRIX_RELEASE_TABLE_B_COUNT],
                             VertrixRelease release, void *context)
{
    for (int i = 0; i < VERTRIX_RELEASE_TABLE_B_COUNT; ++i)
    {
        release(entries[i], context);
    }
}
