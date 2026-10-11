#ifndef VERTRIX_LIFT_RUNTIME_H
#define VERTRIX_LIFT_RUNTIME_H
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "actor_build.h"

/* Runtime of the routines lifted by tools/lift.py: the registers, stack and flags of the
 * original and the memory and call boundaries. The stack is a byte array covering the bytes below
 * the entry esp the routine may read before writing, the return slot and the incoming arguments. */

enum
{
    LIFT_GLOBAL_STORE = 0xf0000000u,
    /* The most argument dwords a caller hands over (the dispatcher's LIFTED_MAX_ARGUMENTS). */
    LIFT_PASSED_LIMIT = 17
};

typedef struct LiftFlags
{
    uint32_t zf;
    uint32_t sf;
    uint32_t cf;
    uint32_t of;
    uint32_t pf;
    uint32_t df;
} LiftFlags;

typedef struct LiftEntry
{
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t esi;
    uint32_t edi;
    uint32_t ebp;
    uint32_t esp;              /* address of the return slot */
    const uint32_t *arguments; /* the dwords above the return slot */
    const uint8_t *garbage;    /* the stack bytes below esp (stack size of them) */
    uint32_t chain;
    /* The argument dwords the caller supplied in `arguments`, or 0 when only the routine's own
     * count is available. A cdecl routine with a variable list (sprintf 0x4cdfb0) declares fewer
     * arguments than its callers push; the rest are mapped above the declared ones. */
    unsigned passed;
} LiftEntry;

typedef struct LiftEnv
{
    const VertrixCalls *calls;
    const VertrixFactoryServices *services;
    const VertrixGlobals *globals;
    uint8_t *stack;
    uint32_t low;
    uint32_t high;
    uint32_t chain;
    int failed;
    /* The supplied arguments beyond the declared ones and the slot after them, little-endian, at
     * passed_low..passed_high (directly above the frame). */
    uint32_t passed_low;
    uint32_t passed_high;
    uint8_t passed[4 * LIFT_PASSED_LIMIT];
} LiftEnv;

/* The stack frames of the lifted routines now executing, outermost first, so the host side of
 * the call boundary can read the strings and structures a routine builds in its locals. The
 * dispatcher sets the index before it runs a routine. Weak: every translation unit shares them. */
enum
{
    LIFT_FRAME_LIMIT = 17
};
__attribute__((weak)) const LiftEnv *vertrix_lift_frames[LIFT_FRAME_LIMIT];
__attribute__((weak)) unsigned vertrix_lift_frame_index;
/* EDX returned by lifted routines and native arithmetic helpers. lift_call seeds this slot
 * with incoming EDX; native arithmetic exposes its output through out_value. */
__attribute__((weak)) uint32_t vertrix_lift_edx;
/* The flags a lifted routine leaves for its caller (RTL compare helpers answer in the flags). */
__attribute__((weak)) LiftFlags vertrix_lift_fl;

static inline void lift_put(uint8_t *bytes, unsigned size, uint32_t value);

/* An x87 instruction: the port has no coprocessor, so the runtime's x87 paths must not run. */
static inline void lift_x87(LiftEnv *env, uint32_t address)
{
    fprintf(stderr, "lifted x87 instruction at 0x%x reached\n", (unsigned)address);
    env->failed = 1;
}

/* A routine with a static frame (tools/lift.py, STATIC_FRAME) was entered while it ran. */
static inline void lift_reentered(uint32_t address)
{
    fprintf(stderr, "lifted 0x%x entered again; its frame is static\n", (unsigned)address);
    abort();
}

