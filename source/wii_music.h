#ifndef VERTRIX_WII_MUSIC_H
#define VERTRIX_WII_MUSIC_H
#include "sequencer.h"

typedef struct VertrixWiiMusic VertrixWiiMusic;
/* Module must outlive the stream. Frames must be a nonzero multiple of eight.
 * Output is stereo little-endian PCM16. ASND must already be initialized. */
VertrixWiiMusic *vertrix_wii_music_create(const VertrixSequenceModule *module, uint32_t rate,
                                          uint32_t master_gain, int interpolate, size_t frames);
/* Start once, with exclusive ownership of voice. Render two buffers before
 * starting playback. Volumes are explicit 0..255. */
int vertrix_wii_music_start(VertrixWiiMusic *music, int voice, unsigned left, unsigned right);
/* Call frequently from the main loop, never an interrupt. Returns 1 when a
 * buffer is submitted, 0 when none is needed/busy, -1 on failure. Busy retries
 * retain the rendered buffer without advancing the sequencer again. */
int vertrix_wii_music_pump(VertrixWiiMusic *music);
/* Stop owned voice before releasing buffers and player. NULL is safe. */
void vertrix_wii_music_free(VertrixWiiMusic *music);
#endif
