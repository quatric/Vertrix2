#ifndef VERTRIX_WII_AUDIO_H
#define VERTRIX_WII_AUDIO_H
#include "audio.h"

typedef struct
{
    unsigned char *samples;
    void *allocation;
    uint32_t sample_rate;
    uint32_t sample_count;
    uint32_t padded_size;
    unsigned playing;
    int voice;
} VertrixWiiPcm8;

/* Read the original WAV from VF into a 32-byte aligned/padded ASND buffer.
 * Initialize output to zero; output is preserved on failure. */
int vertrix_wii_pcm8_load(VertrixVf *archive, const char *name, VertrixWiiPcm8 *output);
/* Requires initialized/unpaused ASND and exclusive ownership of voice slot.
 * Volumes are explicit 0..255; original event scheduling is handled elsewhere.
 * Each clip owns at most one voice. Replay stops its previous voice first. */
int vertrix_wii_pcm8_play(VertrixWiiPcm8 *audio, int voice, unsigned left, unsigned right);
void vertrix_wii_pcm8_stop(VertrixWiiPcm8 *audio);
/* Stops the owned voice before releasing sample storage. */
void vertrix_wii_pcm8_free(VertrixWiiPcm8 *audio);
#endif
