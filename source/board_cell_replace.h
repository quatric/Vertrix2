#ifndef VERTRIX_BOARD_CELL_REPLACE_H
#define VERTRIX_BOARD_CELL_REPLACE_H
#include "block_factory.h"
#include "call_glue.h"
#include <stddef.h>
#include <stdint.h>

enum
{
    VERTRIX_REPLACE_BLOCKS = 0x220,
    VERTRIX_REPLACE_COMPANION = 0x87c,
    VERTRIX_REPLACE_MARKERS = 0xb94,
    VERTRIX_REPLACE_COLUMN_STRIDE = 0x34,
    VERTRIX_REPLACE_MARKER_COLUMN = 13,
    VERTRIX_REPLACE_HANDLER_44D480 = 0x44d480,
    VERTRIX_REPLACE_HANDLER_44D5F0 = 0x44d5f0
};

/* The locals of the two routines are reached through the call boundary: frame is the token for the
 * routine's ebp, whose locals ebp - 0x14 (second) and ebp - 0x18 (first) are what 0x435fe0 and
 * 0x4360b0 are given in ecx and ebx, and ebx and ecx are the caller's incoming values. */

/* Original 0x4365c0: when 0x436030 accepts the board and arg, 0x435fe0 names a cell; mark it (2),
 * move its block to the companion grid and clear the cell, retire the block through 0x4ac8f0,
 * 0x4ac7b0, mark its bytes (+0x4e = 0x64, +0x44 = 0x10), spawn the replacement through 0x430800
 * into the cell and finish both through the 0x4ac490..0x4ac380 chain; finally 0x430440 on the cell.
 * Returns one, zero when 0x436030 refuses. */
uint32_t vertrix_board_replace_cell(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services, uint32_t board,
                                    void *storage, size_t size, uint32_t arg, uint32_t frame,
                                    uint32_t ebx, uint32_t ecx);

/* Original 0x436440: the same with a random cell: the draw 0x4826c0 over the 16-bit result of
 * 0x436030 picks the cell through 0x4360b0. */
uint32_t vertrix_board_replace_random_cell(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services, uint32_t board,
                                           void *storage, size_t size, uint32_t arg, uint32_t frame,
                                           uint32_t ebx, uint32_t ecx);

enum
{
    VERTRIX_REPLACE_COLUMNS = 5,
    VERTRIX_REPLACE_ROWS = 13
};

/* Original 0x433040: over the 5 columns of 13 cells, 0x430660 on the first board when the second
 * board holds a block in the cell and then on the second board when the first does, with the
 * column and row as edx and ebx (the row also in ecx). Returns the last eax, the first board when
 * there was no call. */
uint32_t vertrix_board_burst_occupied(const VertrixCalls *calls, uint32_t first,
                                      const void *first_storage, size_t first_size, uint32_t second,
                                      const void *second_storage, size_t second_size);

/* Original 0x43bbf0: set up the board view of an object: 0x482110 with eleven stack arguments (the
 * addresses inside the object and inside the board its +0x15c names, and the frame's local at
 * ebp - 0x14, to which it stores a handler), then that handler is bound to the object through
 * 0x4ac8f0, the board's dword at +0xb90 set to one, and 0x4726d0 on the board and 0x43ad50 on the
 * object run. frame is the token for ebp. Returns the eax of 0x43ad50, zero when the board does not
 * resolve. */
uint32_t vertrix_board_view_setup(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  uint32_t object, const void *storage, size_t size,
                                  uint32_t frame);
/* Original 0x43bd80: a bare call to 0x43bbf0, whose own frame sits one return address deeper. frame
 * is the token for the entry esp minus 4 as in vertrix_board_view_setup. */
uint32_t vertrix_board_view_setup_forward(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services, uint32_t object,
                                          const void *storage, size_t size, uint32_t frame);
#endif
