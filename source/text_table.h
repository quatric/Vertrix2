#ifndef VERTRIX_TEXT_TABLE_H
#define VERTRIX_TEXT_TABLE_H
#include <stdint.h>

#include "block_factory.h"
#include "call_glue.h"

/* The text table at 0x53bdfc: 20 rows of nine string variables (0x24 bytes a row), with the counts
 * of leading and used columns kept beside it. The services resolve VERTRIX_TEXT_TABLE_REGION to
 * the storage of the table region (0x53bd00 up to 0x53c0d0), the strings by their addresses. */
enum
{
    VERTRIX_TEXT_TABLE_REGION = 0x53bd00,
    VERTRIX_TEXT_TABLE_REGION_SIZE = 0x3d0
};

/* Original 0x415180 (eax = first selector, edx = second selector): assigns (0x4ca310) the variables
 * of rows 0..19 from the addresses of the first source table (0x53c0cc + 80 * first), of rows 1..6
 * from those of the second (0x53c93c + 24 * second); then for each row, 0x4ccfe0 against 0x50d383
 * picks the last column whose string passes (stored at 0x53bd0c + 4 * row as one past its index),
 * and 0x4ccfe0 against 0x50d384 counts the passing columns (0x53bd5c) and sums their string
 * lengths (0x53bdac). Returns zero when a table or string cannot be read. */
int vertrix_text_table_refresh(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               uint32_t first, uint32_t second);

#endif
