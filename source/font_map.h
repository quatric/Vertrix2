#ifndef VERTRIX_FONT_MAP_H
#define VERTRIX_FONT_MAP_H
#include <stddef.h>
#include <stdint.h>
typedef struct
{
    uint32_t space_width, space_height;
    int16_t glyphs[256];
} VertrixFontMap;
/* Original48ab10 initializes indices0..254 to-1; index255 is preserved. */
int vertrix_font_map_construct(VertrixFontMap *map);
/* Original 0x43fc50: preserves unspecified glyphs and maps beyond slot18.
 * Dimensions come from resource4877f0 indices6 and9. */
int vertrix_font_maps_initialize(VertrixFontMap *maps, size_t count, uint32_t width6,
                                 uint32_t height6, uint32_t width9, uint32_t height9);
/* Original 0x43f420/0x48ac00 and shared index5410f4. Resource handles represent
 * original array5410f8. Missing glyph writes index=-1/resource0; invalid indices
 * preserve both outputs. Map initialization and VF resource loading are separate. */
int vertrix_font_glyph(const VertrixFontMap *map, uint8_t glyph, const uint32_t *resources,
                       size_t resource_count, int16_t *selected_index, uint32_t *resource);
#endif
