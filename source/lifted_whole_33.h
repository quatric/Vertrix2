#ifndef VERTRIX_LIFTED_WHOLE_33_H
#define VERTRIX_LIFTED_WHOLE_33_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F40B0A0_STACK = 80,
    LIFTED_F40B0D0_STACK = 88,
    LIFTED_F40B110_STACK = 416,
    LIFTED_F40B490_STACK = 216,
    LIFTED_F40C6B0_STACK = 92,
    LIFTED_F40C8D0_STACK = 72,
    LIFTED_F40C950_STACK = 68,
    LIFTED_AUDIO_SAMPLE_GUARD_STACK = 64,
    LIFTED_MIXER_ATTACH_STACK = 72,
    LIFTED_F40CA70_STACK = 68,
    LIFTED_MIXER_STEP_STACK = 72,
    LIFTED_F40CB70_STACK = 68,
    LIFTED_F40CBB0_STACK = 68,
    LIFTED_F40CCF0_STACK = 68,
    LIFTED_F40CD30_STACK = 64,
    LIFTED_MIXER_TEMPO_STACK = 72,
    LIFTED_FONT_MAP_CONSTRUCT_STACK = 72,
    LIFTED_F48B2F0_STACK = 26668
};

/* Original 0x40b0a0. */
uint32_t lifted_f40b0a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40b0d0. */
uint32_t lifted_f40b0d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40b110. */
uint32_t lifted_f40b110(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40b490. */
uint32_t lifted_f40b490(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40c6b0. */
uint32_t lifted_f40c6b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40c8d0. */
uint32_t lifted_f40c8d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40c950. */
uint32_t lifted_f40c950(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40c990. */
uint32_t lifted_audio_sample_guard(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40c9d0. */
uint32_t lifted_mixer_attach(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ca70. */
uint32_t lifted_f40ca70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40cb10. */
uint32_t lifted_mixer_step(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40cb70. */
uint32_t lifted_f40cb70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40cbb0. */
uint32_t lifted_f40cbb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ccf0. */
uint32_t lifted_f40ccf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40cd30. */
uint32_t lifted_f40cd30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40cd40. */
uint32_t lifted_mixer_tempo(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48ab10. */
uint32_t lifted_font_map_construct(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48b2f0. */
uint32_t lifted_f48b2f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);
#endif
