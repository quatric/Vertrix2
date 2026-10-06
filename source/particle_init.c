#include "particle_init.h"
#include "actor_fields.h"
#include "actor_storage.h"

enum
{
    DRIFT_RESOURCE = 0x544c10,
    DRIFT_FRAME = 15,
    DRIFT_PERIOD_STEPS = 1,
    DRIFT_SCALE = 150,
    DRIFT_FIELD_58 = 0x58,
    DRIFT_VALUE_58 = 200,
    DRIFT_FIELD_5C = 0x5c,
    DRIFT_FIELD_60 = 0x60,
    DRIFT_FIELD_144 = 0x144,
    DRIFT_DRAW_60 = 3,
    FALL_RESOURCE = 0x544c64,
    FALL_FRAME = 0,
    FALL_PERIOD_STEPS = 5,
    FALL_HANDLER = 0x4574a0,
    FALL_FIELD_64 = 0x64,
    FALL_VALUE_64 = 100,
    FALL_FIELD_70 = 0x70,
    FALL_VALUE_70 = 200,
    FIELD_8 = 8,
    FIELD_A = 0xa,
    FIELD_E = 0xe,
    FIELD_16 = 0x16,
    FIELD_93 = 0x93,
    FIELD_4E = 0x4e,
    FIELD_44 = 0x44
};

static int put(void *storage, size_t size, size_t offset, unsigned width, uint32_t value)
{
    return vertrix_actor_storage_write(storage, size, offset, width, value);
}

static int common_setup(void *actor, size_t size, uint32_t resource, uint32_t frame, uint32_t steps,
                        const VertrixBurstHooks *hooks, uint32_t handle)
{
    if (!vertrix_actor_attach_resource(actor, size, resource) ||
        !vertrix_actor_set_frame_index(actor, size, frame))
    {
        return 0;
    }
    hooks->bind_frame(handle, hooks->context);
    return vertrix_actor_set_period_steps(actor, size, steps);
}

int vertrix_particle_init_drift(void *actor, size_t size, uint32_t handle,
                                const VertrixParticleScreen *screen,
                                const VertrixFactoryServices *services,
                                const VertrixBurstHooks *hooks, VertrixParticleScratch *scratch)
{
    uint16_t *s = scratch->scratch;
    uint32_t across, down;
    s[0] = screen->width;
    s[1] = screen->height;
    s[2] = (uint16_t)(screen->width / 2);
    s[3] = (uint16_t)(screen->height / 2);
    if (!common_setup(actor, size, DRIFT_RESOURCE, DRIFT_FRAME, DRIFT_PERIOD_STEPS, hooks,
                      handle) ||
        !put(actor, size, FIELD_E, 2, 0) || !put(actor, size, FIELD_16, 2, 0))
    {
        return 0;
    }
    across = (uint16_t)((services->draw(s[0], services->context) - s[2]) & 0xffff);
    if (!put(actor, size, FIELD_8, 2, (across * DRIFT_SCALE) & 0xffff))
    {
        return 0;
    }
    down = (uint16_t)((services->draw(s[1], services->context) - s[3]) & 0xffff);
    return put(actor, size, DRIFT_FIELD_58, 4, DRIFT_VALUE_58) &&
           put(actor, size, FIELD_A, 2, (down * DRIFT_SCALE) & 0xffff) &&
           put(actor, size, DRIFT_FIELD_5C, 4, 0) &&
           put(actor, size, DRIFT_FIELD_60, 4,
               (uint32_t)(services->draw(DRIFT_DRAW_60, services->context) & 0xffff) + 1) &&
           put(actor, size, DRIFT_FIELD_144, 4, 0);
}

