#include "object_events.h"
#include "actor_storage.h"

enum
{
    BYTE_WIDTH = 1,
    WORD_WIDTH = 2,
    DWORD_WIDTH = 4,
    SIDE_SHIFT = 24,
    DRAW_SIDE = 13,
    DRAW_OFFSET = 11,
    OFFSET_BIAS = 5
};

static int get(const void *storage, size_t size, size_t offset, unsigned width, uint32_t *value)
{
    return vertrix_actor_storage_read(storage, size, offset, width, value);
}

static int put(void *storage, size_t size, size_t offset, unsigned width, uint32_t value)
{
    return vertrix_actor_storage_write(storage, size, offset, width, value);
}

static int related(const VertrixFactoryServices *services, const void *storage, size_t size,
                   void **related_storage, size_t *related_size, uint32_t *handle)
{
    return get(storage, size, VERTRIX_EVENT_RELATED, DWORD_WIDTH, handle) &&
           services->resolve(*handle, related_storage, related_size, services->context);
}

uint32_t vertrix_object_flip_side(const VertrixCalls *calls, uint32_t object, void *storage,
                                  size_t size)
{
    uint32_t side;
    uint32_t side_byte;
    uint32_t verdict;
    vertrix_call(calls, 0x4ac370, object, 0, 0, object, 0);
    uint32_t ready = vertrix_call(calls, 0x4ac390, object, 0, 0, object, 0);
    if (ready != 1)
    {
        return ready;
    }
    vertrix_call(calls, 0x4ac3b0, object, 0, 0, object, 0);
    vertrix_call(calls, 0x4ac380, object, 0, 0, object, 0);
    vertrix_call(calls, 0x4ac810, object, 0, 0, object, 0);
    if (!get(storage, size, VERTRIX_EVENT_SIDE, DWORD_WIDTH, &side) ||
        !put(storage, size, VERTRIX_EVENT_SIDE, DWORD_WIDTH, 1 - side))
    {
        return 0;
    }
    uint32_t draw = vertrix_call(calls, 0x4826c0, VERTRIX_EVENT_RNG_STATE, DRAW_SIDE, 0, object, 0);
    if (!put(storage, size, VERTRIX_EVENT_DRAW_BYTE, BYTE_WIDTH, draw & 0xff) ||
        !get(storage, size, VERTRIX_EVENT_SIDE_BYTE, BYTE_WIDTH, &side_byte))
    {
        return 0;
    }
    uint32_t glyph = (uint32_t)(int32_t)(int8_t)((1 - side) & 0xff);
    verdict = vertrix_call(calls, 0x43f420, glyph, side_byte, 0, object, 0);
    vertrix_call(calls, 0x4ac950, object, verdict, 0, object, 0);
    uint32_t offset =
        vertrix_call(calls, 0x4826c0, VERTRIX_EVENT_RNG_STATE, DRAW_OFFSET, 0, object, 0) -
        OFFSET_BIAS;
    if (!put(storage, size, VERTRIX_EVENT_OFFSET_WORD, WORD_WIDTH, offset & 0xffff))
    {
        return 0;
    }
    return offset;
}

uint32_t vertrix_object_start_hold(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services, uint32_t object,
                                   void *storage, size_t size, uint32_t *flag)
{
    void *other;
    size_t other_size;
    uint32_t handle;
    uint32_t done;
    uint32_t state;
    uint32_t own_done;
    if (!related(services, storage, size, &other, &other_size, &handle) ||
        !get(other, other_size, VERTRIX_EVENT_RELATED_DONE, BYTE_WIDTH, &done))
    {
        return 0;
    }
    if (done != 0)
    {
        return 0;
    }
    if (!get(other, other_size, VERTRIX_EVENT_RELATED_STATE, DWORD_WIDTH, &state))
    {
        return 0;
    }
    vertrix_call(calls, 0x4ac8f0, object, VERTRIX_EVENT_HANDLER_4513D0, 0, object, 0);
    if (state == 1)
    {
        vertrix_call(calls, 0x43bb00, object, 0, 0, object, 0);
    }
    else
    {
        if (!get(storage, size, VERTRIX_EVENT_RELATED_DONE, BYTE_WIDTH, &own_done))
        {
            return 0;
        }
        if (own_done != 0)
        {
            if (!put(storage, size, VERTRIX_EVENT_RELATED_STATE, DWORD_WIDTH, 1))
            {
                return 0;
            }
            vertrix_call(calls, 0x43bb00, object, 0, 0, object, 0);
        }
    }
    *flag = 1;
    return 1;
}

