#ifndef VERTRIX_MIXER_H
#define VERTRIX_MIXER_H
#include <stddef.h>
#include <stdint.h>

typedef struct
{
    uint32_t position;
    uint32_t loop_start;
    uint32_t loop_end;
    uint8_t flags;
} VertrixMixerCursor;

/* Original successful sample attachment 0x40c9d0..0x40ca60 geometry.
 * Byte offsets become sample positions for 16-bit data, then 12-fraction-bit
 * fixed point. Flags: stopped 1, sixteen-bit 2, looping 4, ping-pong 8.
 * Preserves original 32-bit wrapping and signed right shift semantics.
 * Slot validity, sample ownership and source pointer binding are separate. */
VertrixMixerCursor vertrix_mixer_cursor(uint32_t byte_count, uint32_t loop_start, uint32_t loop_end,
                                        uint8_t native_sample_flags);
/* Original 0x40cb10 playback step: frequency 512..524288 Hz, rounded
 * unsigned fixed-point division by output rate. Invalid input preserves output.
 * Native zero-rate rejection avoids the original divide-by-zero fault. */
int vertrix_mixer_step(uint32_t frequency, uint32_t output_rate, uint32_t *output);
typedef struct
{
    uint8_t left;
    uint8_t right;
} VertrixMixerGains;

/* Original noninterpolated stereo kernels 0x401328 and 0x402c18.
 * Volume is the stored channel value (original public volume divided by two).
 * Valid public volume 0..64 therefore gives stored volume 0..32. */
int vertrix_mixer_stereo_gains(uint32_t stored_volume, uint8_t pan, VertrixMixerGains *output);
/* Original 0x40c7d0 signed PCM8 lookup-table value. Table row 0..64,
 * master gain 0..256; mono halves master gain before multiplication.
 * Negative products round toward negative infinity, matching x86 SAR. */
int vertrix_mixer_pcm8_value(uint8_t sample, uint32_t table_row, uint32_t master_gain, int stereo,
                             int32_t *output);
/* Original variants 0x401010, 0x401054: conversion from signed 32-bit accumulation.
 * Emits unsigned PCM8 or signed little-endian PCM16 bytes. Output capacity is
 * checked before writing; zero samples is a native no-op. */
int vertrix_mixer_output(const int32_t *samples, size_t count, int sixteen_bit, uint8_t *output,
                         size_t capacity);
typedef struct
{
    uint32_t position;
    uint8_t last_sample;
} VertrixMixerReadState;

/* Original 0x40109c: noninterpolated PCM8 mono kernel. Accumulates into
 * existing signed 32-bit samples with wrapping. Caller handles loop boundaries.
 * The original prefetches the sample at the final position; it must be readable.
 * Invalid bounds preserve destination and state; zero frames is a native no-op. */
int vertrix_mixer_pcm8_mono(const uint8_t *samples, size_t sample_count, uint32_t step,
                            uint32_t stored_volume, uint32_t master_gain,
                            VertrixMixerReadState *state, int32_t *output, size_t frames,
                            size_t output_capacity);
/* Original 0x401328: noninterpolated PCM8 stereo kernel. Same bounded
 * traversal contract as mono; capacity counts interleaved 32-bit values. */
int vertrix_mixer_pcm8_stereo(const uint8_t *samples, size_t sample_count, uint32_t step,
                              uint32_t stored_volume, uint32_t master_gain, uint8_t pan,
                              VertrixMixerReadState *state, int32_t *output, size_t frames,
                              size_t output_capacity);
/* Original PCM16 kernels 0x402934/0x402c18 read the high byte of each
 * little-endian signed sample. Position and step count samples, not bytes.
 * Same traversal/prefetch contract as PCM8. */
/* Original 0x402934: complete callable routine; tools/verify_mixer_pcm16_mono.py. */
int vertrix_mixer_pcm16_mono(const uint8_t *samples, size_t byte_count, uint32_t step,
                             uint32_t stored_volume, uint32_t master_gain,
                             VertrixMixerReadState *state, int32_t *output, size_t frames,
                             size_t output_capacity);
/* Original noninterpolated PCM16 stereo kernel 0x402c18. Same bounded
 * traversal contract as mono; capacity counts interleaved 32-bit values. */
/* Original 0x402c18: complete callable routine; tools/verify_mixer_pcm16_stereo.py. */
int vertrix_mixer_pcm16_stereo(const uint8_t *samples, size_t byte_count, uint32_t step,
                               uint32_t stored_volume, uint32_t master_gain, uint8_t pan,
                               VertrixMixerReadState *state, int32_t *output, size_t frames,
                               size_t output_capacity);
