#ifndef VERTRIX_SEQUENCER_H
#define VERTRIX_SEQUENCER_H
#include "mixer.h"
#include "xm.h"

typedef struct
{
    const unsigned char *data;
    size_t size;
    size_t cursor;
} VertrixSequenceReader;

/* Complete original 0x40e940 row advancement, including packed seeking and
 * per-channel 0x40e770 initialization. Patterns retain original VF bytes.
 * Returns the row decision 0..3, or -1 for invalid native storage. */
int vertrix_sequence_advance(uint16_t song_length, uint16_t restart, const uint8_t *orders,
                             size_t order_storage, const VertrixXmPattern *patterns,
                             uint16_t pattern_count, int32_t channels, int linear,
                             uint8_t module_flags, const VertrixMixerRowInstrumentView *instruments,
                             uint16_t instrument_count, VertrixMixerSequenceRow *sequence,
                             VertrixSequenceReader *reader, VertrixMixerRowState *rows,
                             size_t row_storage);
/* Apply complete volume-column dispatch to an initialized row. Row selection,
 * defaults and reset state are authoritative for shared channel fields; column
 * retains vibrato speed/depth and portamento speed/target between calls. */
int vertrix_sequence_volume(int32_t tick, VertrixMixerRowState *row,
                            VertrixMixerVolumeColumn *column);
/* Apply original 0x40e030 after effects, synchronizing row/reset fields
 * with persistent envelope state. Playback owns final output values and
 * envelope value/slope fields; row owns current flags and trigger resets. */
int vertrix_sequence_playback(const VertrixMixerPlaybackInstrument *instrument,
                              VertrixMixerRowState *row, VertrixMixerPlayback *playback);
/* Publish final playback outputs through complete original 0x40e8a0.
 * Caller supplies the selected sample handle and persistent sample offset.
 * Shared flags are cleared only after successful command publication. */
int vertrix_sequence_publish(uint32_t global_volume, int linear, uint32_t sample, uint32_t offset,
                             VertrixMixerRowState *row, VertrixMixerPlayback *playback,
                             VertrixMixerPublishCommand commands[7], size_t *count);
/* Execute final playback publication through the recovered mixer setters.
 * Sample is a one-based index in bindings; zero means absent. Invalid native
 * storage preserves row, playback, mixer channel and source binding. */
int vertrix_sequence_deliver(uint32_t global_volume, int linear, uint32_t output_rate,
                             uint32_t sample, uint32_t offset,
                             const VertrixMixerSampleBinding *bindings, size_t binding_count,
                             VertrixMixerRowState *row, VertrixMixerPlayback *playback,
                             VertrixMixerChannel *channel, const uint8_t **source);
typedef struct
{
    uint32_t slide_down;
    uint32_t slide_up;
    uint32_t tremolo_depth;
    uint32_t tremolo_speed;
    uint32_t sample_offset;
    uint8_t volume_slide;
    uint8_t pan_slide;
    uint8_t tremor;
    uint8_t extra_decrease;
    uint8_t extra_increase;
    uint8_t retrigger_transform;
    uint8_t retrigger_interval;
} VertrixSequenceChannelMemory;
/* Integrate main effects 0..10, 12, 25, 29, 30 and 33 with shared row/volume-column state.
 * Returns 1 on success; null storage or an unsupported effect returns 0
 * without mutation. No-op dispatch entries also return success. */
int vertrix_sequence_channel_effect(int32_t tick, int linear, VertrixMixerRowState *row,
                                    VertrixMixerVolumeColumn *column,
                                    VertrixSequenceChannelMemory *memory);
/* Main effects 11/13/15/16/17: pending pattern jump/break, speed/tempo
 * and global volume. Sequence flags are authoritative for shared global flags.
 * Unsupported effects or null storage reject without mutation. */
int vertrix_sequence_global_effect(int32_t tick, uint16_t song_length,
                                   const VertrixMixerRowState *row,
                                   VertrixMixerSequenceRow *sequence,
                                   VertrixMixerGlobalEffects *global);
/* Consume original post-envelope pending updates (0x40eb6e..0x40ebf3).
 * Global-volume changes mark every row/playback channel for publication.
 * Tempo output changes only when tempo_changed is set. No allocation. */
int vertrix_sequence_pending(VertrixMixerSequenceRow *sequence, VertrixMixerGlobalEffects *global,
                             uint32_t *delay, VertrixMixerRowState *rows,
                             VertrixMixerPlayback *playback, size_t channels, uint32_t *tempo,
                             int *tempo_changed);
/* Main effects 20/27: envelope-aware release and sample retrigger.
 * Instrument is the current row instrument; samples can retain another owner.
 * Retrigger preserves envelope/reset state except its byte counter. */
