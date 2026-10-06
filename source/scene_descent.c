#include "scene_descent.h"
#include "collision.h"

int vertrix_scene_descent(VertrixScene *scene, VertrixScenePiece *piece, int16_t origin_x,
                          int16_t origin_y, uint32_t pixels, VertrixSceneResolve resolve,
                          VertrixObjectVisit visit, void *context, uint32_t *failed)
{
    if (!scene || !piece || !resolve || !visit || !failed)
    {
        return 0;
    }
    if (!scene->active || !pixels)
    {
        return 1;
    }
    if (!piece->handle || scene->active != piece->handle)
    {
        return 0;
    }
    VertrixSceneObject *object = resolve(piece->handle, context);
    if (!object)
    {
        return 0;
    }
    uint8_t board[COLS][ROWS];
    for (unsigned column = 0; column < COLS; column++)
    {
        for (unsigned row = 0; row < ROWS; row++)
        {
            board[column][row] = scene->slots[column * ROWS + row] ? 0 : EMPTY;
        }
    }
    while (pixels)
    {
        int32_t bottom = (int32_t)piece->y + 72;
        if ((uint32_t)bottom >= (uint32_t)(int32_t)origin_y)
        {
            uint32_t bits = (uint16_t)bottom;
            int16_t pixel = (int16_t)(bits < 32768 ? (int32_t)bits : (int32_t)bits - 65536);
            int32_t column, row;
            board_pixel_cell(origin_x, origin_y, piece->x, pixel, &column, &row);
            if (column < 0 || column >= COLS || row < 0)
            {
                return 0;
            }
        }
        if (!vertrix_down_clear(board, origin_x, origin_y, piece->x, piece->y))
        {
            int locked;
            if (!vertrix_scene_lock(scene, piece, origin_x, origin_y, resolve, visit, context,
                                    &locked))
            {
                return 0;
            }
            *failed = locked ? 0 : 1;
            return 1;
        }
        uint32_t bits = (uint16_t)((uint16_t)piece->y + 1);
        piece->y = (int16_t)(bits < 32768 ? (int32_t)bits : (int32_t)bits - 65536);
        object->y = piece->y;
        pixels--;
    }
    return 1;
}
