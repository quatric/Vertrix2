#ifndef VERTRIX_PORT_AUDIO_H
#define VERTRIX_PORT_AUDIO_H
#include "port.h"

/* Clean ports of the audio decoder's synthesis (port.h). */

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

#endif
