#ifndef VERTRIX_OBJECT_BOUNDS_H
#define VERTRIX_OBJECT_BOUNDS_H
#include <stdint.h>

#include "block_factory.h"

/* Original 0x4b4270: whether the point (x, y) lies inside the client area of the object. The
 * area starts at the 16.16 position at +0xc/+0x14, the left inset added to the left edge, and
 * ends at the extents at +0xf4/+0xf8 added to the position, less the right inset for the width,
 * less one. The insets are the dword at +4 of the record at +0xb4 of the objects at +0x17c (left)
 * and +0x180 (right). Every handle is resolved through the services; an unresolvable one returns
 * zero. */
uint32_t vertrix_object_contains_point(const VertrixFactoryServices *services, uint32_t object,
                                       int32_t x, int32_t y);
#endif
