#ifndef VERTRIX_PALETTE_TABLES_H
#define VERTRIX_PALETTE_TABLES_H
#include <stdint.h>

typedef struct
{
    uint32_t *lookup;
    uint8_t *hue;
    uint8_t channels[20301];
    uint32_t auxiliary[255];
} VertrixPaletteTables;

/* Original 0x475090: RGB/hue/auxiliary table construction. Zero-initialize output;
 * occupied output is rejected. Tables own their allocations. Allocation
 * failure preserves output. Original global pointer selection is separate. */
int vertrix_palette_tables_build(VertrixPaletteTables *output);
void vertrix_palette_tables_free(VertrixPaletteTables *tables);
/* Convert through the default pointer selection established by475495.
 * Other scene pointer-table selections remain separate. */
int vertrix_palette_tables_pixel(const VertrixPaletteTables *tables, uint32_t source,
                                 int fixed_channels, const uint16_t channels[3], uint32_t *output);
/* Original 0x4754e0 applies byte cycle to default54d1d0 auxiliary pointers.
 * Index0 selects constant100 for cycles0..254; cycle255 reaches original
 * global54cdc8, supplied explicitly as constant_tail (an opaque original
 * value, never a host pointer). Indices1..255 select the auxiliary table plus
 * cycle, including its original zero-filled tail. No host pointer arithmetic
 * escapes allocated tables. Invalid indices preserve output. */
int vertrix_palette_tables_cycle(const VertrixPaletteTables *tables, uint32_t index, uint8_t cycle,
                                 uint32_t constant_tail, uint32_t *output);
#endif