int vertrix_particle_init_fall(void *actor, size_t size, uint32_t handle,
                               const VertrixParticleScreen *screen,
                               const VertrixFactoryServices *services,
                               const VertrixBurstHooks *hooks, VertrixParticleScratch *scratch)
{
    uint32_t across, down, spread;
    scratch->scratch[0] = screen->width;
    scratch->scratch[1] = screen->height;
    if (!common_setup(actor, size, FALL_RESOURCE, FALL_FRAME, FALL_PERIOD_STEPS, hooks, handle) ||
        !put(actor, size, FIELD_8, 2, screen->width) ||
        !put(actor, size, FIELD_A, 2, screen->height))
    {
        return 0;
    }
    across = services->draw(screen->width, services->context);
    if (!put(actor, size, FIELD_E, 2, across))
    {
        return 0;
    }
    down = services->draw(screen->height, services->context);
    if (!put(actor, size, FIELD_16, 2, down) ||
        !vertrix_actor_set_handler(actor, size, FALL_HANDLER) ||
        !put(actor, size, DRIFT_FIELD_58, 4, 0) || !put(actor, size, DRIFT_FIELD_60, 4, 1) ||
        !put(actor, size, FALL_FIELD_70, 4, FALL_VALUE_70) ||
        !put(actor, size, FALL_FIELD_64, 4, FALL_VALUE_64))
    {
        return 0;
    }
    spread = services->draw(FALL_VALUE_70, services->context);
    return put(actor, size, FIELD_93, 1, 1) && put(actor, size, FIELD_4E, 1, 0) &&
           put(actor, size, FIELD_44, 1, 0) &&
           put(actor, size, DRIFT_FIELD_5C, 4, FALL_VALUE_64 + spread);
}

enum
{
    SETUP_SPOT_X = 0x874,
    SETUP_SPOT_Y = 0x8ec,
    SETUP_SPOT_COUNT = 0x964,
    SETUP_PLUME_LIST = 0x864,
    SETUP_FALL_SLOT = 0x870,
    SETUP_FALL_FLAG = 0x968,
    SETUP_PARTICLE_LIST = 0x15c,
    SETUP_ACTOR_SIZE = 0x15c,
    PLUME_RESOURCE = 0x544c48,
    PLUME_HANDLER = 0x457330,
    PLUME_DRAW = 10,
    PLUME_DRAW_BASE = 2,
    PLUME_FIELD_64 = 0x64,
    PLUME_VALUE_64 = 30,
    PLUME_FIELD_70 = 0x70,
    PLUME_VALUE_70 = 180,
    PLUME_RANGE_WIDTH = 151,
    PLUME_FIELD_95 = 0x95,
    PARTICLE_FIELD_58 = 0x58,
    PARTICLE_DRAW_58 = 200,
    FIELD_94 = 0x94
};

/* Allocate, build and place one actor with the zero initialisation of the setup routine. */
static int setup_actor(const VertrixFactoryServices *services, uint32_t *handle, void **storage,
                       size_t *size)
{
    *handle = services->allocate(SETUP_ACTOR_SIZE, services->context);
    return *handle != 0 && services->resolve(*handle, storage, size, services->context) &&
           vertrix_actor_storage_construct(*storage, *size) &&
           vertrix_actor_initialize(*storage, *size, 0, 0, 0, 0, 0, 0, 0);
}

static int scan_spots(void *board, size_t board_size, const VertrixSurface *picture)
{
    uint32_t count = 0;
    for (uint32_t x = 0; x < picture->width; ++x)
    {
        for (uint32_t y = 0; y < picture->height; ++y)
        {
            uint32_t pixel = 0;
            if (!vertrix_surface_read(picture, x, y, &pixel))
            {
                return 0;
            }
            if (pixel != 0 && count < VERTRIX_PARTICLE_SPOTS)
            {
                if (!put(board, board_size, SETUP_SPOT_X + 4 * (size_t)count, 4, x) ||
                    !put(board, board_size, SETUP_SPOT_Y + 4 * (size_t)count, 4, y))
                {
                    return 0;
                }
                ++count;
            }
        }
    }
    return put(board, board_size, SETUP_SPOT_COUNT, 4, count);
}

