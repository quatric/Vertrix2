#include "actor_angle.h"
#include "actor_storage.h"
#include "fixed_point.h"

enum
{
    TURN_ANGLE = 0x24,
    TURN_TARGET = 0x26,
    TURN_RATE = 0x28,
    ORBIT_RADIUS = 0x2a,
    ORBIT_X = 0x2c,
    ORBIT_Y = 0x2e,
    SPIN_ANGLE = 0x34,
    SPIN_RATE = 0x38,
    FULL_TURN = 360,
    FIXED_SHIFT = 16
};

/* Wrap a 16-bit angle word the way the original does: unsigned remainder by 360. */
static uint32_t wrap_word(uint32_t word)
{
    return (word & 0xffff) % FULL_TURN;
}

int vertrix_actor_spin(void *actor, size_t size, uint32_t count)
{
    uint32_t angle;
    uint32_t rate;
    if (!vertrix_actor_storage_read(actor, size, SPIN_ANGLE, 2, &angle) ||
        !vertrix_actor_storage_read(actor, size, SPIN_RATE, 2, &rate))
    {
        return -1;
    }
    int result = 1;
    if (rate == 0)
    {
        return result;
    }
    for (uint32_t step = 0; step < count; step++)
    {
        angle = (angle + rate) & 0xffff;
        if ((int16_t)angle >= FULL_TURN)
        {
            angle = wrap_word(angle);
            result = 0;
        }
        if ((int16_t)angle < 0)
        {
            angle = wrap_word(angle + FULL_TURN);
            result = 0;
        }
    }
    vertrix_actor_storage_write(actor, size, SPIN_ANGLE, 2, angle);
    return result;
}

int vertrix_actor_turn_toward(void *actor, size_t size, int32_t count, uint32_t *unfinished)
{
    uint32_t angle;
    uint32_t target;
    uint32_t rate;
    if (!unfinished || !vertrix_actor_storage_read(actor, size, TURN_ANGLE, 2, &angle) ||
        !vertrix_actor_storage_read(actor, size, TURN_TARGET, 2, &target) ||
        !vertrix_actor_storage_read(actor, size, TURN_RATE, 2, &rate))
    {
        return 0;
    }
    int32_t current = (int16_t)angle;
    int32_t goal = (int16_t)target;
    int32_t step = (int32_t)((uint32_t)(int32_t)(int16_t)rate * (uint32_t)count);
    if (current != goal && step != 0)
    {
        if (step > 0)
        {
            if (goal < current)
            {
                goal += FULL_TURN;
            }
            if (goal - current > step)
            {
                angle = (angle + (uint32_t)step) & 0xffff;
                if ((int16_t)angle >= FULL_TURN)
                {
                    angle = wrap_word(angle);
                }
            }
            else
            {
                angle = target;
            }
        }
        else
        {
            int32_t magnitude = (int32_t)(0u - (uint32_t)step);
            if (current < goal)
            {
                current += FULL_TURN;
            }
            if (current - goal > magnitude)
            {
                angle = (angle - (uint32_t)magnitude) & 0xffff;
                if ((int16_t)angle < 0)
                {
                    angle = wrap_word(angle + FULL_TURN);
                }
            }
            else
            {
                angle = target;
            }
        }
        vertrix_actor_storage_write(actor, size, TURN_ANGLE, 2, angle);
    }
    *unfinished = (angle & 0xffff) != target;
    return 1;
}

static int polar_offset(const void *actor, size_t size, size_t angle_offset,
                        const VertrixAngleTables *tables, int32_t radius_x, int32_t radius_y,
                        int32_t *x, int32_t *y)
{
    uint32_t word;
    if (!tables || !x || !y || !vertrix_actor_storage_read(actor, size, angle_offset, 2, &word))
    {
        return 0;
    }
    int32_t angle = (int16_t)word;
    if (angle < 0 || angle >= VERTRIX_ANGLE_STEPS)
    {
        return 0;
    }
    int32_t scaled_x = (int32_t)((uint32_t)radius_x << FIXED_SHIFT);
    int32_t scaled_y = (int32_t)((uint32_t)radius_y << FIXED_SHIFT);
    *x = vertrix_fixed_multiply(tables->x[angle], scaled_x) >> FIXED_SHIFT;
    *y = vertrix_fixed_multiply(tables->y[angle], scaled_y) >> FIXED_SHIFT;
    return 1;
}

int vertrix_actor_polar_offset(const void *actor, size_t size, const VertrixAngleTables *tables,
                               int32_t radius_x, int32_t radius_y, int32_t *x, int32_t *y)
{
    return polar_offset(actor, size, TURN_ANGLE, tables, radius_x, radius_y, x, y);
}

