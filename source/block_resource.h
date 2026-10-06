#ifndef VERTRIX_BLOCK_RESOURCE_H
#define VERTRIX_BLOCK_RESOURCE_H
#include "animation.h"
#include "frame_resource.h"

/* Original 0x4ac8d0: reset counter/frame, attach borrowed resource, and
 * retain period and existing descriptor. NULL detaches the resource. */
int vertrix_block_resource_attach(VertrixAnimation *animation,
                                  const VertrixFrameResource **attached,
                                  const VertrixFrameResource *resource);
/* Original 0x4ac8a0: NULL resource leaves descriptor unchanged. */
int vertrix_block_resource_bind(const VertrixAnimation *animation,
                                const VertrixFrameResource *resource, size_t traversal_budget,
                                uint32_t *descriptor);
/* Original 0x4ac720. Empty resources select UINT32_MAX by wrapping subtraction;
 * selecting an endpoint does not bind artwork or change the timer. */
int vertrix_block_resource_last(VertrixAnimation *animation, const VertrixFrameResource *resource);

/* Complete normal block update 0x44c860 with live linked resource binding.
 * Animation frame count must match the top resource. Resource storage is borrowed.
 * Invalid state or failed lookup preserves animation and descriptor. */
int vertrix_block_resource_update(VertrixAnimation *animation, const VertrixFrameResource *resource,
                                  size_t traversal_budget, uint32_t elapsed, uint32_t *descriptor);
#endif