static inline void lift_begin(LiftEnv *env, const VertrixCalls *calls,
                              const VertrixFactoryServices *services, const VertrixGlobals *globals,
                              uint8_t *stack, uint32_t below, unsigned argument_count,
                              const LiftEntry *entry)
{
    unsigned i;
    env->calls = calls;
    env->services = services;
    env->globals = globals;
    env->stack = stack;
    env->low = entry->esp - below;
    env->high = entry->esp + 4 + 4 * argument_count + 4;
    env->chain = entry->chain;
    env->failed = 0;
    if (vertrix_lift_frame_index < LIFT_FRAME_LIMIT)
    {
        vertrix_lift_frames[vertrix_lift_frame_index] = env;
    }
    memcpy(stack, entry->garbage, below);
    memset(stack + below, 0, 4 + 4 * argument_count + 4);
    for (i = 0; i < argument_count; i++)
    {
        lift_put(stack + below + 4 + 4 * i, 4, entry->arguments[i]);
    }
    env->passed_low = env->high;
    env->passed_high = env->high;
    if (entry->passed > argument_count && entry->passed <= LIFT_PASSED_LIMIT)
    {
        /* The slot after the declared arguments is in the frame; the rest go above it. */
        lift_put(stack + below + 4 + 4 * argument_count, 4, entry->arguments[argument_count]);
        for (i = argument_count + 1; i < entry->passed; i++)
        {
            lift_put(env->passed + 4 * (i - argument_count - 1), 4, entry->arguments[i]);
        }
        env->passed_high = env->high + 4 * (entry->passed - argument_count - 1);
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

static inline int lift_in_stack(const LiftEnv *env, uint32_t address, unsigned size)
{
    return address >= env->low && (uint64_t)address + size <= env->high;
}

static inline int lift_in_passed(const LiftEnv *env, uint32_t address, unsigned size)
{
    return address >= env->passed_low && (uint64_t)address + size <= env->passed_high;
}

static inline uint32_t lift_load(LiftEnv *env, uint32_t base, uint32_t offset, unsigned size)
{
    uint32_t address = base + offset;
    void *storage;
    size_t length;
    uint32_t value;
    if (lift_in_stack(env, address, size))
    {
        return lift_get(env->stack + (address - env->low), size);
    }
    if (lift_in_passed(env, address, size))
    {
        return lift_get(env->passed + (address - env->passed_low), size);
    }
    if (base != 0 && env->services->resolve(base, &storage, &length, env->services->context) &&
        vertrix_actor_storage_read(storage, length, offset, size, &value))
    {
        return value;
    }
    if (offset != 0 && env->services->resolve(address, &storage, &length, env->services->context) &&
        vertrix_actor_storage_read(storage, length, 0, size, &value))
    {
        /* a negative displacement from an interior pointer, or an object address in the offset
         * (0x4875a0 stores through [esi + eax] with esi = 0 and eax = the array) */
        return value;
    }
    return env->globals->read(address, env->globals->context) & lift_mask(size);
}

extern uint32_t vertrix_debug_watch;
static inline void lift_store(LiftEnv *env, uint32_t base, uint32_t offset, unsigned size,
                              uint32_t value)
{
    uint32_t address = base + offset;
    if (vertrix_debug_watch != 0 && vertrix_debug_watch >= address &&
        vertrix_debug_watch < address + size)
    {
        printf("WATCH store %x size %u = %x\n", (unsigned)address, size, (unsigned)value);
    }
    if (lift_in_stack(env, address, size))
    {
        lift_put(env->stack + (address - env->low), size, value);
    }
    else if (lift_in_passed(env, address, size))
    {
        lift_put(env->passed + (address - env->passed_low), size, value);
    }
    else if (base == 0)
    {
        uint32_t stack[1] = {size};
        if (offset == 0 || !vertrix_build_store(env->services, address, 0, size, value))
        {
            vertrix_calln(env->calls, LIFT_GLOBAL_STORE, address, value, 0, 0, stack, 1, NULL);
        }
    }
    else if (!vertrix_build_store(env->services, base, offset, size, value) &&
             !(base != 0 && offset != 0 &&
               vertrix_build_store(env->services, address, 0, size, value)))
    {
        uint32_t stack[1] = {size};
        vertrix_calln(env->calls, LIFT_GLOBAL_STORE, address, value, 0, 0, stack, 1, NULL);
    }
}

/* A call of an unrecovered routine; the `count` dwords at esp are its stack arguments. The
 * callees that store a dword through the pointer in eax (AnsiString locals) also do so here. */
static inline uint32_t lift_call(LiftEnv *env, uint32_t target, uint32_t eax, uint32_t edx,
                                 uint32_t ebx, uint32_t ecx, unsigned count, uint32_t esp)
{
    uint32_t stack[32] = {0};
    uint32_t out = 0;
    uint32_t result;
    unsigned i;
    vertrix_lift_edx = edx; /* a callee that returns a pair leaves its edx here */
    if (count > 32)
    {
        env->failed = 1;
        count = 32;
    }
    for (i = 0; i < count; i++)
    {
        stack[i] = lift_load(env, esp, 4 * i, 4);
    }
    result = vertrix_calln(env->calls, target, eax, edx, ebx, ecx, stack, count, &out);
    /* A lifted callee has already stored through eax and leaves out 0; only the native ones
     * report the string in out. (Storing out when a lifted assignment kept its buffer wrote 0
     * over the string: 0x4b65d0 called from 0x4b3210 lost the menu labels.) */
    if ((target == 0x4ca280 || target == 0x4ca370) && out != 0)
    {
        lift_store(env, eax, 0, 4, out);
    }
    else if (target == 0x4f175c && count >= 5)
    {
        lift_store(env, stack[4], 0, 4, out); /* CoCreateInstance stores the interface */
    }
    if ((target == 0x4db507 || target == 0x4eb652 || target == 0x4db350 || target == 0x4d809c ||
         target == 0x4d80a6 || target == 0x4d8177 || target == 0x4d81fe))
    {
        vertrix_lift_edx = out;
    }
    return result;
}

static inline uint32_t lift_flags_value(unsigned bits, uint64_t result, LiftFlags *fl)
{
    uint32_t mask = bits >= 32 ? 0xffffffffu : (1u << bits) - 1u;
    uint32_t value = (uint32_t)result & mask;
    uint32_t low = value & 0xffu;
    low ^= low >> 4;
    low ^= low >> 2;
    low ^= low >> 1;
    fl->zf = value == 0;
    fl->sf = (value >> (bits - 1)) & 1u;
    fl->pf = !(low & 1u);
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

static inline uint32_t lift_adc(unsigned bits, uint32_t a, uint32_t b, LiftFlags *fl)
{
    uint32_t mask = bits >= 32 ? 0xffffffffu : (1u << bits) - 1u;
    uint64_t wide = (uint64_t)(a & mask) + (b & mask) + fl->cf;
    uint32_t value = lift_flags_value(bits, wide, fl);
    fl->cf = (uint32_t)((wide >> bits) & 1u);
    fl->of = (((a ^ value) & (b ^ value)) >> (bits - 1)) & 1u;
    return value;
}

static inline uint32_t lift_sbb(unsigned bits, uint32_t a, uint32_t b, LiftFlags *fl)
{
    uint32_t mask = bits >= 32 ? 0xffffffffu : (1u << bits) - 1u;
    uint32_t borrow = fl->cf;
    uint64_t wide = (uint64_t)(a & mask) - (b & mask) - borrow;
    uint32_t value = lift_flags_value(bits, wide, fl);
    fl->cf = (uint64_t)(a & mask) < (uint64_t)(b & mask) + borrow;
    fl->of = (((a ^ b) & (a ^ value)) >> (bits - 1)) & 1u;
    return value;
}

static inline uint32_t lift_rol(unsigned bits, uint32_t a, uint32_t count, LiftFlags *fl)
{
    uint32_t mask = bits >= 32 ? 0xffffffffu : (1u << bits) - 1u;
    uint32_t value = a & mask;
    count &= 31u;
    if (count == 0)
    {
        return a;
    }
    count %= bits;
    if (count != 0)
    {
        value = ((value << count) | (value >> (bits - count))) & mask;
    }
    fl->cf = value & 1u;
    fl->of = ((value >> (bits - 1)) & 1u) ^ fl->cf;
    return value;
}

static inline uint32_t lift_ror(unsigned bits, uint32_t a, uint32_t count, LiftFlags *fl)
{
    uint32_t mask = bits >= 32 ? 0xffffffffu : (1u << bits) - 1u;
    uint32_t value = a & mask;
    count &= 31u;
    if (count == 0)
    {
        return a;
    }
    count %= bits;
    if (count != 0)
    {
        value = ((value >> count) | (value << (bits - count))) & mask;
    }
    fl->cf = (value >> (bits - 1)) & 1u;
    fl->of = ((value >> (bits - 1)) ^ (value >> (bits - 2))) & 1u;
    return value;
}

static inline uint32_t lift_rcl(unsigned bits, uint32_t a, uint32_t count, LiftFlags *fl)
{
    uint32_t mask = bits >= 32 ? 0xffffffffu : (1u << bits) - 1u;
    uint32_t value = a & mask;
    unsigned i;
    count &= 31u;
    if (bits < 32)
    {
        count %= bits + 1;
    }
    for (i = 0; i < count; i++)
    {
        uint32_t out = (value >> (bits - 1)) & 1u;
        value = ((value << 1) | fl->cf) & mask;
        fl->cf = out;
    }
    if (count != 0)
    {
        fl->of = ((value >> (bits - 1)) & 1u) ^ fl->cf;
    }
    return count == 0 ? a : value;
}

static inline uint32_t lift_rcr(unsigned bits, uint32_t a, uint32_t count, LiftFlags *fl)
{
    uint32_t mask = bits >= 32 ? 0xffffffffu : (1u << bits) - 1u;
    uint32_t value = a & mask;
    unsigned i;
    count &= 31u;
    if (bits < 32)
    {
        count %= bits + 1;
    }
    if (count != 0)
    {
        fl->of = ((value >> (bits - 1)) & 1u) ^ fl->cf;
    }
    for (i = 0; i < count; i++)
    {
        uint32_t out = value & 1u;
        value = (value >> 1) | (fl->cf << (bits - 1));
        fl->cf = out;
    }
    return count == 0 ? a : value;
}

static inline uint32_t lift_bsr(uint32_t a)
{
    uint32_t i = 31;
    while (!((a >> i) & 1u))
    {
        i--;
    }
    return i;
}

static inline uint32_t lift_bsf(uint32_t a)
{
    uint32_t i = 0;
    while (!((a >> i) & 1u))
    {
        i++;
    }
    return i;
}

/* One-operand mul/imul/div/idiv on al/ax/eax with the dx/edx high half. */
static inline void lift_mul1(unsigned bits, uint32_t a, uint32_t *eax, uint32_t *edx, LiftFlags *fl)
{
    uint64_t wide;
    if (bits == 8)
    {
        wide = (uint64_t)(*eax & 0xffu) * (a & 0xffu);
        *eax = (*eax & 0xffff0000u) | (uint32_t)(wide & 0xffffu);
        fl->cf = fl->of = (wide >> 8) != 0;
    }
    else if (bits == 16)
    {
        wide = (uint64_t)(*eax & 0xffffu) * (a & 0xffffu);
        *eax = (*eax & 0xffff0000u) | (uint32_t)(wide & 0xffffu);
        *edx = (*edx & 0xffff0000u) | (uint32_t)((wide >> 16) & 0xffffu);
        fl->cf = fl->of = (wide >> 16) != 0;
    }
    else
    {
        wide = (uint64_t)*eax * a;
        *eax = (uint32_t)wide;
        *edx = (uint32_t)(wide >> 32);
        fl->cf = fl->of = *edx != 0;
    }
}

static inline void lift_imul1(unsigned bits, uint32_t a, uint32_t *eax, uint32_t *edx,
                              LiftFlags *fl)
{
    int64_t wide;
    if (bits == 8)
    {
        wide = (int64_t)(int8_t)*eax * (int8_t)a;
        *eax = (*eax & 0xffff0000u) | (uint32_t)(wide & 0xffffu);
        fl->cf = fl->of = wide != (int8_t)wide;
    }
    else if (bits == 16)
    {
        wide = (int64_t)(int16_t)*eax * (int16_t)a;
        *eax = (*eax & 0xffff0000u) | (uint32_t)(wide & 0xffffu);
        *edx = (*edx & 0xffff0000u) | (uint32_t)((wide >> 16) & 0xffffu);
        fl->cf = fl->of = wide != (int16_t)wide;
    }
    else
    {
        wide = (int64_t)(int32_t)*eax * (int32_t)a;
        *eax = (uint32_t)wide;
        *edx = (uint32_t)((uint64_t)wide >> 32);
        fl->cf = fl->of = wide != (int32_t)wide;
    }
}

static inline void lift_div1(unsigned bits, uint32_t a, uint32_t *eax, uint32_t *edx, LiftFlags *fl)
{
    (void)fl;
    if (bits == 8)
    {
        uint32_t n = *eax & 0xffffu;
        uint32_t d = a & 0xffu;
        if (d != 0 && n / d <= 0xffu)
        {
            *eax = (*eax & 0xffff0000u) | ((n % d) << 8) | (n / d);
        }
    }
    else if (bits == 16)
    {
        uint32_t n = ((*edx & 0xffffu) << 16) | (*eax & 0xffffu);
        uint32_t d = a & 0xffffu;
        if (d != 0 && n / d <= 0xffffu)
        {
            *eax = (*eax & 0xffff0000u) | (n / d);
            *edx = (*edx & 0xffff0000u) | (n % d);
        }
    }
    else
    {
        uint64_t n = ((uint64_t)*edx << 32) | *eax;
        if (a != 0 && n / a <= 0xffffffffu)
        {
            *eax = (uint32_t)(n / a);
            *edx = (uint32_t)(n % a);
        }
    }
}

static inline void lift_idiv1(unsigned bits, uint32_t a, uint32_t *eax, uint32_t *edx,
                              LiftFlags *fl)
{
    (void)fl;
    if (bits == 8)
    {
        int32_t n = (int16_t)*eax;
        int32_t d = (int8_t)a;
        if (d != 0 && n / d >= -128 && n / d <= 127)
        {
            *eax = (*eax & 0xffff0000u) | (((uint32_t)(n % d) & 0xffu) << 8) |
                   ((uint32_t)(n / d) & 0xffu);
        }
    }
    else if (bits == 16)
    {
        int32_t n = (int32_t)(((*edx & 0xffffu) << 16) | (*eax & 0xffffu));
        int32_t d = (int16_t)a;
        if (d != 0 && n / d >= -32768 && n / d <= 32767)
        {
            *eax = (*eax & 0xffff0000u) | ((uint32_t)(n / d) & 0xffffu);
            *edx = (*edx & 0xffff0000u) | ((uint32_t)(n % d) & 0xffffu);
        }
    }
    else
    {
        int64_t n = (int64_t)(((uint64_t)*edx << 32) | *eax);
        int64_t d = (int32_t)a;
        if (d != 0 && n / d >= INT32_MIN && n / d <= INT32_MAX && !(n == INT64_MIN && d == -1))
        {
            *eax = (uint32_t)(n / d);
            *edx = (uint32_t)(n % d);
        }
    }
}

/* movs/stos/lods/scas/cmps (kind 0..4) with the optional rep prefix (0 none, 1 rep, 2 repe,
 * 3 repne); the direction flag is clear. Only scas/cmps test ZF: on movs/stos/lods an F2/F3
 * prefix is a plain rep, as the Delphi runtime emits F2 A5/A4. */
static inline void lift_string(LiftEnv *env, int kind, unsigned size, int repeat, uint32_t *eax,
                               uint32_t *ecx, uint32_t *esi, uint32_t *edi, LiftFlags *fl)
{
    uint32_t step = fl->df ? (uint32_t)(0u - size) : size;
    for (;;)
    {
        uint32_t a, b;
        if (repeat != 0 && *ecx == 0)
        {
            return;
        }
        switch (kind)
        {
            case 0:
                lift_store(env, *edi, 0, size, lift_load(env, *esi, 0, size));
                *esi += step;
                *edi += step;
                break;
            case 1:
                lift_store(env, *edi, 0, size, *eax);
                *edi += step;
                break;
            case 2:
                a = lift_load(env, *esi, 0, size);
                *eax = size == 4 ? a : (*eax & ~lift_mask(size)) | a;
                *esi += step;
                break;
            case 3:
                (void)lift_sub(size * 8, *eax, lift_load(env, *edi, 0, size), fl);
                *edi += step;
                break;
            default:
                a = lift_load(env, *esi, 0, size);
                b = lift_load(env, *edi, 0, size);
                (void)lift_sub(size * 8, a, b, fl);
                *esi += step;
                *edi += step;
                break;
        }
        if (repeat == 0)
        {
            return;
        }
        *ecx -= 1u;
        if (kind >= 3 && ((repeat == 2 && !fl->zf) || (repeat == 3 && fl->zf)))
        {
            return;
        }
    }
}

static inline uint32_t lift_shld(unsigned bits, uint32_t a, uint32_t b, uint32_t count,
                                 LiftFlags *fl)
{
    uint32_t mask = bits >= 32 ? 0xffffffffu : (1u << bits) - 1u;
    uint64_t wide;
    count &= 31u;
    if (count == 0 || count > bits)
    {
        return a;
    }
    wide = (((uint64_t)(a & mask) << bits) | (b & mask)) << count;
    fl->cf = (uint32_t)((wide >> (2 * bits)) & 1u);
    return lift_flags_value(bits, wide >> bits, fl);
}

static inline uint32_t lift_shrd(unsigned bits, uint32_t a, uint32_t b, uint32_t count,
                                 LiftFlags *fl)
{
    uint32_t mask = bits >= 32 ? 0xffffffffu : (1u << bits) - 1u;
    uint64_t wide;
    count &= 31u;
    if (count == 0 || count > bits)
    {
        return a;
    }
    wide = (((uint64_t)(b & mask) << bits) | (a & mask));
    fl->cf = (uint32_t)((wide >> (count - 1)) & 1u);
    return lift_flags_value(bits, wide >> count, fl);
}
#endif
