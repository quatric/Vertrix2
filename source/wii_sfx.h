#ifndef VERTRIX_WII_SFX_H
#define VERTRIX_WII_SFX_H
#include "vf.h"

typedef struct VertrixWiiSfx VertrixWiiSfx;

/* Load an uncompressed PCM wave file (8 or 16 bit, mono or stereo) from the archive, as
 * ASND plays it: 16 bit samples little-endian, 8 bit ones unsigned. NULL on failure. */
VertrixWiiSfx *vertrix_wii_sfx_load(VertrixVf *archive, const char *name);

/* Start the sound on an ASND voice with a volume of 0..255 (ASND must be initialized). */
int vertrix_wii_sfx_play(const VertrixWiiSfx *sfx, int voice, unsigned volume);

void vertrix_wii_sfx_free(VertrixWiiSfx *sfx);

#endif
