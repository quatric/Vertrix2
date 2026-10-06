#ifndef VERTRIX_PALETTE_MAP_H
#define VERTRIX_PALETTE_MAP_H
#include "palette_tables.h"
#include <stddef.h>
typedef struct
{
    const uint8_t *data;
    size_t size;
} VertrixPaletteMap;
/* Original475400..475441 default pointer layout, shifted by4ae2de.
 * Relative slots-200..-1 repeat row0;0..200 select channel rows;
 *201..400 repeat row200 (original54b798). Other slots reject.
 * Output borrows table storage; failures preserve it. */
int vertrix_palette_map(const VertrixPaletteTables *tables, int16_t shift, int16_t index,
                        VertrixPaletteMap *output);
/* Original shifted map binding plus48d740/48d7f0 pixel conversion. */
int vertrix_palette_map_pixel(const VertrixPaletteTables *tables, int16_t shift, uint32_t source,
                              int fixed, const uint16_t channels[3], uint32_t *output);
#endif