/* Original interpolation recurrence used for |step| < 4096.
 * Quantized weight 0..31 is abs(step) >> 7. The returned raw signed PCM8
 * bit pattern becomes channel byte +23 for the next output sample. */
int vertrix_mixer_filter(uint8_t previous, uint8_t sample, uint32_t weight, uint8_t *output);
/* Original 0x401cd0: complete PCM8 mono interpolated kernel, including
 * signed |step| >= 4096 fallback. Small-step mode reads frames samples,
 * persists filtered byte, and does not prefetch the final position. */
int vertrix_mixer_pcm8_mono_interpolated(const uint8_t *samples, size_t sample_count, uint32_t step,
                                         uint32_t stored_volume, uint32_t master_gain,
                                         VertrixMixerReadState *state, int32_t *output,
                                         size_t frames, size_t output_capacity);
/* Original 0x401f9c stereo interpolated kernel. Same small-step and
 * fallback contracts as mono; capacity counts interleaved 32-bit values. */
int vertrix_mixer_pcm8_stereo_interpolated(const uint8_t *samples, size_t sample_count,
                                           uint32_t step, uint32_t stored_volume,
                                           uint32_t master_gain, uint8_t pan,
                                           VertrixMixerReadState *state, int32_t *output,
                                           size_t frames, size_t output_capacity);
/* Original 0x4036c8/0x4039e4 PCM16 interpolation, using high bytes
 * of little-endian samples; position/step count samples, source size is bytes. */
int vertrix_mixer_pcm16_mono_interpolated(const uint8_t *samples, size_t byte_count, uint32_t step,
                                          uint32_t stored_volume, uint32_t master_gain,
                                          VertrixMixerReadState *state, int32_t *output,
                                          size_t frames, size_t output_capacity);
/* Original 0x4039e4 stereo interpolated kernel. Same small-step and
 * fallback contracts as mono; capacity counts interleaved 32-bit values. */
int vertrix_mixer_pcm16_stereo_interpolated(const uint8_t *samples, size_t byte_count,
                                            uint32_t step, uint32_t stored_volume,
                                            uint32_t master_gain, uint8_t pan,
                                            VertrixMixerReadState *state, int32_t *output,
                                            size_t frames, size_t output_capacity);
/* One boundary decision from original 0x40c483..0x40c510.
 * Returns 0 stopped, 1 ready to mix, 2 wrapped/reflected (check again).
 * Boundaries compare signed 32-bit positions; arithmetic wraps.
 * Flag 0x10 selects reverse traversal. Null cursor returns -1. */
int vertrix_mixer_boundary(VertrixMixerCursor *cursor);
typedef struct
{
    uint32_t frames;
    uint32_t signed_step;
} VertrixMixerBatch;

/* Original 0x40c518..0x40c547 batch arithmetic for a ready cursor.
 * Positive step magnitude 1..INT32_MAX. Preserves unsigned product wrapping,
 * signed division and reverse-step negation. Does not repair invalid geometry. */
int vertrix_mixer_batch(const VertrixMixerCursor *cursor, uint32_t step, uint32_t remaining_frames,
                        VertrixMixerBatch *output);
/* Dispatch corresponding to original channel flag 2 and mixer stereo/
 * interpolation configuration. Source size is bytes for both sample depths.
 * Step is already signed for the current traversal direction. */
int vertrix_mixer_accumulate(const uint8_t *samples, size_t byte_count, uint32_t step,
                             uint32_t stored_volume, uint32_t master_gain, uint8_t pan,
                             uint8_t channel_flags, int stereo, int interpolate,
                             VertrixMixerReadState *state, int32_t *output, size_t frames,
                             size_t output_capacity);
typedef struct
{
    VertrixMixerCursor cursor;
    uint32_t step;
    uint8_t volume;
    uint8_t pan;
    uint8_t last_sample;
} VertrixMixerChannel;

/* Original 0x40c460 continuous single-channel traversal. Destination capacity
 * counts accumulator values; frames count mono/stereo frames. Rejects invalid
 * source traversal transactionally. Caller owns separate valid buffers. */
int vertrix_mixer_channel(const uint8_t *samples, size_t byte_count, uint32_t master_gain,
                          int stereo, int interpolate, VertrixMixerChannel *channel,
                          int32_t *output, size_t frames, size_t output_capacity);
typedef struct
{
    uint32_t values;
    uint32_t phase;
    int tick;
} VertrixMixerTickBatch;

/* Original 0x40c5d8..0x40c628 scheduling with a tick callback enabled.
 * Counts accumulator values (two per stereo frame), rounded in 64-value
 * chunks. Tick is due before mixing this batch. Zero period is rejected. */
