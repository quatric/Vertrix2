#include "player_slots.h"
#include "actor_fields.h"
#include "actor_storage.h"
#include "object_access.h"
#include "object_scalars.h"
#include "piece.h"
#include "piece_actor_construct.h"
#include "piece_children.h"
#include "timing.h"

enum
{
    DWORD_WIDTH = 4,
    WORD_WIDTH = 2,
    LEVEL_SIDE_CHILD = 0xa60,
    LEVEL_SIDE_SLOT = 0x168,
    LEVEL_SIDE_FRAME = 0x1a,
    LEVEL_SIDE_DELAY_STRIDE = 10,
    LEVEL_SIDE_FRAME_STRIDE = 20,
    MODE_FIELD = 0x4c8,
    B00_FIELD = 0x4c4,
    PREVIEW_PIECE = 0x3b4,
    KIND_FIELD = 0x488,
    KIND_COUNT = 19,
    DIFFICULTY_COUNT = 3,
    INTERNAL_LEVEL = 0x17c,
    DELAY_0 = 0x458,
    DELAY_1 = 0x45c,
    DELAY_2 = 0x460,
    SIDE_OBJECT = 0x4e8,
    SIDE_SIZE = 0x15c,
    PIECE_TARGET = 0x450,
    RESET_STATE_DWORD = 0x470,
    PROGRESS_FLAG = 0x464,
    WIN_STATE = 0x474,
    CHAIN_FIELD = 0x180,
    SUPPRESS_FIELD = 0x44c,
    LOOP_FLAG = 0x3ac,
    SCORE_FIELD = 0x174,
    SCORE_CAP = 0x5f5e0ff,
    BONUS_KIND_DWORD = 0x18d,
    BONUS_HANDLER = 0x451aa0,
    SETUP_MODE = 0x30,
    SETUP_STATE = 4,
    CLEAR_FIELD = 0x18c,
    ADOPT_VALUE = 0x4e4,
    ADOPT_OFFSET = 0x3f4,
    MODE_BASE = 0x25,
    STATE_B08 = 0x4cc,
    STATE_B14 = 0x4cd,
    B01_FIELD = 0x4c5,
    OPPONENT_FIELD = 0x3b0,
    INDEX_FIELD = 0x3fc,
    INDEX_MODE_BASE = 0x32,
    BYTE_3_FIELD = 0x4dc,
    BYTE_3_VALUE = 3,
    INDEX_STATE = 1,
    GROUP_A_FIRST = 0x25,
    GROUP_A_LAST = 0x27,
    GROUP_B_FIRST = 0x32,
    GROUP_B_LAST = 0x34,
    CURSOR_CHILD = 0x15c,
    LEVEL_FIELD = 0x178,
    LEVEL_STORE = 0x17c,
    SIDE_FIELD = 0x190,
    FIRST_FIELD = 0,
    OPPONENT = 0x3b0,
    SIDE_TARGET = 0x450,
    CHILD_X = 0xe,
    CHILD_Y = 0x16,
    CHILD_FIRST_DWORD = 4,
    CHILD_BACK_LINK = 0xce8,
    LEFT_X = 186,
    LEFT_Y = 130,
    RIGHT_X = 334,
    RIGHT_Y = 130,
    LEVEL_LIMIT = 9,
    DRAW_RANGE = 2
};

static int mode_in_range(const void *player, size_t size, uint32_t first, uint32_t last)
{
    uint32_t mode;
    if (!vertrix_actor_storage_read(player, size, MODE_FIELD, 4, &mode))
    {
        return -1;
    }
    return mode >= first && mode <= last;
}

int vertrix_player_mode_in_group_a(const void *player, size_t size)
{
    return mode_in_range(player, size, GROUP_A_FIRST, GROUP_A_LAST);
}

int vertrix_player_mode_in_group_b(const void *player, size_t size)
{
    return mode_in_range(player, size, GROUP_B_FIRST, GROUP_B_LAST);
}

