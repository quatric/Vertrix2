#include "player_ai_tick.h"
#include "actor_storage.h"

enum
{
    PLAYER_AI_ENABLED = 0x454,
    PLAYER_AI_OBJECT = 0x450,
    PLAYER_BOARD_OBJECT = 0x15c,
    PLAYER_TABLE_OFFSET = 0x46c,
    PLAYER_KEY_PERMUTE = 0x164,
    PLAYER_KEY_DROP = 0x166,
    BOARD_PIECE_OFFSET = 0xb78,
    AI_PHASE_OFFSET = 0x178,
    AI_ROTATIONS_OFFSET = 0x16c,
    MIN_PLAYER_SIZE = 0x470,
    MIN_AI_SIZE = 0x180,
    MIN_BOARD_SIZE = 0xb80
};

int vertrix_player_ai_tick(void *player, size_t player_size, const VertrixPlayerAiTickOps *ops)
{
    if (!player || player_size < MIN_PLAYER_SIZE || !ops)
    {
        return 0;
    }

    uint32_t ai_enabled = 0;
    if (!vertrix_actor_storage_read(player, player_size, PLAYER_AI_ENABLED, 4, &ai_enabled) ||
        !ai_enabled)
    {
        return 0;
    }

    uint32_t ai_handle = 0;
    if (!vertrix_actor_storage_read(player, player_size, PLAYER_AI_OBJECT, 4, &ai_handle) ||
        !ai_handle)
    {
        return 0;
    }

    void *ai_storage = NULL;
    size_t ai_size = 0;
    if (ops->resolve)
    {
        if (!ops->resolve(ai_handle, &ai_storage, &ai_size, ops->resolve_context) || !ai_storage ||
            ai_size < MIN_AI_SIZE)
        {
            return 0;
        }
    }
    else
    {
        ai_storage = (void *)(uintptr_t)ai_handle;
        ai_size = MIN_AI_SIZE;
    }

    uint32_t phase = 0;
    if (!vertrix_actor_storage_read(ai_storage, ai_size, AI_PHASE_OFFSET, 4, &phase))
    {
        return 0;
    }

    if (phase == 1)
    {
        if (ops->compare_boards)
        {
            ops->compare_boards(ai_storage, ai_size, player, player_size, ops->compare_context);
        }

        uint32_t board_handle = 0;
        if (vertrix_actor_storage_read(player, player_size, PLAYER_BOARD_OBJECT, 4,
                                       &board_handle) &&
            board_handle)
        {
            void *board_storage = NULL;
            size_t board_size = 0;
            if (ops->resolve &&
                ops->resolve(board_handle, &board_storage, &board_size, ops->resolve_context) &&
                board_storage && board_size >= MIN_BOARD_SIZE)
            {
                uint32_t piece_handle = 0;
                if (vertrix_actor_storage_read(board_storage, board_size, BOARD_PIECE_OFFSET, 4,
                                               &piece_handle) &&
                    piece_handle)
                {
                    void *piece_storage = NULL;
                    size_t piece_size = 0;
                    if (ops->resolve &&
                        ops->resolve(piece_handle, &piece_storage, &piece_size,
                                     ops->resolve_context) &&
                        piece_storage)
                    {
                        uint32_t table[7];
                        if (ops->preview_frames)
                        {
                            ops->preview_frames(piece_storage, piece_size, table,
                                                ops->preview_context);
                        }
                        if (ops->choose_rotation)
                        {
                            uint32_t chosen = 0;
                            ops->choose_rotation(ai_storage, ai_size, table, &chosen,
                                                 ops->rotation_context);
                        }
                    }
                }
            }
        }

        vertrix_actor_storage_write(ai_storage, ai_size, AI_PHASE_OFFSET, 4, 0);

        if (ops->timer_reset)
        {
            ops->timer_reset(ai_storage, ai_size, ops->timer_context);
        }
        uint32_t delay = 0;
        if (ops->draw_delay_2)
        {
            ops->draw_delay_2(player, player_size, &delay, ops->delay_context);
        }
        if (ops->timer_set_period)
        {
            ops->timer_set_period(ai_storage, ai_size, delay, ops->timer_context);
        }
        return 1;
    }
    else
    {
        if (ops->timer_update)
        {
            ops->timer_update(ai_storage, ai_size, ops->timer_context);
        }
        if (!ops->timer_check || ops->timer_check(ai_storage, ai_size, ops->timer_context) != 1)
        {
            return 1;
        }

        if (ops->timer_reset)
        {
            ops->timer_reset(ai_storage, ai_size, ops->timer_context);
        }
        uint32_t delay = 0;
        if (ops->draw_delay_2)
        {
            ops->draw_delay_2(player, player_size, &delay, ops->delay_context);
        }
        if (ops->timer_set_period)
        {
            ops->timer_set_period(ai_storage, ai_size, delay, ops->timer_context);
        }

        uint32_t rotations = 0;
        if (!vertrix_actor_storage_read(ai_storage, ai_size, AI_ROTATIONS_OFFSET, 4, &rotations))
        {
            return 0;
        }

        if ((int32_t)rotations > 0)
        {
            vertrix_actor_storage_write(ai_storage, ai_size, AI_ROTATIONS_OFFSET, 4, rotations - 1);
            uint32_t permute_key = 0;
            if (vertrix_actor_storage_read(player, player_size, PLAYER_KEY_PERMUTE, 2,
                                           &permute_key) &&
                ops->key_event)
            {
                ops->key_event((uint16_t)permute_key, 1, ops->key_context);
                ops->key_event((uint16_t)permute_key, 0, ops->key_context);
            }
            return 2;
        }
        else
        {
            uint32_t board_handle = 0;
            int dropping = 0;
            if (vertrix_actor_storage_read(player, player_size, PLAYER_BOARD_OBJECT, 4,
                                           &board_handle) &&
                board_handle)
            {
                void *board_storage = NULL;
                size_t board_size = 0;
                if (ops->resolve &&
                    ops->resolve(board_handle, &board_storage, &board_size, ops->resolve_context) &&
                    board_storage && board_size >= MIN_BOARD_SIZE)
                {
                    if (ops->check_fast_drop)
                    {
                        dropping =
                            ops->check_fast_drop(board_storage, board_size, ops->drop_context);
                    }
                }
            }

            if (!dropping)
            {
                uint32_t drop_key = 0;
                if (vertrix_actor_storage_read(player, player_size, PLAYER_KEY_DROP, 2,
                                               &drop_key) &&
                    ops->key_event)
                {
                    ops->key_event((uint16_t)drop_key, 1, ops->key_context);
                    ops->key_event((uint16_t)drop_key, 0, ops->key_context);
                }
                return 3;
            }
            return 1;
        }
    }
}
