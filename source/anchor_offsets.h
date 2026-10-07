#ifndef VERTRIX_ANCHOR_OFFSETS_H
#define VERTRIX_ANCHOR_OFFSETS_H
#include <stdint.h>

/* Per-group offsets from anchor points. Each group has an anchor (x, y) and a count of items;
 * an item's offset is the anchor minus the item's own position. Offsets with a negative
 * component are not stored. */
typedef struct
{
    uint32_t groups;         /* number of groups */
    uint32_t stride;         /* dwords reserved per group in the item arrays */
    const uint32_t *counts;  /* items per group */
    const int32_t *anchor_x; /* per group */
    const int32_t *anchor_y; /* per group */
    const int32_t *item_x;   /* groups * stride */
    const int32_t *item_y;   /* groups * stride */
    int32_t *offset_x;       /* groups * stride */
    int32_t *offset_y;       /* groups * stride */
} VertrixAnchorSet;

enum
{
    VERTRIX_ANCHOR_WIDE_GROUPS = 19,
    VERTRIX_ANCHOR_WIDE_STRIDE = 60,
    VERTRIX_ANCHOR_NARROW_GROUPS = 5,
    VERTRIX_ANCHOR_NARROW_STRIDE = 5
};

/* Original variants 0x414a90, 0x414b10: 0x414a90 has 19 groups of up to 60 items (counts 0x53969c,
 * anchors 0x534888 and 0x5348d4, items 0x5396e8 and 0x53a8b8, offsets 0x5372fc and 0x5384cc);
 * 0x414b10 has 5 groups of up to 5 items (counts 0x54021c, anchors 0x540064 and 0x540078, items
 * 0x540230 and 0x540294, offsets 0x540154 and 0x5401b8): for every item compute both offsets and
 * store them together when both are nonnegative (signed). */
void vertrix_anchor_offsets_update(const VertrixAnchorSet *set);
#endif
