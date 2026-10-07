#include "title_letter_step.h"
#include "actor_fields.h"
#include "dword_transition.h"
#include "fixed_point.h"
#include "word_transition.h"

enum
{
    MODE = 0x04,
    POSITION_X = 0x08,
    POSITION_Y = 0x0a,
    ORIGIN_X = 0x2c,
    ORIGIN_Y = 0x2e,
    ANGLE = 0x24,
    ANGLE_STEP = 0x28,
    RADIUS = 0x2a,
    LIMIT = 0x30,
    RADIUS_STEP = 0x32,
    LEVEL = 0x44,
    EFFECT = 0x48,
    EFFECT_TARGET = 0x4a,
    EFFECT_STEP = 0x4c,
    VOICE_INDEX = 0x58,
    COUNTER = 0xbc,
    PERIOD = 0xc0
};

static uint32_t get(const uint8_t *actor, size_t offset, unsigned width)
{
    uint32_t value = 0;
    vertrix_actor_storage_read(actor, VERTRIX_LETTER_STORAGE_SIZE, offset, width, &value);
    return value;
}

static void put(uint8_t *actor, size_t offset, unsigned width, uint32_t value)
{
    vertrix_actor_storage_write(actor, VERTRIX_LETTER_STORAGE_SIZE, offset, width, value);
}

/* The shared body of 0x459be0 and 0x45a290. *parked is 1 when the frame was due and the old
 * radius was zero. Returns 0 for short storage, a zero limit with a radius not above it or an
 * angle outside 0..359. */
static int count_core(uint8_t *actor, size_t size, uint32_t elapsed,
                      const VertrixAngleTables *tables, VertrixRotationTrace *trace, int *parked)
{
    *parked = 0;
    uint32_t limit = (uint32_t)(int32_t)(int16_t)get(actor, LIMIT, 2);
    put(actor, COUNTER, 4, get(actor, COUNTER, 4) + elapsed);
    if (get(actor, COUNTER, 4) < get(actor, PERIOD, 4))
    {
        return 1;
    }
    uint32_t quotient = 0;
    vertrix_actor_counter_quotient(actor, size, &quotient);
    vertrix_actor_counter_wrap(actor, size);
    int16_t angle = (int16_t)get(actor, ANGLE, 2);
    vertrix_rotation_advance(&angle, (int16_t)get(actor, ANGLE_STEP, 2), quotient, trace);
    put(actor, ANGLE, 2, (uint16_t)angle);
    uint16_t x = 0;
    uint16_t y = 0;
    if (!vertrix_actor_orbit_point(actor, size, tables, &x, &y))
    {
        return 0;
    }
    uint32_t radius = (uint32_t)(int32_t)(int16_t)get(actor, RADIUS, 2);
    if (radius > limit)
    {
        put(actor, LEVEL, 1, 0);
        put(actor, EFFECT, 2, 0);
    }
    else
    {
        if (limit == 0)
        {
            return 0;
        }
        uint32_t level = 0x10 - (radius << 4) / limit;
        put(actor, LEVEL, 1, (int32_t)level >= 0x10 ? 0x10 : level & 0xff);
    }
    put(actor, RADIUS, 2, get(actor, RADIUS, 2) - get(actor, RADIUS_STEP, 2) * quotient);
    if ((int16_t)get(actor, RADIUS, 2) < 0)
    {
        put(actor, RADIUS, 2, 0);
    }
    int16_t effect = (int16_t)get(actor, EFFECT, 2);
    vertrix_word_transition(&effect, (int16_t)get(actor, EFFECT_TARGET, 2),
                            (int16_t)get(actor, EFFECT_STEP, 2), quotient);
    put(actor, EFFECT, 2, (uint16_t)effect);
    put(actor, POSITION_X, 2, x);
    put(actor, POSITION_Y, 2, y);
    *parked = radius == 0;
    return 1;
}

