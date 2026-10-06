#include "slide_pair.h"

enum
{
    DWORD_WIDTH = 4,
    WORD_WIDTH = 2,
    SLIDE_ALLOCATE = 0x4ca000,
    SLIDE_SIZE = 0x15c,
    SLIDE_WRAP = 0x4abd70,
    SLIDE_SEH_EDX = 0x4ec1ec,
    SLIDE_SEH_ECX = 0x516248,
    SLIDE_SECOND_ECX = 3,
    SLIDE_VALUE = 0x4ac490,
    SLIDE_PERIOD = 0x4ac7b0,
    SLIDE_BIND = 0x4ac8d0,
    SLIDE_FRAME = 0x4ac710,
    SLIDE_HANDLER = 0x4ac8f0,
    SLIDE_HANDLER_VALUE = 0x44c860,
    SLIDE_REGISTER = 0x4b5e70,
    SLIDE_LIST = 0x54671c,
    SLIDE_KIND = 0,
    SLIDE_X = 0xe,
    SLIDE_Y = 0x16,
    SLIDE_Y_OFFSET = 0x108
};

static int build(const VertrixCalls *calls, const VertrixFactoryServices *services,
                 const VertrixGlobals *globals, uint32_t value, uint32_t edx, uint32_t ecx,
                 uint32_t wrap_ecx, uint32_t kind, uint32_t resource, uint32_t x_global,
                 uint32_t y_global, uint32_t *actor_out)
{
    uint32_t actor = vertrix_call(calls, SLIDE_ALLOCATE, SLIDE_SIZE, edx, 0, ecx, 0);
    if (actor != 0)
    {
        actor = vertrix_call(calls, SLIDE_WRAP, actor, edx, 0, wrap_ecx, 0);
    }
    vertrix_build_init(calls, actor);
    vertrix_call(calls, SLIDE_VALUE, actor, value, 0, 0, 0);
    vertrix_call(calls, SLIDE_PERIOD, actor, 1, 0, 0, 0);
    if (!vertrix_build_store(services, actor, SLIDE_KIND, DWORD_WIDTH, kind))
    {
        return 0;
    }
    vertrix_call(calls, SLIDE_BIND, actor, resource, 0, 0, 0);
    vertrix_call(calls, SLIDE_FRAME, actor, 0, 0, 0, 0);
    if (!vertrix_build_store(services, actor, SLIDE_X, WORD_WIDTH,
                             vertrix_build_global_word(globals, x_global)) ||
        !vertrix_build_store(services, actor, SLIDE_Y, WORD_WIDTH,
                             vertrix_build_global_word(globals, y_global) + SLIDE_Y_OFFSET))
    {
        return 0;
    }
    vertrix_call(calls, SLIDE_HANDLER, actor, SLIDE_HANDLER_VALUE, 0, 0, 0);
    vertrix_call(calls, SLIDE_REGISTER, SLIDE_LIST, actor, 0, 0, 0);
    *actor_out = actor;
    return 1;
}

int vertrix_slide_pair(const VertrixCalls *calls, const VertrixFactoryServices *services,
                       const VertrixGlobals *globals, uint32_t value)
{
    uint32_t first;
    uint32_t second;
    if (!build(calls, services, globals, value, SLIDE_SEH_EDX, SLIDE_SEH_ECX, SLIDE_SEH_ECX, 0x15,
               0x544d44, 0x4f8a48, 0x4f8a4c, &first))
    {
        return 0;
    }
    return build(calls, services, globals, value, first, 0, SLIDE_SECOND_ECX, 0x16, 0x544d60,
                 0x4f8a50, 0x4f8a54, &second);
}