int vertrix_player_set_side(void *player, size_t size, uint32_t handle, uint8_t side,
                            VertrixObjectStorage resolve, void *context)
{
    uint32_t cursor;
    uint32_t first;
    uint32_t target;
    if (!vertrix_actor_storage_write(player, size, SIDE_FIELD, 1, side) ||
        !vertrix_actor_storage_read(player, size, CURSOR_CHILD, 4, &cursor) ||
        !vertrix_actor_storage_read(player, size, FIRST_FIELD, 4, &first) ||
        !vertrix_actor_storage_read(player, size, SIDE_TARGET, 4, &target))
    {
        return 0;
    }
    if (!vertrix_object_write(cursor, resolve, context, CHILD_X, 2, side == 0 ? LEFT_X : RIGHT_X) ||
        !vertrix_object_write(cursor, resolve, context, CHILD_Y, 2, side == 0 ? LEFT_Y : RIGHT_Y) ||
        !vertrix_object_write(cursor, resolve, context, CHILD_FIRST_DWORD, 4, first) ||
        !vertrix_object_write(cursor, resolve, context, CHILD_BACK_LINK, 4, handle) ||
        !vertrix_object_write(target, resolve, context, LEVEL_STORE, 1, side))
    {
        return 0;
    }
    return 1;
}

int vertrix_player_set_level(void *player, size_t size, int32_t level, VertrixLevelNotify notify,
                             void *context)
{
    uint32_t previous;
    uint32_t cursor;
    uint32_t stored = level < 0 ? 0 : (level >= LEVEL_LIMIT + 1 ? LEVEL_LIMIT : (uint32_t)level);
    if (!vertrix_actor_storage_read(player, size, LEVEL_STORE, 4, &previous) ||
        !vertrix_actor_storage_read(player, size, CURSOR_CHILD, 4, &cursor) ||
        !vertrix_actor_storage_write(player, size, LEVEL_STORE, 4, stored))
    {
        return -1;
    }
    if (previous == stored)
    {
        return 0;
    }
    notify(cursor, stored, context);
    return 1;
}

uint32_t vertrix_player_level_side(VertrixObjectStorage resolve, void *context, uint32_t holder,
                                   void *storage, size_t size, uint32_t level, uint32_t alter,
                                   const uint32_t *delay_table, const uint16_t *frame_table)
{
    uint32_t child;
    uint32_t slot;
    void *child_storage;
    size_t child_size;
    if (!vertrix_actor_storage_read(storage, size, LEVEL_SIDE_CHILD, DWORD_WIDTH, &child))
    {
        return 0;
    }
    if (child == 0)
    {
        return holder;
    }
    if (!resolve(child, &child_storage, &child_size, context) ||
        !vertrix_actor_storage_read(child_storage, child_size, LEVEL_SIDE_SLOT, DWORD_WIDTH, &slot))
    {
        return 0;
    }
    if (slot != 0)
    {
        return holder;
    }
    if (!vertrix_actor_set_period(child_storage, child_size,
                                  delay_table[level + alter * LEVEL_SIDE_DELAY_STRIDE]) ||
        !vertrix_actor_storage_write(child_storage, child_size, LEVEL_SIDE_FRAME, WORD_WIDTH,
                                     frame_table[level * 2 + alter * LEVEL_SIDE_FRAME_STRIDE]) ||
        !vertrix_actor_clear_counter(child_storage, child_size))
    {
        return 0;
    }
    return child;
}

int vertrix_player_first_turn(const void *player, size_t size, VertrixTurnGlobals *globals,
                              VertrixObjectStorage resolve, VertrixTurnDraw draw, void *context)
{
    uint32_t own;
    uint32_t opponent;
    uint32_t other;
    int decide = 0;
    if (!vertrix_actor_storage_read(player, size, LEVEL_FIELD, 4, &own))
    {
        return -1;
    }
    if (globals->mode_flag == 1)
    {
        globals->candidate = globals->last_index - 1;
        globals->level = own;
        decide = globals->candidate == globals->level;
    }
    if (!decide)
    {
        if (!vertrix_actor_storage_read(player, size, OPPONENT, 4, &opponent) ||
            !vertrix_object_read(opponent, resolve, context, LEVEL_FIELD, 4, &other))
        {
            return -1;
        }
        globals->candidate = own + 1;
        globals->level = other;
        decide = (int32_t)other > (int32_t)globals->candidate;
    }
    if (!decide)
    {
        return 1;
    }
    globals->draw = draw(DRAW_RANGE, context);
    globals->drawn = 1;
    return globals->draw == 1;
}