int vertrix_mixer_tick_batch(uint32_t period, uint32_t phase, uint32_t remaining_values,
                             VertrixMixerTickBatch *output);
/* Original 0x40cd40: tempo setter: BPM 32..255, period in accumulator
 * values. Stereo doubles the rate before wrapped multiplication by five. */
int vertrix_mixer_tempo(uint32_t bpm, uint32_t output_rate, int stereo, uint32_t *period);
/* Original 0x40ce20 pitch-to-frequency conversion. Nonpositive periods
 * return zero. Linear mode uses original table and x86 masked shift count. */
uint32_t vertrix_mixer_pitch(int32_t period, int linear);
/* Original 0x40ce80 note + relative-note + finetune conversion.
 * Arguments retain original signed 32-bit register bit patterns. */
uint32_t vertrix_mixer_note_period(int32_t note, int32_t relative_note, int32_t finetune,
                                   int linear);
/* Original 0x40cef0: arpeggio effect. Parameter zero leaves period/flags
 * unchanged. Tick uses signed remainder modulo three; nonpositive remainders
 * select the base note. Output pointers are required. */
int vertrix_mixer_arpeggio(uint8_t parameter, int32_t tick, uint8_t note, int32_t relative_note,
                           int32_t finetune, int linear, uint32_t *period, uint8_t *update_flags);
typedef struct
{
    uint32_t base_period;
    uint32_t output_period;
    uint32_t amount;
    uint8_t update_flags;
} VertrixMixerSlide;

/* Original variants 0x40cf50, 0x40cfa0: pitch slides. Tick zero remembers a nonzero
 * parameter times four; later ticks apply memory and mark pitch dirty.
 * Increasing period clamps to 0x7cff; decreasing period clamps to one. */
int vertrix_mixer_pitch_slide(uint8_t parameter, int32_t tick, int increasing_period,
                              VertrixMixerSlide *state);
typedef struct
{
    uint32_t base_period;
    uint32_t output_period;
    uint32_t speed;
    uint32_t target;
    uint8_t update_flags;
} VertrixMixerPortamento;
/* Original 0x40cff0 target-note slide. Tick zero sets target, remembers
 * nonzero speed, and clears original flags 1 and 8. Later ticks move pitch. */
int vertrix_mixer_portamento(uint8_t parameter, int32_t tick, uint8_t note, int32_t relative_note,
                             int32_t finetune, int linear, VertrixMixerPortamento *state);
typedef struct
{
    uint32_t base_period;
    uint32_t output_period;
    uint32_t phase;
    uint32_t depth;
    uint32_t speed;
    uint8_t waveform;
    uint8_t update_flags;
} VertrixMixerVibrato;
/* Original 0x40d090 pitch vibrato, including tick-zero nibble memory,
 * original waveform lookup, signed output clamps and phase wrapping. */
int vertrix_mixer_vibrato(uint8_t parameter, int32_t tick, VertrixMixerVibrato *state);
/* Original 0x40d170 fine vibrato: same memory/waveform/phase behavior,
 * but signed magnitude product shifts seven bits rather than five. */
int vertrix_mixer_fine_vibrato(uint8_t parameter, int32_t tick, VertrixMixerVibrato *state);
typedef struct
{
    uint32_t base_volume;
    uint32_t output_volume;
    uint8_t parameter_memory;
    uint8_t update_flags;
} VertrixMixerVolumeSlide;
/* Original 0x40d250 volume slide: upper nibble takes precedence.
 * Tick zero remembers nonzero parameter; later ticks set volume dirty bit 2. */
int vertrix_mixer_volume_slide(uint8_t parameter, int32_t tick, VertrixMixerVolumeSlide *state);
/* Original combined effects 0x40d2d0/0x40d300. Pitch-state flags are
 * authoritative shared channel flags; both returned states receive them.
 * Tick zero only updates volume memory (portamento also clears bits 1/8). */
/* Original 0x40d2d0: complete callable routine; tools/verify_mixer_combined.py. */
int vertrix_mixer_portamento_volume(uint8_t parameter, int32_t tick, VertrixMixerPortamento *pitch,
                                    VertrixMixerVolumeSlide *volume);
/* Original 0x40d300: complete callable routine; tools/verify_mixer_combined.py. */
int vertrix_mixer_vibrato_volume(uint8_t parameter, int32_t tick, VertrixMixerVibrato *pitch,
                                 VertrixMixerVolumeSlide *volume);
