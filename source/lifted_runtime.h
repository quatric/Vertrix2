#ifndef VERTRIX_LIFTED_RUNTIME_H
#define VERTRIX_LIFTED_RUNTIME_H
#include "actor_storage.h"
#include "bonus_effects.h"
#include <stdint.h>
#include <string.h>

/* Runtime for routines produced by tools/lift.py. A lifted routine is a statement-for-statement
 * translation of the original x86 code: the registers are C variables, flags are computed as the
 * instructions set them, the jumps are gotos and every access to memory goes through the
 * functions below. Objects are original address tokens resolved to storage by the services; the
 * stack is a shadow buffer whose addresses are the original stack tokens; callees that are not
 * recovered, virtual slots and globals go through the services. */
typedef struct
{
    const VertrixEffectServices *services;
    uint8_t *stack;
    uint32_t stack_low;
    uint32_t stack_size;
    int failed;
    uint32_t steps;
} LiftContext;

/* A lifted routine stops (failed) after this many backward jumps, so that data the original
 * would not loop on cannot hang the caller. */
#define VERTRIX_LIFT_STEP_LIMIT 150000u

/* Reads or writes the original memory at an effective address. base is the register that formed
 * it (zero when the address is absolute or indexed): an object handle resolves to storage, the
 * stack range maps to the shadow stack and the rest is global data. */
uint32_t vertrix_lift_read(LiftContext *context, uint32_t address, unsigned width, uint32_t base);
void vertrix_lift_write(LiftContext *context, uint32_t address, unsigned width, uint32_t value,
                        uint32_t base);

/* A call to an unrecovered routine: registers, then count stack dwords read from esp. */
uint32_t vertrix_lift_call(LiftContext *context, uint32_t target, uint32_t eax, uint32_t edx,
                           uint32_t ebx, uint32_t ecx, uint32_t esp, unsigned count);

/* A virtual call through slot (vtable offset / 4) of the object in eax. */
uint32_t vertrix_lift_virtual(LiftContext *context, uint32_t object, uint32_t slot);

static inline uint32_t vertrix_lift_mask(unsigned width)
{
    return width == 32 ? 0xffffffffu : (1u << width) - 1u;
}

static inline uint32_t vertrix_lift_sign(unsigned width)
{
    return 1u << (width - 1);
}

#endif
