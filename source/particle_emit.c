#include "particle_emit.h"
#include "actor_storage.h"

enum
{
    BYTE_WIDTH = 1,
    WORD_WIDTH = 2,
    DWORD_WIDTH = 4,
    EMITTER_MODE = 0x94c,
    MODE_PICK = 1,
    ENTRY_STRIDE = 28,
    ENTRY_BASE = 0x544ac0,
    ENTRY_DRAWS = 7,
    SPREAD = 0x32,
    RNG_STATE = 0x598d30
};

static uint32_t draw(const VertrixCalls *calls, uint32_t emitter, uint32_t particle,
                     uint32_t divisor)
{
    return vertrix_call(calls, 0x4826c0, RNG_STATE, divisor, emitter, particle, 0);
}

static int put(void *storage, size_t size, size_t offset, unsigned width, uint32_t value)
{
    return vertrix_actor_storage_write(storage, size, offset, width, value);
}

static uint32_t spread_word(uint32_t drawn, uint16_t half)
{
    uint32_t t = (drawn & 0xffff0000u) | (uint16_t)((uint16_t)drawn - half);
    return t * SPREAD;
}

uint32_t vertrix_particle_emit(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               uint32_t emitter, const void *emitter_storage, size_t emitter_size,
                               uint32_t particle, void *particle_storage, size_t particle_size,
                               const VertrixParticleScreen *screen, VertrixParticleScratch *scratch)
{
    uint32_t mode;
    uint32_t edx;
    uint32_t product;
    (void)services;
    scratch->scratch[0] = screen->width;
    scratch->scratch[1] = screen->height;
    scratch->scratch[2] = (uint16_t)(screen->width / 2);
    scratch->scratch[3] = (uint16_t)(screen->height / 2);
    if (!put(particle_storage, particle_size, 0x70, DWORD_WIDTH, 0) ||
        !vertrix_actor_storage_read(emitter_storage, emitter_size, EMITTER_MODE, DWORD_WIDTH,
                                    &mode))
    {
        return 0;
    }
    if (mode != MODE_PICK)
    {
        uint32_t pick = draw(calls, emitter, particle, ENTRY_DRAWS) & 0xffff;
        uint32_t delay;
        vertrix_call(calls, 0x4ac8d0, particle, ENTRY_BASE + ENTRY_STRIDE * pick, emitter, particle,
                     0);
        if (!put(particle_storage, particle_size, 0x52, BYTE_WIDTH, 0xd))
        {
            return 0;
        }
        vertrix_call(calls, 0x4ac7b0, particle, 2, emitter, particle, 0);
        delay = vertrix_call(calls, 0x415470, pick, 2, emitter, particle, 0);
        vertrix_call(calls, 0x4ac490, particle, delay, emitter, particle, 0);
        vertrix_call(calls, 0x4ac710, particle, 0, emitter, particle, 0);
        edx = 0;
    }
    else if ((draw(calls, emitter, particle, 2) & 0xffff) == 0)
    {
        uint32_t color;
        uint32_t life;
        vertrix_call(calls, 0x4ac8d0, particle, 0x544c2c, emitter, particle, 0);
        color = draw(calls, emitter, particle, 0xe);
        if (!put(particle_storage, particle_size, 0x52, BYTE_WIDTH, color & 0xff))
        {
            return 0;
        }
        vertrix_call(calls, 0x4ac7b0, particle, 2, emitter, particle, 0);
        life = draw(calls, emitter, particle, 5) & 0xffff;
        edx = life + 2;
        vertrix_call(calls, 0x4ac470, particle, edx, emitter, particle, 0);
        if (!put(particle_storage, particle_size, 0x93, BYTE_WIDTH, 0))
        {
            return 0;
        }
    }
    else
    {
        uint32_t frame;
        vertrix_call(calls, 0x4ac8d0, particle, 0x544a34, emitter, particle, 0);
        if (!put(particle_storage, particle_size, 0x52, BYTE_WIDTH, 0xd))
        {
            return 0;
        }
        vertrix_call(calls, 0x4ac7d0, particle, 0xa, emitter, particle, 0);
        vertrix_call(calls, 0x4ac470, particle, 100000, emitter, particle, 0);
        frame = draw(calls, emitter, particle, 0x13) & 0xffff;
        edx = frame;
        vertrix_call(calls, 0x4ac710, particle, edx, emitter, particle, 0);
        if (!put(particle_storage, particle_size, 0x93, BYTE_WIDTH, 1) ||
            !put(particle_storage, particle_size, 0x4e, BYTE_WIDTH, 0x32) ||
            !put(particle_storage, particle_size, 0x94, BYTE_WIDTH, 1) ||
            !put(particle_storage, particle_size, 0x95, BYTE_WIDTH, 4))
        {
            return 0;
        }
    }
    vertrix_call(calls, 0x4ac8a0, particle, edx, emitter, particle, 0);
    product = spread_word(draw(calls, emitter, particle, screen->width), scratch->scratch[2]);
    if (!put(particle_storage, particle_size, 0x8, WORD_WIDTH, product & 0xffff))
    {
        return 0;
    }
    product = spread_word(draw(calls, emitter, particle, screen->height), scratch->scratch[3]);
    if (!put(particle_storage, particle_size, 0xe, WORD_WIDTH, 0) ||
        !put(particle_storage, particle_size, 0x16, WORD_WIDTH, 0) ||
        !put(particle_storage, particle_size, 0xa, WORD_WIDTH, product & 0xffff) ||
        !put(particle_storage, particle_size, 0x58, DWORD_WIDTH, 0xc8) ||
        !put(particle_storage, particle_size, 0x5c, DWORD_WIDTH, 0) ||
        !put(particle_storage, particle_size, 0x60, DWORD_WIDTH, 1))
    {
        return 0;
    }
    return product;
}
