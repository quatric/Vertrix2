#include "board_collections.h"
#include "actor_fields.h"

enum
{
    PIECE_CHILDREN = 3,
    PIECE_LIST_0 = 0x15c,
    PIECE_LIST_1 = 0x170,
    ACTOR_HANDLER = 0x154,
    DESTROY_FLAG = 2,
    MARKED = 2,
    EXTRA_FIRST = 421,
    EFFECT_WORD = 0x4c,
    EFFECT_DWORD = 0x88,
    EFFECT_TIME = 10,
    PATTERN_FIELD = 0x48,
    PATTERN_VALUE = 0x64,
    PREPARE_INDEX = 0x44,
    PREPARE_KEPT_INDEX = 0x10,
    PREPARE_HANDLER = 0x44eaf0,
    PREPARE_KIND = 0x15c,
    PREPARE_STONE_KIND = 5,
    PREPARE_FLAG_93 = 0x93,
    PREPARE_POWER = 0x4e,
    PREPARE_STONE_POWER = 0x32,
    PREPARE_FLAG_95 = 0x95
};

typedef struct
{
    int first;
    int count;
} Range;

static int collection_range(VertrixBoardCollection collection, Range *range)
{
    static const Range ranges[] = {{0, 65},   {65, 65},  {130, 5},  {135, 13},
                                   {148, 13}, {421, 65}, {161, 260}};
    if ((int)collection < 0 || (int)collection >= (int)(sizeof ranges / sizeof ranges[0]))
    {
        return 0;
    }
    *range = ranges[collection];
    return 1;
}

int vertrix_board_clear_collection(VertrixScene *scene, VertrixBoardCollection collection,
                                   VertrixBoardDestroy destroy, void *context)
{
    Range range;
    if (!collection_range(collection, &range))
    {
        return 0;
    }
    for (int slot = range.first; slot < range.first + range.count; ++slot)
    {
        if (scene->slots[slot] != 0)
        {
            destroy(scene->slots[slot], DESTROY_FLAG, context);
            scene->slots[slot] = 0;
        }
    }
    return 1;
}

/* Handler-token check over a list of handles: *all reports whether all set entries match. */
static int all_handler(const uint32_t *handles, int count, uint32_t handler,
                       VertrixObjectStorage resolve, void *context, uint32_t *all)
{
    *all = 1;
    for (int i = 0; i < count; ++i)
    {
        void *storage;
        size_t size;
        uint32_t token;
        if (handles[i] == 0)
        {
            continue;
        }
        if (!resolve(handles[i], &storage, &size, context) ||
            !vertrix_actor_storage_read(storage, size, ACTOR_HANDLER, 4, &token))
        {
            return 0;
        }
        if (token != handler)
        {
            *all = 0;
            return 1;
        }
    }
    return 1;
}

static int set_handler(const uint32_t *handles, int count, uint32_t handler,
                       VertrixObjectStorage resolve, void *context)
{
    for (int i = 0; i < count; ++i)
    {
        void *storage;
        size_t size;
        if (handles[i] != 0 && (!resolve(handles[i], &storage, &size, context) ||
                                !vertrix_actor_set_handler(storage, size, handler)))
        {
            return 0;
        }
    }
    return 1;
}

int vertrix_board_collection_all_handler(const VertrixScene *scene,
                                         VertrixBoardCollection collection, uint32_t handler,
                                         VertrixObjectStorage resolve, void *context, uint32_t *all)
{
    Range range;
    return collection_range(collection, &range) &&
           all_handler(&scene->slots[range.first], range.count, handler, resolve, context, all);
}

int vertrix_board_collection_set_handler(const VertrixScene *scene,
                                         VertrixBoardCollection collection, uint32_t handler,
                                         VertrixObjectStorage resolve, void *context)
{
    Range range;
    return collection_range(collection, &range) &&
           set_handler(&scene->slots[range.first], range.count, handler, resolve, context);
}

/* The active piece's child handles, read from the piece's own storage. */
static int piece_children(const VertrixScene *scene, size_t offset, VertrixObjectStorage resolve,
                          void *context, uint32_t children[PIECE_CHILDREN])
{
    void *piece;
    size_t size;
    if (!resolve(scene->active, &piece, &size, context))
    {
        return 0;
    }
    for (int i = 0; i < PIECE_CHILDREN; ++i)
    {
        if (!vertrix_actor_storage_read(piece, size, offset + 4 * i, 4, &children[i]))
        {
            return 0;
        }
    }
    return 1;
}