int vertrix_player_set_mode_and_refresh(void *player, size_t size, uint32_t handle, uint32_t mode,
                                        VertrixRefreshNotify notify, void *context)
{
    if (!vertrix_actor_storage_write(player, size, MODE_FIELD, 4, mode))
    {
        return 0;
    }
    notify(handle, context);
    return 1;
}

int vertrix_player_set_b00_and_refresh(void *player, size_t size, uint32_t handle, uint8_t value,
                                       VertrixRefreshNotify notify, void *context)
{
    if (!vertrix_actor_storage_write(player, size, B00_FIELD, 1, value))
    {
        return 0;
    }
    notify(handle, context);
    return 1;
}

int vertrix_player_generate_preview(const void *player, size_t size, VertrixRandom *random,
                                    VertrixObjectStorage resolve, void *context)
{
    uint32_t mode;
    uint32_t preview;
    void *storage;
    size_t storage_size;
    uint8_t blocks[3];
    if (!random || !vertrix_actor_storage_read(player, size, MODE_FIELD, 4, &mode) ||
        !vertrix_actor_storage_read(player, size, PREVIEW_PIECE, 4, &preview) ||
        !resolve(preview, &storage, &storage_size, context))
    {
        return 0;
    }
    vertrix_piece(random, mode, blocks);
    return vertrix_piece_store_preview_kinds(storage, storage_size, blocks[0], blocks[1],
                                             blocks[2]);
}

/* Shared core of 0x43b5b0 (parameter 0) and 0x43b6a0 (parameters 1 and 2):
 * table lookup plus RNG range draw, stored at the given field. */
static int draw_delay(void *player, size_t size, VertrixRandom *random, uint32_t difficulty,
                      int parameter, size_t field)
{
    uint32_t kind;
    uint32_t level;
    VertrixDelay delay;
    if (!random || !vertrix_actor_storage_read(player, size, KIND_FIELD, 4, &kind) ||
        !vertrix_actor_storage_read(player, size, INTERNAL_LEVEL, 4, &level) ||
        kind >= KIND_COUNT || difficulty >= DIFFICULTY_COUNT)
    {
        return 0;
    }
    delay = vertrix_delay((int)kind, (int)difficulty, level, parameter);
    return vertrix_actor_storage_write(player, size, field, 4,
                                       vertrix_random_range(random, delay.minimum, delay.width));
}

int vertrix_player_draw_delay_0(void *player, size_t size, VertrixRandom *random,
                                uint32_t difficulty)
{
    return draw_delay(player, size, random, difficulty, 0, DELAY_0);
}

int vertrix_player_draw_delay_1(void *player, size_t size, VertrixRandom *random,
                                uint32_t difficulty)
{
    return draw_delay(player, size, random, difficulty, 1, DELAY_1);
}

int vertrix_player_draw_delay_2(void *player, size_t size, VertrixRandom *random,
                                uint32_t difficulty)
{
    return draw_delay(player, size, random, difficulty, 2, DELAY_2);
}

int vertrix_player_draw_all_delays(void *player, size_t size, VertrixRandom *random,
                                   uint32_t difficulty)
{
    return vertrix_player_draw_delay_0(player, size, random, difficulty) &&
           vertrix_player_draw_delay_1(player, size, random, difficulty) &&
           vertrix_player_draw_delay_2(player, size, random, difficulty);
}

int vertrix_player_release_side(void *player, size_t size, uint32_t handle, VertrixRandom *random,
                                VertrixSideDestroy destroy, VertrixRefreshNotify notify,
                                VertrixObjectStorage resolve, void *context)
{
    uint32_t side;
    if (!vertrix_actor_storage_read(player, size, SIDE_OBJECT, 4, &side))
    {
        return 0;
    }
    if (side == 0)
    {
        return 1;
    }
    destroy(side, context);
    if (!vertrix_actor_storage_write(player, size, SIDE_OBJECT, 4, 0))
    {
        return 0;
    }
    return vertrix_player_reset_side(player, size, handle, random, destroy, notify, resolve,
                                     context);
}

int vertrix_player_reset_side(void *player, size_t size, uint32_t handle, VertrixRandom *random,
                              VertrixSideDestroy destroy, VertrixRefreshNotify notify,
                              VertrixObjectStorage resolve, void *context)
{
    if (!vertrix_player_release_side(player, size, handle, random, destroy, notify, resolve,
                                     context) ||
        !vertrix_player_set_mode_and_refresh(player, size, handle, 0, notify, context) ||
        !vertrix_player_enter_state(player, size) ||
        !vertrix_player_generate_preview(player, size, random, resolve, context))
    {
        return 0;
    }
    return 1;
}

