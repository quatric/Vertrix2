#ifndef VERTRIX_PATTERN_TABLES_H
#define VERTRIX_PATTERN_TABLES_H
#include <stdint.h>

#include "block_factory.h"
#include "call_glue.h"

/* The data the builder reads and writes: the services resolve VERTRIX_PATTERN_SOURCE to the byte
 * table at 0x4fba48 (0x73 entries) and VERTRIX_PATTERN_TARGET to the working tables from 0x5440f6
 * (the run bounds, the pointer and size tables at 0x54414c and 0x544318, the expanded tables at
 * 0x54438c and 0x544790). */
enum
{
    VERTRIX_PATTERN_SOURCE = 0x4fba48,
    VERTRIX_PATTERN_SOURCE_SIZE = 0x80,
    VERTRIX_PATTERN_TARGET = 0x5440f6,
    VERTRIX_PATTERN_TARGET_SIZE = 0x7a0
};

/* Original 0x441f20 (eax = surface): scans the surface (0x478f10 reads a pixel for x and y) in six
 * passes of ten columns (starting at 1, eleven further each pass, then x back to zero): a column
 * run that reads zero ten times in a row ends a pattern that began at the first column which did
 * not; the pattern's width (bounds kept at 0x5440f6 / 0x5440f7 as largest and smallest) and the
 * pixels of each of the ten columns are copied (an allocation from 0x4ec160 of ten times the width)
 * to the next entry of the pointer and size tables. Finally 256 entries of the expanded tables are
 * taken from those entries through the byte table at 0x4fba48 (entry 0x53 when absent). Returns
 * zero when a table or the surface cannot be accessed. */
int vertrix_pattern_tables(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           uint32_t surface);

#endif
