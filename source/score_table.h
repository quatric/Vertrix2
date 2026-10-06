#ifndef VERTRIX_SCORE_TABLE_H
#define VERTRIX_SCORE_TABLE_H
#include "call_glue.h"
#include <stdint.h>

enum
{
    VERTRIX_SCORE_ENTRIES = 5,
    VERTRIX_SCORE_NAMES = 0x5332a8,
    VERTRIX_SCORE_DEFAULT_NAME = 0x50d678,
    VERTRIX_SCORE_NOT_RANKED = 0xff
};

/* Original 0x4177b0: insert a score into the five-entry table (the dwords at 0x533294, which stay
 * in the caller's array). The rank is the first entry the score exceeds; lower entries and their
 * names (the string slots at 0x5332a8, moved through 0x4ca310) shift down, the name slot of the
 * rank is reset to the default text 0x50d678 through 0x4ca370 and the score stored. Returns the
 * rank in the low byte (the 0x4ca370 result above it), 0xff when the table keeps its entries.
 * ebx_high is the caller's ebx above its low word. */
uint32_t vertrix_high_score_insert(const VertrixCalls *calls, uint32_t scores[5], uint32_t score,
                                   uint32_t ebx_high);

/* Original 0x4179d0: four 0x417970 lookups on the byte a at the byte indices 4 * index + 0 to 3
 * (0xffffffff means missing and counts as zero). *sum receives their total and *average twelve
 * times the total over the number found, zero when none was. The guest addresses of the two
 * outputs are what the first calls see in ebx. Returns the average (the total when none). */
uint32_t vertrix_quad_average(const VertrixCalls *calls, uint8_t a, uint8_t index,
                              uint32_t sum_address, uint32_t *sum, uint32_t *average);
#endif
