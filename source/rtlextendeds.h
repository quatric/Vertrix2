#ifndef RTLEXTENDEDS_H
#define RTLEXTENDEDS_H

#include "port.h"

/* The runtime's 80-bit extended reals, unpacked as the originals take them: the first operand's
 * mantissa in edx:eax, the second's in ecx:ebx, and esi with the first's sign and exponent word in
 * its low half and the second's in its high half. The result is the mantissa in edx:eax and its
 * word in si (the rest of esi as the original leaves it). */
typedef struct VertrixExtended
{
    uint32_t eax, edx, esi;
} VertrixExtended;

VertrixExtended vertrix_extended_multiply(uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                                          uint32_t esi);
VertrixExtended vertrix_extended_divide(Port *port, uint32_t eax, uint32_t edx, uint32_t ebx,
                                        uint32_t ecx, uint32_t esi);
/* Addition; `negate` 0x80000000 subtracts (the second operand's sign turned). */
VertrixExtended vertrix_extended_add(uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                                     uint32_t esi, uint32_t negate);

/* The operations themselves, for their dispatch entries (their callers take si from the
 * functions above). */
uint32_t vertrix_port_rtl_extended_multiply_4edc0e(PORT_SIGNATURE);
uint32_t vertrix_port_rtl_extended_divide_4eddc4(PORT_SIGNATURE);
uint32_t vertrix_port_rtl_extended_subtract_4ee160(PORT_SIGNATURE);

#endif
