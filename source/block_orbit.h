#ifndef VERTRIX_BLOCK_ORBIT_H
#define VERTRIX_BLOCK_ORBIT_H
#include "block_update.h"
#include "rotation.h"
#include "rotation_tables.h"
typedef struct
{
    VertrixTimer timer;
    int16_t origin_x, origin_y;
    int16_t x, target_x, step_x, y, target_y, step_y;
    int16_t angle, rotation_step;
    uint8_t mode, mode_target;
    int16_t mode_step;
    int32_t current, target, step;
    uint32_t parameter_64, parameter_6c;
    int16_t effect_target, effect_step;
    uint8_t field_95;
    uint32_t handler;
    int32_t radius_target;
    int16_t effect;
    uint8_t field_94, stage;
    uint8_t amount, field_93;
} VertrixBlockOrbit;
typedef struct
{
    const VertrixRotationTables *tables;
    uint16_t width, height;
    uint8_t screen_override, screen_unscaled, screen_mode;
} VertrixBlockOrbitContext;
/* Original 0x44de20/0x44dfb0 and centered 0x44e920/0x44e9f0. Context dimensions describe the OLD
 * bound descriptor or fallback, before this update binds its animation frame. Trace is shared
 * rotation state. Invalid resources or dimensions preserve all outputs. */
int vertrix_block_orbit_update(VertrixAnimation *animation, const uint32_t *frames, size_t storage,
                               uint32_t elapsed, uint32_t *descriptor, VertrixBlockOrbit *orbit,
                               VertrixRotationTrace *trace,
                               const VertrixBlockOrbitContext *context);
#endif
