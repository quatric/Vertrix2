#ifndef VERTRIX_AUDIO_H
#define VERTRIX_AUDIO_H
#include "vf.h"

typedef struct
{
    uint32_t sample_rate;
    uint32_t sample_count;
    unsigned char *samples;
} VertrixPcm8;

/* Original WAV effects are PCM, mono, unsigned eight-bit samples.
 * Reads RIFF chunks directly from VF without extraction or resampling.
 * Initialize output to zero. Invalid/unsupported files preserve output. */
int vertrix_audio_pcm8(VertrixVf *archive, const char *name, VertrixPcm8 *output);
void vertrix_pcm8_free(VertrixPcm8 *audio);
typedef struct
{
    uint16_t format;
    uint16_t channels;
    uint32_t sample_rate;
    uint32_t byte_rate;
    uint16_t block_align;
    uint16_t bits_per_sample;
} VertrixAudioFormat;

/* Original output builder 0x410ffd..0x41106a (after device capabilities).
 * Flag bit zero selects 16-bit/stereo; rate is the original config word.
 * Describes original output; this does not select Wii hardware output rate. */
VertrixAudioFormat vertrix_audio_output_format(uint8_t flag_4, uint8_t flag_5, uint16_t rate);
/* Original buffer sizing 0x41108a..0x4110b3, stereo branch 0x41111e.
 * Takes floor(rate/20) sample frames, converts to bytes, rounds up to 16.
 * A zero rate produces zero bytes, as in the original configuration path. */
uint32_t vertrix_audio_buffer_bytes(uint8_t flag_4, uint8_t flag_5, uint16_t rate);
/* Original tracker sample delta decoding 0x411280. Cumulative unsigned
 * byte/LE-word sums wrap at 8/16 bits. Odd final byte is untouched in word mode.
 * Each call starts its accumulator at zero, matching one sample resource. */
int vertrix_audio_delta_decode(unsigned char *samples, size_t byte_count, int sixteen_bit);
/* Original software-mixer sample update 0x40c990. Forward-loop flag 0x10
 * copies four bytes from loop start to loop end; otherwise an update reaching
 * byte_count writes four zero guard bytes at the end. Range failures preserve
 * storage. updated_offset + updated_bytes uses original uint32 wrapping. */
int vertrix_audio_sample_guard(unsigned char *samples, size_t capacity, uint32_t byte_count,
                               uint32_t loop_start, uint32_t loop_end, uint8_t native_flags,
                               uint32_t updated_offset, uint32_t updated_bytes);
#endif
