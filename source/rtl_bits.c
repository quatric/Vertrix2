#include "rtl_bits.h"

uint32_t vertrix_rtl_single_negate(uint32_t bits)
{
    return bits ? bits ^ 0x80000000u : 0;
}
