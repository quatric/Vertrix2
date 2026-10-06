#ifndef VERTRIX_CIRCLE_POINTS_H
#define VERTRIX_CIRCLE_POINTS_H
#include <stdint.h>

#include "block_factory.h"
#include "call_glue.h"

/* The scratch words the circle routine keeps (0x558a62 up to 0x558a76): the services resolve
 * VERTRIX_CIRCLE_STATE to their storage. */
enum
{
    VERTRIX_CIRCLE_STATE = 0x558a60,
    VERTRIX_CIRCLE_STATE_SIZE = 0x20
};

/* Original 0x479e50 (eax = surface, edx = the plotting argument, ebx = radius): the midpoint circle
 * of the given radius around the middle of the surface (width at +4 and height at +8, halved);
 * each step plots the four mirrored points with 0x479df0(surface, argument, x, y) until the
 * vertical offset reaches zero. The state (x +0x558a64, y +0x558a66, decision +0x558a68 and the
 * two test words +0x558a6c and +0x558a6e, the centre at +0x558a70 and +0x558a74) is kept in the
 * state region as the original keeps it. Returns zero when the surface or the region cannot be
 * accessed. */
int vertrix_circle_points(const VertrixCalls *calls, const VertrixFactoryServices *services,
                          uint32_t surface, uint32_t argument, uint32_t radius);

#endif
