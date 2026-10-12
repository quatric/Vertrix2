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

/* Original 0x4046e0: the next bit of the stream: the byte at the position shifted left by the
 * bit offset (modulo 32, kept to 8 bits), its top bit. The offset grows by one; a whole byte moves
 * the position. edx is unchanged. */
uint32_t vertrix_port_bit_get(PORT_SIGNATURE);

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

/* Original 0x404610 (eax = count, at most 24): the next `count` bits of the stream, like 0x404680
 * with three bytes kept to 24 bits; nothing is read for a count of 0 (returns 0). edx is
 * unchanged. */
uint32_t vertrix_port_bits_get24(PORT_SIGNATURE);

/* Original 0x40dc50 (eax = channel row): run the row's effect (byte +3, below 0x24) through the
 * table at 0x4f7444 (edx and bl the effect), when it or the parameter (+4) is set. Returns the
 * effect's eax (the row otherwise); edx is unchanged. */
uint32_t vertrix_port_mixer_effect(PORT_SIGNATURE);

/* Original 0x40c430 (eax, edx, ebx = arguments): the mixer's output routine, cdecl with the three
 * as its arguments: 0x401054 for stereo (0x52fc1c bit 1), 0x401010 otherwise. Returns its eax and
 * edx. */
uint32_t vertrix_port_mixer_output(PORT_SIGNATURE);

/* Original 0x401054 (cdecl: samples out, 32-bit mix in, count): clamp each mixed value into a
 * 16-bit sample (at least one is written). Registers are unchanged. */
uint32_t vertrix_port_mix_clamp(PORT_SIGNATURE);

/* Original 0x4060e0 (eax = bytes used): drop the used bytes from the reader's buffer: the count
 * left (0x51f014) shrinks and the rest moves down (0x4eb5e0) from the buffer (the reader 0x51f01c,
 * its frame +0x3668 of 0x900 bytes from +0x25c, offset +0x10); the pending flag 0x51f018 is
 * cleared. Returns 0, or -1 for a used count past a failed read. edx is unchanged. */
uint32_t vertrix_port_reader_consume(PORT_SIGNATURE);

/* Original 0x4111c0: the wave output pump: the current buffer (0x532570 of 3, 0x20-byte headers
 * from 0x532510) when done (flag bit 1 of +0x10) and with a fill routine (0x532574) is unprepared
 * (waveOutUnprepareHeader 0x4f1750) if still prepared (+0xc), refilled (data +0, size +4), then
 * prepared (0x4f1748) and written (0x4f1754) to the device 0x532500, and the next buffer becomes
 * current. Returns 0; edx is unchanged. */
uint32_t vertrix_port_wave_pump(PORT_SIGNATURE);

/* Original 0x40cb70 (eax = channel, edx = volume): set the channel's volume (byte +0x14 of its
 * 0x18-byte record at 0x52f918) to half the volume. Returns 1 for a channel past 0x52fc18, 2 for
 * a volume over 0x40, else 0. */
uint32_t vertrix_port_channel_volume(PORT_SIGNATURE);

/* Original 0x40ca70 (eax = channel): clear the channel's playing bit (bit 0 of byte +0x16).
 * Returns 1 for a channel past 0x52fc18, else 0. edx is unchanged. */
uint32_t vertrix_port_channel_stop(PORT_SIGNATURE);

/* Original 0x40adb0 (eax = channel from 1): the driver routine 0x52f060, like 0x40adc0, 0x40adf0,
 * 0x40ae00 and their routines at 0x52f060, 0x52f064, 0x52f070 and 0x52f074 with the channel from 0.
 */
uint32_t vertrix_port_driver_call_60(PORT_SIGNATURE);
/* Original 0x40adc0: the driver routine 0x52f064. */
uint32_t vertrix_port_driver_call_64(PORT_SIGNATURE);
/* Original 0x40adf0: the driver routine 0x52f070. */
uint32_t vertrix_port_driver_call_70(PORT_SIGNATURE);
/* Original 0x40ae00: the driver routine 0x52f074. */
uint32_t vertrix_port_driver_call_74(PORT_SIGNATURE);

/* Original 0x40c950 (eax = sample): rewind it (+4 from +0). Returns 1 without a sample, else 0.
 * edx is unchanged. */
uint32_t vertrix_port_sample_rewind(PORT_SIGNATURE);

/* Original 0x40acd0 (eax = device, ebx = buffer): the driver's write routine (0x52f05c). Returns
 * 1 without an open device, 2 without a buffer. */
uint32_t vertrix_port_driver_write(PORT_SIGNATURE);

#endif