int vertrix_title_letter_count(uint8_t *actor, size_t size, uint32_t elapsed,
                               const VertrixAngleTables *tables, VertrixRotationTrace *trace,
                               uint32_t voice_base, const VertrixResourceDimensions *descriptor,
                               uint8_t screen_unscaled, uint8_t screen_mode,
                               VertrixLetterVoice *voice)
{
    if (!actor || size < VERTRIX_LETTER_STORAGE_SIZE || !tables || !trace || !voice)
    {
        return 0;
    }
    voice->played = 0;
    int parked = 0;
    if (!count_core(actor, size, elapsed, tables, trace, &parked))
    {
        return 0;
    }
    if (parked)
    {
        put(actor, POSITION_X, 2, get(actor, ORIGIN_X, 2));
        put(actor, LEVEL, 1, 0x10);
        put(actor, POSITION_Y, 2, get(actor, ORIGIN_Y, 2));
        voice->played = 1;
        voice->variant = get(actor, MODE, 4) == 1;
        voice->voice = voice_base + get(actor, VOICE_INDEX, 4) - 1;
        put(actor, 0x154, 4, VERTRIX_LETTER_HANDLER_DONE);
    }
    return vertrix_ui_center_on_anchor(actor, size, descriptor, screen_unscaled, screen_mode);
}

int vertrix_title_letter_fight_count(uint8_t *actor, size_t size, uint32_t elapsed,
                                     const VertrixAngleTables *tables, VertrixRotationTrace *trace,
                                     const VertrixResourceDimensions *descriptor,
                                     uint8_t screen_unscaled, uint8_t screen_mode,
                                     const VertrixFightServices *services)
{
    if (!actor || size < VERTRIX_LETTER_STORAGE_SIZE || !tables || !trace || !services)
    {
        return 0;
    }
    int parked = 0;
    if (!count_core(actor, size, elapsed, tables, trace, &parked))
    {
        return 0;
    }
    if (parked)
    {
        put(actor, POSITION_X, 2, get(actor, ORIGIN_X, 2));
        put(actor, POSITION_Y, 2, get(actor, ORIGIN_Y, 2));
        put(actor, LEVEL, 1, 0x10);
        services->fight(services->context);
        put(actor, EFFECT, 2, 0);
        put(actor, EFFECT_TARGET, 2, 0x96);
        put(actor, EFFECT_STEP, 2, 5);
        put(actor, 0x154, 4, 0x45a3e0);
    }
    return vertrix_ui_center_on_anchor(actor, size, descriptor, screen_unscaled, screen_mode);
}

static int effect_step(uint8_t *actor, size_t size, uint32_t elapsed, int *arrived)
{
    *arrived = 0;
    if (!actor || size < VERTRIX_LETTER_STORAGE_SIZE)
    {
        return 0;
    }
    put(actor, COUNTER, 4, get(actor, COUNTER, 4) + elapsed);
    if (get(actor, COUNTER, 4) >= get(actor, PERIOD, 4))
    {
        uint32_t quotient = 0;
        vertrix_actor_counter_quotient(actor, size, &quotient);
        vertrix_actor_counter_wrap(actor, size);
        int16_t effect = (int16_t)get(actor, EFFECT, 2);
        int moving = vertrix_word_transition(&effect, (int16_t)get(actor, EFFECT_TARGET, 2),
                                             (int16_t)get(actor, EFFECT_STEP, 2), quotient);
        put(actor, EFFECT, 2, (uint16_t)effect);
        *arrived = moving == 0;
    }
    return 1;
}

int vertrix_title_letter_settle(uint8_t *actor, size_t size, uint32_t elapsed,
                                const VertrixResourceDimensions *descriptor,
                                uint8_t screen_unscaled, uint8_t screen_mode)
{
    int arrived = 0;
    if (!effect_step(actor, size, elapsed, &arrived))
    {
        return 0;
    }
    if (arrived)
    {
        put(actor, EFFECT_TARGET, 2, 0);
        put(actor, EFFECT_STEP, 2, 5);
        put(actor, 0x154, 4, 0x459e00);
    }
    return vertrix_ui_center_on_anchor(actor, size, descriptor, screen_unscaled, screen_mode);
}

