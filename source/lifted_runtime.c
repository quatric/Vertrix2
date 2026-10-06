#include "lifted_runtime.h"
#include "call_glue.h"

static int in_stack(const LiftContext *context, uint32_t address, unsigned width)
{
    return address >= context->stack_low &&
           (uint64_t)address + width <= (uint64_t)context->stack_low + context->stack_size;
}

static uint32_t global_read(LiftContext *context, uint32_t address, unsigned width)
{
    const VertrixEffectServices *services = context->services;
    uint32_t value;
    if (!services || !services->global)
    {
        context->failed = 1;
        return 0;
    }
    value = services->global(address, services->global_context);
    return value & vertrix_lift_mask(width);
}

static void global_write(LiftContext *context, uint32_t address, unsigned width, uint32_t value)
{
    const VertrixEffectServices *services = context->services;
    uint32_t old;
    uint32_t mask = vertrix_lift_mask(width);
    if (!services || !services->global || !services->global_write)
    {
        context->failed = 1;
        return;
    }
    old = services->global(address, services->global_context);
    services->global_write(address, (old & ~mask) | (value & mask), services->global_context);
}

uint32_t vertrix_lift_read(LiftContext *context, uint32_t address, unsigned width, uint32_t base)
{
    const VertrixEffectServices *services = context->services;
    uint32_t value = 0;
    if (in_stack(context, address, width))
    {
        memcpy(&value, context->stack + (address - context->stack_low), width / 8);
        return value;
    }
    if (base && services && services->resolve)
    {
        void *storage;
        size_t size;
        if (services->resolve(base, &storage, &size, services->resolve_context))
        {
            uint32_t offset = address - base;
            if (vertrix_actor_storage_read(storage, size, offset, width / 8, &value))
            {
                return value;
            }
            context->failed = 1;
            return 0;
        }
    }
    return global_read(context, address, width);
}

void vertrix_lift_write(LiftContext *context, uint32_t address, unsigned width, uint32_t value,
                        uint32_t base)
{
    const VertrixEffectServices *services = context->services;
    if (in_stack(context, address, width))
    {
        memcpy(context->stack + (address - context->stack_low), &value, width / 8);
        return;
    }
    if (base && services && services->resolve)
    {
        void *storage;
        size_t size;
        if (services->resolve(base, &storage, &size, services->resolve_context))
        {
            if (!vertrix_actor_storage_write(storage, size, address - base, width / 8, value))
            {
                context->failed = 1;
            }
            return;
        }
    }
    global_write(context, address, width, value);
}

uint32_t vertrix_lift_call(LiftContext *context, uint32_t target, uint32_t eax, uint32_t edx,
                           uint32_t ebx, uint32_t ecx, uint32_t esp, unsigned count)
{
    uint32_t stack[11] = {0};
    unsigned i;
    if (!context->services || !context->services->calls)
    {
        context->failed = 1;
        return 0;
    }
    for (i = 0; i < count && i < 11; ++i)
    {
        stack[i] = vertrix_lift_read(context, esp + 4u * i, 32, 0);
    }
    return vertrix_calln(context->services->calls, target, eax, edx, ebx, ecx, stack,
                         count > 11 ? 11 : count, NULL);
}

uint32_t vertrix_lift_virtual(LiftContext *context, uint32_t object, uint32_t slot)
{
    const VertrixEffectServices *services = context->services;
    if (!services || !services->virtual_call)
    {
        context->failed = 1;
        return 0;
    }
    return (uint32_t)services->virtual_call(services->virtual_context, object, slot, 0);
}