typedef struct
{
    uint32_t base_volume;
    uint32_t output_volume;
    uint32_t phase;
    uint32_t depth;
    uint32_t speed;
    uint8_t waveform;
    uint8_t update_flags;
} VertrixMixerTremolo;
/* Original 0x40d330 volume modulation, using waveform bits 4..5. */
int vertrix_mixer_tremolo(uint8_t parameter, int32_t tick, VertrixMixerTremolo *state);
typedef enum
{
    VERTRIX_MIXER_SET_PAN,
    VERTRIX_MIXER_SET_SAMPLE_OFFSET,
    VERTRIX_MIXER_SET_VOLUME
} VertrixMixerSetEffect;

typedef struct
{
    uint32_t pan;
    uint32_t sample_offset;
    uint32_t base_volume;
    uint32_t output_volume;
    uint8_t update_flags;
} VertrixMixerSetState;
/* Original variants 0x40d410, 0x40d430, 0x40d490: tick-zero setters.
 * Nonzero ticks preserve all state. Invalid effect/null state rejects. */
int vertrix_mixer_set_effect(VertrixMixerSetEffect effect, uint8_t parameter, int32_t tick,
                             VertrixMixerSetState *state);
typedef struct
{
    uint32_t order;
    uint32_t row;
    uint8_t flags;
} VertrixMixerPatternChange;
/* Original variants 0x40d450, 0x40d4c0: order jump and decimal-nibble row break.
 * Only tick zero acts. Jump checks parameter against original song length.
 * Row break accepts all nibbles, including values above decimal nine. */
int vertrix_mixer_pattern_change(uint8_t parameter, int32_t tick, int row_break,
                                 uint16_t song_length, VertrixMixerPatternChange *state);
/* Original extended fine-slide cases 0x40d55f/0x40d5a4. Only tick zero
 * acts: remember nonzero low nibble times four, then apply immediately.
 * Amount represents original byte memory; values above 255 reject. */
int vertrix_mixer_fine_slide(uint8_t parameter, int32_t tick, int increasing_period,
                             VertrixMixerSlide *state);
/* Original extended selectors 4/7 waveform nibble setters.
 * Tick zero replaces vibrato low nibble or tremolo high nibble, preserving
 * the other nibble. Parameter must contain selector 4 or 7. */
int vertrix_mixer_waveform_control(uint8_t parameter, int32_t tick, uint8_t *waveform);
typedef struct
{
    int32_t finetune;
    uint32_t output_period;
    uint8_t update_flags;
} VertrixMixerFinetune;
/* Original extended selector 5 at 0x40d62d. Tick zero converts low nibble
 * to signed finetune -128..112, updates output pitch, and sets dirty bit 1. */
int vertrix_mixer_finetune_control(uint8_t parameter, int32_t tick, uint8_t note,
                                   int32_t relative_note, int linear, VertrixMixerFinetune *state);
typedef struct
{
    uint32_t start_row;
    uint32_t remaining;
} VertrixMixerPatternLoop;
/* Original extended selector 6 at 0x40d66a. Tick zero records loop start
 * for low nibble zero, otherwise initializes/decrements repeat memory and
 * requests the original current order and saved row while count is nonzero. */
int vertrix_mixer_pattern_loop(uint8_t parameter, int32_t tick, uint32_t current_order,
                               uint32_t current_row, VertrixMixerPatternLoop *loop,
                               VertrixMixerPatternChange *change);
/* Original extended note-cut case 0x40d7ec: zero base/output volume and
 * set dirty bit 2 exactly when signed tick equals the low nibble. */
int vertrix_mixer_note_cut(uint8_t parameter, int32_t tick, VertrixMixerVolumeSlide *state);
/* Original 0x40e640: note release. Clears active byte; instrument volume
 * envelope flag 1 preserves volume/flags, absent envelope clears volume and
 * sets flags 0x12, absent instrument sets flag 0x10 without clearing volume. */
int vertrix_mixer_note_release(int instrument_present, uint8_t envelope_flags, uint8_t *active,
                               VertrixMixerVolumeSlide *state);
/* Original extended selector 14 at 0x40d842. At tick zero, if pending
 * flag 4 is clear, stores low nibble + 1 and sets flag 4. */
int vertrix_mixer_pattern_delay(uint8_t parameter, int32_t tick, uint32_t *delay,
                                uint8_t *sequencer_flags);
/* Original extended fine-volume selectors 10/11 at 0x40d76d/0x40d7a7.
 * Only tick zero acts; low nibble changes volume immediately, without
 * altering ordinary volume-slide memory. */
int vertrix_mixer_fine_volume(uint8_t parameter, int32_t tick, VertrixMixerVolumeSlide *state);
/* Original extended selector 3 at 0x40d5ec. Tick zero stores the low
 * nibble in original channel byte +61; other ticks preserve it.
 * Its later pitch-quantization use remains separate. */