int vertrix_title_letter_restart(uint8_t *actor, size_t size, uint32_t elapsed,
                                 const VertrixResourceDimensions *descriptor,
                                 uint8_t screen_unscaled, uint8_t screen_mode)
{
    int arrived = 0;
    if (!effect_step(actor, size, elapsed, &arrived))
    {
        return 0;
    }
    if (arrived)
    {
        put(actor, RADIUS, 2, 1);
        put(actor, ORIGIN_X, 2, get(actor, POSITION_X, 2));
        put(actor, ORIGIN_Y, 2, get(actor, POSITION_Y, 2));
        put(actor, ANGLE, 2, 0);
        put(actor, COUNTER, 4, 0);
        put(actor, EFFECT, 2, 0);
        put(actor, EFFECT_TARGET, 2, 0x96);
        put(actor, EFFECT_STEP, 2, 1);
        put(actor, 0x154, 4, VERTRIX_LETTER_HANDLER_DONE);
    }
    return vertrix_ui_center_on_anchor(actor, size, descriptor, screen_unscaled, screen_mode);
}

static uint32_t letter_effect_call(const VertrixCalls *calls, uint8_t *actor, size_t size,
                                   uint32_t object, uint32_t elapsed, uint32_t previous_exception,
                                   int restart)
{
    if (!calls || !calls->call || !actor || size < VERTRIX_LETTER_STORAGE_SIZE)
    {
        return 0;
    }
    uint32_t edx = 0x4ec1ec;
    uint32_t ebx = restart ? 0 : 0x515370;
    uint32_t ecx = restart ? 0x515374 : object;
    uint32_t counter = get(actor, COUNTER, 4) + elapsed;
    if (counter >= get(actor, PERIOD, 4))
    {
        edx = (uint32_t)(int32_t)(int16_t)get(actor, EFFECT_TARGET, 2);
    }
    int arrived = 0;
    effect_step(actor, size, elapsed, &arrived);
    if (arrived)
    {
        if (restart)
        {
            ebx = (uint32_t)(int32_t)(int16_t)get(actor, POSITION_X, 2);
            ecx = (uint32_t)(int32_t)(int16_t)get(actor, POSITION_Y, 2);
            put(actor, RADIUS, 2, 1);
            put(actor, ORIGIN_X, 2, ebx);
            put(actor, ORIGIN_Y, 2, ecx);
            put(actor, ANGLE, 2, 0);
            put(actor, COUNTER, 4, 0);
            put(actor, EFFECT, 2, 0);
            put(actor, EFFECT_TARGET, 2, 0x96);
            put(actor, EFFECT_STEP, 2, 1);
            edx = VERTRIX_LETTER_HANDLER_DONE;
        }
        else
        {
            put(actor, EFFECT_TARGET, 2, 0);
            put(actor, EFFECT_STEP, 2, 5);
            edx = 0x459e00;
        }
        put(actor, 0x154, 4, edx);
    }
    VertrixCallSite site = {.target = 0x457890, .eax = object, .edx = edx, .ebx = ebx, .ecx = ecx};
    calls->call(&site, calls->context);
    return previous_exception;
}

uint32_t vertrix_title_letter_settle_call(const VertrixCalls *calls, uint8_t *actor, size_t size,
                                          uint32_t object, uint32_t elapsed,
                                          uint32_t previous_exception)
{
    return letter_effect_call(calls, actor, size, object, elapsed, previous_exception, 0);
}

uint32_t vertrix_title_letter_restart_call(const VertrixCalls *calls, uint8_t *actor, size_t size,
                                           uint32_t object, uint32_t elapsed,
                                           uint32_t previous_exception)
{
    return letter_effect_call(calls, actor, size, object, elapsed, previous_exception, 1);
}

/* The shared body of 0x459ec0 and 0x45a4f0. *level_zero is 1 when the frame was due and the level
 * byte ended zero (the transition tail then runs). */
