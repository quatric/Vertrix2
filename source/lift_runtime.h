#ifndef VERTRIX_LIFT_RUNTIME_H
#define VERTRIX_LIFT_RUNTIME_H
#include <stdint.h>
#include <string.h>

#include "actor_build.h"

/* Runtime of the routines lifted by tools/lift.py: the frame of the original, its flags, its
 * pushed arguments and the memory and call boundaries. */

enum
{
    LIFT_STACK_DEPTH = 64,
    LIFT_GLOBAL_STORE = 0xf0000000u
};

typedef struct LiftFlags
{
    uint32_t zf;
    uint32_t sf;
    uint32_t cf;
    uint32_t of;
} LiftFlags;

typedef struct LiftEnv
{
    const VertrixCalls *calls;
    const VertrixFactoryServices *services;
    const VertrixGlobals *globals;
    uint32_t frame;
    uint8_t *local;
    uint32_t locals;
    uint32_t size;
    uint32_t chain;
    uint32_t stack[LIFT_STACK_DEPTH];
    unsigned sp;
    int failed;
} LiftEnv;

static inline void lift_begin(LiftEnv *env, const VertrixCalls *calls,
                              const VertrixFactoryServices *services, const VertrixGlobals *globals,
                              uint32_t frame, uint8_t *local, uint32_t locals,
                              unsigned argument_count, const uint8_t *garbage,
                              const uint32_t *arguments, uint32_t chain)
{
    unsigned i;
    env->calls = calls;
    env->services = services;
    env->globals = globals;
    env->frame = frame;
    env->local = local;
    env->locals = locals;
    env->size = locals + 8 + 4 * argument_count;
    env->chain = chain;
    env->sp = 0;
    env->failed = 0;
    memcpy(local, garbage, locals);
    memset(local + locals, 0, 8 + 4 * argument_count + 4);
    for (i = 0; i < argument_count; i++)
    {
        memcpy(local + locals + 8 + 4 * i, &arguments[i], 4);
    }
}

static inline uint32_t lift_mask(unsigned size)
{
    return size >= 4 ? 0xffffffffu : (1u << (8 * size)) - 1u;
}

static inline uint32_t lift_get(const uint8_t *bytes, unsigned size)
{
    uint32_t value = 0;
    unsigned i;
    for (i = 0; i < size; i++)
    {
        value |= (uint32_t)bytes[i] << (8 * i);
    }
    return value;
}

static inline void lift_put(uint8_t *bytes, unsigned size, uint32_t value)
{
    unsigned i;
    for (i = 0; i < size; i++)
    {
        bytes[i] = (uint8_t)(value >> (8 * i));
    }
}

static inline uint32_t lift_local_read(LiftEnv *env, int32_t disp, unsigned size)
{
    int64_t index = (int64_t)env->locals + disp;
    if (index < 0 || index + size > env->size)
    {
        env->failed = 1;
        return 0;
    }
    return lift_get(env->local + index, size);
}

static inline void lift_local_write(LiftEnv *env, int32_t disp, unsigned size, uint32_t value)
{
    int64_t index = (int64_t)env->locals + disp;
    if (index < 0 || index + size > env->size)
    {
        env->failed = 1;
        return;
    }
    lift_put(env->local + index, size, value);
}

static inline int lift_in_frame(const LiftEnv *env, uint32_t address, unsigned size)
{
    return address >= env->frame - env->locals &&
           (uint64_t)address + size <= (uint64_t)env->frame + (env->size - env->locals);
}

static inline uint32_t lift_load(LiftEnv *env, uint32_t base, uint32_t offset, unsigned size)
{
    uint32_t address = base + offset;
    void *storage;
    size_t length;
    uint32_t value;
    if (lift_in_frame(env, address, size))
    {
        return lift_local_read(env, (int32_t)(address - env->frame), size);
    }
    if (base != 0 && env->services->resolve(base, &storage, &length, env->services->context) &&
        vertrix_actor_storage_read(storage, length, offset, size, &value))
    {
        return value;
    }
    return env->globals->read(address, env->globals->context) & lift_mask(size);
}

static inline void lift_store(LiftEnv *env, uint32_t base, uint32_t offset, unsigned size,
                              uint32_t value)
{
    uint32_t address = base + offset;
    if (lift_in_frame(env, address, size))
    {
        lift_local_write(env, (int32_t)(address - env->frame), size, value);
    }
    else if (base == 0)
    {
        uint32_t stack[1] = {size};
        vertrix_calln(env->calls, LIFT_GLOBAL_STORE, address, value, 0, 0, stack, 1, NULL);
    }
    else if (!vertrix_build_store(env->services, base, offset, size, value))
    {
        env->failed = 1;
    }
}

/* The effects of the callees that store a dword through the pointer in eax (AnsiString locals). */
static inline uint32_t lift_call(LiftEnv *env, uint32_t target, uint32_t eax, uint32_t edx,
                                 uint32_t ebx, uint32_t ecx, unsigned count)
{
    uint32_t stack[LIFT_STACK_DEPTH] = {0};
    uint32_t out = 0;
    uint32_t result;
    unsigned i;
    if (count > env->sp)
    {
        env->failed = 1;
        count = env->sp;
    }
    for (i = 0; i < count; i++)
    {
        stack[i] = env->stack[env->sp - 1 - i];
    }
    env->sp -= count;
    result = vertrix_calln(env->calls, target, eax, edx, ebx, ecx, stack, count, &out);
    if (target == 0x4ca280 || target == 0x4ca370)
    {
        lift_store(env, eax, 0, 4, out);
    }
    return result;
}