int vertrix_mixer_glissando_control(uint8_t parameter, int32_t tick, uint8_t *mode);
/* Original extended selector 8 at 0x40d70a. Tick zero sets pan to low
 * nibble times sixteen (0..240) and marks pan dirty. */
int vertrix_mixer_extended_pan(uint8_t parameter, int32_t tick, VertrixMixerSetState *state);
typedef struct
{
    uint32_t vibrato_phase;
    uint32_t tremolo_phase;
    uint32_t fade_volume;
    uint32_t fade_step;
    uint32_t volume_tick;
    uint32_t volume_point;
    uint32_t pan_tick;
    uint32_t pan_point;
    uint32_t instrument_phase;
    uint32_t instrument_amount;
    uint32_t instrument_step;
    uint8_t waveform;
    uint8_t state_112;
    uint8_t state_114;
    uint8_t state_115;
} VertrixMixerTriggerReset;
/* Original 0x40df20: complete reset. Null instrument preserves instrument
 * dependent fields. Envelope flags and instrument bytes are explicit inputs. */
int vertrix_mixer_trigger_reset(int instrument_present, uint8_t volume_flags, uint8_t pan_flags,
                                uint16_t fade_step, uint8_t sweep, uint8_t depth,
                                VertrixMixerTriggerReset *state);
typedef struct
{
    int8_t relative_note;
    int8_t finetune;
} VertrixMixerSamplePitch;
typedef struct
{
    uint32_t selected_sample;
    int32_t relative_note;
    int32_t finetune;
    uint32_t base_period;
    uint32_t output_period;
    uint8_t note;
    uint8_t active;
    uint8_t mapping;
    uint8_t effect;
    uint8_t volume_command;
    uint8_t flags;
} VertrixMixerSampleSelection;
/* Original 0x40e580. Note mapping has 96 entries. Selected sample is a
 * native index, with UINT32_MAX representing the original null pointer. */
int vertrix_mixer_select_sample(int instrument_present, const uint8_t *mapping,
                                const VertrixMixerSamplePitch *samples, uint16_t sample_count,
                                int linear, VertrixMixerSampleSelection *state);
typedef struct
{
    const uint8_t *mapping;
    const VertrixMixerSamplePitch *samples;
    uint16_t sample_count;
    uint16_t fade_step;
    uint8_t volume_flags;
    uint8_t pan_flags;
    uint8_t sweep;
    uint8_t depth;
} VertrixMixerTriggerInstrument;
/* Complete 0x40e670, selecting the sample then resetting envelopes even
 * when the note is invalid. Null instrument means no instrument present. */
int vertrix_mixer_trigger(const VertrixMixerTriggerInstrument *instrument, int linear,
                          VertrixMixerSampleSelection *selection, VertrixMixerTriggerReset *reset);
/* Extended selectors 9/D at 0x40d730/0x40d818. Retrigger acts on tick zero
 * or signed tick multiples of a nonzero low nibble. Delay clears flags to
 * bit 0x10 every tick, triggers exactly at the low nibble, then sets bits 6. */
int vertrix_mixer_timed_trigger(uint8_t parameter, int32_t tick,
                                const VertrixMixerTriggerInstrument *instrument, int linear,
                                VertrixMixerSampleSelection *selection,
                                VertrixMixerTriggerReset *reset);
typedef struct
{
    uint16_t tick;
    uint16_t value;
} VertrixMixerEnvelopePoint;
typedef struct
{
    uint32_t tick;
    uint32_t value;
    uint32_t point;
    uint32_t slope;
} VertrixMixerEnvelopeState;
/* Enabled envelope advancement from 0x40e070 and 0x40e122. The caller
 * supplies storage count separately from the original byte point count. */
int vertrix_mixer_envelope_step(const VertrixMixerEnvelopePoint *points, size_t storage_count,
                                uint8_t point_count, uint8_t flags, uint8_t sustain,
                                uint8_t loop_start, uint8_t loop_end, uint8_t active,
                                VertrixMixerEnvelopeState *state);
typedef struct
{
    uint32_t volume;
    uint32_t step;
    uint8_t flags;
} VertrixMixerFade;
/* Released-note fade from 0x40e038..0x40e05b. */
int vertrix_mixer_fade_step(int instrument_present, uint8_t active, VertrixMixerFade *state);
/* Output scaling at 0x40e0f2/0x40e3c3 and 0x40e1a4/0x40e4ff.
 * Multiplication wraps before arithmetic shifts, as in the original. */
