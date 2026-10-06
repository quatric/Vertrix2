#ifndef VERTRIX_FIXED_POINT_H
#define VERTRIX_FIXED_POINT_H
#include <stdint.h>

#define VERTRIX_RATIO_TABLE_SIZE 0x10000

/* Original0x4849e0: 16.16 fixed-point product, the low 32 bits of (a * b) >> 16. */
int32_t vertrix_fixed_multiply(int32_t a, int32_t b);

/* Original0x4849f0: 16.16 fixed-point quotient (a << 16) / b. The original faults on a zero
 * divisor or a quotient that does not fit 32 bits; both report 0 and clear *valid. */
int32_t vertrix_fixed_divide(int32_t a, int32_t b, int *valid);

/* Original0x484630: iterative square root (Newton steps from a guess of one, stopping when
 * two guesses differ by at most one, with 32-bit wrap-around in the averaging step). A guess
 * of zero before a division (a fault in the original) reports 0 and clears *valid. */
uint32_t vertrix_integer_root(uint32_t value, int *valid);

/* Original0x484680: root of the squared distance between two points (x1, y1, x2, y2 are
 * the low 16 bits taken as signed). */
uint32_t vertrix_point_distance(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, int *valid);

/* Original0x4845d0: angle in degrees for a signed 16.16 ratio through the 65536-entry word
 * table (the original table at 0x59993c): zero past the table, 180 minus the entry for
 * negative ratios, 180 for negative ratios beyond the table. */
uint32_t vertrix_angle_from_ratio(const uint16_t table[VERTRIX_RATIO_TABLE_SIZE], int32_t ratio);

/* Original0x484700: heading in degrees (low 16 bits are the result) of the vector between two
 * points: the angle of the horizontal component over the distance, mirrored to 360 minus it
 * when the vertical component is positive. Identical points give zero. */
uint16_t vertrix_point_heading(const uint16_t table[VERTRIX_RATIO_TABLE_SIZE], uint16_t x1,
                               uint16_t y1, uint16_t x2, uint16_t y2, int *valid);
#endif
