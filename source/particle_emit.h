#ifndef VERTRIX_PARTICLE_EMIT_H
#define VERTRIX_PARTICLE_EMIT_H
#include "block_factory.h"
#include "call_glue.h"
#include "particle_init.h"
#include <stddef.h>
#include <stdint.h>

/* Original 0x43dc80: set up a particle of an emitter on the screen of the given size. The scratch
 * words (0x540fcc..0x540fd2) become width, height, width / 2 and height / 2; the dword +0x70 of
 * the particle is cleared; the emitter's mode (+0x94c) then selects the resource: one picks a
 * resource through a draw below 2 (zero: 0x544c2c with a draw below 14 at +0x52, 0x4ac7b0 with 2,
 * 0x4ac470 with 2 plus a draw below 5 and +0x93 = 0; otherwise 0x544a34 with +0x52 = 0xd, 0x4ac7d0
 * with 10, 0x4ac470 with 100000, 0x4ac710 with a draw below 19, +0x93 = 1, +0x4e = 0x32, +0x94 = 1,
 * +0x95 = 4) and any other mode a draw below 7 selecting the 28-byte entry of 0x544ac0 (+0x52 =
 * 0xd, 0x4ac7b0 with 2, the delay of 0x415470 through 0x4ac490, 0x4ac710 with 0). Every case binds
 * the frame through 0x4ac8a0, places the particle at 50 times a draw below the screen size minus
 * half (words +8 and +0xa, +0xe and +0x16 zero) and stores +0x58 = 200, +0x5c = 0, +0x60 = 1. The
 * emitter and particle handles are what the calls see in ebx and eax. Returns the last product,
 * zero when an object does not resolve. */
uint32_t vertrix_particle_emit(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               uint32_t emitter, const void *emitter_storage, size_t emitter_size,
                               uint32_t particle, void *particle_storage, size_t particle_size,
                               const VertrixParticleScreen *screen,
                               VertrixParticleScratch *scratch);
#endif
