#include "scene.h"
#include <stddef.h>
#include <string.h>

int vertrix_scene_update(VertrixScene *scene, uint32_t board_handle, VertrixSceneDispatch dispatch,
                         void *context)
{
    if (!scene || !dispatch)
    {
        return 0;
    }
    if (scene->active)
    {
        uint32_t active = scene->active;
        dispatch(0x42a960, active, (uint32_t)(int32_t)(int8_t)scene->active_a, context);
        dispatch(0x42a970, scene->active, (uint32_t)(int32_t)(int8_t)scene->active_b, context);
        dispatch(0, scene->active, 0, context);
    }
    for (size_t index = 0; index < VERTRIX_SCENE_SLOTS; index++)
    {
        if (scene->slots[index])
        {
            dispatch(0, scene->slots[index], 0, context);
        }
    }
    if (scene->extra)
    {
        dispatch(0, scene->extra, 0, context);
    }
    if (!scene->suppress_layout)
    {
        dispatch(0x430930, board_handle, 0, context);
    }
    dispatch(0x4b6200, board_handle + 0xcec, 0, context);
    dispatch(0x4b5f50, board_handle + 0xcec, 0, context);
    memset(scene->cell_a, 0, sizeof(scene->cell_a));
    memset(scene->cell_b, 0, sizeof(scene->cell_b));
    memset(scene->columns_a, 0, sizeof(scene->columns_a));
    memset(scene->columns_b, 0, sizeof(scene->columns_b));
    memset(scene->rows, 0, sizeof(scene->rows));
    scene->active_a = 0;
    scene->active_b = 0;
    return 1;
}

static int16_t scene_word(uint32_t value)
{
    uint32_t word = value & 65535u;
    return (int16_t)(word < 32768u ? (int32_t)word : (int32_t)word - 65536);
}

static int scene_position(uint32_t handle, int32_t x, int32_t y, int center,
                          VertrixSceneResolve resolve, void *context)
{
    if (!handle)
    {
        return 1;
    }
    VertrixSceneObject *object = resolve(handle, context);
    if (!object)
    {
        return 0;
    }
    uint32_t px = (uint32_t)x;
    uint32_t py = (uint32_t)y;
    if (center && object->mode != 16)
    {
        px += (24u - (uint32_t)object->measured_width) >> 1;
        py += (24u - (uint32_t)object->measured_height) >> 1;
    }
    object->x = scene_word(px);
    object->y = scene_word(py);
    return 1;
}

int vertrix_scene_layout(const VertrixScene *scene, int16_t ox, int16_t oy,
                         VertrixSceneResolve resolve, void *context)
{
    if (!scene || !resolve)
    {
        return 0;
    }
    for (unsigned group = 0; group < 2; group++)
    {
        for (unsigned cell = 0; cell < 65; cell++)
        {
            int32_t x = ox + (int32_t)(cell / 13) * 24 + (int8_t)scene->cell_a[cell];
            int32_t y = oy + (int32_t)(cell % 13) * 24 + (int8_t)scene->cell_b[cell];
            if (!scene_position(scene->slots[group * 65 + cell], x, y, 1, resolve, context))
            {
                return 0;
            }
        }
    }
    for (unsigned column = 0; column < 5; column++)
    {
        int32_t x = ox + (int32_t)column * 24 + (int8_t)scene->columns_a[column];
        int32_t y = oy + 312 + (int8_t)scene->columns_b[column];
        if (!scene_position(scene->slots[130 + column], x, y, 1, resolve, context))
        {
            return 0;
        }
    }
    for (unsigned group = 0; group < 2; group++)
    {
        for (unsigned row = 0; row < 13; row++)
        {
            int32_t x = ox + (group ? 120 : -24) + (int8_t)scene->rows[group * 2][row];
            int32_t y = oy + (int32_t)row * 24 + (int8_t)scene->rows[group * 2 + 1][row];
            if (!scene_position(scene->slots[135 + group * 13 + row], x, y, 1, resolve, context))
            {
                return 0;
            }
        }
    }
    for (unsigned cell = 0; cell < 65; cell++)
    {
        int32_t x = ox + (int32_t)(cell / 13) * 24 + (int8_t)scene->cell_a[cell];
        int32_t y = oy + (int32_t)(cell % 13) * 24 + (int8_t)scene->cell_b[cell];
        for (unsigned quadrant = 0; quadrant < 4; quadrant++)
        {
            if (!scene_position(scene->slots[161 + cell * 4 + quadrant],
                                x + (int32_t)(quadrant & 1) * 12, y + (int32_t)(quadrant >> 1) * 12,
                                0, resolve, context))
            {
                return 0;
            }
        }
    }
    return 1;
}
