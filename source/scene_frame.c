#include "scene_frame.h"
#include <stddef.h>

typedef struct
{
    VertrixSceneFrame *frame;
    int valid;
} FrameDispatch;

static int frame_state(uint32_t handle, uint32_t *state, void *context)
{
    FrameDispatch *dispatch = context;
    VertrixSceneFrame *frame = dispatch->frame;
    VertrixSceneObject *object = frame->resolve(handle, frame->context);
    if (!object)
    {
        return 0;
    }
    *state = object->state;
    return 1;
}

static void frame_visit(uint32_t handle, unsigned destroy, void *context)
{
    FrameDispatch *dispatch = context;
    if (!dispatch->valid)
    {
        return;
    }
    if (!dispatch->frame->resolve(handle, dispatch->frame->context))
    {
        dispatch->valid = 0;
        return;
    }
    dispatch->frame->visit(handle, destroy, dispatch->frame->context);
}

static void frame_dispatch(uint32_t operation, uint32_t handle, uint32_t value, void *context)
{
    FrameDispatch *dispatch = context;
    VertrixSceneFrame *frame = dispatch->frame;
    if (!dispatch->valid)
    {
        return;
    }
    switch (operation)
    {
        case 0:
            if (!frame->resolve(handle, frame->context))
            {
                dispatch->valid = 0;
                return;
            }
            frame->visit(handle, 0, frame->context);
            break;
        case 0x42a960:
        case 0x42a970:
        {
            VertrixSceneObject *object = frame->resolve(handle, frame->context);
            if (!object)
            {
                dispatch->valid = 0;
                return;
            }
            if (operation == 0x42a960)
            {
                object->active_a = (uint8_t)value;
            }
            else
            {
                object->active_b = (uint8_t)value;
            }
            break;
        }
        case 0x430930:
            dispatch->valid = vertrix_scene_layout(frame->scene, frame->origin_x, frame->origin_y,
                                                   frame->resolve, frame->context);
            break;
        case 0x4b6200:
            dispatch->valid =
                vertrix_object_list_update(frame->list, frame_visit, dispatch) && dispatch->valid;
            break;
        case 0x4b5f50:
            dispatch->valid =
                vertrix_object_list_prune(frame->list, value, frame_state, frame_visit, dispatch);
            break;
        default:
            dispatch->valid = 0;
            break;
    }
}

int vertrix_scene_frame(VertrixSceneFrame *frame)
{
    if (!frame || !frame->scene || !frame->list || !frame->resolve || !frame->visit)
    {
        return 0;
    }
    FrameDispatch dispatch = {frame, 1};
    return vertrix_scene_update(frame->scene, 0, frame_dispatch, &dispatch) && dispatch.valid;
}
