#ifndef VERTRIX_UI_DISPLAY_LAYOUT_H
#define VERTRIX_UI_DISPLAY_LAYOUT_H
#include <stddef.h>
#include <stdint.h>
/* Original46e0c8..46e101 and46e257..46e290, tables4f8b88/4f8bb8/
 * 4f8be8/4f8c18. side0=left, side1=right. Runtime offsets533d70/533d74.
 * Invalid pair/side preserves outputs. This computes actor position; full
 * constructor and resource/handler initialization are separate. */
int vertrix_ui_display_position(size_t pair, unsigned side, int16_t offset_x, int16_t offset_y,
                                int16_t *x, int16_t *y);
#endif
