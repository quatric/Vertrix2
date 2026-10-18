#ifndef INPUTDEVICES_H
#define INPUTDEVICES_H
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

/* Original 0x475d70 (eax = input slot): whether its byte at +4 (read by 0x475800) is 1. Returns
 * 1 or 0, with the call's edx. */
uint32_t vertrix_port_input_ready(PORT_SIGNATURE);

/* Original 0x476480 (eax = input table, dx = slot): 0x475d70 for the slot's 0x60-byte record
 * (edx the slot, ecx the table). */
uint32_t vertrix_port_input_slot_ready(PORT_SIGNATURE);

/* Original 0x4b7b80: when the input thread is running (0x5328bc), inside its critical section
 * (0x5328c0, EnterCriticalSection 0x4f1b48 and LeaveCriticalSection 0x4f1c40) poll the open
 * devices: 0x55608c (0x4774e0), 0x5588f8 (0x477f10), 0x5536c8 and 0x553798 (0x476d70). Returns
 * the last call's eax; edx is unchanged. */
uint32_t vertrix_port_input_poll_devices(PORT_SIGNATURE);

/* Original 0x4764a0 (eax = keys, dx = key, ebx, ecx, stack = the three outputs): the key record's
 * three fields (0x475da0 of the 0x60-byte record). */
uint32_t vertrix_port_key_fields(PORT_SIGNATURE);

/* Original 0x475da0 (eax = record, edx, ebx, ecx = outputs): store its fields +4, +8 and +0xc of
 * the state at +4 (0x475810, 0x475820, 0x475830). */
uint32_t vertrix_port_key_record_fields(PORT_SIGNATURE);

/* Original 0x476400 (eax = keys, edx = elapsed time): age each of the 256 key records (0x475cd0).
 * Returns 0x100. */
uint32_t vertrix_port_keys_age(PORT_SIGNATURE);

/* Original 0x476440: 0x476400's code with the age routine 0x475d20. */
uint32_t vertrix_port_keys_age_476440(PORT_SIGNATURE);

/* Original 0x475a20 (eax = key record): reset it: its flag (0x475af0), counters +0x3c to +0x54,
 * state (0x475790 with zeros) and pending events (0x4759e0). Registers but eax are unchanged. */
uint32_t vertrix_port_key_record_reset(PORT_SIGNATURE);

/* Original 0x476d70(eax = joystick): poll a DirectInput joystick unless it is disabled (+8),
 * publishing +0x14 and +0x18 at 0x5536b4. The device (+0x10) is polled and its 0x50-byte state
 * read into a local, a lost device reacquired by 0x476c80 and read again. Each direction of the
 * two axes runs its press routine when it comes on and its release routine when it goes off
 * (states at +0xa4 to +0xb0), and so does each of the 32 buttons (0x476fb0 and 0x476fe0, states
 * at +0x24). Keeps edx. */
uint32_t vertrix_port_joystick_poll(PORT_SIGNATURE);

/* Original 0x4774e0(eax = keyboard): read the keyboard's buffered DirectInput events (+0xc the
 * device; GetDeviceData into 0x553878, count 0x556078, status 0x553870), reacquiring a lost
 * device (+0x10 the acquired flag). Each event's scan code maps through 0x4fe600 to a key
 * (0x553874, 0x553876 the last), which goes to the key table 0x54d640 as pressed (0x4761d0) or
 * released (0x476280); key 0x6b is skipped. Keeps edx. */
uint32_t vertrix_port_keyboard_poll(PORT_SIGNATURE);

/* Original 0x477f10(eax = mouse): poll a DirectInput mouse unless it is disabled (+8). Its
 * buffered events (GetDeviceData into 0x5560dc, a lost device reacquired by 0x477c30) move the
 * position (0x5560d4, 0x5560d8; from +0x48 and +0x4a) by the axis data times the speed (+0x44)
 * in percent, clamped by 0x478480, and press (0x4784d0) or release (0x478520) the keys of the
 * buttons: 0x74 and 0x75 (swapped by +0x38), 0xbe to 0xc3. With edge scrolling (+0x60 == 1)
 * the four edges around +0x5c and +0x5e, +0x54 wide, run their enter and leave routines and
 * the cursor is held at the centre. Keeps edx. */
uint32_t vertrix_port_mouse_poll(PORT_SIGNATURE);

#endif