int vertrix_mixer_envelope_volume(uint32_t base, uint32_t fade, uint32_t envelope, int enabled,
                                  uint32_t *output, uint8_t *flags);
int vertrix_mixer_envelope_pan(uint32_t base, uint32_t envelope, int enabled, uint32_t *output,
                               uint8_t *flags);
typedef struct
{
    uint32_t phase;
    uint32_t amount;
    uint32_t step;
    uint32_t period;
    uint32_t output_period;
    uint8_t active;
    uint8_t flags;
} VertrixMixerInstrumentVibrato;
/* Original 0x40e1db..0x40e57a, including absent/zero-depth bypass. */
int vertrix_mixer_instrument_vibrato(int instrument_present, uint8_t waveform, uint8_t depth,
                                     uint8_t rate, VertrixMixerInstrumentVibrato *state);
typedef struct
{
    const VertrixMixerEnvelopePoint *points;
    size_t storage_count;
    uint8_t point_count;
    uint8_t flags;
    uint8_t sustain;
    uint8_t loop_start;
    uint8_t loop_end;
} VertrixMixerEnvelope;
typedef struct
{
    VertrixMixerEnvelope volume;
    VertrixMixerEnvelope pan;
    uint8_t waveform;
    uint8_t depth;
    uint8_t rate;
} VertrixMixerPlaybackInstrument;
typedef struct
{
    uint32_t base_volume;
    uint32_t output_volume;
    uint32_t base_pan;
    uint32_t output_pan;
    uint32_t fade_volume;
    uint32_t fade_step;
    VertrixMixerEnvelopeState volume;
    VertrixMixerEnvelopeState pan;
    VertrixMixerInstrumentVibrato vibrato;
} VertrixMixerPlayback;
/* Complete original 0x40e030 update, in original fade/envelope/vibrato order.
 * Active and update flags live in vibrato. Invalid storage rejects atomically. */
/* Original 0x40e030: complete callable routine; tools/verify_mixer_playback_tick.py. */
int vertrix_mixer_playback_tick(const VertrixMixerPlaybackInstrument *instrument,
                                VertrixMixerPlayback *state);
enum
{
    VERTRIX_MIXER_PUBLISH_SAMPLE,
    VERTRIX_MIXER_PUBLISH_OFFSET,
    VERTRIX_MIXER_PUBLISH_STOP,
    VERTRIX_MIXER_PUBLISH_FREQUENCY,
    VERTRIX_MIXER_PUBLISH_VOLUME,
    VERTRIX_MIXER_PUBLISH_PAN,
    VERTRIX_MIXER_PUBLISH_START
};
typedef struct
{
    uint32_t value;
    uint8_t kind;
} VertrixMixerPublishCommand;
typedef struct
{
    uint32_t sample;
    uint32_t offset;
    uint32_t period;
    uint32_t volume;
    uint32_t pan;
    uint8_t flags;
} VertrixMixerPublishState;
/* Complete 0x40e8a0 command ordering. Sample zero means absent; other
 * values are caller-defined handles. Commands still require mixer delivery. */
/* Original 0x40e8a0: complete callable routine; tools/verify_mixer_publish.py. */
int vertrix_mixer_publish(uint32_t global_volume, int linear, VertrixMixerPublishState *state,
                          VertrixMixerPublishCommand commands[7], size_t *count);
/* Execute non-attachment publication commands using original setters
 * 0x40ca70..0x40cbb0. Returns 0 success, 1 null channel, 2 invalid value/kind.
 * Sample attachment requires a separately bound descriptor. */
int vertrix_mixer_command(uint8_t kind, uint32_t value, uint32_t output_rate,
                          VertrixMixerChannel *channel);
typedef struct
{
    const uint8_t *samples;
    uint32_t byte_count;
    uint32_t loop_start;
    uint32_t loop_end;
    uint8_t flags;
} VertrixMixerSampleBinding;
/* Original 0x40c9d0: complete routine for an already-selected channel. Rebinds the
 * source and cursor while preserving step, volume, pan and interpolation cache.
 * Returns 0 success, 1 invalid native storage. Does not take buffer ownership. */
int vertrix_mixer_attach(const VertrixMixerSampleBinding *sample, VertrixMixerChannel *channel,
                         const uint8_t **source);
/* Publish and execute original 0x40e8a0 against a selected channel.
 * Sample handles are one-based indices in bindings; zero means absent.
 * Original setter failures do not abort later commands. Invalid native
 * storage rejects before any state changes; output_rate must be nonzero. */
