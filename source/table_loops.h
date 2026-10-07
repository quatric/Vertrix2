#ifndef VERTRIX_TABLE_LOOPS_H
#define VERTRIX_TABLE_LOOPS_H
#include "call_glue.h"
#include <stdint.h>

/* The routines here are loops over the resource tables built through 0x4877f0 (table entry),
 * 0x4831b0 (image from entry), 0x487640 (allocate frames) and 0x487850 (store frame). Their callees
 * are reached through the injected call boundary and keep edx, ebx and ecx except for the results
 * in eax. */

typedef struct VertrixTableDims
{
    uint32_t count;
    uint32_t columns;
    uint32_t cell_width;
    uint32_t cell_height;
} VertrixTableDims;

/* Original 0x45e590: seven rows of 0x1c bytes from 0x544ac0; per row allocate eight frames at the
 * output block and fill each from the image of the entry. Returns the last 0x487850 eax. */
uint32_t vertrix_resource_rows_build(const VertrixCalls *calls, uint32_t ebx);

/* Original 0x45e6b0: allocate 0x13 frames at 0x544a50 and fill each from the 0x544a34 entry image,
 * calling 0x418270 on two after every frame. Returns its last eax. */
uint32_t vertrix_resource_column_build(const VertrixCalls *calls);

/* Original 0x45ec50: for each cell of the grid in dims (the globals 0x4f90b0 to 0x4f90bc), fetch
 * the 0x544bf4 entry, hand it the argument through 0x482e10 with the cell position as ebx and ecx,
 * and finish it through 0x483ed0 with 0x5b9c60. Returns the last eax; the argument when the grid is
 * empty, zero for zero columns. */
uint32_t vertrix_resource_grid_finish(const VertrixCalls *calls, const VertrixTableDims *dims,
                                      uint32_t argument);

/* One run of 0x45ee30: the origin and spacing globals of a row of cells, in the order the original
 * reads them (0x4f9090, 0x4f9094, 0x4f9098 and 0x4f909c for the first run). */
typedef struct VertrixCellRow
{
    uint32_t left;
    uint32_t top;
    uint32_t spacing;
    uint32_t row_spacing;
} VertrixCellRow;

/* Original 0x45ed10: finish the entry of 0x544a6c selected by eax, handing it edx. Returns the
 * eax of 0x483ed0. */
uint32_t vertrix_resource_single_finish(const VertrixCalls *calls, uint32_t selector,
                                        uint32_t argument);

/* Original 0x45ee30: three rows of cells (12 of 0x544ba0, 12 of 0x544bbc and 7 of 0x544bd8), each
 * entry handed the argument through 0x482e10 at ebx = (spacing + 1) * index + left and ecx = top
 * and finished through 0x483ed0 with 0x5b9c60. ebx and ecx are the caller's values for the first
 * call. Returns the last eax. */
uint32_t vertrix_resource_cell_rows(const VertrixCalls *calls, const VertrixCellRow rows[3],
                                    uint32_t argument, uint32_t ebx, uint32_t ecx);

/* Original 0x45f020: the 13 entries of 0x544b84 handed the argument at ebx = first[i] and
 * ecx = second[i] (the dword tables 0x4fbfe0 and 0x4fc014), finished with ecx = 4 * (i + 1).
 * Returns the last eax. */
uint32_t vertrix_resource_paired_finish(const VertrixCalls *calls, const uint32_t first[13],
                                        const uint32_t second[13], uint32_t argument);

/* Original 0x45f140: the eight entries of the 0x544ac0 row first[column] (table 0x4fc050) offset
 * by second[line] (table 0x4fc058) handed the argument and finished; both tables have seven bytes.
 */
uint32_t vertrix_resource_indexed_finish(const VertrixCalls *calls, const uint8_t first[7],
                                         const uint8_t second[7], uint32_t line, uint32_t column,
                                         uint32_t argument);

/* Original 0x45f1f0: the eight entries of 0x544d28 at ebx = 1 + 31 * index and ecx = 1 handed the
 * argument and finished. Returns the last eax. */
uint32_t vertrix_resource_stride_finish(const VertrixCalls *calls, uint32_t argument);

/* Original 0x45f250: count entries of 0x544d60 (flag one) or 0x544d44 (flag zero) at ecx = 1 + 49 *
 * index handed the argument, through 0x483ce0 as well when the flag is one, and finished. The
 * argument is returned for a zero count. */
uint32_t vertrix_resource_flagged_finish(const VertrixCalls *calls, uint32_t argument,
                                         uint32_t flag, uint32_t count);

/* Original fragment 0x45f1e0: initialize seven scratch bytes to 0..6 (the comparison table at
 * 0x53bcc8, element-compared at 0x43635e/0x436404). */
void vertrix_table_identity_cells(uint8_t cells[7]);
/* Original 0x45f1e0: write the seven bytes of global 0x53bcc8 in ascending
 * order and return original eax, seven. Caller supplies that table storage. */
uint32_t vertrix_table_identity_cells_full(uint8_t cells[7]);
#endif