int vertrix_player_alloc_side(void *player, size_t size, uint32_t handle, uint32_t steps,
                              VertrixRandom *random, VertrixSideAllocate allocate,
                              VertrixSideDestroy destroy, VertrixRefreshNotify notify,
                              VertrixObjectStorage resolve, void *context)
{
    uint32_t side;
    void *storage;
    size_t storage_size;
    if (!vertrix_player_release_side(player, size, handle, random, destroy, notify, resolve,
                                     context))
    {
        return 0;
    }
    side = allocate(SIDE_SIZE, context);
    if (side == 0)
    {
        return 0;
    }
    if (!resolve(side, &storage, &storage_size, context) ||
        !vertrix_actor_storage_construct(storage, storage_size) ||
        !vertrix_actor_storage_write(player, size, SIDE_OBJECT, 4, side) ||
        !vertrix_actor_set_period_steps(storage, storage_size, steps))
    {
        return 0;
    }
    return 1;
}

int vertrix_player_setup_side(void *player, size_t size, uint32_t handle, uint32_t steps,
                              VertrixRandom *random, VertrixSideAllocate allocate,
                              VertrixSideDestroy destroy, VertrixRefreshNotify notify,
                              VertrixObjectStorage resolve, void *context)
{
    if (!vertrix_player_alloc_side(player, size, handle, steps, random, allocate, destroy, notify,
                                   resolve, context) ||
        !vertrix_player_enter_state(player, size) ||
        !vertrix_player_set_mode_and_refresh(player, size, handle, SETUP_MODE, notify, context) ||
        !vertrix_actor_storage_write(player, size, RESET_STATE_DWORD, 4, SETUP_STATE))
    {
        return 0;
    }
    return 1;
}

int vertrix_player_clear_field_18c(void *player, size_t size)
{
    return vertrix_actor_storage_write(player, size, CLEAR_FIELD, 4, 0);
}

int vertrix_player_bonus_ready(const void *player, size_t size)
{
    uint32_t meter;
    if (!vertrix_actor_storage_read(player, size, CLEAR_FIELD, 4, &meter))
    {
        return -1;
    }
    return meter == 3;
}

int vertrix_player_reset_piece_progress(const void *player, size_t size,
                                        VertrixObjectStorage resolve, void *context)
{
    uint32_t piece;
    void *storage;
    size_t storage_size;
    if (!vertrix_actor_storage_read(player, size, PIECE_TARGET, 4, &piece) ||
        !resolve(piece, &storage, &storage_size, context))
    {
        return 0;
    }
    return vertrix_actor_storage_write(storage, storage_size, LEVEL_FIELD, 4, 1);
}

int vertrix_player_progress_update(void *player, size_t size, uint32_t handle, int32_t delta,
                                   VertrixProgressGlobals *globals, VertrixProgressReset reset,
                                   VertrixProgressLetter letter, VertrixProgressEffect effect,
                                   VertrixProgressWin win, VertrixRefreshNotify notify,
                                   VertrixObjectStorage resolve, void *context)
{
    uint32_t previous;
    int32_t updated;
    uint32_t opponent;
    uint32_t alive;
    uint32_t first;
    uint32_t refresh_arg;
    if (!vertrix_actor_storage_read(player, size, LEVEL_FIELD, 4, &previous))
    {
        return -1;
    }
    updated = (int32_t)previous + delta;
    if (updated < 0)
    {
        updated = 0;
    }
    else if (globals->mode_flag == 1 && (uint32_t)updated >= globals->race_limit)
    {
        if (!vertrix_actor_storage_write(player, size, PROGRESS_FLAG, 4, globals->mode_flag) ||
            !vertrix_actor_storage_read(player, size, OPPONENT_FIELD, 4, &opponent) ||
            !vertrix_object_read(opponent, resolve, context, B01_FIELD, 1, &alive))
        {
            return -1;
        }
        updated = (int32_t)globals->race_limit;
        if (alive == 0)
        {
            globals->loser_flag = globals->mode_flag;
            refresh_arg = opponent;
            goto store;
        }
        reset(handle, 0, context);
        if (!vertrix_actor_storage_read(player, size, FIRST_FIELD, 4, &first))
        {
            return -1;
        }
        letter(first, context);
        effect(handle, globals->effect, context);
        if (!vertrix_actor_storage_write(player, size, WIN_STATE, 4, 1))
        {
            return -1;
        }
        refresh_arg = win(handle, globals->race_limit, handle, context);
        goto store;
    }
    refresh_arg = handle;
store:
    if (!vertrix_actor_storage_write(player, size, LEVEL_FIELD, 4, (uint32_t)updated))
    {
        return -1;
    }
    if ((uint32_t)updated == previous)
    {
        return 0;
    }
    notify(refresh_arg, context);
    return 1;
}