uint32_t vertrix_object_arm_hold(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 uint32_t object, void *storage, size_t size)
{
    void *other;
    size_t other_size;
    uint32_t handle;
    uint32_t done;
    uint32_t count;
    if (!get(storage, size, VERTRIX_EVENT_RELATED, DWORD_WIDTH, &handle))
    {
        return 0;
    }
    vertrix_call(calls, 0x4ac8f0, object, VERTRIX_EVENT_HANDLER_450FF0, handle, object, 0);
    uint32_t result = vertrix_call(calls, 0x43bae0, object, 0, handle, object, 0);
    if (!services->resolve(handle, &other, &other_size, services->context) ||
        !get(other, other_size, VERTRIX_EVENT_RELATED_DONE, BYTE_WIDTH, &done))
    {
        return 0;
    }
    if (done == 0)
    {
        return (result & 0xffffff00u) | done;
    }
    if (!get(storage, size, VERTRIX_EVENT_COUNT, DWORD_WIDTH, &count))
    {
        return 0;
    }
    if (count == 0)
    {
        return 0;
    }
    vertrix_call(calls, 0x43bb60, object, 0, handle, object, 0);
    if (!get(storage, size, VERTRIX_EVENT_COUNT, DWORD_WIDTH, &count) ||
        !put(storage, size, VERTRIX_EVENT_SAVED_COUNT, DWORD_WIDTH, count) ||
        !put(storage, size, VERTRIX_EVENT_SAVED_STEP, DWORD_WIDTH, 0))
    {
        return 0;
    }
    vertrix_call(calls, 0x43bae0, object, 4, handle, object, 0);
    return vertrix_call(calls, 0x4ac8f0, object, VERTRIX_EVENT_HANDLER_4522C0, handle, object, 0);
}

uint32_t vertrix_object_enter_attack(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services, uint32_t object,
                                     void *storage, size_t size, VertrixCursorMethod method,
                                     void *context)
{
    void *other;
    size_t other_size;
    void *cursor_storage;
    size_t cursor_size;
    void *opponent_cursor_storage;
    size_t opponent_cursor_size;
    uint32_t handle;
    uint32_t cursor;
    uint32_t table;
    uint32_t done;
    uint32_t opponent_cursor;
    uint32_t state;
    uint32_t step;
    if (!get(storage, size, VERTRIX_EVENT_RELATED, DWORD_WIDTH, &handle) ||
        !get(storage, size, VERTRIX_EVENT_CURSOR, DWORD_WIDTH, &cursor) ||
        !services->resolve(handle, &other, &other_size, services->context) ||
        !get(other, other_size, VERTRIX_EVENT_RELATED_DONE, BYTE_WIDTH, &done) ||
        !get(other, other_size, VERTRIX_EVENT_CURSOR, DWORD_WIDTH, &opponent_cursor) ||
        !services->resolve(cursor, &cursor_storage, &cursor_size, services->context) ||
        !get(cursor_storage, cursor_size, VERTRIX_EVENT_TABLE_SLOT, DWORD_WIDTH, &table))
    {
        return 0;
    }
    if (done == 0)
    {
        method(cursor, table, context);
        return vertrix_call(calls, VERTRIX_EVENT_VIEW_SETUP, object, table, done, cursor, 0);
    }
    if (!get(other, other_size, VERTRIX_EVENT_OPPONENT_STATE, BYTE_WIDTH, &state))
    {
        return 0;
    }
    if (state == 1)
    {
        return method(cursor, table, context);
    }
    if (!get(other, other_size, VERTRIX_EVENT_OPPONENT_STEP, DWORD_WIDTH, &step))
    {
        return 0;
    }
    if (step != 0)
    {
        return method(cursor, table, context);
    }
    vertrix_call(calls, VERTRIX_EVENT_ENTER_452370, handle, object, state, cursor, 0);
    if (!put(storage, size, VERTRIX_EVENT_SAVED_STEP, DWORD_WIDTH, 1) ||
        !services->resolve(opponent_cursor, &opponent_cursor_storage, &opponent_cursor_size,
                           services->context))
    {
        return 0;
    }
    vertrix_call(calls, VERTRIX_EVENT_ENTER_4523D0, object, object, state, cursor, 0);
    if (!put(opponent_cursor_storage, opponent_cursor_size, VERTRIX_EVENT_CURSOR_FLAG0, DWORD_WIDTH,
             1) ||
        !put(opponent_cursor_storage, opponent_cursor_size, VERTRIX_EVENT_CURSOR_FLAG1, DWORD_WIDTH,
             1) ||
        !put(opponent_cursor_storage, opponent_cursor_size, VERTRIX_EVENT_CURSOR_FLAG2, DWORD_WIDTH,
             1))
    {
        return 0;
    }
    return method(cursor, table, context);
}

