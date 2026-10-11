#ifndef VERTRIX_LIFTED_WHOLE_41_H
#define VERTRIX_LIFTED_WHOLE_41_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_MIXER_PCM8_STEREO_STACK = 116,
    LIFTED_MIXER_PCM16_STEREO_STACK = 116
};

/* Original 0x401328. */
uint32_t lifted_mixer_pcm8_stereo(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x402c18. */
uint32_t lifted_mixer_pcm16_stereo(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);
#endif