int vertrix_board_piece_all_handler(const VertrixScene *scene, int list, uint32_t handler,
                                    VertrixObjectStorage resolve, void *context, uint32_t *all)
{
    uint32_t children[PIECE_CHILDREN];
    if (scene->active == 0)
    {
        *all = 1;
        return 1;
    }
    return piece_children(scene, list == 0 ? PIECE_LIST_0 : PIECE_LIST_1, resolve, context,
                          children) &&
           all_handler(children, PIECE_CHILDREN, handler, resolve, context, all);
}

int vertrix_board_piece_set_handler(const VertrixScene *scene, uint32_t handler,
                                    VertrixObjectStorage resolve, void *context)
{
    uint32_t children[PIECE_CHILDREN];
    if (scene->active == 0)
    {
        return 1;
    }
    return piece_children(scene, PIECE_LIST_0, resolve, context, children) &&
           set_handler(children, PIECE_CHILDREN, handler, resolve, context);
}

int vertrix_board_prepare_slots(const VertrixScene *scene, VertrixObjectStorage resolve,
                                void *context)
{
    for (int slot = 0; slot < 65; ++slot)
    {
        void *storage;
        size_t size;
        uint32_t index, kind;
        if (scene->slots[slot] == 0)
        {
            continue;
        }
        if (!resolve(scene->slots[slot], &storage, &size, context) ||
            !vertrix_actor_storage_read(storage, size, PREPARE_INDEX, 1, &index))
        {
            return 0;
        }
        if (index != PREPARE_KEPT_INDEX)
        {
            if (!vertrix_actor_set_handler(storage, size, PREPARE_HANDLER))
            {
                return 0;
            }
            continue;
        }
        if (!vertrix_actor_storage_read(storage, size, PREPARE_KIND, 1, &kind))
        {
            return 0;
        }
        if (kind == PREPARE_STONE_KIND &&
            (!vertrix_actor_storage_write(storage, size, PREPARE_FLAG_93, 1, 0) ||
             !vertrix_actor_storage_write(storage, size, PREPARE_POWER, 1, PREPARE_STONE_POWER) ||
             !vertrix_actor_storage_write(storage, size, PREPARE_FLAG_95, 1, 1)))
        {
            return 0;
        }
    }
    return 1;
}

int vertrix_board_apply_pattern(const VertrixScene *scene, const uint8_t pattern[65],
                                VertrixObjectStorage resolve, void *context)
{
    for (int row = 0; row < 13; ++row)
    {
        for (int column = 0; column < 5; ++column)
        {
            void *storage;
            size_t size;
            uint32_t handle = scene->slots[column * 13 + row];
            if (handle == 0 || pattern[row * 5 + column] != 1)
            {
                continue;
            }
            if (!resolve(handle, &storage, &size, context) ||
                !vertrix_actor_storage_write(storage, size, PATTERN_FIELD, 2, PATTERN_VALUE))
            {
                return 0;
            }
        }
    }
    return 1;
}

void vertrix_board_clear_marked_extra(VertrixScene *scene, const uint8_t markers[65],
                                      VertrixBoardDestroy destroy, void *context)
{
    for (int cell = 0; cell < 65; ++cell)
    {
        if (markers[cell] == MARKED)
        {
            vertrix_board_release_slot(&scene->slots[EXTRA_FIRST + cell], destroy, context);
        }
    }
}

int vertrix_board_destroy_marked(VertrixScene *scene, const uint8_t markers[65],
                                 VertrixBoardDestroy destroy, void *context)
{
    for (int cell = 0; cell < 65; ++cell)
    {
        if (markers[cell] == MARKED)
        {
            vertrix_board_release_slot(&scene->slots[cell], destroy, context);
            vertrix_board_release_slot(&scene->slots[EXTRA_FIRST + cell], destroy, context);
        }
    }
    return 1;
}

int vertrix_board_assign_effect(const VertrixScene *scene, uint8_t mode,
                                VertrixObjectStorage resolve, void *context)
{
    static const uint32_t handlers[] = {0x44f1e0, 0x44f320, 0x44f430, 0x44f560, 0x44f690};
    for (int row = 0; row < 13; ++row)
    {
        for (int column = 0; column < 5; ++column)
        {
            void *storage;
            size_t size;
            uint32_t handle = scene->slots[column * 13 + row];
            if (handle == 0 || mode > 4)
            {
                continue;
            }
            if (!resolve(handle, &storage, &size, context) ||
                !vertrix_actor_set_handler(storage, size, handlers[mode]))
            {
                return 0;
            }
            if (mode <= 1 &&
                !vertrix_actor_storage_write(storage, size, EFFECT_WORD, 2, EFFECT_TIME))
            {
                return 0;
            }
            if (mode == 2 &&
                !vertrix_actor_storage_write(storage, size, EFFECT_DWORD, 4, EFFECT_TIME))
            {
                return 0;
            }
        }
    }
    return 1;
}