static int build_plume(void *board, size_t board_size, uint32_t index,
                       const VertrixFactoryServices *services, const VertrixBurstHooks *hooks)
{
    uint32_t handle;
    void *actor;
    size_t size;
    uint32_t steps;
    if (!setup_actor(services, &handle, &actor, &size) ||
        !put(board, board_size, SETUP_PLUME_LIST + 4 * (size_t)index, 4, handle) ||
        !put(actor, size, FIELD_E, 2, 0) || !put(actor, size, FIELD_16, 2, 0) ||
        !common_setup(actor, size, PLUME_RESOURCE, 0, 1, hooks, handle))
    {
        return 0;
    }
    steps = (uint32_t)(services->draw(PLUME_DRAW, services->context) & 0xffff) + PLUME_DRAW_BASE;
    return vertrix_actor_set_d0_steps(actor, size, steps) &&
           put(actor, size, PLUME_FIELD_64, 4, PLUME_VALUE_64) &&
           put(actor, size, PLUME_FIELD_70, 4, PLUME_VALUE_70) &&
           put(actor, size, DRIFT_FIELD_58, 4, 0) && put(actor, size, DRIFT_FIELD_60, 4, 1) &&
           put(actor, size, DRIFT_FIELD_5C, 4,
               (uint32_t)(services->draw(PLUME_RANGE_WIDTH, services->context) & 0xffff) +
                   PLUME_VALUE_64) &&
           put(actor, size, FIELD_93, 1, 1) && put(actor, size, FIELD_4E, 1, 0) &&
           vertrix_actor_set_handler(actor, size, PLUME_HANDLER) &&
           put(actor, size, PLUME_FIELD_95, 1, 4);
}

int vertrix_board_particles_setup(void *board, size_t board_size, uint32_t board_handle,
                                  uint32_t picture_name, const VertrixParticleScreen *screen,
                                  const VertrixFactoryServices *services,
                                  const VertrixBurstHooks *hooks,
                                  const VertrixPictureLoader *loader,
                                  VertrixParticleScratch *drift_scratch,
                                  VertrixParticleScratch *fall_scratch)
{
    const VertrixSurface *picture = loader->load(picture_name, loader->context);
    uint32_t handle;
    void *actor;
    size_t size;
    (void)board_handle;
    if (picture != NULL)
    {
        if (!scan_spots(board, board_size, picture))
        {
            return 0;
        }
        for (uint32_t i = 0; i < VERTRIX_PARTICLE_PLUMES; ++i)
        {
            if (!build_plume(board, board_size, i, services, hooks))
            {
                return 0;
            }
        }
        loader->release(picture, loader->context);
    }
    for (uint32_t i = 0; i < VERTRIX_PARTICLE_COUNT; ++i)
    {
        if (!setup_actor(services, &handle, &actor, &size) ||
            !vertrix_particle_init_drift(actor, size, handle, screen, services, hooks,
                                         drift_scratch) ||
            !put(actor, size, PARTICLE_FIELD_58, 4,
                 services->draw(PARTICLE_DRAW_58, services->context) & 0xffff) ||
            !put(board, board_size, SETUP_PARTICLE_LIST + 4 * (size_t)i, 4, handle))
        {
            return 0;
        }
    }
    if (!setup_actor(services, &handle, &actor, &size) || !put(actor, size, FIELD_94, 1, 1) ||
        !put(actor, size, PLUME_FIELD_95, 1, 4) ||
        !vertrix_particle_init_fall(actor, size, handle, screen, services, hooks, fall_scratch) ||
        !put(board, board_size, SETUP_FALL_SLOT, 4, handle) ||
        !put(board, board_size, SETUP_FALL_FLAG, 4, 0))
    {
        return 0;
    }
    return 1;
}

