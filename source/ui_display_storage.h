#ifndef VERTRIX_UI_DISPLAY_STORAGE_H
#define VERTRIX_UI_DISPLAY_STORAGE_H
#include "ui_display.h"

/* Create/update original actor bytes using VF-owned image resources. Assets
 * must remain live. Caller resolves linked values and registers actor storage. */
int vertrix_ui_display_storage_construct(void *storage, size_t size, size_t pair, unsigned side,
                                         int16_t offset_x, int16_t offset_y,
                                         const VertrixUiDisplayAssets *assets);
int vertrix_ui_display_storage_update(void *storage, size_t size, int linked_present,
                                      uint32_t linked_value, uint32_t linked_state, int16_t start_y,
                                      uint32_t elapsed, const VertrixUiDisplayAssets *assets);
/* Borrow the current descriptor image and original32-bit origins. Invalid
 * identity/descriptor or freed assets preserve outputs. */
int vertrix_ui_display_storage_image(const void *storage, size_t size,
                                     const VertrixUiDisplayAssets *assets,
                                     const VertrixImage **image, uint32_t *origin_x,
                                     uint32_t *origin_y);
#endif