int vertrix_player_set_b08(void *player, size_t size, uint8_t value)
{
    return vertrix_actor_storage_write(player, size, STATE_B08, 1, value);
}

int vertrix_player_set_b14(void *player, size_t size, uint8_t value)
{
    return vertrix_actor_storage_write(player, size, STATE_B14, 1, value);
}

int vertrix_player_conditional_reset(void *player, size_t size, uint32_t handle, uint8_t b01,
                                     VertrixRandom *random, VertrixSideDestroy destroy,
                                     VertrixRefreshNotify notify, VertrixObjectStorage resolve,
                                     void *context)
{
    int group;
    uint32_t opponent;
    void *opponent_storage;
    size_t opponent_size;
    if (!vertrix_actor_storage_write(player, size, B01_FIELD, 1, b01))
    {
        return 0;
    }
    if (b01 != 0)
    {
        notify(handle, context);
        return 1;
    }
    group = mode_in_range(player, size, GROUP_A_FIRST, GROUP_A_LAST);
    if (group < 0)
    {
        return 0;
    }
    if (group && (!vertrix_actor_storage_read(player, size, OPPONENT_FIELD, 4, &opponent) ||
                  !resolve(opponent, &opponent_storage, &opponent_size, context) ||
                  !vertrix_player_reset_side(opponent_storage, opponent_size, opponent, random,
                                             destroy, notify, resolve, context)))
    {
        return 0;
    }
    if (!vertrix_player_release_side(player, size, handle, random, destroy, notify, resolve,
                                     context) ||
        !vertrix_player_reset_side(player, size, handle, random, destroy, notify, resolve, context))
    {
        return 0;
    }
    /* As in the gated reset, the trailing refresh observes the reset's return. */
    notify(1, context);
    return 1;
}

int vertrix_player_gated_reset(void *player, size_t size, uint32_t handle, VertrixRandom *random,
                               VertrixSideDestroy destroy, VertrixRefreshNotify notify,
                               VertrixObjectStorage resolve, void *context)
{
    int group;
    group = vertrix_player_mode_in_group_a(player, size);
    if (group < 0)
    {
        return 0;
    }
    if (!group)
    {
        return 0;
    }
    if (!vertrix_player_reset_side(player, size, handle, random, destroy, notify, resolve, context))
    {
        return 0;
    }
    /* The original trails the refresh directly after the reset call, so the
     * refresh observes the reset's return value (1) rather than the player. */
    notify(1, context);
    return 1;
}

static int setup_with_mode(void *player, size_t size, uint32_t handle, uint32_t steps,
                           uint32_t mode, VertrixRandom *random, VertrixSideAllocate allocate,
                           VertrixSideDestroy destroy, VertrixRefreshNotify notify,
                           VertrixObjectStorage resolve, void *context)
{
    if (!vertrix_player_alloc_side(player, size, handle, steps, random, allocate, destroy, notify,
                                   resolve, context) ||
        !vertrix_player_set_mode_and_refresh(player, size, handle, mode, notify, context) ||
        !vertrix_player_enter_state(player, size))
    {
        return 0;
    }
    return 1;
}

int vertrix_player_setup_side_2b(void *player, size_t size, uint32_t handle, uint32_t steps,
                                 VertrixRandom *random, VertrixSideAllocate allocate,
                                 VertrixSideDestroy destroy, VertrixRefreshNotify notify,
                                 VertrixObjectStorage resolve, void *context)
{
    return setup_with_mode(player, size, handle, steps, 0x2b, random, allocate, destroy, notify,
                           resolve, context);
}