enum
{
    MARQUEE_RESOURCE = 0x54651c,
    MARQUEE_HANDLER = 0x444850,
    MARQUEE_D0_STEPS = 1,
    MARQUEE_PERIOD_STEPS = 2,
    MARQUEE_FIELD_E0_BASE = 12,
    MARQUEE_CELL_STEP = 22,
    MARQUEE_OFFSET = 16,
    MARQUEE_SPEED = 4,
    MARQUEE_FIELD_24 = 0x24,
    MARQUEE_FIELD_28 = 0x28,
    MARQUEE_FIELD_30 = 0x30,
    MARQUEE_FIELD_32 = 0x32,
    MARQUEE_FIELD_44 = 0x44,
    MARQUEE_FIELD_48 = 0x48,
    MARQUEE_FIELD_OWNER = 4,
    MARQUEE_VALUE_30 = 0x140,
    MARQUEE_VALUE_32 = 5
};

int vertrix_marquee_build(uint32_t owner, uint32_t a, uint32_t b, uint32_t c, uint32_t forward,
                          const VertrixFactoryServices *services, const VertrixBurstHooks *hooks)
{
    for (uint32_t i = 0; i < VERTRIX_MARQUEE_COUNT; ++i)
    {
        uint32_t handle;
        void *actor;
        size_t size;
        if (!setup_actor(services, &handle, &actor, &size) || !put(actor, size, FIELD_E, 2, 0) ||
            !put(actor, size, FIELD_16, 2, 0) ||
            !vertrix_actor_set_d0_steps(actor, size, MARQUEE_D0_STEPS) ||
            !vertrix_actor_set_period_steps(actor, size, MARQUEE_PERIOD_STEPS) ||
            !vertrix_actor_attach_resource(actor, size, MARQUEE_RESOURCE) ||
            !vertrix_actor_set_frame_index(actor, size, 2 * i) || !put(actor, size, FIELD_94, 1, 1))
        {
            return 0;
        }
        hooks->bind_frame(handle, hooks->context);
        if (!put(actor, size, MARQUEE_FIELD_48, 2, (uint32_t)(-MARQUEE_OFFSET) & 0xffff) ||
            !put(actor, size, PLUME_FIELD_95, 1, 4) || !put(actor, size, FIELD_4E, 1, 0x32) ||
            !put(actor, size, MARQUEE_FIELD_24, 2, MARQUEE_CELL_STEP * i) ||
            !put(actor, size, FIELD_93, 1, 1) ||
            !vertrix_actor_set_words_2a(actor, size, (uint16_t)c, (uint16_t)a, (uint16_t)b) ||
            !put(actor, size, MARQUEE_FIELD_28, 2,
                 forward == 1 ? MARQUEE_SPEED : (uint32_t)(-MARQUEE_SPEED) & 0xffff) ||
            !vertrix_actor_set_e0(actor, size, MARQUEE_FIELD_E0_BASE + i) ||
            !put(actor, size, MARQUEE_FIELD_30, 2, MARQUEE_VALUE_30) ||
            !put(actor, size, MARQUEE_FIELD_32, 2, MARQUEE_VALUE_32) ||
            !put(actor, size, MARQUEE_FIELD_44, 1, 0) ||
            !vertrix_actor_set_handler(actor, size, MARQUEE_HANDLER) ||
            !put(actor, size, MARQUEE_FIELD_OWNER, 4, owner))
        {
            return 0;
        }
        hooks->append(VERTRIX_MARQUEE_LIST, handle, hooks->context);
    }
    return 1;
}

