#include "object_accessors.h"

#include "actor_storage.h"

enum
{
    ACTOR_CLOCK = 0xbc,
    ACTOR_PERIOD = 0xc0,
    ACTOR_SELECTED = 0x154,
    ACTOR_CHOICE_EC = 0xec,
    ACTOR_CHOICE_F0 = 0xf0,
    PLAYER_BYTES = 0x168,
    PLAYER_FLAG_4E8 = 0x4e8,
    PLAYER_BONUS_METER = 0x18c,
    PLAYER_BONUS_FULL = 3,
    PLAYER_FLAG_A60 = 0xa60,
    PLAYER_BYTE_4C4 = 0x4c4,
    OBJECT_FIELD_18 = 0x18,
    OBJECT_SLOTS_END = 0x1c
};

static int copy_dword(void *storage, size_t size, size_t from, size_t to)
{
    uint32_t value;
    return vertrix_actor_storage_read(storage, size, from, 4, &value) &&
           vertrix_actor_storage_write(storage, size, to, 4, value);
}

int vertrix_actor_add_elapsed(void *actor, size_t size, uint32_t offset, uint32_t elapsed)
{
    uint32_t value;
    return vertrix_actor_storage_read(actor, size, offset, 4, &value) &&
           vertrix_actor_storage_write(actor, size, offset, 4, value + elapsed);
}

int vertrix_actor_clock_reached(const void *actor, size_t size, uint32_t *reached)
{
    uint32_t clock;
    uint32_t period;
    if (!reached || !vertrix_actor_storage_read(actor, size, ACTOR_CLOCK, 4, &clock) ||
        !vertrix_actor_storage_read(actor, size, ACTOR_PERIOD, 4, &period))
    {
        return 0;
    }
    *reached = clock >= period;
    return 1;
}

int vertrix_actor_clock_to_period(void *actor, size_t size)
{
    return copy_dword(actor, size, ACTOR_PERIOD, ACTOR_CLOCK);
}

int vertrix_actor_select_ec(void *actor, size_t size)
{
    return copy_dword(actor, size, ACTOR_CHOICE_EC, ACTOR_SELECTED);
}

int vertrix_actor_select_f0(void *actor, size_t size)
{
    return copy_dword(actor, size, ACTOR_CHOICE_F0, ACTOR_SELECTED);
}

int vertrix_player_set_bytes_168(void *player, size_t size, uint32_t first, uint32_t second,
                                 uint32_t third)
{
    uint32_t probe;
    if (!vertrix_actor_storage_read(player, size, PLAYER_BYTES + 2, 1, &probe))
    {
        return 0;
    }
    return vertrix_actor_storage_write(player, size, PLAYER_BYTES, 1, first) &&
           vertrix_actor_storage_write(player, size, PLAYER_BYTES + 1, 1, second) &&
           vertrix_actor_storage_write(player, size, PLAYER_BYTES + 2, 1, third);
}

static int read_flag(const void *storage, size_t size, size_t offset, unsigned width,
                     uint32_t expected, int equal, uint32_t *out)
{
    uint32_t value;
    if (!out || !vertrix_actor_storage_read(storage, size, offset, width, &value))
    {
        return 0;
    }
    *out = (value == expected) == equal;
    return 1;
}

int vertrix_player_flag_4e8(const void *player, size_t size, uint32_t *set)
{
    return read_flag(player, size, PLAYER_FLAG_4E8, 4, 0, 0, set);
}

int vertrix_player_bonus_meter_full(const void *player, size_t size, uint32_t *full)
{
    return read_flag(player, size, PLAYER_BONUS_METER, 4, PLAYER_BONUS_FULL, 1, full);
}

int vertrix_player_flag_a60(const void *player, size_t size, uint32_t *set)
{
    return read_flag(player, size, PLAYER_FLAG_A60, 4, 0, 0, set);
}

int vertrix_player_byte_4c4_is_one(const void *player, size_t size, uint32_t *is_one)
{
    return read_flag(player, size, PLAYER_BYTE_4C4, 1, 1, 1, is_one);
}

int vertrix_object_set_18(void *object, size_t size, uint32_t value)
{
    return vertrix_actor_storage_write(object, size, OBJECT_FIELD_18, 4, value);
}

