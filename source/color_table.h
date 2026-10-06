#ifndef VERTRIX_COLOR_TABLE_H
#define VERTRIX_COLOR_TABLE_H
#include "call_glue.h"
#include <stdint.h>

enum
{
    VERTRIX_COLOR_ROWS = 7,
    VERTRIX_COLOR_COLUMNS = 3,
    VERTRIX_COLOR_OBJECT = 0x58,
    VERTRIX_COLOR_FRAME_HANDLER = 0x4ec1ec,
    VERTRIX_COLOR_FRAME_TYPE = 0x515120
};

/* Original 0x441e30: build the palette entries of the seven rows of three colours. A local format
 * object (the frame local at ebp - 0x58, reached through the token frame) is constructed by
 * 0x481b20, given the masks 0xff0000, 0xff00, 0xff and 0xff000000 through 0x481bc0 and, when that
 * succeeds, asked through 0x481e10 for the entry of each colour (edx the argument, ebx the colour,
 * ecx the column plus one); the entries are stored in out. The object is released through 0x481b30
 * whatever happened. */
void vertrix_color_table_build(const VertrixCalls *calls, uint32_t frame, uint32_t argument,
                               const uint32_t colors[7][3], uint32_t out[7][3]);
#endif