enum
{
    ICON_FIRST_X = 59,
    ICON_SECOND_X = 573,
    ICON_Y = 90,
    ICON_FIRST_DATA = 0x13,
    ICON_SECOND_DATA = 0x14,
    ICON_RESOURCE = 0x544a34,
    ICON_INITIAL_HANDLER = 0x448ca0,
    ICON_HANDLER = 0x45d140,
    ICON_PERIOD = 500,
    ICON_E0 = 10,
    ICON_HEADING_LIMIT = 360,
    ICON_SPEED_LIMIT = 2,
    ICON_VALUE_LIMIT = 5,
    ICON_DATA = 0,
    ICON_FIELD_8E = 0x8e,
    ICON_FIELD_8F = 0x8f,
    ICON_FIELD_HEADING = 0x24,
    ICON_FIELD_SPEED = 0x28,
    ICON_FIELD_30 = 0x30,
    ICON_FIELD_58 = 0x58,
    ICON_FIELD_64 = 0x64,
    ICON_FIELD_68 = 0x68,
    ICON_FIELD_70 = 0x70,
    ICON_FIELD_124 = 0x124,
    ICON_FIELD_128 = 0x128,
    ICON_FIELD_12A = 0x12a,
    ICON_FIELD_12C = 0x12c,
    ICON_FIELD_130 = 0x130,
    ICON_FIELD_13C = 0x13c,
    ICON_FIELD_140 = 0x140,
    ICON_FIELD_144 = 0x144,
    ICON_FIELD_150 = 0x150
};

static int build_icon(uint32_t x, uint32_t data, uint32_t frame, uint32_t initial_handler,
                      uint32_t mode, const VertrixFactoryServices *services,
                      const VertrixBurstHooks *hooks)
{
    uint32_t handle;
    void *actor;
    size_t size;
    uint32_t heading, speed, value;
    handle = services->allocate(SETUP_ACTOR_SIZE, services->context);
    if (handle == 0 || !services->resolve(handle, &actor, &size, services->context) ||
        !vertrix_actor_storage_construct(actor, size) ||
        !vertrix_actor_initialize(actor, size, (uint16_t)x, ICON_Y, 0, 0, 0, 0, initial_handler) ||
        !put(actor, size, ICON_DATA, 4, data) || !vertrix_actor_set_ec(actor, size, 0) ||
        !vertrix_actor_attach_resource(actor, size, ICON_RESOURCE) ||
        !vertrix_actor_set_frame_index(actor, size, frame))
    {
        return 0;
    }
    hooks->bind_frame(handle, hooks->context);
    if (mode == 1 &&
        (!put(actor, size, ICON_FIELD_8E, 1, 0) || !put(actor, size, FIELD_A, 2, ICON_Y) ||
         !put(actor, size, ICON_FIELD_8F, 1, 1)))
    {
        return 0;
    }
    heading = services->draw(ICON_HEADING_LIMIT, services->context);
    if (!put(actor, size, ICON_FIELD_HEADING, 2, heading))
    {
        return 0;
    }
    speed = (uint32_t)services->draw(ICON_SPEED_LIMIT, services->context) + 1;
    if (!put(actor, size, ICON_FIELD_SPEED, 2, speed & 0xffff))
    {
        return 0;
    }
    value = services->draw(ICON_VALUE_LIMIT, services->context);
    if (!put(actor, size, ICON_FIELD_30, 2, value) || !vertrix_actor_set_e0(actor, size, ICON_E0) ||
        !put(actor, size, ICON_FIELD_150, 4, 1) || !put(actor, size, ICON_FIELD_64, 4, 0) ||
        !put(actor, size, ICON_FIELD_70, 4, mode) || !put(actor, size, ICON_FIELD_58, 4, frame) ||
        !put(actor, size, ICON_FIELD_68, 4, 0) ||
        !vertrix_actor_set_period(actor, size, ICON_PERIOD) ||
        !vertrix_actor_set_handler(actor, size, ICON_HANDLER) ||
        !put(actor, size, ICON_FIELD_124, 4, 1) || !put(actor, size, ICON_FIELD_128, 2, 0) ||
        !put(actor, size, ICON_FIELD_12A, 2, 0) || !put(actor, size, ICON_FIELD_12C, 4, 0) ||
        !put(actor, size, ICON_FIELD_130, 4, 0) || !put(actor, size, ICON_FIELD_13C, 4, 0) ||
        !put(actor, size, ICON_FIELD_140, 4, 1) ||
        (mode == 2 && !put(actor, size, ICON_FIELD_144, 4, 0)))
    {
        return 0;
    }
    hooks->append(VERTRIX_ICON_LIST, handle, hooks->context);
    return 1;
}