static inline uint32_t lift_flags_value(unsigned bits, uint64_t result, LiftFlags *fl)
{
    uint32_t mask = bits >= 32 ? 0xffffffffu : (1u << bits) - 1u;
    uint32_t value = (uint32_t)result & mask;
    fl->zf = value == 0;
    fl->sf = (value >> (bits - 1)) & 1u;
    return value;
}

static inline uint32_t lift_add(unsigned bits, uint32_t a, uint32_t b, LiftFlags *fl)
{
    uint32_t mask = bits >= 32 ? 0xffffffffu : (1u << bits) - 1u;
    uint64_t wide = (uint64_t)(a & mask) + (b & mask);
    uint32_t value = lift_flags_value(bits, wide, fl);
    fl->cf = (uint32_t)((wide >> bits) & 1u);
    fl->of = (((a ^ value) & (b ^ value)) >> (bits - 1)) & 1u;
    return value;
}

static inline uint32_t lift_sub(unsigned bits, uint32_t a, uint32_t b, LiftFlags *fl)
{
    uint32_t mask = bits >= 32 ? 0xffffffffu : (1u << bits) - 1u;
    uint32_t value = lift_flags_value(bits, (uint64_t)(a & mask) - (b & mask), fl);
    fl->cf = (a & mask) < (b & mask);
    fl->of = (((a ^ b) & (a ^ value)) >> (bits - 1)) & 1u;
    return value;
}

static inline uint32_t lift_inc(unsigned bits, uint32_t a, LiftFlags *fl, int unused)
{
    uint32_t keep = fl->cf;
    uint32_t value = lift_add(bits, a, 1, fl);
    (void)unused;
    fl->cf = keep;
    return value;
}

static inline uint32_t lift_dec(unsigned bits, uint32_t a, LiftFlags *fl, int unused)
{
    uint32_t keep = fl->cf;
    uint32_t value = lift_sub(bits, a, 1, fl);
    (void)unused;
    fl->cf = keep;
    return value;
}

static inline uint32_t lift_and(unsigned bits, uint32_t a, uint32_t b, LiftFlags *fl)
{
    uint32_t value = lift_flags_value(bits, (uint64_t)(a & b), fl);
    fl->cf = 0;
    fl->of = 0;
    return value;
}

static inline uint32_t lift_or(unsigned bits, uint32_t a, uint32_t b, LiftFlags *fl)
{
    uint32_t value = lift_flags_value(bits, (uint64_t)(a | b), fl);
    fl->cf = 0;
    fl->of = 0;
    return value;
}

static inline uint32_t lift_xor(unsigned bits, uint32_t a, uint32_t b, LiftFlags *fl)
{
    uint32_t value = lift_flags_value(bits, (uint64_t)(a ^ b), fl);
    fl->cf = 0;
    fl->of = 0;
    return value;
}

static inline int64_t lift_signed(unsigned bits, uint32_t value)
{
    if (bits == 8)
    {
        return (int8_t)value;
    }
    if (bits == 16)
    {
        return (int16_t)value;
    }
    return (int32_t)value;
}

static inline uint32_t lift_imul(unsigned bits, uint32_t a, uint32_t b, LiftFlags *fl)
{
    int64_t wide = lift_signed(bits, a) * lift_signed(bits, b);
    uint32_t value = lift_flags_value(bits, (uint64_t)wide, fl);
    fl->cf = fl->of = wide != lift_signed(bits, value);
    return value;
}

static inline uint32_t lift_shl(unsigned bits, uint32_t a, uint32_t count, LiftFlags *fl)
{
    uint32_t mask = bits >= 32 ? 0xffffffffu : (1u << bits) - 1u;
    uint64_t wide;
    count &= 31u;
    if (count == 0)
    {
        return a;
    }
    wide = (uint64_t)(a & mask) << count;
    fl->cf = (uint32_t)((wide >> bits) & 1u);
    return lift_flags_value(bits, wide, fl);
}

static inline uint32_t lift_shr(unsigned bits, uint32_t a, uint32_t count, LiftFlags *fl)
{
    uint32_t mask = bits >= 32 ? 0xffffffffu : (1u << bits) - 1u;
    uint32_t value = a & mask;
    count &= 31u;
    if (count == 0)
    {
        return a;
    }
    fl->cf = (value >> (count - 1)) & 1u;
    return lift_flags_value(bits, (uint64_t)(value >> count), fl);
}

static inline uint32_t lift_sar(unsigned bits, uint32_t a, uint32_t count, LiftFlags *fl)
{
    int64_t value = lift_signed(bits, a);
    count &= 31u;
    if (count == 0)
    {
        return a;
    }
    fl->cf = (uint32_t)((value >> (count - 1)) & 1);
    return lift_flags_value(bits, (uint64_t)(value >> count), fl);
}
#endif
