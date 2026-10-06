#include "scene_actors.h"

enum
{
    BYTE_WIDTH = 1,
    DWORD_WIDTH = 4,
    SCENE_ALLOCATE = 0x4ca000,
    SCENE_SIZE = 0x15c,
    SCENE_WRAP = 0x4abd70,
    SCENE_HANDLER = 0x4ac8f0,
    SCENE_DELAY = 0x4ac7d0,
    SCENE_REGISTER = 0x4b5e70,
    SCENE_LIST = 0x54671c,
    DELAY_INDEX = 0x532a64,
    DELAY_TABLE = 0x53bdac,
    DELAY_STRIDE = 180,
    DELAY_BASE = 0x1388,
    DELAY_HANDLER = 0x457770,
    DELAY_KIND = 0xc8,
    BANNER_X = 0x140,
    BANNER_Y = 0xf0,
    BANNER_BIND = 0x4ac8d0,
    BANNER_RESOURCE = 0x544a34,
    BANNER_KIND = 0x13,
    BANNER_FRAME = 0x4ac710,
    BANNER_FRAME_GLOBAL = 0x532a68,
    BANNER_PREPARE = 0x4ac8a0,
    BANNER_PERIOD = 0x4ac7b0,
    BANNER_STEPS = 0x46,
    BANNER_STATE = 0x4e,
    BANNER_SHOWN = 0x93,
    BANNER_FLAG = 0x150,
    BANNER_HANDLER = 0x45ad20
};

static uint32_t allocate(const VertrixCalls *calls, uint32_t edx, uint32_t ebx, uint32_t ecx)
{
    uint32_t actor = vertrix_call(calls, SCENE_ALLOCATE, SCENE_SIZE, edx, ebx, ecx, 0);
    if (actor != 0)
    {
        actor = vertrix_call(calls, SCENE_WRAP, actor, edx, ebx, ecx, 0);
    }
    return actor;
}

uint32_t vertrix_delay_actor_spawn(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, uint32_t edx, uint32_t ebx,
                                   uint32_t ecx)
{
    uint32_t index = globals->read(DELAY_INDEX, globals->context);
    uint32_t entry = globals->read(DELAY_TABLE + index * 4, globals->context);
    uint32_t delay = entry * DELAY_STRIDE + DELAY_BASE;
    uint32_t actor = allocate(calls, edx, ebx, ecx);
    vertrix_build_init(calls, actor);
    vertrix_call(calls, SCENE_HANDLER, actor, DELAY_HANDLER, 0, 0, 0);
    vertrix_call(calls, SCENE_DELAY, actor, delay, 0, 0, 0);
    if (!vertrix_build_store(services, actor, 0, DWORD_WIDTH, DELAY_KIND))
    {
        return 0;
    }
    return vertrix_call(calls, SCENE_REGISTER, SCENE_LIST, actor, 0, 0, 0);
}

uint32_t vertrix_banner_actor_spawn(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, uint32_t edx, uint32_t ebx,
                                    uint32_t ecx)
{
    static const uint32_t zeros[VERTRIX_BUILD_INIT_ARGUMENTS] = {0, 0, 0, 0, 0};
    uint32_t actor = allocate(calls, edx, ebx, ecx);
    vertrix_calln(calls, VERTRIX_BUILD_INIT, actor, BANNER_X, BANNER_Y, 0, zeros,
                  VERTRIX_BUILD_INIT_ARGUMENTS, NULL);
    if (!vertrix_build_store(services, actor, 0, DWORD_WIDTH, BANNER_KIND))
    {
        return 0;
    }
    vertrix_call(calls, BANNER_BIND, actor, BANNER_RESOURCE, BANNER_Y, 0, 0);
    vertrix_call(calls, BANNER_FRAME, actor, globals->read(BANNER_FRAME_GLOBAL, globals->context),
                 BANNER_Y, 0, 0);
    vertrix_call(calls, BANNER_PREPARE, actor, BANNER_STEPS, BANNER_Y, 0, 0);
    if (!vertrix_build_store(services, actor, BANNER_STATE, BYTE_WIDTH, 0x64) ||
        !vertrix_build_store(services, actor, BANNER_SHOWN, BYTE_WIDTH, 0))
    {
        return 0;
    }
    vertrix_call(calls, BANNER_PERIOD, actor, BANNER_STEPS, BANNER_Y, 0, 0);
    if (!vertrix_build_store(services, actor, BANNER_FLAG, DWORD_WIDTH, 1))
    {
        return 0;
    }
    vertrix_call(calls, SCENE_HANDLER, actor, BANNER_HANDLER, BANNER_Y, 0, 0);
    return vertrix_call(calls, SCENE_REGISTER, SCENE_LIST, actor, BANNER_Y, 0, 0);
}

enum
{
    WORD_WIDTH = 2,
    OVERLAY_SIZE = 0x160,
    OVERLAY_WRAP = 0x4b5400,
    OVERLAY_BOX = 0x4b54d0,
    OVERLAY_SOURCE_WIDTH = 4,
    OVERLAY_SOURCE_HEIGHT = 8,
    OVERLAY_TABLE = 0x158,
    OVERLAY_SHOWN = 0x94,
    OVERLAY_OFFSET = 0x48,
    OVERLAY_SHADOW = 0x52,
    OVERLAY_FIRST_SLOT = 8,
    OVERLAY_STEPS = 2
};

static int read_value(const VertrixFactoryServices *services, uint32_t handle, uint32_t offset,
                      unsigned width, uint32_t *value)
{
    void *storage;
    size_t size;
    return services->resolve(handle, &storage, &size, services->context) &&
           vertrix_actor_storage_read(storage, size, offset, width, value);
}

uint32_t vertrix_overlay_spawn(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, uint32_t source, uint32_t edx,
                               uint32_t ebx, uint32_t ecx)
{
    uint32_t actor = vertrix_call(calls, SCENE_ALLOCATE, OVERLAY_SIZE, edx, ebx, ecx, 0);
    uint32_t width;
    uint32_t height;
    uint32_t table;
    if (actor != 0)
    {
        actor = vertrix_call(calls, OVERLAY_WRAP, actor, edx, ebx, ecx, 0);
    }
    vertrix_build_init(calls, actor);
    if (!read_value(services, source, OVERLAY_SOURCE_HEIGHT, WORD_WIDTH, &height) ||
        !read_value(services, source, OVERLAY_SOURCE_WIDTH, WORD_WIDTH, &width))
    {
        return 0;
    }
    vertrix_call(calls, OVERLAY_BOX, actor, 0, 0, width, height);
    if (!vertrix_build_store(services, actor, OVERLAY_SHOWN, BYTE_WIDTH, 0) ||
        !vertrix_build_store(services, actor, OVERLAY_OFFSET, WORD_WIDTH, 0) ||
        !read_value(services, actor, OVERLAY_TABLE, DWORD_WIDTH, &table) ||
        !vertrix_build_store(services, actor, OVERLAY_SHADOW, BYTE_WIDTH, 0))
    {
        return 0;
    }
    vertrix_call(calls, globals->read(table + OVERLAY_FIRST_SLOT, globals->context), actor, source,
                 0, table, 0);
    if (!read_value(services, actor, OVERLAY_TABLE, DWORD_WIDTH, &table))
    {
        return 0;
    }
    return vertrix_call(calls, globals->read(table, globals->context), actor, OVERLAY_STEPS, 0,
                        table, 0);
}