int vertrix_sequence_note_effect(int32_t tick, int linear,
                                 const VertrixMixerTriggerInstrument *instrument,
                                 VertrixMixerRowState *row, VertrixMixerVolumeColumn *column,
                                 VertrixSequenceChannelMemory *memory);
typedef struct
{
    VertrixMixerPatternLoop loop;
    uint8_t fine_decrease;
    uint8_t fine_increase;
    uint8_t glissando;
} VertrixSequenceExtendedMemory;
/* Complete extended effect 14 integration, preserving current row and
 * trigger-reset ownership. Invalid native storage rejects atomically. */
int vertrix_sequence_extended_effect(int32_t tick, int linear,
                                     const VertrixMixerTriggerInstrument *instrument,
                                     VertrixMixerRowState *row, VertrixMixerVolumeColumn *column,
                                     VertrixSequenceExtendedMemory *memory,
                                     VertrixMixerSequenceRow *sequence, uint32_t *delay);
/* Complete original main dispatcher 0x40dc50, all 36 entries and ignored
 * commands. Caller performs volume-column processing before this call.
 * Callback 35 receives current order/row on tick zero. No allocation. */
int vertrix_sequence_effect(int32_t tick, int linear, uint16_t song_length,
                            const VertrixMixerTriggerInstrument *instrument,
                            VertrixMixerRowState *row, VertrixMixerVolumeColumn *column,
                            VertrixSequenceChannelMemory *memory,
                            VertrixSequenceExtendedMemory *extended,
                            VertrixMixerSequenceRow *sequence, VertrixMixerGlobalEffects *global,
                            uint32_t *delay, VertrixMixerEffectCallback callback, void *context);
typedef struct
{
    VertrixMixerTriggerInstrument trigger;
    VertrixMixerPlaybackInstrument playback;
    uint32_t first_sample;
} VertrixSequenceInstrument;
typedef struct
{
    VertrixMixerPublishCommand commands[7];
    size_t count;
} VertrixSequencePublication;
/* Original tick body after row advancement: process all channels, consume
 * pending globals, then publish all channels. first_sample is a zero-based
 * binding offset; emitted sample handles are one-based. No allocation.
 * Invalid runtime metadata can fail after earlier channels have progressed.
 * Caller executes tempo/mixer commands and owns all sample/envelope storage. */
int vertrix_sequence_process(
    int linear, uint16_t song_length, const VertrixSequenceInstrument *instruments,
    uint16_t instrument_count, VertrixMixerSequenceRow *sequence, VertrixMixerGlobalEffects *global,
    uint32_t *delay, VertrixMixerRowState *rows, VertrixMixerVolumeColumn *columns,
    VertrixSequenceChannelMemory *memory, VertrixSequenceExtendedMemory *extended,
    VertrixMixerPlayback *playback, size_t channels, VertrixSequencePublication *publications,
    uint32_t *tempo, int *tempo_changed, VertrixMixerEffectCallback callback, void *context);
typedef struct
{
    uint16_t length;
    uint16_t restart;
    const uint8_t *orders;
    size_t order_storage;
    const VertrixXmPattern *patterns;
    uint16_t pattern_count;
    uint16_t instrument_count;
    const VertrixSequenceInstrument *instruments;
    const VertrixMixerRowInstrumentView *row_instruments;
    int linear;
    uint8_t module_flags;
} VertrixSequenceSong;
/* Complete original 0x40eb10 tick composition. Returns 0 already stopped,
 * 1 processed, -1 invalid runtime data. A stop set during row advancement
 * still finishes this tick, as in the original. Row advancement allocates
 * temporary storage; real-time suitability is not yet established. */
int vertrix_sequence_tick(const VertrixSequenceSong *song, VertrixMixerSequenceRow *sequence,
                          VertrixMixerGlobalEffects *global, uint32_t *delay,
                          VertrixSequenceReader *reader, VertrixMixerRowState *rows,
                          VertrixMixerVolumeColumn *columns, VertrixSequenceChannelMemory *memory,
                          VertrixSequenceExtendedMemory *extended, VertrixMixerPlayback *playback,
                          size_t channels, VertrixSequencePublication *publications,
                          uint32_t *tempo, int *tempo_changed, VertrixMixerEffectCallback callback,
                          void *context);
typedef struct
{
    VertrixSequenceInstrument instrument;
    VertrixMixerRowInstrumentView row;
    uint8_t mapping[96];
    VertrixMixerSamplePitch pitches[16];
    uint8_t volumes[16];
    uint8_t pans[16];
    VertrixMixerEnvelopePoint volume_points[12];
    VertrixMixerEnvelopePoint pan_points[12];
    VertrixMixerSampleBinding bindings[16];
} VertrixSequenceInstrumentStorage;
/* Bind recovered VF-loaded instrument/sample metadata to sequencer views.
 * Output contains internal pointers: keep it at a fixed address, do not copy.
 * PCM buffers remain owned by loaded samples and must outlive this storage.
 * Invalid metadata preserves output. No allocation or PCM conversion. */
