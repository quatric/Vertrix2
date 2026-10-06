#include "scene_fall.h"

int vertrix_scene_fall_tick(VertrixScene *scene, VertrixScenePiece *piece,
                            VertrixDescentState *state, int16_t origin_x, int16_t origin_y,
                            uint32_t elapsed, int paused, uint32_t frozen, uint32_t blink,
                            VertrixSceneResolve resolve, VertrixObjectVisit visit, void *context,
                            uint32_t *failed)
{
    if (!scene || !piece || !state || !resolve || !visit || !failed)
    {
        return 0;
    }
    if (!scene->active)
    {
        return 1;
    }
    if (!piece->handle || scene->active != piece->handle || !resolve(piece->handle, context))
    {
        return 0;
    }
    VertrixSceneObject *children[3];
    for (unsigned index = 0; index < 3; index++)
    {
        children[index] = piece->children[index] ? resolve(piece->children[index], context) : NULL;
        if (!children[index])
        {
            return 0;
        }
        state->block_effect[index] = children[index]->effect;
    }
    uint32_t pixels = vertrix_descent_budget(state, elapsed, paused, frozen, blink);
    for (unsigned index = 0; index < 3; index++)
    {
        children[index]->effect = state->block_effect[index];
    }
    return vertrix_scene_descent(scene, piece, origin_x, origin_y, pixels, resolve, visit, context,
                                 failed);
}