static int fly_core(uint8_t *actor, size_t size, uint32_t elapsed, const VertrixAngleTables *tables,
                    VertrixRotationTrace *trace, const VertrixResourceDimensions *descriptor,
                    uint8_t screen_unscaled, uint8_t screen_mode, int *level_zero)
{
    *level_zero = 0;
    uint32_t limit = (uint32_t)(int32_t)(int16_t)get(actor, LIMIT, 2);
    put(actor, COUNTER, 4, get(actor, COUNTER, 4) + elapsed);
    if (get(actor, COUNTER, 4) < get(actor, PERIOD, 4))
    {
        return 1;
    }
    uint32_t quotient = 0;
    vertrix_actor_counter_quotient(actor, size, &quotient);
    vertrix_actor_counter_wrap(actor, size);
    int16_t angle = (int16_t)get(actor, ANGLE, 2);
    vertrix_rotation_advance(&angle, (int16_t)get(actor, ANGLE_STEP, 2), quotient, trace);
    put(actor, ANGLE, 2, (uint16_t)angle);
    uint16_t x = 0;
    uint16_t y = 0;
    if (!vertrix_actor_orbit_point(actor, size, tables, &x, &y))
    {
        return 0;
    }
    uint32_t radius = (uint32_t)(int32_t)(int16_t)get(actor, RADIUS, 2);
    if (radius > limit)
    {
        put(actor, LEVEL, 1, 0);
        put(actor, EFFECT, 2, 0);
    }
    else
    {
        if (limit == 0)
        {
            return 0;
        }
        uint32_t level = 0x10 - (radius << 4) / limit;
        put(actor, LEVEL, 1, (int32_t)level >= 0x10 ? 0x10 : level & 0xff);
    }
    VertrixResourceDimensions fallback = {(uint16_t)get(actor, 0xf4, 2),
                                          (uint16_t)get(actor, 0xf8, 2)};
    int32_t width = 0;
    int32_t height = 0;
    vertrix_resource_measure_state(descriptor, fallback, (uint8_t)get(actor, LEVEL, 1),
                                   (uint8_t)get(actor, 0x91, 1), screen_unscaled, screen_mode,
                                   &width, &height);
    put(actor, 0xe, 2, (uint16_t)((int32_t)x - (int32_t)((uint32_t)width >> 1)));
    put(actor, 0x16, 2, (uint16_t)((int32_t)y - (int32_t)((uint32_t)height >> 1)));
    put(actor, RADIUS, 2, get(actor, RADIUS, 2) + get(actor, RADIUS_STEP, 2) * quotient);
    int16_t effect = (int16_t)get(actor, EFFECT, 2);
    vertrix_word_transition(&effect, (int16_t)get(actor, EFFECT_TARGET, 2),
                            (int16_t)get(actor, EFFECT_STEP, 2), quotient);
    put(actor, EFFECT, 2, (uint16_t)effect);
    *level_zero = get(actor, LEVEL, 1) == 0;
    return 1;
}

int vertrix_title_letter_fight_fly(uint8_t *actor, size_t size, uint32_t elapsed,
                                   const VertrixAngleTables *tables, VertrixRotationTrace *trace,
                                   const VertrixResourceDimensions *descriptor,
                                   uint8_t screen_unscaled, uint8_t screen_mode, uint32_t *finished)
{
    if (!actor || size < VERTRIX_LETTER_STORAGE_SIZE || !tables || !trace || !finished)
    {
        return 0;
    }
    int level_zero = 0;
    if (!fly_core(actor, size, elapsed, tables, trace, descriptor, screen_unscaled, screen_mode,
                  &level_zero))
    {
        return 0;
    }
    if (level_zero)
    {
        put(actor, 0x154, 4, 0);
        *finished = 1;
    }
    return 1;
}

