#ifndef VERTRIX_UI_DISPLAY_H
#define VERTRIX_UI_DISPLAY_H
#include "linked_alternating.h"
#include "ui_artwork.h"

typedef struct
{
    VertrixUiArtwork artwork;
    uint32_t descriptors[2];
    VertrixFrameResource resources[2];
} VertrixUiDisplayAssets;

/* Owned VF images bound to original546618/546634. Keep this structure at a
 * stable address while displays borrow its resources. Descriptor IDs0/1 are
 * local to this bank; they are not original memory addresses. */
int vertrix_ui_display_assets_load(VertrixVf *archive, const char *name, const uint32_t masks[3],
                                   size_t first_source, uint32_t source_index,
                                   VertrixUiDisplayAssets *assets);
void vertrix_ui_display_assets_free(VertrixUiDisplayAssets *assets);
/* Post-position setup46e101/46e290 for pair0..11. Preserves position,
 * transition values and primary/secondary counters. Actor ID/flags and list
 * insertion belong to the surrounding actor constructor, outside this API. */
int vertrix_ui_display_initialize_animation(VertrixLinkedAlternating *display, size_t pair,
                                            const VertrixUiDisplayAssets *assets);
int vertrix_ui_display_update(VertrixLinkedAlternating *display, int linked_present,
                              uint32_t linked_value, uint32_t linked_state, int16_t start_y,
                              uint32_t elapsed, const VertrixUiDisplayAssets *assets);
/* Resolve only descriptors currently bound to this bank. Outputs are preserved
 * if the display has no valid bank image. Returned pixels are borrowed. */
int vertrix_ui_display_image(const VertrixLinkedAlternating *display,
                             const VertrixUiDisplayAssets *assets, const VertrixImage **image,
                             uint32_t *origin_x, uint32_t *origin_y);
#endif