int vertrix_sequence_instrument_bind(const VertrixXmInstrument *instrument,
                                     const VertrixXmSample *samples, size_t sample_count,
                                     uint32_t first_sample,
                                     VertrixSequenceInstrumentStorage *output);
typedef struct VertrixSequenceModule VertrixSequenceModule;
/* Own a complete module loaded directly from VF. Returned views remain valid
 * after archive closure and until module_free. module_flags is caller playback
 * policy; initial supplies pre-song instrument scratch. NULL on failure. */
VertrixSequenceModule *vertrix_sequence_module_load(VertrixVf *archive, const char *name,
                                                    uint8_t module_flags,
                                                    const VertrixXmInstrument *initial);
void vertrix_sequence_module_free(VertrixSequenceModule *module);
const VertrixXmHeader *vertrix_sequence_module_header(const VertrixSequenceModule *module);
const VertrixSequenceSong *vertrix_sequence_module_song(const VertrixSequenceModule *module);
const VertrixMixerSampleBinding *
vertrix_sequence_module_bindings(const VertrixSequenceModule *module, size_t *count);
const VertrixXmInstrument *vertrix_sequence_module_scratch(const VertrixSequenceModule *module);
/* Original 0x40ec40 successful song-start state and emitted pan/tempo
 * commands. Returns 0 success, 2 invalid native storage, 3 already active.
 * NULL pans selects original XM-loader default 127. Mixer slot allocation
 * and tick-callback registration remain caller responsibilities. */
int vertrix_sequence_start(const VertrixXmHeader *header, const uint8_t *pans,
                           VertrixMixerSequenceRow *sequence, VertrixMixerGlobalEffects *global,
                           uint32_t *delay, VertrixSequenceReader *reader,
                           VertrixMixerRowState *rows, VertrixMixerVolumeColumn *columns,
                           VertrixSequenceChannelMemory *memory,
                           VertrixSequenceExtendedMemory *extended, VertrixMixerPlayback *playback,
                           size_t storage, VertrixSequencePublication *publications,
                           uint32_t *tempo);
/* Execute per-channel publications against already selected mixer slots.
 * Validates native command storage/handles before mutation; original setter
 * rejection does not stop later commands. PCM ownership stays with bindings. */
int vertrix_sequence_execute(const VertrixMixerSampleBinding *bindings, size_t binding_count,
                             uint32_t output_rate, const VertrixSequencePublication *publications,
                             VertrixMixerChannel *channels, const uint8_t **sources, size_t count);
/* Accumulate original per-slot PCM traversal in channel order. Source bounds
 * come from module bindings, including their four-byte interpolation guards.
 * Preserves all channels/output on failure. Temporary allocation is used;
 * real-time suitability remains unverified. Capacity counts accumulator values. */
int vertrix_sequence_mix(const VertrixMixerSampleBinding *bindings, size_t binding_count,
                         uint32_t master_gain, int stereo, int interpolate,
                         VertrixMixerChannel *channels, const uint8_t *const *sources, size_t count,
                         int32_t *output, size_t frames, size_t output_capacity);
typedef struct VertrixSequencePlayer VertrixSequencePlayer;
/* Borrow an owned module for tempo-scheduled PCM accumulation. The module
 * must outlive the player. Native buffers/row processing still allocate during
 * render; hardware callback suitability is not established. */
VertrixSequencePlayer *vertrix_sequence_player_create(const VertrixSequenceModule *module,
                                                      uint32_t output_rate, uint32_t master_gain,
                                                      int stereo, int interpolate);
void vertrix_sequence_player_free(VertrixSequencePlayer *player);
/* Clear and fill interleaved signed accumulators using original 0x40c5c0
 * tick-before-mix scheduling. Capacity counts values. Runtime failure can
 * leave earlier batches progressed; valid modules/configuration are required. */
int vertrix_sequence_player_mix(VertrixSequencePlayer *player, int32_t *output, size_t frames,
                                size_t capacity);
/* Render original unsigned PCM8 or little-endian signed PCM16. Scratch capacity
 * counts accumulator values; output capacity counts bytes. Caller owns both
 * buffers, which must not overlap. Invalid capacity does not advance playback. */
int vertrix_sequence_player_pcm(VertrixSequencePlayer *player, size_t frames, int sixteen_bit,
                                int32_t *scratch, size_t scratch_capacity, uint8_t *output,
                                size_t output_capacity);
int vertrix_sequence_player_state(const VertrixSequencePlayer *player,
                                  VertrixMixerSequenceRow *sequence,
                                  VertrixMixerGlobalEffects *global, uint32_t *period,
                                  uint32_t *phase);
#endif