int vertrix_title_letter_digit(uint8_t *actor, size_t size, uint32_t elapsed,
                               const VertrixAngleTables *tables, VertrixRotationTrace *trace,
                               const VertrixResourceDimensions *descriptor, uint8_t screen_unscaled,
                               uint8_t screen_mode, int8_t glyph_level,
                               const VertrixLetterServices *services, uint32_t *finished)
{
    if (!actor || size < VERTRIX_LETTER_STORAGE_SIZE || !tables || !trace || !services || !finished)
    {
        return 0;
    }
    int level_zero = 0;
    if (!fly_core(actor, size, elapsed, tables, trace, descriptor, screen_unscaled, screen_mode,
                  &level_zero))
    {
        return 0;
    }
    if (!level_zero)
    {
        return 1;
    }
    uint32_t moving = 0;
    vertrix_actor_dword_transition(actor, size, VERTRIX_TRANSITION_FIRST, 1, &moving);
    if (moving)
    {
        char digits[12];
        uint32_t value = get(actor, VOICE_INDEX, 4);
        int length = 0;
        do
        {
            digits[length++] = (char)('0' + value % 10);
            value /= 10;
        } while (value);
        uint32_t descriptor_value =
            services->glyph(services->context, (uint8_t)digits[length - 1], glyph_level);
        put(actor, 0xb4, 4, descriptor_value);
        if (get(actor, 0xb0, 4) != 0)
        {
            put(actor, 0xb4, 4,
                services->bind(services->context, get(actor, 0xb0, 4), get(actor, 0xb8, 4)));
        }
        put(actor, 0x154, 4, 0x459be0);
    }
    else
    {
        if (!services->related(services->context, get(actor, MODE, 4)))
        {
            *finished = 1;
        }
        put(actor, 0x154, 4, 0);
    }
    return 1;
}

int vertrix_title_letter_fight_settle(uint8_t *actor, size_t size, uint32_t elapsed,
                                      const VertrixResourceDimensions *descriptor,
                                      uint8_t screen_unscaled, uint8_t screen_mode)
{
    int arrived = 0;
    if (!effect_step(actor, size, elapsed, &arrived))
    {
        return 0;
    }
    if (arrived)
    {
        put(actor, EFFECT_TARGET, 2, 0);
        put(actor, EFFECT_STEP, 2, 5);
        put(actor, 0x154, 4, 0x45a440);
    }
    return vertrix_ui_center_on_anchor(actor, size, descriptor, screen_unscaled, screen_mode);
}

int vertrix_title_letter_fight_restart(uint8_t *actor, size_t size, uint32_t elapsed,
                                       const VertrixResourceDimensions *descriptor,
                                       uint8_t screen_unscaled, uint8_t screen_mode,
                                       const VertrixFightServices *services)
{
    int arrived = 0;
    if (!services || !effect_step(actor, size, elapsed, &arrived))
    {
        return 0;
    }
    if (arrived)
    {
        put(actor, 0x30, 2, 0xa0);
        put(actor, RADIUS, 2, 1);
        put(actor, ORIGIN_X, 2, get(actor, POSITION_X, 2));
        put(actor, ORIGIN_Y, 2, get(actor, POSITION_Y, 2));
        put(actor, ANGLE, 2, services->draw(services->context, 0x168));
        put(actor, ANGLE_STEP, 2, services->draw(services->context, 10) + 10);
        put(actor, RADIUS_STEP, 2, 2);
        put(actor, 0x154, 4, 0x45a4f0);
    }
    return vertrix_ui_center_on_anchor(actor, size, descriptor, screen_unscaled, screen_mode);
}

static void letter_prepare_fly(const VertrixCalls *calls, uint8_t *actor, uint32_t *ebx,
                               uint32_t *ecx, uint32_t handler)
{
    *ebx = (uint32_t)(int32_t)(int16_t)get(actor, POSITION_X, 2);
    *ecx = (uint32_t)(int32_t)(int16_t)get(actor, POSITION_Y, 2);
    put(actor, LIMIT, 2, 0xa0);
    put(actor, RADIUS, 2, 1);
    put(actor, ORIGIN_X, 2, *ebx);
    put(actor, ORIGIN_Y, 2, *ecx);
    VertrixCallSite draw = {
        .target = 0x4826c0, .eax = 0x598d30, .edx = 0x168, .ebx = *ebx, .ecx = *ecx};
    uint32_t angle = calls->call(&draw, calls->context);
    put(actor, ANGLE, 2, angle);
    draw =
        (VertrixCallSite){.target = 0x4826c0, .eax = 0x598d30, .edx = 10, .ebx = *ebx, .ecx = *ecx};
    uint32_t rate = calls->call(&draw, calls->context);
    put(actor, ANGLE_STEP, 2, rate + 10u);
    put(actor, RADIUS_STEP, 2, 2);
    put(actor, 0x154, 4, handler);
}

