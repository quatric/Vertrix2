#ifndef VERTRIX_WII_MP3_H
#define VERTRIX_WII_MP3_H
#include "vf.h"

typedef struct
{
    unsigned char *samples;
    void *allocation;
    uint32_t sample_rate;
    uint32_t channels;
    uint32_t sample_frames;
    uint32_t byte_count;
    uint32_t padded_size;
} VertrixWiiMp3;

/* Decode original VF MP3 into aligned, padded big-endian signed PCM16.
 * Output must be zero initialized and is preserved on failure. Each decoder
 * is independent; voice allocation/playback is an application responsibility. */
int vertrix_wii_mp3_load(VertrixVf *archive, const char *name, VertrixWiiMp3 *output);
/* Caller must stop any playback referencing samples before cleanup. */
void vertrix_wii_mp3_free(VertrixWiiMp3 *audio);
#endif