int vertrix_actor_polar_offset_second(const void *actor, size_t size,
                                      const VertrixAngleTables *tables, int32_t radius_x,
                                      int32_t radius_y, int32_t *x, int32_t *y)
{
    return polar_offset(actor, size, SPIN_ANGLE, tables, radius_x, radius_y, x, y);
}

int vertrix_actor_orbit_point(const void *actor, size_t size, const VertrixAngleTables *tables,
                              uint16_t *x, uint16_t *y)
{
    uint32_t radius;
    uint32_t origin_x;
    uint32_t origin_y;
    int32_t offset_x;
    int32_t offset_y;
    if (!x || !y || !vertrix_actor_storage_read(actor, size, ORBIT_RADIUS, 2, &radius) ||
        !vertrix_actor_storage_read(actor, size, ORBIT_X, 2, &origin_x) ||
        !vertrix_actor_storage_read(actor, size, ORBIT_Y, 2, &origin_y) ||
        !vertrix_actor_polar_offset(actor, size, tables, (int16_t)radius, (int16_t)radius,
                                    &offset_x, &offset_y))
    {
        return 0;
    }
    *x = (uint16_t)(origin_x + (uint32_t)offset_x);
    *y = (uint16_t)(origin_y - (uint32_t)offset_y);
    return 1;
}

enum
{
    DOUBLE_RADIUS_FIRST = 0x3a,
    DOUBLE_RADIUS_SECOND = 0x2a,
    DOUBLE_ORIGIN_X = 0x2c,
    DOUBLE_ORIGIN_Y = 0x2e
};

int vertrix_actor_double_orbit_point(const void *actor, size_t size,
                                     const VertrixAngleTables *tables, uint16_t *x, uint16_t *y,
                                     VertrixOrbitScratch *scratch)
{
    uint32_t first, second, origin_x, origin_y;
    int32_t first_x, first_y, second_x, second_y, radius;
    if (!x || !y || !vertrix_actor_storage_read(actor, size, DOUBLE_RADIUS_FIRST, 2, &first) ||
        !vertrix_actor_storage_read(actor, size, DOUBLE_RADIUS_SECOND, 2, &second) ||
        !vertrix_actor_storage_read(actor, size, DOUBLE_ORIGIN_X, 2, &origin_x) ||
        !vertrix_actor_storage_read(actor, size, DOUBLE_ORIGIN_Y, 2, &origin_y) ||
        !vertrix_actor_polar_offset_second(actor, size, tables, (int16_t)first, (int16_t)first,
                                           &first_x, &first_y))
    {
        return 0;
    }
    radius = (int32_t)((uint32_t)(int16_t)second + (uint32_t)first_x);
    if (!vertrix_actor_polar_offset(actor, size, tables, radius, radius, &second_x, &second_y))
    {
        return 0;
    }
    scratch->x = second_x;
    scratch->y = second_y;
    scratch->radius = radius;
    *x = (uint16_t)(origin_x + (uint32_t)second_x);
    *y = (uint16_t)(origin_y - (uint32_t)second_y);
    return 1;
}

int vertrix_actor_chain_orbit_point(const void *actor, size_t size,
                                    const VertrixAngleTables *tables, uint16_t *x, uint16_t *y,
                                    VertrixChainScratch *scratch)
{
    uint32_t radius_x, radius_y, origin_x, origin_y;
    int32_t first_x, first_y, second_x, second_y, third_x, third_y;
    if (!x || !y || !vertrix_actor_storage_read(actor, size, DOUBLE_RADIUS_FIRST, 2, &radius_x) ||
        !vertrix_actor_storage_read(actor, size, DOUBLE_RADIUS_SECOND, 2, &radius_y) ||
        !vertrix_actor_storage_read(actor, size, DOUBLE_ORIGIN_X, 2, &origin_x) ||
        !vertrix_actor_storage_read(actor, size, DOUBLE_ORIGIN_Y, 2, &origin_y) ||
        !vertrix_actor_polar_offset(actor, size, tables, (int16_t)radius_x, (int16_t)radius_y,
                                    &first_x, &first_y))
    {
        return 0;
    }
    scratch->first_x = (uint16_t)first_x;
    scratch->first_y = (uint16_t)first_y;
    if (!vertrix_actor_polar_offset_second(actor, size, tables, (int16_t)scratch->first_x,
                                           (int16_t)scratch->first_y, &second_x, &second_y))
    {
        return 0;
    }
    *x = (uint16_t)((uint16_t)second_x - (uint16_t)second_y + origin_x);
    if (!vertrix_actor_polar_offset_second(actor, size, tables, (int16_t)scratch->first_y,
                                           (int16_t)scratch->first_x, &third_x, &third_y))
    {
        return 0;
    }
    scratch->x = third_x;
    scratch->y = third_y;
    *y = (uint16_t)((uint16_t)third_y + (uint16_t)third_x + origin_y);
    return 1;
}