static uint32_t fight_effect_call(const VertrixCalls *calls, uint8_t *actor, size_t size,
                                  uint32_t object, uint32_t elapsed, uint32_t edx, uint32_t ebx,
                                  uint32_t ecx, int restart)
{
    if (!calls || !calls->call || !actor || size < VERTRIX_LETTER_STORAGE_SIZE)
    {
        return 0;
    }
    uint32_t counter = get(actor, COUNTER, 4) + elapsed;
    if (counter >= get(actor, PERIOD, 4))
    {
        edx = (uint32_t)(int32_t)(int16_t)get(actor, EFFECT_TARGET, 2);
    }
    int arrived = 0;
    effect_step(actor, size, elapsed, &arrived);
    if (arrived)
    {
        if (restart)
        {
            letter_prepare_fly(calls, actor, &ebx, &ecx, 0x45a4f0);
            edx = 0x45a4f0;
        }
        else
        {
            put(actor, EFFECT_TARGET, 2, 0);
            put(actor, EFFECT_STEP, 2, 5);
            edx = 0x45a440;
            put(actor, 0x154, 4, edx);
        }
    }
    VertrixCallSite center = {
        .target = 0x457890, .eax = object, .edx = edx, .ebx = ebx, .ecx = ecx};
    return calls->call(&center, calls->context);
}

uint32_t vertrix_title_letter_fight_settle_call(const VertrixCalls *calls, uint8_t *actor,
                                                size_t size, uint32_t object, uint32_t elapsed,
                                                uint32_t edx, uint32_t ebx)
{
    return fight_effect_call(calls, actor, size, object, elapsed, edx, ebx, object, 0);
}

uint32_t vertrix_title_letter_fight_restart_call(const VertrixCalls *calls, uint8_t *actor,
                                                 size_t size, uint32_t object, uint32_t elapsed,
                                                 uint32_t edx, uint32_t ebx, uint32_t ecx)
{
    return fight_effect_call(calls, actor, size, object, elapsed, edx, ebx, ecx, 1);
}

int vertrix_title_letter_fly_out(uint8_t *actor, size_t size, uint32_t elapsed,
                                 const VertrixAngleTables *tables, VertrixRotationTrace *trace,
                                 const VertrixResourceDimensions *descriptor,
                                 uint8_t screen_unscaled, uint8_t screen_mode)
{
    if (!actor || size < VERTRIX_LETTER_STORAGE_SIZE || !tables || !trace)
    {
        return 0;
    }
    put(actor, COUNTER, 4, get(actor, COUNTER, 4) + elapsed);
    if (get(actor, COUNTER, 4) < get(actor, PERIOD, 4))
    {
        return 1;
    }
    uint32_t quotient = 0;
    vertrix_actor_counter_quotient(actor, size, &quotient);
    vertrix_actor_counter_wrap(actor, size);
    int16_t angle = (int16_t)get(actor, ANGLE, 2);
    vertrix_rotation_advance(&angle, (int16_t)get(actor, ANGLE_STEP, 2), quotient, trace);
    put(actor, ANGLE, 2, (uint16_t)angle);
    uint16_t x = 0;
    uint16_t y = 0;
    if (!vertrix_actor_orbit_point(actor, size, tables, &x, &y))
    {
        return 0;
    }
    VertrixResourceDimensions fallback = {(uint16_t)get(actor, 0xf4, 2),
                                          (uint16_t)get(actor, 0xf8, 2)};
    int32_t width = 0;
    int32_t height = 0;
    vertrix_resource_measure_state(descriptor, fallback, (uint8_t)get(actor, LEVEL, 1),
                                   (uint8_t)get(actor, 0x91, 1), screen_unscaled, screen_mode,
                                   &width, &height);
    put(actor, 0xe, 2, (uint16_t)((int32_t)x - (int32_t)((uint32_t)width >> 1)));
    put(actor, 0x16, 2, (uint16_t)((int32_t)y - (int32_t)((uint32_t)height >> 1)));
    put(actor, RADIUS_STEP, 2, get(actor, RADIUS_STEP, 2) + quotient);
    uint32_t unfinished = 0;
    vertrix_actor_dword_transition(actor, size, 0x64, quotient, &unfinished);
    if (unfinished)
    {
        return 1;
    }
    put(actor, 0x64, 4, 0);
    int16_t radius = (int16_t)get(actor, RADIUS, 2);
    int moving = vertrix_word_transition(&radius, (int16_t)get(actor, LIMIT, 2),
                                         (int16_t)get(actor, RADIUS_STEP, 2), 1);
    put(actor, RADIUS, 2, (uint16_t)radius);
    if (!moving)
    {
        put(actor, 0x154, 4, 0);
    }
    return 1;
}