int vertrix_mixer_deliver(uint32_t global_volume, int linear, uint32_t output_rate,
                          const VertrixMixerSampleBinding *bindings, size_t binding_count,
                          VertrixMixerPublishState *state, VertrixMixerChannel *channel,
                          const uint8_t **source);
typedef struct
{
    uint32_t base_period;
    uint32_t output_period;
    uint8_t volume_command;
    uint8_t effect;
    uint8_t parameter;
    uint8_t flags;
} VertrixMixerRowEffects;
/* Original 0x40e77f..0x40e7ba row transition. Restores base pitch when
 * leaving vibrato/combined vibrato or a nonzero arpeggio for another effect. */
int vertrix_mixer_row_effects(uint8_t volume_command, uint8_t effect, uint8_t parameter,
                              VertrixMixerRowEffects *state);
typedef struct
{
    uint32_t selected;
    uint8_t number;
} VertrixMixerRowInstrument;
/* Original 0x40e7ba..0x40e7f8. Native selected is the one-based instrument
 * handle; zero or out-of-range incoming numbers preserve prior selection. */
int vertrix_mixer_row_instrument(uint8_t number, uint16_t instrument_count,
                                 VertrixMixerRowInstrument *state);
typedef struct
{
    uint32_t base_volume;
    uint32_t output_volume;
    uint32_t pan;
    uint8_t flags;
} VertrixMixerRowDefaults;
/* Original 0x40e82c..0x40e89d. A nonzero incoming instrument and present
 * sample copy default volume. Module flag 0x80 suppresses default pan. */
int vertrix_mixer_row_defaults(uint8_t incoming_instrument, int sample_present,
                               uint8_t sample_volume, uint8_t sample_pan, uint8_t module_flags,
                               VertrixMixerRowDefaults *state);
typedef struct
{
    VertrixMixerTriggerInstrument trigger;
    const uint8_t *sample_volumes;
    const uint8_t *sample_pans;
} VertrixMixerRowInstrumentView;
typedef struct
{
    VertrixMixerRowInstrument instrument;
    uint32_t sample_instrument;
    VertrixMixerSampleSelection selection;
    VertrixMixerTriggerReset reset;
    VertrixMixerRowDefaults defaults;
    uint8_t parameter;
} VertrixMixerRowState;
/* Original 0x40e770: complete routine after event decoding. Event order is note,
 * instrument, volume command, effect, parameter. Sample ownership is tracked
 * separately because changing instruments can preserve the previous sample.
 * Selection flags are authoritative; invalid native storage rejects atomically. */
int vertrix_mixer_row(const uint8_t event[5], int linear, uint8_t module_flags,
                      const VertrixMixerRowInstrumentView *instruments, uint16_t instrument_count,
                      VertrixMixerRowState *state);
typedef struct
{
    uint32_t base_volume;
    uint32_t output_volume;
    uint32_t pan;
    uint32_t base_period;
    uint32_t output_period;
    uint32_t portamento_speed;
    uint32_t portamento_target;
    uint32_t vibrato_phase;
    uint32_t vibrato_depth;
    uint32_t vibrato_speed;
    uint8_t waveform;
    uint8_t flags;
} VertrixMixerVolumeColumn;
/* Original 0x40dc80: complete volume-column dispatch. Later B/F commands
 * invoke existing vibrato/portamento with the channel's effect parameter. */
int vertrix_mixer_volume_column(uint8_t command, uint8_t effect_parameter, int32_t tick,
                                VertrixMixerVolumeColumn *state);
typedef struct
{
    uint32_t speed;
    uint32_t tempo;
    uint32_t volume;
    uint32_t slide_memory;
    uint8_t flags;
} VertrixMixerGlobalEffects;
/* Original effects F/G/H at 0x40d880/0x40d8c0/0x40d8f0. Effect numbers
 * are 15/16/17. Tempo/volume dirty flags are pending sequencer work. */
/* Original variants 0x40d880, 0x40d8c0, 0x40d8f0: complete callable routines;
 * tools/verify_mixer_global_effects.py. */
int vertrix_mixer_global_effect(uint8_t effect, uint8_t parameter, int32_t tick,
                                VertrixMixerGlobalEffects *state);
typedef struct
{
    uint32_t pan;
    uint8_t memory;
    uint8_t flags;
} VertrixMixerPanSlide;
/* Main effect 25 at 0x40d9b0. Tick zero remembers nonzero parameters;
 * later ticks prioritize upper-nibble increase over lower-nibble decrease. */
/* Original 0x40d9b0: complete callable routine; tools/verify_mixer_pan_release.py. */
int vertrix_mixer_pan_slide(uint8_t parameter, int32_t tick, VertrixMixerPanSlide *state);
/* Main effect 20 at 0x40d990 releases exactly when signed tick equals
 * the full parameter byte, using the recovered envelope-aware release. */