int vertrix_player_setup_side_2c(void *player, size_t size, uint32_t handle, uint32_t steps,
                                 VertrixRandom *random, VertrixSideAllocate allocate,
                                 VertrixSideDestroy destroy, VertrixRefreshNotify notify,
                                 VertrixObjectStorage resolve, void *context)
{
    return setup_with_mode(player, size, handle, steps, 0x2c, random, allocate, destroy, notify,
                           resolve, context);
}

int vertrix_player_adopt_side(void *player, size_t size, uint32_t handle, uint32_t value,
                              VertrixRandom *random, VertrixSideDestroy destroy,
                              VertrixRefreshNotify notify, VertrixObjectStorage resolve,
                              void *context)
{
    if (!vertrix_player_release_side(player, size, handle, random, destroy, notify, resolve,
                                     context) ||
        !vertrix_actor_storage_write(player, size, ADOPT_VALUE, 4, value) ||
        !vertrix_player_set_mode_and_refresh(player, size, handle, value + MODE_BASE, notify,
                                             context) ||
        !vertrix_player_enter_state(player, size) ||
        !vertrix_player_clear_field_18c(player, size) ||
        !vertrix_actor_storage_write(player, size, ADOPT_OFFSET, 4, 0))
    {
        return 0;
    }
    notify(handle, context);
    return 1;
}

/* Shared allocate + mode + mark shape behind the mode-setup family. */
static int setup_alloc_marked(void *player, size_t size, uint32_t handle, uint32_t steps,
                              uint32_t mode, VertrixRandom *random, VertrixSideAllocate allocate,
                              VertrixSideDestroy destroy, VertrixRefreshNotify notify,
                              VertrixObjectStorage resolve, void *context)
{
    if (!vertrix_player_alloc_side(player, size, handle, steps, random, allocate, destroy, notify,
                                   resolve, context) ||
        !vertrix_player_set_mode_and_refresh(player, size, handle, mode, notify, context) ||
        !vertrix_player_enter_state(player, size))
    {
        return 0;
    }
    return 1;
}

static int setup_alloc_preview(void *player, size_t size, uint32_t handle, uint32_t steps,
                               uint32_t mode, VertrixRandom *random, VertrixSideAllocate allocate,
                               VertrixSideDestroy destroy, VertrixRefreshNotify notify,
                               VertrixObjectStorage resolve, void *context)
{
    if (!setup_alloc_marked(player, size, handle, steps, mode, random, allocate, destroy, notify,
                            resolve, context) ||
        !vertrix_player_generate_preview(player, size, random, resolve, context))
    {
        return 0;
    }
    return 1;
}

int vertrix_player_setup_side_22(void *player, size_t size, uint32_t handle, uint32_t steps,
                                 VertrixRandom *random, VertrixSideAllocate allocate,
                                 VertrixSideDestroy destroy, VertrixRefreshNotify notify,
                                 VertrixObjectStorage resolve, void *context)
{
    return setup_alloc_preview(player, size, handle, steps, 0x22, random, allocate, destroy, notify,
                               resolve, context);
}

int vertrix_player_setup_side_23(void *player, size_t size, uint32_t handle, uint32_t steps,
                                 VertrixRandom *random, VertrixSideAllocate allocate,
                                 VertrixSideDestroy destroy, VertrixRefreshNotify notify,
                                 VertrixObjectStorage resolve, void *context)
{
    return setup_alloc_preview(player, size, handle, steps, 0x23, random, allocate, destroy, notify,
                               resolve, context);
}

int vertrix_player_setup_side_24(void *player, size_t size, uint32_t handle, uint32_t steps,
                                 VertrixRandom *random, VertrixSideAllocate allocate,
                                 VertrixSideDestroy destroy, VertrixRefreshNotify notify,
                                 VertrixObjectStorage resolve, void *context)
{
    if (!setup_alloc_marked(player, size, handle, steps, 0x24, random, allocate, destroy, notify,
                            resolve, context) ||
        !vertrix_actor_storage_write(player, size, BYTE_3_FIELD, 1, BYTE_3_VALUE))
    {
        return 0;
    }
    return 1;
}

int vertrix_player_setup_side_28(void *player, size_t size, uint32_t handle, uint32_t steps,
                                 VertrixRandom *random, VertrixSideAllocate allocate,
                                 VertrixSideDestroy destroy, VertrixRefreshNotify notify,
                                 VertrixObjectStorage resolve, void *context)
{
    return setup_alloc_preview(player, size, handle, steps, 0x28, random, allocate, destroy, notify,
                               resolve, context);
}

