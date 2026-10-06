#ifndef VERTRIX_FRAME_RESOURCE_H
#define VERTRIX_FRAME_RESOURCE_H
#include <stddef.h>
#include <stdint.h>

typedef struct VertrixFrameResource VertrixFrameResource;
struct VertrixFrameResource
{
    uint32_t kind;
    size_t count;
    const uint32_t *frames;
    const VertrixFrameResource *const *children;
    const uint32_t *indices;
};

/* Original 0x4877f0. Kind one follows child/index pairs; other kinds
 * address direct descriptors. Budget bounds malformed or cyclic graphs.
 * Output is unchanged on invalid storage, index or exhausted budget. */
int vertrix_frame_resource_get(const VertrixFrameResource *resource, uint32_t index, size_t budget,
                               uint32_t *descriptor);
#endif