int vertrix_title_letter_launch(uint8_t *actor, size_t size,
                                const uint16_t heading_table[VERTRIX_RATIO_TABLE_SIZE],
                                void (*play)(void *context, uint32_t channel), void *context)
{
    if (!actor || size < VERTRIX_LETTER_STORAGE_SIZE || !heading_table || !play)
    {
        return 0;
    }
    uint16_t x = (uint16_t)get(actor, POSITION_X, 2);
    uint16_t y = (uint16_t)get(actor, POSITION_Y, 2);
    int valid = 1;
    uint32_t distance = vertrix_point_distance(x, y, 0x140, 0xf0, &valid);
    if (!valid)
    {
        return 0;
    }
    put(actor, RADIUS, 2, distance);
    put(actor, ORIGIN_X, 2, 0x140);
    put(actor, ORIGIN_Y, 2, 0xf0);
    uint16_t heading = vertrix_point_heading(heading_table, 0x140, 0xf0, x, y, &valid);
    if (!valid)
    {
        return 0;
    }
    put(actor, ANGLE_STEP, 2, 0);
    put(actor, LIMIT, 2, 0x240);
    put(actor, RADIUS_STEP, 2, 1);
    put(actor, 0x64, 4, 0);
    put(actor, 0x68, 4, 6);
    put(actor, 0x6c, 4, 1);
    put(actor, ANGLE, 2, heading % 0x168);
    put(actor, PERIOD, 4, 10);
    put(actor, COUNTER, 4, 0);
    play(context, 0);
    play(context, 4);
    put(actor, 0x154, 4, 0x45a1c0);
    return 1;
}

int vertrix_title_letter_wave_count(uint8_t *actor, size_t size, uint32_t elapsed,
                                    const VertrixAngleTables *tables, VertrixRotationTrace *trace,
                                    const VertrixResourceDimensions *descriptor,
                                    uint8_t screen_unscaled, uint8_t screen_mode)
{
    if (!actor || size < VERTRIX_LETTER_STORAGE_SIZE || !tables || !trace)
    {
        return 0;
    }
    int parked = 0;
    if (!count_core(actor, size, elapsed, tables, trace, &parked))
    {
        return 0;
    }
    if (parked)
    {
        put(actor, LEVEL, 1, 0x10);
        put(actor, EFFECT, 2, 0);
        put(actor, POSITION_X, 2, get(actor, ORIGIN_X, 2));
        put(actor, EFFECT_TARGET, 2, 0x32);
        put(actor, POSITION_Y, 2, get(actor, ORIGIN_Y, 2));
        put(actor, EFFECT_STEP, 2, 2);
        put(actor, 0x154, 4, 0x45a750);
    }
    return vertrix_ui_center_on_anchor(actor, size, descriptor, screen_unscaled, screen_mode);
}

