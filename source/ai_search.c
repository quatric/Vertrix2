#include "ai_search.h"

#include "actor_storage.h"
#include "ai_features.h"

enum
{
    DWORD_WIDTH = 4,
    WORD_WIDTH = 2,
    BYTE_WIDTH = 1,
    BOARD_OFFSET = 0x184,
    BOARD_SIZE = VERTRIX_REACH_COLUMNS * VERTRIX_BOARD_ROWS,
    COLUMN_STRIDE = VERTRIX_BOARD_ROWS,
    EMPTY_CELL = 0xff,
    LOCAL_BEST = 0x40,
    LOCAL_KIND = 0x48,
    LOCAL_REACH = 0x38,
    LOCAL_BOARD = 0x8c,
    LOCAL_SCORE = 0x10,
    LOCAL_SCRATCH = 0x190,
    MIN_LEVEL = 2,
    ROTATIONS = 3,
    SCORE = 0x434ee0
};

typedef struct Search
{
    const VertrixFactoryServices *services;
    uint32_t frame;
    int ok;
} Search;

static uint32_t get(Search *s, uint32_t handle, size_t offset, unsigned width)
{
    void *storage;
    size_t size;
    uint32_t value = 0;
    if (!s->services->resolve(handle, &storage, &size, s->services->context) ||
        !vertrix_actor_storage_read(storage, size, offset, width, &value))
    {
        s->ok = 0;
    }
    return value;
}

static void put(Search *s, uint32_t handle, size_t offset, unsigned width, uint32_t value)
{
    void *storage;
    size_t size;
    if (!s->services->resolve(handle, &storage, &size, s->services->context) ||
        !vertrix_actor_storage_write(storage, size, offset, width, value))
    {
        s->ok = 0;
    }
}

static uint32_t local_get(Search *s, uint32_t below, int32_t extra, unsigned width)
{
    return get(s, s->frame - VERTRIX_AI_SEARCH_FRAME_SIZE,
               (size_t)(VERTRIX_AI_SEARCH_FRAME_SIZE - (int32_t)below + extra), width);
}

static void local_put(Search *s, uint32_t below, int32_t extra, unsigned width, uint32_t value)
{
    put(s, s->frame - VERTRIX_AI_SEARCH_FRAME_SIZE,
        (size_t)(VERTRIX_AI_SEARCH_FRAME_SIZE - (int32_t)below + extra), width, value);
}

static void copy_board(Search *s, uint32_t object)
{
    uint32_t i;
    for (i = 0; i < BOARD_SIZE && s->ok; i++)
    {
        local_put(s, LOCAL_BOARD, (int32_t)i, BYTE_WIDTH,
                  get(s, object, BOARD_OFFSET + i, BYTE_WIDTH));
    }
}

int vertrix_ai_search(const VertrixCalls *calls, const VertrixFactoryServices *services,
                      uint32_t frame, const VertrixAiSearch *search, uint32_t *result)
{
    Search state = {services, frame, 1};
    Search *s = &state;
    uint32_t colours[ROTATIONS][ROTATIONS] = {{search->a, search->c, search->b},
                                              {search->b, search->a, search->c},
                                              {search->c, search->b, search->a}};
    uint8_t cells[BOARD_SIZE], reach[VERTRIX_REACH_COLUMNS];
    uint32_t column, rotation, i, failed = 1;
    *result = 0;
    if (search->level <= MIN_LEVEL)
    {
        return 1;
    }
    for (i = 0; i < VERTRIX_REACH_COLUMNS; i++)
    {
        local_put(s, LOCAL_BEST, (int32_t)i, BYTE_WIDTH, 0);
        local_put(s, LOCAL_KIND, (int32_t)i, BYTE_WIDTH, 0);
    }
    copy_board(s, search->object);
    for (i = 0; i < BOARD_SIZE; i++)
    {
        cells[i] = (uint8_t)local_get(s, LOCAL_BOARD, (int32_t)i, BYTE_WIDTH);
    }
    if (!s->ok || !vertrix_ai_row_reach(cells, search->start, search->row, reach))
    {
        return 0;
    }
    for (i = 0; i < VERTRIX_REACH_COLUMNS; i++)
    {
        local_put(s, LOCAL_REACH, (int32_t)i, BYTE_WIDTH, reach[i]);
    }
    for (column = 0; s->ok && column < VERTRIX_REACH_COLUMNS; column++)
    {
        int32_t cell = COLUMN_STRIDE - 1;
        uint32_t base = column * COLUMN_STRIDE;
        if (local_get(s, LOCAL_REACH, (int32_t)column, BYTE_WIDTH) == 0)
        {
            continue;
        }
        copy_board(s, search->object);
        while (cell >= 0 &&
               local_get(s, LOCAL_BOARD, (int32_t)base + cell, BYTE_WIDTH) != EMPTY_CELL)
        {
            cell--;
        }
        if (cell < 0)
        {
            continue;
        }
        for (rotation = 0; s->ok && rotation < ROTATIONS; rotation++)
        {
            VertrixCallSite site = {SCORE, 0, 0, 0, 0, 0, 0, 0, 0, 0, {0}, 0};
            uint32_t word;
            local_put(s, LOCAL_BOARD, (int32_t)base + cell, BYTE_WIDTH, colours[rotation][0]);
            if (cell > 0)
            {
                local_put(s, LOCAL_BOARD, (int32_t)base + cell - 1, BYTE_WIDTH,
                          colours[rotation][1]);
            }
            if (cell > 1)
            {
                local_put(s, LOCAL_BOARD, (int32_t)base + cell - 2, BYTE_WIDTH,
                          colours[rotation][2]);
            }
            local_put(s, LOCAL_SCORE, 0, WORD_WIDTH, 0);
            site.eax = frame - LOCAL_BOARD;
            site.edx = frame - LOCAL_SCRATCH;
            site.ebx = search->pressure & 0xff;
            site.ecx = 0;
            site.stack = frame - LOCAL_SCORE;
            if (calls->call(&site, calls->context) == 1)
            {
                word = site.out_value & 0xffff;
                local_put(s, LOCAL_SCORE, 0, WORD_WIDTH, word);
                failed = 0;
                if (word > local_get(s, LOCAL_BEST, (int32_t)column, BYTE_WIDTH))
                {
                    local_put(s, LOCAL_BEST, (int32_t)column, BYTE_WIDTH, word & 0xff);
                    local_put(s, LOCAL_KIND, (int32_t)column, BYTE_WIDTH, rotation);
                }
            }
            else
            {
                local_put(s, LOCAL_SCORE, 0, WORD_WIDTH, site.out_value & 0xffff);
            }
        }
    }
    if (failed == 0)
    {
        uint32_t best = 0;
        for (i = 1; i < VERTRIX_REACH_COLUMNS; i++)
        {
            if (local_get(s, LOCAL_BEST, (int32_t)i, BYTE_WIDTH) >
                local_get(s, LOCAL_BEST, (int32_t)best, BYTE_WIDTH))
            {
                best = i;
            }
        }
        put(s, search->column_out, 0, DWORD_WIDTH, best);
        put(s, search->kind_out, 0, DWORD_WIDTH,
            local_get(s, LOCAL_KIND, (int32_t)best, BYTE_WIDTH));
        *result = 1;
    }
    return s->ok;
}
