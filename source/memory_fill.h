#ifndef MEMORY_FILL_H
#define MEMORY_FILL_H
#include "port.h"

/* Clean ports of the runtime's memory fills (port.h). The originals also read a byte ahead of the
 * stores (cmp byte [eax], dl) to touch the cache; those reads change nothing and are left out. */

/* Original 0x4eb5c0 (eax = destination, edx = byte in dl, ebx = count): fill with the byte through
 * 0x4ec2d0 (edx the byte repeated four times, ecx the count). Returns eax unchanged, with edx the
 * fill's. */
uint32_t vertrix_port_fill_bytes(PORT_SIGNATURE);

/* Original 0x4ec2d0 (eax = destination, edx = four pattern bytes, ecx = count): store the pattern's
 * low byte, rotating the pattern right by eight bits each time, until the destination is aligned
 * to four (or the count runs out); then 0x4ec307 for the whole dwords (ecx the count over four)
 * and the remaining one to three bytes from its returned address: dl, dh and dl of its edx.
 * Returns that address and edx. A zero count returns at once. */
uint32_t vertrix_port_fill_pattern(PORT_SIGNATURE);

/* Original 0x4ec307 (eax = destination, edx = value, ecx = count): store the value at count
 * consecutive dwords, in order (single dwords until the address is aligned to 32 bytes, then
 * groups of four, then the rest). Returns the address after the last; edx is unchanged. */
uint32_t vertrix_port_fill_dwords(PORT_SIGNATURE);

#endif
