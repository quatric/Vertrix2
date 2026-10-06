#ifndef VERTRIX_WINDOW_TABLES_H
#define VERTRIX_WINDOW_TABLES_H
#include <stdint.h>

#include "block_factory.h"
#include "call_glue.h"

/* The data the table builder reads and writes. The services resolve VERTRIX_WINDOW_SOURCE to the
 * storage of the pointer and integer tables (0x4f5f90 up to 0x4f63b0), VERTRIX_WINDOW_TARGET to
 * that of the table it fills (0x52e784, 0x900 bytes) and each pointer of the first table to the
 * array it designates. */
enum
{
    VERTRIX_WINDOW_SOURCE = 0x4f5f90,
    VERTRIX_WINDOW_SOURCE_SIZE = 0x420,
    VERTRIX_WINDOW_TARGET = 0x52e784,
    VERTRIX_WINDOW_TARGET_SIZE = 0x900
};

/* Original 0x40a590 (eax = sign, ebx and ecx are the caller's registers, which show in the first
 * calls): fills five arrays of single precision windows, 1 / (2 cos((2i + 1) pi / n)) for i below
 * 16 >> k with n = 64 >> k (k = 0..4, the arrays at the pointers of the first table), then scales
 * the 512 integers at 0x4f5fa4 by 2^-16 and the sign (flipped every 64 entries) into the table at
 * 0x52e784 in two passes of 256 (rows 128 bytes apart, wrapping back 0xffc every 32, each value
 * stored twice, 0x40 bytes apart). The arithmetic is done by the runtime helpers 0x4d6768,
 * 0x4db507, 0x4db350, 0x4eb652, 0x4c9dd6 and 0x4eb606, which return their double in eax:edx (edx in
 * the call's out_value). Returns zero when a table or array cannot be accessed. */
int vertrix_window_tables(const VertrixCalls *calls, const VertrixFactoryServices *services,
                          uint32_t sign, uint32_t ebx, uint32_t ecx);

#endif
