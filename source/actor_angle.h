#ifndef VERTRIX_ACTOR_ANGLE_H
#define VERTRIX_ACTOR_ANGLE_H
#include <stddef.h>
#include <stdint.h>

#define VERTRIX_ANGLE_STEPS 360

/* Per-degree 16.16 factors (the original tables at 0x59939c for x and 0x598dfc for y). */
typedef struct
{
    int32_t x[VERTRIX_ANGLE_STEPS];
    int32_t y[VERTRIX_ANGLE_STEPS];
} VertrixAngleTables;

/* Original0x4ad110: advance the angle word at +0x34 by the rate word at +0x38, count times,
 * wrapping into 0..359 after each step. A zero rate or count changes nothing. Returns 1 when
 * no wrap was needed, 0 otherwise; -1 for short storage. */
int vertrix_actor_spin(void *actor, size_t size, uint32_t count);

/* Original0x4ace40: turn the angle word at +0x24 toward the target word at +0x26 by count times
 * the signed rate word at +0x28, the short way round a 360 degree circle. Reaching or passing
 * the target snaps to it. *unfinished is 1 while the angle differs from the target. */
int vertrix_actor_turn_toward(void *actor, size_t size, int32_t count, uint32_t *unfinished);

/* Original0x4ad1c0 (angle word at +0x24) and 0x4ad210 (angle word at +0x34): scale the
 * x and y factors of the actor's angle by two radii. Reports 0 for short storage or an angle
 * outside 0..359 (the original would read past the tables). */
int vertrix_actor_polar_offset(const void *actor, size_t size, const VertrixAngleTables *tables,
                               int32_t radius_x, int32_t radius_y, int32_t *x, int32_t *y);
int vertrix_actor_polar_offset_second(const void *actor, size_t size,
                                      const VertrixAngleTables *tables, int32_t radius_x,
                                      int32_t radius_y, int32_t *x, int32_t *y);

/* Original0x4ad260: position of the point at the radius word at +0x2a and the angle at +0x24
 * around the origin words +0x2c/+0x2e: x = origin x + offset x, y = origin y - offset y (both
 * 16-bit). */
int vertrix_actor_orbit_point(const void *actor, size_t size, const VertrixAngleTables *tables,
                              uint16_t *x, uint16_t *y);

/* The scratch globals of 0x4ad3c0 (0x5bb620, 0x5bb624 and 0x5bb628). */
typedef struct
{
    int32_t x;
    int32_t y;
    int32_t radius;
} VertrixOrbitScratch;

/* Original0x4ad3c0: a point on a double orbit: the first offset has the radius word at +0x3a and
 * the angle at +0x34 (0x4ad210); the second has the radius word at +0x2a plus the first x and the
 * angle at +0x24 (0x4ad1c0). The point is x = word +0x2c + the second x and y = word +0x2e minus
 * the second y (16-bit). The scratch receives the second offset and its radius. Returns zero for
 * short storage or an angle outside 0..359. */
int vertrix_actor_double_orbit_point(const void *actor, size_t size,
                                     const VertrixAngleTables *tables, uint16_t *x, uint16_t *y,
                                     VertrixOrbitScratch *scratch);

/* The scratch globals of 0x4ad440 (0x5bb62c .. 0x5bb637): two dwords and two words. */
typedef struct
{
    int32_t x;
    int32_t y;
    uint16_t first_x;
    uint16_t first_y;
} VertrixChainScratch;

/* Original0x4ad440: chain three offsets. The first uses the angle at +0x24 with the radius words
 * +0x3a (for x) and +0x2a (for y) (0x4ad1c0); the second the angle at +0x34 with the low words of
 * the first x and y as radii; the third the same angle with the radii swapped (0x4ad210). The point
 * is x = word +0x2c + low(second x) - low(second y) and y = word +0x2e + low(third x) + low(third
 * y), both 16-bit. The scratch receives the final dwords and the low words of the first offset.
 * Returns zero for short storage or an angle outside 0..359. */
int vertrix_actor_chain_orbit_point(const void *actor, size_t size,
                                    const VertrixAngleTables *tables, uint16_t *x, uint16_t *y,
                                    VertrixChainScratch *scratch);
#endif
