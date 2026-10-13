#ifndef VERTRIX_PORT_STREAM_H
#define VERTRIX_PORT_STREAM_H
#include "port.h"

/* Clean ports of the memory stream reads (port.h). A memory stream keeps its read position at
 * +0x04 and its end at +0x08 (addresses). */

/* Original 0x48a930 (eax = stream, edx = destination, ebx = item size, ecx = item count): copy
 * size * count bytes (32-bit product, stored at the global 0x5bb234) from the read position, or
 * only the bytes left (stored at 0x5bb238) when fewer remain, and advance the position. The
 * answer, 1 when everything was there and 0 otherwise, goes to 0x5bb230 and the count copied to
 * 0x5bb22c. The copy runs forward, four bytes at a time and then the rest one at a time. Returns
 * the answer, with edx the stream (unchanged when nothing was copied). */
uint32_t vertrix_port_stream_read_exact(PORT_SIGNATURE);

/* Original 0x48aa90 (eax = stream, edx = count): move the read position by the count, at most to
 * the end (unsigned), and store the step at 0x5bb24c. A negative count moves it by its negation
 * (forward). Returns the stream, with edx the count (the bytes left when clamped). */
uint32_t vertrix_port_stream_skip(PORT_SIGNATURE);

/* Original 0x48a910 (eax = stream): 1 when the read position is at or past the end (unsigned),
 * otherwise 0. edx is unchanged. */
uint32_t vertrix_port_stream_done(PORT_SIGNATURE);

/* Original 0x475df0: the same for the position and end at +0x44 and +0x48. */
uint32_t vertrix_port_stream_done_475df0(PORT_SIGNATURE);

/* Original 0x48aa80 (eax = stream): the read position. edx is unchanged. */
uint32_t vertrix_port_stream_position(PORT_SIGNATURE);

/* Original 0x48a3c0(edx = stream, ebx = string): read a token. The string is set to 0x510a59
 * (0x4ca370); until the stream ends (0x48a910) the next byte (0x48aa80, consumed by 0x48aa90) is
 * appended (0x4ca630), stopping after a backslash or a line end, which are not kept. The string
 * is then trimmed (0x4ce030 and 0x4cdfe0, whose eax and edx are returned). */
uint32_t vertrix_port_stream_read_token(PORT_SIGNATURE);

#endif