int vertrix_title_letter_wave(uint8_t *actor, size_t size, uint32_t elapsed, int second,
                              uint32_t running, const VertrixResourceDimensions *descriptor,
                              uint8_t screen_unscaled, uint8_t screen_mode,
                              const VertrixFightServices *services)
{
    if (!actor || size < VERTRIX_LETTER_STORAGE_SIZE || !services)
    {
        return 0;
    }
    put(actor, COUNTER, 4, get(actor, COUNTER, 4) + elapsed);
    if (get(actor, COUNTER, 4) >= get(actor, PERIOD, 4))
    {
        uint32_t quotient = 0;
        vertrix_actor_counter_quotient(actor, size, &quotient);
        vertrix_actor_counter_wrap(actor, size);
        if (running)
        {
            int16_t effect = (int16_t)get(actor, EFFECT, 2);
            int moving = vertrix_word_transition(&effect, (int16_t)get(actor, EFFECT_TARGET, 2),
                                                 (int16_t)get(actor, EFFECT_STEP, 2), quotient);
            put(actor, EFFECT, 2, (uint16_t)effect);
            if (!moving)
            {
                put(actor, EFFECT_TARGET, 2, second ? 0x32 : 0xffec);
                put(actor, EFFECT_STEP, 2, 2);
                put(actor, 0x154, 4, second ? 0x45a750 : 0x45a830);
            }
        }
        else
        {
            put(actor, EFFECT_TARGET, 2, 0);
            put(actor, EFFECT_STEP, 2, 5);
            put(actor, 0x30, 2, 0xa0);
            put(actor, RADIUS, 2, 1);
            put(actor, ORIGIN_X, 2, get(actor, POSITION_X, 2));
            put(actor, ORIGIN_Y, 2, get(actor, POSITION_Y, 2));
            put(actor, ANGLE, 2, services->draw(services->context, 0x168));
            put(actor, ANGLE_STEP, 2, services->draw(services->context, 10) + 10);
            put(actor, RADIUS_STEP, 2, 2);
            put(actor, 0x154, 4, 0x45a910);
        }
    }
    return vertrix_ui_center_on_anchor(actor, size, descriptor, screen_unscaled, screen_mode);
}

uint32_t vertrix_title_letter_wave_call(const VertrixCalls *calls, uint8_t *actor, size_t size,
                                        uint32_t object, uint32_t elapsed, unsigned second,
                                        const uint32_t *running, uint32_t edx, uint32_t ebx,
                                        uint32_t ecx)
{
    if (!calls || !calls->call || !running || second > 1 || !actor ||
        size < VERTRIX_LETTER_STORAGE_SIZE)
    {
        return 0;
    }
    put(actor, COUNTER, 4, get(actor, COUNTER, 4) + elapsed);
    if (get(actor, COUNTER, 4) >= get(actor, PERIOD, 4))
    {
        uint32_t quotient = 0;
        vertrix_actor_counter_quotient(actor, size, &quotient);
        vertrix_actor_counter_wrap(actor, size);
        if (*running)
        {
            int16_t effect = (int16_t)get(actor, EFFECT, 2);
            int16_t target = (int16_t)get(actor, EFFECT_TARGET, 2);
            edx = (uint32_t)(int32_t)target;
            int moving = vertrix_word_transition(&effect, target,
                                                 (int16_t)get(actor, EFFECT_STEP, 2), quotient);
            put(actor, EFFECT, 2, (uint16_t)effect);
            if (!moving)
            {
                put(actor, EFFECT_TARGET, 2, second ? 0x32 : 0xffec);
                put(actor, EFFECT_STEP, 2, 2);
                edx = second ? 0x45a750 : 0x45a830;
                put(actor, 0x154, 4, edx);
            }
        }
        else
        {
            put(actor, EFFECT_TARGET, 2, 0);
            put(actor, EFFECT_STEP, 2, 5);
            letter_prepare_fly(calls, actor, &ebx, &ecx, 0x45a910);
            edx = 0x45a910;
        }
    }
    VertrixCallSite center = {
        .target = 0x457890, .eax = object, .edx = edx, .ebx = ebx, .ecx = ecx};
    return calls->call(&center, calls->context);
}

int vertrix_title_letter_wave_fly(uint8_t *actor, size_t size, uint32_t elapsed,
                                  const VertrixAngleTables *tables, VertrixRotationTrace *trace,
                                  const VertrixResourceDimensions *descriptor,
                                  uint8_t screen_unscaled, uint8_t screen_mode)
{
    if (!actor || size < VERTRIX_LETTER_STORAGE_SIZE || !tables || !trace)
    {
        return 0;
    }
    int level_zero = 0;
    if (!fly_core(actor, size, elapsed, tables, trace, descriptor, screen_unscaled, screen_mode,
                  &level_zero))
    {
        return 0;
    }
    if (level_zero)
    {
        put(actor, 0x154, 4, 0);
    }
    return 1;
}
