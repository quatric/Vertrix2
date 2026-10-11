#ifndef VERTRIX_PORT_INPUT_H
#define VERTRIX_PORT_INPUT_H
#include "port.h"

/* Clean ports of the input repeat routines (port.h). A repeating input keeps its state byte at
 * +0x00, its key record at +0x04, its target record at +0x20 (with +0x2c its handler), its time
 * at +0x40 and +0x48, the arguments of its step at +0x4c, +0x50 and +0x54 and its enable byte at
 * +0x5a. */

/* Original 0x475e50 (eax = input): when enabled (1) with a time, 0x475e30 updates it; when
 * 0x475df0 then answers 1, 0x475e10 gives the number of steps, 0x475de0 is called with it, the
 * time +0x40 is copied to +0x48 and, while the edx 0x475de0 leaves is not 0, 0x475b20 runs that
 * many times (edx, ebx and ecx the step arguments). Returns the last call's eax and edx (the input
 * and edx unchanged when disabled or without a time; the time when there are no steps). */
uint32_t vertrix_port_input_repeat_tick(PORT_SIGNATURE);

/* Original 0x475cd0 (eax = input): 0x475e50, then unless the global 0x553648 is set: with state 0,
 * the handler 0x475c30 when the target has one; with state 1, 0x475800 on the key record and,
 * unless it answers 1 in al, the handler when the target its edx points to has one. Returns the
 * last call's eax and edx; when no further call is made the tick's eax has the state in its second
 * byte and edx is the target record. */
uint32_t vertrix_port_input_poll(PORT_SIGNATURE);

/* Original 0x475800 (eax = record): its first byte in al (eax's upper bytes unchanged). edx is
 * unchanged. */
uint32_t vertrix_port_byte_get(PORT_SIGNATURE);

/* Original 0x475d20 (eax = input): 0x475cd0 without the suspension check, with ebx the target
 * record for the handler calls, and with state 1 repeating 0x475800 (eax and edx the key record)
 * and the handler until the key answers 1 in al or the target has no handler. Returns the last
 * call's eax and edx; when no further call is made the tick's eax has the state in its second
 * byte and edx is the tick's. */
uint32_t vertrix_port_input_drain(PORT_SIGNATURE);

#endif