int vertrix_player_setup_side_29(void *player, size_t size, uint32_t handle, uint32_t steps,
                                 VertrixRandom *random, VertrixSideAllocate allocate,
                                 VertrixSideDestroy destroy, VertrixRefreshNotify notify,
                                 VertrixObjectStorage resolve, void *context)
{
    return setup_alloc_preview(player, size, handle, steps, 0x29, random, allocate, destroy, notify,
                               resolve, context);
}

int vertrix_player_setup_side_2a(void *player, size_t size, uint32_t handle, uint32_t steps,
                                 VertrixRandom *random, VertrixSideAllocate allocate,
                                 VertrixSideDestroy destroy, VertrixRefreshNotify notify,
                                 VertrixObjectStorage resolve, void *context)
{
    return setup_alloc_preview(player, size, handle, steps, 0x2a, random, allocate, destroy, notify,
                               resolve, context);
}

int vertrix_player_setup_side_2d(void *player, size_t size, uint32_t handle, uint32_t steps,
                                 VertrixRandom *random, VertrixSideAllocate allocate,
                                 VertrixSideDestroy destroy, VertrixRefreshNotify notify,
                                 VertrixObjectStorage resolve, void *context)
{
    return setup_alloc_preview(player, size, handle, steps, 0x2d, random, allocate, destroy, notify,
                               resolve, context);
}

int vertrix_player_setup_side_2e(void *player, size_t size, uint32_t handle, uint32_t steps,
                                 VertrixRandom *random, VertrixSideAllocate allocate,
                                 VertrixSideDestroy destroy, VertrixRefreshNotify notify,
                                 VertrixObjectStorage resolve, void *context)
{
    return setup_alloc_preview(player, size, handle, steps, 0x2e, random, allocate, destroy, notify,
                               resolve, context);
}

int vertrix_player_setup_side_2f(void *player, size_t size, uint32_t handle, uint32_t steps,
                                 VertrixRandom *random, VertrixSideAllocate allocate,
                                 VertrixSideDestroy destroy, VertrixRefreshNotify notify,
                                 VertrixObjectStorage resolve, void *context)
{
    if (!vertrix_player_alloc_side(player, size, handle, steps, random, allocate, destroy, notify,
                                   resolve, context) ||
        !vertrix_player_enter_state(player, size) ||
        !vertrix_player_set_mode_and_refresh(player, size, handle, 0x2f, notify, context) ||
        !vertrix_actor_storage_write(player, size, RESET_STATE_DWORD, 4, INDEX_STATE))
    {
        return 0;
    }
    return 1;
}

int vertrix_player_setup_side_31(void *player, size_t size, uint32_t handle, uint32_t steps,
                                 VertrixRandom *random, VertrixSideAllocate allocate,
                                 VertrixSideDestroy destroy, VertrixRefreshNotify notify,
                                 VertrixObjectStorage resolve, void *context)
{
    return vertrix_player_alloc_side(player, size, handle, steps, random, allocate, destroy, notify,
                                     resolve, context) &&
           vertrix_player_enter_state(player, size) &&
           vertrix_player_set_mode_and_refresh(player, size, handle, 0x31, notify, context);
}

int vertrix_player_setup_indexed(void *player, size_t size, uint32_t handle, uint32_t steps,
                                 VertrixRandom *random, VertrixSideAllocate allocate,
                                 VertrixSideDestroy destroy, VertrixRefreshNotify notify,
                                 VertrixObjectStorage resolve, void *context)
{
    uint32_t index;
    if (!vertrix_actor_storage_read(player, size, INDEX_FIELD, 4, &index) ||
        !vertrix_player_alloc_side(player, size, handle, steps, random, allocate, destroy, notify,
                                   resolve, context) ||
        !vertrix_player_enter_state(player, size) ||
        !vertrix_player_set_mode_and_refresh(player, size, handle, index + INDEX_MODE_BASE, notify,
                                             context))
    {
        return 0;
    }
    return 1;
}