int vertrix_icons_build(uint32_t frame_first, uint32_t frame_second,
                        const VertrixFactoryServices *services, const VertrixBurstHooks *hooks)
{
    return build_icon(ICON_FIRST_X, ICON_FIRST_DATA, frame_first, 0, 1, services, hooks) &&
           build_icon(ICON_SECOND_X, ICON_SECOND_DATA, frame_second, ICON_INITIAL_HANDLER, 2,
                      services, hooks);
}

enum
{
    FRAME_BLOCK_SIZE = 0x160,
    FRAME_FIELD_A8 = 0xa8,
    FRAME_FIELD_AA = 0xaa,
    FRAME_FIELD_AC = 0xac,
    FRAME_FIELD_AE = 0xae,
    FRAME_FIELD_8E = 0x8e,
    FRAME_VALUE_8E = 3,
    FRAME_D0 = 150,
    FRAME_PERIOD_STEPS = 1
};

int vertrix_piece_frames_build(void *piece, size_t piece_size, int16_t left, int16_t width,
                               int16_t top, int16_t height, int16_t step, uint8_t mode,
                               const VertrixFactoryServices *services)
{
    for (uint32_t i = 0; i < VERTRIX_FRAME_COUNT; ++i)
    {
        uint32_t handle = services->allocate(FRAME_BLOCK_SIZE, services->context);
        void *block;
        size_t size;
        int32_t first = top + step * (int32_t)i;
        if (handle == 0 || !services->resolve(handle, &block, &size, services->context) ||
            !vertrix_block_construct(block, size) ||
            !vertrix_actor_initialize(block, size, (uint16_t)left, (uint16_t)first, 0, 0, 0, 0,
                                      0) ||
            !put(block, size, FRAME_FIELD_A8, 2, (uint16_t)left) ||
            !put(block, size, FRAME_FIELD_AA, 2, (uint16_t)(left + width - 1)) ||
            !put(block, size, FRAME_FIELD_AC, 2, (uint16_t)first) ||
            !put(block, size, FRAME_FIELD_AE, 2, (uint16_t)(first + height - 1)) ||
            !put(block, size, FIELD_44, 1, mode) ||
            !put(block, size, FRAME_FIELD_8E, 1, FRAME_VALUE_8E) ||
            !vertrix_actor_set_period_steps(block, size, FRAME_PERIOD_STEPS) ||
            !vertrix_actor_set_d0(block, size, FRAME_D0) ||
            !put(piece, piece_size, VERTRIX_FRAME_LIST + 4 * (size_t)i, 4, handle))
        {
            return 0;
        }
    }
    return 1;
}

int vertrix_board_particles_reset(void *board, size_t board_size)
{
    enum
    {
        PARTICLE_CLASS = 0x514e94,
        DRIFT_BASE = 0x15c,
        DRIFT_COUNT = 450,
        PLUME_BASE = 0x864,
        PLUME_COUNT = 3,
        FALL_BASE = 0x870,
        ACTIVE_FLAG = 0x968
    };
    uint32_t i;
    if (!vertrix_actor_storage_construct(board, board_size) ||
        !vertrix_actor_storage_write(board, board_size, 0x158, 4, PARTICLE_CLASS))
    {
        return 0;
    }
    for (i = 0; i < DRIFT_COUNT; ++i)
    {
        if (!vertrix_actor_storage_write(board, board_size, DRIFT_BASE + 4 * i, 4, 0))
        {
            return 0;
        }
    }
    for (i = 0; i < PLUME_COUNT; ++i)
    {
        if (!vertrix_actor_storage_write(board, board_size, PLUME_BASE + 4 * i, 4, 0))
        {
            return 0;
        }
    }
    if (!vertrix_actor_storage_write(board, board_size, FALL_BASE, 4, 0) ||
        !vertrix_actor_storage_write(board, board_size, ACTIVE_FLAG, 4, 1))
    {
        return 0;
    }
    return 1;
}