int vertrix_actor_counter_pair_reached(const void *actor, size_t size, uint32_t counter_offset,
                                       uint32_t limit_offset, uint32_t *reached)
{
    uint32_t counter;
    uint32_t limit;
    if (!reached || !vertrix_actor_storage_read(actor, size, counter_offset, 4, &counter) ||
        !vertrix_actor_storage_read(actor, size, limit_offset, 4, &limit))
    {
        return 0;
    }
    *reached = counter >= limit;
    return 1;
}

int vertrix_actor_set_times_twelve(void *actor, size_t size, uint32_t offset, uint32_t value)
{
    return vertrix_actor_storage_write(actor, size, offset, 4, value * 12u);
}

int vertrix_player_fill_bytes(void *player, size_t size, uint32_t start, uint32_t count,
                              uint32_t value)
{
    uint32_t probe;
    uint32_t i;
    if (count == 0 || !vertrix_actor_storage_read(player, size, start + count - 1, 1, &probe))
    {
        return 0;
    }
    for (i = 0; i < count; i++)
    {
        vertrix_actor_storage_write(player, size, start + i, 1, value);
    }
    return 1;
}

int vertrix_object_clear_slots(void *object, size_t size)
{
    uint32_t probe;
    unsigned i;
    if (!vertrix_actor_storage_read(object, size, OBJECT_SLOTS_END - 4, 4, &probe))
    {
        return 0;
    }
    for (i = 0; i < OBJECT_SLOTS_END; i += 4)
    {
        vertrix_actor_storage_write(object, size, i, 4, 0xffffffffu);
    }
    return 1;
}

int32_t vertrix_compare_u32(uint32_t first, uint32_t second)
{
    return first < second ? -1 : first > second;
}

uint32_t vertrix_actor_advance_elapsed(void *actor, size_t size, uint32_t object, uint32_t offset,
                                       uint32_t elapsed)
{
    return vertrix_actor_add_elapsed(actor, size, offset, elapsed) ? object : 0;
}

uint32_t vertrix_actor_sync_clock_period(void *actor, size_t size, uint32_t object)
{
    return vertrix_actor_clock_to_period(actor, size) ? object : 0;
}

uint32_t vertrix_actor_choose_handler(void *actor, size_t size, uint32_t object,
                                      uint32_t source_offset)
{
    return copy_dword(actor, size, source_offset, ACTOR_SELECTED) ? object : 0;
}

uint32_t vertrix_player_write_bytes_168(void *player, size_t size, uint32_t object, uint32_t first,
                                        uint32_t second, uint32_t third)
{
    return vertrix_player_set_bytes_168(player, size, first, second, third) ? object : 0;
}

uint32_t vertrix_player_test_4e8(const void *player, size_t size)
{
    uint32_t result = 0;
    vertrix_player_flag_4e8(player, size, &result);
    return result;
}

uint32_t vertrix_player_test_bonus_full(const void *player, size_t size)
{
    uint32_t result = 0;
    vertrix_player_bonus_meter_full(player, size, &result);
    return result;
}

uint32_t vertrix_player_test_a60(const void *player, size_t size)
{
    uint32_t result = 0;
    vertrix_player_flag_a60(player, size, &result);
    return result;
}

uint32_t vertrix_player_test_4c4(const void *player, size_t size)
{
    uint32_t result = 0;
    vertrix_player_byte_4c4_is_one(player, size, &result);
    return result;
}

uint32_t vertrix_object_write_18(void *storage, size_t size, uint32_t object, uint32_t value)
{
    return vertrix_object_set_18(storage, size, value) ? object : 0;
}

uint32_t vertrix_actor_test_counter_pair(const void *actor, size_t size, uint32_t counter_offset,
                                         uint32_t limit_offset)
{
    uint32_t result = 0;
    vertrix_actor_counter_pair_reached(actor, size, counter_offset, limit_offset, &result);
    return result;
}

uint32_t vertrix_actor_store_times_twelve(void *actor, size_t size, uint32_t offset, uint32_t value)
{
    return vertrix_actor_set_times_twelve(actor, size, offset, value) ? value * 12u : 0;
}

uint32_t vertrix_player_fill_byte_range(void *player, size_t size, uint32_t object, uint32_t start,
                                        uint32_t count, uint32_t value)
{
    if (start > size || count > size - start)
    {
        return 0;
    }
    return vertrix_player_fill_bytes(player, size, start, count, value) ? object + count : 0;
}

uint32_t vertrix_object_reset_slots(void *storage, size_t size, uint32_t object)
{
    return vertrix_object_clear_slots(storage, size) ? object + OBJECT_SLOTS_END : 0;
}