int vertrix_player_init_piece_and_delays(void *player, size_t size, VertrixRandom *random,
                                         uint32_t difficulty, VertrixObjectStorage resolve,
                                         void *context)
{
    uint32_t kind;
    uint32_t piece;
    void *storage;
    size_t storage_size;
    uint32_t byte;
    if (!vertrix_actor_storage_read(player, size, KIND_FIELD, 1, &byte) ||
        !vertrix_actor_storage_read(player, size, PIECE_TARGET, 4, &piece) ||
        !resolve(piece, &storage, &storage_size, context))
    {
        return 0;
    }
    kind = byte;
    if (kind >= KIND_COUNT)
    {
        return 0;
    }
    if (!vertrix_piece_init_from_kind(storage, storage_size, (uint8_t)kind))
    {
        return 0;
    }
    return vertrix_player_draw_all_delays(player, size, random, difficulty);
}

int vertrix_player_match_reward(void *player, size_t size, uint32_t handle, int32_t reward,
                                uint32_t loop_effect, VertrixRewardProgress progress,
                                VertrixRewardLevel level, VertrixRewardEffect effect,
                                VertrixRefreshNotify refresh, void *context)
{
    uint32_t chain_raw;
    int32_t chain;
    uint32_t suppress;
    uint32_t meter;
    if (!vertrix_actor_storage_read(player, size, CHAIN_FIELD, 4, &chain_raw))
    {
        return 0;
    }
    chain = (int32_t)chain_raw - reward;
    while (chain < 1)
    {
        progress(handle, 1, context);
        level(handle, 1, context);
        chain += 0x0c;
        effect(handle, loop_effect, context);
        refresh(handle, context);
        if (!vertrix_actor_storage_write(player, size, LOOP_FLAG, 4, 1))
        {
            return 0;
        }
    }
    if (!vertrix_actor_storage_read(player, size, SUPPRESS_FIELD, 4, &suppress) ||
        !vertrix_actor_storage_write(player, size, CHAIN_FIELD, 4, (uint32_t)chain))
    {
        return 0;
    }
    if (suppress == 1)
    {
        return vertrix_actor_storage_write(player, size, CLEAR_FIELD, 4, 0);
    }
    if (!vertrix_actor_storage_read(player, size, CLEAR_FIELD, 4, &meter))
    {
        return 0;
    }
    meter += (uint32_t)reward;
    if (meter > 3)
    {
        meter = 3;
    }
    return vertrix_actor_storage_write(player, size, CLEAR_FIELD, 4, meter);
}

int vertrix_player_add_score(void *player, size_t size, int32_t reward, uint32_t difficulty,
                             const uint32_t *table, size_t count)
{
    uint32_t score;
    uint32_t scaled;
    if (table == NULL || difficulty >= count ||
        !vertrix_actor_storage_read(player, size, SCORE_FIELD, 4, &score))
    {
        return 0;
    }
    scaled = (uint32_t)reward * table[difficulty];
    score += scaled;
    if (score > SCORE_CAP)
    {
        score = SCORE_CAP;
    }
    return vertrix_actor_storage_write(player, size, SCORE_FIELD, 4, score);
}

int vertrix_player_bump_level(void *player, size_t size, int32_t delta, VertrixLevelNotify notify,
                              void *context)
{
    uint32_t level;
    if (!vertrix_actor_storage_read(player, size, LEVEL_STORE, 4, &level))
    {
        return -1;
    }
    return vertrix_player_set_level(player, size, (int32_t)(level + (uint32_t)delta), notify,
                                    context);
}

int vertrix_player_init_chain(void *player, size_t size)
{
    return vertrix_actor_storage_write(player, size, CHAIN_FIELD, 4, 12);
}

int vertrix_player_start_bonus(void *player, size_t size, uint32_t handle,
                               VertrixPieceAllocate allocate, VertrixPieceFinish finish,
                               VertrixBonusBegin begin, VertrixObjectStorage resolve, void *context)
{
    uint32_t board;
    uint32_t word;
    void *board_storage;
    size_t board_size;
    if (!vertrix_actor_storage_read(player, size, CURSOR_CHILD, 4, &board) ||
        !vertrix_actor_storage_read(player, size, BONUS_KIND_DWORD, 4, &word) ||
        !resolve(board, &board_storage, &board_size, context))
    {
        return 0;
    }
    if (!vertrix_piece_actor_spawn(board_storage, board_size, (int32_t)(int8_t)(word >> 24),
                                   allocate, finish, resolve, context))
    {
        return 0;
    }
    begin(handle, BONUS_HANDLER, context);
    return vertrix_player_reset_piece_progress(player, size, resolve, context);
}
