#ifndef VERTRIX_UI_SLIDE_SETUP_H
#define VERTRIX_UI_SLIDE_SETUP_H
#include "render_geometry.h"
#include <stddef.h>
#include <stdint.h>

/* Slide-in setup for UI actors. Each routine edits the signed-word position fields of one actor:
 * +0xe/+0x16 current x/y, +0x10/+0x18 start x/y, +0x12/+0x1a step, +0x14/+0x1c target x/y.
 * Storage that is too small to hold the touched fields is preserved and 0 is returned. */
#define VERTRIX_SLIDE_STORAGE_SIZE 0x1e

/* Original 0x4717f0: remember the position as start, step 8, move y down 0x140. */
int vertrix_ui_slide_from_below(uint8_t *actor, size_t size);

/* Original 0x471820: mode 1 enters from the left (x = offset - ebx - 4), other modes enter
 * from the right (x = screen_width + 4 + offset). The original removes two stack words; only the
 * first, offset, is read. screen_width is the word at 0x5b9c8e. */
int vertrix_ui_slide_sideways(uint8_t *actor, size_t size, uint32_t mode, int32_t distance,
                              int32_t offset, uint16_t screen_width);

/* Original 0x4719a0: remember the position as start, step 8/4, move y up 0x70 and copy the new
 * position to +8/+0xa. */
int vertrix_ui_slide_from_above(uint8_t *actor, size_t size);

/* Original 0x457890: centre the actor on its anchor using the measured resource size from
 * 0x4b14c0. The resource inputs mirror vertrix_resource_measure_state; descriptor is NULL when
 * the actor +0xb4 descriptor is zero. Requires 0x100 bytes of storage. */
#define VERTRIX_CENTER_STORAGE_SIZE 0x100
int vertrix_ui_center_on_anchor(uint8_t *actor, size_t size,
                                const VertrixResourceDimensions *descriptor,
                                uint8_t screen_unscaled, uint8_t screen_mode);
#endif
