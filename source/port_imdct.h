#ifndef VERTRIX_PORT_IMDCT_H
#define VERTRIX_PORT_IMDCT_H
#include "port.h"

/* Original 0x4088e0 (eax = 18 singles, edx = the previous block's overlap, ebx = this block's
 * overlap, ecx = the window, stack = the output, 0x80 bytes a sample): the long-block inverse
 * transform of one subband. The inputs are summed in place, then five butterflies each give two
 * overlap values (windowed) and two outputs (windowed, plus the previous overlap). Every
 * operation is a call to the single-precision helpers. */
uint32_t vertrix_port_imdct_long(PORT_SIGNATURE);

/* Original 0x408800(eax = samples, edx = granule): the MPEG layer III alias reduction. Short
 * blocks (+0x10 == 2) without mixed blocks (+0x14) are left alone; mixed ones get one boundary,
 * long ones +0x40 less one. At each boundary the eight sample pairs across it are rotated with
 * the cs and ca tables 0x5238a0 and 0x523880 through the fixed-point multiply 0x4d8177, subtract
 * 0x4d809c and add 0x4d80a6. Returns the last add's eax and edx. */
uint32_t vertrix_port_mpeg_antialias(PORT_SIGNATURE);

/* Original 0x407720(eax = output, edx = granule, ebx = 0 or the intensity channel): read the
 * MPEG-2 scale factors. The length word comes from 0x51f020 by +0xc (or 0x51f820 by +0xc / 2);
 * its bit 15 is the preflag +0x4c. The block kind (0 long, 1 short, 2 mixed) and bits 12..14 pick
 * four band counts in 0x4f5e98; each count of factors is read with the next 3-bit length
 * (0x404680) or zeroed when it is 0, and the factors' bit total is returned. 2 * kind + 1 more
 * zeros follow. */
uint32_t vertrix_port_mpeg_scale_factors(PORT_SIGNATURE);

/* Original 0x405f70(eax = decoder, edx = resync flag, ecx = output; stack: the output size and a
 * pointer for the sample count; ret 8): decode one MPEG audio frame. Returns -1 for an output
 * below 0x1200 bytes or a failed resync (0x405e00), 1 when the frame is not all buffered (the
 * header is read first: 0x405f30 and 0x404480, its size +0x58 into +0xc). Otherwise the frame is
 * copied from the reader (+4: data, length, position; refilled by 0x405ea0) into the next of the
 * two buffers at +0x25c (0x51f014, bit position 0x51f018), the count cleared, 0x404610 run when
 * +0x30 is set, the frame decoded by 0x40a190 and its size moved to +0x10. Returns 0. */
uint32_t vertrix_port_mpeg_decode_frame(PORT_SIGNATURE);

/* Original 0x409f00(eax = dequantised samples, edx = output, ebx = channel, ecx = granule): the
 * MPEG layer III hybrid synthesis of one channel. The channel's two overlap buffers (0x900 bytes
 * at the decoder's +0x125c, the side flag at +0x365c) swap; mixed blocks (+0x14) run their two
 * lowest subbands through the long IMDCT 0x4088e0, then every subband pair below +0x40 goes
 * through the short IMDCT 0x4095d0 (block type +0x10 == 2) or the long one with the block type's
 * windows. The remaining subbands up to 32 copy the previous overlap to the output (a stride of
 * 0x80) and clear the other buffer. */
uint32_t vertrix_port_mpeg_hybrid(PORT_SIGNATURE);

/* Original 0x407280(eax = side info, edx = channels, ebx = the stereo gain shift, ecx = sample
 * rate index; stack: the mode, 3 for mono; ret 4): read the MPEG layer III side info of one
 * granule through the bit readers 0x404610, 0x404680 and 0x4046e0. Each channel's 0xd0-byte
 * record gets the part sizes, big values (at most 0x120), the global gain as a pointer into the
 * table 0x523698, the scale factor compression, the window switching fields or the region
 * bounds (the band table 0x4f5918), the preflag and the scale factor scale. */
uint32_t vertrix_port_mpeg_side_info(PORT_SIGNATURE);

/* Original 0x4095d0(eax = samples, edx = previous block, ebx = overlap, ecx = window; stack:
 * the output; ret 4): the MPEG layer III short-block IMDCT of one subband. The first six outputs
 * (a stride of 0x80) copy the previous block; the three 6-point transforms are straight-line
 * fixed-point arithmetic through the add 0x4d80a6, subtract 0x4d809c and multiply 0x4d8177,
 * windowed by ecx and overlapped into the output and the overlap buffer. No branches. */
uint32_t vertrix_port_mpeg_imdct_short(PORT_SIGNATURE);

/* Original 0x40a190(eax = frame header, edx = output, ebx = the output count): decode the
 * granules of one MPEG layer III frame. The side info is read (0x407280 for MPEG-1, 0x407020
 * for MPEG-2) and the main data located (0x4060e0, -1 ends the frame with 0). For each granule
 * the scale factors (0x407720 or 0x4074a0) and Huffman data (0x407830) of each channel are read
 * into 0x52c30c and 0x52cc0c; stereo frames get mid/side (header +0x34 bit 1) and intensity
 * (bit 0, 0x4083a0) processing, the larger big value count, and the single-channel copies.
 * Each channel then goes through 0x408800 and 0x409f00 and each of the 18 time slots through
 * the synthesis (0x4056c0, or 0x405720 for both channels). Returns the samples written. */
uint32_t vertrix_port_mpeg_decode_granules(PORT_SIGNATURE);

#endif