/* Original 0x40d990: complete callable routine; tools/verify_mixer_pan_release.py. */
int vertrix_mixer_timed_release(uint8_t parameter, int32_t tick, int instrument_present,
                                uint8_t envelope_flags, uint8_t *active,
                                VertrixMixerVolumeSlide *state);
typedef struct
{
    uint32_t base_volume;
    uint32_t output_volume;
    uint8_t memory;
    uint8_t on;
    uint8_t remaining;
    uint8_t flags;
} VertrixMixerTremor;
/* Main effect 29, original 0x40db00. Updates its byte counter on every tick. */
/* Original 0x40db00: complete callable routine; tools/verify_mixer_tremor_extra_fine.py. */
int vertrix_mixer_tremor(uint8_t parameter, int32_t tick, VertrixMixerTremor *state);
typedef struct
{
    uint32_t base_period;
    uint32_t output_period;
    uint8_t decrease_memory;
    uint8_t increase_memory;
    uint8_t flags;
} VertrixMixerExtraFineSlide;
/* Main effect 33, original 0x40db70. Tick-zero selectors 1/2 change
 * period by the remembered low nibble, without the ordinary factor four. */
/* Original 0x40db70: complete callable routine; tools/verify_mixer_tremor_extra_fine.py. */
int vertrix_mixer_extra_fine_slide(uint8_t parameter, int32_t tick,
                                   VertrixMixerExtraFineSlide *state);
typedef struct
{
    uint32_t base_volume;
    uint32_t output_volume;
    uint32_t pan;
    uint8_t transform;
    uint8_t interval;
    uint8_t counter;
} VertrixMixerRetrigger;
/* Complete effect 27 at 0x40da20. Selection flags are shared channel flags.
 * Retrigger reselects the sample without resetting envelope state. */
/* Original 0x40da20: complete callable routine; tools/verify_mixer_retrigger.py. */
int vertrix_mixer_retrigger(uint8_t parameter, int32_t tick,
                            const VertrixMixerTriggerInstrument *instrument, int linear,
                            VertrixMixerSampleSelection *selection, VertrixMixerRetrigger *state);
typedef void (*VertrixMixerEffectCallback)(uint8_t parameter, uint32_t order, uint32_t row,
                                           void *context);
/* Original effect 35 at 0x40dc10. Callback runs only on tick zero. */
/* Original 0x40dc10: complete callable routine; tools/verify_mixer_effect_selection.py. */
void vertrix_mixer_effect_callback(uint8_t parameter, int32_t tick, uint32_t order, uint32_t row,
                                   VertrixMixerEffectCallback callback, void *context);
/* Original 0x40dc50 dispatch selection. Returns the active effect number
 * or -1 for ignored/no-op commands. This selects; execution remains separate. */
int vertrix_mixer_effect_select(uint8_t effect, uint8_t parameter);
typedef struct
{
    uint32_t tick;
    uint32_t speed;
    uint32_t delay;
    uint32_t tempo;
    uint8_t flags;
} VertrixMixerSequenceTick;
/* Original 0x40eb14..0x40eb3a. Returns -1 invalid, 0 stopped, 1 continue,
 * 2 invoke row advancement before channel effects. Does not reset tick itself. */
int vertrix_mixer_sequence_begin(VertrixMixerSequenceTick *state);
/* Original 0x40eb6e..0x40ebf3, after channel effects/envelopes. Consumes
 * delay and pending global updates. Tempo output is valid only if changed. */
int vertrix_mixer_sequence_pending(VertrixMixerSequenceTick *state, uint8_t *channel_flags,
                                   size_t channels, uint32_t *tempo, int *tempo_changed);
typedef struct
{
    uint32_t tick;
    uint32_t row;
    uint32_t rows;
    uint32_t pattern;
    uint32_t order;
    uint32_t pending_order;
    uint32_t pending_row;
    uint8_t flags;
} VertrixMixerSequenceRow;
/* Original 0x40e940 row/order/pattern decisions. Returns -1 invalid storage,
 * 0 delayed, 1 continue current pattern, 2 bind chosen pattern, 3 stopped.
 * Rebinding includes invalid pattern indices (original empty 64-row fallback).
 * Packed cursor positioning and channel row initialization remain separate. */
int vertrix_mixer_sequence_row(uint16_t song_length, uint16_t restart, const uint8_t *orders,
                               size_t order_storage, const uint16_t *pattern_rows,
                               uint16_t pattern_count, VertrixMixerSequenceRow *state);
#endif
