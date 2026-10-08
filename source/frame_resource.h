#ifndef VERTRIX_FRAME_RESOURCE_H
#define VERTRIX_FRAME_RESOURCE_H
#include "actor_gate.h"
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
/* Original 0x487860: read raw resource dword +4 (the frame count) into EAX.
 * No mutation; other registers are preserved. Short/null storage/result rejects. */
int vertrix_frame_resource_count_full(const void *storage, size_t size, uint32_t *result);
/* Original 0x487850: read the live frame-table token from resource +0, write
 * descriptor to table+4*index with 32-bit address wrapping, and return the table
 * token in result (original EAX). Incoming EDX/EBX/ECX are unchanged. No count
 * check or pointer nonzero check is added: the supplied memory boundaries decide
 * which original addresses are accessible. Missing boundaries/output reject before
 * calls. Boundary failure leaves result unchanged and retains completed callback
 * effects; these failures adapt original memory faults rather than model them. */
int vertrix_frame_resource_set_full(uint32_t resource, uint32_t index, uint32_t descriptor,
                                     VertrixMemoryRead read, VertrixMemoryWrite write,
                                     void *context, uint32_t *result);
#endif
