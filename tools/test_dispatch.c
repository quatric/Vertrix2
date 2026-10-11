/* Host check: link every non-Wii source/*.c (the dispatcher reaches the native ports). */
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "lifted_dispatch.h"

typedef struct Boundary
{
    unsigned calls;
    unsigned comparator_calls;
    VertrixCallSite last;
} Boundary;

static uint32_t boundary_call(VertrixCallSite *site, void *context)
{
    Boundary *boundary = context;
    if (site->target == 0x418150)
    {
        boundary->comparator_calls++;
        return site->eax < site->edx ? UINT32_MAX : site->eax > site->edx;
    }
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
    static const uint32_t targets[] = {0x401010, 0x478da0};
    /* Routines whose lift still fails verification (docs/lifted-batch-verification.json). */
    static const uint32_t unlifted[] = {0x415c60, 0x432c00, 0x475090, 0x479450};
    static const uint32_t screens[] = {0x465af0, 0x466d60, 0x46b810, 0x46c9d0};
    static const uint32_t optional[] = {0x423960, 0x44b810};
    static const uint32_t leaves[] = {0x4b9ce0, 0x4bb260, 0x4c5c20, 0x4c6a80, 0x4c93c0};
    Boundary boundary = {0};
    VertrixCalls inner = {boundary_call, &boundary};
    VertrixGlobals globals = {read_global, NULL};
    VertrixFactoryServices services = {0};
    VertrixLiftedCalls adapter;
    VertrixCallSite site = {0};
    unsigned i;
    unsigned j;

    assert(vertrix_lifted_depth() == 0);
    vertrix_lifted_set_trace(0);
    services.resolve = resolve_object;
    vertrix_lifted_calls_init(&adapter, &inner, &services, &globals);
    assert(vertrix_lifted_count() >=
           sizeof targets / sizeof targets[0] + sizeof screens / sizeof screens[0]);
    for (i = 0; i < sizeof targets / sizeof targets[0]; ++i)
    {
        assert(vertrix_lifted_has(targets[i]));
    }
    for (i = 0; i < sizeof unlifted / sizeof unlifted[0]; ++i)
    {
        assert(!vertrix_lifted_has(unlifted[i]));
    }
    for (i = 0; i < sizeof screens / sizeof screens[0]; ++i)
    {
        assert(vertrix_lifted_has(screens[i]));
    }
    for (i = 0; i < sizeof optional / sizeof optional[0]; ++i)
    {
        uint32_t result = 0xabcdef01;
        site.target = optional[i];
        assert(!vertrix_lifted_has(site.target));
        assert(!vertrix_lifted_dispatch(&adapter.calls, &services, &globals, &site, &result));
        assert(result == 0xabcdef01);
        assert(boundary.calls == 0);
    }
    {
        unsigned verified_count = vertrix_lifted_count();
        vertrix_lifted_allow_unverified(1);
        for (i = 0; i < sizeof optional / sizeof optional[0]; ++i)
        {
            assert(vertrix_lifted_has(optional[i]));
        }
        assert(vertrix_lifted_count() == verified_count);
        assert(!vertrix_lifted_has(0x401000));
        {
            Boundary native_boundary = {0};
            VertrixCalls native_inner = {boundary_call, &native_boundary};
            VertrixLiftedCalls native_adapter;
            uint32_t result = 0xabcdef01;
            site.target = 0x48ae00;
            site.eax = 0x12345678;
            assert(!vertrix_lifted_has(site.target));
            assert(!vertrix_lifted_dispatch(&adapter.calls, &services, &globals, &site, &result));
            assert(result == 0xabcdef01);
            vertrix_lifted_calls_init(&native_adapter, &native_inner, &services, &globals);
            assert(native_adapter.calls.call(&site, native_adapter.calls.context) == 7);
            assert(native_boundary.calls == 1);
            assert(memcmp(&native_boundary.last, &site, sizeof site) == 0);
        }
        vertrix_lifted_allow_unverified(0);
        for (i = 0; i < sizeof optional / sizeof optional[0]; ++i)
        {
            assert(!vertrix_lifted_has(optional[i]));
        }
        assert(vertrix_lifted_count() == verified_count);
    }
    for (i = 0; i < sizeof leaves / sizeof leaves[0]; ++i)
    {
        for (j = 0; j < sizeof values / sizeof values[0]; ++j)
        {
            uint32_t result = 0;
            site.target = leaves[i];
            site.eax = values[j];
            assert(vertrix_lifted_dispatch(&adapter.calls, &services, &globals, &site, &result));
            assert(result == values[j]);
            assert(vertrix_lifted_depth() == 0);
            assert(boundary.calls == 0);
        }
    }
    site.target = 0x418150;
    for (i = 0; i < sizeof values / sizeof values[0]; ++i)
    {
        for (j = 0; j < sizeof values / sizeof values[0]; ++j)
        {
            uint32_t expected = values[i] < values[j] ? UINT32_MAX : values[i] > values[j];
            uint32_t result = 0xabcdef01;
            site.eax = values[i];
            site.edx = values[j];
            assert(vertrix_lifted_dispatch(&adapter.calls, &services, &globals, &site, &result));
            assert(result == expected);
            assert(adapter.calls.call(&site, adapter.calls.context) == expected);
            assert(boundary.calls == 0);
        }
    }
    assert(boundary.comparator_calls == 0); /* the verified lift of 0x418150 serves all 36 */
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
