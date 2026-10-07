/* Host check: link all source/lifted_*.c with actor_storage.c and call_glue.c. */
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "lifted_dispatch.h"

typedef struct Boundary
{
    unsigned calls;
    VertrixCallSite last;
} Boundary;

static uint32_t boundary_call(VertrixCallSite *site, void *context)
{
    Boundary *boundary = context;
    boundary->calls++;
    boundary->last = *site;
    return 7;
}

static uint32_t read_global(uint32_t address, void *context)
{
    (void)address;
    (void)context;
    assert(0 && "comparator must not read global storage");
    return 0;
}

static int resolve_object(uint32_t handle, void **storage, size_t *length, void *context)
{
    (void)handle;
    (void)storage;
    (void)length;
    (void)context;
    assert(0 && "comparator must not resolve object storage");
    return 0;
}

int main(void)
{
    static const uint32_t values[] = {0, 1, 0x7fffffffu, 0x80000000u, 0xfffffffeu, 0xffffffffu};
    static const uint32_t targets[] = {0x401010, 0x418150, 0x45f1e0, 0x471e10, 0x4725f0, 0x478da0};
    static const uint32_t screens[] = {0x465af0, 0x466d60, 0x46b810, 0x46c9d0};
    Boundary boundary = {0};
    VertrixCalls inner = {boundary_call, &boundary};
    VertrixGlobals globals = {read_global, NULL};
    VertrixFactoryServices services = {0};
    VertrixLiftedCalls adapter;
    VertrixCallSite site = {0};
    unsigned i;
    unsigned j;

    services.resolve = resolve_object;
    vertrix_lifted_calls_init(&adapter, &inner, &services, &globals);
    assert(vertrix_lifted_count() >=
           sizeof targets / sizeof targets[0] + sizeof screens / sizeof screens[0]);
    for (i = 0; i < sizeof targets / sizeof targets[0]; ++i)
    {
        assert(vertrix_lifted_has(targets[i]));
    }
    for (i = 0; i < sizeof screens / sizeof screens[0]; ++i)
    {
        assert(vertrix_lifted_has(screens[i]));
    }
    site.target = 0x418150;
    for (i = 0; i < sizeof values / sizeof values[0]; ++i)
    {
        for (j = 0; j < sizeof values / sizeof values[0]; ++j)
        {
            uint32_t expected = values[i] < values[j] ? UINT32_MAX : values[i] > values[j];
            uint32_t result = 0;
            site.eax = values[i];
            site.edx = values[j];
            assert(vertrix_lifted_dispatch(&adapter.calls, &services, &globals, &site, &result));
            assert(result == expected);
            assert(adapter.calls.call(&site, adapter.calls.context) == expected);
            assert(boundary.calls == 0);
        }
    }
    site.target = 0x401000;
    site.eax = 0x12345678;
    site.edx = 0x87654321;
    site.ebx = 0x80000000u;
    site.ecx = 0xffffffffu;
    site.stack = 0x11223344;
    site.stack_next = 0x55667788;
    site.stack_third = 0x99aabbcc;
    site.stack_rest[13] = 0xddeeff00;
    assert(!vertrix_lifted_has(site.target));
    {
        uint32_t result = 0xabcdef01;
        assert(!vertrix_lifted_dispatch(&adapter.calls, &services, &globals, &site, &result));
        assert(result == 0xabcdef01);
        assert(boundary.calls == 0);
    }
    assert(adapter.calls.call(&site, adapter.calls.context) == 7);
    assert(boundary.calls == 1);
    assert(memcmp(&boundary.last, &site, sizeof site) == 0);
    printf("Dispatch integration passed: %u routines, 36 unsigned cases, one boundary call.\n",
           vertrix_lifted_count());
    return 0;
}