enum
{
    POST_LOCK_MODE = 0x4c8,
    POST_LOCK_MODE_BONUS = 0x24,
    POST_LOCK_SIDE = 0x4dc,
    POST_LOCK_SUPPRESS = 0x44c,
    POST_LOCK_COUNT = 0x184,
    POST_LOCK_TOTAL = 0x188
};

typedef struct
{
    const VertrixPostLockServices *services;
    void *player;
    size_t player_size;
    uint32_t object;
} PostLockFrame;

static void post_lock_preset(uint32_t player, uint8_t b01, void *context)
{
    PostLockFrame *frame = context;
    const VertrixPostLockServices *post = frame->services;
    vertrix_player_conditional_reset(frame->player, frame->player_size, player, b01, post->random,
                                     post->side_destroy, post->refresh, post->resolve,
                                     post->context);
}

static void post_lock_sfx(PostLockFrame *frame, uint32_t effect)
{
    const VertrixPostLockServices *post = frame->services;
    post->sfx(frame->object, effect, post->context);
    vertrix_sfx_dispatch_event(frame->player, frame->player_size, effect, post->sfx_play,
                               post->context);
}

static void post_lock_effect(uint32_t player, uint32_t effect, void *context)
{
    PostLockFrame *frame = context;
    (void)player;
    post_lock_sfx(frame, effect);
}

static void post_lock_progress(uint32_t player, int32_t delta, void *context)
{
    PostLockFrame *frame = context;
    const VertrixPostLockServices *post = frame->services;
    vertrix_player_progress_update(frame->player, frame->player_size, player, delta, post->progress,
                                   post_lock_preset, post->pletter, post_lock_effect, post->win,
                                   post->refresh, post->resolve, context);
}

static void post_lock_level(uint32_t player, int32_t delta, void *context)
{
    PostLockFrame *frame = context;
    const VertrixPostLockServices *post = frame->services;
    (void)player;
    vertrix_player_bump_level(frame->player, frame->player_size, delta, post->level_notify,
                              post->context);
}

static uint32_t post_lock_run(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              uint32_t object, void *storage, size_t size,
                              const VertrixPostLockServices *post, int twin);

uint32_t vertrix_object_post_lock(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  uint32_t object, void *storage, size_t size,
                                  const VertrixPostLockServices *post)
{
    return post_lock_run(calls, services, object, storage, size, post, 0);
}

