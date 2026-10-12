#ifndef VERTRIX_PORT_AUDIO_H
#define VERTRIX_PORT_AUDIO_H
#include "port.h"

/* Clean ports of the audio decoder's synthesis (port.h). */

/* Original 0x404730 (eax and edx = the two output halves, 0x40 bytes a sample, ebx and ecx =
 * 0x80-byte work buffers, stack = 32 singles): the 32-point cosine transform of the polyphase
 * synthesis, five butterfly passes between the work buffers with the cosine tables at 0x4f5f90 to
 * 0x4f5fa0, then the outputs summed from the last pass. Every operation is a call to the
 * single-precision helpers. Returns the last output (32 into the second half). */
uint32_t vertrix_port_synth_dct(PORT_SIGNATURE);

/* Original 0x405680 (eax, edx passed on): 0x404730 with two 0x80-byte buffers of the frame, ebx
 * the one at ebp-0x104 and ecx the one at ebp-0x84, and the entry ebx as its stack argument.
 * Returns its eax and edx. */
uint32_t vertrix_port_synth_window(PORT_SIGNATURE);

/* Original 0x4056c0 (eax = decoder, edx = output, ebx = address of the output offset): 0x405720
 * (edx 0, ebx a frame buffer of 32 dwords, ecx the address of a cleared dword) fills the buffer;
 * the low words of its 32 dwords are stored at the output plus the offset, which then grows by
 * 0x40. Returns 0x405720's eax, with edx its high word over the last sample stored. */
uint32_t vertrix_port_synth_samples(PORT_SIGNATURE);

/* Original 0x405720 (eax = subband samples, edx = channel, ebx = output, ecx = address of the
 * output offset), the polyphase synthesis of 32 samples of one channel. The decoder ([0x51f01c])
 * keeps a 16-step phase at +0x476c (the left channel, edx 0, steps it back) and a buffer per
 * channel (+0x366c and +0x3eec, in two halves 0x440 apart), into which 0x405680 transforms the
 * subband samples. The samples are windowed sums (0x52e7c4, the window) made with the single
 * helpers (0x4d8177 multiply, 0x4d809c subtract, 0x4d80a6 add, 0x4eb5b4 negate), clamped to 16
 * bits through doubles (0x4eb526, compared by 0x4eb57c) or converted by 0x4d67a8, and stored at
 * the output plus the offset, a channel's samples [0x4056b0] * 2 bytes apart. The offset then
 * grows by 0x80. Returns the number of samples clamped, with edx the last call's (or the last
 * sample's address). */
uint32_t vertrix_port_synth_filter(PORT_SIGNATURE);

/* Original 0x404680 (eax = count): the next `count` bits (at most 16) of the stream at the byte
 * [0x51f014] and the bit [0x51f018]: the two bytes there, big-endian, shifted left by the bit
 * offset (modulo 32) and kept to 16 bits, then right by 16 - count. The bit offset grows by the
 * count; its whole bytes (signed) move the position and it keeps the rest. edx is unchanged. */
uint32_t vertrix_port_bits_get(PORT_SIGNATURE);

/* Original 0x40c460 (eax = buffer, edx = samples, ebx = channel): mix the channel into the
 * buffer (halving the samples for stereo, bit 1 of 0x52fc1d). A channel keeps its position at
 * +4, its step at +8, its loop at +0xc to +0x10 and its state byte at +0x16 (1 stopped, 2 ramped,
 * 4 looping, 8 ping-pong, 0x10 playing backward). Past the loop bound in its direction it turns
 * (ping-pong), wraps (looping) or stops; otherwise the samples up to the bound (signed division,
 * leaving the registers as they were when it would fault) are rendered by the routine at
 * [0x52fc38] (ramped, ecx the buffer) or [0x52fc34] (edx the buffer), cdecl (buffer, samples,
 * channel), with the step negated around the call for a backward channel. Returns the eax and edx
 * the original leaves. */
uint32_t vertrix_port_mixer_channel(PORT_SIGNATURE);

#endif
