#ifndef VERTRIX_XM_H
#define VERTRIX_XM_H
#include "vf.h"
#include <stddef.h>
#include <stdint.h>

typedef struct
{
    uint8_t note;
    uint8_t instrument;
    uint8_t volume;
    uint8_t effect;
    uint8_t parameter;
} VertrixXmEvent;

/* Original packed/unpacked event decoder 0x40e690. Null data with zero size
 * means an empty pattern: zero event without cursor advance. Otherwise reads
 * one event and advances cursor. Truncation preserves both outputs. */
int vertrix_xm_event(const unsigned char *data, size_t size, size_t *cursor,
                     VertrixXmEvent *output);
/* Original 0x40ea45..0x40ea79 packed row skipping on pattern rebind.
 * Starts at byte zero, skips signed-positive rows/channels using the event
 * decoder. Empty patterns keep cursor zero. Truncation preserves output. */
int vertrix_xm_seek_row(const unsigned char *data, size_t size, int32_t row, int32_t channels,
                        size_t *cursor);
typedef struct
{
    char name[21];
    uint16_t song_length;
    uint16_t restart;
    uint16_t channels;
    uint16_t patterns;
    uint16_t instruments;
    uint16_t flags;
    uint16_t speed;
    uint16_t bpm;
    uint8_t order[256];
} VertrixXmHeader;

/* Original XM 1.04 header fields and limits from 0x411322..0x411448.
 * Read directly from VF; preserves output on unsupported/truncated input. */
int vertrix_xm_header(VertrixVf *archive, const char *name, VertrixXmHeader *output);

typedef struct
{
    uint16_t channels;
    uint16_t rows;
    uint16_t packed_size;
    unsigned char *packed;
} VertrixXmPattern;

/* Original pattern records 0x411594..0x41166c. Initialize output to zero.
 * Keeps original packed bytes; empty patterns use a null packed pointer.
 * Truncated event data fails before publishing output. */
int vertrix_xm_pattern_load(VertrixVf *archive, const char *name, uint32_t pattern,
                            VertrixXmPattern *output);
void vertrix_xm_pattern_free(VertrixXmPattern *pattern);
typedef struct
{
    char name[23];
    uint32_t byte_count;
    uint32_t loop_start;
    uint32_t loop_length;
    uint32_t loop_end;
    uint16_t base_frequency;
    uint8_t volume;
    int8_t finetune;
    uint8_t type;
    uint8_t panning;
    int8_t relative_note;
    uint8_t native_flags;
    unsigned char *samples;
    unsigned ready;
} VertrixXmSample;

/* Original sample metadata 0x411ad8..0x411b52 and delta conversion 0x411bac.
 * Instrument/sample indices are zero based. Owns signed PCM byte patterns;
 * sixteen-bit data stays explicitly LE. Applies the recovered software-mixer
 * interpolation guard in byte_count + 4 owned bytes. Initialize output to zero;
 * preserved on failure. */
int vertrix_xm_sample_load(VertrixVf *archive, const char *name, uint32_t instrument,
                           uint32_t sample, VertrixXmSample *output);
void vertrix_xm_sample_free(VertrixXmSample *sample);
typedef struct
{
    uint16_t tick;
    uint16_t value;
} VertrixXmEnvelopePoint;
typedef struct
{
    VertrixXmEnvelopePoint points[12];
    uint8_t count;
    uint8_t sustain;
    uint8_t loop_start;
    uint8_t loop_end;
    uint8_t flags;
} VertrixXmEnvelope;
typedef struct
{
    char name[23];
    uint8_t mapping[96];
    uint16_t samples;
    uint8_t waveform;
    uint8_t sweep;
    uint8_t depth;
    uint8_t rate;
    uint16_t fade_step;
    VertrixXmEnvelope volume;
    VertrixXmEnvelope pan;
} VertrixXmInstrument;
/* Original 0x4117e0..0x411a00 metadata normalization. For a zero-sample
 * header, carry supplies prior loader scratch metadata; NULL means initially
 * zero scratch. Header bytes remain original XM/VF data. Failure preserves output. */
int vertrix_xm_instrument_header(const uint8_t *data, size_t size, const VertrixXmInstrument *carry,
                                 VertrixXmInstrument *output);
/* Read an instrument directly from original VF XM bytes, replaying prior
 * headers to preserve empty-instrument scratch carry. initial is the scratch
 * state before this song (NULL means zero). Failure preserves output. */
int vertrix_xm_instrument_load(VertrixVf *archive, const char *name, uint32_t instrument,
                               const VertrixXmInstrument *initial, VertrixXmInstrument *output);
#endif
