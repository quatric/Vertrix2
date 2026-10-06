#include "scene_lock.h"
#include "game.h"

int vertrix_scene_lock(VertrixScene *scene, VertrixScenePiece *piece, int16_t origin_x,
                       int16_t origin_y, VertrixSceneResolve resolve, VertrixObjectVisit visit,
                       void *context, int *locked)
{
    if (!scene || !piece || !resolve || !visit || !locked || !piece->handle ||
        scene->active != piece->handle)
    {
        return 0;
    }
    int32_t column, top;
    board_pixel_cell(origin_x, origin_y, piece->x, piece->y, &column, &top);
    if (column < 0 || column >= COLS)
    {
        return 0;
    }
    int result = top > -3;
    if (result)
    {
        for (unsigned index = 0; index < 3; index++)
        {
            int32_t row = top + (int32_t)index;
            uint32_t child = piece->children[index];
            if (row >= 0 && row < ROWS)
            {
                VertrixSceneObject *object = child ? resolve(child, context) : NULL;
                if (!object)
                {
                    return 0;
                }
                scene->slots[(unsigned)column * ROWS + (unsigned)row] = child;
                object->field_93 = 0;
                object->field_4e = 50;
                object->effect = 0;
            }
            else if (child)
            {
                visit(child, 2, context);
            }
            piece->children[index] = 0;
        }
    }
    visit(piece->handle, 2, context);
    scene->active = 0;
    *locked = result;
    return 1;
}