uint32_t vertrix_object_post_lock_twin(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services, uint32_t object,
                                       void *storage, size_t size,
                                       const VertrixPostLockServices *post)
{
    return post_lock_run(calls, services, object, storage, size, post, 1);
}

static uint32_t post_lock_run(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              uint32_t object, void *storage, size_t size,
                              const VertrixPostLockServices *post, int twin)
{
    PostLockFrame frame = {post, storage, size, object};
    uint32_t cursor;
    uint32_t side;
    uint32_t flag_a;
    uint32_t flag_b;
    uint32_t reward;
    uint32_t mult;
    uint32_t suppress;
    uint32_t mode;
    uint32_t count;
    uint32_t total;
    void *cursor_storage;
    size_t cursor_size;
    uint32_t table;
    if (!get(storage, size, VERTRIX_EVENT_CURSOR, DWORD_WIDTH, &cursor) ||
        !get(storage, size, POST_LOCK_SIDE, BYTE_WIDTH, &side) ||
        !services->resolve(cursor, &cursor_storage, &cursor_size, services->context) ||
        !get(cursor_storage, cursor_size, VERTRIX_EVENT_TABLE_SLOT, DWORD_WIDTH, &table))
    {
        return 0;
    }
    if (!post->match(cursor, (uint8_t)side, &flag_a, &flag_b, &reward, &mult, post->context))
    {
        if (!get(storage, size, POST_LOCK_SUPPRESS, DWORD_WIDTH, &suppress))
        {
            return 0;
        }
        if (suppress == 1)
        {
            vertrix_object_arm_hold(calls, services, object, storage, size);
            return post->cursor(cursor, table, post->context);
        }
        if (vertrix_player_bonus_ready(storage, size) == 1)
        {
            post->event(object, VERTRIX_EVENT_BONUS_START, post->context);
            vertrix_player_set_b08(storage, size, 2);
            vertrix_player_clear_field_18c(storage, size);
            return post->cursor(cursor, table, post->context);
        }
        post->event(object, VERTRIX_EVENT_HANDLER_450FF0, post->context);
        vertrix_player_set_b08(storage, size, 0);
        return post->cursor(cursor, table, post->context);
    }
    if (!get(storage, size, POST_LOCK_MODE, DWORD_WIDTH, &mode))
    {
        return 0;
    }
    if (mode == POST_LOCK_MODE_BONUS)
    {
        post_lock_sfx(&frame, post->tables.mode_effect);
        vertrix_player_reset_side(storage, size, object, post->random, post->side_destroy,
                                  post->refresh, post->resolve, post->context);
    }
    vertrix_player_match_reward(storage, size, object, (int32_t)reward, post->tables.loop_effect,
                                post_lock_progress, post_lock_level, post_lock_effect,
                                post->refresh, &frame);
    vertrix_player_add_score(storage, size, (int32_t)mult, post->tables.difficulty,
                             post->tables.mult_table, post->tables.mult_count);
    if (!get(storage, size, POST_LOCK_COUNT, DWORD_WIDTH, &count) ||
        !get(storage, size, POST_LOCK_TOTAL, DWORD_WIDTH, &total))
    {
        return 0;
    }
    count += 1;
    total += reward;
    put(storage, size, POST_LOCK_COUNT, DWORD_WIDTH, count);
    put(storage, size, POST_LOCK_TOTAL, DWORD_WIDTH, total);
    if (count == 3 || (!twin && count == 6))
    {
        post_lock_sfx(&frame, post->tables.chain_effect);
    }
    if (twin)
    {
        post_lock_sfx(&frame, flag_a == 0 ? post->tables.alt_effect : post->tables.flag_effect);
    }
    else if (flag_a == 1)
    {
        post_lock_sfx(&frame, post->tables.flag_effect);
    }
    else if (flag_b == 1)
    {
        post_lock_sfx(&frame, post->tables.alt_effect);
    }
    post->event(object, VERTRIX_EVENT_HANDLER_4520F0, post->context);
    return post->cursor(cursor, table, post->context);
}
